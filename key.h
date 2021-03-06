/**********************************************
*文件名：KEY.H
*作用：	定义了KEY的宏和引脚定义
*		申明了KEY相关的功能函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/07/04
**********************************************/
#ifndef _KEY_H_
#define _KEY_H_
/*************************包含头文件**********************************/
#include "common.h"
#include <reg52.h>

/*************************引脚定义************************************/
sbit s7=P3^0;
sbit s6=P3^1;
sbit s5=P3^2;
sbit s4=P3^3;

/*************************宏定义**************************************/
#define KEY P3
#define IAP 0  			//比赛把0改1
/*************************变量定义**************************************/

/*************************函数声明**************************************/
uchar KEY_Scan();
uchar KEY_Scan_L(uchar row);
uchar KEY_Scan16();
uint KEY_Scan16_Return_Int();
void KEY_delayms(int t);
#endif