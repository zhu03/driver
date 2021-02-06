/******************************************
*�ļ�����ONEWIRE.C
*���ã�ʵ��DS18B20�Ķ�д���ܺ���
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/08/02
******************************************/

#include "onewire.h"

/******************************************
*��������Delay_OneWire
*���룺t		
*���أ���
*���ã��¶ȴ�����ר����ʱ������tUS��
******************************************/
void Delay_OneWire(unsigned int t)
{
	while(t--);
}

/******************************************
*��������Init_DS18B20
*���룺��		
*���أ�initflag
*���ã��¶ȴ�������ʼ��
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
*��������Write_DS18B20
*���룺dat		
*���أ���
*���ã�дһ���ֽ�����
******************************************/
void Write_DS18B20(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ = 0;
		DQ = dat&0x01;	  //���͵�һλ
		Delay_OneWire(5);
		DQ = 1;
		dat >>= 1;		  //����һλ��ʹ�õڶ�λ��ɵ�һλ
	}
	Delay_OneWire(5);
}

/******************************************
*��������Read_DS18B20
*���룺��		
*���أ�dat
*���ã���һ���ֽ�����
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
*��������*read_temp
*���룺��		
*���أ�temp
*���ã���ȡ�¶ȴ��������ݣ�������С����������
******************************************/
unsigned char *read_temp()
{
	unsigned char low,high,temp_int,temp_float_t,temp_flag,temp_float;
	unsigned char temp[3]={0,0,0};
	Init_DS18B20();
	Write_DS18B20(0xcc);	//����ROM 
	Write_DS18B20(0x44);	//�����¶�ת��(����18B20)
	Delay_OneWire(200);
	Init_DS18B20();
	Write_DS18B20(0xcc);   //����ROM  ֻ��һ���¶ȴ���������������ROM
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
*��������Read_ROM
*���룺*ROM		
*���أ���
*���ã���ȡ�¶ȴ��������ݣ�������С����������
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
*��������*Match_ROM
*���룺*ROM		
*���أ�temp
*���ã�ƥ�䲢��ȡ�¶ȴ��������ݣ�������С����������
******************************************/
unsigned char *Match_ROM(unsigned char *ROM)
{
	int i=0;
	unsigned char low,high,temp_int,temp_float_t,temp_flag,temp_float;
	unsigned char temp[3]={0,0,0};

	Init_DS18B20();
	Write_DS18B20(0xcc);	//����ROM
	Write_DS18B20(0x44);	//�����¶�ת��(����18B20)
	Init_DS18B20();
	Write_DS18B20(0x55);	//ƥ��ROM
	for(i=0;i<8;i++)
	{
		Write_DS18B20(*(ROM+i));		//д��ROM
	}
	Write_DS18B20(0xbe);	//��ʼ��ȡ
	
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
*��������get_Temp_HL
*���룺*limit		
*���أ���
*���ã���ȡ�¶����޺�����
******************************************/
void get_Temp_HL(unsigned char *limit)
{
	Init_DS18B20();
	Write_DS18B20(0xcc);	//����ROM
	Write_DS18B20(0x44);	//�����¶�ת��(����18B20)
	Init_DS18B20();
	Write_DS18B20(0xcc);	//ƥ��ROM
	Write_DS18B20(0xbe);	//��ʼ��ȡ
	*limit=Read_DS18B20();	  //L
	*(limit+1)=Read_DS18B20();	  //H
	*(limit+1)=Read_DS18B20();		  //H
	*limit=Read_DS18B20();		  //L

}

/******************************************
*��������Temp_HL_CONF
*���룺	TH  		����
*		TL			����
*		precision	����					
*���أ���
*���ã������¶����ޡ����޺;���
******************************************/
void Temp_HL_CONF(char TH,char TL,char precision)
{
	char h,l;
	if(TL>TH)
	{
		//����TH��TL��ֵ		
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
	Write_DS18B20(0xcc);	//����ROM
	Write_DS18B20(0x44);	//�����¶�ת��(����18B20)
	Init_DS18B20();
	Write_DS18B20(0xcc);	//����ROM
	Write_DS18B20(0x4e);	//������д���ݴ�����TH��TL�ֽ�
	Write_DS18B20(TH);	    //TH
	Write_DS18B20(TL);	    //TL
	Write_DS18B20(precision);	    //����
	Init_DS18B20();
	Write_DS18B20(0xcc);	//����ROM
	Write_DS18B20(0x48);	//���ݴ�����TH��TL�ֽ�д��E2PROM��
	Write_DS18B20(0xB8);	//��E2PROM�е�TH��TL�ֽ�д���ݴ���TH��TL�ֽ�

}

/******************************************
*��������rd_temperature
*���룺��					
*���أ�temp
*���ã���ȡ�¶ȣ�������
******************************************/
unsigned char rd_temperature(void)	   //DS18B20�¶Ȳɼ���������
{
    unsigned char low,high;
  	char temp;
  
  	Init_DS18B20();
  	Write_DS18B20(0xCC);
  	Write_DS18B20(0x44); //�����¶�ת��
  	Delay_OneWire(200);

  	Init_DS18B20();
  	Write_DS18B20(0xCC);
  	Write_DS18B20(0xBE); //��ȡ�Ĵ���

  	low = Read_DS18B20(); //���ֽ�
  	high = Read_DS18B20(); //���ֽ�
  
  	temp = high<<4;
  	temp |= (low>>4);
  
  	return temp;
}
