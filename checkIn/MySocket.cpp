#include"MySocket.h"
// 建立socket
MySocket::MySocket(string http = "") :sHttp(http) {
	// 调用WS2_32.dll
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	// 给hint填零
	ZeroMemory(&hints, sizeof(hints));
	// 返回类型:适用于指定主机名和服务名且适合任何协议族的地址
	hints.ai_family = AF_UNSPEC;
	// 提供面向连接的稳定数据传输，即TCP协议
	hints.ai_socktype = SOCK_STREAM;
	// 指定TCP协议
	hints.ai_protocol = IPPROTO_TCP;
}
// 获取服务器信息
void MySocket::Connect() {
	iResult = getaddrinfo(sHttp.c_str(), DEFAULT_PORT, &hints, &result);
	ptr = result;
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	freeaddrinfo(result);
}
// 交换数据
string MySocket::Exchange() {
	Connect();
	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];
	string ret;
	//发送数据
	send(ConnectSocket, upload.c_str(), (int)upload.length(), 0);
	//关闭连接
	shutdown(ConnectSocket, SD_SEND);
	//接收数据
	do {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			for (int i = 0; i < iResult; i++)
				ret += recvbuf[i];
		}
	} while (iResult > 0);
	return ret;
}
// 构造请求
string MySocket::Get(string page, string info) {
	sPage = page;
	upload = "GET " + sPage
		+ "?" + info + " HTTP/1.1\r\n"
		+ "Host: " + sHttp + "\r\n"
		+ "Connection: Keep-Alive\r\n\r\n";
	return ToGBK(Exchange());
}
string MySocket::Post(string page, string info) {
	sPage = page;
	upload = "";
	upload = upload + "POST "
		+ sPage + " HTTP/1.1\r\n"
		+ "Cache-Control: max-age=0\r\n"
		+ "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
		+ "Accept-Language: zh-Hans-CN,zh-Hans;q=0.5\r\n"
		+ "Content-Type: application/x-www-form-urlencoded\r\n"
		+ "Upgrade-Insecure-Requests: 1\r\n"
		+ "Accept-Encoding: gzip, deflate\r\n"
		+ "Host: " + sHttp + "\r\n"
		+ "Content-Length: " + (char)(info.length() / 100 % 10 + '0') + (char)(info.length() / 10 % 10 + '0') + (char)(info.length() % 10 + '0') + "\r\n"
		+ "Connection: Keep-Alive\r\n\r\n"
		+ info;
	return ToGBK(Exchange());
}
// 转码
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
