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
  MyArm.Set_Arm_Torque_On();
  MyArm.position_init();
  delay(2200);
}

void loop() {
  
    MyArm.move_to_position(100.0, 200,232,500);
    delay(510);
    MyArm.move_to_position(-100.0, 200,232,700);
    delay(710);
    MyArm.move_to_position(-100.0, 200, 133,500);
    delay(510);
    MyArm.move_to_position(100.0, 200, 133,700);
    delay(710);
}



