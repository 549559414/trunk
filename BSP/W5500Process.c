#include <string.h>
#include "W5500Process.h"
#include "W5500.h"	

//网关：192.168.1.1
//掩码:	255.255.255.0
//物理地址：0C 29 AB 7C 00 01
//本机IP地址:192.168.1.198
//端口0的端口号：5000
//端口0的目的IP地址：192.168.1.190
//端口0的目的端口号：6000

/*******************************************************************************
* 函数名  : W5500_Initialization
* 描述    : W5500初始货配置
* 输入    : 无
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void W5500_Initialization(void)
{
	W5500_Init();		//初始化W5500寄存器函数
	Detect_Gateway();	//检查网关服务器 
	Socket_Init(0);		//指定Socket(0~7)初始化,初始化端口0
}

/*******************************************************************************
* 函数名  : Load_Net_Parameters
* 描述    : 装载网络参数
* 输入    : 无
* 输出    : 无
* 返回值  : 无
* 说明    : 网关、掩码、物理地址、本机IP地址、端口号、目的IP地址、目的端口号、端口工作模式
*******************************************************************************/
void Load_Net_Parameters(void)
{
	Gateway_IP[0] = 192;//加载网关参数
	Gateway_IP[1] = 168;
	Gateway_IP[2] = 10;
	Gateway_IP[3] = 1;

	Sub_Mask[0]=255;//加载子网掩码
	Sub_Mask[1]=255;
	Sub_Mask[2]=255;
	Sub_Mask[3]=0;

	Phy_Addr[0]=0x0c;//加载物理地址
	Phy_Addr[1]=0x29;
	Phy_Addr[2]=0xab;
	Phy_Addr[3]=0x7c;
	Phy_Addr[4]=0x00;
	Phy_Addr[5]=0x01;

	IP_Addr[0]=192;//加载本机IP地址
	IP_Addr[1]=168;
	IP_Addr[2]=10;
	IP_Addr[3]=199;

	S0_Port[0] = 0x13;//加载端口0的端口号5000 
	S0_Port[1] = 0x88;

//	S0_DIP[0]=192;//加载端口0的目的IP地址
//	S0_DIP[1]=168;
//	S0_DIP[2]=1;
//	S0_DIP[3]=190;
//	
//	S0_DPort[0] = 0x17;//加载端口0的目的端口号6000
//	S0_DPort[1] = 0x70;

//	UDP_DIPR[0] = 192;	//UDP(广播)模式,目的主机IP地址
//	UDP_DIPR[1] = 168;
//	UDP_DIPR[2] = 1;
//	UDP_DIPR[3] = 190;

//	UDP_DPORT[0] = 0x17;	//UDP(广播)模式,目的主机端口号
//	UDP_DPORT[1] = 0x70;

	S0_Mode=UDP_MODE;//加载端口0的工作模式,UDP模式
}


/*******************************************************************************
* 函数名  : W5500_Socket_Set
* 描述    : W5500端口初始化配置
* 输入    : 无
* 输出    : 无
* 返回值  : 无
* 说明    : 分别设置4个端口,根据端口工作模式,将端口置于TCP服务器、TCP客户端或UDP模式.
*			从端口状态字节Socket_State可以判断端口的工作情况
*******************************************************************************/
void W5500_Socket_Set(void)
{
	if(S0_State==0)//端口0初始化配置
	{
		if(S0_Mode==TCP_SERVER)//TCP服务器模式 
		{
			if(Socket_Listen(0)==TRUE)
				S0_State=S_INIT;
			else
				S0_State=0;
		}
		else if(S0_Mode==TCP_CLIENT)//TCP客户端模式 
		{
			if(Socket_Connect(0)==TRUE)
				S0_State=S_INIT;
			else
				S0_State=0;
		}
		else//UDP模式 
		{
			if(Socket_UDP(0)==TRUE)
				S0_State=S_INIT|S_CONN;
			else
				S0_State=0;
		}
	}
}


/*******************************************************************************
* 函数名  : Process_Socket_Data
* 描述    : W5500接收并发送接收到的数据
* 输入    : s:端口号
* 输出    : 无
* 返回值  : 无
* 说明    : 本过程先调用S_rx_process()从W5500的端口接收数据缓冲区读取数据,
*			然后将读取的数据从Rx_Buffer拷贝到Temp_Buffer缓冲区进行处理。
*			处理完毕，将数据从Temp_Buffer拷贝到Tx_Buffer缓冲区。调用S_tx_process()
*			发送数据。
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
	W5500_Socket_Set();//W5500端口初始化配置

	W5500_Interrupt_Process();//W5500中断处理程序框架
	if((S0_Data & S_RECEIVE) == S_RECEIVE)//如果Socket0接收到数据
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
	SPI_Configuration();		//W5500 SPI初始化配置(STM32 SPI1)
	W5500_GPIO_Configuration();	//W5500 GPIO初始化配置	
	Load_Net_Parameters();		//装载网络参数	
	W5500_Hardware_Reset();		//硬件复位W5500
	W5500_Initialization();		//W5500初始货配置
}

void TestW5500(void)
{
		W5500_Socket_Set();//W5500端口初始化配置

		W5500_Interrupt_Process();//W5500中断处理程序框架
		
		if((S0_Data & S_RECEIVE) == S_RECEIVE)//如果Socket0接收到数据
		{
			S0_Data&=~S_RECEIVE;
			Process_Socket_Data(0);//W5500接收并发送接收到的数据
		}
}
void TestW5500TX(void)
{
		if(S0_State == (S_INIT|S_CONN))
		{
			S0_Data&=~S_TRANSMITOK;
			memcpy(Tx_Buffer, "\r\nGet msg\r\n", 27);
			Write_SOCK_Data_Buffer(0, Tx_Buffer, 27);//指定Socket(0~7)发送数据处理,端口0发送27字节数据
		}
}

