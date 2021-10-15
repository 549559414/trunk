#include "includes.h"
#include "ultrasonic.h"

/*
*����������
*��ĳ�����ģ�������⣬���ֶ����ECHO��ʱ���ߵ�ƽ���ڵ�ʱ�����ʱ����ʱ��ʱһ�µġ����ǳ�������ֻ�ܼ�⵽һ�����
*���Ҿ���ǳ���ʱ�ߵ�ƽ�����ڵ�ʱ���ͻȻ���
*�ļ�����exti.c��time_test.c
*/
volatile u32 UltTime; // ms ��ʱ����


void Ult_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PC�˿�
  GPIO_SetBits(GPIOA, GPIO_Pin_1 );	 // �ر�����LED
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

