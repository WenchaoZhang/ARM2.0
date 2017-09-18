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



