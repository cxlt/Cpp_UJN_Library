#include"MySocket.h"
using namespace std;
MySocket::MySocket() {
	// 调用WS2_32.dll
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	// 值初始化
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}
void MySocket::Set(string http, string url) {
	sUrl = url; sHttp = http;
}
void MySocket::Connect() {
	// 获取服务器ip,端口信息
	iResult = getaddrinfo(sHttp.c_str(), DEFAULT_PORT, &hints, &result);
	// 导入信息,连接
	ptr = result;
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	//连接服务器
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	freeaddrinfo(result);
}
void MySocket::Send() {
	char temp[10000];
	strcpy_s(temp, 10000, upload.c_str());
	sendbuf = temp;
	//发送数据
	iResult = send(ConnectSocket, upload.c_str(), (int)strlen(sendbuf), 0);
	//关闭连接
	iResult = shutdown(ConnectSocket, SD_SEND);
	//接收数据
	recData = "";
	do {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			for (int i = 0; i < iResult; i++)
				recData += recvbuf[i];
		}
		else if (iResult == 0)
			;//连接关闭
		else {
			;//接收错误
		}
	} while (iResult > 0);
}
string MySocket::Get() {
	upload = "";
	upload = upload + "GET " + sUrl + " HTTP/1.1\r\nHost: " + sHttp + "\r\nConnection: Keep-Alive\r\n\r\n";
	Connect();
	Send();
	return ToGBK(recData);
}
string MySocket::Get(string info) {
	upload = "GET " + sUrl + "?" + info + " HTTP/1.1\r\n" + "Host: " + sHttp + "\r\n" + "Connection: Keep-Alive\r\n\r\n";
	Connect();
	Send();
	return ToGBK(recData);
}
string MySocket::GetChinese(string info) {
	upload = "GET " + sUrl + "?" + info + " HTTP/1.1\r\n" + "Host: " + sHttp + "\r\n" + "Connection: Keep-Alive\r\n\r\n";
	upload = ToUTF8(upload);
	cout << upload;
	Connect();
	Send();
	return ToGBK(recData);
}
string MySocket::Post(string info) {
	upload = "";
	upload = upload + "POST " + sUrl + " HTTP/1.1\r\nCache-Control: max-age=0\r\nAccept"
		+ ": text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-"
		+ "Language: zh-Hans-CN,zh-Hans;q=0.5\r\nContent-Type: application/x-www-"
		+ "form-urlencoded\r\nUpgrade-Insecure-Requests: 1\r\nAccept-Encoding: "
		+ "gzip, deflate\r\nHost: " + sHttp + "\r\nContent-Length: 78\r\nConnection:"
		+ " Keep-Alive\r\n\r\n" + info;
	Connect();
	Send();
	return ToGBK(recData);
}
string MySocket::ToGBK(const string& str) {
	//CTRL+C FROM
	//https://blog.csdn.net/zhangxueyang1/article/details/54178195
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	memset(pwBuf, 0, nwLen * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);
	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	std::string retStr = pBuf;
	delete[]pBuf;
	delete[]pwBuf;
	pBuf = NULL;
	pwBuf = NULL;
	return retStr;
}
string MySocket::ToUTF8(const string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	ZeroMemory(pwBuf, nwLen * 2 + 2);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);
	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	string retStr(pBuf);
	delete[]pwBuf;
	delete[]pBuf;
	pwBuf = NULL;
	pBuf = NULL;
	return retStr;
}
