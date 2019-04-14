//崔雨鸣,2019年4月14日
//mailto:cym2018.xyz@qq.com
# include <iostream>
# include <fstream>
# include "MySocket.h"
# include <time.h>
using namespace std;
// 连接网络
MySocket Library("seat.ujn.edu.cn");
// 打开文件
ifstream file;
ofstream Log;
string getToken(string user, string pass);
string getSeat(string token, string start, string end, string seat, string date);
std::string getTime();
int main(int arc, char** arg) {
	file.open("data.txt");
	Log.open("log.txt", ios::app);
	string user, pass, seat, start, end, ret, token, date;
	date = getTime();
	// 选座
	while (!file.eof()) {
		// 读取文件
		file >> user >> pass >> seat >> start >> end;
		// 获取token
		token=getToken(user, pass);
		// 失败后隔一秒重试
		if (token == "") {
			Sleep(1000);
			token = getToken(user, pass);
			// 再次失败,跳过
			if (token == "")
				continue;
		}
		// 预约
		ret = getSeat(token,start,end,seat,date);
		// 失败后隔一秒重试
		if (ret == "") {
			Sleep(1000);
			ret = getSeat(token, start, end, seat, date);
			// 再次失败,跳过
			if (ret == "")
				continue;
		}
	}
}
string getToken(string user, string pass) {
	// 登录
	string token = Library.Get("/rest/auth", (string)"username=" + user + "&password=" + pass);
	// 查错
	if (token.find("successs") > 0) {
		token = token.erase(0, 289).erase(18);
		Log << user + " " + pass + " " + token << endl;
		return token;
	}
	else {
		Log << user + " " + pass + " " + token << endl;
		return "";
	}
}
string getSeat(string token, string start, string end, string seat, string date) {
	string ret = Library.Post("/rest/v2/freeBook", (string)"token=" + token + "&startTime=" + start + "&endTime=" + end + "&seat=" + seat + "&date=" + date);
	if (ret.find("success") > 0) {
		ret = ret.erase(0, ret.find("message\"") + 10);
		ret = ret.erase(ret.find("\""));
		Log << ret << endl;
		return ret;
	}
	else {
		Log << ret << endl;
		return "";
	}
}
std::string getTime() {
	char tmp[64];
	time_t timep;
	time(&timep);
	timep += 86400;
	tm a;
	localtime_s(&a, &timep);
	strftime(tmp, sizeof(tmp), "%Y-%m-%d", &a);
	return tmp;
}