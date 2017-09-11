/**
  *************************************************************************************************
  * @file           Steer_Read_Test
  * @author         
  * @qq             269426626
  * @version        V1.0
  * @date           2017.08.01
  * @note    ´      此程序用于测试读舵机中内存
  * @config_steer   Serial1
  * @computer       Serial
  *************************************************************************************************
  */

#include<Steer_protocol.h>

const unsigned char LEN = 0X02;                            //记录需要读取的内存长度

Steer_protocol Steer1(&Serial1,10);                       //初始化一个舵机对象

byte buf[LEN] ={0, 0};                                     //用于存储读回来的数据

bool flag;                                                 //接收read()函数的返回值

void setup() {
  
  Steer1.begin(&Serial,10);                                //初始化和Arduino IDE的通信串口
  Serial.println( "Steer_protocol_init");                 
  
  flag = Steer1.read(0x01 , 0x38 , buf , LEN);             //read()函数读取当前位置数据（具体需要读取什么要查看舵机说明书）
  Serial.print("flag is :");
  Serial.print( flag );
  
  Serial.print("  buf is : ");
  for(int i = 0; i < LEN; i++)
  {
    Serial.print("  0X");
    Serial.print(buf[i], HEX);
  }
  
  Serial.println(" ");  
  
  flag = Steer1.read(0x01 , 0x2A , buf , LEN);            //read()函数读取目标位置数据（具体需要读取什么要查看舵机说明书）
  Serial.print("flag is :");
  Serial.print( flag );
  
  Serial.print("  buf is : ");
  for(int i = 0; i < LEN; i++)
  {
    Serial.print("  0X");
    Serial.print(buf[i], HEX);
  }
  
  Serial.println(" ");
  
  Serial.println("test over");
}

void loop() {
//Serial.println("zhang ");
}

