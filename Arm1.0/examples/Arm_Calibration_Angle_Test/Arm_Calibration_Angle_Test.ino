/**
  *************************************************************************************************
  * @file           Arm_Calibration_Angle_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.09
  * @note    ´      为机械臂校准程序（利用输入值为角度进行校准）
  * @computer       Serial
  *************************************************************************************************
  */
#include <Arm_1.0.h>

Arm Myarm;
Serial_arm myserial;

double angle[] = {90, 90, 90, 90, 90, 90};  //middle position
void setup() {
  Myarm.begin(&USB_SER);
  
  Serial.println("Please enter in the following format: ");
  Serial.println("0 100");
  Serial.println("Steer's ID = 1,We set its offset = 100");
  
  Myarm.originalPositionMove();
}

void loop() {
    while(Serial.available()){
      
    byte id = myserial.parseint(&Serial);   
    double offset = myserial.parsedouble(&Serial);

    Serial.print("ID = ");        Serial.print(id);
    Serial.print("  offset = ");  Serial.println(offset);

  }
}



