#include "includes.h"

OS_STK task_led2_stk[TASK_LED2_STK_SIZE];		  //����ջ 
extern u8 ModePin;
void Task_Start(void *p_arg)
{
    (void)p_arg;                				// 'p_arg' ��û���õ�����ֹ��������ʾ����
	SysTick_init();


	OSTaskCreate(Task_LED2,(void *)0,		  	//��������2
	   &task_led2_stk[TASK_LED2_STK_SIZE-1], TASK_LED2_PRIO); 	
    while (1)
    {
				/*lora��Ŀ*/
//			LSRelay();			//LS��
				OSTimeDlyHMSM(0, 0,1,0);
				/*lora��Ŀ*/
//				PLCRelay();			//PLC��
			/*Զ�̿�����Ŀ*/
			if(ModePin == 0)
			{
					TestRelay();		//Զ�̿��ƿ���
			}
    }
}

//����2
void Task_LED2(void *p_arg)
{
    (void)p_arg;                	
		SysTick_init();
    while (1)
    {
			LED1( ON );		//�������Ƿ���������
			OSTimeDlyHMSM(0, 0,0,500); 
      LED1( OFF);
			OSTimeDlyHMSM(0, 0,0,500); 
			/*lora��Ŀ*/
			if(ModePin == 1)
				TestFlash();
//			Motor();
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
			OSTimeDlyHMSM(0, 0,0,500);
//			TestDS1307();
    }
}


