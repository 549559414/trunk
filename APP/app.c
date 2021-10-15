#include "includes.h"

OS_STK task_led2_stk[TASK_LED2_STK_SIZE];		  //����ջ 

void Task_Start(void *p_arg)
{
    (void)p_arg;                				// 'p_arg' ��û���õ�����ֹ��������ʾ����
	SysTick_init();

	OSTaskCreate(Task_LED2,(void *)0,		  	//��������2
	   &task_led2_stk[TASK_LED2_STK_SIZE-1], TASK_LED2_PRIO); 	
    while (1)
    {
//				LED1( ON );
//				OSTimeDlyHMSM(0, 0,1,0); 
//        LED1( OFF);   
//				OSTimeDlyHMSM(0, 0,1,0); 
			TestRelay();
    }
}

//����2
void Task_LED2(void *p_arg)
{
    (void)p_arg;                	
		SysTick_init();
    while (1)
    {
//			FlashTest();				//�ڲ�flash���Գ���
			#ifdef	LCDRGB			//ʹ�ò���
			Rotate_Test();
			#else
//			GUITest();					//��ɫ��
			#endif
			#ifdef USEULT 				//ʹ�ó�����
			UltTest();
			#endif
			#ifdef	USEHLK				//����ģ��
			TestHLKVoice();
			#endif
			OSTimeDlyHMSM(0, 0,1,0);
    }
}


