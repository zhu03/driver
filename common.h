/**********************************************
*文件名：common.h
*作用：	定义了工程通用的宏和引脚定义
*		申明了工程通用相关的功能函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/07/25
**********************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

/*************************包含头文件**********************************/
#include "led.h"
/*************************引脚定义************************************/

/*************************宏定义**************************************/ 
#define uchar   unsigned char 
#define uint    unsigned int 
#define uint8   unsigned char 
#define uint16  unsigned int
#define u8   	unsigned char 
#define u16  	unsigned int
#define MHZ12

/*************************变量定义**************************************/
unsigned int inter;
bit temper_flag = 0;//温度读取标志
bit utl_flag = 0;//超声波读取标志

/*************************函数声明**************************************/
void GPIO_Init(void);
void Init_Parameter(void);
void System_Init();
unsigned char BCD_Decimal(unsigned char bcd);

void Delay1ms();
void Delay10ms();
void Delay100ms();
void Delay1000ms();
void DelayNms(u16 t);
void DelayNs(u16 t);
void Delay1us();
void Delay12us();
void Delay10us();
void Delay20us();
void Delay100us();
void DelayNus(u16 t);
void DelaytNus(u16 t);	  //@11.0592MHz

//void Delay_ms(uint n);
////void delay_ms(unsigned int n);
//void delay_m(unsigned int n);
//void delay_10um(unsigned int n);
//void delay(unsigned int n);
#endif