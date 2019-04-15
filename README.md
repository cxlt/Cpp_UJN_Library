# Cpp_Socket
Sent Post or Get Request by C++ Socket
# 程序功能:
  使用C++,Socket发送Get Post请求

# 使用方法:
```C++
#include"Mysocket.h"
// 网址只在初始化时确定
MySocket myObject("www.baidu.com");
// 只获取页面内容,不提交表单
cout<<myObject.Get("页面地址");
// 使用Get方式提交表单
cout<<myObject.Get("页面地址","表单内容");
// 使用Post方式提交表单
cout<<myObject.Post("页面地址","表单内容");
// =浏览器访问www.baidu.com/index.jsp?word=123
cout<<myObject.Get("/index.jsp","word=123");
```

# 已知问题:
  1.Get请求，无法发送中文

  ~~2.无法处理302重定向~~（只用于发送请求所以应该不会完善这个功能）
  
  

# 其他信息:

  大部分代码来自微软文档
  
  https://docs.microsoft.com/zh-cn/windows/desktop/WinSock/windows-sockets-start-page-2
  
  utf-8,gbk转码部分代码来自csdn博客
  
  https://blog.csdn.net/zhangxueyang1/article/details/54178195
  
  (自己写了get,post函数,顺便翻译注释)
  
崔雨鸣
2019年4月15日20:04
