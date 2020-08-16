/*-------------------------------------------------------------------------------------
 * ��Ŀ����:

     TM1650оƬ��������v1.0

 * ��Ȩ��Ϣ:

     (c) �������, 2016.

 * ��ʷ�汾:
     2016-12-07:
       - ��ʼ�汾 V1.0.0;

 * ��ע:
     - ʹ��ǰ��Ҫ������Ľӿ����ò�������ͨ�Žӿ�

----------------------------------------------------------------------------------------*/

#ifndef _TM1650_H_
#define _TM1650_H_

/*---------------------------�ӿ�����---------------------------------------------------*/

sbit SCK = P1^0;			   //ʱ���ź����� 
sbit DIO = P1^1; 			   //���������������

/*---------------------оƬ�������壨�����޸ģ�-----------------------------------------*/
//���ȵȼ�����
#define LV1	0x00
#define LV2	0x10
#define LV3	0x20
#define LV4	0x30
#define LV5	0x40
#define LV6	0x50
#define LV7	0x60
#define LV8	0x70
//��ģʽ����
#define _8_SEGMENT_MODE	0x00	   //�˶���ʾģʽ
#define _7_SEGMENT_MODE	0x08	   //�߶���ʾģʽ
//����ģʽ����
#define NORMAL_MODE		0x00	   //��������ģʽ
#define STANDBY_MODE	0x04	   //��������ģʽ
//����ģʽ����
#define DISPLAY_ON		0x01	   //��ʾ��
#define DISPLAY_OFF		0x00	   //��ʾ��
//����
#define CMD_SYSTEM_CONFIG	0x48   //����ϵͳ��������,д��ʾʱ�ȷ��ʹ��ֽ�
#define CMD_READ_KEYPAD		0x4F   //��ȡ������������
//��ʾ��ַ����
#define DIG1_ADDRESS	0x68	   //��һλ����ܵ�ַ
#define DIG2_ADDRESS    0x6A	   //�ڶ�λ����ܵ�ַ
#define DIG3_ADDRESS	0x6C	   //����λ����ܵ�ַ
#define DIG4_ADDRESS    0x6E	   //����λ����ܵ�ַ
							   
/*---------------------------��������------------------------------------------------*/

//����ģ����ʾģʽ�����ȵ�
bit DisplayConfig_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode,unsigned char on_or_off);
//��1-4λ����һλ��ʾ
bit DisplayOneDigi_TM1650(unsigned char digi,unsigned char cha);
//����ʾ
bit DisplayOFF_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode);
//����ʾ
bit DisplayON_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode);

#endif