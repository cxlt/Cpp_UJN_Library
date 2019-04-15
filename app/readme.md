# UJN_Library_Checkin.cpp
UJN_Library_Checkin.cpp用于济南大学图书馆签到
  
  外网签到需要在"MySocket.cpp/Post()/upload"添加"X-Forwarded-For: 10.167.146.62\r\n"
  
    (+ "X-Forwarded-For: 10.167.146.62\r\n")
  
  方法来源于:
  
  //https://github.com/iozephyr/UJN-Lib-Seat-API
  
  原issue链接:
  
  //https://github.com/iozephyr/UJN-Lib-Seat-API/issues/17
  
  (未经验证)

# UJN_Library_GetSeat.cpp

UJN_Library_GetSeat.cpp用于济南大学图书馆预约

# 运行条件

程序运行需要读取文件目录下的"data.txt"
文件格式如下:(N为第几个账号,1,2,3,4…)

6N+1行:注释

6N+2行:学号

6N+3行:密码

6N+4行:座位代码

6N+5行:开始时间

6N+6行:结束时间

# 日志样例

![image](https://github.com/cym2018/Cpp_Socket/blob/master/app/log.jpg)

# data.txt样例

![image](https://github.com/cym2018/Cpp_Socket/blob/master/app/data.jpg)
