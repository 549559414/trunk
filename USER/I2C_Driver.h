#ifndef __I2C_Driver_H
#define __I2C_Driver_H

/* Includes ------------------------------------------------------------------*/
#include "type32.h"

#define SCL_H         GPIOB->BSRR = GPIO_Pin_6
#define SCL_L         GPIOB->BRR  = GPIO_Pin_6 
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_7
#define SDA_L         GPIOB->BRR  = GPIO_Pin_7

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6
#define SDA_read      GPIOB->IDR  & GPIO_Pin_7

#define I2C_PageSize  8  //24C02Ã¿Ò³8×Ö½Ú

void I2C_GPIO_Config(void);
U8 I2C_WriteByte(u8 SendByte, u16 WriteAddress, u8 DeviceAddress);
U8 I2C_BufferWrite(u8* pBuffer, u8 length,     u16 WriteAddress, u8 DeviceAddress);
void I2C_PageWrite(  u8* pBuffer, u8 length,     u16 WriteAddress, u8 DeviceAddress);
U8 I2C_ReadByte(u8* pBuffer,   u8 length,     u16 ReadAddress,  u8 DeviceAddress);

void AT24C04_WritePage(void);
void AT24C04_ReadPage(void);
void AT24C04_Test(void);

#endif 



