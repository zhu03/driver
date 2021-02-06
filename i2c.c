/******************************************
*文件名：i2c.c
*作用：实现i2c的功能函数
*版本：V 0.0.1
*作者：程序小黑
*完成日期：2020/08/13
******************************************/

#include "i2c.h"

/******************************************
*函数名：i2c_Delay5us
*输入：无
*返回：无
*作用：延时5us
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
*函数名：i2c_Init
*输入：无
*返回：无
*作用：i2c初始化
******************************************/
void i2c_Init(void)
{	
	SDA = 1;
	SCL = 1;
	i2c_Delay5us();
}


/******************************************
*函数名：i2c_Start
*输入：无
*返回：无
*作用：i2c启动
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
*函数名：i2c_Stop
*输入：无
*返回：无
*作用：i2c停止
******************************************/
void i2c_Stop(void)
{	
	SDA = 0;
	SCL = 1;	
	i2c_Delay5us();
	SDA = 1;
}

/******************************************
*函数名：i2c_Ask
*输入：无
*返回：无
*作用：i2c应答
******************************************/
void i2c_Ask(void)
{	
	SDA = 0;		  //响应
	i2c_Delay5us();
	SCL = 1;	
	i2c_Delay5us();
	SCL = 0;
	i2c_Delay5us();	  //当SDA=0,SCL=1时，总线产生应答信号
	SDA = 1;		  //释放总线
	i2c_Delay5us();
}

/******************************************
*函数名：i2c_Nask
*输入：无
*返回：无
*作用：i2c非应答
******************************************/
void i2c_Nask(void)
{	
	SDA = 1;		  //响应
	i2c_Delay5us();
	SCL = 1;	
	i2c_Delay5us();	  //当SDA=1,SCL=1时，总线产生非应答信号
	SCL = 0;
	i2c_Delay5us();
	SDA = 1;		  //释放总线
	i2c_Delay5us();
}

/******************************************
*函数名：i2c_WaitAsk
*输入：无
*返回：无
*作用：i2c等待应答信号 1:应答 0:无器件响应
******************************************/
bit i2c_WaitAsk(void)
{	
//	bit re; //应答信号等于0则应答正确，等于1则没有应答
	SDA = 1;		   //释放总线，能让对方拉低
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
*函数名：i2c_SendByte
*输入：byte
*返回：无
*作用：发送一个字节数据到iic总线
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
*函数名：i2c_RecByte
*输入：无
*返回：dat
*作用：从iic总线读取一个字节数据
******************************************/
unsigned char i2c_RecByte(void)
{
	unsigned char dat;
	unsigned char i;
	
	SCL = 0;			   //在改变sda前先确保scl为低电平
	i2c_Delay5us();
	SDA = 1;			   //主机释放sda,以便从机可以改变sda
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
*函数名：Write_Byte_E2PROM
*输入：	addr  写入的地址
		dat	  写入的数据
*返回：无
*作用：把dat写入eeprom的addr里
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
*函数名：Read_Byte_E2PROM
*输入：addr
*返回：dat
*作用：从eeprom的addr地址读取数据
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
