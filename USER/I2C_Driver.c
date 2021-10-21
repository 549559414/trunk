#include "includes.h"
#include "I2C_Driver.h"
/********************************************************/              
//extern void Systick_Delay_1ms(u32 nCount);
/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length (time base 1 ms).
* Output         : None
* Return         : None
*******************************************************************************/

/***************************************************************
**模拟IIC接口PB6:SCL     PB7：SDA
*/
void Systick_Delay_1ms(u32 nCount)
{
	delay_ms(nCount);
}

void I2C_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
	RCC_AHBPeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // ??GPIOB???
  /* Configure I2C1 pins: SCL and SDA */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void I2C_delay(void)
{	
   u8 i=10; //这里可以优化速度	，经测试最低到5还能写入
   while(i) 
   { 
     i--; 
   } 
}

u8 I2C_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_delay();
	if(!SDA_read)return FALSE;	//SDA线为低电平则总线忙,退出
	SDA_L;
	I2C_delay();
	if(SDA_read) return FALSE;	//SDA线为高电平则总线出错,退出
	SDA_L;
	I2C_delay();
	return TRUE;
}

void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
}

void I2C_Ack(void)
{	
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}

void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}

u8 I2C_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	SCL_L;
	I2C_delay();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
      SCL_L;
			printf("失败\r\n");
      return FALSE;
	}
	SCL_L;
	return TRUE;
}

void I2C_SendByte(u8 SendByte) //数据从高位到低位//
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        I2C_delay();
		SCL_H;
        I2C_delay();
    }
    SCL_L;
}

u8 I2C_ReceiveByte(void)  //数据从高位到低位//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay();
	  SCL_H;
      I2C_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
}

u8 TESTDATA[] =
{
0xBB,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF
};
u8 BUF[16]={
0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA
};
void AT24C04_WritePage(void)
{
	u8 i;
	I2C_Start();
	I2C_SendByte(0xa0);
	I2C_SendByte(0x00);
	for(i=0;i<16;i++)
	{
		I2C_SendByte(TESTDATA[i]);
	}
	I2C_Stop();
}

void AT24C04_ReadPage(void)
{
 u8 i;
  I2C_Start();
  I2C_SendByte(0xa0);
	I2C_SendByte(0x00);
	I2C_Start();
	I2C_SendByte(0xa1);
	for(i=0;i<16;i++)
	{
		BUF[i]=I2C_ReceiveByte();
		if(i==15)
		{
			I2C_NoAck();
		}
		else
		{
			I2C_Ack();
		}
	}
	I2C_Stop();
}
/*
**网上说STM32的硬件IIC有问题，目前使用的是模拟IIC但是目前系统板上的AT24C04存储芯片用模拟IIC还没有调通。
**不知道是不是存储芯片有问题。也可能是移植的模拟IIC没移植好。
*/
void AT24C04_Test(void)
{
	u8 i;
	Debug("AT24C04_Test\r\n",DEBUGLEVEL);
	AT24C04_WritePage();

  OSTimeDlyHMSM(0, 0,0,5);

	AT24C04_ReadPage();
	
	for(i=0;i<16;i++)
	printf("%c",BUF[i]);
	
	OSTimeDlyHMSM(0, 0,0,500);
}














//写入1字节数据       待写入数据    待写入地址       器件类型(24c16或SD2403)
u8 I2C_WriteByte(u8 SendByte, u16 WriteAddress, u8 DeviceAddress)
{		
    if(!I2C_Start())return FALSE;
    I2C_SendByte(((WriteAddress & 0x0700) >>7) | DeviceAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE;}
    I2C_SendByte((u8)(WriteAddress & 0x00FF));   //设置低起始地址      
    I2C_WaitAck();	
    I2C_SendByte(SendByte);
    I2C_WaitAck();   
    I2C_Stop(); 
	//注意：因为这里要等待EEPROM写完，可以采用查询或延时方式(10ms)
    //Systick_Delay_1ms(10);
    return TRUE;
}

//注意不能跨页写
//写入1串数据      待写入数组地址    待写入长度      待写入地址       器件类型(24c16或SD2403)
u8 I2C_BufferWrite(u8* pBuffer, u8 length,     u16 WriteAddress, u8 DeviceAddress)
{
    if(!I2C_Start())return FALSE;
    I2C_SendByte(((WriteAddress & 0x0700) >>7) | DeviceAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE;}
    I2C_SendByte((u8)(WriteAddress & 0x00FF));   //设置低起始地址      
	  I2C_WaitAck();	
	  
		while(length--)
		{
		  I2C_SendByte(* pBuffer);
		  I2C_WaitAck();
          pBuffer++;
		}
	  I2C_Stop();
	  //注意：因为这里要等待EEPROM写完，可以采用查询或延时方式(10ms)
	  //Systick_Delay_1ms(10);
	  return TRUE;
}

//跨页写入1串数据  待写入数组地址    待写入长度      待写入地址       器件类型(24c16或SD2403)
void I2C_PageWrite(  u8* pBuffer, u8 length,     u16 WriteAddress, u8 DeviceAddress)
{
    u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;
    Addr  = WriteAddress % I2C_PageSize;      //写入地址是开始页的第几位
    count = I2C_PageSize - Addr;					    //在开始页要写入的个数
    NumOfPage   =  length / I2C_PageSize;     //要写入的页数
    NumOfSingle =  length % I2C_PageSize;     //不足一页的个数

    if(Addr == 0)         //写入地址是页的开始 
    {
      if(NumOfPage == 0)  //数据小于一页 
      {
        I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);   //写少于一页的数据
      }
      else		            //数据大于等于一页  
      {
        while(NumOfPage)//要写入的页数
        {
          I2C_BufferWrite(pBuffer,I2C_PageSize,WriteAddress,DeviceAddress);//写一页的数据
          WriteAddress +=  I2C_PageSize;
          pBuffer      +=  I2C_PageSize;
					NumOfPage--;
					Systick_Delay_1ms(10);
         }
        if(NumOfSingle!=0)//剩余数据小于一页
        {
          I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress); //写少于一页的数据
					Systick_Delay_1ms(10);
        }
       }
    }

    else                  //写入地址不是页的开始 
    {
      if(NumOfPage== 0)   //数据小于一页 
      {
        I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress);   //写少于一页的数据
      }
      else                //数据大于等于一页
      {
        length       -= count;
        NumOfPage     = length / I2C_PageSize;  //重新计算要写入的页数
        NumOfSingle   = length % I2C_PageSize;  //重新计算不足一页的个数	
      
        if(count != 0)
        {  
				  I2C_BufferWrite(pBuffer,count,WriteAddress,DeviceAddress);      //将开始的空间写满一页
          WriteAddress += count;
          pBuffer      += count;
         } 
      
        while(NumOfPage--)  //要写入的页数
        {
          I2C_BufferWrite(pBuffer,I2C_PageSize,WriteAddress,DeviceAddress);//写一页的数据
          WriteAddress +=  I2C_PageSize;
          pBuffer      +=  I2C_PageSize; 
        }
        if(NumOfSingle != 0)//剩余数据小于一页
        {
          I2C_BufferWrite(pBuffer,NumOfSingle,WriteAddress,DeviceAddress); //写少于一页的数据 
        }
      }
    } 
}

//读出1串数据         存放读出数据  待读出长度      待读出地址       器件类型(24c16或SD2403)	
u8 I2C_ReadByte(u8* pBuffer,   u8 length,     u16 ReadAddress,  u8 DeviceAddress)
{		
    if(!I2C_Start())return FALSE;
    I2C_SendByte(((ReadAddress & 0x0700) >>7) | DeviceAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE;}
    I2C_SendByte((u8)(ReadAddress & 0x00FF));   //设置低起始地址      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(((ReadAddress & 0x0700) >>7) | DeviceAddress | 0x0001);
    I2C_WaitAck();
    while(length)
    {
      *pBuffer = I2C_ReceiveByte();
      if(length == 1)I2C_NoAck();
      else I2C_Ack(); 
      pBuffer++;
      length--;
    }
    I2C_Stop();
    return TRUE;
}

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
u8 DS1307Buf[8];
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
	u8 showtime[5],Hours,Minutes,Seconds;
	SetTime();
	
	Read_DS1307(0,3);
	Seconds = DS1307Buf[0];
	Minutes = DS1307Buf[1];
	Hours   = DS1307Buf[2];
	sprintf((char*)showtime,"%d%d:%d%d:%d%d",(Hours>>4)&0x03,Hours&0x0f,(Minutes>>4)&0x07,Minutes&0x0f,(Seconds>>4)&0x07,Seconds&0x0f);
//	printf("%s",showtime);
	OLED_Clear(0);
	GUI_ShowString(40,0,showtime,8,1);
//	for(i=0;i<3;i++)
//	{
//		printf("%c",DS1307Buf[i]);
//	}
}

