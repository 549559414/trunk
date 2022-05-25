#include "includes.h"
#include "relay.h"
#include "stmflash.h"
#include <string.h>

const u8 OpenRelay[]={0x55,0x55,0x55,0x00,0x00,0x00,0x00,0x55,0x55,0x55};
const u8 CloseRelay[]={0x55,0x55,0x55,0x00,0x00,0x00,0x01,0x55,0x55,0x55};
const u8 OpenRelay_2[]={0x55,0x55,0x55,0x00,0x00,0x01,0x00,0x55,0x55,0x55};
const u8 CloseRelay_2[]={0x55,0x55,0x55,0x00,0x00,0x01,0x01,0x55,0x55,0x55};
const u8 OpenRelay_3[]={0x55,0x55,0x55,0x00,0x00,0x02,0x00,0x55,0x55,0x55};
const u8 CloseRelay_3[]={0x55,0x55,0x55,0x00,0x00,0x02,0x01,0x55,0x55,0x55};
const u8 OpenRelay_4[]={0x55,0x55,0x55,0x00,0x00,0x03,0x00,0x55,0x55,0x55};
const u8 CloseRelay_4[]={0x55,0x55,0x55,0x00,0x00,0x03,0x01,0x55,0x55,0x55};
//const u8 IPConfig[]={0x55,0x55,0x55,0x00,0x00,0x00,0x02,0x55,0x55,0x55};
//const u8 OpenRelayAnswer[]= "RelayOpen ";
//const u8 CloseRelayAnswer[]="RelayClose";



u8 RelayCommand(void)
{
	u8 Commandstatus = REALYFLASE,RelayBuf[REALYBUFLEN],RelayBufLen;
	
	memset(RelayBuf,0,REALYBUFLEN);
	
	RelayBufLen = Process_Socket_Data1(RelayBuf);
	
	if(RelayBufLen !=10)
	{
		return Commandstatus;
	}
	
	if(memcmp((const char *)OpenRelay,(const char *)RelayBuf,REALYBUFLEN) == 0)
	{
		Commandstatus = REALYOPEN;
	}
	else if(memcmp((const char *)CloseRelay,(const char *)RelayBuf,REALYBUFLEN) == 0)
	{
		Commandstatus = REALYCLOSE;
	}
	
	if(memcmp((const char *)OpenRelay_2,(const char *)RelayBuf,REALYBUFLEN) == 0)
	{
		Commandstatus = REALYOPEN_2;
	}
	else if(memcmp((const char *)CloseRelay_2,(const char *)RelayBuf,REALYBUFLEN) == 0)
	{
		Commandstatus = REALYCLOSE_2;
	}
	
	if(memcmp((const char *)OpenRelay_3,(const char *)RelayBuf,REALYBUFLEN) == 0)
	{
		Commandstatus = REALYOPEN_3;
	}
	else if(memcmp((const char *)CloseRelay_3,(const char *)RelayBuf,REALYBUFLEN) == 0)
	{
		Commandstatus = REALYCLOSE_3;
	}
	
	if(memcmp((const char *)OpenRelay_4,(const char *)RelayBuf,REALYBUFLEN) == 0)
	{
		Commandstatus = REALYOPEN_4;
	}
	else if(memcmp((const char *)CloseRelay_4,(const char *)RelayBuf,REALYBUFLEN) == 0)
	{
		Commandstatus = REALYCLOSE_4;
	}
	
	if(Commandstatus == REALYCLOSE | Commandstatus == REALYOPEN)
	{
		DebugTx(RelayBuf,RelayBufLen);
	}
	
	if(Commandstatus == REALYCLOSE_2 | Commandstatus == REALYOPEN_2)
	{
		DebugTx(RelayBuf,RelayBufLen);
	}
	
	if(Commandstatus == REALYCLOSE_3 | Commandstatus == REALYOPEN_3)
	{
		DebugTx(RelayBuf,RelayBufLen);
	}
	
	if(Commandstatus == REALYCLOSE_4 | Commandstatus == REALYOPEN_4)
	{
		DebugTx(RelayBuf,RelayBufLen);
	}
	
	return Commandstatus;
}

void TestRelay(void)
{
	u8 Commandstatus;
	
	Commandstatus = RelayCommand();
	
	if(Commandstatus == REALYOPEN)
	{
		RealySW(OPENREALY);//B4口不能做普通IO
//		RealySW_2(OPENREALY);
	}
	if(Commandstatus == REALYCLOSE)
	{
		RealySW(CLOSEREALY);
//		RealySW_2(CLOSEREALY);
	}
	
	if(Commandstatus == REALYOPEN_2)
	{
		RealySW_2(OPENREALY);
	}
	if(Commandstatus == REALYCLOSE_2)
	{
		RealySW_2(CLOSEREALY);
	}
	
	if(Commandstatus == REALYOPEN_3)
	{
		RealySW_3(OPENREALY);
	}
	if(Commandstatus == REALYCLOSE_3)
	{
		RealySW_3(CLOSEREALY);
	}
	
	if(Commandstatus == REALYOPEN_4)
	{
		RealySW_4(OPENREALY);
	}
	if(Commandstatus == REALYCLOSE_4)
	{
		RealySW_4(CLOSEREALY);
	}
	
//	OSTimeDlyHMSM(0, 0,0,500); 
}
const u8 LSRelay0Open[]={0xAA,0xAA,0xAA,0x00,0x00,0x00,0x00,0xAA,0xAA,0xAA};				//继电器0开
const u8 LSRelay0Close[]={0xAA,0xAA,0xAA,0x00,0x00,0x00,0x01,0xAA,0xAA,0xAA};				//继电器0关
const u8 LSRelay1Open[]={0xAA,0xAA,0xAA,0x00,0x01,0x00,0x00,0xAA,0xAA,0xAA};				//继电器1开
const u8 LSRelay1Close[]={0xAA,0xAA,0xAA,0x00,0x01,0x00,0x01,0xAA,0xAA,0xAA};				//继电器1关
const u8 LSRelay2Open[]={0xAA,0xAA,0xAA,0x00,0x02,0x00,0x00,0xAA,0xAA,0xAA};				//继电器2开
const u8 LSRelay2Close[]={0xAA,0xAA,0xAA,0x00,0x02,0x00,0x01,0xAA,0xAA,0xAA};				//继电器2关
const u8 LSRelay3Open[]={0xAA,0xAA,0xAA,0x00,0x03,0x00,0x00,0xAA,0xAA,0xAA};				//继电器3开
const u8 LSRelay3Close[]={0xAA,0xAA,0xAA,0x00,0x03,0x00,0x01,0xAA,0xAA,0xAA};				//继电器3关

const u8 LSRelay0Open1Close[]={0xAA,0xAA,0xAA,0x00,0x04,0x00,0x00,0xAA,0xAA,0xAA};	//继电器0开1关
const u8 LSRelay0Close1Open[]={0xAA,0xAA,0xAA,0x00,0x04,0x00,0x01,0xAA,0xAA,0xAA};	//继电器0关1开
const u8 LSRelay0Close1Close[]={0xAA,0xAA,0xAA,0x00,0x04,0x00,0x02,0xAA,0xAA,0xAA};	//继电器0关1关
const u8 LSRelay2Open3Close[]={0xAA,0xAA,0xAA,0x00,0x05,0x00,0x00,0xAA,0xAA,0xAA};	//继电器2开3关
const u8 LSRelay2Close3Open[]={0xAA,0xAA,0xAA,0x00,0x05,0x00,0x01,0xAA,0xAA,0xAA};	//继电器2关3开
const u8 LSRelay2Close3Close[]={0xAA,0xAA,0xAA,0x00,0x05,0x00,0x02,0xAA,0xAA,0xAA};	//继电器2关3关

/*********************************************************
*处理LS数据控制继电器开关的数据
*                            
*/
u8 LSDate(void)
{
	u8 LSBuf[LSLEN],Commandstatus = LSSTATUSINIT;
	u16 uLen = 0;
	memset(LSBuf,0,sizeof(LSBuf));
	uLen = GetUsart1Buffer(LSBuf);

	if(uLen != LSLEN)
		Commandstatus = LSSTATUSINIT;
		
	if(memcmp((const char *)LSRelay0Open,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY0OPEN;
	}
	if(memcmp((const char *)LSRelay0Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY0CLOSE;
	}
	
	if(memcmp((const char *)LSRelay1Open,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY1OPEN;
	}
	if(memcmp((const char *)LSRelay1Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY1CLOSE;
	}
	
	if(memcmp((const char *)LSRelay2Open,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY2OPEN;
	}
	if(memcmp((const char *)LSRelay2Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY2CLOSE;
	}
	
	if(memcmp((const char *)LSRelay3Open,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY3OPEN;
	}
	if(memcmp((const char *)LSRelay3Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY3CLOSE;
	}
	
	if(memcmp((const char *)LSRelay0Open1Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY0OPEN1CLOSE;
	}
	
	if(memcmp((const char *)LSRelay0Close1Open,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY0CLOSE1OPEN;
	}
	
	if(memcmp((const char *)LSRelay0Close1Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY0CLOSE1CLOSE;
	}
	
	if(memcmp((const char *)LSRelay2Open3Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY2OPEN3CLOSE;
	}
	
	if(memcmp((const char *)LSRelay2Close3Open,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY2CLOSE3OPEN;
	}
	
	if(memcmp((const char *)LSRelay2Close3Close,(const char *)LSBuf,10) == 0)
	{
		Commandstatus = LSRELAY2CLOSE3CLOSE;
	}
	
	return Commandstatus;
}


/*********************************************************
*LS读取管脚的状态。
*                            
*/
void LSReadRelayPin(void)
{
	u8 ReadPinA0 = LSIOINIT,ReadPinA1 = LSIOINIT,ReadPinA2 = LSIOINIT,ReadPinA3 = LSIOINIT;
	u8 PinState[LSIOLEN];
	memset(PinState,0,LSIOLEN);
	ReadPinA0 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
	ReadPinA1 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
	ReadPinA2 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
	ReadPinA3 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
	PinState[0] = ReadPinA0;
	PinState[1] = ReadPinA1;
	PinState[2] = ReadPinA2;
	PinState[3] = ReadPinA3;
	UART1SendDate(PinState,LSIOLEN);
//	sprintf((char*)PinState,"A0=%d,A1=%d,A2=%d,A3=%d\r\n",ReadPinA0,ReadPinA1,ReadPinA2,ReadPinA3);
//	printf("%s",PinState);
}

/*********************************************************
*控制LS的通断
*                            
*/
void LSRelay(void)
{
	u8 Commandstatus = LSSTATUSINIT;
	Commandstatus = LSDate();
	switch(Commandstatus)
	{
		case	LSRELAY0OPEN:					RELAYPIN0(ON);LSReadRelayPin();break;
		case	LSRELAY0CLOSE:				RELAYPIN0(OFF);LSReadRelayPin();break;
		case	LSRELAY1OPEN:					RELAYPIN1(ON);LSReadRelayPin();break;
		case	LSRELAY1CLOSE:				RELAYPIN1(OFF);LSReadRelayPin();break;
		case	LSRELAY2OPEN:					RELAYPIN2(ON);LSReadRelayPin();break;
		case	LSRELAY2CLOSE:				RELAYPIN2(OFF);LSReadRelayPin();break;
		case	LSRELAY3OPEN:					RELAYPIN3(ON);LSReadRelayPin();break;
		case	LSRELAY3CLOSE:				RELAYPIN3(OFF);LSReadRelayPin();break;
		case	LSRELAY0OPEN1CLOSE:		RELAYPIN0(ON);RELAYPIN1(OFF);LSReadRelayPin();break;
		case	LSRELAY0CLOSE1OPEN:		RELAYPIN0(OFF);RELAYPIN1(ON);LSReadRelayPin();break;
		case	LSRELAY0CLOSE1CLOSE:	RELAYPIN0(OFF);RELAYPIN1(OFF);LSReadRelayPin();break;
		case	LSRELAY2OPEN3CLOSE:		RELAYPIN2(ON);RELAYPIN3(OFF);LSReadRelayPin();break;
		case	LSRELAY2CLOSE3OPEN:		RELAYPIN2(OFF);RELAYPIN3(ON);LSReadRelayPin();break;
		case	LSRELAY2CLOSE3CLOSE:	RELAYPIN2(OFF);RELAYPIN3(OFF);LSReadRelayPin();break;
		default: ;
	}
}

/*********************************************************
*PLC端IO的输出
*                            
*/
void PLCDate(void)
{
	u8 PLCBuf[PLCIOLEN];
	u16 uLen = 0;
	memset(PLCBuf,0,sizeof(PLCBuf));
	uLen = GetUsart1Buffer(PLCBuf);
	
	if(uLen != PLCIOLEN)
		return;
	
	if(PLCBuf[PLCA0BIT] == PALOW)
	{
		RELAYPIN0(OFF);
	}
	if(PLCBuf[PLCA0BIT] == PAHIGH)
	{
		RELAYPIN0(ON);
	}
	
	if(PLCBuf[PLCA1BIT] == PALOW)
	{
		RELAYPIN1(OFF);
	}
	if(PLCBuf[PLCA1BIT] == PAHIGH)
	{
		RELAYPIN1(ON);
	}
	
	if(PLCBuf[PLCA2BIT] == PALOW)
	{
		RELAYPIN2(OFF);
	}
	if(PLCBuf[PLCA2BIT] == PAHIGH)
	{
		RELAYPIN2(ON);
	}
	
	if(PLCBuf[PLCA3BIT] == PALOW)
	{
		RELAYPIN3(OFF);
	}
	if(PLCBuf[PLCA3BIT] == PAHIGH)
	{
		RELAYPIN3(ON);
	}
}

/*********************************************************
*PLC读取管脚的状态。
*                            
*/
void PLCReadRelayPin(void)
{
	u8 ReadPinA0 = PLCIOINIT,ReadPinA1 = PLCIOINIT,ReadPinA2 = PLCIOINIT,ReadPinA3 = PLCIOINIT;
	ReadPinA0 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
	ReadPinA1 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
	ReadPinA2 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
	ReadPinA3 = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
	if(ReadPinA0 == PAHIGH && ReadPinA1 == PALOW)
	{
		UART1SendDate((U8*)LSRelay0Open1Close,PLCLEN);
		OSTimeDlyHMSM(0, 0,1,0);
	}
	
	if(ReadPinA0 == PALOW && ReadPinA1 == PAHIGH)
	{
		UART1SendDate((U8*)LSRelay0Close1Open,PLCLEN);
		OSTimeDlyHMSM(0, 0,1,0);
	}
	
	if(ReadPinA0 == PALOW && ReadPinA1 == PALOW)
	{
		UART1SendDate((U8*)LSRelay0Close1Close,PLCLEN);
		OSTimeDlyHMSM(0, 0,1,0);
	}
	PLCDate();
	
	if(ReadPinA2 == PAHIGH && ReadPinA3 == PALOW)
	{
		UART1SendDate((U8*)LSRelay2Open3Close,PLCLEN);
		OSTimeDlyHMSM(0, 0,1,0);
	}
	if(ReadPinA2 == PALOW && ReadPinA3 == PAHIGH)
	{
		UART1SendDate((U8*)LSRelay2Close3Open,PLCLEN);
		OSTimeDlyHMSM(0, 0,1,0);
	}
	
	if(ReadPinA2 == PALOW && ReadPinA3 == PALOW)
	{
		UART1SendDate((U8*)LSRelay2Close3Close,PLCLEN);
		OSTimeDlyHMSM(0, 0,1,0);
	}
	PLCDate();
}


void PLCRelay(void)
{
	PLCReadRelayPin();
}

