#include "stmflash.h"
#include "stm32f10x_flash.h"
//#include "delay.h"
//#include "usart.h"
 
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F103ZE核心板
//STM32 FLASH 驱动代码	   
							  
//////////////////////////////////////////////////////////////////////////////////
 
//读取指定地址的半字(16位数据)
//faddr:读地址(此地址必须为2的倍数!!)
//返回值:对应数据.
//u16 STMFLASH_ReadHalfWord(u32 faddr)
//{
//	return *(vu16*)faddr; 
//}
//#if STM32_FLASH_WREN	//如果使能了写   
////不检查的写入
////WriteAddr:起始地址
////pBuffer:数据指针
////NumToWrite:半字(16位)数   
//void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
//{ 			 		 
//	u16 i;
//	for(i=0;i<NumToWrite;i++)
//	{
//		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
//	    WriteAddr+=2;//地址增加2.
//	}  
//} 
////从指定地址开始写入指定长度的数据
////WriteAddr:起始地址(此地址必须为2的倍数!!)
////pBuffer:数据指针
////NumToWrite:半字(16位)数(就是要写入的16位数据的个数.)
//#if STM32_FLASH_SIZE<256
//#define STM_SECTOR_SIZE 1024 //字节
//#else 
//#define STM_SECTOR_SIZE	2048
//#endif		 
//u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];//最多是2K字节
//void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
//{
//	u32 secpos;	   //扇区地址
//	u16 secoff;	   //扇区内偏移地址(16位字计算)
//	u16 secremain; //扇区内剩余地址(16位字计算)	   
// 	u16 i;    
//	u32 offaddr;   //去掉0X08000000后的地址
//	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//非法地址
//	FLASH_Unlock();						//解锁
//	offaddr=WriteAddr-STM32_FLASH_BASE;		//实际偏移地址.
//	secpos=offaddr/STM_SECTOR_SIZE;			//扇区地址  0~127 for STM32F103RBT6
//	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//在扇区内的偏移(2个字节为基本单位.)
//	secremain=STM_SECTOR_SIZE/2-secoff;		//扇区剩余空间大小   
//	if(NumToWrite<=secremain)secremain=NumToWrite;//不大于该扇区范围
//	while(1) 
//	{	
//		STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//读出整个扇区的内容
//		for(i=0;i<secremain;i++)//校验数据
//		{
//			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//需要擦除  	  
//		}
//		if(i<secremain)//需要擦除
//		{
//			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);//擦除这个扇区
//			for(i=0;i<secremain;i++)//复制
//			{
//				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
//			}
//			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//写入整个扇区  
//		}else STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
//		if(NumToWrite==secremain)break;//写入结束了
//		else//写入未结束
//		{
//			secpos++;				//扇区地址增1
//			secoff=0;				//偏移位置为0 	 
//		   	pBuffer+=secremain;  	//指针偏移
//			WriteAddr+=secremain;	//写地址偏移	   
//		   	NumToWrite-=secremain;	//字节(16位)数递减
//			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//下一个扇区还是写不完
//			else secremain=NumToWrite;//下一个扇区可以写完了
//		}	 
//	};	
//	FLASH_Lock();//上锁
//}
//#endif

////从指定地址开始读出指定长度的数据
////ReadAddr:起始地址
////pBuffer:数据指针
////NumToWrite:半字(16位)数
//void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
//{
//	u16 i;
//	for(i=0;i<NumToRead;i++)
//	{
//		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//读取2个字节.
//		ReadAddr+=2;//偏移2个字节.	
//	}
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////WriteAddr:起始地址
////WriteData:要写入的数据
//void Test_Write(u32 WriteAddr,u16 WriteData)   	
//{
//	STMFLASH_Write(WriteAddr,&WriteData,1);//写入一个字 
//}

//void WriteFlash(u32 WriteAddr,u16 WriteData)
//{
////	FLASH_Unlock();
////	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
////  FLASH_ErasePage(WriteAddr);
//	FLASH_ProgramHalfWord(WriteAddr,WriteData);
////	FLASH_Lock();
//}

//u16 ReadFlash(u32 WriteAddr)
//{
//	u16 BUF;
//	BUF = STMFLASH_ReadHalfWord(WriteAddr);
//	return BUF;
//}

///********************************************************
//**写flash内地址数据，数据长度必须是两个字节的倍数
//**WriteAddr：flash地址
//**ch：写入数据
//**Leng：数据长度
//**返回失败数据长度不是2的倍数
//*/

//u8 WriteFlashDate(u32 WriteAddr,u8 *ch,u8 Leng)
//{
//	u8 status = COMPLETE;
//	u16 i,DateLong,BUF,chLong;
//	chLong = Leng;
////	printf("chLong=%d\r\n",chLong);
//	if(chLong%2!=0)
//	{
//		status = FALSE;
//		Debug("Write FALSE\r\n",DEBUGLEVEL);
//		return status;
//	}
//	DateLong = chLong;
//	FLASH_Unlock();
//	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
//  FLASH_ErasePage(WriteAddr);
//	for(i=0;i<DateLong;)
//	{
//		BUF = ch[i+1]<<8|ch[i];
//		WriteFlash(WriteAddr+i*2,BUF);
////		printf("%x\r\n",BUF);
//		
////		BUF=ReadFlash(WriteAddr+(i*2));
////		printf("%x\r\n",BUF);
//		Debug("Write COMPLETE\r\n",DEBUGLEVEL);
//		i++;i++;
//	}
//	FLASH_Lock();
//	return status;
//}
///********************************************************
//**读取flash内地址数据，数据长度必须是两个字节的倍数
//**WriteAddr：地址
//**DateLong：数据长度
//*/
//u8 ReadFlashDate(u32 WriteAddr,u16 DateLong)
//{
//	u8 status = COMPLETE;
//	u16 i,BUF,temp;
////	printf("%d\r\n",DateLong);
//	if(DateLong%2!=0)
//	{
//		status = FALSE;
//		Debug("Read FALSE\r\n",DEBUGLEVEL);
//		return status;
//	}
//	for(i=0;i<DateLong;)
//	{
//		temp=ReadFlash(WriteAddr+(i*2));
//		BUF = (temp&0x00FF)<<8|temp>>8;
//		printf("%x\r\n",BUF);
//		i++;i++;
//	}
//	return status;
//}


///*******************************************************
//**falsh测试相关代码
//*/
////要写入到STM32 FLASH的字符串数组
//u8 TEXT_Buffer[]={
//	0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,
//	0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF,0X00
//};
//#define SIZE sizeof(TEXT_Buffer)		//数组长度
//#define FLASH_SAVE_ADDR  0X08010000		//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)


//void FlashTest(void)
//{
//	Debug("FlashTest\r\n",DEBUGLEVEL);
//	WriteFlashDate(FLASH_SAVE_ADDR,TEXT_Buffer,sizeof(TEXT_Buffer));
//	OSTimeDlyHMSM(0, 0,0,600);
//	ReadFlashDate(FLASH_SAVE_ADDR,sizeof(TEXT_Buffer));
//	OSTimeDlyHMSM(0, 0,0,600);
//		
//}

//void FlashWriteW5500(void)
//{
//	;
////	WriteFlashDate(FLASH_SAVE_ADDR,ch,Leng);
////	FLASH_Unlock();
////	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
////  FLASH_ErasePage(WriteAddr);
//}


