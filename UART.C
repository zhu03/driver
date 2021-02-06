/******************************************
*文件名：UART.C
*作用：实现串口收发、初始化等功能函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/08/
******************************************/
#include "UART.H"

//void Init_UART(void)
//{	
//	SCON = 0x50;
//	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
//	TL1 = 0xFD;			//设定定时初值
//	TH1 = 0xFD;			//设定定时器重装值
//	TR1=1;				//打开计数器
//}

//void UartInit(void)		//9600bps@12.000MHz
//{
//	PCON = 0x00;		//SMOD=0,波特率不倍速
//	SCON = 0x50;		//8位数据,可变波特率,禁止串口接收
//	TMOD &= 0x0F;		//清除定时器1模式位
//	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
//	TL1 = 0xFD;			//设定定时初值
//	TH1 = 0xFD;			//设定定时器重装值
//	ES  = 1;			//打开串口中断
//	EA  = 1;			//打开总中断
//	TR1 = 1;			//启动定时器1
//}


void UART_Init()
{   

	TMOD|=0x20;		 //用来定时器设置
	TH1=0xf3;		 //设置初值 2400=(2的SMOD次方/32)*（TI溢出率）=（1/32）*11059200/(256-X)*12
	TL1=0xf3;		 //9600误码率太高，所以选用误码率最低的波特率2400
	TR1=1;			 //开启定时器1
	SM0=0;			 //设置串行口工作方式
	SM1=1;
	REN=1;         	//允许串行接收位
	EA=1;          	//开启总中断
	ES=1;			//开启串口中断
}

void Uart_Send_Byte(uint8 dat)
{
	SBUF = dat;
	while(!TI);
	TI = 0;
}

uint8 Uart_Receive_Byte(void)
{
	uint8 dat;	
	while(!RI);
	RI = 0;
	dat = SBUF;
	return dat;
}

void Uart_Send_String(uint8 *buf)
{
	ES = 0;
	while(*buf != '\0')
	{
		Uart_Send_Byte(*buf++);
	} 
	ES = 1;
}


void Uart_Receive_String(uint8 *buf)
{	
	ES = 0;
	while(*buf != '\0')
	{	  
		if(RI == 1)
		{
			RI = 0;
			*buf = SBUF;
			buf++;
		}	
	}
   	ES = 1;
}
