/*-------------------------------------------------------------------------------------
 * ��Ŀ����:

     TM1650оƬ��������v1.0

 * ��ʷ�汾:
     2016-12-07:
       - ��ʼ�汾 V1.0.0;

 * ��ע:
     - ʹ��ǰ��Ҫ������Ľӿ����ò�������ͨ�Žӿ�

----------------------------------------------------------------------------------------*/

#ifndef _TM1650_H_
#define _TM1650_H_

#include "stm8l10x.h"
#include "stm8l10x_gpio.h"
#include "bsp.h"

/*---------------------------�ӿ�����---------------------------------------------------*/

#define SCK_GPIO_PIN   GPIO_Pin_2
#define SCK_GPIO_PORT  GPIOB


#define DIO_GPIO_PIN   GPIO_Pin_1
#define DIO_GPIO_PORT  GPIOB

#define KEY_GPIO_PIN   GPIO_Pin_1
#define KEY_GPIO_PORT  GPIOB
#define KEY_EXTI_PIN   EXTI_Pin_2          //key�ж���
#define KEY_EXTI_TRIG  EXTI_Trigger_Falling //������ʽ

	//ʱ���ź����� 
#define SCK(C)        if(C != 1){GPIO_ResetBits(SCK_GPIO_PORT,SCK_GPIO_PIN);}else{GPIO_SetBits(SCK_GPIO_PORT,SCK_GPIO_PIN);}

    //���������������
#define DIO(C)        if(C != 1){GPIO_ResetBits(DIO_GPIO_PORT,DIO_GPIO_PIN);}else{GPIO_SetBits(DIO_GPIO_PORT,DIO_GPIO_PIN);}
#define R_DIO         read_dio()
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

void init_Gpio1650(void);
//����ģ����ʾģʽ�����ȵ�
unsigned char DisplayConfig_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode,unsigned char on_or_off);
//��1-4λ����һλ��ʾ
unsigned char DisplayOneDigi_TM1650(unsigned char digi,unsigned char cha);
//����ʾ
unsigned char DisplayOFF_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode);
//����ʾ
unsigned char DisplayON_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode);

unsigned char Scan_Key_TM1650(void);

#endif
