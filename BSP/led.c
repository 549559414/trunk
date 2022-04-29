/******************** *****************
 * 文件名  ：led.c
 * 描述    ：led 应用函数库
 *          
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：-----------------
 *          |   PB13 - LED1   |
 *          |                 |
 *          |                 |
 *           ----------------- 
 * 库版本  ：ST3.0.0  																										  
 
*********************************************************/
#include "led.h"


 /***************  配置LED用到的I/O口 *******************/
void LED_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化PC端口
  GPIO_SetBits(GPIOC, GPIO_Pin_13 );	 // 关闭所有LED
	GPIO_SetBits(GPIOC, GPIO_Pin_14 );	 // 关闭所有LED
	
//  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // 使能PB端口时钟  
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB端口
//  GPIO_SetBits(GPIOB, GPIO_Pin_7);	 // 关闭所有LED
//	GPIO_SetBits(GPIOB, GPIO_Pin_6 );	 // 关闭所有LED
//	GPIO_SetBits(GPIOB, GPIO_Pin_5 );	 // 关闭所有LED
//	
//	GPIO_SetBits(GPIOB, GPIO_Pin_12);	 // 关闭所有LED
//	GPIO_SetBits(GPIOB, GPIO_Pin_13 );	 // 关闭所有LED
//	GPIO_SetBits(GPIOB, GPIO_Pin_14 );	 // 关闭所有LED
//	GPIO_SetBits(GPIOB, GPIO_Pin_15 );	 // 关闭所有LED
}

void ChangeMode(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // 使能PB端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB端口
	
	GPIO_SetBits(GPIOB, GPIO_Pin_0 );	 // 关闭所有LED
}

void Relay_Pin_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // 使能PB端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PB端口
	
	GPIO_SetBits(GPIOB, GPIO_Pin_0);	 // 关闭所有LED
	GPIO_SetBits(GPIOB, GPIO_Pin_1 );	 // 关闭所有LED
	GPIO_SetBits(GPIOB, GPIO_Pin_2 );	 // 关闭所有LED
	GPIO_SetBits(GPIOB, GPIO_Pin_3 );	 // 关闭所有LED
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // 使能PB端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PB端口
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);	 // 关闭所有LED
	GPIO_ResetBits(GPIOB, GPIO_Pin_5 );	 // 关闭所有LED
	GPIO_ResetBits(GPIOB, GPIO_Pin_6 );	 // 关闭所有LED
	GPIO_ResetBits(GPIOB, GPIO_Pin_7 );	 // 关闭所有LED
}
