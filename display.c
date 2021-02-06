/******************************************
*�ļ�����DISPLAY.C
*���ã�ʵ�����������ʾ��صĸ������ܺ���
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/07/28
******************************************/

#include "display.h"

/******************************************
*��������dsp
*���룺��
*���أ���
*���ã��������ʾ����ʱ��ˢ��
******************************************/
void dsp()
{
   P0=0xff;//��Ӱ
   P2=P2&0x1f|0xe0;
   P2&=0x1f;

   P0=1<<dspcom;//λѡ
   P2=P2&0x1f|0xc0;
   P2&=0x1f;

   P0=tab[dspbuf[dspcom]];//��ѡ
   P2=P2&0x1f|0xe0;
   P2&=0x1f;
   
   if(++dspcom==8)
      dspcom=0;
}

/******************************************
*��������temp_dsp
*���룺	temp_int 	    DS18B20���ݵ���������
		temp_float		DS18B20���ݵ�С������
		flag			DS18B20��������
		FOI				ѡ���Ƿ���ʾС�����֣��ò����к궨�壩
*���أ���
*���ã���ʾ��ȡ��DS18B20�¶�
******************************************/
void temp_dsp(unsigned char temp_int, unsigned char temp_float, unsigned char flag, unsigned char FOI)
{
	if(flag == 0x0)
	{
		dspbuf[0]=flag%16;
		if(FOI == INT)
		{	
			dspbuf[3]=20;
			dspbuf[4]=temp_int/1000;
			dspbuf[5]=temp_int%1000/100;
			dspbuf[6]=temp_int%100/10;
			dspbuf[7]=temp_int%10;
		
		}
		else if(FOI == FLOAT)
		{	
			dspbuf[3]=20;
			dspbuf[4]=temp_int%100/10;
			dspbuf[5]=temp_int%10+10;
			dspbuf[6]=temp_float%100/10;
			dspbuf[7]=temp_float%10;
			
		}
	}
	else
	{
		dspbuf[0]=flag%16 + 12;
		if(FOI == INT)
		{
			dspbuf[3]=21;
			dspbuf[4]=temp_int/1000;
			dspbuf[5]=temp_int%1000/100;
			dspbuf[6]=temp_int%100/10;
			dspbuf[7]=temp_int%10;
		}
		else if(FOI == FLOAT)
		{
			dspbuf[3]=21;
			dspbuf[4]=temp_int%100/10;
			dspbuf[5]=temp_int%10+10;
			dspbuf[6]=temp_float%100/10;
			dspbuf[7]=temp_float%10;
		}
	
	}
//	
}

/******************************************
*��������ds18b20id_dsp
*���룺	ds18b20id 	��ȡ��DS18B20 ID
		i			�������ʾλ			
*���أ���
*���ã���ʾ��ȡ��DS18B20 ID��
******************************************/
void ds18b20id_dsp(unsigned char *ds18b20id,unsigned int i,unsigned int times)
{
//	unsigned char ds18b20id[8] = {0,0,0,0,0,0,0,0};

//	Read_ROM(&ds18b20id);
	unsigned char h,l,j;
	for(j=0+times*8;j<8+times*8;j++)
	{
		l = ds18b20id[j] & 0x0f;            //ȡ��4λ
		h = ds18b20id[j] & 0xf0;            //ȡ��4λ  
		h >>= 4;
		if( ( h >= 0x00 )&&( h <= 0x09 ) )
		{
			dspbuf[i]=h;	        
		}
	//	else 
	//	{ 
	//		dspbuf[i]=(h+22);
	//	}
		if( ( l >= 0x00 )&&( l <= 0x09 ) )
		{
			dspbuf[i+1]=l;	        
		}
	//	else 
	//	{ 
	//		dspbuf[i+1]=(l+22);
	//	}  
	}
}

/******************************************
*��������smgdsp
*���룺pwm
*���أ���
*���ã���ʾ��λ�ɵ�����
******************************************/
void smgdsp(unsigned char pwm)
{
	 dspbuf[5]=pwm/100;
	 dspbuf[6]=pwm%100/10;
	 dspbuf[7]=pwm%10;
}

/******************************************
*��������DS1302_dsp_time
*���룺*time
*���أ���
*���ã���ʾʵʱʱ�䣨hh-mm-ss��
******************************************/
void DS1302_dsp_time(unsigned char *time)
{
	dspbuf[7]=time[0]%16;
	dspbuf[6]=time[0]/16;
	dspbuf[5]=21;
	dspbuf[4]=time[1]%16;
	dspbuf[3]=time[1]/16;
	dspbuf[2]=21;
	dspbuf[1]=time[2]%16;
	dspbuf[0]=time[2]/16;
}

/******************************************
*��������DS1302_dsp_date
*���룺*time
*���أ���
*���ã���ʾʵʱ����(-   yy/- MM - dd)
******************************************/
void DS1302_dsp_date(unsigned char *time,unsigned char year)
{
	if(year == 1)
	{
		dspbuf[7]=time[6]%16;
		dspbuf[6]=time[6]/16;
		dspbuf[5]=0;
		dspbuf[4]=2;
		dspbuf[3]=20;
		dspbuf[2]=20;
		dspbuf[1]=20;
		dspbuf[0]=21;
	}
	else
	{
		dspbuf[7]=time[3]%16;
		dspbuf[6]=time[3]/16;
		dspbuf[5]=20;
		dspbuf[4]=21;
		dspbuf[3]=time[4]%16;
		dspbuf[2]=time[4]/16;
		dspbuf[1]=20;
		dspbuf[0]=21;
	}
}

/******************************************
*��������DS1302_dsp_week
*���룺*time
*���أ���
*���ã���ʾ��ǰ����(1~7��ʾ��һ������)
******************************************/
void DS1302_dsp_week(unsigned char *time)
{
	dspbuf[7]=time[5]%16;
	dspbuf[6]=time[5]/16;
	dspbuf[5]=20;
	dspbuf[4]=20;
	dspbuf[3]=21;
	dspbuf[2]=21;
	dspbuf[1]=20;
	dspbuf[0]=20;
}
