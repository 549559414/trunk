#ifndef __DS1307_H
#define __DS1307_H
#include "type32.h"

#define DS1307ADDR		0xD0

#define NOCOMMAND			0x00
#define GETCOMMAND		0x01

typedef struct
{
  u8 Seconds;
	u8 Minutes;
	u8 Hours;
}Time_TypeDef;

u8 SetTime(void);
void TestDS1307(void);

#endif 






