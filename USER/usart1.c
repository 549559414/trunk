/***************************************
 * �ļ���  ��usart1.c
 * ����    ������USART1         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ�------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * ��汾  ��ST3.0.0  

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
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = 115200;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

	
}

 /*����һ���ֽ�����*/
 void UART1SendByte(unsigned char SendData)
{	   
        USART_SendData(USART1,SendData);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	    
}  

/*����һ���ֽ�����*/
U8 Buf[MAX_LENGTH];
U16 Count = 0;
unsigned char UART1GetByte(unsigned char* GetData)
{   	 
	  
        if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {  return 0;//û���յ����� 
		}
        *GetData = USART_ReceiveData(USART1); 
        return 1;//�յ�����
}

void USART1_IRQHandler(void)        //����1�ж�            
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

/*printf�������ض���*/
int fputc(int ch,FILE *f)
{
		UART1SendByte(ch);
		
		return ch;
}
/******************************************************************
*��ȡ���ڵ�����ֵ
**ch:����
*����ֵ���������ݳ���
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
**������Ϣ����
**ch��������Ϣ
**Level�����Եȼ� Ϊ0ʱ�رյ�����Ϣ��1Ϊ��
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
**�������ݵĻ���
*/
void Echo(void)
{
//	UART1GetString();
	OSTimeDlyHMSM(0, 0,0,2); 
	Debug("Echo\r\n",DEBUGLEVEL);
	UART1SendString();
}




