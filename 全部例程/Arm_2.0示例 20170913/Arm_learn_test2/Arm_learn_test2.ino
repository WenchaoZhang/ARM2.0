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
  Serial.println("Arm_Learn_Test2");
  MyArm.Set_Arm_Torque_Off();
}
int x= 2;
word pos[6] = {0};
void loop() {
  while(Serial.available())
  {
    x = Serial.parseInt();
    if(x == 0)
    {   
        for(int i = 0; i < 6; i++)
        { 
          word pos = MyArm_learn.get_steer_positon(i);
          Serial.print("pos"); Serial.print(i); Serial.print(" = ");Serial.println(pos);
          Serial.println("0");
          MyArm.Set_Arm_Torque_Off();
        }
    }
    if(x == 1)
    {   
        for(int i = 0; i < 6; i++)
        { 
           pos[i] = MyArm_learn.get_steer_positon(i);
           delay(10);
           MyArm.steer[i]->Set_Steer_position_runtime(pos[i], 2000);
           MyArm.steer[i]->Get_Steer_Position_Target_Inf();
           Serial.print(".....");Serial.println((MyArm.steer[i]->Position_Target[0] << 8) + MyArm.steer[i]->Position_Target[1]);
          Serial.print("pos"); Serial.print(i); Serial.print(" = ");Serial.println(pos[i]);
          Serial.println("1");
        }
        //  MyArm.move_to_position(pos[0],pos[1],pos[2],2000);
          
          MyArm.Set_Arm_Torque_On();
          MyArm.move_to_position(pos[0],pos[1],pos[2],2000);
          
    }
  }
}



