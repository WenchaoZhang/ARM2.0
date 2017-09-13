/**
  *************************************************************************************************
  * @file           Arm_Detect_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.22
  * @note    ´      此程序机械臂舵机检测
  * @computer       Serial
  *************************************************************************************************
  */

#include<Arm.h>                           

Arm MyArm;
    
void setup() {
  MyArm.begin(USB_SER);
  Serial.println("Detect_Test");
}

void loop() {
  Serial.println(MyArm.Steer_Num);
}


