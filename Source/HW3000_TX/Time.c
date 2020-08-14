#include "Time.h"
#include "stm8l10x.h"
#include "TM1650.h"
#include "System.h"
#include "Key.h"
#include "LED.h"
#include "System.h"
unsigned int timer2 = 0;
unsigned int timer3 = 0;
unsigned char shi,ge;
extern unsigned char  Number_arr[10];
void Timer3_Init(void)  
{  
//	4/128 = 0.03125
//	x / 31250 = 1
	//时钟配置  
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM3,ENABLE);    
	//1分频，向上计数，每50us定时中断一次   
	TIM3_DeInit();  
	TIM3_TimeBaseInit(TIM3_Prescaler_128, TIM3_CounterMode_Up, 31249);       
	TIM3_ARRPreloadConfig(ENABLE);  
	TIM3_ITConfig(TIM3_IT_Update, ENABLE);  
//	TIM3_Cmd(ENABLE); 
}  
void Timer2_Init(void)
{  
//	4/1 = 4000000
//	x / 4000000 = 0.01s = 10ms 
	//时钟配置  
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM2,ENABLE);    
	//1分频，向上计数，每50us定时中断一次   
	TIM2_DeInit();  
	TIM2_TimeBaseInit(TIM2_Prescaler_4, TIM3_CounterMode_Up, 39999);       
	TIM2_ARRPreloadConfig(ENABLE);  
	TIM2_ITConfig(TIM2_IT_Update, ENABLE);  
//	TIM2_Cmd(ENABLE); 
} 
void Timer2_interrupt()
{
	timer2 ++;
	SYS_doScan();
	/* key operaing stop scan Key after 10s no Key push */

	if(timer2 % 100)
	{
	    LED_Blink();
	}

}
void Timer3_interrupt()
{
	timer3 ++;
	
//	/* Read Test Key Value  Judge Stop*/
//	if(GPIO_ReadInputPin(TEST_GPIO_PORT,TEST_GPIO_PIN)==RESET)
//	{
//		SYS_SetEven(SYS_EVEN_TEST_STOP);
//	}else{
//	    SYS_SetEven(SYS_EVEN_TEST_START);
//	}
	if(SYS_GetSYS_Status() == SYS_STATUS_ACTIVE)
	{
	    if(timer3 == SYS_Get_WaterTime())
	    {
	        SYS_SetEven( SYS_EVEN_ACTIVE_STOP );  
	    }
	}else{
		/* Show time of out water */
		if(timer3 < 10)
		{
			DisplayOneDigi_TM1650(1,Number_arr[timer3]);
		}else{
			if(timer3 < 100)
			{
				shi = timer3 / 10;
				ge  = timer3 % 10;
				DisplayOneDigi_TM1650(2,Number_arr[ge]);
				DisplayOneDigi_TM1650(1,Number_arr[shi]);
			}else
			{
				timer3 =0;
				DisplayOneDigi_TM1650(1,Number_arr[8]);
				DisplayOneDigi_TM1650(2,Number_arr[8]);
			}

		}
	}

    
}
