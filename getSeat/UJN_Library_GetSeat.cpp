//崔雨鸣,2019年4月14日
# include <iostream>
# include <fstream>
# include <time.h>
# include "MySocket.h"
enum timetype {
	NX_yMd, yMdHms, Hms
};
using namespace std;
// 连接网络
// 文件
// 全局变量
// 子函数列表
MySocket Library("seat.ujn.edu.cn");
ifstream file;
ofstream Log;
string info, getToken(string user, string pass), getSeat(string token, string start, string end, string seat, string date), getTime(timetype flag);

// 程序入口
int main(int arc, char** arg) {
	// 初始化
	file.open("data.txt"); Log.open("log.txt", ios::app);
	string user, pass, seat, start, end, ret, token, date = getTime(NX_yMd);
	// 记录程序开始时间
	Log << "Start At:" << getTime(yMdHms) << endl;
	if (!file.is_open()) {
		cout << "无法打开文件data.txt,该文件应该与程序在同一个目录下" << endl
			<< "文件格式:\n1+6N:注释\n2+6N:学号\n3+6N:密码\n4+6N:座位号\n5+6N:开始时间\n6+6N:结束时间" << endl
			<< "项目地址:https://github.com/cym2018/Cpp_Socket" << endl;
		Log << "找不到data.txt" << endl;
		Log << "End At:" << getTime(yMdHms) << endl;
		return -1;
	}

	// 选座
	while (!file.eof()) {
		// 读取文件
		file >> info >> user >> pass >> seat >> start >> end;
		// 获取token
		token = getToken(user, pass);
		// 失败后隔一秒重试,再次失败,跳过
		if (token == "") {
			Sleep(1000);
			token = getToken(user, pass);
			if (token == "")continue;
		}
		// 预约
		ret = getSeat(token, start, end, seat, date);
		// 失败后隔一秒重试
		if (ret == "") {
			Sleep(1000);
			ret = getSeat(token, start, end, seat, date);
			// 再次失败,跳过
			if (ret == "")
				continue;
		}
	}
	Log << "End At:" << getTime(yMdHms) << endl;
	return 0;
}
string getToken(string user, string pass) {
	// 登录
	string token = Library.Get("/rest/auth", (string)"username=" + user + "&password=" + pass);
	// 查错
	//cout<<
	if (token.find("success") < token.length()) {
		token = token.erase(0, 289).erase(18);
		Log << "\t" << getTime(Hms) + info + " " + token << endl;
		return token;
	}
	else {
		Log << "\t" << getTime(Hms) + info + " " + token << endl;
		return "";
	}
}
string getSeat(string token, string start, string end, string seat, string date) {
	string ret = Library.Post("/rest/v2/freeBook", (string)"token=" + token + "&startTime=" + start + "&endTime=" + end + "&seat=" + seat + "&date=" + date);
	if (ret.find("success") < ret.length()) {
		ret = ret.erase(0, ret.find("location\"") + 11);
		ret = ret.erase(ret.find("\""));
		Log << "\t\t" << ret << endl;
		return ret;
	}
	else if (ret.find("已有1个有效预约") < ret.length() || ret.find("预约失败") < ret.length()) {
		ret = ret.erase(0, ret.find("message") + 10);
		ret = ret.erase(ret.find("\""));
		Log << "\t\t" << ret << endl;
		return ret;
	}
	else if (ret.find("{")<ret.length()) {
		ret = ret.erase(0, ret.find("{")).erase(ret.find("}") + 1);
		Log << "\t\t" << ret << endl;
		return ret;
	}
	else {
		Log << "\t\tERROR" << ret << endl;
		return "";
	}
}
// CTRL + C FROM https://blog.csdn.net/sylsjane/article/details/80868013
string getTime(timetype flag) {
	char tmp[64];
	time_t timep;
	time(&timep);
	tm a;
	switch (flag) {
	case NX_yMd:
		// 获取下一天时间 yyyy - MM - dd
		timep += 86400;
		localtime_s(&a, &timep);
		strftime(tmp, sizeof(tmp), "%Y-%m-%d", &a);
		return tmp;
	case yMdHms:
		// 获取当前时间yyyy-MM-dd HH:mm:ss
		localtime_s(&a, &timep);
		strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", &a);
		return tmp;
	case Hms:
		// 获取当前时间HH-mm-ss
		localtime_s(&a, &timep);
		strftime(tmp, sizeof(tmp), "%H:%M:%S", &a);
		return tmp;
	}
	cout << __LINE__ << "错误的传入参数" << endl;
	return "";
}
