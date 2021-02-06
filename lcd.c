/******************************************
*�ļ�����LCD.C
*���ã�ʵ����LCD��ʾ��صĸ������ܺ���
*	   ��������1602��12864��OLED��Һ����ʾ��
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/08/05
******************************************/

#include "lcd.h"
#include "common.h"
//===========================1602====================================//
//======8bit======//
/******************************************
*��������Lcd1602_ds18b20id_dsp
*���룺	*ds18b20id 	��ȡ��DS18B20��ID��ָ��
		y			LCD��y����ʾ			
*���أ���
*���ã�LCD1602��ʾ��ȡ��DS18B20 ID��
******************************************/
void Lcd1602_ds18b20id_dsp(unsigned char *ds18b20id, unsigned int y)
{
	unsigned int i=0;
	unsigned char ds_temp,cmd = 0x80;
	if(y)
		cmd = 0xc0;
	else
		cmd = 0x80;
	Lcd1602_WriteCmd(cmd);
	for(i=0;i<8;i++)
	{
		ds_temp = ds18b20id[i]>>4;	//��ʾ����λ
		if(ds_temp < 10)
		{
			Lcd1602_WriteDat(ds_temp + 0x30);				//  ��ʾ����
		}
		else
		{
			Lcd1602_WriteDat(ds_temp + 0x37);	  			//  ��ʾ��ĸ
		}
		ds_temp = ds18b20id[i]&0x0f;//��ʾ����λ
		if(ds_temp < 10)
		{
			Lcd1602_WriteDat(ds_temp + 0x30);	
		}
		else
		{
			Lcd1602_WriteDat(ds_temp + 0x37);
		}	
	}

}
/******************************************
*��������Lcd1602_Show_str
*���룺 ����1��x   0��ʾ��һ�У�1��ʾ�ڶ���
*	   	����2��y   0~15  ��ʾ��ʾ����ʼλ��
*		����3��*s  ��Ҫ��ʾ������ 
*���أ���
*���ã���LCD1602��ָ��������ʾ����
******************************************/
void Lcd1602_Show_str(unsigned char x, unsigned char y, unsigned char *s)
{
	if((x > 1) || (y > 15))
	{
		return ;
	}
	if(0 == x)
	{
		Lcd1602_WriteCmd(y + 0x80);
			 
	}
	else if(1 == x)
	{
		Lcd1602_WriteCmd(y + 0xc0);
	}
	while(*s)
	{
			
		Lcd1602_WriteDat(*s);
		s++;	
	}
}
/******************************************
*��������Lcd1602_WaitReady
*���룺��
*���أ���
*���ã����LCD1602�Ƿ���æµ�����ȴ�����
******************************************/
void Lcd1602_WaitReady()
{
    unsigned char sta;
	LCD1602_DAT = 0xff;
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    do {
        LCD1602_E = 1;
        sta = LCD1602_DAT;		// һֱ�ڶ�ȡP0�ڵ����ݣ�״̬��
        LCD1602_E = 0;
    } while (sta & 0x80);		//��P0�ڵ�bit7����1��ʾҺ����æ���ظ����ֱ�������0Ϊֹ
}

/******************************************
*��������Lcd1602_WriteCmd
*���룺cmd 
*���أ���
*���ã���LCD1602д������
******************************************/
void Lcd1602_WriteCmd(unsigned char cmd)
{
    Lcd1602_WaitReady();
    LCD1602_RS = 0;
    LCD1602_RW = 0;
    LCD1602_DAT = cmd;
    LCD1602_E  = 1;
    LCD1602_E  = 0;
}

/******************************************
*��������Lcd1602_WriteDat
*���룺dat 
*���أ���
*���ã���LCD1602д������
******************************************/
void Lcd1602_WriteDat(unsigned char dat)
{
    Lcd1602_WaitReady();
    LCD1602_RS = 1;
    LCD1602_RW = 0;
    LCD1602_DAT = dat;
    LCD1602_E  = 1;
    LCD1602_E  = 0;
}

/******************************************
*��������Lcd1602_SetCursor
*���룺 ����1��x   0��ʾ��һ�У�1��ʾ�ڶ���
*	   	����2��y   0~15  ��ʾ��ʾ����ʼλ��
*���أ���
*���ã�����LCD1602����ʼ��ʾλ��
******************************************/
void Lcd1602_SetCursor(unsigned char x, unsigned char y)
{
    unsigned char addr;
    
    if (y == 0) 
        addr = 0x00 + x;  
    else
        addr = 0x40 + x;  
    Lcd1602_WriteCmd(addr | 0x80); 
}

/******************************************
*��������Lcd1602_ShowStr
*���룺 ����1��x     0��ʾ��һ�У�1��ʾ�ڶ���
*	   	����2��y     0~15  ��ʾ��ʾ����ʼλ��
*		����3��*str  ��Ҫ��ʾ������ 
*		����4��len	 ��ʾ���ݵĳ���
*���أ���
*���ã���LCD1602��ָ��������ʾ����
******************************************/
void Lcd1602_ShowStr(unsigned char x, unsigned char y, unsigned char *str, unsigned char len)
{
    Lcd1602_SetCursor(x, y);
    while (len--)      
    {
        Lcd1602_WriteDat(*str++); 
    }
}

/******************************************
*��������InitLcd1602
*���룺��
*���أ���
*���ã���ʼ��LCD1602
******************************************/
void InitLcd1602()
{
    Lcd1602_WriteCmd(0x38); 
    Lcd1602_WriteCmd(0x0C);
    Lcd1602_WriteCmd(0x06);
    Lcd1602_WriteCmd(0x01);
}

/******************************************
*��������Lcd1602_cls
*���룺��
*���أ���
*���ã�����
******************************************/
void Lcd1602_cls()  	   //clear screen
{
	Lcd1602_WriteCmd(0x01);  //�����ַ���ʾ
	Lcd1602_WriteCmd(0x01);  //�����ַ���ʾ
	Lcd1602_WriteCmd(0x01);  //�����ַ���ʾ	
}
//===========================12864====================================//
//======8bit======//

/* 12864Һ����ʼ������ */
void InitLcd12864()
{
	LCD12864_PSB = 1;         //����Ϊ8BIT���ڹ���ģʽ
 	//�ַ�ģʽ��ʼ��
	Lcd12864_WriteCmd(0x34);  //����ָ�
    Lcd12864_WriteCmd(0x30);  //����ָ�
	Lcd12864_WriteCmd(0x0C);  //����ʾ
    Lcd12864_WriteCmd(0x01);  //�����ַ���ʾ
}

/******************************************
*��������Lcd12864_WaitReady
*���룺��
*���أ���
*���ã����LCD12864�Ƿ���æµ�����ȴ�����
******************************************/
void Lcd12864_WaitReady()
{
    unsigned char sta;
	LCD12864_DAT = 0xff;
    LCD12864_RS = 0;
    LCD12864_RW = 1;
    do {
        LCD12864_E = 1;
        sta = LCD12864_DAT;		// һֱ�ڶ�ȡP0�ڵ����ݣ�״̬��
        LCD12864_E = 0;
    } while (sta & 0x80);		//��P0�ڵ�bit7����1��ʾҺ����æ���ظ����ֱ�������0Ϊֹ
}

/******************************************
*��������Lcd12864_WriteCmd
*���룺cmd 
*���أ���
*���ã���LCD12864д������
******************************************/
void Lcd12864_WriteCmd(unsigned char cmd)
{
    Lcd12864_WaitReady();
    LCD12864_RS = 0;
    LCD12864_RW = 0;
    LCD12864_DAT = cmd;
    LCD12864_E  = 1;
    LCD12864_E  = 0;
}

/******************************************
*��������Lcd12864_WriteDat
*���룺dat 
*���أ���
*���ã���LCD12864д������
******************************************/
void Lcd12864_WriteDat(unsigned char dat)
{
    Lcd12864_WaitReady();
    LCD12864_RS = 1;
    LCD12864_RW = 0;
    LCD12864_DAT = dat;
    LCD12864_E  = 1;
    LCD12864_E  = 0;
}


/******************************************
*��������Lcd12864_cls
*���룺��
*���أ���
*���ã�����
******************************************/
void Lcd12864_cls()  	   //clear screen
{
	Lcd12864_WriteCmd(0x01);  //�����ַ���ʾ
	Lcd12864_WriteCmd(0x01);  //�����ַ���ʾ
	Lcd12864_WriteCmd(0x01);  //�����ַ���ʾ	
}


/******************************************
*��������Lcd12864_POS
*���룺x  ��x��ƫ����   y  ��y��ƫ����  
*���أ���
*���ã���LCD12864��λ��x,y����ʼ����
******************************************/
void Lcd12864_POS(unsigned char x, unsigned char y)
{
	//��λ
	switch(y)
	{
		case 0:x += 0x80;break;
		case 1:x += 0x90;break;
		case 2:x += 0x88;break;
		case 3:x += 0x98;break;
		default:break;
	}
	Lcd12864_WriteCmd(x);
}


/******************************************
*��������Lcd12864_Show_Str1
*���룺x  ��x��ƫ����  ��0~7��   
	   y  ��y��ƫ����  ��0~3��
	   *str	��Ҫ��ʾ���ַ������������֣�  
*���أ���
*���ã�LCD12864�ַ�����ʽ��ʾ
******************************************/
void Lcd12864_Show_Str1(unsigned char x, unsigned char y, unsigned char *str)
{
	//��λ
	switch(y)
	{
		case 0:x += 0x80;break;
		case 1:x += 0x90;break;
		case 2:x += 0x88;break;
		case 3:x += 0x98;break;
		default:break;
	}
	Lcd12864_WriteCmd(x);	
	while(*str!='\0')
	{ 
		Lcd12864_WriteDat(*str);
		str++;
	}

}
/******************************************
*��������Lcd12864_Show_Str2
*���룺x  ��x��ƫ����  ��0~15��   
	   y  ��y��ƫ����  ��0~3��
	   *str	��Ҫ��ʾ����ĸ  
*���أ���
*���ã�LCD12864����ĸ���ַ�����ʽ��ʾ����ʾӢ���ַ���ר�ã�
******************************************/
void Lcd12864_Show_Str2(unsigned char x, unsigned char y, unsigned char *str)
{
	//��λ
	Lcd12864_POS(x/2,y);	 //������������2������λ��С2��֮1	
	while(*str != '\0')
	{
		if(x%2 != 0)
		{
			x = x + 1;
			Lcd12864_WriteDat(' ');
		}
		Lcd12864_WriteDat(*str);
		str++;
	}
}

/******************************************
*��������Lcd12864_draw_point
*���룺x  ��x��ƫ����  ��0~15��   
	   y  ��y��ƫ����  ��0~3�� 
*���أ���
*���ã�����
******************************************/
void Lcd12864_draw_point(unsigned char x, unsigned char y)
{
	//��λ
	Lcd12864_POS(x/2,y);	 //������������2������λ��С2��֮1	

	if(x%2 != 0)
	{
		x = x + 1;
		Lcd12864_WriteDat(' ');
	}
	Lcd12864_WriteDat('.');
}

/******************************************
*�������� Lcd12864_draw_pixels  �����ص�
*���룺x  ��x��ƫ����  ��0~127��   
	   y  ��y��ƫ����  ��0~63�� 
*���أ���
*���ã������ص�
******************************************/
void Lcd12864_draw_pixels(unsigned char x, unsigned char y)
{
//	unsigned char temph, templ;//
	unsigned char x_byte,x_bit;//
	unsigned char y_byte,y_bit;//
	
	Lcd12864_WriteCmd(0x34);//
	Lcd12864_WriteCmd(0x36);//
	x_byte = x >> 4;//
	x_bit = x&0x0f;//
	y_byte = y/32;//
	y_bit = y%32;//
	Lcd12864_WriteCmd(0x80+y_bit);//
	Lcd12864_WriteCmd(0x80+x_byte+8*y_byte);//

				

}

/******************************************
*��������Lcd12864_Show_Variate
*���룺x  ��x��ƫ����  ��0~15��   
	   y  ��y��ƫ����  ��0~3��
	   variate	��Ҫ��ʾ�ı���(С����ȷ��С�����2λ)
	   FOI  float or int  ��float���ͱ�����������100������variate*100��  
*���أ���
*���ã�LCD12864��ʾ����
******************************************/
void Lcd12864_Show_Variate(unsigned char x, unsigned char y, unsigned int variate, unsigned char FOI)
{
	//��λ
	Lcd12864_POS(x/2,y);	 //������������2������λ��С2��֮1	

	if(x%2 != 0)
	{
		x = x + 1;
		Lcd12864_WriteDat(' ');
	}
	if(FOI == INT)
	{
//		Lcd12864_WriteDat(variate/10000 + 0x30);
//		Lcd12864_WriteDat(variate%10000/1000 + 0x30);
//		Lcd12864_WriteDat(variate%1000/100 + 0x30);
		Lcd12864_WriteDat(variate/10 + 0x30);
		Lcd12864_WriteDat(variate%10 + 0x30);
	}
	else if(FOI == FLOAT)
	{
		Lcd12864_WriteDat(variate/100000 + 0x30);
		Lcd12864_WriteDat(variate%100000/10000 + 0x30);
		Lcd12864_WriteDat(variate%10000/1000 + 0x30);
		Lcd12864_WriteDat(variate%1000/100 + 0x30);
		Lcd12864_WriteDat('.');
		Lcd12864_WriteDat(variate%100/10 + 0x30);
		Lcd12864_WriteDat(variate%10 + 0x30);
	}
}

/******************************************
*��������Lcd12864_ds18b20id_dsp
*���룺	
		*ds18b20id 	��ȡ��DS18B20��ID��ָ��			
*���أ���
*���ã�LCD1602��ʾ��ȡ��DS18B20 ID��
******************************************/
void Lcd12864_ds18b20id_dsp(unsigned char x, unsigned char y, unsigned char *ds18b20id)
{
	unsigned int i=0;
	unsigned char ds_tem;
	//��λ
	Lcd12864_POS(x/2,y);	 //������������2������λ��С2��֮1	

	if(x%2 != 0)
	{
		x = x + 1;
		Lcd12864_WriteDat(' ');
	}
	for(i=0;i<8;i++)
	{
		ds_tem = ds18b20id[i]>>4;	//��ʾ����λ
		if(ds_tem < 10)
		{
			Lcd12864_WriteDat(ds_tem + 0x30);				//  ��ʾ����
		}
		else
		{
			Lcd12864_WriteDat(ds_tem + 0x37);	  			//  ��ʾ��ĸ
		}
		ds_tem = ds18b20id[i]&0x0f;//��ʾ����λ
		if(ds_tem < 10)
		{
			Lcd12864_WriteDat(ds_tem + 0x30);	
		}
		else
		{	
			Lcd12864_WriteDat(ds_tem + 0x37);
		}	
	}

}