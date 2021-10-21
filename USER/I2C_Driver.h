#ifndef __I2C_Driver_H
#define __I2C_Driver_H

/* Includes ------------------------------------------------------------------*/
#include "type32.h"

#define SCL_H         GPIOB->BSRR = GPIO_Pin_9
#define SCL_L         GPIOB->BRR  = GPIO_Pin_9 
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_8
#define SDA_L         GPIOB->BRR  = GPIO_Pin_8

#define SCL_read      GPIOB->IDR  & GPIO_Pin_9
#define SDA_read      GPIOB->IDR  & GPIO_Pin_8

#define I2C_PageSize  8  //24C02ÿҳ8�ֽ�

#define DS1307ADDR					0xD0

#define NOCOMMAND			0x00
#define GETCOMMAND		0x01

void I2C_GPIO_Config(void);
U8 I2C_WriteByte(u8 SendByte, u16 WriteAddress, u8 DeviceAddress);
U8 I2C_BufferWrite(u8* pBuffer, u8 length,     u16 WriteAddress, u8 DeviceAddress);
void I2C_PageWrite(  u8* pBuffer, u8 length,     u16 WriteAddress, u8 DeviceAddress);
U8 I2C_ReadByte(u8* pBuffer,   u8 length,     u16 ReadAddress,  u8 DeviceAddress);

void AT24C04_WritePage(void);
void AT24C04_ReadPage(void);
void AT24C04_Test(void);

u8 SetTime(void);
void TestDS1307(void);

#endif 



