#include "includes.h"
#include "voice.h"
#include <string.h>
/*
*
*���������ģ��
*
*/



const u8 CallBack[]={0x75,0x41,0x72,0x54,0x63,0x50,0x0A,0x00,0x03,0xE9,0x8D,0xA7,0x00,0x0A,0xA1,0x4A,0x77,0x61,0x6B,0x65,0x75,0x70,0x5F,0x75,0x6E,0x69 };
const u8 OpenSW[]= {0x00,0x0C,0xC1,0x8C,0x64,0x61,0x6B,0x61,0x69,0x6B,0x61,0x69,0x67,0x75,0x61,0x6E };
const u8 CloseSW[]={0x00,0x0D,0xD1,0xAD,0x67,0x75,0x61,0x6E,0x62,0x69,0x6B,0x61,0x69,0x67,0x75,0x61,0x6E};
const u8 CloseLED={0x08};
const u8 OpenLED={0x07};
/***************************************************************************
*����ģ��ָ�������Ŀǰֻ��������ָ���Ӧָ��������ؿ�ָ��������ع�ָ�
*����ֵΪ��Ӧָ��ֵ��
*/
u8 HLKCommand(void)
{
	u8 Commandstatus = NONESWCOMMAND,HLKBuf[HLKBUFLEN],HLKLen,StatusFlag;
	HLKLen = GetUsart1Buffer(HLKBuf);
	StatusFlag = HLKBuf[STATUSFLAG];
	if(HLKLen<10)
	{
		return Commandstatus;
	}
	if(strcmp((const char *)CallBack,(const char *)HLKBuf) == 0)
	{
//		printf("callback\r\n");
			Commandstatus = CALLBACKCOMMAND;
	}
	else if(StatusFlag == OPENFLAG)
	{
			
//		printf("opensw\r\n");
			Commandstatus = OPENSWCOMMAND;
	}
	else if(StatusFlag == CLOSEFLAG)
	{
//		printf("CloseSW\r\n");
			Commandstatus = CLOSESWCOMMAND;
	}
	else Commandstatus = NONESWCOMMAND;//printf("NONE");
	
	if(StatusFlag == OpenLED)
	{
		Commandstatus = OPENSWCOMMAND;
	}
	else if(StatusFlag == CloseLED)
	{
		Commandstatus = CLOSESWCOMMAND;
	}
	
	return Commandstatus;
}

/****************************************************************************************
*�������Գ���ͨ�Žӿ��Ǵ���1�����Դ������򿪿��ء��رտ��ء����ɹ�ʱOLED��ɹ���ʾͼƬ
*
*/
void TestHLKVoice(void)
{
	u8 Commandstatus;
	Commandstatus = HLKCommand();
	if(Commandstatus == OPENSWCOMMAND)
	{
//		GUITest();
		LED1( ON );
	}
	else if(Commandstatus == CLOSESWCOMMAND)
	{
//		OLED_Clear(0); 
		LED1( OFF );
	}
}









