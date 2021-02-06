/**********************************************
*�ļ�����DS1302.h
*���ã�������DS1302�ĺ�����Ŷ���
	   ������DS1302��صĹ��ܺ���
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/07/27
**********************************************/
#ifndef  __DS1302_H__
#define  __DS1302_H__

/*************************����ͷ�ļ�**********************************/
#include <reg52.h>
#include <intrins.h>
/*************************���Ŷ���************************************/ 
sbit SCK=P1^7;		
sbit SD=P2^3;		
sbit RST=P1^3;
/*************************�궨��**************************************/ 
/*��λ��*/
#define RST_CLR	RST=0	/*��ƽ�õ�*/
#define RST_SET	RST=1	/*��ƽ�ø�*/
/*˫������*/
#define SDA_CLR	SD=0	/*��ƽ�õ�*/
#define SDA_SET	SD=1	/*��ƽ�ø�*/
#define SDA_R	SD	    /*��ƽ��ȡ*/	
/*ʱ���ź�*/
#define SCK_CLR	SCK=0	/*ʱ���ź�*/
#define SCK_SET	SCK=1	/*��ƽ�ø�*/
/********************************************************************/ 
#define ds1302_sec_addr			0x80		//�����ݵ�ַ
#define ds1302_min_addr			0x82		//�����ݵ�ַ
#define ds1302_hr_addr			0x84		//ʱ���ݵ�ַ
#define ds1302_date_addr		0x86		//�����ݵ�ַ
#define ds1302_month_addr		0x88		//�����ݵ�ַ
#define ds1302_day_addr			0x8A		//�������ݵ�ַ
#define ds1302_year_addr		0x8C		//�����ݵ�ַ

#define ds1302_control_addr		0x8Ee		//д���������ֵ�Ԫ��ַ
#define ds1302_charger_addr		0x90 		//丵�����������ֵ�ַ			 
#define ds1302_clkburst_addr	0xBE		//������ʱ��ͻ��ģʽ�����ֵ�ַ
/*************************��������**************************************/  
unsigned char time[7]={0x30,0x59,0x23,0x26,0x10,0x06,0x11};
unsigned char time_rd[7]={0};
/*************************��������**************************************/ 
/*���ֽ�д��һ�ֽ�����*/
void Write_Ds1302_Byte(unsigned char dat); 
/*���ֽڶ���һ�ֽ�����*/
unsigned char Read_Ds1302_Byte(void);
/*��DS1302���ֽ�д��һ�ֽ�����*/
void Ds1302_Single_Byte_Write(unsigned char addr, unsigned char dat);
/*��DS1302���ֽڶ���һ�ֽ�����*/
unsigned char Ds1302_Single_Byte_Read(unsigned char addr);
/*��DS1302��������*/
void RD_DS1302_Data(unsigned char *str);
/*��ʼ��DS1302*/
void Init_DS1302(unsigned char *str);



#endif