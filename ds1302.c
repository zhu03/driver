/******************************************
*�ļ�����DS1302.C
*���ã�ʵ����ʵʱʱ��DS1302��صĸ������ܺ���
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/07/28
******************************************/

#include "ds1302.h"

/******************************************
*��������Write_Ds1302_Byte
*���룺dat			
*���أ���
*���ã���DS1302д��һ�ֽ�����
******************************************/
void Write_Ds1302_Byte(unsigned char dat) 
{
	unsigned char i;
	SCK_CLR;
	for (i=0;i<8;i++) 
	{ 
		if (dat & 0x01) 	// �ȼ���if((addr & 0x01) ==1) 
		{
			SDA_SET;		//#define SDA_SET SDA=1 /*��ƽ�ø�*/
		}
		else 
		{
			SDA_CLR;		//#define SDA_CLR SDA=0 /*��ƽ�õ�*/
		}		 
		SCK_SET;
		SCK_CLR;		
		dat = dat >> 1; 
	} 
}

/******************************************
*��������Read_Ds1302_Byte
*���룺��			
*���أ�dat
*���ã���DS1302����һ�ֽ�����
******************************************/
unsigned char Read_Ds1302_Byte(void) 
{
	unsigned char i, dat=0;	
	for (i=0;i<8;i++)
	{	
		dat = dat >> 1;
		if(SDA_R) 	  //�ȼ���if(SDA_R==1)    #define SDA_R SDA /*��ƽ��ȡ*/	
		{
			dat |= 0x80;
		}
		else 
		{
			dat &= 0x7F;
		}
		SCK_SET;
		SCK_CLR;				//�½���
	}
	return dat;
}

/******************************************
*��������Ds1302_Single_Byte_Write
*���룺	addr	��ַ
		dat		����	
*���أ���
*���ã���DS1302ָ����ַд��һ�ֽ�����
******************************************/
void Ds1302_Single_Byte_Write(unsigned char addr, unsigned char dat)
{ 

	RST_CLR;			/*RST���õͣ�ʵ��DS1302�ĳ�ʼ��*/
	SCK_CLR;			/*SCK���õͣ�ʵ��DS1302�ĳ�ʼ��*/

	RST_SET;			/*����DS1302����,RST=1��ƽ�ø� */
	addr = addr & 0xFE;	 
	Write_Ds1302_Byte(addr); /*д��Ŀ���ַ��addr,��֤��д����,д֮ǰ�����λ����*/	
	Write_Ds1302_Byte(dat);	 /*д�����ݣ�dat*/
	RST_CLR;				 /*ֹͣDS1302����*/
}

/******************************************
*��������Ds1302_Single_Byte_Read
*���룺	addr	��ַ		
*���أ�temp		����
*���ã���DS1302ָ����ַ����һ�ֽ�����
******************************************/
unsigned char Ds1302_Single_Byte_Read(unsigned char addr) 
{ 
	unsigned char temp;
	RST_CLR;			/*RST���õͣ�ʵ��DS1302�ĳ�ʼ��*/
	SCK_CLR;			/*SCK���õͣ�ʵ��DS1302�ĳ�ʼ��*/

	RST_SET;			/*����DS1302����,RST=1��ƽ�ø� */	
	addr = addr | 0x01;	 
	Write_Ds1302_Byte(addr); /*д��Ŀ���ַ��addr,��֤�Ƕ�����,д֮ǰ�����λ�ø�*/
	temp=Read_Ds1302_Byte(); /*��DS1302�ж���һ���ֽڵ�����*/		
	RST_CLR;	/*ֹͣDS1302����*/
	return temp;
}

/******************************************
*��������Init_DS1302
*���룺	*str		
*���أ���
*���ã���ʼ��1302����*str�е�����д������
******************************************/
void Init_DS1302(unsigned char *str)
{
	unsigned i;
	Ds1302_Single_Byte_Write(0x8e,0x00);
	for(i=0;i<7;i++)
	{
		Ds1302_Single_Byte_Write(0x80+2*i,str[i]);
	}	
	Ds1302_Single_Byte_Write(0x8e,0x80);
}

/******************************************
*��������RD_DS1302_Data
*���룺*str		
*���أ���
*���ã��Ѵ�1302��ȡ��������д��*str��
******************************************/
void RD_DS1302_Data(unsigned char *str)
{
   int i;
   for(i=0;i<7;i++)
   {
   	 str[i]=Ds1302_Single_Byte_Read(0x81+i*2);
   }
}