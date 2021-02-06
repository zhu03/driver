/*************************************************
*�ļ�����KEY.C
*���ã�ʵ�ֻ�ȡ������ֵ�ĸ������ܺ����͸�������
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/07/04
*************************************************/

#include "key.h"
/******************************************
*��������KEY_delayms
*���룺t   ʱ��
*���أ���
*���ã���ʱtMS
******************************************/
void KEY_delayms(int t)
{
   int i,j;
   for(i=500;i>0;i--)
   	 for(j=t;j>0;j--);

}

/******************************************
*��������KEY_Scan_L
*���룺row(1\2\3\4)
*���أ���ֵ
*���ã���ȡĳ��4λ��������ȡֵ
******************************************/
uchar KEY_Scan_L(uchar row)
{
	uchar h=0,keynum=0;
	if(row >0 && row <5)
	{
		P3 = (~(0x1<<(4-row))<<4);
		#if IAP				//�������룬���ʹ�ñ����õ�IAPоƬ���������ϱ߻���ͷ�ļ�����#define IAP
			if(row == 2)
				P42 = 0;
			if(row == 4)
				P44 = 0;
		#endif				//��־����#if			
	}

	P3 |= 0X0F;	  	//����ѡȡ���в���
	h = P3 & 0x0f;	//��ȡ��ֵ
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
*��������KEY_Scan
*���룺��
*���أ���ֵ
*���ã�4λ��������ȡֵ
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
*��������KEY_Scan16
*���룺��
*���أ���ֵ
*���ã�16λ�������ȡֵ����ת����
******************************************/
uchar KEY_Scan16()
{
	uchar h,l;
	P3 = 0X0F;	  	//��Ϊ0
	h = P3 & 0x0f;	//��ȡ��ֵ
	if(h != 0x0f)
	{
		KEY_delayms(5);
		if(h != 0x0f)
		{
			h  = P3&0x0f;	//��ȡ��ֵ
			P3 = 0XF0;
			l  = P3&0XF0;
			return (h+l);
		}	
	}
	return 0xff;
}

/******************************************
*��������key_decoder_hex_to_int
*���룺��ֵ��16���ƣ�
*���أ���ֵ��10���ƣ�
*���ã�16����ת10����
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
*��������KEY_Scan16_Return_Int
*���룺��
*���أ���ֵ��10���ƣ�
*���ã���ȡ������ֵ��ת��Ϊ10���Ƽ�ֵ
******************************************/
uint KEY_Scan16_Return_Int()
{
	uchar hh,ll;
	int keynums = -1;

	P3 = 0X0F;	  	//��Ϊ0
	hh = P3 & 0x0f;	//��ȡ��ֵ
	if(hh != 0x0f)
	{
		KEY_delayms(5);
		if(hh != 0x0f)
		{
			hh  = P3&0x0f;	//��ȡ��ֵ
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
