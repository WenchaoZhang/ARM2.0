/**
  *************************************************************************************************
  * @file           Arm_IK_Test
  * @author         ZWC
  * @qq             269426626
  * @qq_group       604556405
  * @version        V2.0
  * @date           2017.09.18
  * @note    ´      此程序用于机械臂运动学逆解，并且运动到该位置
  * @computer       Serial
  *************************************************************************************************
  */

#include<Arm.h>                           
    
void setup() {
  MyArm.begin(USB_SER);
  Serial.println("Inverse_Movement_Test");
  MyArm.position_init();
}

void loop() {
  
  while(Serial.available())
  {
    int x = Serial.parseInt();
    int y = Serial.parseInt();
    int z = Serial.parseInt();
    int t = Serial.parseInt();
    
    Serial.println("get xyz");
   
    Serial.print("x = "); Serial.print(x);
    Serial.print("  y = "); Serial.print(y); 
    Serial.print("  z = "); Serial.print(z); 
    Serial.print("  t = "); Serial.println(t);
   
    
    MyArm.move_to_position(x,y,z,t);
    for(int i = 0; i < 3; i++)
    {
      Serial.print(MyArm.Rad2Angle(MyArm.theta[i]));Serial.print("  ");  
    }
    
    Serial.println();
  }
}



