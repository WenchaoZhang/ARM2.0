#ifndef  ARM_PROTECT_H
#define ARM_PROTECT_H

#include "Arduino.h"
#include "Arm.h"
#include "Serial_arm.h"

#define BUZZER_PIN                37                                              //����������

//ע�⣺�����нǶȵ��������ȫ�����Ի�����Ϊ׼

const double STEER_0_MIN_LIMT   = PI/9;
const double STEER_0_MAX_LIMT   = 8*PI/9;
const double STEER_1_MIN_LIMT   = PI/9;
const double STEER_1_MAX_LIMT   = PI;
const double STEER_2_MIN_LIMT   = PI/6;
const double STEER_2_MAX_LIMT   = 8*PI/9;

/*************������ϸ˵�������CPP�ļ�*************/

class Arm_protect{
  private:
  
  public:
      
 boolean angle_limt_protect(double theta[], int num = 0);
  
  boolean position_line_calculate(double theta1, double theta2);
  void Position_Protect( double *theta, int num);
  void warning();
};

#endif
