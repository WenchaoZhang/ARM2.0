#ifndef ARM_H
#define ARM_H

#include <Arduino.h>
#include <Serial_arm.h>
#include <HardwareSerial.h>
#include <Steer.h>
#include <EEPROM.h>
#include <PVector.h>
#include <TimerOne.h>

#define USB_SER                     &Serial                                            //USB串口设置

//mechanical constraints        机械臂尺寸，详细尺寸说明见说明书
const double a = 120, b = 40, c = 188, d = 24.28, e = 79, f = 21.6, g = 12, h = 34.8;

class Arm{

private:
    HardwareSerial *comSer;
    
    word *pos_goal;                                                                    //存储目标位置
    word *pos_pre;                                                                     //存储之前的舵机位置
    word *pos_step;                                                                   //存储每一次舵机的移动步长
    word clc_Times_now;                                                                     //舵机移动一个步长所耗时间，也是定时器中断的时长步数
    word clc_Times_Total;                                                              //舵机从当前位置到达目标位置的总耗时
    
    byte pos_flag;

    byte Steer_Detect();
    void Para_Init();
    
    short Rad2Pos(double rad);
    short Angle2Pos(double angle);
    short Pos2Angle(double pos);
    
    void Arm_Step_Control();
        
public:

    byte Steer_Num;
    short *offPos;
    double *theta;

    Steer *steer[7] = {NULL};
    
    void begin(HardwareSerial *desireSer);
    
    void position_init(void);
    void inverse_movement(double x_ , double y_, double z_);
    void inverse_movement(PVector pt);
    void move_to_position( double x_ , double y_, double z_ , word runtime);
    void move_to_position( PVector pt , word runtime);

    
    void offset_by_pos(byte id, short offset);
    void offset_by_angle(byte id, double angle);
    void Get_Offset();

};

double mapFloat(double val, double in_min, double in_max, double out_min, double out_max);
void timerIsr();


#endif
