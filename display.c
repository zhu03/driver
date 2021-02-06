/******************************************
*文件名：DISPLAY.C
*作用：实现与数码管显示相关的各个功能函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/07/28
******************************************/

#include "display.h"

/******************************************
*函数名：dsp
*输入：无
*返回：无
*作用：数码管显示，定时器刷新
******************************************/
void dsp()
{
   P0=0xff;//消影
   P2=P2&0x1f|0xe0;
   P2&=0x1f;

   P0=1<<dspcom;//位选
   P2=P2&0x1f|0xc0;
   P2&=0x1f;

   P0=tab[dspbuf[dspcom]];//段选
   P2=P2&0x1f|0xe0;
   P2&=0x1f;
   
   if(++dspcom==8)
      dspcom=0;
}

/******************************************
*函数名：temp_dsp
*输入：	temp_int 	    DS18B20数据的整数部分
		temp_float		DS18B20数据的小数部分
		flag			DS18B20数据正负
		FOI				选择是否显示小数部分（该参数有宏定义）
*返回：无
*作用：显示读取的DS18B20温度
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
*函数名：ds18b20id_dsp
*输入：	ds18b20id 	读取的DS18B20 ID
		i			数码管显示位			
*返回：无
*作用：显示读取的DS18B20 ID号
******************************************/
void ds18b20id_dsp(unsigned char *ds18b20id,unsigned int i,unsigned int times)
{
//	unsigned char ds18b20id[8] = {0,0,0,0,0,0,0,0};

//	Read_ROM(&ds18b20id);
	unsigned char h,l,j;
	for(j=0+times*8;j<8+times*8;j++)
	{
		l = ds18b20id[j] & 0x0f;            //取低4位
		h = ds18b20id[j] & 0xf0;            //取高4位  
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
*函数名：smgdsp
*输入：pwm
*返回：无
*作用：显示三位可调变量
******************************************/
void smgdsp(unsigned char pwm)
{
	 dspbuf[5]=pwm/100;
	 dspbuf[6]=pwm%100/10;
	 dspbuf[7]=pwm%10;
}

/******************************************
*函数名：DS1302_dsp_time
*输入：*time
*返回：无
*作用：显示实时时间（hh-mm-ss）
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
*函数名：DS1302_dsp_date
*输入：*time
*返回：无
*作用：显示实时日期(-   yy/- MM - dd)
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
*函数名：DS1302_dsp_week
*输入：*time
*返回：无
*作用：显示当前星期(1~7表示周一到周日)
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
