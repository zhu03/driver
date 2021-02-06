/*****************************************************
*�ļ�����DISPLAY.H
*���ã�	����������ܵĺ�����Ŷ���
*		�������������صĹ��ܺ���
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/07/28
*****************************************************/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_
/*************************����ͷ�ļ�**********************************/
#include "common.h"
#include <reg52.h>

/*************************���Ŷ���************************************/

/*************************�궨��**************************************/
#define INT   0
#define FLOAT 1
#define YEAR  1
#define NYEAR 0
/*************************��������**************************************/
code uchar tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
		0xc0&0x7f,0xf9&0x7f,0xa4&0x7f,0xb0&0x7f,0x99&0x7f,0x92&0x7f,
		0x82&0x7f,0xf8&0x7f,0x80&0x7f,0x90&0x7f,
		0xff,0xbf,//20-21 �� -
		0x88,0x83,0xc6,0xa1,0x86,0x8e};//22-27  a-f
//code uchar tab_lt[]={0x88,0x83,0xcb,0xa1,0x86,0x8e};
uchar dspcom=0;
uchar dspbuf[8]={20,20,20,20,20,20,20,20};
/*************************��������**************************************/
void dsp();
void smgdsp(unsigned char pwm);

void temp_dsp(unsigned char temp_int, unsigned char temp_float, unsigned char flag, unsigned char FOI);
void ds18b20id_dsp(unsigned char *ds18b20id,unsigned int i,unsigned int times);

void DS1302_dsp_time(unsigned char *time);
void DS1302_dsp_date(unsigned char *time,unsigned char year);
void DS1302_dsp_week(unsigned char *time);
#endif