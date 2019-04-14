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
