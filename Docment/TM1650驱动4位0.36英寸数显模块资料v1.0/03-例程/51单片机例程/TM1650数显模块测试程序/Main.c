/*------------------------------------------------------------------------------------
 * 项目名称:

     TM1650数显模块测试程序

 * 版权信息:

     (c) 飞翼电子, 2016.

 * 历史版本:
 	 
     2016-5-11:
       - 初始版本 V1.0.0;

 * 配置说明:

     - 编译前，请根据硬件连接配置MCU与模块的通讯接口
-------------------------------------------------------------------------------------*/
/************************包含头文件***************************************************/

#include<reg52.h>
#include<TM1650.h>

/****************执行芯片初始化函数时是以此处所定义参数来设置芯片*********************/
#define ON	DISPLAY_ON
#define OFF	DISPLAY_OFF
unsigned char  LightLevel =	LV1;				   //显示亮度设置，设置取值范围见【芯片参数定义】				
unsigned char  WorkMode	 =	NORMAL_MODE;		   //工作模式定义，取值范围见【芯片参数定义】
//显示段模式设置，有两种：8段显示模式和7段显示模式（取值范围见【芯片参数定义】）
#define SegmentMode		_8_SEGMENT_MODE	

/*******************************全局变量**********************************************/
//八段数码管显示的每一段
unsigned char code Seg_test[8]=      {0x20,0x01,0x02,0x04,0x08,0x10,0x40,0x80};	
//共阳极数码管数字0-9编码数组				
unsigned char code Number_arr[10]=   {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	

/*************************************************************************************
*函数名：Delay(unsigned char time)
*功  能：延时函数
**************************************************************************************/
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

/************************主程序*******************************************************/
void main()
{
	unsigned char i,j=0,k=0,l=0,m=0;
	unsigned char temp[4]={0x3f,0x06,0x5b,0x4f};
	bit err = 0;
	Delay(10);

	P0 = 0;
	Delay(10);
	P0 = 0xFF;
	P1 = 0;

	while(1)
	{
		//配置显示模块参数
		err = DisplayConfig_TM1650(LightLevel,SegmentMode,WorkMode,ON);
		//上电后让所有位所有段全亮
		for(i = 0;i < 4; i++)
		{
			err = DisplayOneDigi_TM1650(i+1,0xFF);
		}
		Delay(10);
		
		//让4位数码管的每个段分别点亮
		for(m=0;m<=9;m++)
		{
			for(i=0;i<4;i++)
			{
				 err = DisplayOneDigi_TM1650(i+1,Seg_test[m]);
			}
			Delay(10);
		}

		//数码管显示测试,控制每个数码管显示从0-9
		for(m=0;m<=9;m++)
		{
			for(i=0;i<4;i++)
			{
				err = DisplayOneDigi_TM1650(i+1,Number_arr[m]);
			}
			Delay(10);			
		}
		//显示temp数组中的内容
		for(i=0;i<4;i++)
		{
			err = DisplayOneDigi_TM1650(i+1,temp[i]);
		}
		Delay(10);	

		//关显示
		err = DisplayOFF_TM1650(LightLevel,SegmentMode,WorkMode);			
		Delay(10);	
		
		//开显示
		err = DisplayON_TM1650(LightLevel,SegmentMode,WorkMode);			
		Delay(10);	
			
	}
}