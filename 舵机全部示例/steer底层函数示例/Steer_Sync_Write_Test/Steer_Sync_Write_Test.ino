/**
  *************************************************************************************************
  * @file           Steer_Sync_Write_Test
  * @author         
  * @qq             269426626
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.02
  * @note    ´      此程序用于测试同步写舵机中内存（程序过程是先读再写再读）
  * @note    ´      此程序为舵机通信底层函数
  * @config_steer   Serial1
  * @computer       Serial
  *************************************************************************************************
  */

#include<Steer_protocol.h>

const unsigned char READ_LEN = 0X02;                              //记录需要读取的内存长度
const unsigned char WRITE_LEN = 0X05;                             //记录需要写的内存长度
const unsigned char ID = 0X04;                                    //舵机ID号       

Steer_protocol Steer1(&Serial1,10);                              //初始化一个舵机对象

byte writebuf[WRITE_LEN] = {ID, 0X07, 0x77,0x0b,0xc9};            //用于写的数据
byte readbuf[READ_LEN];
bool read_flag;                                                   //接收read()函数的返回值


void setup() {
  
  Steer1.begin(&Serial,10);                                      //初始化和Arduino IDE的通信串口
  Serial.println( "Steer_protocol_init");                 

  /******************读******************/
  read_flag = Steer1.read(ID , 0x2a , readbuf , READ_LEN);        //read()函数读取当前位置数据（具体需要读取什么要查看舵机说明书）
  Serial.print("flag is :");
  Serial.print( read_flag );
  
  Serial.print("  readbuf is : ");
  for(int i = 0; i < READ_LEN; i++)
  {
    Serial.print("  0X");
    Serial.print(readbuf[i], HEX);
  }
  
  Serial.println(" ");  

 /******************写******************/
  Steer1.sync_write(0x2a , writebuf , 1 , WRITE_LEN);            
  Serial.print("flag is :");
  
  Serial.print("  buf is : ");
  for(int i = 0; i < WRITE_LEN; i++)
  {
    Serial.print("  0X");
    Serial.print(writebuf[i], HEX);
  }
  
  Serial.println(" ");

//  delay(9000);

 read_flag = Steer1.read(ID , 0x2c , readbuf , READ_LEN);             //read()函数读取当前位置数据（具体需要读取什么要查看舵机说明书）
  Serial.print("flag is :");
  Serial.print( read_flag );
  
  Serial.print("  readbuf is : ");
  for(int i = 0; i < READ_LEN; i++)
  {
    Serial.print("  0X");
    Serial.print(readbuf[i], HEX);
  }
  
  Serial.println(" ");  

/******************连续读******************/
  while(1){
  read_flag = Steer1.read(ID , 0x38 , readbuf , READ_LEN);             //read()函数读取当前位置数据（具体需要读取什么要查看舵机说明书）
  Serial.print("flag is :");
  Serial.print( read_flag );
  
  Serial.print("  readbuf is : ");
  for(int i = 0; i < READ_LEN; i++){
    Serial.print("  0X");
    Serial.print(readbuf[i], HEX);
  }  
  Serial.println(" ");  
  delay(500);
}
  Serial.println("test over");
}

void loop() {
}



