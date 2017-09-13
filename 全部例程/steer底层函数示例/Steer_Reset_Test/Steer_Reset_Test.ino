/**
  *************************************************************************************************
  * @file           Steer_Reset_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.02
  * @note    ´      此程序用于复位舵机到出厂设置
  * @config_steer   Serial1
  * @computer       Serial
  *************************************************************************************************
  */

/*********重点提示：不要轻易复位，已经复位ID设为0X01，其他初始内存参照《机器人舵机通信协议》**********/

#include<Steer_protocol.h>

const unsigned char ID = 0Xfe;                                    //需要复位的舵机ID号，为保险起见，不让用户在串口监视器中修改，只允许在程序中修改       

Steer_protocol Steer1(&Serial1,10);                              //初始化一个舵机对象

void setup() {
  
  Steer1.begin(&Serial,10);                                      //初始化和Arduino IDE的通信串口
  Serial.println( "Steer_protocol_init");                 

  Steer1.reset(ID);                                               //调用复位函数
  
  Serial.println("test over");
}

void loop() {
}



