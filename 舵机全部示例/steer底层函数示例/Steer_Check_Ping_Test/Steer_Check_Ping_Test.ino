/**
  *************************************************************************************************
  * @file           Steer_Check_Ping_Test
  * @author         
  * @qq             269426626
  * @version        V1.0
  * @date           2017.08.01
  * @note    ´      此程序有两个用途，校验和测试（check sum test），舵机应答测试（ping test）
  * @config_steer   Serial1
  * @computer       Serial
  *************************************************************************************************
  */

#include<Steer_protocol.h>

Steer_protocol Steer1(&Serial1,10);                      //初始化一个舵机对象

byte buf[] ={1,2,3,4,5,6};                                //用于校验和测试的数组

int  check_sum1 = 0;                                      //用于接收check_sum()的返回值，即校验和
byte data;                                                //用于接收ping()函数的状态数据
bool flag;                                                //接收ping()函数的返回值

void setup() {
  
  Steer1.begin(&Serial,10);                               //初始化和Arduino IDE的通信串口
  Serial.println( "Steer_protocol_init");                 
  
  check_sum1 =  Steer1.Check_Sum(buf, 5);                 //校验和函数                  
  Serial.print("check sum is : ");
  Serial.println(check_sum1);
  
  flag = Steer1.ping(1 , &data);                          //应答测试函数
  Serial.print("flag is :");
  Serial.print( flag );
  Serial.print("  data is : ");
  Serial.println(data);
  
  Serial.println("test over");
}

void loop() {
  flag = Steer1.ping(1 , &data);                          //应答测试函数
  Serial.print("flag is :");
  Serial.print( flag );
  delay(1000);
}
