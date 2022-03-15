#include "includes.h"

/*
 * 函数名：BSP_Init
 * 描述  ：时钟初始化、硬件初始化
 * 输入  ：无
 * 输出  ：无
 */
void BSP_Init(void)
{
    SystemInit();		/* 配置系统时钟为72M */	
    LED_GPIO_Config();  /* LED 端口初始化 */
//		USART1_Config(); //USART1 配置 	
		
		delay_init();

//液晶屏SPI与网口冲突		
//		#ifdef	LCDRGB					//使用彩屏
//		LCD_Init();
//		#else
//		OLED_Init();			         //初始化OLED  
//		OLED_Clear(0);             //清屏（全黑）
//		#endif
		
		#ifdef USEULT 				//使用超声波
		EXTIX_Init();				//外部中断
		Ult_GPIO_Config();	//IO配置
		TIM2_NVIC_Configuration();//定时器
		TIM2_Configuration();
		#endif
//		I2C_GPIO_Config();//硬件IIC有问题使用模拟IIC
		
		/*网口驱动*/
		W5500Pro_Initialization();
		
		/**********/
}

/*
 * 函数名：SysTick_init
 * 描述  ：配置SysTick定时器
 * 输入  ：无
 * 输出  ：无
 */
void SysTick_init(void)
{
    SysTick_Config(SystemFrequency/OS_TICKS_PER_SEC);//初始化并使能SysTick定时器
}
