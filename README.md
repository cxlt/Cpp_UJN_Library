# Cpp_UJN_Library

_一个由C++编写的用于预约济南大学图书馆座位的可执行程序_

## 说明

早上睁眼第一件事情就是打开APP占座,却发现喜欢的座位被别人占走了?

借了多个账号占座,一不留神就失约?

网上的占座脚本都是Python编写的,学习太麻烦?

Cpp_UJN_Library可以帮你.

## 安装

[预定座位](https://raw.githubusercontent.com/cym2018/Cpp_UJN_Library/master/app/library.exe)

[签到](https://raw.githubusercontent.com/cym2018/Cpp_UJN_Library/master/app/checkin.exe)

## 使用

在你保存可执行程序的文件夹下新建一个空白文本文档,命名为"data.txt",这个文件用于保存预约座位需要的信息

### "data.txt"文件格式
__

第1行:此行不会对程序的运行产生任何影响,可以保存预约信息的中文描述,方便查改

第2行:学号

第3行:密码

第4行:座位id[获取座位id的方法]()

第5行:开始时间(单位:分钟)

第6行:结束时间

第7行开始填写第2个预约信息,以此类推.

##### 注:文件内含空行,空格,可能会出错.

### 定时任务






