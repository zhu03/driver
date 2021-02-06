/******************************************
*�ļ�����UART.C
*���ã�ʵ�ִ����շ�����ʼ���ȹ��ܺ���
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/08/
******************************************/
#include "UART.H"

//void Init_UART(void)
//{	
//	SCON = 0x50;
//	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
//	TL1 = 0xFD;			//�趨��ʱ��ֵ
//	TH1 = 0xFD;			//�趨��ʱ����װֵ
//	TR1=1;				//�򿪼�����
//}

//void UartInit(void)		//9600bps@12.000MHz
//{
//	PCON = 0x00;		//SMOD=0,�����ʲ�����
//	SCON = 0x50;		//8λ����,�ɱ䲨����,��ֹ���ڽ���
//	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
//	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
//	TL1 = 0xFD;			//�趨��ʱ��ֵ
//	TH1 = 0xFD;			//�趨��ʱ����װֵ
//	ES  = 1;			//�򿪴����ж�
//	EA  = 1;			//�����ж�
//	TR1 = 1;			//������ʱ��1
//}


void UART_Init()
{   

	TMOD|=0x20;		 //������ʱ������
	TH1=0xf3;		 //���ó�ֵ 2400=(2��SMOD�η�/32)*��TI����ʣ�=��1/32��*11059200/(256-X)*12
	TL1=0xf3;		 //9600������̫�ߣ�����ѡ����������͵Ĳ�����2400
	TR1=1;			 //������ʱ��1
	SM0=0;			 //���ô��пڹ�����ʽ
	SM1=1;
	REN=1;         	//�������н���λ
	EA=1;          	//�������ж�
	ES=1;			//���������ж�
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