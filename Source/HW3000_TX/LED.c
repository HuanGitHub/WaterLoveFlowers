#include "LED.h"
#include "TM1650.h"
#include "Time.h"
extern unsigned char  Number_arr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
LED_SHOW_POS LED_Show_Pos;
typedef union{
    unsigned char LED_SYS_Par;
    struct{
		unsigned char ST_Mode:1;
		unsigned char :1;
		unsigned char Work_Mode:1;
		unsigned char Out_Mode:1;
        unsigned char LV:4;
    
    }Data;
}LED_CONFIG;
LED_CONFIG LED_Config;
unsigned char  LightLevel =	LV8;				   //显示亮度设置，设置取值范围见【芯片参数定义】				
unsigned char  WorkMode	 =	NORMAL_MODE;		   //工作模式定义，取值范围见【芯片参数定义】
#define SegmentMode		_8_SEGMENT_MODE	
void LED_Init()
{
    LED_Config.LED_SYS_Par = LV8 | _8_SEGMENT_MODE | NORMAL_MODE | DISPLAY_ON;
	
}
void LED_SetBlink(LED_BLINK_REQ Status)
{
    if(Status == REQ_START_BLINK)
	{
	    TIM2_Cmd(ENABLE); 
	}else
	{
	    TIM2_Cmd(DISABLE); 
	}
}
void LED_SetDisp_ONOFF(unsigned char status)
{
    if(DISPLAY_ON == status)
	{
		LED_Config.Data.ST_Mode = 0;
        DisplayOFF_TM1650(LightLevel,SegmentMode,WorkMode);
	}else{
		LED_Config.Data.ST_Mode = 1;
        DisplayON_TM1650(LightLevel,SegmentMode,WorkMode);
	}
}
void LED_Blink()
{
	if( 1 == LED_Config.Data.ST_Mode)
	{
	    LED_SetDisp_ONOFF(DISPLAY_ON);
	}else{
	    LED_SetDisp_ONOFF(DISPLAY_OFF);
	}
}
void LED_Show()
{
	unsigned char i;
	//配置显示模块参数
	DisplayConfig_TM1650(LightLevel,SegmentMode,WorkMode,DISPLAY_ON);
	{
		//开显示
		DisplayON_TM1650(LightLevel,SegmentMode,WorkMode);			
		Delay(10);	
		//上电后让所有位所有段全亮
		for(i = 0;i < 4; i++)
		{
			DisplayOneDigi_TM1650(i+1,0xFF);
		}	
	}
        DisplayOFF_TM1650(LightLevel,SegmentMode,WorkMode);
}
