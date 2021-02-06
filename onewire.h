/*****************************************************
*文件名：ONEWIRE.H
*作用：	定义了DS18B20的宏和引脚定义
*		申明了DS18B20相关的功能函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/08/02
*****************************************************/
#ifndef _ONEWIRE_H
#define _ONEWIRE_H
/*************************包含头文件**********************************/
#include<reg52.h>

/*************************引脚定义************************************/ 
//IC引脚定义
sbit DQ = P1^4;

/*************************宏定义**************************************/
#define READ_ROM         	   0x33			//读 ROM（读取温度传感器 ROM 中的编码）
#define MATCH_ROM              0x55			//匹配 ROM（发出该指令后，再发 64 位 ROM 编码，用于匹配相应的 DS18B20）
#define SKIP_ROM               0xCC			//（跳过 ROM，忽略 64 位 ROM 地址，直接向 DS18B20 发温度变换命令）
#define SEARCH_ROM 			   0xF0			//（搜索 ROM 用于确定挂接在同一总线上 DS18B20 的数量）
#define ALARM_SEARCH		   0xEC			//告警搜索命令，执行后只有温度超过设定值的上下限才做出响应
#define Write_Scratchpad 	   0x4E			//写暂存器
#define Read_Scratchpad 	   0xBE			//读温度暂存器，读内部 RAM 中 9 字节的温度数据
#define Copy_Scratchpad 	   0x48			//复制暂存存储器
#define Convert_T		 	   0x44		  	//启动温度转换 温度转换，启动 DS18B20 进行温度转换	
#define Recall_E2              0xB8			//把E2PROM中字节写到暂存器
#define Read_Power_Supply      0xB4			//读供电模式命令			

#define _9bit				   0x1f			// 9-bit 0.5℃
#define _10bit				   0x3f			//10-bit 0.25℃
#define _11bit				   0x5f			//11-bit 0.125℃
#define _12bit				   0x7f			//12-bit 0.0625℃

#define _9bit_f				   0.5			// 9-bit 0.5℃
#define _10bit_f			   0.25			//10-bit 0.25℃
#define _11bit_f			   0.125		//11-bit 0.125℃
#define _12bit_f			   0.0625		//12-bit 0.0625℃
/*************************变量定义**************************************/
unsigned char ds18b20[3]={0,0,0},ds18b20_temp=0;
unsigned char ds18b20id[8]={0,0,0,0,0,0,0,0};
/*************************函数声明**************************************/ 
//函数声明
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