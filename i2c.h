/*****************************************************
*文件名：I2C.H
*作用：	定义了IIC的宏和引脚定义
*		申明了IIC相关的功能函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/08/13
*****************************************************/
#ifndef _I2C_H_
#define _I2C_H_
/*************************包含头文件**********************************/
#include "intrins.h"
/*************************引脚定义************************************/
sbit SDA = P2^1;  /* 数据线 */
sbit SCL = P2^0;  /* 时钟线 */
/*************************宏定义**************************************/
#define eeprom_wr_addr 0xa0
#define eeprom_rd_addr 0xa1
/*************************变量定义**************************************/
/*************************函数声明**************************************/
void i2c_Delay5us(void);
void i2c_Init(void);
void i2c_Start(void);
void i2c_Stop(void);
void i2c_Ask(void);
void i2c_Nask(void);
bit i2c_WaitAsk(void);
void i2c_SendByte(unsigned char byte);
unsigned char i2c_RecByte(void);

//-------------------------EEPROM---------------------------------------------
void Write_Byte_E2PROM(u8 addr, u8 dat);
u8 Read_Byte_E2PROM(u8 addr);
#endif