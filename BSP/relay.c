#include "includes.h"
#include "relay.h"
#include <string.h>

const u8 OpenRelay[]={0x55,0x55,0x55,0x00,0x00,0x00,0x00,0x55,0x55,0x55};
const u8 CloseRelay[]={0x55,0x55,0x55,0x00,0x00,0x00,0x01,0x55,0x55,0x55};
const u8 OpenRelayAnswer[]= "RelayOpen ";
const u8 CloseRelayAnswer[]="RelayClose";


u8 RelayCommand(void)
{
	u8 Commandstatus = REALYFLASE,RelayBuf[REALYBUFLEN],RelayBufLen;
//	RelayBufLen = GetUsart1Buffer(RelayBuf);
	RelayBufLen = Process_Socket_Data1(RelayBuf);
//	TestW5500();
	if(RelayBufLen !=10)
	{
		return Commandstatus;
	}
//	for(i=0;i<10;i++)
//		UART1SendByte(RelayBuf[i]);
//	printf("%s",RelayBuf);
	if(memcmp((const char *)OpenRelay,(const char *)RelayBuf,REALYBUFLEN) == 0)
	{
		Commandstatus = REALYOPEN;
//		TestW5500TX((u8 *)OpenRelayAnswer,REALYBUFLEN);
//		printf("OPEN\r\n");
	}
	else if(memcmp((const char *)CloseRelay,(const char *)RelayBuf,REALYBUFLEN) == 0)
	{
		Commandstatus = REALYCLOSE;
//		TestW5500TX((u8 *)CloseRelayAnswer,REALYBUFLEN);
//		printf("CLOSE\r\n");
	}
	
	return Commandstatus;
}

void TestRelay(void)
{
	u8 Commandstatus;
	
	Commandstatus = RelayCommand();
	
	if(Commandstatus == REALYOPEN)
	{
		RealySW(OPENREALY);
	}
	if(Commandstatus == REALYCLOSE)
	{
		RealySW(CLOSEREALY);
	}
	
//	OSTimeDlyHMSM(0, 0,0,500); 
}
const u8 LSRelay0Open[]={0xAA,0xAA,0xAA,0x00,0x00,0x00,0x00,0xAA,0xAA,0xAA};
const u8 LSRelay0Close[]={0xAA,0xAA,0xAA,0x00,0x00,0x00,0x01,0xAA,0xAA,0xAA};
const u8 LSRelay1Open[]={0xAA,0xAA,0xAA,0x00,0x01,0x00,0x00,0xAA,0xAA,0xAA};
const u8 LSRelay1Close[]={0xAA,0xAA,0xAA,0x00,0x01,0x00,0x01,0xAA,0xAA,0xAA};
const u8 LSRelay2Open[]={0xAA,0xAA,0xAA,0x00,0x02,0x00,0x00,0xAA,0xAA,0xAA};
const u8 LSRelay2Close[]={0xAA,0xAA,0xAA,0x00,0x02,0x00,0x01,0xAA,0xAA,0xAA};
const u8 LSRelay3Open[]={0xAA,0xAA,0xAA,0x00,0x03,0x00,0x00,0xAA,0xAA,0xAA};
const u8 LSRelay3Close[]={0xAA,0xAA,0xAA,0x00,0x03,0x00,0x01,0xAA,0xAA,0xAA};

const u8 LSRelay0Open1Close[]={0xAA,0xAA,0xAA,0x00,0x04,0x00,0x00,0xAA,0xAA,0xAA};
const u8 LSRelay0Close1Open[]={0xAA,0xAA,0xAA,0x00,0x04,0x00,0x01,0xAA,0xAA,0xAA};
const u8 LSRelay0Close1Close[]={0xAA,0xAA,0xAA,0x00,0x04,0x00,0x02,0xAA,0xAA,0xAA};
const u8 LSRelay2Open3Close[]={0xAA,0xAA,0xAA,0x00,0x05,0x00,0x00,0xAA,0xAA,0xAA};
const u8 LSRelay2Close3Open[]={0xAA,0xAA,0xAA,0x00,0x05,0x00,0x01,0xAA,0xAA,0xAA};
const u8 LSRelay2Close3Close[]={0xAA,0xAA,0xAA,0x00,0x05,0x00,0x02,0xAA,0xAA,0xAA};

u8 LSDate(void)
{
	u8 LSBuf[10],Commandstatus = 0xFF;
	u16 uLen = 0;
	memset(LSBuf,0,sizeof(LSBuf));
	uLen = GetUsart1Buffer(LSBuf);

	if(uLen != 10)
		Commandstatus = 0xFF;
	if(memcmp((const char *)LSRelay0Open,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x00;
	}
	if(memcmp((const char *)LSRelay0Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x01;
	}
	
	if(memcmp((const char *)LSRelay1Open,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x10;
	}
	if(memcmp((const char *)LSRelay1Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x11;
	}
	
	if(memcmp((const char *)LSRelay2Open,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x20;
	}
	if(memcmp((const char *)LSRelay2Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x21;
	}
	
	if(memcmp((const char *)LSRelay3Open,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x30;
	}
	if(memcmp((const char *)LSRelay3Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x31;
	}
	
	if(memcmp((const char *)LSRelay0Open1Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x40;
	}
	
	if(memcmp((const char *)LSRelay0Close1Open,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x41;
	}
	
	if(memcmp((const char *)LSRelay0Close1Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x42;
	}
	
	if(memcmp((const char *)LSRelay2Open3Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x50;
	}
	
	if(memcmp((const char *)LSRelay2Close3Open,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x51;
	}
	
	if(memcmp((const char *)LSRelay2Close3Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = 0x52;
	}
	
	return Commandstatus;
}

void LSReadRelayPin(void)
{
	u8 ReadPinA0 = 0xFF,ReadPinA1 = 0xFF,ReadPinA2 = 0xFF,ReadPinA3 = 0xFF;
	u8 PinState[32];
	memset(PinState,0,32);
	ReadPinA0 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
	ReadPinA1 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
	ReadPinA2 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
	ReadPinA3 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
	PinState[0] = ReadPinA0;
	PinState[1] = ReadPinA1;
	PinState[2] = ReadPinA2;
	PinState[3] = ReadPinA3;
	UART1SendDate(PinState,4);
//	sprintf((char*)PinState,"A0=%d,A1=%d,A2=%d,A3=%d\r\n",ReadPinA0,ReadPinA1,ReadPinA2,ReadPinA3);
//	printf("%s",PinState);
}

void LSRelay(void)
{
	u8 Commandstatus = 0xFF;
	Commandstatus = LSDate();
	switch(Commandstatus)
	{
		case	0x00:	RELAYPIN0(ON);LSReadRelayPin();break;
		case	0x01:	RELAYPIN0(OFF);LSReadRelayPin();break;
		case	0x10:	RELAYPIN1(ON);LSReadRelayPin();break;
		case	0x11:	RELAYPIN1(OFF);LSReadRelayPin();break;
		case	0x20:	RELAYPIN2(ON);LSReadRelayPin();break;
		case	0x21:	RELAYPIN2(OFF);LSReadRelayPin();break;
		case	0x30:	RELAYPIN3(ON);LSReadRelayPin();break;
		case	0x31:	RELAYPIN3(OFF);LSReadRelayPin();break;
		case	0x40:	RELAYPIN0(ON);RELAYPIN1(OFF);LSReadRelayPin();break;
		case	0x41:	RELAYPIN0(OFF);RELAYPIN1(ON);LSReadRelayPin();break;
		case	0x42:	RELAYPIN0(OFF);RELAYPIN1(OFF);LSReadRelayPin();break;
		case	0x50:	RELAYPIN2(ON);RELAYPIN3(OFF);LSReadRelayPin();break;
		case	0x51:	RELAYPIN2(OFF);RELAYPIN3(ON);LSReadRelayPin();break;
		case	0x52:	RELAYPIN2(OFF);RELAYPIN3(OFF);LSReadRelayPin();break;
		
		default: ;
	}
}

void PLCReadRelayPin(void)
{
	u8 ReadPinA0 = 0xFF,ReadPinA1 = 0xFF,ReadPinA2 = 0xFF,ReadPinA3 = 0xFF;
	ReadPinA0 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
	ReadPinA1 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
	ReadPinA2 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
	ReadPinA3 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
	if(ReadPinA0 == 1 && ReadPinA1 == 0)
	{
		UART1SendDate((U8*)LSRelay0Open1Close,10);
		OSTimeDlyHMSM(0, 0,1,0);
	}
	
	if(ReadPinA0 == 0 && ReadPinA1 == 1)
	{
		UART1SendDate((U8*)LSRelay0Close1Open,10);
		OSTimeDlyHMSM(0, 0,1,0);
	}
	
	if(ReadPinA0 == 0 && ReadPinA1 == 0)
	{
		UART1SendDate((U8*)LSRelay0Close1Close,10);
		OSTimeDlyHMSM(0, 0,1,0);
	}
	
	if(ReadPinA2 == 1 && ReadPinA3 == 0)
	{
		UART1SendDate((U8*)LSRelay2Open3Close,10);
		OSTimeDlyHMSM(0, 0,1,0);
	}
	if(ReadPinA2 == 0 && ReadPinA3 == 1)
	{
		UART1SendDate((U8*)LSRelay2Close3Open,10);
		OSTimeDlyHMSM(0, 0,1,0);
	}
	
	if(ReadPinA2 == 0 && ReadPinA3 == 0)
	{
		UART1SendDate((U8*)LSRelay2Close3Close,10);
		OSTimeDlyHMSM(0, 0,1,0);
	}
}
void PLCDate(void)
{
	u8 PLCBuf[32];
	u16 uLen = 0;
	memset(PLCBuf,0,sizeof(PLCBuf));
	uLen = GetUsart1Buffer(PLCBuf);
	if(uLen != 10)
	{
		return ;
	}
	
	if(memcmp((const char *)LSRelay0Open1Close,(const char *)PLCBuf,10) == 0)
	{
		RELAYPIN0(ON);RELAYPIN1(OFF);
	}
	
	if(memcmp((const char *)LSRelay0Close1Open,(const char *)PLCBuf,10) == 0)
	{
		RELAYPIN0(OFF);RELAYPIN1(ON);
	}
	
	if(memcmp((const char *)LSRelay0Close1Close,(const char *)PLCBuf,10) == 0)
	{
		RELAYPIN0(OFF);RELAYPIN1(OFF);
	}
	
	if(memcmp((const char *)LSRelay2Open3Close,(const char *)PLCBuf,10) == 0)
	{
		RELAYPIN2(ON);RELAYPIN3(OFF);
	}
	
	if(memcmp((const char *)LSRelay2Close3Open,(const char *)PLCBuf,10) == 0)
	{
		RELAYPIN2(OFF);RELAYPIN3(ON);
	}
	
	if(memcmp((const char *)LSRelay2Close3Close,(const char *)PLCBuf,10) == 0)
	{
		RELAYPIN2(OFF);RELAYPIN3(OFF);
	}
	
}

void PLCRelay(void)
{
	PLCReadRelayPin();
	PLCDate();
}

