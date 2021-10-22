#ifndef __DS1307_H
#define __DS1307_H
#include "type32.h"
typedef struct
{
  u8 Seconds;
	u8 Minutes;
	u8 Hours;
}Time_TypeDef;

u8 SetTime(void);
void TestDS1307(void);

#endif 






