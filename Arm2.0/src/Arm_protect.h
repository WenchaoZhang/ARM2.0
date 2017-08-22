#ifndef  ARM_PROTECT_H
#define ARM_PROTECT_H

#include "Arduino.h"


/*************������ϸ˵�������CPP�ļ�*************/

class arm_protect{
  private:
  
  byte *Temperature;
  byte *Electric_Current;  
  byte *position;
  
  public:
  
  double *Tempera;
  double *Pos;
  double *Elec;
  
  void Get_Temperature();
  void Get_Electric_Current();
  void Get_position();
  
  void Temperature_Protect();
  void Electric_Current_Protect();
  void Position_Protect();
};

#endif
