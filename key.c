/*************************************************
*文件名：KEY.C
*作用：实现获取按键键值的各个功能函数和辅助函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/07/04
*************************************************/

#include "key.h"
/******************************************
*函数名：KEY_delayms
*输入：t   时间
*返回：无
*作用：延时tMS
******************************************/
void KEY_delayms(int t)
{
   int i,j;
   for(i=500;i>0;i--)
   	 for(j=t;j>0;j--);

}

/******************************************
*函数名：KEY_Scan_L
*输入：row(1\2\3\4)
*返回：键值
*作用：获取某列4位独立按键取值
******************************************/
uchar KEY_Scan_L(uchar row)
{
	uchar h=0,keynum=0;
	if(row >0 && row <5)
	{
		P3 = (~(0x1<<(4-row))<<4);
		#if IAP				//条件编译，如果使用比赛用的IAP芯片，就在最上边或者头文件加上#define IAP
			if(row == 2)
				P42 = 0;
			if(row == 4)
				P44 = 0;
		#endif				//标志结束#if			
	}

	P3 |= 0X0F;	  	//保持选取的列不变
	h = P3 & 0x0f;	//读取行值
	if(h != 0x0f)
	{
		switch(h)
		{
			case 0x0e:keynum = 1;break;
			case 0x0d:keynum = 2;break;
			case 0x0b:keynum = 3;break;
			case 0x07:keynum = 4;break;
		}	
	}
	return keynum;
}

/******************************************
*函数名：KEY_Scan
*输入：无
*返回：键值
*作用：4位独立按键取值
******************************************/
uchar KEY_Scan()
{
	 if(s4==0)
	 {
	 	KEY_delayms(5);
		if(s4==0)
			return 0;
	 }
	  if(s5==0)
	 {
	 	KEY_delayms(5);
		if(s5==0)
			return 1;
	 }
	  if(s6==0)
	 {
	 	KEY_delayms(5);
		if(s6==0)
			return 2;
	 }
	  if(s7==0)
	 {
	 	KEY_delayms(5);
		if(s7==0)
			return 3;
	 }
	 return 0xff;
}

/******************************************
*函数名：KEY_Scan16
*输入：无
*返回：键值
*作用：16位矩阵键盘取值（反转法）
******************************************/
uchar KEY_Scan16()
{
	uchar h,l;
	P3 = 0X0F;	  	//列为0
	h = P3 & 0x0f;	//读取行值
	if(h != 0x0f)
	{
		KEY_delayms(5);
		if(h != 0x0f)
		{
			h  = P3&0x0f;	//读取行值
			P3 = 0XF0;
			l  = P3&0XF0;
			return (h+l);
		}	
	}
	return 0xff;
}

/******************************************
*函数名：key_decoder_hex_to_int
*输入：键值（16进制）
*返回：键值（10进制）
*作用：16进制转10进制
******************************************/
int key_decoder_hex_to_int(unsigned char key_hex)
{
	int keynum = -1;
	switch(key_hex)
	{
		case 0x7e:keynum = 0;break;
		case 0xbe:keynum = 1;break;
		case 0xde:keynum = 2;break;
		case 0xee:keynum = 3;break;
		case 0x7d:keynum = 4;break;
		case 0xbd:keynum = 5;break;
		case 0xdd:keynum = 6;break;
		case 0xed:keynum = 7;break;
		case 0x7b:keynum = 8;break;
		case 0xbb:keynum = 9;break;
		case 0xdb:keynum = 10;break;
		case 0xeb:keynum = 11;break;
		case 0x77:keynum = 12;break;
		case 0xb7:keynum = 13;break;
		case 0xd7:keynum = 14;break;
		case 0xe7:keynum = 15;break;
		default:keynum=-1;break;
	}
	return keynum;
}

/******************************************
*函数名：KEY_Scan16_Return_Int
*输入：无
*返回：键值（10进制）
*作用：获取按键键值并转换为10进制键值
******************************************/
uint KEY_Scan16_Return_Int()
{
	uchar hh,ll;
	int keynums = -1;

	P3 = 0X0F;	  	//列为0
	hh = P3 & 0x0f;	//读取行值
	if(hh != 0x0f)
	{
		KEY_delayms(5);
		if(hh != 0x0f)
		{
			hh  = P3&0x0f;	//读取行值
			P3 = 0XF0;
			ll  = P3&0XF0;
			//return (hh+ll);
		}	
	}
//	return 0xff;	

	switch(hh+ll)
	{
		case 0x7e:keynums = 0;break;
		case 0xbe:keynums = 1;break;
		case 0xde:keynums = 2;break;
		case 0xee:keynums = 3;break;
		case 0x7d:keynums = 4;break;
		case 0xbd:keynums = 5;break;
		case 0xdd:keynums = 6;break;
		case 0xed:keynums = 7;break;
		case 0x7b:keynums = 8;break;
		case 0xbb:keynums = 9;break;
		case 0xdb:keynums = 10;break;
		case 0xeb:keynums = 11;break;
		case 0x77:keynums = 12;break;
		case 0xb7:keynums = 13;break;
		case 0xd7:keynums = 14;break;
		case 0xe7:keynums = 15;break;
		default:  keynums = 16;break;
	}
	return keynums;
}
