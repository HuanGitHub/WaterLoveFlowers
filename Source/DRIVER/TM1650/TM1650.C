/*------------------------------------------------------------------------------------
 * 项目名称:

     TM1650芯片驱动程序v1.0

 * 历史版本:
     2016-12-07:
       - 初始版本 V1.0.0;

 * 备注:
     - 使用前需要在TM1668.h文件设置通信接口、初始化数据
-------------------------------------------------------------------------------------*/

/************************包含头文件***************************************************/

#include "TM1650.h"
#include "bsp.h"
#include "stm8l10x.h"
unsigned char tmp,err;
unsigned char DisplayAddressArray[4] = {DIG1_ADDRESS,DIG2_ADDRESS,DIG3_ADDRESS,DIG4_ADDRESS};
/*************************************************************************************
*函数名：void FrameStart_1650(void)
*功  能：帧起始信号
*说  明：保持SCK为高，DIO从1跳到0为起始信号
**************************************************************************************/
void FrameStart_1650(void)
{
	//先全部拉高
	DIO(1);
	SCK(1);		  
	//DIO拉低,然后将SCK也拉低，为后续传输准备
	HAL_Delay_nMS(1);
	DIO(0);
    HAL_Delay_nMS(1);
}
/*************************************************************************************
*函数名：void FrameStop_1650(void)
*功  能：帧结束信号
*说  明：保持SCK为高，DIO从0跳到1为结束信号
**************************************************************************************/
void FrameEnd_1650(void)
{
	//先全部拉高
	DIO(0);
	SCK(1);		  
	//DIO拉低,然后将SCK也拉低，为后续传输准备
	DIO(1);
}
BitStatus read_dio()
{
	BitStatus GPIO_Value = 1;
	GPIO_Init(DIO_GPIO_PORT,DIO_GPIO_PIN,GPIO_Mode_In_FL_No_IT);
    HAL_Delay_nMS(5);
	GPIO_Value = GPIO_ReadInputDataBit(DIO_GPIO_PORT,DIO_GPIO_PIN);
	GPIO_Init(DIO_GPIO_PORT,DIO_GPIO_PIN,GPIO_Mode_Out_PP_High_Slow);
	return GPIO_Value;
}
void init_Gpio1650()
{
    GPIO_Init(SCK_GPIO_PORT, SCK_GPIO_PIN,   GPIO_Mode_Out_PP_High_Slow);
    GPIO_Init(DIO_GPIO_PORT, DIO_GPIO_PIN,   GPIO_Mode_Out_PP_High_Slow);   
	
	GPIO_Init(KEY_GPIO_PORT, KEY_GPIO_PIN,   GPIO_Mode_In_PU_IT);  
	EXTI_DeInit (); 
    EXTI_SetPinSensitivity (KEY_EXTI_PIN,EXTI_Trigger_Falling);   //设置中断IRQ
//	GPIO_Init(GPIOD, GPIO_Pin_0,   GPIO_Mode_Out_PP_High_Slow); 
}
/*************************************************************************************
*函数名：unsigned char FrameAck_1650(void)
*功  能：帧Ack信号
*说  明：返回值为0表示通信正常，返回值为1表示通信异常
**************************************************************************************/
unsigned char FrameAck_1650(void)
{
	//先判断DIO
	if(read_dio()==0)
	{
		SCK(1);
		SCK(0);
		return 0;
	}
	else
	{
		return 1;
	}
}
/*************************************************************************************
*函数名：SendOne_TM1650(unsigned char firstByte)
*功  能：发送一个字节的数据
*说  明：低位先发送
**************************************************************************************/
unsigned char SendOne_TM1650(unsigned char firstByte)
{
	unsigned char tmp;
	unsigned char i=0;
	unsigned char err=0;			//出错时返回1

	tmp=firstByte;
	//起始信号
	FrameStart_1650();
	//发送数据，先发firstByte，再发secondByte，MSB在前
	for(i=0;i<8;i++)
	{
		if(tmp&0x80)
		{
			DIO(1);
		}
		else
		{
			DIO(0);
		}
	
		SCK(0);
		SCK(1);
		SCK(0);
		
		tmp=tmp<<1;
	}
	//判断ACK
	if(FrameAck_1650()==1)
	{
		err=1;
	}
	//发送secondByte
	return err;
}
/*************************************************************************************
*函数名：SendOneCouple_TM1650(unsigned char firstByte,unsigned char secondByte)
*功  能：1668发送一个字节的数据
*说  明：低位先发送
**************************************************************************************/
unsigned char SendOneCouple_TM1650(unsigned char firstByte,unsigned char secondByte)
{
	unsigned char tmp;
	unsigned char i=0;
	unsigned char err=0;			//出错时返回1

	tmp=firstByte;
	//起始信号
	FrameStart_1650();
	//发送数据，先发firstByte，再发secondByte，MSB在前
	for(i=0;i<8;i++)
	{
		if(tmp&0x80)
		{
			DIO(1);
		}
		else
		{
			DIO(0);
		}
	    HAL_Delay_nMS(1);
		SCK(0);
		HAL_Delay_nMS(1);
		SCK(1);
		HAL_Delay_nMS(1);
		SCK(0);
		
		tmp=tmp<<1;
	}
	//判断ACK
	if(FrameAck_1650()==1)
	{
		err=1;
	}
	//发送secondByte
	tmp=secondByte;
	for(i=0;i<8;i++)
	{
		if(tmp&0x80)
		{
			DIO(1);
		}
		else
		{
			DIO(0);
		}
	
		SCK(0);
		HAL_Delay_nMS(1);
		SCK(1);
		HAL_Delay_nMS(1);
		SCK(0);
		
		tmp=tmp<<1;
	}
	//判断ACK
	if(FrameAck_1650()==1)
	{
		err=1;
	}
	//结束信号
	FrameEnd_1650();
	//返回值
	return err;
}
/*************************************************************************************
*函数名：unsigned char DisplayConfig_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode)
*功  能：1668发送一个命令
*说  明：低位先发送
**************************************************************************************/
unsigned char DisplayConfig_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode,unsigned char on_or_off)
{
	unsigned char tmp = 0;
	unsigned char err = 0;
	tmp = lightLevel | SegmentMode |  WorkMode | on_or_off;
	err = SendOneCouple_TM1650(CMD_SYSTEM_CONFIG,tmp);

	if(err == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}
/*************************************************************************************
*函数名：unsigned char DisplayOneDigi_TM1650(unsigned char digi,unsigned char cha)
*功  能：
*说  明：
*参  数：
**************************************************************************************/
unsigned char DisplayOneDigi_TM1650(unsigned char digi,unsigned char cha)
{
	unsigned char tmp = 0;
	unsigned char err = 0;
	err = SendOneCouple_TM1650(DisplayAddressArray[digi-1],cha);
	return err;
}

/*************************************************************************************
*函数名：unsigned char DisplayOFF_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode)
*功  能：
*说  明：
*参  数：
**************************************************************************************/
unsigned char DisplayOFF_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode)
{
	unsigned char tmp = 0;
	unsigned char err = 0;
	tmp = lightLevel | SegmentMode |  WorkMode | DISPLAY_OFF;
	err = SendOneCouple_TM1650(CMD_SYSTEM_CONFIG,tmp);

	if(err == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*************************************************************************************
*函数名：DisplayON_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode)
*功  能：固定地址模式在指定位显示一个数据
*说  明：
*参  数：digi-显示的位，从1-4（从左到右），cha-待显示数据
**************************************************************************************/
unsigned char DisplayON_TM1650(unsigned char lightLevel,unsigned char SegmentMode,unsigned char WorkMode)
{
	unsigned char tmp = 0;
	unsigned char err = 0;
	tmp = lightLevel | SegmentMode |  WorkMode | DISPLAY_ON;
	err = SendOneCouple_TM1650(CMD_SYSTEM_CONFIG,tmp);

	if(err == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*************************************************************************************
*函数名：unsigned char Scan_Key_TM1650(void)
*功  能：从TM1650获取按键值
*说  明：
*参  数：返回键值
**************************************************************************************/
unsigned char Scan_Key_TM1650()          // 按键扫描
{
        unsigned char i;
        unsigned char rekey;
        FrameStart_1650();
		err = SendOne_TM1650(CMD_READ_KEYPAD);
        FrameAck_1650();
       // DIO(1);
        for(i=0;i<8;i++)
        {
           SCK(1);
           rekey = rekey<<1;
           if(R_DIO)
           {
                   rekey++;
           } 
           SCK(0);        
        }
        FrameAck_1650();
        FrameEnd_1650();
        return(rekey);
}



/***************************************END******************************************/

