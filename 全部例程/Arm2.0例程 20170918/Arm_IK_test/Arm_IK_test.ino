/**
  *************************************************************************************************
  * @file           Arm_IK_Test
  * @author         ZWC
  * @qq             269426626
  * @qq_group       604556405
  * @version        V2.0
  * @date           2017.09.16
  * @note    ´      此程序测试运动学逆解（由末端位置推测关节角度）
  * @computer       Serial
  *************************************************************************************************
  */

#include<Arm.h>                           
    
void setup() {
  MyArm.begin(USB_SER);
  Serial.println("Inverse_Movement_Test");
}

void loop() {
  
  while(Serial.available())
  {
    double x = Serial.parseInt();
    double y = Serial.parseInt();
    double z = Serial.parseInt();
    
    Serial.println("get xyz");
    MyArm.inverse_movement(x,y,z);
    Serial.print("x = "); Serial.print(x);
    Serial.print("  y = "); Serial.print(y);
    Serial.print("  z = "); Serial.println(z);
    for(int i = 0; i < 3; i++)
    {
      Serial.print(MyArm.Rad2Angle(MyArm.theta[i]));Serial.print("  ");  
    }
    
    Serial.println();
  }
}



