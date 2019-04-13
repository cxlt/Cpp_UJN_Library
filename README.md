崔雨鸣
mailto:cym2018.xyz@qq.com
 

程序功能:
  使用C++,Socket发送Get Post请求

使用方法:
    # 1.文件包含:  
#include"Mysocket.h"
    # 2.新建对象 
MySocket myObject;
    # 3.设置网址,url路径
myObject.Set("www.xxxx.com","/index.jsp");
    # 4.发送请求,输出返回结果
cout<<myObject.Get("info");

已知问题:
  1.Get请求，无法发送中文
  2.Post请求失效
  3.无法处理302重定向
  
其他信息:
  大部分代码来自微软文档
  //https://docs.microsoft.com/zh-cn/windows/desktop/WinSock/windows-sockets-start-page-2
  utf-8,gbk转码部分代码来自csdn博客
  //https://blog.csdn.net/zhangxueyang1/article/details/54178195
  
  
