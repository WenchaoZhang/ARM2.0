/**
  *************************************************************************************************
  * @file           Arm_steer345_test
  * @author         ZWC
  * @qq             269426626
  * @qq_group       604556405
  * @version        V2.0
  * @date           2017.09.18
  * @note    ´      此程序用于机械臂出厂质量检测
  * @computer       Serial
  *************************************************************************************************
  */

#include<Arm.h>                           
    
void setup() {
  MyArm.begin(USB_SER);
  Serial.println("Arm_steer345_test");
  MyArm.position_init();
  delay(3000);
}

void loop() {
    //舵机5
    MyArm.turn_steer_345_to_positon((word)2047,2047,1024,2000);
    delay(2000);
    MyArm.turn_steer_345_to_positon((word)2047,2047,3047,2000);
    delay(2000);
    MyArm.turn_steer_345_to_positon((word)2047,2047,2047,1000);
    delay(1000);
    //舵机4
    MyArm.turn_steer_345_to_positon((word)2047,1024,2047,2000);
    delay(2000);
    MyArm.turn_steer_345_to_positon((word)2047,3047,2047,2000);
    delay(2000);
    MyArm.turn_steer_345_to_positon((word)2047,2047,2047,1000);
    delay(1000);
     //舵机3
    MyArm.turn_steer_345_to_positon((word)1024,2047,2047,2000);
    delay(2000);
    MyArm.turn_steer_345_to_positon((word)3047,2047,2047,2000);
    delay(2000);
    MyArm.turn_steer_345_to_positon((word)2047,2047,2047,1000);
    delay(1000);
}



