/*------------------------------------------------------------------------------------
 * ��Ŀ����:

     TM1650����ģ����Գ���

 * ��Ȩ��Ϣ:

     (c) �������, 2016.

 * ��ʷ�汾:
 	 
     2016-5-11:
       - ��ʼ�汾 V1.0.0;

 * ����˵��:

     - ����ǰ�������Ӳ����������MCU��ģ���ͨѶ�ӿ�
-------------------------------------------------------------------------------------*/
/************************����ͷ�ļ�***************************************************/

#include<reg52.h>
#include<TM1650.h>

/****************ִ��оƬ��ʼ������ʱ���Դ˴����������������оƬ*********************/
#define ON	DISPLAY_ON
#define OFF	DISPLAY_OFF
unsigned char  LightLevel =	LV1;				   //��ʾ�������ã�����ȡֵ��Χ����оƬ�������塿				
unsigned char  WorkMode	 =	NORMAL_MODE;		   //����ģʽ���壬ȡֵ��Χ����оƬ�������塿
//��ʾ��ģʽ���ã������֣�8����ʾģʽ��7����ʾģʽ��ȡֵ��Χ����оƬ�������塿��
#define SegmentMode		_8_SEGMENT_MODE	

/*******************************ȫ�ֱ���**********************************************/
//�˶��������ʾ��ÿһ��
unsigned char code Seg_test[8]=      {0x20,0x01,0x02,0x04,0x08,0x10,0x40,0x80};	
//���������������0-9��������				
unsigned char code Number_arr[10]=   {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	

/*************************************************************************************
*��������Delay(unsigned char time)
*��  �ܣ���ʱ����
**************************************************************************************/
void Delay(unsigned char time)
{
	int i,j,k;
	for(i=0;i<time;i++)
		for(j=0;j<50;j++)
			for(k=0;k<90;k++)
			{
				;
			}
}

/************************������*******************************************************/
void main()
{
	unsigned char i,j=0,k=0,l=0,m=0;
	unsigned char temp[4]={0x3f,0x06,0x5b,0x4f};
	bit err = 0;
	Delay(10);

	P0 = 0;
	Delay(10);
	P0 = 0xFF;
	P1 = 0;

	while(1)
	{
		//������ʾģ�����
		err = DisplayConfig_TM1650(LightLevel,SegmentMode,WorkMode,ON);
		//�ϵ��������λ���ж�ȫ��
		for(i = 0;i < 4; i++)
		{
			err = DisplayOneDigi_TM1650(i+1,0xFF);
		}
		Delay(10);
		
		//��4λ����ܵ�ÿ���ηֱ����
		for(m=0;m<=9;m++)
		{
			for(i=0;i<4;i++)
			{
				 err = DisplayOneDigi_TM1650(i+1,Seg_test[m]);
			}
			Delay(10);
		}

		//�������ʾ����,����ÿ���������ʾ��0-9
		for(m=0;m<=9;m++)
		{
			for(i=0;i<4;i++)
			{
				err = DisplayOneDigi_TM1650(i+1,Number_arr[m]);
			}
			Delay(10);			
		}
		//��ʾtemp�����е�����
		for(i=0;i<4;i++)
		{
			err = DisplayOneDigi_TM1650(i+1,temp[i]);
		}
		Delay(10);	

		//����ʾ
		err = DisplayOFF_TM1650(LightLevel,SegmentMode,WorkMode);			
		Delay(10);	
		
		//����ʾ
		err = DisplayON_TM1650(LightLevel,SegmentMode,WorkMode);			
		Delay(10);	
			
	}
}