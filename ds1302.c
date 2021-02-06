/******************************************
*文件名：DS1302.C
*作用：实现与实时时钟DS1302相关的各个功能函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/07/28
******************************************/

#include "ds1302.h"

/******************************************
*函数名：Write_Ds1302_Byte
*输入：dat			
*返回：无
*作用：给DS1302写入一字节数据
******************************************/
void Write_Ds1302_Byte(unsigned char dat) 
{
	unsigned char i;
	SCK_CLR;
	for (i=0;i<8;i++) 
	{ 
		if (dat & 0x01) 	// 等价于if((addr & 0x01) ==1) 
		{
			SDA_SET;		//#define SDA_SET SDA=1 /*电平置高*/
		}
		else 
		{
			SDA_CLR;		//#define SDA_CLR SDA=0 /*电平置低*/
		}		 
		SCK_SET;
		SCK_CLR;		
		dat = dat >> 1; 
	} 
}

/******************************************
*函数名：Read_Ds1302_Byte
*输入：无			
*返回：dat
*作用：从DS1302读出一字节数据
******************************************/
unsigned char Read_Ds1302_Byte(void) 
{
	unsigned char i, dat=0;	
	for (i=0;i<8;i++)
	{	
		dat = dat >> 1;
		if(SDA_R) 	  //等价于if(SDA_R==1)    #define SDA_R SDA /*电平读取*/	
		{
			dat |= 0x80;
		}
		else 
		{
			dat &= 0x7F;
		}
		SCK_SET;
		SCK_CLR;				//下降沿
	}
	return dat;
}

/******************************************
*函数名：Ds1302_Single_Byte_Write
*输入：	addr	地址
		dat		数据	
*返回：无
*作用：给DS1302指定地址写入一字节数据
******************************************/
void Ds1302_Single_Byte_Write(unsigned char addr, unsigned char dat)
{ 

	RST_CLR;			/*RST脚置低，实现DS1302的初始化*/
	SCK_CLR;			/*SCK脚置低，实现DS1302的初始化*/

	RST_SET;			/*启动DS1302总线,RST=1电平置高 */
	addr = addr & 0xFE;	 
	Write_Ds1302_Byte(addr); /*写入目标地址：addr,保证是写操作,写之前将最低位置零*/	
	Write_Ds1302_Byte(dat);	 /*写入数据：dat*/
	RST_CLR;				 /*停止DS1302总线*/
}

/******************************************
*函数名：Ds1302_Single_Byte_Read
*输入：	addr	地址		
*返回：temp		数据
*作用：从DS1302指定地址读出一字节数据
******************************************/
unsigned char Ds1302_Single_Byte_Read(unsigned char addr) 
{ 
	unsigned char temp;
	RST_CLR;			/*RST脚置低，实现DS1302的初始化*/
	SCK_CLR;			/*SCK脚置低，实现DS1302的初始化*/

	RST_SET;			/*启动DS1302总线,RST=1电平置高 */	
	addr = addr | 0x01;	 
	Write_Ds1302_Byte(addr); /*写入目标地址：addr,保证是读操作,写之前将最低位置高*/
	temp=Read_Ds1302_Byte(); /*从DS1302中读出一个字节的数据*/		
	RST_CLR;	/*停止DS1302总线*/
	return temp;
}

/******************************************
*函数名：Init_DS1302
*输入：	*str		
*返回：无
*作用：初始化1302，把*str中的内容写到其中
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
*函数名：RD_DS1302_Data
*输入：*str		
*返回：无
*作用：把从1302读取到的内容写到*str中
******************************************/
void RD_DS1302_Data(unsigned char *str)
{
   int i;
   for(i=0;i<7;i++)
   {
   	 str[i]=Ds1302_Single_Byte_Read(0x81+i*2);
   }
}