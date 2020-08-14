#ifndef __SYSTEM_INC__
#define __SYSTEM_INC__
#include "stm8l10x.h"
typedef enum{
	SYS_STATUS_IDEL,
    SYS_STATUS_SCAN,
	SYS_STATUS_HALT,
	SYS_STATUS_ACTIVE,
	SYS_STATUS_SETING,
}SYS_STATUS;
typedef enum{
	SYS_EVEN_NULL,
	SYS_EVEN_TEST_START,
	SYS_EVEN_TEST_STOP,
    SYS_EVEN_SCAN,
	SYS_EVEN_SETING,
	SYS_EVEN_SETING_OVER,
	SYS_EVEN_HALT,
	SYS_EVEN_ACTIVE,
	SYS_EVEN_ACTIVE_STOP,
}SYS_EVEN;
void SYS_Init(void);
void SYS_Start(void);
void SYS_SetEven(SYS_EVEN even);
void DS3231_Interrupt(void);



#endif

