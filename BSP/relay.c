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

