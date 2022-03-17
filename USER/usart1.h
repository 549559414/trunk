#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>
#include "type32.h"

#define DEBUGLEVEL	0
void USART1_Config(void);
void UART1Test(void);
void Echo(void);
void Debug(const char *ch,U8 Level);
u16 GetUsart1Buffer(u8* ch);
void UART1SendDate(U8 *ch,U16 len);
#endif /* __USART1_H */
