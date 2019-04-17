#pragma once
#include<iostream>
#include<string>
#include <ws2tcpip.h>
#define DEFAULT_PORT "80"//默认端口
#define DEFAULT_BUFLEN 512//单次发送数据大小
#pragma comment(lib, "Ws2_32.lib")
using std::string;
class MySocket {
private:
	//windows socks data
	// 地址信息
	// Socket
	WSADATA wsaData;
	struct addrinfo* result = NULL, * ptr = NULL, hints;
	SOCKET ConnectSocket = INVALID_SOCKET;

	// 服务器网址,url
	// 发送的数据
	// 验证连接是否成功,接收数据大小
	string sHttp,sPage;
	string upload;
	int iResult;
	
	// 获取服务器信息
	// 收发数据
	// 转码
	void Connect();
	string Exchange();
	string ToGBK(const string& str);
	string ToUTF8(const string& str);
public:
	MySocket(string http);
	string Get(string page, string info="");
	string Post(string page, string info);
};
