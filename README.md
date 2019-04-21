# 本项目用于济南大学图书馆预约和签到
## app/checkin.exe 用于签到
## app/library.exe 用于预约
## 使用方式:
#### <仅支持windows>

下载app目录下的两个可执行文件.

新建data.txt,并根据"运行条件"部分的描述填写内容.

使用windows自带的"任务计划程序",设置每天定时启动,实现自动签到,自动预约.

#### 注意事项:

  ~~外网签到需要在"MySocket.cpp/Post()/upload"添加"X-Forwarded-For: 10.167.146.62\r\n"~~  
  ~~(+ "X-Forwarded-For: 10.167.146.62\r\n")~~
  ~~方法来源于:~~
  ~~//https://github.com/iozephyr/UJN-Lib-Seat-API~~
  ~~原issue链接:~~
  ~~//https://github.com/iozephyr/UJN-Lib-Seat-API/issues/17~~
  ~~(未经验证)~~
  
  #### 外网签到功能经测试失效,可能服务器修改了验证方式.

#### 运行条件

程序运行需要读取文件目录下的"data.txt"
文件格式如下:(N为第几个账号,0,1,2,3,4…)

6N+1行:注释

6N+2行:学号

6N+3行:密码

6N+4行:座位代码

6N+5行:开始时间

6N+6行:结束时间

#### 日志样例

![image](https://github.com/cym2018/Cpp_UJN_Library/blob/master/app/log.jpg)

#### data.txt样例

![image](https://github.com/cym2018/Cpp_UJN_Library/blob/master/app/data.jpg)
