/**
  *************************************************************************************************
  * @file           Steer_Loose_Torque_Test
  * @author         
  * @qq             269426626  
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.10
  * @note    ´      此程序用于测试舵机扭矩的获得与失去
  * @config_steer   Serial1
  * @computer       Serial
  *************************************************************************************************
  */
#include<Steer_protocol.h>

Steer_protocol fz1(&Serial1,10);

#define ID 0X04

byte writebuf[] = {0X00};                          //用于存储需要写的数据:0X00失去扭矩  0X01得到扭矩

void setup() {
  Serial.begin(115200);

  fz1.write(ID , 0X28 , writebuf , 1);                
}

void loop() {

}
