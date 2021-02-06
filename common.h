/**********************************************
*�ļ�����common.h
*���ã�	�����˹���ͨ�õĺ�����Ŷ���
*		�����˹���ͨ����صĹ��ܺ���
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/07/25
**********************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

/*************************����ͷ�ļ�**********************************/
#include "led.h"
/*************************���Ŷ���************************************/

/*************************�궨��**************************************/ 
#define uchar   unsigned char 
#define uint    unsigned int 
#define uint8   unsigned char 
#define uint16  unsigned int
#define u8   	unsigned char 
#define u16  	unsigned int
#define MHZ12

/*************************��������**************************************/
unsigned int inter;
bit temper_flag = 0;//�¶ȶ�ȡ��־
bit utl_flag = 0;//��������ȡ��־

/*************************��������**************************************/
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