/******************** *****************
 * �ļ���  ��led.c
 * ����    ��led Ӧ�ú�����
 *          
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ�-----------------
 *          |   PB13 - LED1   |
 *          |                 |
 *          |                 |
 *           ----------------- 
 * ��汾  ��ST3.0.0  																										  
 
*********************************************************/
#include "led.h"


 /***************  ����LED�õ���I/O�� *******************/
void LED_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // ʹ��PC�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ��PC�˿�
  GPIO_SetBits(GPIOC, GPIO_Pin_13 );	 // �ر�����LED
	GPIO_SetBits(GPIOC, GPIO_Pin_14 );	 // �ر�����LED
	
//  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // ʹ��PB�˿�ʱ��  
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB�˿�
//  GPIO_SetBits(GPIOB, GPIO_Pin_7);	 // �ر�����LED
//	GPIO_SetBits(GPIOB, GPIO_Pin_6 );	 // �ر�����LED
//	GPIO_SetBits(GPIOB, GPIO_Pin_5 );	 // �ر�����LED
//	
//	GPIO_SetBits(GPIOB, GPIO_Pin_12);	 // �ر�����LED
//	GPIO_SetBits(GPIOB, GPIO_Pin_13 );	 // �ر�����LED
//	GPIO_SetBits(GPIOB, GPIO_Pin_14 );	 // �ر�����LED
//	GPIO_SetBits(GPIOB, GPIO_Pin_15 );	 // �ر�����LED
}

void ChangeMode(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // ʹ��PB�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB�˿�
	
	GPIO_SetBits(GPIOB, GPIO_Pin_0 );	 // �ر�����LED
}

void Relay_Pin_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // ʹ��PB�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PB�˿�
	
	GPIO_SetBits(GPIOB, GPIO_Pin_0);	 // �ر�����LED
	GPIO_SetBits(GPIOB, GPIO_Pin_1 );	 // �ر�����LED
	GPIO_SetBits(GPIOB, GPIO_Pin_2 );	 // �ر�����LED
	GPIO_SetBits(GPIOB, GPIO_Pin_3 );	 // �ر�����LED
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // ʹ��PB�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PB�˿�
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);	 // �ر�����LED
	GPIO_ResetBits(GPIOB, GPIO_Pin_5 );	 // �ر�����LED
	GPIO_ResetBits(GPIOB, GPIO_Pin_6 );	 // �ر�����LED
	GPIO_ResetBits(GPIOB, GPIO_Pin_7 );	 // �ر�����LED
}
