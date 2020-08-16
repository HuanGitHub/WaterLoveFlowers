/*------------------------------------------------------------------------------------
 * ��Ŀ����:

     TM1650оƬ��������v1.0

 * ��Ȩ��Ϣ:

     (c) �������, 2016.

 * ��ʷ�汾:
     2016-12-07:
       - ��ʼ�汾 V1.0.0;

 * ��ע:
     - ʹ��ǰ��Ҫ��TM1668.h�ļ�����ͨ�Žӿڡ���ʼ������
-------------------------------------------------------------------------------------*/

/************************����ͷ�ļ�***************************************************/

#include <reg52.h>
#include "TM1650.h"

code unsigned char DisplayAddressArray[4] = {DIG1_ADDRESS,DIG2_ADDRESS,DIG3_ADDRESS,DIG4_ADDRESS};

/*************************************************************************************
*��������void FrameStart_1650(void)
*��  �ܣ�֡��ʼ�ź�
*˵  ��������SCKΪ�ߣ�DIO��1����0Ϊ��ʼ�ź�
**************************************************************************************/
void FrameStart_1650(void)
{
	//��ȫ������
	DIO=1;
	SCK=1;		  
	//DIO����,Ȼ��SCKҲ���ͣ�Ϊ��������׼��
	DIO=0;
}

/*************************************************************************************
*��������void FrameStop_1650(void)
*��  �ܣ�֡�����ź�
*˵  ��������SCKΪ�ߣ�DIO��0����1Ϊ�����ź�
**************************************************************************************/
void FrameEnd_1650(void)
{
	//��ȫ������
	DIO=0;
	SCK=1;		  
	//DIO����,Ȼ��SCKҲ���ͣ�Ϊ��������׼��
	DIO=1;
}
/*************************************************************************************
*��������bit FrameAck_1650(void)
*��  �ܣ�֡Ack�ź�
*˵  ��������ֵΪ0��ʾͨ������������ֵΪ1��ʾͨ���쳣
**************************************************************************************/
bit FrameAck_1650(void)
{
	//���ж�DIO
	if(DIO==0)
	{
		SCK=1;
		SCK=0;
		return 0;
	}
	else
	{
		return 1;
	}
}
/*************************************************************************************
*��������void SendOneByte_TM1668(unsigned char byt)
*��  �ܣ�1668����һ���ֽڵ�����
*˵  ������λ�ȷ���
**************************************************************************************/
bit SendOneCouple_TM1650(unsigned char firstByte,unsigned char secondByte)
{
	unsigned char tmp;
	unsigned char i=0;
	bit err=0;			//����ʱ����1

	tmp=firstByte;
	//��ʼ�ź�
	FrameStart_1650();
	//�������ݣ��ȷ�firstByte���ٷ�secondByte��MSB��ǰ
	for(i=0;i<8;i++)
	{
		if(tmp&0x80)
		{
			DIO=1;
		}
		else
		{
			DIO=0;
		}
	
		SCK=0;
		SCK=1;
		SCK=0;
		
		tmp=tmp<<1;
	}
	//�ж�ACK
	if(FrameAck_1650()==1)
	{
		err=1;
	}
	//����secondByte
	tmp=secondByte;
	for(i=0;i<8;i++)
	{
		if(tmp&0x80)
		{
			DIO=1;
		}
		else
		{
			DIO=0;
		}
	
		SCK=0;
		SCK=1;
		SCK=0;
		
		tmp=tmp<<1;
	}
	//�ж�ACK
	if(FrameAck_1650()==1)
	{
		err=1;
	}
	//�����ź�
	FrameEnd_1650();
	//����ֵ
	return err;
}
/*************************************************************************************
*��������bit DisplayConfig_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode)
*��  �ܣ�1668����һ������
*˵  ������λ�ȷ���
**************************************************************************************/
bit DisplayConfig_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode,unsigned char on_or_off)
{
	unsigned char tmp = 0;
	bit err = 0;
	tmp = lightLevel | SegmentMode |  WorkMode | on_or_off;
	err = SendOneCouple_TM1650(CMD_SYSTEM_CONFIG,tmp);

	if(err == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}
/*************************************************************************************
*��������void DisplayOneDigi_TM1668(unsigned char addr,unsigned char cha)
*��  �ܣ��̶���ַģʽ��ָ��λ��ʾһ������
*˵  ����
*��  ����digi-��ʾ��λ����1-4�������ң���cha-����ʾ����
**************************************************************************************/
bit DisplayOneDigi_TM1650(unsigned char digi,unsigned char cha)
{
	unsigned char tmp = 0;
	bit err = 0;
	err = SendOneCouple_TM1650(DisplayAddressArray[digi-1],cha);
	return err;
}

/*************************************************************************************
*��������void DisplayOneDigi_TM1668(unsigned char addr,unsigned char cha)
*��  �ܣ��̶���ַģʽ��ָ��λ��ʾһ������
*˵  ����
*��  ����digi-��ʾ��λ����1-4�������ң���cha-����ʾ����
**************************************************************************************/
bit DisplayOFF_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode)
{
	unsigned char tmp = 0;
	bit err = 0;
	tmp = lightLevel | SegmentMode |  WorkMode | DISPLAY_OFF;
	err = SendOneCouple_TM1650(CMD_SYSTEM_CONFIG,tmp);

	if(err == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*************************************************************************************
*��������void DisplayOneDigi_TM1668(unsigned char addr,unsigned char cha)
*��  �ܣ��̶���ַģʽ��ָ��λ��ʾһ������
*˵  ����
*��  ����digi-��ʾ��λ����1-4�������ң���cha-����ʾ����
**************************************************************************************/
bit DisplayON_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode)
{
	unsigned char tmp = 0;
	bit err = 0;
	tmp = lightLevel | SegmentMode |  WorkMode | DISPLAY_ON;
	err = SendOneCouple_TM1650(CMD_SYSTEM_CONFIG,tmp);

	if(err == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/***************************************END******************************************/
