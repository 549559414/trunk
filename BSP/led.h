#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  0
#define OFF 1

#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_13)
					
#define RELAYPIN0(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_0);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define RELAYPIN1(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define RELAYPIN2(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define RELAYPIN3(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_3);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_3)
					

//#define LED2(a)	if (a)	\
//					GPIO_SetBits(GPIOB,GPIO_Pin_14);\
//					else		\
//					GPIO_ResetBits(GPIOB,GPIO_Pin_14)


void LED_GPIO_Config(void);
void ChangeMode(void);
void Relay_Pin_Config(void);

#endif /* __LED_H */
