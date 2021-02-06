/*****************************************************
*�ļ�����dht11.h
*���ã�	������dht11�ĺ�����Ŷ���
*		������dht11��صĹ��ܺ���
*�汾��V 0.0.1
*���ߣ�����С��
*�޸����ڣ�2020/08/08
*****************************************************/
#ifndef _DHT11_H_
#define _DHT11_H_
/*************************����ͷ�ļ�**********************************/
#include "common.h"
/*************************���Ŷ���************************************/
sbit Data=P2^6;   //����������
/*************************�궨��**************************************/
/*************************��������**************************************/
/*************************��������**************************************/
void DHT11_delay_us(unsigned char n);
void DHT11_delay_ms(unsigned int z);
void DHT11_start();
unsigned char DHT11_rec_byte();
void DHT11_receive(unsigned char *rec_dat);

#endif