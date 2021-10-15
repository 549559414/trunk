/***************************************
 * 文件名  ：usart1.c
 * 描述    ：配置USART1         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * 库版本  ：ST3.0.0  

**********************************************************************************/
#include "includes.h"
#include "usart1.h"
#include "type32.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "misc.h"



void USART1_Config(void)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = 115200;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

	
}

 /*发送一个字节数据*/
 void UART1SendByte(unsigned char SendData)
{	   
        USART_SendData(USART1,SendData);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	    
}  

/*接收一个字节数据*/
U8 Buf[MAX_LENGTH];
U16 Count = 0;
unsigned char UART1GetByte(unsigned char* GetData)
{   	 
	  
        if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {  return 0;//没有收到数据 
		}
        *GetData = USART_ReceiveData(USART1); 
        return 1;//收到数据
}

void USART1_IRQHandler(void)        //串口1中断            
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)   
    {
			Buf[Count++]=USART_ReceiveData(USART1);
//			USART_SendData(USART1, USART_ReceiveData(USART1));   
    }

}

void UART1SendString(void)
{
	U16 i;
	for(i=0;i<Count;i++)
	{
		UART1SendByte(Buf[i]);
		if(	Count-1 == i)
				Count = 0;
	}
	memset(Buf,0,sizeof(Buf));
}

/*printf函数的重定向*/
int fputc(int ch,FILE *f)
{
		UART1SendByte(ch);
		
		return ch;
}
/******************************************************************
*获取串口的数据值
**ch:缓存
*返回值：缓存数据长度
*/
u16 GetUsart1Buffer(u8* ch)
{
	u16 i,tmp = 0;
	if(Count == 0)
		return tmp;
	for(i=0;i<Count;i++)
	{
		ch[i] = Buf[i];
	}
	memset(Buf,0,sizeof(Buf));
	tmp = Count;
	Count = 0;
	return tmp;
}

/*************************************************************
**调试信息函数
**ch：调试信息
**Level：调试等级 为0时关闭调试信息，1为开
*/

void Debug(const char *ch,U8 Level)
{
	switch(Level)
	{
		case 0:break;
		case 1:printf(ch);break;
		default :
      break;
	}
}

/******************************************************************
**串口数据的回显
*/
void Echo(void)
{
//	UART1GetString();
	OSTimeDlyHMSM(0, 0,0,2); 
	Debug("Echo\r\n",DEBUGLEVEL);
	UART1SendString();
}




