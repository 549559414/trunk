#include "includes.h"

/*
 * ��������BSP_Init
 * ����  ��ʱ�ӳ�ʼ����Ӳ����ʼ��
 * ����  ����
 * ���  ����
 */
void BSP_Init(void)
{
    SystemInit();		/* ����ϵͳʱ��Ϊ72M */	
    LED_GPIO_Config();  /* LED �˿ڳ�ʼ�� */
//		USART1_Config(); //USART1 ���� 	
		
		delay_init();

//Һ����SPI�����ڳ�ͻ		
//		#ifdef	LCDRGB					//ʹ�ò���
//		LCD_Init();
//		#else
//		OLED_Init();			         //��ʼ��OLED  
//		OLED_Clear(0);             //������ȫ�ڣ�
//		#endif
		
		#ifdef USEULT 				//ʹ�ó�����
		EXTIX_Init();				//�ⲿ�ж�
		Ult_GPIO_Config();	//IO����
		TIM2_NVIC_Configuration();//��ʱ��
		TIM2_Configuration();
		#endif
//		I2C_GPIO_Config();//Ӳ��IIC������ʹ��ģ��IIC
		
		/*��������*/
		W5500Pro_Initialization();
		
		/**********/
}

/*
 * ��������SysTick_init
 * ����  ������SysTick��ʱ��
 * ����  ����
 * ���  ����
 */
void SysTick_init(void)
{
    SysTick_Config(SystemFrequency/OS_TICKS_PER_SEC);//��ʼ����ʹ��SysTick��ʱ��
}
