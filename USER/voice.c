#include "includes.h"
#include "voice.h"
/*
*
*���������ģ��
*
*/



const u8 CallBack[]={0x75,0x41,0x72,0x54,0x63,0x50,0x0A,0x00,0x03,0xE9,0x8D,0xA7,0x00,0x0A,0xA1,0x4A,0x77,0x61,0x6B,0x65,0x75,0x70,0x5F,0x75,0x6E,0x69 };
const u8 OpenSW[]={0x75,0x41,0x72,0x54,0x63,0x50,0x0B,0x00,0x03,0xE9,0x6B,0x3E,0x00,0x0C,0xC1,0x8C,0x64,0x61,0x6B,0x61,0x69,0x6B,0x61,0x69,0x67,0x75,0x61,0x6E };
const u8 CloseSW[]={0x75,0x41,0x72,0x54,0x63,0x50,0x0D,0x00,0x03,0xE9,0x42,0xF8,0x00,0x0D,0xD1,0xAD,0x67,0x75,0x61,0x6E,0x62,0x69,0x6B,0x61,0x69,0x67,0x75,0x61,0x6E };

void HLKCommand(void)
{
	u8 Commandstatus = NONESWCOMMAND,HLKBuf[1024],HLKLen;
	HLKLen = GetUsart1Buffer(HLKBuf);
	if(strcmp(CallBack = HLKBuf) == 0)
	{
		printf("callback\r\n");
	}
	else if(strcmp(OpenSW = HLKBuf) == 0)
	{
		printf("opensw\r\n");
	}
	else if(strcmp(CloseSW = HLKBuf) == 0)
	{
		printf("CloseSW\r\n");
	}
	
}










