#ifndef __REALY_H
#define	__REALY_H
#include "stm32f10x.h"




#define OPENREALY  0
#define CLOSEREALY 1

#define RealySW(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_14)
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
	REALYCLOSE_4,
};

#define	LSSTATUSINIT		0xFF		
#define	LSLEN		10
#define	LSRELAY0OPEN	0x00
#define	LSRELAY0CLOSE	0x01
#define	LSRELAY1OPEN	0x10
#define	LSRELAY1CLOSE	0x11
#define	LSRELAY2OPEN	0x20
#define	LSRELAY2CLOSE	0x21
#define	LSRELAY3OPEN	0x30
#define	LSRELAY3CLOSE	0x31

#define	LSRELAY0OPEN1CLOSE	0x40
#define	LSRELAY0CLOSE1OPEN	0x41
#define	LSRELAY0CLOSE1CLOSE	0x42
#define	LSRELAY2OPEN3CLOSE	0x50
#define	LSRELAY2CLOSE3OPEN	0x51
#define	LSRELAY2CLOSE3CLOSE	0x52

#define LSIOINIT	0xFF
#define	LSIOLEN		4

#define PLCIOINIT	0xFF
#define	PLCIOLEN		4
#define	PLCA0BIT		0
#define	PLCA1BIT		1
#define	PLCA2BIT		2
#define	PLCA3BIT		3
#define	PAHIGH			1
#define	PALOW				0
#define	PLCLEN			10


u8 RelayCommand(void);
void TestRelay(void);				
void LSRelay(void);
void PLCRelay(void);

#endif

