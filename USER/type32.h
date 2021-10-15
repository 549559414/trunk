 /******************************************************************************
 * File��			type32.h
 * Brief��    		32λϵͳ�����Ͷ���
 * Author:			tao.lan
 * Date:			2011-8-9 created
 * Description:		ͨ���������Ͷ��壬����lzw Type32bit.h��д
 ******************************************************************************/
 
#ifndef __TYPE32_H
#define	__TYPE32_H

//////////////////////////////////////////////////////////////////////////////////
// ����32λ�����µ�ͨ������
//////////////////////////////////////////////////////////////////////////////////

typedef	unsigned char			U8;
typedef	unsigned char			u8;
typedef U8*						P_U8;
typedef signed char				S8;
typedef S8*						P_S8;
typedef unsigned short			U16;
typedef unsigned short			u16;
typedef U16*					P_U16;
typedef signed short			S16;
typedef S16*					P_S16;
typedef unsigned long			U32;
typedef U32*					P_U32;
typedef signed long				S32;
typedef S32*					P_S32;
typedef void*					P_VOID;

#define FALSE					0
#define SUCCEED				1
#define COMPLETE			1
#define MAX_LENGTH		1024

#endif //__TYPE32_H
