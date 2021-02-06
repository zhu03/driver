/******************************************
*�ļ�����COMMON.C
*���ã���Ż���ͨ�ú���
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/07/25
******************************************/	
//_nop_();    //ִ��һ��_nop_()ָ�����1us	  
#include "common.h"

/******************************************
*��������Init_Parameter
*���룺��
*���أ���
*���ã�������ʼ��
******************************************/
void Init_Parameter(void)
{
//	u8 *buf;
//	u8 rx;		   
//	u8 *str1="i love mcu";
//	u8 *str2="�ҳ�ϲ����֪����";
//	u8 a = 'a',b = 'b';
//	u8 i=7,j=3;
//	float temp =30.62;
//	uchar i;

//	unsigned char ds18b20[3]={0,0,0},ds18b20_temp=0;
//	unsigned char ds18b20id[8] = {0,0,0,0,0,0,0,0};

//	unsigned char dht11_temp[4] = {0,0,0,0};
	//unsigned char LIMI[8] = {0,0,0,0,0,0,0,0};
//	char test = -100;
//	unsigned char tests[3] = {0,0,0};
//	uint i,ds_temp;
//	unsigned int temp=0;   	  						//ע������������8λ����unsigned int��ΧΪ ��0,2^8-1=255��
//	int keynums=0,keynum=0;
//	unsigned char lcd_time[8];
//	uint8 Buf[]="i love mcu\n";
	u8 cont = 0;
}

/******************************************
*��������System_Init
*���룺��
*���أ���
*���ã�ϵͳ��ʼ��
******************************************/
void System_Init()
{
	relay(OFF);
	beep(OFF);
	led_init();
}

/******************************************
*��������BCD_Decimal
*���룺bcd
*���أ�Decimal
*���ã�BCDת����
******************************************/
unsigned char BCD_Decimal(unsigned char bcd)
{
   	unsigned char Decimal;
	Decimal=bcd>>4;
	return(Decimal=Decimal*10+(bcd&=0x0F));
}


/******************************************
*��������ʱ����
*���ã���ʱ
******************************************/
//===================================STC89ϵ��============================================//
#ifdef MHZ12
//
//bin2oct
//
//bi
/****************12.000MHz*******************/
void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void Delay10ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 20;
	j = 113;
	do
	{
		while (--j);
	} while (--i);
}

void Delay100ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 195;
	j = 138;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 154;
	k = 122;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay1us()		//@12.000MHz
{
	_nop_();
}

void Delay10us()		//@12.000MHz
{
	unsigned char i;
	_nop_();
	i = 2;
	while (--i);
}

void Delay12us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 3;
	while (--i);
}

void Delay20us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 7;
	while (--i);
}


void Delay100us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 47;
	while (--i);
}

void DelayNus(u16 t)		//@12.000MHz
{
	u16 i=0;
	for(i=0;i<t;i++)
		Delay1us();	
}

void DelayNms(u16 t)		//@12.000MHz
{
	u16 i=0;
	for(i=0;i<t;i++)
		Delay1ms();	
}

void DelayNs(u16 t)		//@12.000MHz
{
	u16 i=0;
	for(i=0;i<t;i++)
		Delay1000ms();
}
#else
/****************11.0592MHz*******************/
void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}

void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 180;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

void Delay100us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 43;
	while (--i);
}

void DelaytNus(u16 t)
{
	u16 i=0;
	for(i=0;i<t;i++)
		Delay10us();	
}

void DelayNms(u16 t)	
{
	u16 i=0;
	for(i=0;i<t;i++)
		Delay1ms();	
}

void DelayNs(u16 t)	
{
	u16 i=0;
	for(i=0;i<t;i++)
		Delay1000ms();	
}

#endif

//===================================STC15ϵ��============================================//

//#ifdef MHZ12
///****************12.000MHz*******************/
//void Delay1ms()		//@12.000MHz
//{
//	unsigned char i, j;
//
//	i = 12;
//	j = 169;
//	do
//	{
//		while (--j);
//	} while (--i);
//}
//
//void Delay10ms()		//@12.000MHz
//{
//	unsigned char i, j;
//
//	i = 117;
//	j = 184;
//	do
//	{
//		while (--j);
//	} while (--i);
//}
//
//void Delay100ms()		//@12.000MHz
//{
//	unsigned char i, j, k;
//
//	_nop_();
//	_nop_();
//	i = 5;
//	j = 144;
//	k = 71;
//	do
//	{
//		do
//		{
//			while (--k);
//		} while (--j);
//	} while (--i);
//}
//
//void Delay1000ms()		//@12.000MHz
//{
//	unsigned char i, j, k;
//
//	_nop_();
//	_nop_();
//	i = 46;
//	j = 153;
//	k = 245;
//	do
//	{
//		do
//		{
//			while (--k);
//		} while (--j);
//	} while (--i);
//}
//
//void Delay1us()		//@12.000MHz
//{
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//}
//
//void Delay10us()		//@12.000MHz
//{
//	unsigned char i;
//
//	_nop_();
//	_nop_();
//	i = 27;
//	while (--i);
//}
//
//void Delay100us()		//@12.000MHz
//{
//	unsigned char i, j;
//
//	i = 2;
//	j = 39;
//	do
//	{
//		while (--j);
//	} while (--i);
//}
//
//void DelayNus(u16 t)		//@12.000MHz
//{
//	u16 i=0;
//	for(i=0;i<t;i++)
//		Delay1us();	
//}
//
//void DelayNms(u16 t)		//@12.000MHz
//{
//	u16 i=0;
//	for(i=0;i<t;i++)
//		Delay1ms();	
//}
//
//void DelayNs(u16 t)		//@12.000MHz
//{
//	u16 i=0;
//	for(i=0;i<t;i++)
//		Delay1000ms();	
//}
//#else
///****************11.0592MHz*******************/
//void Delay1ms()		//@11.0592MHz
//{
//	unsigned char i, j;
//
//	_nop_();
//	_nop_();
//	_nop_();
//	i = 11;
//	j = 190;
//	do
//	{
//		while (--j);
//	} while (--i);
//}
//
//
//void Delay10ms()		//@11.0592MHz
//{
//	unsigned char i, j;
//
//	i = 108;
//	j = 145;
//	do
//	{
//		while (--j);
//	} while (--i);
//}
//
//
//void Delay100ms()		//@11.0592MHz
//{
//	unsigned char i, j, k;
//
//	_nop_();
//	_nop_();
//	i = 5;
//	j = 52;
//	k = 195;
//	do
//	{
//		do
//		{
//			while (--k);
//		} while (--j);
//	} while (--i);
//}
//
//void Delay1000ms()		//@11.0592MHz
//{
//	unsigned char i, j, k;
//
//	_nop_();
//	_nop_();
//	i = 43;
//	j = 6;
//	k = 203;
//	do
//	{
//		do
//		{
//			while (--k);
//		} while (--j);
//	} while (--i);
//}
//
//	
//void Delay1us()		//@11.0592MHz
//{
//	_nop_();
//	_nop_();
//	_nop_();
//}
//
//void Delay10us()		//@11.0592MHz
//{
//	unsigned char i;
//
//	_nop_();
//	i = 25;
//	while (--i);
//}
//
//void Delay100us()		//@11.0592MHz
//{
//	unsigned char i, j;
//
//	_nop_();
//	_nop_();
//	i = 2;
//	j = 15;
//	do
//	{
//		while (--j);
//	} while (--i);
//}
//
//void DelayNus(u16 t)
//{
//	u16 i=0;
//	for(i=0;i<t;i++)
//		Delay1us();	
//}
//
//void DelayNms(u16 t)	
//{
//	u16 i=0;
//	for(i=0;i<t;i++)
//		Delay1ms();	
//}
//
//void DelayNs(u16 t)	
//{
//	u16 i=0;
//	for(i=0;i<t;i++)
//		Delay1000ms();	
//}
//#endif








/*
void Delay_ms(uint n)
{
	uint i,j;
	for(i=n;i>0;i--)
		for(j=114;j>0;j--);
}

////��ʱn����  12MHz����
//void delay_ms(unsigned int n)
//{
//    unsigned int i=0,j=0;
//	for(i=0;i<n;i++)
//		for(j=0;j<123;j++);
//}

//��ʱn��   12MHz����
void delay_m(unsigned int n)
{
    unsigned int i=0,j=0;
    for(i=0;i<n;i++)
        for(j=0;j<21738;j++);
}

//��ʱ10*n΢��	12MHz����
void delay_10um(unsigned int n)
{
    while(n--);
}

//��ʱ10*n΢��	12MHz����
void delay(unsigned int n)
{
	while (n--);
}
*/