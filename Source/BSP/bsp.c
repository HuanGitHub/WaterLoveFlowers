/*===========================================================================
* ��ַ ��http://www.cdebyte.com/   http://yhmcu.taobao.com/                 *
* ���� ������  ԭ �ں͵��ӹ�����  �� �ڰ��ص��ӿƼ����޹�˾                 *
* �ʼ� ��yihe_liyong@126.com                                                *
* �绰 ��18615799380                                                        *
============================================================================*/

#include "bsp.h"

/*===========================================================================
* ���� ��SClK_Initial() => ��ʼ��ϵͳʱ�ӣ�ϵͳʱ�� = 4MHZ                  *
============================================================================*/
void SClK_Initial(void)
{
	CLK_MasterPrescalerConfig(CLK_MasterPrescaler_HSIDiv4); // 4M
}
void MCU_gpio_init(void)
{
 GPIO_Init(HW3000_CSN_PORT, HW3000_CSN_IO,GPIO_MODE_OUT_PP_HIGH_FAST);
 GPIO_Init(HW3000_CLK_PORT, HW3000_CLK_IO,GPIO_MODE_OUT_PP_LOW_FAST);
 GPIO_Init(HW3000_SDO_PORT, HW3000_SDO_IO,GPIO_MODE_IN_PU_NO_IT);
 GPIO_Init(HW3000_SDI_PORT, HW3000_SDI_IO,GPIO_MODE_OUT_PP_HIGH_FAST);
 GPIO_Init(HW3000_IRQ_PORT, HW3000_IRQ_IO,GPIO_MODE_IN_PU_IT);
 GPIO_Init(HW3000_PDN_PORT, HW3000_PDN_IO,GPIO_MODE_OUT_PP_LOW_FAST);
 
}
void init_allGpio()
{
    GPIO_Init(GPIOA, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOB, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOC, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOD, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
}
/*===========================================================================
* ���� ��GPIO_Initial() => ��ʼ��ͨ��IO�˿�                                 *
============================================================================*/
void GPIO_Initial(void)
{
   init_allGpio();
    // ����LED���ź�KEY���� KEY(PC4), LED(PA2)

   GPIO_Init(PORT_KEY, PIN_KEY, GPIO_Mode_In_PU_IT);
 
   GPIO_Init(PORT_LED, PIN_LED, GPIO_Mode_Out_PP_Low_Slow);
   GPIO_SetBits(PORT_LED, PIN_LED);
   
   MCU_gpio_init();

}
void GPIO_WriteLow(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
{
	GPIOx->ODR &= (uint8_t)(~PortPins);
}
void GPIO_WriteHigh(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
{
	GPIOx->ODR |= (uint8_t)PortPins;
}
BitStatus GPIO_ReadInputPin(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef GPIO_Pin)
{
	if((GPIOx->IDR & (uint8_t)GPIO_Pin)==0)
	{
		return RESET;
	}
	else
	{
		return SET;
	}
// return ((BitStatus)(GPIOx->IDR & (uint8_t)GPIO_Pin));
}
/*===========================================================================
* ���� ��SPI_Initial() => ��ʼ��SPI                                         *
============================================================================*/
void SPI_Initial(void)
{
	CLK_PeripheralClockConfig(CLK_Peripheral_SPI, ENABLE);

	SPI_DeInit();

	// ����SPI��ز���,2��Ƶ��8MHZ��
	SPI_Init(SPI_FirstBit_MSB, SPI_BaudRatePrescaler_2,
             SPI_Mode_Master, SPI_CPOL_Low, SPI_CPHA_1Edge,
             SPI_Direction_2Lines_FullDuplex, SPI_NSS_Soft);

	SPI_Cmd(ENABLE);

	// SPI���IO������
	GPIO_Init(PORT_SPI, PIN_MISO, GPIO_Mode_In_PU_No_IT);       // MISO (PB7)
	GPIO_Init(PORT_SPI, PIN_SCLK, GPIO_Mode_Out_PP_High_Slow);  // SCLK (PB5)
	GPIO_Init(PORT_SPI, PIN_MOSI, GPIO_Mode_Out_PP_High_Slow);  // MOSI (PB6)
	
	// ����SX127X��ؿ�������NSS(PB4), RST(PA3)
//	GPIO_Init(PORT_SX127X_CSN, PIN_SX127X_CSN, GPIO_Mode_Out_PP_High_Slow);
//	GPIO_SetBits(PORT_SX127X_CSN, PIN_SX127X_CSN);
//	
//	GPIO_Init(PORT_SX127X_RST, PIN_SX127X_RST, GPIO_Mode_Out_PP_High_Slow);
//	GPIO_SetBits(PORT_SX127X_RST, PIN_SX127X_RST);
}

/*===========================================================================
* ���� ��TIM3_Initial() => ��ʼ����ʱ��3����ʱʱ��Ϊ1ms                     *
============================================================================*/
void TIM3_Initial(void)
{
    TIM3_DeInit();

    CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, ENABLE);

    // ����Timer3��ز�����ʱ��Ϊ16/16 = 1MHZ����ʱʱ�� = 1000/1000000 = 1ms
    TIM3_TimeBaseInit(TIM3_Prescaler_4, TIM3_CounterMode_Up, 1000);
    TIM3_ITConfig(TIM3_IT_Update, ENABLE);

    TIM3_Cmd(ENABLE);
}

/*===========================================================================
* ���� ��SPI_ExchangeByte() => ͨ��SPI�������ݽ���                          *
* ���� ����Ҫд��SPI��ֵ                                                    *
* ��� ��ͨ��SPI������ֵ                                                    *
============================================================================*/
INT8U SPI_ExchangeByte(INT8U input)
{
    SPI_SendData(input);
	while (RESET == SPI_GetFlagStatus(SPI_FLAG_TXE));   // �ȴ����ݴ������
	while (RESET == SPI_GetFlagStatus(SPI_FLAG_RXNE));  // �ȴ����ݽ������
	return (SPI_ReceiveData());
}
void HAL_Delay_nMS(uint16_t time_delay)
{
 uint16_t i,j;
 for(i=time_delay;i>0;i--)
 {
   for(j=3200;j>0;j--);
 }
}
/*===========================================================================
-----------------------------------�ļ�����----------------------------------
===========================================================================*/
