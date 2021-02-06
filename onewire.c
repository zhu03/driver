/******************************************
*文件名：ONEWIRE.C
*作用：实现DS18B20的读写功能函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/08/02
******************************************/

#include "onewire.h"

/******************************************
*函数名：Delay_OneWire
*输入：t		
*返回：无
*作用：温度传感器专用延时函数（tUS）
******************************************/
void Delay_OneWire(unsigned int t)
{
	while(t--);
}

/******************************************
*函数名：Init_DS18B20
*输入：无		
*返回：initflag
*作用：温度传感器初始化
******************************************/
bit Init_DS18B20(void)
{
	bit initflag = 0;
	DQ = 1;
	Delay_OneWire(12);
	DQ = 0;
	Delay_OneWire(80); 
	DQ = 1;
	Delay_OneWire(10); 
	initflag = DQ;    
	Delay_OneWire(20);
  
	return initflag;
}

/******************************************
*函数名：Write_DS18B20
*输入：dat		
*返回：无
*作用：写一个字节数据
******************************************/
void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;	  //发送第一位
		Delay_OneWire(5);
		DQ = 1;
		dat >>= 1;		  //右移一位，使得第二位变成第一位
	}
	Delay_OneWire(5);
}

/******************************************
*函数名：Read_DS18B20
*输入：无		
*返回：dat
*作用：读一个字节数据
******************************************/
unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		DQ = 0;
		dat >>= 1;
		DQ = 1;
		if(DQ)
		{
			dat |= 0x80;
		}
		else
		{
			dat |= 0x00;
		}	    
		Delay_OneWire(5);
	}
	return dat;
}

/******************************************
*函数名：*read_temp
*输入：无		
*返回：temp
*作用：读取温度传感器数据（整数、小数、正负）
******************************************/
unsigned char *read_temp()
{
	unsigned char low,high,temp_int,temp_float_t,temp_flag,temp_float;
	unsigned char temp[3]={0,0,0};
	Init_DS18B20();
	Write_DS18B20(0xcc);	//跳过ROM 
	Write_DS18B20(0x44);	//启动温度转换(启动18B20)
	Delay_OneWire(200);
	Init_DS18B20();
	Write_DS18B20(0xcc);   //跳过ROM  只有一个温度传感器，所以跳过ROM
	Write_DS18B20(0xbe);
	
	low=Read_DS18B20();
	high=Read_DS18B20();
	
	temp_int=(high<<4);
	temp_int|=(low>>4);
	
	temp_float_t = low & 0x0f;
	temp_float = (int)temp_float_t;
	temp_flag = ((high & 0xf0)>>4);
	
	temp[0] = temp_int;
	temp[1] = temp_float;
	temp[2] = temp_flag;
	
	return temp;
}

/******************************************
*函数名：Read_ROM
*输入：*ROM		
*返回：无
*作用：读取温度传感器数据（整数、小数、正负）
******************************************/
void Read_ROM(unsigned char *ROM)
{
	int i=0;
	Init_DS18B20();
	Write_DS18B20(0x33);
	for(i=0;i<8;i++)
	{
		ROM[i]=Read_DS18B20();	
	}
}

/******************************************
*函数名：*Match_ROM
*输入：*ROM		
*返回：temp
*作用：匹配并读取温度传感器数据（整数、小数、正负）
******************************************/
unsigned char *Match_ROM(unsigned char *ROM)
{
	int i=0;
	unsigned char low,high,temp_int,temp_float_t,temp_flag,temp_float;
	unsigned char temp[3]={0,0,0};

	Init_DS18B20();
	Write_DS18B20(0xcc);	//跳过ROM
	Write_DS18B20(0x44);	//启动温度转换(启动18B20)
	Init_DS18B20();
	Write_DS18B20(0x55);	//匹配ROM
	for(i=0;i<8;i++)
	{
		Write_DS18B20(*(ROM+i));		//写入ROM
	}
	Write_DS18B20(0xbe);	//开始读取
	
	low=Read_DS18B20();
	high=Read_DS18B20();
	
	temp_int=(high<<4);
	temp_int|=(low>>4);
	
	temp_float_t = low & 0x0f;
	temp_float = (int)temp_float_t;
	temp_flag = ((high & 0xf0)>>4);
	
	temp[0] = temp_int;
	temp[1] = temp_float;
	temp[2] = temp_flag;
	
	return temp;

}

/******************************************
*函数名：get_Temp_HL
*输入：*limit		
*返回：无
*作用：读取温度上限和下限
******************************************/
void get_Temp_HL(unsigned char *limit)
{
	Init_DS18B20();
	Write_DS18B20(0xcc);	//跳过ROM
	Write_DS18B20(0x44);	//启动温度转换(启动18B20)
	Init_DS18B20();
	Write_DS18B20(0xcc);	//匹配ROM
	Write_DS18B20(0xbe);	//开始读取
	*limit=Read_DS18B20();	  //L
	*(limit+1)=Read_DS18B20();	  //H
	*(limit+1)=Read_DS18B20();		  //H
	*limit=Read_DS18B20();		  //L

}

/******************************************
*函数名：Temp_HL_CONF
*输入：	TH  		上限
*		TL			下限
*		precision	精度					
*返回：无
*作用：配置温度上限、下限和精度
******************************************/
void Temp_HL_CONF(char TH,char TL,char precision)
{
	char h,l;
	if(TL>TH)
	{
		//交换TH和TL的值		
		TH = TH + TL;
		TL = TH - TL;
		TH = TH - TL;
	}
	if(TH >= 0)
	{
		h = TH/16;
		l = TH%16;
		TH = (h<<4)|l;	
	}	
	else
	{
		h = (256 + TH)/16;
		l = (256 + TH)%16;
		TH = (h<<4)|l;
	}
	if(TL >= 0)
	{
		h = TL/16;
		l = TL%16;
		TL = (h<<4)|l;	
	}	
	else
	{
		h = (256 + TL)/16;
		l = (256 + TL)%16;
		TL = (h<<4)|l;
	}
	Init_DS18B20();
	Write_DS18B20(0xcc);	//跳过ROM
	Write_DS18B20(0x44);	//启动温度转换(启动18B20)
	Init_DS18B20();
	Write_DS18B20(0xcc);	//跳过ROM
	Write_DS18B20(0x4e);	//将数据写入暂存器的TH、TL字节
	Write_DS18B20(TH);	    //TH
	Write_DS18B20(TL);	    //TL
	Write_DS18B20(precision);	    //精度
	Init_DS18B20();
	Write_DS18B20(0xcc);	//跳过ROM
	Write_DS18B20(0x48);	//把暂存器的TH、TL字节写到E2PROM中
	Write_DS18B20(0xB8);	//把E2PROM中的TH、TL字节写到暂存器TH、TL字节

}

/******************************************
*函数名：rd_temperature
*输入：无					
*返回：temp
*作用：读取温度（整数）
******************************************/
unsigned char rd_temperature(void)	   //DS18B20温度采集程序：整数
{
    unsigned char low,high;
  	char temp;
  
  	Init_DS18B20();
  	Write_DS18B20(0xCC);
  	Write_DS18B20(0x44); //启动温度转换
  	Delay_OneWire(200);

  	Init_DS18B20();
  	Write_DS18B20(0xCC);
  	Write_DS18B20(0xBE); //读取寄存器

  	low = Read_DS18B20(); //低字节
  	high = Read_DS18B20(); //高字节
  
  	temp = high<<4;
  	temp |= (low>>4);
  
  	return temp;
}
