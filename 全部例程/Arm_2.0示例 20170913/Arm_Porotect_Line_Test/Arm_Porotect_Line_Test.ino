/**
  *************************************************************************************************
  * @file           Arm_Protect_Line_Test
  * @author         zwc/h
  * @qq             269426626
  * @qq_group       604556405
  * @version        V2.0
  * @date           2017.08.28
  * @note    ´      此程序为测试机械臂直线保护程序
  * @computer       Serial
  *************************************************************************************************
  */

#include "Arm_protect.h"                   

Serial_arm serial;
Arm_protect My_Protect;

double theta[3] = {0, 0, 0};

void setup() {
  Serial.begin(115200);
  Serial.println("Arm_Protect——Line_Test");
}

void loop() {
  while(Serial.available())
  {
      theta[1] = serial.parsedouble(&Serial);
      theta[2] = serial.parsedouble(&Serial);

      Serial.print("theta[1] = ");Serial.println(theta[1]);
      Serial.print("theta[2] = ");Serial.println(theta[2]);

      boolean j = My_Protect.position_line_calculate(theta[1], theta[2]);
      boolean j2 = My_Protect.Positon_line2_limit(theta[1], theta[2]);

      Serial.print("judge ans = ");    Serial.println(j);
      Serial.print(" judge ans_j2 = "); Serial.println(j2);
      Serial.print(" t_judge = "); Serial.println(j&&j2);
      Serial.println();
  }
}



