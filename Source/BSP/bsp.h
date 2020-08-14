/*===========================================================================
网址 ：http://yhmcu.taobao.com/
作者 ：李勇  原 亿和电子工作室  现 亿佰特电子科技有限公司
邮件 ：yihe_liyong@126.com
电话 ：18615799380
===========================================================================*/

#ifndef _BSP_H_
#define _BSP_H_

#include "STM8l10x_conf.h"
#include "mytypedef.h"

// SPI引脚定义 SCLK(PB5), MOSI(PB6), MISO(PB7)
#define PORT_SPI        GPIOB
#define PIN_SCLK        GPIO_Pin_5
#define PIN_MOSI        GPIO_Pin_6
#define PIN_MISO        GPIO_Pin_7

// LED和KEY引脚定义，LED(PB0), KEY(PC1)
#define PORT_LED        GPIOA
#define PIN_LED         GPIO_Pin_2

#define PORT_KEY        GPIOC
#define PIN_KEY         GPIO_Pin_4

// LED操作函数，(ON)打开, (OFF)关闭，(TOG)翻转
#define LED_ON()        GPIO_ResetBits(PORT_LED, PIN_LED)
#define LED_OFF()       GPIO_SetBits(PORT_LED, PIN_LED)
#define LED_TOG()       GPIO_ToggleBits(PORT_LED, PIN_LED)

void SClK_Initial(void);                // 初始化系统时钟，系统时钟 = 16MHZ
void GPIO_Initial(void);                // 初始化通用IO端口
void SPI_Initial(void);                 // 初始化SPI
void TIM3_Initial(void);                // 初始化定时器3，定时时间为1ms
INT8U SPI_ExchangeByte(INT8U input);    // 通过SPI进行数据交换

#define  HW3000_CSN_PORT        GPIOB
#define  HW3000_CSN_IO          GPIO_Pin_4

#define  HW3000_CLK_PORT        GPIOB
#define  HW3000_CLK_IO          GPIO_Pin_5

#define  HW3000_SDO_PORT        GPIOB
#define  HW3000_SDO_IO          GPIO_Pin_7

#define  HW3000_SDI_PORT        GPIOB
#define  HW3000_SDI_IO          GPIO_Pin_6

#define  HW3000_IRQ_PORT        GPIOB
#define  HW3000_IRQ_IO          GPIO_Pin_2

#define  HW3000_PDN_PORT        GPIOB
#define  HW3000_PDN_IO          GPIO_Pin_3
   
#define  LED_PORT               GPIOA
#define  LED_IO                 GPIO_Pin_2

#define GPIO_MODE_IN_FL_NO_IT             GPIO_Mode_In_FL_No_IT     
#define GPIO_MODE_IN_PU_NO_IT             GPIO_Mode_In_PU_No_IT     
#define GPIO_MODE_IN_FL_IT                GPIO_Mode_In_FL_IT        
#define GPIO_MODE_IN_PU_IT                GPIO_Mode_In_PU_IT        
#define GPIO_MODE_OUT_OD_LOW_FAST         GPIO_Mode_Out_OD_Low_Fast 
#define GPIO_MODE_OUT_PP_LOW_FAST         GPIO_Mode_Out_PP_Low_Fast 
#define GPIO_MODE_OUT_OD_LOW_SLOW         GPIO_Mode_Out_OD_Low_Slow 
#define GPIO_MODE_OUT_PP_LOW_SLOW         GPIO_Mode_Out_PP_Low_Slow 
#define GPIO_MODE_OUT_OD_HIZ_FAST         GPIO_Mode_Out_OD_HiZ_Fast 
#define GPIO_MODE_OUT_PP_HIGH_FAST        GPIO_Mode_Out_PP_High_Fast
#define GPIO_MODE_OUT_OD_HIZ_SLOW         GPIO_Mode_Out_OD_HiZ_Slow 
#define GPIO_MODE_OUT_PP_HIGH_SLOW        GPIO_Mode_Out_PP_High_Slow
				
void MCU_gpio_init(void);
void HAL_Delay_nMS(uint16_t time_delay);
void GPIO_WriteLow(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins);
void GPIO_WriteHigh(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins);
BitStatus GPIO_ReadInputPin(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin);
typedef enum
{
    RFLR_STATE_IDLE,
    RFLR_STATE_RX_INIT,
    RFLR_STATE_RX_RUNNING,
    RFLR_STATE_RX_DONE,
    
    RFLR_STATE_RX_ACK_INIT,
    RFLR_STATE_RX_ACK_DONE,
    RFLR_STATE_RX_TIMEOUT,
	
    RFLR_STATE_TX_INIT,
    RFLR_STATE_TX_RUNNING,
    RFLR_STATE_TX_DONE,
    RFLR_STATE_TX_TIMEOUT,
    
    RFLR_STATE_TX_ACK_INIT,
    RFLR_STATE_TX_ACK_DONE,
    
    RFLR_STATE_SLEEP,
}tRFLRStates;
#endif //_BSP_H_

/*===========================================================================
-----------------------------------文件结束----------------------------------
===========================================================================*/
