/**
  *************************************************************************************************
  * @file           Eeprom_Put_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.08
  * @note    ´      此程序为偏置offset函数的预备知识学习，学习eeprom.put()的使用
  * @computer       Serial
  *************************************************************************************************
  */
#include <EEPROM.h>

short *offPos;                                                  //指针
short pos = 0x12cd;

void setup() {
  
  Serial.begin(115200);

  byte high = highByte(pos);
  byte low = lowByte(pos);
  
  Serial.print("highbyte is  0X"); Serial.println(high, HEX);
  Serial.print("lowbyte is   0X"); Serial.println(low, HEX);
  
  offPos = (short *)malloc(6* sizeof(short));                   //内存分配
  
  for (short i = 0; i < 6; i++) {
    EEPROM.put(i * sizeof(short), i*i);                        //向申请的内存中写入数据，请注意区分put和write的区别
    EEPROM.get(i * sizeof(short), offPos[i]);
    Serial.println("the number of i is:");
    Serial.println(offPos[i]);
  }
}

void loop() {
}
