#include "arm_protect.h"

boolean Arm_protect::angle_limt_protect(double theta[], int num = 0)
{
      
      Serial.println(num);
      
      if(num > 2)
      {
        if( (theta[0] >= STEER_0_MIN_LIMT)  && (theta[0] <= STEER_0_MAX_LIMT)  \
            && (theta[1] >= STEER_1_MIN_LIMT) && (theta[1] <= STEER_1_MAX_LIMT) \
            && (theta[2] >= STEER_2_MIN_LIMT) && (theta[2] <= STEER_2_MAX_LIMT) )
            {
              Serial.println("in limit");
              return true;
            }
          else
          {
              Serial.println("no in limit");
              return false;
          }
      }
      else 
      {
        Serial.println("Eeror : there is not enough data");
        return false;
      }
}

boolean Arm_protect::position_line_calculate(double theta1, double theta2)
{
   double jud = -43*tan(theta1) + 43*tan(theta1)*cos(theta1 + theta2 - PI) - 43*sin(theta1 + theta2 - PI) + 18;
   if(jud > 0)
   {
      return true;
   }
    else 
   {
        Serial.println("Eeror : out of position limit");
        return false;
   }
}

void Arm_protect::Position_Protect( double *theta, int num)
{
        if(num > 2)
        {
          boolean judge1 = angle_limt_protect( theta);
          boolean judge2 = position_line_calculate(theta[1], theta[2]);
          if( judge1 && judge2){return true;}
          else{return false;}
        }
        else
        {
          return false;
        }
}

void Arm_protect::warning()
{
  for(int i = 0; i < 3; i++)
  {
    tone(BUZZER_PIN, 3500, 200);
    delay(200);
    noTone(BUZZER_PIN);
    delay(300);
  }
}

