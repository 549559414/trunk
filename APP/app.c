#include "includes.h"

OS_STK task_led2_stk[TASK_LED2_STK_SIZE];		  //定义栈 

void Task_Start(void *p_arg)
{
    (void)p_arg;                				// 'p_arg' 并没有用到，防止编译器提示警告
	SysTick_init();

	OSTaskCreate(Task_LED2,(void *)0,		  	//创建任务2
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

//任务2
void Task_LED2(void *p_arg)
{
    (void)p_arg;                	
		SysTick_init();
    while (1)
    {
//			FlashTest();				//内部flash测试程序
			#ifdef	LCDRGB			//使用彩屏
			Rotate_Test();
			#else
//			GUITest();					//单色屏
			#endif
			#ifdef USEULT 				//使用超声波
			UltTest();
			#endif
			#ifdef	USEHLK				//语音模块
			TestHLKVoice();
			#endif
			OSTimeDlyHMSM(0, 0,1,0);
    }
}


