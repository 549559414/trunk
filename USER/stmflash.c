#include "stmflash.h"
#include "stm32f10x_flash.h"
//#include "delay.h"
//#include "usart.h"
 
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F103ZE���İ�
//STM32 FLASH ��������	   
							  
//////////////////////////////////////////////////////////////////////////////////
 
//��ȡָ����ַ�İ���(16λ����)
//faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
//����ֵ:��Ӧ����.
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}
#if STM32_FLASH_WREN	//���ʹ����д   
//������д��
//WriteAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToWrite:����(16λ)��   
void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;//��ַ����2.
	}  
} 
//��ָ����ַ��ʼд��ָ�����ȵ�����
//WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
//pBuffer:����ָ��
//NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //�ֽ�
#else 
#define STM_SECTOR_SIZE	2048
#endif		 
u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];//�����2K�ֽ�
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	   //������ַ
	u16 secoff;	   //������ƫ�Ƶ�ַ(16λ�ּ���)
	u16 secremain; //������ʣ���ַ(16λ�ּ���)	   
 	u16 i;    
	u32 offaddr;   //ȥ��0X08000000��ĵ�ַ
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//�Ƿ���ַ
	FLASH_Unlock();						//����
	offaddr=WriteAddr-STM32_FLASH_BASE;		//ʵ��ƫ�Ƶ�ַ.
	secpos=offaddr/STM_SECTOR_SIZE;			//������ַ  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//����ʣ��ռ��С   
	if(NumToWrite<=secremain)secremain=NumToWrite;//�����ڸ�������Χ
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);//�����������
			for(i=0;i<secremain;i++)//����
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//д����������  
		}else STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;				//������ַ��1
			secoff=0;				//ƫ��λ��Ϊ0 	 
		   	pBuffer+=secremain;  	//ָ��ƫ��
			WriteAddr+=secremain;	//д��ַƫ��	   
		   	NumToWrite-=secremain;	//�ֽ�(16λ)���ݼ�
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//��һ����������д����
			else secremain=NumToWrite;//��һ����������д����
		}	 
	};	
	FLASH_Lock();//����
}
#endif

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToWrite:����(16λ)��
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//��ȡ2���ֽ�.
		ReadAddr+=2;//ƫ��2���ֽ�.	
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//WriteAddr:��ʼ��ַ
//WriteData:Ҫд�������
void Test_Write(u32 WriteAddr,u16 WriteData)   	
{
	STMFLASH_Write(WriteAddr,&WriteData,1);//д��һ���� 
}

void WriteFlash(u32 WriteAddr,u16 WriteData)
{
//	FLASH_Unlock();
//	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
//  FLASH_ErasePage(WriteAddr);
	FLASH_ProgramHalfWord(WriteAddr,WriteData);
//	FLASH_Lock();
}

u16 ReadFlash(u32 WriteAddr)
{
	u16 BUF;
	BUF = STMFLASH_ReadHalfWord(WriteAddr);
	return BUF;
}

/********************************************************
**дflash�ڵ�ַ���ݣ����ݳ��ȱ����������ֽڵı���
**WriteAddr��flash��ַ
**ch��д������
**Leng�����ݳ���
**����ʧ�����ݳ��Ȳ���2�ı���
*/

u8 WriteFlashDate(u32 WriteAddr,u8 *ch,u8 Leng)
{
	u8 status = COMPLETE;
	u16 i,DateLong,BUF,chLong;
	chLong = Leng;
//	printf("chLong=%d\r\n",chLong);
	if(chLong%2!=0)
	{
		status = FALSE;
		Debug("Write FALSE\r\n",DEBUGLEVEL);
		return status;
	}
	DateLong = chLong;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
  FLASH_ErasePage(WriteAddr);
	for(i=0;i<DateLong;)
	{
		BUF = ch[i+1]<<8|ch[i];
		WriteFlash(WriteAddr+i*2,BUF);
//		printf("%x\r\n",BUF);
		
//		BUF=ReadFlash(WriteAddr+(i*2));
//		printf("%x\r\n",BUF);
		Debug("Write COMPLETE\r\n",DEBUGLEVEL);
		i++;i++;
	}
	FLASH_Lock();
	return status;
}
/********************************************************
**��ȡflash�ڵ�ַ���ݣ����ݳ��ȱ����������ֽڵı���
**WriteAddr����ַ
**DateLong�����ݳ���
*/
u8 ReadFlashDate(u32 WriteAddr,u16 DateLong)
{
	u8 status = COMPLETE;
	u16 i,BUF,temp;
//	printf("%d\r\n",DateLong);
	if(DateLong%2!=0)
	{
		status = FALSE;
		Debug("Read FALSE\r\n",DEBUGLEVEL);
		return status;
	}
	for(i=0;i<DateLong;)
	{
		temp=ReadFlash(WriteAddr+(i*2));
		BUF = (temp&0x00FF)<<8|temp>>8;
		printf("%x\r\n",BUF);
		i++;i++;
	}
	return status;
}


/*******************************************************
**falsh������ش���
*/
//Ҫд�뵽STM32 FLASH���ַ�������
u8 TEXT_Buffer[]={
	0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,
	0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,0X00
};
#define SIZE sizeof(TEXT_Buffer)		//���鳤��
#define FLASH_SAVE_ADDR  0X08010000		//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)


void FlashTest(void)
{
	Debug("FlashTest\r\n",DEBUGLEVEL);
	WriteFlashDate(FLASH_SAVE_ADDR,TEXT_Buffer,sizeof(TEXT_Buffer));
	OSTimeDlyHMSM(0, 0,0,600);
	ReadFlashDate(FLASH_SAVE_ADDR,sizeof(TEXT_Buffer));
	OSTimeDlyHMSM(0, 0,0,600);
		
}











