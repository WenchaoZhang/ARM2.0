/**
  *************************************************************************************************
  * @file           Pvector_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.03
  * @note    ´      此程序测试位置向量的初始化，介绍了初始化的方法
  * @note    ´      此程序为位置向量应用
  * @computer       Serial
  *************************************************************************************************
  */

#include<PVector.h>

void _display(PVector p);                             //显示函数，负责把位置向量里面的参数打印出来

PVector p1;                                           //初始化1
PVector p2(1.2, 2.3, 3.3);                            //初始化2

void setup() {
  Serial.begin(115200);
  _display(p1);
  _display(p2);  
}

void loop() {
}

void _display(PVector p)
{
  Serial.println("Display: ");
  Serial.print("p.x = ");    Serial.print(p.x);      
  Serial.print("   p.y = "); Serial.print(p.y);    
  Serial.print("   p.z = "); Serial.print(p.z);
  Serial.println(" ");    
}
