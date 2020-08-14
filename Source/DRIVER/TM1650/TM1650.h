/*-------------------------------------------------------------------------------------
 * 项目名称:

     TM1650芯片驱动程序v1.0

 * 历史版本:
     2016-12-07:
       - 初始版本 V1.0.0;

 * 备注:
     - 使用前需要在下面的接口设置部分设置通信接口

----------------------------------------------------------------------------------------*/

#ifndef _TM1650_H_
#define _TM1650_H_

#include "stm8l10x.h"
#include "stm8l10x_gpio.h"
#include "bsp.h"

/*---------------------------接口设置---------------------------------------------------*/

#define SCK_GPIO_PIN   GPIO_Pin_2
#define SCK_GPIO_PORT  GPIOB


#define DIO_GPIO_PIN   GPIO_Pin_1
#define DIO_GPIO_PORT  GPIOB

#define KEY_GPIO_PIN   GPIO_Pin_1
#define KEY_GPIO_PORT  GPIOB
#define KEY_EXTI_PIN   EXTI_Pin_2          //key中断线
#define KEY_EXTI_TRIG  EXTI_Trigger_Falling //触发方式

	//时钟信号引脚 
#define SCK(C)        if(C != 1){GPIO_ResetBits(SCK_GPIO_PORT,SCK_GPIO_PIN);}else{GPIO_SetBits(SCK_GPIO_PORT,SCK_GPIO_PIN);}

    //数据输入输出引脚
#define DIO(C)        if(C != 1){GPIO_ResetBits(DIO_GPIO_PORT,DIO_GPIO_PIN);}else{GPIO_SetBits(DIO_GPIO_PORT,DIO_GPIO_PIN);}
#define R_DIO         read_dio()
/*---------------------芯片参数定义（不可修改）-----------------------------------------*/
//亮度等级定义
#define LV1	0x00
#define LV2	0x10
#define LV3	0x20
#define LV4	0x30
#define LV5	0x40
#define LV6	0x50
#define LV7	0x60
#define LV8	0x70
//段模式定义
#define _8_SEGMENT_MODE	0x00	   //八段显示模式
#define _7_SEGMENT_MODE	0x08	   //七段显示模式
//工作模式定义
#define NORMAL_MODE		0x00	   //正常工作模式
#define STANDBY_MODE	0x04	   //待机工作模式
//开关模式定义
#define DISPLAY_ON		0x01	   //显示开
#define DISPLAY_OFF		0x00	   //显示关
//命令
#define CMD_SYSTEM_CONFIG	0x48   //设置系统参数命令,写显示时先发送此字节
#define CMD_READ_KEYPAD		0x4F   //读取按键数据命令
//显示地址定义
#define DIG1_ADDRESS	0x68	   //第一位数码管地址
#define DIG2_ADDRESS    0x6A	   //第二位数码管地址
#define DIG3_ADDRESS	0x6C	   //第三位数码管地址
#define DIG4_ADDRESS    0x6E	   //第四位数码管地址
							   
/*---------------------------函数声明------------------------------------------------*/

void init_Gpio1650(void);
//配置模块显示模式、亮度等
unsigned char DisplayConfig_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode,unsigned char on_or_off);
//在1-4位其中一位显示
unsigned char DisplayOneDigi_TM1650(unsigned char digi,unsigned char cha);
//关显示
unsigned char DisplayOFF_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode);
//开显示
unsigned char DisplayON_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode);

unsigned char Scan_Key_TM1650(void);

#endif
