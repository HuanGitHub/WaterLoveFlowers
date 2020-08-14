#include "Motor.h"

MOTOR_STATUS Motor_Status;
void MOTOR_Init()
{
    GPIO_Init(MOTOR_GPIO_PORT, MOTOR_GPIO_PIN, GPIO_Mode_Out_PP_High_Slow); 
}

void MOTOR_Open()
{
    Motor_Status = MOTOR_OPEN;
}
void MOTOR_Close()
{
    Motor_Status = MOTOR_CLOSE;
}
void MOTOR_DoTest()
{
    if(MOTOR_OPEN != Motor_Status)
	{
	    MOTOR_Open();
	}else{
		MOTOR_Close();
	}
}
MOTOR_STATUS MOTOR_GetStatus()
{
    return Motor_Status;
}
