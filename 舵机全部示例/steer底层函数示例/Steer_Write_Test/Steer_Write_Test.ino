/**
  *************************************************************************************************
  * @file           Steer_Write_Test
  * @author         
  * @qq             269426626  
  * @qq_group       604556405
  * @version        V1.0
  * @date           2017.08.01
  * @note    ´      此程序用于测试舵机写内存(程序过程为先读再写再读)
  * @note    ´      此程序为舵机通信底层函数
  * @config_steer   Serial1
  * @computer       Serial
  *************************************************************************************************
  */
#include<Steer_protocol.h>

Steer_protocol fz1(&Serial1,10);

const unsigned char READ_LEN = 0X02;                             //记录需要读取的内存长度
const unsigned char WRITE_LEN = 0X02;                            //记录需要写入的内存长度
const unsigned char ID = 0X04;                                   //舵机ID号
const unsigned char ADDR = 0X12;                                 //内存首地址


byte writebuf[WRITE_LEN] = {0X03, 0X04};                         //用于存储需要写的数据
byte readbuf[READ_LEN];                                          //存储读的数据
bool read_flag;                                                  //接收read()函数的返回值

void setup() {
  delay(100);

  Serial.begin(115200);

 /*****************读*********************/
  read_flag = fz1.read(ID , 0X2E , readbuf , READ_LEN);         //read()函数读取当前位置数据（具体需要读取什么要查看舵机说明书）
  Serial.print("flag is :");
  Serial.print( read_flag );
  
  Serial.print("  readbuf is : ");
  for(int i = 0; i < READ_LEN; i++)
  {
    Serial.print("  0X");
    Serial.print(readbuf[i], HEX);
  }
  
  Serial.println(" ");  

  /*****************写*********************/
  fz1.write(ID , ADDR , writebuf , WRITE_LEN);                   //给ID = 3 的舵机在起始位置为0x12的地方写入数据
  Serial.print("flag is :");
  
  Serial.print("  buf is : ");
  for(int i = 0; i < WRITE_LEN; i++)
  {
    Serial.print("  0X");
    Serial.print(writebuf[i], HEX);
  }
  
  Serial.println(" ");

  delay(3000);

 /*****************读*********************/
  read_flag = fz1.read(ID , ADDR , readbuf , READ_LEN);           //read()函数读取当前位置数据（具体需要读取什么要查看舵机说明书）
  Serial.print("flag is :");
  Serial.print( read_flag );
  
  Serial.print("  readbuf is : ");
  for(int i = 0; i < READ_LEN; i++)
  {
    Serial.print("  0X");
    Serial.print(readbuf[i], HEX);
  }
  
  Serial.println(" ");  
}

void loop() {
  fz1.reset(0);
 read_flag = fz1.read(1 , 0X38 , readbuf ,2);         //read()函数读取当前位置数据（具体需要读取什么要查看舵机说明书）
  Serial.print("flag is :");
  Serial.print( read_flag );
  
  Serial.print("  readbuf is : ");
  for(int i = 0; i < READ_LEN; i++)
  {
    Serial.print("  0X");
    Serial.print(readbuf[i], HEX);
  }
  
  Serial.println(" ");  
}
