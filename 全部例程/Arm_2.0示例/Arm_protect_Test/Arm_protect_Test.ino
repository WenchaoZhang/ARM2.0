/**
  *************************************************************************************************
  * @file           Arm_Protect_Test
  * @author         zwc/h
  * @qq             269426626
  * @qq_group       604556405
  * @version        V2.0
  * @date           2017.08.28
  * @note    ´      此程序为测试机械臂角度保护程序
  * @computer       Serial
  *************************************************************************************************
  */

#include "Arm_protect.h"                   

Serial_arm serial;
Arm_protect My_Protect;

double theta[3] = {0, 0, 0};

void setup() {
  Serial.begin(115200);
  Serial.println("Arm_Protect_Test");
}

void loop() {
  while(Serial.available())
  {
      theta[0] = serial.parsedouble(&Serial);
      theta[1] = serial.parsedouble(&Serial);
      theta[2] = serial.parsedouble(&Serial);

      Serial.print("theta[0] = ");Serial.println(theta[0]);
      Serial.print("theta[1] = ");Serial.println(theta[1]);
      Serial.print("theta[2] = ");Serial.println(theta[2]);

      boolean j = My_Protect.angle_limt_protect(theta,sizeof(theta)/sizeof(theta[0]));

      Serial.print("judge ans = "); Serial.println(j);
  }
}



