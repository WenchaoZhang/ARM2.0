/**
  *************************************************************************************************
  * @file           Arm_torque_Set_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.26
  * @note    ´      此程序为测试舵机扭矩开关
  * @computer       Serial
  *************************************************************************************************
  */

#include<Arm.h>                           
    
void setup() {
  MyArm.begin(USB_SER);
  Serial.println("Touque_Off_Test");
 
  MyArm.position_init(); 
  MyArm.Set_Arm_Torque_On();
  delay(3000);
}
int x = 1;

void loop() {
  
  while(Serial.available())
  {
     x = Serial.parseInt();
    if(x == 0)
    {
        Serial.println("Set Arm Torque off");
        MyArm.Set_Arm_Torque_Off();
    }
    if(x > 0)
    {
      Serial.println("Set Arm Torue On");
      MyArm.position_init();
      MyArm.Set_Arm_Torque_On();
      
    }
  }
}



