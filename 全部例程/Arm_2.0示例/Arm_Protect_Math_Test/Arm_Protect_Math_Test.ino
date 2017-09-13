/**
  *************************************************************************************************
  * @file           Arm_IK_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.23
  * @note    ´      此程序测试运动学逆解（由末端位置推测关节角度）
  * @computer       Serial
  *************************************************************************************************
  */

#include<Arm_protect.h>                           

Serial_arm serial_arm;
    
void setup() {
  Serial.begin(115200);
  Serial.println("Math_Test");
}

void loop() {
 
  while(Serial.available())
  {
    double theta = serial_arm.parsedouble(&Serial);
    
    Serial.print("get theta = "); Serial.println(theta);
    double v = tan(theta);
    Serial.println(v);
  }
}



