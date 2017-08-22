/**
  *************************************************************************************************
  * @file           arm_ik_test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.07
  * @note    ´      此程序测试运动学逆解（由末端位置推测关节角度）
  * @computer       Serial
  *************************************************************************************************
  */

#include<Arm_1.0.h>                               

PVector pv(100,100,100);                                                            //运动学逆解坐标

Arm Myarm;                                                                             

void setup() {
  Myarm.begin(&Serial);                                                            //初始化
  Serial.println("IK_test");
  
  Myarm.IK(pv);                                                                     //运动学逆解函数
  Serial.print("Myarm.theta[0] = ");Serial.println(Myarm.theta[0]);
  Serial.print("Myarm.theta[1] = ");Serial.println(Myarm.theta[1]);
  Serial.print("Myarm.theta[2] = ");Serial.println(Myarm.theta[2]);
}

void loop() {
  
}



