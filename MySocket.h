#pragma once
#include<iostream>
#include<string>
#include <ws2tcpip.h>
//#include<WinSock2.h>
#define DEFAULT_PORT "80"//默认端口
#define DEFAULT_BUFLEN 512//单次发送数据大小
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
class MySocket {
	/*
作者:崔雨鸣
联系方式:mailto:cym2018.xyz@outlook.com
时间:2019年4月1日
功能:利用socket发送Get,Post请求
例:对"www.baidu.com/index.html"发送包含"username=10000,text=text"的Get请求
	MySocket test;
	test.Set("www.baidu.com","/index.html");
	getToken.Get("username=10000&text=text");
Post同理.
函数返回(string)网页内容
*/
private:
	//连接
	WSADATA wsaData;//windows socks data
	struct addrinfo* result = NULL, * ptr = NULL, hints;//地址信息
	SOCKET ConnectSocket = INVALID_SOCKET;//Socket
	//控制
	string sUrl, sHttp;//服务器网址,url
	int iResult;//验证连接是否成功,接收数据大小
	int recvbuflen = DEFAULT_BUFLEN;//单次接收数据长度
	char recvbuf[DEFAULT_BUFLEN];//存放接收的数据
	string upload;
	//数据
	char* sendbuf;//发送的数据
	string recData;//接收到的数据
	//函数
	void Connect();//获取服务器信息
	void Send();//发送,接收数据
	string ToGBK(const string& str);
	string ToUTF8(const string& str);
	//转码
public:
	MySocket();//初始化变量
	void Set(string http, string url);//设置网址,网页地址
	string Get();//空get
	string Get(string);
	string GetChinese(string info);
	//带参数的get
	string Post(string);//带参数的post
};
