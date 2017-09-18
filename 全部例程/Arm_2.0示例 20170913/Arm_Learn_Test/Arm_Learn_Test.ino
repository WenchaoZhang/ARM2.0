/**
  *************************************************************************************************
  * @file           Arm_Learn_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.24
  * @note    ´      此程序为机械臂学习程序
  * @computer       Serial
  *************************************************************************************************
  */

#include<Arm_learn.h>                           

    
void setup() {
    MyArm.begin(USB_SER);
  Serial.println("Arm_Learn_Test");
}

void loop() {
  while(1)
  {
    MyArm_learn.button_learn_detect();
   
  }
}



