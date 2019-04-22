# Cpp_UJN_Library

_由C++编写,用于济南大学图书馆预约座位的可执行程序_

## 说明

早上睡醒,先打开APP占座,喜欢的座位还是被别人抢走了?

借了多个账号占座,一不留神就失约?

网上的Python占座脚本,看不懂,不会用,版本不兼容?

#### Cpp_UJN_Library可以帮你.

## 安装

点击链接下载

[预定座位](https://raw.githubusercontent.com/cym2018/Cpp_UJN_Library/master/app/library.exe)

[签到](https://raw.githubusercontent.com/cym2018/Cpp_UJN_Library/master/app/checkin.exe)

## 使用

#### 找到Library.exe所在的文件夹,新建文本文档,命名为"data.txt".

#### 打开data.txt,按照以下格式填写
```
第1行:此行不会对程序的运行产生任何影响,可以保存预约信息的中文描述,方便查改
第2行:学号
第3行:密码
第4行:座位id  [_获取座位id的方法_]()
第5行:开始时间(单位:分钟)
第6行:结束时间
第7行开始填写第2个预约信息,以此类推.
```
###### 注:文件内含空行,空格,可能会出错.

### 定时任务
