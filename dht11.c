/******************************************
*文件名：dht11.C
*作用：实现dht11的读取温湿度相关功能函数
*版本：V 0.0.1
*作者：程序小黑
*修改日期：2020/08/08
******************************************/

#include "dht11.h"

/******************************************
*函数名：DHT11_delay_us
*输入：定时值n
*返回：无
*作用：延时us
******************************************/
void DHT11_delay_us(unsigned char n)
{
    while(--n);
}

/******************************************
*函数名：DHT11_delay_ms
*输入：定时值z
*返回：无
*作用：延时ms
******************************************/
void DHT11_delay_ms(unsigned int z)
{
   uint i,j;
   for(i=z;i>0;i--)
      for(j=110;j>0;j--);
}

/******************************************
*函数名：DHT11_start
*输入：无
*返回：无
*作用：DHT11开始时序
******************************************/
void DHT11_start()
{
	Data=1;
	DHT11_delay_us(2);
	Data=0;
	DHT11_delay_ms(20);   //延时18ms以上
	Data=1;
	DHT11_delay_us(30);
}

/******************************************
*函数名：DHT11_rec_byte
*输入：无
*返回：dat 
*作用：DHT11接收一个字节
******************************************/
unsigned char DHT11_rec_byte()      //接收一个字节
{
	uchar i,dat=0;
	for(i=0;i<8;i++)    //从高到低依次接收8位数据
	{          
		while(!Data);   //等待50us低电平过去
		DHT11_delay_us(8);     //延时60us，如果还为高则数据为1，否则为0 
		dat<<=1;           //移位使正确接收8位数据，数据为0时直接移位
		if(Data==1)    //数据为1时，使dat加1来接收数据1
			dat+=1;
		while(Data);  //等待数据线拉低    
	}  
	return dat;
}

/******************************************
*函数名：DHT11_receive
*输入：*rec_dat   （用于获取温湿度值）
				湿度范围（20-90%RH，精度+-5%RH）
				温度范围（0~50℃，精度+-2℃）
*返回：无 
*作用：DHT11接收40位的数据
******************************************/
void DHT11_receive(unsigned char *rec_dat)      //接收40位的数据
{
    uchar R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise; 
    DHT11_start();
    if(Data==0)
    {
        while(Data==0);   //等待拉高     
        DHT11_delay_us(40);  //拉高后延时40us
        R_H=DHT11_rec_byte();    //接收湿度高八位  整数
        R_L=DHT11_rec_byte();    //接收湿度低八位  小数
        T_H=DHT11_rec_byte();    //接收温度高八位  整数
        T_L=DHT11_rec_byte();    //接收温度低八位  小数
        revise=DHT11_rec_byte(); //接收校正位 8位

        DHT11_delay_us(25);    //结束

        if(revise == (R_H+R_L+T_H+T_L))      //校正
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
        } 
        /*数据处理*/
        rec_dat[0]=RH;			//存放湿度整数位
		rec_dat[1]=RL;			//存放湿度小数位
        rec_dat[2]=TH;			//存放温度整数位
		rec_dat[3]=TL;			//存放温度小数位

    }
}