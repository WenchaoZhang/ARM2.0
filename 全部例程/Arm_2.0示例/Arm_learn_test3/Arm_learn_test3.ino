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
#include <Arm_learn.h>                        
    
void setup() {
  MyArm.begin(USB_SER);
  Serial.println("Inverse_Movement_Test");
  //MyArm.Set_Arm_Torque_On();
  MyArm.position_init();
  delay(2200);
}

void loop() {
  
   MyArm_learn.start_learn();
   MyArm_learn.reappear_learn();
}



