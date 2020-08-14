#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "stm8l10x.h"

#define MOTOR_GPIO_PIN   GPIO_Pin_1
#define MOTOR_GPIO_PORT  GPIOB

typedef enum{
    MOTOR_OPEN,
	MOTOR_CLOSE,
}MOTOR_STATUS;

void MOTOR_Init(void);
void MOTOR_Open(void);
void MOTOR_Close(void);
void MOTOR_DoTest(void);

MOTOR_STATUS MOTOR_GetStatus(void);




#endif

