/*****************************************************
*文件名：HC573ANDULD2003.H
*作用：	定义了蜂鸣器和继电器、步进电机的宏和引脚定义
*		申明了蜂鸣器和继电器、步进电机相关的功能函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/07/29
*****************************************************/
#ifndef _HC573ANDULD2003_H_
#define _HC573ANDULD2003_H_
/*************************包含头文件**********************************/
#include <reg52.h>

/*************************引脚定义************************************/
/*************************宏定义**************************************/
#define ON   1
#define OFF  0

/*************************变量定义**************************************/
/*************************函数声明**************************************/
void relay(unsigned char on_off);
void beep(unsigned char on_off);

#endif