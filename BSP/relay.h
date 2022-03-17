#ifndef __REALY_H
#define	__REALY_H
#include "stm32f10x.h"




#define OPENREALY  0
#define CLOSEREALY 1

#define RealySW(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_13)
#define RealySW_2(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define RealySW_3(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define RealySW_4(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define	REALYBUFLEN		10			

enum{
	REALYFLASE,
	REALYOPEN,
	REALYCLOSE,
	REALYOPEN_2,
	REALYCLOSE_2,
	REALYOPEN_3,
	REALYCLOSE_3,
	REALYOPEN_4,
	REALYCLOSE_4
};
u8 RelayCommand(void);
void TestRelay(void);				
void LSRelay(void);
void PLCRelay(void);

#endif

