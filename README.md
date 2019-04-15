# Cpp_Socket
Sent Post or Get Request by C++ Socket
# 程序功能:
  使用C++,Socket发送Get Post请求

# 使用方法:
    # 1.文件包含:  
`#include"Mysocket.h"`

    # 2.新建对象 
MySocket myObject("网址");//每个对象的网址在初始化时确定，不提供修改函数
`MySocket myObject("www.baidu.com")`

    # 3.发送请求,输出返回结果
`cout<<myObject.Get("页面地址");//只获取页面内容,不提交表单`

`cout<<myObject.Get("页面地址","表单内容");`

`cout<<myObject.Post("页面地址","表单内容");`

`cout<<myObject.Get("/index.jsp","word=123");`

# 已知问题:
  1.Get请求，无法发送中文

  2.无法处理302重定向

# 其他信息:

  大部分代码来自微软文档
  
  //https://docs.microsoft.com/zh-cn/windows/desktop/WinSock/windows-sockets-start-page-2
  
  utf-8,gbk转码部分代码来自csdn博客
  
  //https://blog.csdn.net/zhangxueyang1/article/details/54178195
  
崔雨鸣

mailto:cym2018.xyz@qq.com

2019年4月14日20：18
