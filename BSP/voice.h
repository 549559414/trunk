#ifndef __VOICE_H
#define __VOICE_H	

#include "includes.h"

//#define USEHLK

#define NONESWCOMMAND		0
#define CALLBACKCOMMAND	1
#define OPENSWCOMMAND		2
#define CLOSESWCOMMAND	3

#define HLKBUFLEN				1024
#define STATUSFLAG			13
#define	OPENFLAG				0x0C
#define CLOSEFLAG				0x0D

u8 HLKCommand(void);
void TestHLKVoice(void);


#endif



