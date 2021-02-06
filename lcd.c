/******************************************
*文件名：LCD.C
*作用：实现与LCD显示相关的各个功能函数
*	   包括各类1602、12864、OLED等液晶显示屏
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/08/05
******************************************/

#include "lcd.h"
#include "common.h"
//===========================1602====================================//
//======8bit======//
/******************************************
*函数名：Lcd1602_ds18b20id_dsp
*输入：	*ds18b20id 	读取的DS18B20的ID的指针
		y			LCD第y行显示			
*返回：无
*作用：LCD1602显示读取的DS18B20 ID号
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
		ds_temp = ds18b20id[i]>>4;	//显示高四位
		if(ds_temp < 10)
		{
			Lcd1602_WriteDat(ds_temp + 0x30);				//  显示数字
		}
		else
		{
			Lcd1602_WriteDat(ds_temp + 0x37);	  			//  显示字母
		}
		ds_temp = ds18b20id[i]&0x0f;//显示低四位
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
*函数名：Lcd1602_Show_str
*输入： 参数1：x   0表示第一行，1表示第二行
*	   	参数2：y   0~15  表示显示的起始位置
*		参数3：*s  需要显示的数据 
*返回：无
*作用：在LCD1602的指定行列显示数据
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
*函数名：Lcd1602_WaitReady
*输入：无
*返回：无
*作用：检测LCD1602是否处于忙碌，并等待空闲
******************************************/
void Lcd1602_WaitReady()
{
    unsigned char sta;
	LCD1602_DAT = 0xff;
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    do {
        LCD1602_E = 1;
        sta = LCD1602_DAT;		// 一直在读取P0口的数据（状态）
        LCD1602_E = 0;
    } while (sta & 0x80);		//当P0口的bit7等于1表示液晶正忙，重复检测直到其等于0为止
}

/******************************************
*函数名：Lcd1602_WriteCmd
*输入：cmd 
*返回：无
*作用：给LCD1602写入命令
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
*函数名：Lcd1602_WriteDat
*输入：dat 
*返回：无
*作用：给LCD1602写入数据
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
*函数名：Lcd1602_SetCursor
*输入： 参数1：x   0表示第一行，1表示第二行
*	   	参数2：y   0~15  表示显示的起始位置
*返回：无
*作用：设置LCD1602的起始显示位置
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
*函数名：Lcd1602_ShowStr
*输入： 参数1：x     0表示第一行，1表示第二行
*	   	参数2：y     0~15  表示显示的起始位置
*		参数3：*str  需要显示的数据 
*		参数4：len	 显示数据的长度
*返回：无
*作用：在LCD1602的指定行列显示数据
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
*函数名：InitLcd1602
*输入：无
*返回：无
*作用：初始化LCD1602
******************************************/
void InitLcd1602()
{
    Lcd1602_WriteCmd(0x38); 
    Lcd1602_WriteCmd(0x0C);
    Lcd1602_WriteCmd(0x06);
    Lcd1602_WriteCmd(0x01);
}

/******************************************
*函数名：Lcd1602_cls
*输入：无
*返回：无
*作用：清屏
******************************************/
void Lcd1602_cls()  	   //clear screen
{
	Lcd1602_WriteCmd(0x01);  //清零字符显示
	Lcd1602_WriteCmd(0x01);  //清零字符显示
	Lcd1602_WriteCmd(0x01);  //清零字符显示	
}
//===========================12864====================================//
//======8bit======//

/* 12864液晶初始化函数 */
void InitLcd12864()
{
	LCD12864_PSB = 1;         //设置为8BIT并口工作模式
 	//字符模式初始化
	Lcd12864_WriteCmd(0x34);  //基本指令集
    Lcd12864_WriteCmd(0x30);  //基本指令集
	Lcd12864_WriteCmd(0x0C);  //开显示
    Lcd12864_WriteCmd(0x01);  //清零字符显示
}

/******************************************
*函数名：Lcd12864_WaitReady
*输入：无
*返回：无
*作用：检测LCD12864是否处于忙碌，并等待空闲
******************************************/
void Lcd12864_WaitReady()
{
    unsigned char sta;
	LCD12864_DAT = 0xff;
    LCD12864_RS = 0;
    LCD12864_RW = 1;
    do {
        LCD12864_E = 1;
        sta = LCD12864_DAT;		// 一直在读取P0口的数据（状态）
        LCD12864_E = 0;
    } while (sta & 0x80);		//当P0口的bit7等于1表示液晶正忙，重复检测直到其等于0为止
}

/******************************************
*函数名：Lcd12864_WriteCmd
*输入：cmd 
*返回：无
*作用：给LCD12864写入命令
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
*函数名：Lcd12864_WriteDat
*输入：dat 
*返回：无
*作用：给LCD12864写入数据
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
*函数名：Lcd12864_cls
*输入：无
*返回：无
*作用：清屏
******************************************/
void Lcd12864_cls()  	   //clear screen
{
	Lcd12864_WriteCmd(0x01);  //清零字符显示
	Lcd12864_WriteCmd(0x01);  //清零字符显示
	Lcd12864_WriteCmd(0x01);  //清零字符显示	
}


/******************************************
*函数名：Lcd12864_POS
*输入：x  往x轴偏移量   y  往y轴偏移量  
*返回：无
*作用：给LCD12864定位（x,y）开始输入
******************************************/
void Lcd12864_POS(unsigned char x, unsigned char y)
{
	//定位
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
*函数名：Lcd12864_Show_Str1
*输入：x  往x轴偏移量  （0~7）   
	   y  往y轴偏移量  （0~3）
	   *str	需要显示的字符串（包括汉字）  
*返回：无
*作用：LCD12864字符串形式显示
******************************************/
void Lcd12864_Show_Str1(unsigned char x, unsigned char y, unsigned char *str)
{
	//定位
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
*函数名：Lcd12864_Show_Str2
*输入：x  往x轴偏移量  （0~15）   
	   y  往y轴偏移量  （0~3）
	   *str	需要显示的字母  
*返回：无
*作用：LCD12864以字母的字符串形式显示（显示英文字符串专用）
******************************************/
void Lcd12864_Show_Str2(unsigned char x, unsigned char y, unsigned char *str)
{
	//定位
	Lcd12864_POS(x/2,y);	 //输入数字扩大2倍，定位缩小2分之1	
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
*函数名：Lcd12864_draw_point
*输入：x  往x轴偏移量  （0~15）   
	   y  往y轴偏移量  （0~3） 
*返回：无
*作用：画点
******************************************/
void Lcd12864_draw_point(unsigned char x, unsigned char y)
{
	//定位
	Lcd12864_POS(x/2,y);	 //输入数字扩大2倍，定位缩小2分之1	

	if(x%2 != 0)
	{
		x = x + 1;
		Lcd12864_WriteDat(' ');
	}
	Lcd12864_WriteDat('.');
}

/******************************************
*函数名： Lcd12864_draw_pixels  画像素点
*输入：x  往x轴偏移量  （0~127）   
	   y  往y轴偏移量  （0~63） 
*返回：无
*作用：画像素点
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
*函数名：Lcd12864_Show_Variate
*输入：x  往x轴偏移量  （0~15）   
	   y  往y轴偏移量  （0~3）
	   variate	需要显示的变量(小数精确到小数点后2位)
	   FOI  float or int  （float类型变量输入扩大100倍，即variate*100）  
*返回：无
*作用：LCD12864显示变量
******************************************/
void Lcd12864_Show_Variate(unsigned char x, unsigned char y, unsigned int variate, unsigned char FOI)
{
	//定位
	Lcd12864_POS(x/2,y);	 //输入数字扩大2倍，定位缩小2分之1	

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
*函数名：Lcd12864_ds18b20id_dsp
*输入：	
		*ds18b20id 	读取的DS18B20的ID的指针			
*返回：无
*作用：LCD1602显示读取的DS18B20 ID号
******************************************/
void Lcd12864_ds18b20id_dsp(unsigned char x, unsigned char y, unsigned char *ds18b20id)
{
	unsigned int i=0;
	unsigned char ds_tem;
	//定位
	Lcd12864_POS(x/2,y);	 //输入数字扩大2倍，定位缩小2分之1	

	if(x%2 != 0)
	{
		x = x + 1;
		Lcd12864_WriteDat(' ');
	}
	for(i=0;i<8;i++)
	{
		ds_tem = ds18b20id[i]>>4;	//显示高四位
		if(ds_tem < 10)
		{
			Lcd12864_WriteDat(ds_tem + 0x30);				//  显示数字
		}
		else
		{
			Lcd12864_WriteDat(ds_tem + 0x37);	  			//  显示字母
		}
		ds_tem = ds18b20id[i]&0x0f;//显示低四位
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