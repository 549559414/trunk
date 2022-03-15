#include "includes.h"
#include "I2C_Driver.h"
#include "DS1307.h"

u8 DS1307Buf[8];

void Write_DS1307(u8 address,u8 data)
{
	I2C_Start();
	I2C_SendByte(DS1307ADDR);
	I2C_WaitAck();
	I2C_SendByte(address);
	I2C_WaitAck();
	I2C_SendByte(data);
	I2C_WaitAck();
	I2C_Stop();
}

void Read_DS1307(u8 START,u8 n)
{
	u8 i;
	I2C_Start();
	I2C_SendByte(DS1307ADDR);
	I2C_SendByte(START);
	I2C_Stop();
	
	I2C_Start();
	I2C_SendByte(DS1307ADDR+1);
	I2C_WaitAck();
	for(i=0;i<n;i++)
	{
		DS1307Buf[i] = I2C_ReceiveByte();
		if(i<n-1)
		{
			I2C_Ack();
		}
		else
		{
			I2C_NoAck();
		}
	}
	I2C_Stop();
}


/*********************************************************
*设置时间函数，使用串口发送。xx 	xx xx xx  xx 
*                            任意 时 分 秒 任意
*/
u8 SetTime(void)
{
	u8 Buf[5],BufLen = 0,Commandstatus = NOCOMMAND;
	BufLen = GetUsart1Buffer(Buf);
	if(BufLen != 5)
		return Commandstatus;
	Commandstatus = GETCOMMAND;
	Write_DS1307(0x00,Buf[3]);
	Systick_Delay_1ms(10);
	Write_DS1307(0x01,Buf[2]);
	Systick_Delay_1ms(10);
	Write_DS1307(0x02,Buf[1]);
	Systick_Delay_1ms(10);

	return Commandstatus;
}
void TestDS1307(void)
{
	
	u8 showtime[8];
	Time_TypeDef ShowTime;
	SetTime();
	
	Read_DS1307(0,3);
	ShowTime.Seconds = DS1307Buf[0];
	ShowTime.Minutes = DS1307Buf[1];
	ShowTime.Hours   = DS1307Buf[2];
	sprintf((char*)showtime,"%d%d:%d%d:%d%d",(ShowTime.Hours>>4)&0x03,ShowTime.Hours&0x0f,(ShowTime.Minutes>>4)&0x07,ShowTime.Minutes&0x0f,(ShowTime.Seconds>>4)&0x07,ShowTime.Seconds&0x0f);
	printf("%s",showtime);
//	OLED_Clear(0);
//	GUI_ShowString(40,0,showtime,8,1);
}




