/**
  *************************************************************************************************
  * @file           Arm_IK_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.22
  * @note    ´      此程序测试运动学逆解（由末端位置推测关节角度）
  * @computer       Serial
  *************************************************************************************************
  */

#include<Arm.h>                           
    
void setup(){
  MyArm.begin(USB_SER);
  Serial.println("Offset_Test");
  MyArm.position_init();
}

void loop() {
  while(Serial.available())
  {
    byte id = Serial.parseInt();
    short offset = Serial.parseInt();
    MyArm.offset_by_angle(id, offset);
    MyArm.Get_Offset();
    Serial.println("get offset");
    for(int i = 0; i < MyArm.Steer_Num; i++)
    {
      Serial.print("id = "); Serial.print(i); Serial.print("  0ffset = "); Serial.println(MyArm.offPos[i]);  
    }
    MyArm.position_init();
  }
}
