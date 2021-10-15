#include <string.h>
#include "W5500Process.h"
#include "W5500.h"	

//���أ�192.168.1.1
//����:	255.255.255.0
//�����ַ��0C 29 AB 7C 00 01
//����IP��ַ:192.168.1.198
//�˿�0�Ķ˿ںţ�5000
//�˿�0��Ŀ��IP��ַ��192.168.1.190
//�˿�0��Ŀ�Ķ˿ںţ�6000

/*******************************************************************************
* ������  : W5500_Initialization
* ����    : W5500��ʼ������
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : ��
*******************************************************************************/
void W5500_Initialization(void)
{
	W5500_Init();		//��ʼ��W5500�Ĵ�������
	Detect_Gateway();	//������ط����� 
	Socket_Init(0);		//ָ��Socket(0~7)��ʼ��,��ʼ���˿�0
}

/*******************************************************************************
* ������  : Load_Net_Parameters
* ����    : װ���������
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : ���ء����롢�����ַ������IP��ַ���˿ںš�Ŀ��IP��ַ��Ŀ�Ķ˿ںš��˿ڹ���ģʽ
*******************************************************************************/
void Load_Net_Parameters(void)
{
	Gateway_IP[0] = 192;//�������ز���
	Gateway_IP[1] = 168;
	Gateway_IP[2] = 10;
	Gateway_IP[3] = 1;

	Sub_Mask[0]=255;//������������
	Sub_Mask[1]=255;
	Sub_Mask[2]=255;
	Sub_Mask[3]=0;

	Phy_Addr[0]=0x0c;//���������ַ
	Phy_Addr[1]=0x29;
	Phy_Addr[2]=0xab;
	Phy_Addr[3]=0x7c;
	Phy_Addr[4]=0x00;
	Phy_Addr[5]=0x01;

	IP_Addr[0]=192;//���ر���IP��ַ
	IP_Addr[1]=168;
	IP_Addr[2]=10;
	IP_Addr[3]=199;

	S0_Port[0] = 0x13;//���ض˿�0�Ķ˿ں�5000 
	S0_Port[1] = 0x88;

//	S0_DIP[0]=192;//���ض˿�0��Ŀ��IP��ַ
//	S0_DIP[1]=168;
//	S0_DIP[2]=1;
//	S0_DIP[3]=190;
//	
//	S0_DPort[0] = 0x17;//���ض˿�0��Ŀ�Ķ˿ں�6000
//	S0_DPort[1] = 0x70;

//	UDP_DIPR[0] = 192;	//UDP(�㲥)ģʽ,Ŀ������IP��ַ
//	UDP_DIPR[1] = 168;
//	UDP_DIPR[2] = 1;
//	UDP_DIPR[3] = 190;

//	UDP_DPORT[0] = 0x17;	//UDP(�㲥)ģʽ,Ŀ�������˿ں�
//	UDP_DPORT[1] = 0x70;

	S0_Mode=UDP_MODE;//���ض˿�0�Ĺ���ģʽ,UDPģʽ
}


/*******************************************************************************
* ������  : W5500_Socket_Set
* ����    : W5500�˿ڳ�ʼ������
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : �ֱ�����4���˿�,���ݶ˿ڹ���ģʽ,���˿�����TCP��������TCP�ͻ��˻�UDPģʽ.
*			�Ӷ˿�״̬�ֽ�Socket_State�����ж϶˿ڵĹ������
*******************************************************************************/
void W5500_Socket_Set(void)
{
	if(S0_State==0)//�˿�0��ʼ������
	{
		if(S0_Mode==TCP_SERVER)//TCP������ģʽ 
		{
			if(Socket_Listen(0)==TRUE)
				S0_State=S_INIT;
			else
				S0_State=0;
		}
		else if(S0_Mode==TCP_CLIENT)//TCP�ͻ���ģʽ 
		{
			if(Socket_Connect(0)==TRUE)
				S0_State=S_INIT;
			else
				S0_State=0;
		}
		else//UDPģʽ 
		{
			if(Socket_UDP(0)==TRUE)
				S0_State=S_INIT|S_CONN;
			else
				S0_State=0;
		}
	}
}


/*******************************************************************************
* ������  : Process_Socket_Data
* ����    : W5500���ղ����ͽ��յ�������
* ����    : s:�˿ں�
* ���    : ��
* ����ֵ  : ��
* ˵��    : �������ȵ���S_rx_process()��W5500�Ķ˿ڽ������ݻ�������ȡ����,
*			Ȼ�󽫶�ȡ�����ݴ�Rx_Buffer������Temp_Buffer���������д���
*			������ϣ������ݴ�Temp_Buffer������Tx_Buffer������������S_tx_process()
*			�������ݡ�
*******************************************************************************/
void Process_Socket_Data(SOCKET s)
{
	unsigned short size;
	size=Read_SOCK_Data_Buffer(s, Rx_Buffer);
	
	UDP_DIPR[0] = Rx_Buffer[0];
	UDP_DIPR[1] = Rx_Buffer[1];
	UDP_DIPR[2] = Rx_Buffer[2];
	UDP_DIPR[3] = Rx_Buffer[3];

	UDP_DPORT[0] = Rx_Buffer[4];
	UDP_DPORT[1] = Rx_Buffer[5];
	memcpy(Tx_Buffer, Rx_Buffer+8, size-8);			
	Write_SOCK_Data_Buffer(s, Tx_Buffer, size);
}

unsigned short Process_Socket_Data1(unsigned char *ch)
{
	unsigned short len = 0;
	W5500_Socket_Set();//W5500�˿ڳ�ʼ������

	W5500_Interrupt_Process();//W5500�жϴ��������
	if((S0_Data & S_RECEIVE) == S_RECEIVE)//���Socket0���յ�����
	{
			S0_Data&=~S_RECEIVE;
			len=Read_SOCK_Data_Buffer(0, Rx_Buffer);
	}
	if(len == 0)
		return 0;
//	memcpy(ch, Rx_Buffer+7, 10);	
	len=10;
	ch[0]=0;
	memcpy(ch,Rx_Buffer+8,10);
//	for(i=0;i<len;i++)
//	UART1SendByte(ch[i]);
	return len;
}

void W5500Pro_Initialization(void)
{
	SPI_Configuration();		//W5500 SPI��ʼ������(STM32 SPI1)
	W5500_GPIO_Configuration();	//W5500 GPIO��ʼ������	
	Load_Net_Parameters();		//װ���������	
	W5500_Hardware_Reset();		//Ӳ����λW5500
	W5500_Initialization();		//W5500��ʼ������
}

void TestW5500(void)
{
		W5500_Socket_Set();//W5500�˿ڳ�ʼ������

		W5500_Interrupt_Process();//W5500�жϴ��������
		
		if((S0_Data & S_RECEIVE) == S_RECEIVE)//���Socket0���յ�����
		{
			S0_Data&=~S_RECEIVE;
			Process_Socket_Data(0);//W5500���ղ����ͽ��յ�������
		}
}
void TestW5500TX(void)
{
		if(S0_State == (S_INIT|S_CONN))
		{
			S0_Data&=~S_TRANSMITOK;
			memcpy(Tx_Buffer, "\r\nGet msg\r\n", 27);
			Write_SOCK_Data_Buffer(0, Tx_Buffer, 27);//ָ��Socket(0~7)�������ݴ���,�˿�0����27�ֽ�����
		}
}

