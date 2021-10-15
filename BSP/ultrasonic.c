#include "includes.h"
#include "ultrasonic.h"

/*
*超声波程序
*买的超声波模块有问题，在手动检测ECHO脚时，高电平存在的时间跟计时器的时间时一致的。但是超声波就只能检测到一点距离
*而且距离非常近时高电平所存在的时间会突然变大。
*文件关联exti.c、time_test.c
*/
volatile u32 UltTime; // ms 计时变量


void Ult_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PC端口
  GPIO_SetBits(GPIOA, GPIO_Pin_1 );	 // 关闭所有LED
}
extern u32 TRIGFlag;
void UltTest(void)
{
	TRIG(HIGH);
	delay_us(20);
	TRIG(LOW);
	TRIGFlag=0;
	while(WK_UP==0);
	UltTime=0;
	while(WK_UP==1);
	GUI_ShowNum(0,16,TRIGFlag,10,8,1);
	GUI_ShowNum(30,16,UltTime,10,8,1);
	TRIGFlag=0;
	OSTimeDlyHMSM(0, 0,0,50);
}

