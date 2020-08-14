#include "System.h"
#include "FSM.h"
#include "stdlib.h" 
#include "Key.h"
#include "ds3231.h"
#include "Motor.h"
#include "stm8l10x_flash.h"
#include "Time.h"
#define KEY_TIMEOUT  0xffff

#define USER_SET_ADDR  0x009FF0
#define DS3231_INT_CON_ADDR 0x009FF2


void SYS_doScan(void);
void SYS_DoTest_Start(void);
void SYS_DoTest_Stop(void);
void SYS_User_Seting(void);
void SYS_User_Seting_Over(void);
uint8_t rtc_buf[RTC_BUF_SIZE];
FSM_t *SYS_FSM;
SYS_STATUS SYS_Status;
SYS_EVEN SYS_Even;
unsigned int key_time2 = 0;
//typedef struct{
//    unsigned char water_time;
//	unsigned char day_time;
//}S_SET_NUM;
typedef enum{
    WATER,
	DAY,
	TYPE_END,
}E_SET_TYPE;
unsigned char set_num[TYPE_END];

void SYS_Start_Water(void);
void SYS_Stop_Water(void);
E_SET_TYPE e_set_type;


FsmTable_t SYS_Table[]=
{
    {SYS_EVEN_SCAN,SYS_STATUS_HALT,SYS_doScan,SYS_STATUS_SCAN},
	{SYS_EVEN_TEST_START,SYS_STATUS_HALT,SYS_DoTest_Start,SYS_STATUS_SCAN},
	{SYS_EVEN_TEST_STOP,SYS_STATUS_HALT,SYS_DoTest_Stop,SYS_STATUS_SCAN},
	{SYS_EVEN_SETING,SYS_STATUS_HALT,SYS_User_Seting,SYS_STATUS_SETING},
	{SYS_EVEN_SETING,SYS_STATUS_SETING,SYS_User_Seting,SYS_STATUS_SETING},
	{SYS_EVEN_SETING,SYS_STATUS_HALT,SYS_User_Seting_Over,SYS_STATUS_SETING},
	{SYS_EVEN_ACTIVE,SYS_STATUS_HALT,SYS_Start_Water,SYS_STATUS_ACTIVE},
	{SYS_EVEN_ACTIVE_STOP,SYS_STATUS_ACTIVE,SYS_Stop_Water,SYS_STATUS_HALT},
	
};
unsigned char SYS_GetSYS_Status()
{
    return SYS_FSM->curState;
}
unsigned char SYS_Get_WaterTime()
{
    return set_num[WATER];	
}
void SYS_Start_Water()
{
    TIM3_Cmd(ENABLE); 
	MOTOR_Open();
}
void SYS_Stop_Water()
{
    TIM3_Cmd(DISABLE); 
	MOTOR_Close();
}
void SYS_Chang_SetNum()
{
//    if(e_set_type == WATER)
//	{
//	    e_set_type == DAY;
//	}else{
//	    e_set_type == WATER;
//	}
	e_set_type = (e_set_type == WATER ? DAY : WATER);
}
void SYS_Set_DayNum(unsigned char Num)
{
    set_num[DAY] = Num;
}
void SYS_Set_WaterNum(unsigned char Num)
{
    set_num[WATER] = Num;
}

unsigned char *SYS_ReadFlash(uint16_t Address,unsigned char *buf,unsigned char size)
{

	FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);
	FLASH_Unlock(FLASH_MemType_Program); 
	do{
	    *buf = FLASH_ReadByte(Address);
		buf ++;
		Address ++;
		size--;
	}while(size);
    FLASH_Lock(FLASH_MemType_Program); 
	return buf;
}
void SYS_WriteFlash(uint16_t Address,unsigned char *buf,unsigned char size)
{
	FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);
	FLASH_Unlock(FLASH_MemType_Program); 
	do{
	    FLASH_ProgramByte(Address, *buf);
		buf ++;
		Address ++;
		size--;
	}while(size);
		
	FLASH_Lock(FLASH_MemType_Program); 

}
void DS3231_Interrupt()
{
	unsigned char int_con = 0;
    SYS_ReadFlash(USER_SET_ADDR,set_num,TYPE_END);
	SYS_ReadFlash(DS3231_INT_CON_ADDR,&int_con,1);
	
	/* check trigger conditiong */
	if(int_con == set_num[DAY])
	{
	    SYS_SetEven(SYS_EVEN_ACTIVE);
		int_con = 0 ;
	}else{
	   int_con ++ ;
	}
	SYS_WriteFlash(DS3231_INT_CON_ADDR,&int_con,1);
	
}
void SYS_User_Seting_Over()
{
	unsigned char curr_rtc_buf[RTC_BUF_SIZE];
	unsigned char set_rtc_buf[RTC_BUF_SIZE];
	/* Seting Over collect LED show Number use be Save Seting Number*/
//	s_set_num
	// write_to_Flash(s_set_num);
	SYS_WriteFlash(USER_SET_ADDR,set_num,TYPE_END);
	SYS_WriteFlash(DS3231_INT_CON_ADDR,0x00,1);
	/* Set Time of curr time */

	DS3231_GetTime(curr_rtc_buf,RTC_BUF_SIZE);
	/* time calc */
	DS3231_SetAlarm1(curr_rtc_buf,RTC_BUF_SIZE);
	

}
void SYS_User_Seting()
{
	if( SYS_FSM->curState == SYS_STATUS_SETING)
	{
	    SYS_Chang_SetNum();
	}
	
    TIM2_Cmd(ENABLE); 
}
void SYS_doScan()
{
	unsigned char key = 0x00;
    key = KEY_ReadTM1650Key();
	if(key != 0x00)
	{
		/* check Key push Set water time or day time*/
		if(key == KEY_UP)
		{
		    if(e_set_type == WATER)
			{
			    set_num[WATER] ++;
			}else
			{
			    set_num[DAY] ++;
			}
		}
		if(key == KEY_DOWN)
		{
			if(e_set_type == WATER)
			{
			    set_num[WATER] --;
			}else
			{
			     set_num[DAY] --;
			}
		}
		/* Update Show LED Number */
        DisplayOneDigi_TM1650(1,set_num[WATER]);
		DisplayOneDigi_TM1650(3,set_num[DAY]);
		
	    key_time2 = 0;
		
	}else{
	    key_time2 ++;
	}
	/* User not operation Timeout */
	if(key_time2 == KEY_TIMEOUT)
	{
		/* scan key active over */
		SYS_SetEven( SYS_EVEN_SETING_OVER );    
	}
}
/*************************************************************************************
*函数名：void SYS_DoTest(void)
*功  能：Do Test Start Pump
*说  明：Test Out Write,Start Time Show out Write Time on LED.
**************************************************************************************/
void SYS_DoTest_Start()
{
	TIM3_Cmd(ENABLE); 
    MOTOR_DoTest();
}
void SYS_DoTest_Stop()
{
	TIM3_Cmd(DISABLE); 
    MOTOR_DoTest();
}
void SYS_JoinHalt()
{
    halt();
}
void SYS_SetEven(SYS_EVEN even)
{
    SYS_Even = even;
}
void SYS_Init()
{
	e_set_type = WATER;
	SYS_Even = SYS_EVEN_NULL;
    SYS_FSM = (FSM_t *)malloc(sizeof(FSM_t));
	FSM_Init(SYS_FSM,SYS_Table,sizeof(SYS_Table)/sizeof(SYS_Table[0]),SYS_STATUS_IDEL);
}

void SYS_Start()
{
    SYS_Init();
	while(1)
	{
		if(SYS_Even != SYS_EVEN_NULL)
		{
			FSM_EventHandle(SYS_FSM,SYS_Even);
			SYS_Even = SYS_EVEN_NULL;
		}
	}
}
