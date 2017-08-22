/**
  *************************************************************************************************
  * @file           Arm_Calibration_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.08
  * @note    ´      为机械臂校准程序，即为机械臂设置偏置，使机械臂处于90°正位状态
  * @computer       Serial
  *************************************************************************************************
  */
#include <Arm.h>

double angle[] = {90, 90, 90, 90, 90, 90};  

Arm Myarm;

void setup() {
  Myarm.begin(&USB_SER);

  Serial.println("Please enter in the following format: ");
  Serial.println("0 100");
  Serial.println("Steer's ID = 0,We set its offset = 100");

}

void loop() {
    while(Serial.available()){
    byte id = Serial.parseInt();
    short offset = Serial.parseInt();
    
    Serial.print("ID = ");        Serial.print(id);
    Serial.print("  offset = ");  Serial.println(offset);

    Myarm.offsetSet(id, offset);
    Myarm.angleMove(angle, 700);
  }
}
