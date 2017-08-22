#ifndef ARM_1.0_H
#define ARM_1.0_H

#include <Arduino.h>
#include <Serial_arm.h>
#include <HardwareSerial.h>
#include <Steer_protocol.h>
#include <Steer.h>
#include <EEPROM.h>
#include <PVector.h>


#define USB_SER                     Serial                                            //USB串口设置
#define WIFI_SER                    Serial3                                          //WiFi串口设置

#define BTN0_PIN                   2                                                 //暂未定义功能
#define BTN1_PIN                   3                                                 //暂未定义功能
#define PUMP_PIN                  40                                               //真空吸盘作用引脚（可以扩展为其他用途的末端执行机构作用引脚）
#define VALVE_PIN                  36                                              //
#define BUZZER_PIN                37                                              //蜂鸣器引脚
#define V33_EN_PIN                42                                             //3V3使能端


//mechanical constraints        机械臂尺寸，详细尺寸说明见说明书
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
