/**
  *************************************************************************************************
  * @file           Arm_Protect_Line_Test
  * @author         zwc/h
  * @qq             269426626
  * @qq_group       604556405
  * @version        V2.0
  * @date           2017.08.29
  * @note    ´      此程序为测试机械臂直线保护程序
  * @computer       Serial
  *************************************************************************************************
  */

#include "Arm_protect.h"                   

Arm_protect My_Protect;

word get_steer_positon(byte i);

double theta[3] = {0, 0, 0};

void setup() {
  MyArm.begin(USB_SER);
  Serial.println("Arm_Protect_Line_Test");
  MyArm.Set_Arm_Torque_Off();
}

void loop() {
  while(Serial.available())
  {
    if(Serial.read() == 'j')
    {
      theta[0] = MyArm.Pos2Rad(get_steer_positon(0));
      theta[1] = MyArm.Pos2Rad(get_steer_positon(1));
      theta[2] = MyArm.Pos2Rad(get_steer_positon(2));

      Serial.print("theta[0] = ");Serial.print(theta[0]);    Serial.print("  angle[0] = ");Serial.println(MyArm.Rad2Angle(theta[0]));
      Serial.print("theta[1] = ");Serial.print(theta[1]);    Serial.print("  angle[1] = ");Serial.println(MyArm.Rad2Angle(theta[1]));
      Serial.print("theta[2] = ");Serial.print(theta[2]);    Serial.print("  angle[2] = ");Serial.println(MyArm.Rad2Angle(theta[2]));

      boolean j = My_Protect.Position_Protect(theta,sizeof(theta)/sizeof(theta[0]));
     
      Serial.print("judge ans = ");    Serial.println(j);
     } 
  }
}

word get_steer_positon(byte i)
{
  word pos_tmp[3] = {0};
  for(int j = 0; j < 3; j++)
  {
    MyArm.steer[i]->Get_Steer_Position_Current_Inf();
    pos_tmp[j] = MyArm.steer[i] ->Position_Current[0];
    pos_tmp[j] = (pos_tmp[j] << 8) + MyArm.steer[i] ->Position_Current[1];
  }
  return (pos_tmp[0] + pos_tmp[1] + pos_tmp[2])/3;
}


