#ifndef __REALY_H
#define	__REALY_H
#include "stm32f10x.h"




#define OPENREALY  0
#define CLOSEREALY 1

#define RealySW(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_13)
#define	REALYBUFLEN		10			

enum{
	REALYFLASE,
	REALYOPEN,
	REALYCLOSE
};
u8 RelayCommand(void);
void TestRelay(void);					

#endif

