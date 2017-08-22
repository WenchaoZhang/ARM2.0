#ifndef ARM_H
#define ARM_H

#include <Arduino.h>
#include <Serial_arm.h>
#include <HardwareSerial.h>
#include <Steer.h>
#include <EEPROM.h>
#include <PVector.h>
#include <TimerOne.h>

#define USB_SER                     &Serial                                            //USB��������

//mechanical constraints        ��е�۳ߴ磬��ϸ�ߴ�˵����˵����
const double a = 120, b = 40, c = 188, d = 24.28, e = 79, f = 21.6, g = 12, h = 34.8;

class Arm{

private:
    HardwareSerial *comSer;
    
    word *pos_goal;                                                                    //�洢Ŀ��λ��
    word *pos_pre;                                                                     //�洢֮ǰ�Ķ��λ��
    word *pos_step;                                                                   //�洢ÿһ�ζ�����ƶ�����
    word clc_Times_now;                                                                     //����ƶ�һ����������ʱ�䣬Ҳ�Ƕ�ʱ���жϵ�ʱ������
    word clc_Times_Total;                                                              //����ӵ�ǰλ�õ���Ŀ��λ�õ��ܺ�ʱ
    
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
