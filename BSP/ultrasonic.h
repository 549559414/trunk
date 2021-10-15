#ifndef __ULT_H
#define	__ULT_H

//#define USEULT
#define LOW  0
#define HIGH 1

#define TRIG(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_1)
					
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

//extern unsigned int UltTime;

void Ult_GPIO_Config(void);
void UltTest(void);


#endif
