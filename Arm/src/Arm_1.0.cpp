#include <Arm_1.0.h>


Steer_protocol armSrv(&Serial1, 10);
//Steer armSrv(0, &Serial1);


 /**
 * @brief   		                  数值映射函数    
 * @code                        示例  
 *      				                      //把 3 从 （0 - 100）映射到（0 - 200）是该为6
 *      				                      xArm.mapFloat( 3, 0 , 100, 0 ,200 );      
 * @endcode
 * @param[in]                 val                     需要映射的值
 * @param[in]                 in_min                原区间的最小值            
 * @param[in]                 in_max               原区间的最大值
 * @param[in]                 out_min              需要映射到的区间的最小值
 * @param[in]                 out_max             需要映射到的区间的最大值
 * @return                                               返回值：返回映射后的值
 */
double mapFloat(double val, double in_min, double in_max, double out_min, double out_max)
{
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

 /**
 * @brief   		                  机械臂初始化函数    
 * @code                        示例  
 *      				                      //初始化串口使用 USB_SER
 *      				                      xArm.begin( USB_SER) ;     
 * @endcode
 * @param[in]                 desireSer            串口选择
 *          @arg                  USB_SER            使用USB通信
 *          @arg                  WIFI_SER            使用WiFi通信
 */
void Arm::begin(HardwareSerial *desireSer)         //机械臂初始化
{
    pinMode(BTN0_PIN, INPUT);
    pinMode(BTN1_PIN, INPUT);
    pinMode(PUMP_PIN, OUTPUT);
    pinMode(VALVE_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(V33_EN_PIN, OUTPUT);


    digitalWrite(PUMP_PIN, LOW);
    digitalWrite(VALVE_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);                   //端口配置


    comSer = desireSer;
    comSer->begin(115200);
    comSer->setTimeout(5);


    if (*comSer == WIFI_SER) {
        digitalWrite(V33_EN_PIN, HIGH);
        delay(50);
        while (comSer->available()) {
            comSer->read();
        }
    }

    srvCnt = servoDetect();

    theta = (double *)malloc(7 * sizeof(double));
    posRtData = (byte *)malloc(srvCnt * sizeof(byte) * 5);
    offPos = (short *)malloc(srvCnt * sizeof(short));


    for (byte i = 0; i < srvCnt; i++) {
        EEPROM.get(i * sizeof(short), offPos[i]);
    }

    //for 10ms
    TCCR1A = 0;                                                                                //正常模式,定时10ms
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12) | (1 << CS11);
    TCNT1 = 0;
    OCR1A = 19999;
    TIMSK1 = 0;
    TIMSK1 |= (1 << OCIE1A);
}

 /**
 * @brief   		                  舵机检测函数    
 * @code                        示例  
 *      				                      xArm.servoDetect( ) ;     
 * @endcode
 * @param[in]                 desireSer            串口选择
 *          @arg                  USB_SER            使用USB通信
 *          @arg                  WIFI_SER            使用WiFi通信
 * @return                       cnt                     返回值：可以正常通信的舵机数量
 */
byte Arm::servoDetect(){
    byte state;
    byte cnt = 0;

    for (byte i = 0; i < 7; i++) {
        if (armSrv.ping(i, &state)) {
            cnt ++;
        }
    }
    
    return cnt;
}

 /**
 * @brief   		                  运动逆解弧度    
 * @code                        示例  
 *      				                      //PVector p( 120, 188, 20)
 *      				                       xArm.IK( p) ;     
 * @endcode
 * @param[in]                  pt                       PVector 的一个对象，作为逆解的目标位置
 **/
void Arm::IK(PVector pt) {
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
   
    Serial.print("Myarm.theta[0] = ");Serial.println(theta[0]);
    Serial.print("Myarm.theta[1] = ");Serial.println(theta[1]);
    Serial.print("Myarm.theta[2] = ");Serial.println(theta[2]);
}

 /**
 * @brief   		                  起始位置设定和移动    
 * @code                        示例  
 *      				                       xArm.originalPositionMove( ) ;     
 * @endcode
 **/
void Arm::originalPositionMove()
{
    xyz_pre = PVector(0, 212.28, 233.8);

    for(byte i = 0; i < srvCnt; i++){
        *(posRtData + i*5) = i;
        *(posRtData + i*5 + 1) = highByte(2047 + offPos[i]);
        *(posRtData + i*5 + 2) = lowByte(2047 + offPos[i]);
        *(posRtData + i*5 + 3) = 0xb;
        *(posRtData + i*5 + 4) = 0xb8;
    }
    armSrv.sync_write(TARGET_POSITION_H, posRtData, srvCnt, 5);
}

 /**
 * @brief   		                  角度设定函数    
 * @code                        示例  
 *      				                      //把 设定旋转角度都为90°， 设定运转时间为3000ms, 设定double p = { 90，,90，......，90 } ;  word time = 3000;  
 *      				                      xArm.angleMove( p，time);      
 * @endcode
 * @param[in]                 angle                      数组首地址
 * @param[in]                 angleRunTime         运行时间            
 */
void Arm::angleMove(double *angle, word angleRunTime)
{
    for (byte i = 0; i < srvCnt; i++) {
        short tmpPos = mapFloat(angle[i], 0, 180, 1024, 3071) + offPos[i];
        *(posRtData + i*5)= i;
        *(posRtData + i*5 + 1) = highByte(tmpPos);
        *(posRtData + i*5 + 2) = lowByte(tmpPos);
        *(posRtData + i*5 + 3) = highByte(angleRunTime);
        *(posRtData + i*5 + 4) = lowByte(angleRunTime);
    }
    armSrv.sync_write(TARGET_POSITION_H, posRtData, srvCnt, 5);
}

 /**
 * @brief   		                  运动逆解函数设定    
 * @code                        示例  
 *      				                      //PVector p( 120,200,60) 
 *      				                      xArm.IKMove( p，3000, 90, 90, 90);      
 * @endcode
 * @param[in]                 pt                           PVector 的一个对象，作为逆解的目标位置
 * @param[in]                 ptRunTime              运行时间（单位：MS）                            
 * @param[in]                 theta3                     参考说明书机械图设定第三个舵机的角度            
 * @param[in]                 theta4                     参考说明书机械图设定第四个舵机的角度            
 * @param[in]                 theta5                     参考说明书机械图设定第五个舵机的角度            
 */
void Arm::IKMove(PVector pt, word ptRunTime, double theta3, double theta4, double theta5)
{
    double *tmpAngle;
    xyz = pt;
    clcTotalTimes = ptRunTime / 10;
    clcTimes = 0;
    FSMState = 1;

    PVector delta = xyz.sub(xyz_pre);
    stp_x = delta.x / clcTotalTimes;
    stp_y = delta.y / clcTotalTimes;
    stp_z = delta.z / clcTotalTimes;

    if(theta3 != -1){
        short tmpPos = mapFloat(theta3, 0, 180, 1024, 3071) + offPos[3];
        *(posRtData + 15) = 3;
        *(posRtData + 16) = highByte(tmpPos);
        *(posRtData + 17) = lowByte(tmpPos);
        *(posRtData + 18) = highByte(ptRunTime);
        *(posRtData + 19) = lowByte(ptRunTime);

        armSrv.sync_write(TARGET_POSITION_H, &posRtData[15], 1, 5);
    }

    if(theta4 != -1){
        short tmpPos = mapFloat(theta4, 0, 180, 1024, 3071) + offPos[4];
        *(posRtData + 20) = 4;
        *(posRtData + 21) = highByte(tmpPos);
        *(posRtData + 22) = lowByte(tmpPos);
        *(posRtData + 23) = highByte(ptRunTime);
        *(posRtData + 24) = lowByte(ptRunTime);

        armSrv.sync_write(TARGET_POSITION_H, &posRtData[20], 1, 5 );
    }

    if(theta5 != -1){
        short tmpPos = mapFloat(theta5, 0, 180, 1024, 3071) + offPos[5];
        *(posRtData + 25) = 5;
        *(posRtData + 26) = highByte(tmpPos);
        *(posRtData + 27) = lowByte(tmpPos);
        *(posRtData + 28) = highByte(ptRunTime);
        *(posRtData + 29) = lowByte(ptRunTime);

        armSrv.sync_write(TARGET_POSITION_H, &posRtData[25], 1, 5 );
    }
}

 /**
 * @brief   		                  舵机控制函数   
 * @code                        示例  
 *      				                      xArm.servoControl( );      
 * @endcode
 */
void Arm::servoControl()
{
    if (FSMState == 1) {
        if (clcTimes < clcTotalTimes) {

            clcTimes ++;

            PVector tmp(xyz_pre.x + clcTimes*stp_x, xyz_pre.y + clcTimes*stp_y, xyz_pre.z + clcTimes*stp_z);
            IK(tmp);

            short tmpPos = rad2Pos(theta[0]) + offPos[0];
            *posRtData = 0;
            *(posRtData + 1) = highByte(tmpPos);
            *(posRtData + 2) = lowByte(tmpPos);
            *(posRtData + 3) = 0;
            *(posRtData + 4) = 10;
            Serial.print(tmpPos);
            Serial.print('\t');


            tmpPos = rad2Pos(theta[1]) + offPos[1];
            *(posRtData + 5) = 1;
            *(posRtData + 6) = highByte(tmpPos);
            *(posRtData + 7) = lowByte(tmpPos);
            *(posRtData + 8) = 0;
            *(posRtData + 9) = 10;
            Serial.print(tmpPos);
            Serial.print('\t');


            tmpPos = rad2Pos(theta[2]) + offPos[2];
            *(posRtData + 10) = 2;
            *(posRtData + 11) = highByte(tmpPos);
            *(posRtData + 12) = lowByte(tmpPos);
            *(posRtData + 13) = 0;
            *(posRtData + 14) = 10;
            Serial.println(tmpPos);

            armSrv.sync_write(TARGET_POSITION_H, posRtData, 3, 5);
        }
        else{
            xyz_pre = xyz;
            FSMState = 0;
        }
    }
}

 /**
 * @brief   		                  弧度映射函数   
 * @code                        示例  
 *      				                      xArm.rad2Pos(  0.8 );      
 * @endcode
 * @param[in]                 rad                    需要转换的弧度值            
 */
short Arm::rad2Pos(double rad)
{
    return short(mapFloat(rad, 0, PI, 1024, 3071));
}


 /**
 * @brief   		                  真空吸盘控制函数   
 * @code                        示例  设真空吸盘状态为吸状态
 *      				                      xArm.pumpSuck(  true );      
 * @endcode
 * @param[in]                 state                 状态
 *          @arg                  true            为真，吸盘吸住
 *          @arg                  false           为假，吸盘释放
 */
void Arm::pumpSuck(bool state)
{
    digitalWrite(PUMP_PIN, state ? HIGH : LOW);
    digitalWrite(VALVE_PIN, state ? LOW : HIGH);
}


 /**
 * @brief   		                  偏置设定函数   
 * @code                        示例  设定ID= 3 的舵机的偏置设定为25°
 *      				                      xArm.offset(  3,  25 );      
 * @endcode
 * @param[in]                 id                舵机的id
 * @param[in]                 offset          舵机的偏置角度
 */
void Arm::offsetSet(byte id, short offset)
{
    EEPROM.put(id * sizeof(short), offset);
    offPos[id] = offset;
}


void Arm::offset_Angle( byte id, double off_angle)
{
  short offset_ = mapFloat(off_angle, 0, 180, 0, 2047);
  EEPROM.put(id * sizeof(short), offset_);
   offPos[id] = offset_;
}


Arm xArm = Arm();                                                          

 /**
 * @brief   		                  定时器1的中断函数   
 * @code                        
 *      				              用户不需要调用      
 * @endcode
 */
ISR(TIMER1_COMPA_vect)
{
    xArm.servoControl();
}
