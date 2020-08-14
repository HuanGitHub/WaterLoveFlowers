#include "stm8l10x.h"
#include "gpio.h"
#include "uart.h"
#include "i2c.h"
#include "stdio.h"
#include "ds3231.h"
#include "tm1621.h"
#include "bsp.h"
#include "TM1650.h"
#include "System.h"
#include "Key.h"
#include "Time.h"
#include "LED.h"

void delay_s(uint8_t delay)
{
    while (delay-- > 0)
        for(volatile uint32_t d = 0; d < 80000; d++);
}
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
void Init_HW()
{
    SClK_Initial();
 //   GpioInit();
 //   UartInit();
    I2CInit();
    init_Gpio1650();
	KEY_Init();
	SYS_Init();
    LED_Init();
	Timer3_Init();
	Timer2_Init();
    LED_SetBlink(REQ_START_BLINK);
	LED_Show();
}

/************************主程序*******************************************************/


void main(void){
    uint8_t rtc_buf[RTC_BUF_SIZE];
	uint8_t alarm_buf[ALM_BUF_SIZE];
    uint8_t pattern = 0;
    uint8_t counter = 0;
    uint8_t cnt = 0;
    uint8_t tmp,S_shi,S_ge;
 
    int8_t  tempd;
    uint8_t tempf;
    memset(rtc_buf,0x00,3);
	disableInterrupts();
    Init_HW();
	enableInterrupts();     // 打开总中断
	

//	tempf = 0x00;
//   DS3231_ReadReg(0x0E,&tempf,1);
//	tempf = tempf | 0x01;
//	DS3231_WriteReg(0x0E,&tempf,1);
//   alarm_buf[0] = 0x00;
//   alarm_buf[1] = 0x80;
//   alarm_buf[2] = 0x80;
//   alarm_buf[3] = 0x80;
//   DS3231_SetAlarm1(alarm_buf, ALM_BUF_SIZE);
//   memset(alarm_buf,0x00,ALM_BUF_SIZE);
    while(1)
    {   
//      DS3231_GetTime(rtc_buf, RTC_BUF_SIZE);
//      DS3231_GetTemp(&tempd, &tempf);
//      S_ge = 0x0f &  rtc_buf[0]; 
//	   S_shi = (0xf0 & rtc_buf[0])>>4; 
//	DisplayOneDigi_TM1650(2,Number_arr[S_ge]);
//	DisplayOneDigi_TM1650(1,Number_arr[S_shi]);
//	    DS3231_GetAlarm1(alarm_buf, ALM_BUF_SIZE);
	
 //   SYS_Start();
 }
}

int putchar (int c)
{
    // this implementation is SDCC 3.8 specific
    // see sdcc stdio.h for details
    USART->DR = (uint8_t) c;
    while (!(USART->SR & USART_FLAG_TXE));
    return c;
}

/***********************************************************************/


// This is called by some of the SPL files on error.
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    (void)file;
    (void)line;

    /* User can add their own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {

    }
}
#endif
