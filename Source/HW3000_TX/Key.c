#include "Key.h"
#include "TM1650.h"
#include "System.h"
void KEY_Init(void)
{
    GPIO_Init(SET_GPIO_PORT,  SET_GPIO_PIN,   SET_GPIO_MODE);
    GPIO_Init(TEST_GPIO_PORT, TEST_GPIO_PIN,   TEST_GPIO_MODE);   
	
	EXTI_DeInit (); 
    EXTI_SetPinSensitivity (TEST_EXTI_PIN,TEST_EXTI_TRIG);   //设置中断IRQ
	EXTI_SetPinSensitivity (SET_EXTI_PIN,SET_EXTI_TRIG);   //设置中断IRQ
}
unsigned char  KEY_ReadTM1650Key()
{
	unsigned char push_key;
	push_key = Scan_Key_TM1650();
	return push_key;
}
void KEY_TEST_Key_Interrupt()
{
	/* need delay wipe debouncing circuit */
	//delay();
	if(GPIO_ReadInputPin(TEST_GPIO_PORT,TEST_GPIO_PIN)==RESET)
	{
		SYS_SetEven(SYS_EVEN_TEST_STOP);
	}else
	{
	    SYS_SetEven(SYS_EVEN_TEST_START);
	}
    
}
void KEY_SET_Key_Interrupt()
{
    SYS_SetEven(SYS_EVEN_SETING);
}
