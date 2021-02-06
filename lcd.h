/**********************************************
*文件名：LCD.h
*作用：定义了LCD的宏和引脚定义
	   申明了LCD相关的功能函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/08/5
**********************************************/
#ifndef _LCD_H_
#define _LCD_H_
/*************************包含头文件**********************************/
#include <reg52.h>

/*************************引脚定义************************************/
//1602
#define LCD1602_DAT P0
sbit LCD1602_RS = P2^0;
sbit LCD1602_RW = P2^1;
sbit LCD1602_E  = P1^2;

//12864
#define LCD12864_DAT P0
sbit LCD12864_RS = P2^0;
sbit LCD12864_RW = P2^1;
sbit LCD12864_PSB = P2^6;
sbit LCD12864_E  = P1^2;

/*************************宏定义**************************************/
#define INT   0
#define FLOAT 1

/*************************变量定义**************************************/

/*************************函数声明**************************************/
//1602  
//8bit
void Lcd1602_Show_str(unsigned char x, unsigned char y, unsigned char *s);
void Lcd1602_ShowStr(unsigned char x, unsigned char y, unsigned char *str, unsigned char len);
void Lcd1602_cls();
void InitLcd1602();
void Lcd1602_WaitReady();
void Lcd1602_WriteCmd(unsigned char cmd);
void Lcd1602_WriteDat(unsigned char dat);
void Lcd1602_SetCursor(unsigned char x, unsigned char y);
void Lcd1602_ds18b20id_dsp(unsigned char *ds18b20id, unsigned int y);
//12864
//8bit
void InitLcd12864();
void Lcd12864_cls();
void Lcd12864_WaitReady();
void Lcd12864_WriteCmd(unsigned char cmd);
void Lcd12864_WriteDat(unsigned char dat);
void Lcd12864_Show_Str1(unsigned char x, unsigned char y, unsigned char *str);
void Lcd12864_Show_Str2(unsigned char x, unsigned char y, unsigned char *str);
void Lcd12864_draw_point(unsigned char x, unsigned char y);
void Lcd12864_draw_pixels(unsigned char x, unsigned char y);
void Lcd12864_Show_Variate(unsigned char x, unsigned char y, unsigned int variate, unsigned char FOI);
void Lcd12864_POS(unsigned char x, unsigned char y);
void Lcd12864_ds18b20id_dsp(unsigned char x, unsigned char y, unsigned char *ds18b20id);
#endif