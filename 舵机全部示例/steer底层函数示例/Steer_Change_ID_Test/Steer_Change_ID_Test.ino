/**
  *************************************************************************************************
  * @file           Steer_Change_ID_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.02
  * @note    ´      此程序用于更改舵机的ID号
  * @config_steer   Serial1
  * @computer       Serial
  *************************************************************************************************
  */

#include<Steer_protocol.h>

unsigned char old_id = 0x0c;                                    //舵机老的ID号
unsigned char new_id = 0x05;                                    //舵机新的ID号       

Steer_protocol Steer1(&Serial1,10);                              //初始化一个舵机对象

void setup() {
  
  Steer1.begin(&Serial,10);                                      //初始化和Arduino IDE的通信串口
  Serial.println( "Steer_protocol_init over");
  Serial.println("Please enter in the following format: ");
  Serial.println("old_ID new_ID");
  Serial.println("such as: 3 1");                 

}

void loop() {
  while(Serial.available()){
    byte old_id = Serial.parseInt();                             //可以把old_id设为广播地址254，这时可以改变任意舵机的ID
    byte new_id = Serial.parseInt();                      
    Steer1.write(old_id, ID_REG, &new_id, sizeof(new_id)); 
    Serial.println("Change over. Please input another.") ;
  }
}




