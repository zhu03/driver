/******************************************
*�ļ�����i2c.c
*���ã�ʵ��i2c�Ĺ��ܺ���
*�汾��V 0.0.1
*���ߣ�����С��
*������ڣ�2020/08/13
******************************************/

#include "i2c.h"

/******************************************
*��������i2c_Delay5us
*���룺��
*���أ���
*���ã���ʱ5us
******************************************/
void i2c_Delay5us(void)
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

/******************************************
*��������i2c_Init
*���룺��
*���أ���
*���ã�i2c��ʼ��
******************************************/
void i2c_Init(void)
{	
	SDA = 1;
	SCL = 1;
	i2c_Delay5us();
}


/******************************************
*��������i2c_Start
*���룺��
*���أ���
*���ã�i2c����
******************************************/
void i2c_Start(void)
{	
	SDA = 1;
	SCL = 1;
	i2c_Delay5us();
	SDA = 0;
	i2c_Delay5us();
	SCL = 0;
}

/******************************************
*��������i2c_Stop
*���룺��
*���أ���
*���ã�i2cֹͣ
******************************************/
void i2c_Stop(void)
{	
	SDA = 0;
	SCL = 1;	
	i2c_Delay5us();
	SDA = 1;
}

/******************************************
*��������i2c_Ask
*���룺��
*���أ���
*���ã�i2cӦ��
******************************************/
void i2c_Ask(void)
{	
	SDA = 0;		  //��Ӧ
	i2c_Delay5us();
	SCL = 1;	
	i2c_Delay5us();
	SCL = 0;
	i2c_Delay5us();	  //��SDA=0,SCL=1ʱ�����߲���Ӧ���ź�
	SDA = 1;		  //�ͷ�����
	i2c_Delay5us();
}

/******************************************
*��������i2c_Nask
*���룺��
*���أ���
*���ã�i2c��Ӧ��
******************************************/
void i2c_Nask(void)
{	
	SDA = 1;		  //��Ӧ
	i2c_Delay5us();
	SCL = 1;	
	i2c_Delay5us();	  //��SDA=1,SCL=1ʱ�����߲�����Ӧ���ź�
	SCL = 0;
	i2c_Delay5us();
	SDA = 1;		  //�ͷ�����
	i2c_Delay5us();
}

/******************************************
*��������i2c_WaitAsk
*���룺��
*���أ���
*���ã�i2c�ȴ�Ӧ���ź� 1:Ӧ�� 0:��������Ӧ
******************************************/
bit i2c_WaitAsk(void)
{	
//	bit re; //Ӧ���źŵ���0��Ӧ����ȷ������1��û��Ӧ��
	SDA = 1;		   //�ͷ����ߣ����öԷ�����
	i2c_Delay5us();
	SCL = 1;	
	i2c_Delay5us();
	if(SDA)
	{
		SCL = 0;
		i2c_Stop();
		return 0;
	}
	else
	{	
		SCL = 0;
		return 1;
	}
}

/******************************************
*��������i2c_SendByte
*���룺byte
*���أ���
*���ã�����һ���ֽ����ݵ�iic����
******************************************/
void i2c_SendByte(unsigned char byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(byte&0x80)
			SDA = 1;
		else
			SDA = 0;
		i2c_Delay5us();
		SCL = 1;
		byte <<= 1;
		i2c_Delay5us();
		SCL = 0;		
	}

}

/******************************************
*��������i2c_RecByte
*���룺��
*���أ�dat
*���ã���iic���߶�ȡһ���ֽ�����
******************************************/
unsigned char i2c_RecByte(void)
{
	unsigned char dat;
	unsigned char i;
	
	SCL = 0;			   //�ڸı�sdaǰ��ȷ��sclΪ�͵�ƽ
	i2c_Delay5us();
	SDA = 1;			   //�����ͷ�sda,�Ա�ӻ����Ըı�sda
	i2c_Delay5us();

	for(i=0;i<8;i++)
	{   
		SCL = 1;
		i2c_Delay5us();
		dat <<= 1;
		if(SDA) 
			dat |= 0x01;
		SCL = 0;
		i2c_Delay5us();
	}
	return dat;
}

/******************************************
*��������Write_Byte_E2PROM
*���룺	addr  д��ĵ�ַ
		dat	  д�������
*���أ���
*���ã���datд��eeprom��addr��
******************************************/
void Write_Byte_E2PROM(u8 addr, u8 dat)
{
	i2c_Delay5us();
	i2c_Start();
	i2c_SendByte(eeprom_wr_addr);
	i2c_Ask();
	i2c_SendByte(addr);
	i2c_Ask();
	i2c_SendByte(dat);
	i2c_Ask();
	i2c_Stop();
	i2c_Delay5us();
}

/******************************************
*��������Read_Byte_E2PROM
*���룺addr
*���أ�dat
*���ã���eeprom��addr��ַ��ȡ����
******************************************/
u8 Read_Byte_E2PROM(u8 addr)
{
	u8 dat;
	
	i2c_Delay5us();
	i2c_Start();
	i2c_SendByte(eeprom_wr_addr);
	i2c_Ask();
	i2c_SendByte(addr);
	i2c_Ask();
	i2c_Start();
	i2c_SendByte(eeprom_rd_addr);
	i2c_Ask();
	dat = i2c_RecByte();
	i2c_Nask();
	i2c_Stop();
	i2c_Delay5us();
	
	return dat;	
}
