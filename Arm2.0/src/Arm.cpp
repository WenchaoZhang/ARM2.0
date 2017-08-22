#include <Arm.h>


Steer_protocol  steer_tmp(&Serial1, 10);

void Arm::begin(HardwareSerial *desireSer)         
{
    comSer = desireSer;
    comSer->begin(115200);
    comSer->setTimeout(5);

    Steer_Detect();
    Steer_Num = 6;
    Para_Init();
    Get_Offset();
    Timer1.initialize(10000);                         //初始化定时器1中断为10000us，也就是 10ms 
    Timer1.attachInterrupt( timerIsr );         // 中断回调函数
}

void Arm::position_init(void)
{
  Get_Offset();
  for(int i = 0; i < Steer_Num; i++)
  {
    steer[i] ->Set_Steer_position_runtime(2047+offPos[i] , 0x0bb8);
    pos_goal[i] = 2047+offPos[i];
    pos_pre[i] = 2047+offPos[i];
    pos_step[i] = 0;
  }
}

void Arm::inverse_movement(double x_ , double y_, double z_)
{
  double x = x_, y = y_, z = z_;

    theta[0] = atan2(y, x);
    x -= d * cos(theta[0]);
    y -= d * sin(theta[0]);
    z -= e;
    
    double lengthA = sqrt(x * x + y * y + z * z);
    double lengthC = sqrt(h * h + c * c);
    double offsetAngle = atan(h / c);
    double angleA = acos( (a * a + lengthC * lengthC - lengthA * lengthA) / (2 * a * lengthC) );
    double angleB = atan( z / sqrt(x * x + y * y) );
    double angleC = acos( (a * a + lengthA * lengthA - lengthC * lengthC) / (2 * a * lengthA) );
    theta[1] = angleB + angleC;
    theta[2] = PI - angleA - angleB - angleC + offsetAngle;
    theta[2] += HALF_PI;
}

void Arm::inverse_movement(PVector pt)
{
  double x = pt.x, y = pt.y, z = pt.z;

    theta[0] = atan2(y, x);
    x -= d * cos(theta[0]);
    y -= d * sin(theta[0]);
    z -= e;
    
    double lengthA = sqrt(x * x + y * y + z * z);
    double lengthC = sqrt(h * h + c * c);
    double offsetAngle = atan(h / c);
    double angleA = acos( (a * a + lengthC * lengthC - lengthA * lengthA) / (2 * a * lengthC) );
    double angleB = atan( z / sqrt(x * x + y * y) );
    double angleC = acos( (a * a + lengthA * lengthA - lengthC * lengthC) / (2 * a * lengthA) );
    theta[1] = angleB + angleC;
    theta[2] = PI - angleA - angleB - angleC + offsetAngle;
    theta[2] += HALF_PI;
}

void Arm::move_to_position( double x_ , double y_, double z_ , word runtime)
{    
    clc_Times_Total = runtime/10 - 1; 
    clc_Times_now = 0;
    
    inverse_movement(x_ , y_, z_);
     
    for(byte i = 0 ; i < 3; i++)   
    {
      pos_goal[i] = Rad2Pos(theta[i]);
      pos_step[i] = (pos_goal[i] - pos_pre[i]) / clc_Times_Total;
    }
    pos_flag = 1;
}

void Arm::move_to_position( PVector pt , word runtime)
{
  
}

byte Arm::Steer_Detect()
{
    byte state;
    byte num = 0;

    for (byte i = 0; i < 7; i++) 
    {
        if (steer_tmp.ping(i, &state)) 
        {
            num ++;
        }
    }
    Steer_Num = num;
    return num;
}



 void Arm::Para_Init()
 {
    if(Steer_Num > 0)
    {
          offPos = (short *)malloc(Steer_Num * sizeof(short));
          theta = (double *)malloc(Steer_Num * sizeof(double));
          
          pos_goal = (word *)malloc(Steer_Num * sizeof(word));
          pos_pre = (word *)malloc(Steer_Num * sizeof(word));
          pos_step = (word *)malloc(Steer_Num * sizeof(word));
          
          for(byte i  = 0; i < Steer_Num; i++ )
          {
            steer[i] = new Steer( i, &Serial1); 
          }
    }
 }

void Arm::Get_Offset()
{
    for (byte i = 0; i < Steer_Num; i++) 
    {
        EEPROM.get(i * sizeof(short), offPos[i]);
    }
}

void Arm::offset_by_pos(byte id, short offset)
{
      if(id < Steer_Num)
      {
        EEPROM.put(id * sizeof(short), offset);
      }
      else 
      {
        comSer -> println("error: id > Steer_Num");
        comSer -> println("Please enter a correct id");
      }
}

void Arm::offset_by_angle(byte id, double angle)
{
  short tmp = mapFloat(angle, -90, 90, -1024, 1024);
  offset_by_pos(id, tmp);
}


double mapFloat(double val, double in_min, double in_max, double out_min, double out_max)
{
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


short Arm::Rad2Pos(double rad)
{
    return short(mapFloat(rad, 0, PI, 1024, 3071));
}

short Arm::Angle2Pos(double angle)
{
    return short(mapFloat(angle, 0, 180, 1024, 3071));
}

short Pos2Angle(double pos)
{
    return short(mapFloat(pos, 1024, 3071, 0, 180));
}

void Arm_Step_Control()
{
  if(pos_flag = 1)
  {
    clc_Times_now++;
    if(clc_Times_now >= clc_Times_Total){ pos_flag = 0;}
    for(int i = 0; i < 3; i++)
    {
      steer[i] ->Set_Steer_position_runtime(pos_pre[i] + clc_Times_now*pos_step[i], 10);
    }
  }
  else
  {
    for(int i = 0; i < 3; i++)
    {
      steer[i] ->Set_Steer_position_runtime(pos_goal[i], 2000);
    }
  }
}
    

void timerIsr()
{
    Arm_Step_Control();
}

//利用速度去做整体调整