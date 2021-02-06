/*****************************************************
*�ļ�����ONEWIRE.H
*���ã�	������DS18B20�ĺ�����Ŷ���
*		������DS18B20��صĹ��ܺ���
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/08/02
*****************************************************/
#ifndef _ONEWIRE_H
#define _ONEWIRE_H
/*************************����ͷ�ļ�**********************************/
#include<reg52.h>

/*************************���Ŷ���************************************/ 
//IC���Ŷ���
sbit DQ = P1^4;

/*************************�궨��**************************************/
#define READ_ROM         	   0x33			//�� ROM����ȡ�¶ȴ����� ROM �еı��룩
#define MATCH_ROM              0x55			//ƥ�� ROM��������ָ����ٷ� 64 λ ROM ���룬����ƥ����Ӧ�� DS18B20��
#define SKIP_ROM               0xCC			//������ ROM������ 64 λ ROM ��ַ��ֱ���� DS18B20 ���¶ȱ任���
#define SEARCH_ROM 			   0xF0			//������ ROM ����ȷ���ҽ���ͬһ������ DS18B20 ��������
#define ALARM_SEARCH		   0xEC			//�澯�������ִ�к�ֻ���¶ȳ����趨ֵ�������޲�������Ӧ
#define Write_Scratchpad 	   0x4E			//д�ݴ���
#define Read_Scratchpad 	   0xBE			//���¶��ݴ��������ڲ� RAM �� 9 �ֽڵ��¶�����
#define Copy_Scratchpad 	   0x48			//�����ݴ�洢��
#define Convert_T		 	   0x44		  	//�����¶�ת�� �¶�ת�������� DS18B20 �����¶�ת��	
#define Recall_E2              0xB8			//��E2PROM���ֽ�д���ݴ���
#define Read_Power_Supply      0xB4			//������ģʽ����			

#define _9bit				   0x1f			// 9-bit 0.5��
#define _10bit				   0x3f			//10-bit 0.25��
#define _11bit				   0x5f			//11-bit 0.125��
#define _12bit				   0x7f			//12-bit 0.0625��

#define _9bit_f				   0.5			// 9-bit 0.5��
#define _10bit_f			   0.25			//10-bit 0.25��
#define _11bit_f			   0.125		//11-bit 0.125��
#define _12bit_f			   0.0625		//12-bit 0.0625��
/*************************��������**************************************/
unsigned char ds18b20[3]={0,0,0},ds18b20_temp=0;
unsigned char ds18b20id[8]={0,0,0,0,0,0,0,0};
/*************************��������**************************************/ 
//��������
void Delay_OneWire(unsigned int t);
void Write_DS18B20(unsigned char dat);
bit Init_DS18B20(void);
unsigned char Read_DS18B20(void);
unsigned char *read_temp();
unsigned char rd_temperature(void);
void Read_ROM(unsigned char *ROM);
unsigned char *Match_ROM(unsigned char *ROM);
void get_Temp_HL(unsigned char *limit);
void Temp_HL_CONF(char TH,char TL,char precision);
#endif