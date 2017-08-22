#ifndef ARM_1.0_H
#define ARM_1.0_H

#include <Arduino.h>
#include <Serial_arm.h>
#include <HardwareSerial.h>
#include <Steer_protocol.h>
#include <Steer.h>
#include <EEPROM.h>
#include <PVector.h>


#define USB_SER                     Serial                                            //USB��������
#define WIFI_SER                    Serial3                                          //WiFi��������

#define BTN0_PIN                   2                                                 //��δ���幦��
#define BTN1_PIN                   3                                                 //��δ���幦��
#define PUMP_PIN                  40                                               //��������������ţ�������չΪ������;��ĩ��ִ�л����������ţ�
#define VALVE_PIN                  36                                              //
#define BUZZER_PIN                37                                              //����������
#define V33_EN_PIN                42                                             //3V3ʹ�ܶ�


//mechanical constraints        ��е�۳ߴ磬��ϸ�ߴ�˵����˵����
const double a = 120, b = 40, c = 188, d = 24.28, e = 79, f = 21.6, g = 12, h = 34.8;


class Arm{
private:
    HardwareSerial *comSer;

  //  byte servoDetect();
    short rad2Pos(double rad);

    PVector xyz;
    PVector xyz_pre;

    word clcTimes;
    word clcTotalTimes;

    double stp_x;
    double stp_y;
    double stp_z;

    byte FSMState;

public:
    byte srvCnt;
    double *theta;
    
    byte servoDetect();

    short *offPos;
    byte *posRtData;

    void begin(HardwareSerial *desireSer);
    void IK(PVector pt);
    void IKMove(PVector pt, word ptRunTime, double theta3 = -1, double theta4 = -1, double theta5 = -1);
    void angleMove(double *angle, word angleRunTime);
    void originalPositionMove();
    void servoControl();
    void offsetSet(byte id, short offset);
    
    void offset_Angle( byte id, double off_angle);
    
    void pumpSuck(bool state);
};

extern Arm xArm;

#endif
