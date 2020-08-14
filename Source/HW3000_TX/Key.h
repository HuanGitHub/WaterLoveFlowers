#ifndef __KEY_H__
#define __KEY_H__
#include "stm8l10x.h"

#define  SET_GPIO_PIN   GPIO_Pin_1
#define  SET_GPIO_PORT  GPIOB
#define  SET_GPIO_MODE GPIO_Mode_In_PU_IT
#define  SET_EXTI_PIN   EXTI_Pin_2          //key�ж���
#define  SET_EXTI_TRIG  EXTI_Trigger_Falling //������ʽ

#define  TEST_GPIO_PIN   GPIO_Pin_1
#define  TEST_GPIO_PORT  GPIOB
#define  TEST_GPIO_MODE  GPIO_Mode_In_PU_IT
#define  TEST_EXTI_PIN   EXTI_Pin_2          //key�ж���
#define  TEST_EXTI_TRIG  EXTI_Trigger_Falling //������ʽ

#define KEY_UP     0x01
#define KEY_DOWN   0x02
void KEY_Init(void);
unsigned char  KEY_ReadTM1650Key(void);

#endif
