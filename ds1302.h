/**********************************************
*文件名：DS1302.h
*作用：定义了DS1302的宏和引脚定义
	   申明了DS1302相关的功能函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/07/27
**********************************************/
#ifndef  __DS1302_H__
#define  __DS1302_H__

/*************************包含头文件**********************************/
#include <reg52.h>
#include <intrins.h>
/*************************引脚定义************************************/ 
sbit SCK=P1^7;		
sbit SD=P2^3;		
sbit RST=P1^3;
/*************************宏定义**************************************/ 
/*复位脚*/
#define RST_CLR	RST=0	/*电平置低*/
#define RST_SET	RST=1	/*电平置高*/
/*双向数据*/
#define SDA_CLR	SD=0	/*电平置低*/
#define SDA_SET	SD=1	/*电平置高*/
#define SDA_R	SD	    /*电平读取*/	
/*时钟信号*/
#define SCK_CLR	SCK=0	/*时钟信号*/
#define SCK_SET	SCK=1	/*电平置高*/
/********************************************************************/ 
#define ds1302_sec_addr			0x80		//秒数据地址
#define ds1302_min_addr			0x82		//分数据地址
#define ds1302_hr_addr			0x84		//时数据地址
#define ds1302_date_addr		0x86		//日数据地址
#define ds1302_month_addr		0x88		//月数据地址
#define ds1302_day_addr			0x8A		//星期数据地址
#define ds1302_year_addr		0x8C		//年数据地址

#define ds1302_control_addr		0x8Ee		//写保护命令字单元地址
#define ds1302_charger_addr		0x90 		//涓电流充电命令字地址			 
#define ds1302_clkburst_addr	0xBE		//日历、时钟突发模式命令字地址
/*************************变量定义**************************************/  
unsigned char time[7]={0x30,0x59,0x23,0x26,0x10,0x06,0x11};
unsigned char time_rd[7]={0};
/*************************函数声明**************************************/ 
/*单字节写入一字节数据*/
void Write_Ds1302_Byte(unsigned char dat); 
/*单字节读出一字节数据*/
unsigned char Read_Ds1302_Byte(void);
/*向DS1302单字节写入一字节数据*/
void Ds1302_Single_Byte_Write(unsigned char addr, unsigned char dat);
/*从DS1302单字节读出一字节数据*/
unsigned char Ds1302_Single_Byte_Read(unsigned char addr);
/*从DS1302读出数据*/
void RD_DS1302_Data(unsigned char *str);
/*初始化DS1302*/
void Init_DS1302(unsigned char *str);



#endif