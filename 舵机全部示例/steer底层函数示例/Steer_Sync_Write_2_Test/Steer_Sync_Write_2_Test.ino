/**
  *************************************************************************************************
  * @file           Steer_Sync_Write_2_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.02
  * @note    ´      此程序通过sync_write()方法去控制舵机运动
  * @note    ´      此程序为舵机通信底层函数
  * @config_steer   Serial1
  * @computer       Serial
  *************************************************************************************************
  */

#include<Steer_protocol.h>

Steer_protocol Steer1(&Serial1,10);                            //初始化一个舵机对象

byte data[] = {1, 0x3, 0xff, 0x3, 0x20};


void setup() {
  Serial.begin(115200);
  Serial.println("Please input in the following format :");
  Serial.println("position(word)  runtime(word)");
  Serial.println("such as :2334 4301");
}

void loop() {
  while(Serial.available()){
    data[0] = byte(Serial.parseInt());
    word pos = word(Serial.parseInt());
    word vel = word(Serial.parseInt());

    Serial.print(data[0]); Serial.print(" ");
    Serial.print(pos); Serial.print(" ");
    Serial.print(vel); Serial.println(" ");
    
    data[1] = highByte(pos);
    data[2] = lowByte(pos);
    data[3] = highByte(vel);
    data[4] = lowByte(vel);
    Steer1.sync_write(TARGET_POSITION_H, data, 1, 5);  
  }
}

