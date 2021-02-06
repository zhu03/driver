/******************************************
*�ļ�����HC573ANDULD2003.C
*���ã�ʵ�ֿ��Ʒ������ȹ��ܺ���
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/07/29
******************************************/

#include "HC573ANDULD2003.h"

/******************************************
*��������relay
*���룺on_off
*���أ���
*���ã����Ƽ̵�����ͨ��
******************************************/
void relay(unsigned char on_off)
{
	if(on_off)
	{	
		P0&=0xEF;
		P0|=0x10;
	   	P2=(P2&0x1f)|0xa0;	
	   	P2&=0x1f;
	}
	else
	{	
		P0&=0xEF;
		P2=(P2&0x1f)|0xa0;
	   	P2&=0x1f;
	}	
}
/*
void beep_time(unsigned int time)
{
	if(on_off)
	{
	   	P2=(P2&0x1f)|0xa0;
		P0=P0&0XFF;
	   	P2&=0x1f;
	}
	else
	{
		P2=(P2&0x1f)|0xa0;
		P0=P0&0XBF;
	   	P2&=0x1f;
	}
}
*/

/******************************************
*��������beep
*���룺on_off
*���أ���
*���ã����Ʒ�������ͨ��
******************************************/
void beep(unsigned char on_off)
{
	if(on_off)
	{
	   	P0&=0xBF;
		P0|=0x40;
	   	P2=(P2&0x1f)|0xa0;	
	   	P2&=0x1f;
	}
	else
	{
		P0&=0xBF;
		P2=(P2&0x1f)|0xa0;
	   	P2&=0x1f;
	}
}
