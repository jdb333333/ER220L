/*****************************************************************************
 *   typedef.h:  Type definition Header file for NXP LPC17xx Family
 *   Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.25  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/

#ifndef __TYPE_H__
#define __TYPE_H__

#include <stdint.h>  //ouhs 20140814

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef CONST
#define CONST    const
#endif

#ifndef false
#define false   (0)
#endif

#ifndef true
#define true    (1)
#endif

/*ouhs20160406
#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif
*/

/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

#if defined(DEBUGBYPC)
/* These types must be 8-bit integer */
typedef char			CHAR;
typedef signed char		SCHAR;
typedef unsigned char	UCHAR;
typedef unsigned char   uchar;

/* These types must be 16-bit integer */
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WCHAR;
/* These types must be 32-bit integer */
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;


typedef unsigned char	BYTE;
typedef unsigned short	WORD;

#else
/* These types must be 8-bit integer */
typedef char		CHAR;
typedef int8_t		schar;
typedef int8_t		SCHAR;
typedef uint8_t	    UCHAR;
typedef uint8_t     uchar;
typedef uint8_t	    BYTE;


/* These types must be 16-bit integer */
typedef int16_t		SHORT;
typedef uint16_t	USHORT;
typedef uint16_t	WORD;
//typedef unsigned short	WCHAR;

/* These types must be 32-bit integer */
typedef int32_t		LONG;
typedef uint32_t	ULONG;
typedef uint32_t	DWORD;
#endif

/* RTC timer strcuture ccr2014-10-14 */
typedef struct {
    int     sec;     /* Second value - [0,59] */
    int     min;     /* Minute value - [0,59] */
    int     hour;    /* Hour value - [0,23] */
    int     mday;    /* Day of the month value - [1,31] */
	int     wday;    /* Day of week value - [0,6] */
    int     mon;     /* Month value - [1,12] */
    int    year;    /* Year value - [0,4095] */
} RTCTime;
///////////////////////////////////////////////////////////////

#define BIT0	0x00000001
#define BIT1	0x00000002
#define BIT2	0x00000004
#define BIT3	0x00000008
#define BIT4	0x00000010
#define BIT5	0x00000020
#define BIT6	0x00000040
#define BIT7	0x00000080
#define BIT8	0x00000100
#define BIT9	0x00000200
#define BIT10	0x00000400
#define BIT11	0x00000800
#define BIT12	0x00001000
#define BIT13	0x00002000
#define BIT14	0x00004000
#define BIT15	0x00008000
#define BIT16	0x00010000L
#define BIT17	0x00020000L
#define BIT18	0x00040000L
#define BIT19	0x00080000L
#define BIT20	0x00100000L
#define BIT21	0x00200000L
#define BIT22	0x00400000L
#define BIT23	0x00800000L
#define BIT24	0x01000000L
#define BIT25	0x02000000L
#define BIT26	0x04000000L
#define BIT27	0x08000000L
#define BIT28	0x10000000L
#define BIT29	0x20000000L
#define BIT30	0x40000000L
#define BIT31	0x80000000L

#define BIT(w,i)	    (w & (i))       //test bit on w
#define SETBIT(w,i)	    (w |= (i))      //set bit on w
#define CLRBIT(w,i)	    (w &= ~(i))     //clear bit on w
#define INVBIT(w,i)	    (w ^= (i))      //incert bit on w

#define SOH		0x01
#define STX		0x02
#define ETX		0x03
#define EOT		0x04
#define ENQ		0x05
#define ACK		0x06
#define BEL		0x07
#define LF		0x0A
#define VT		0x0B
#define FF		0x0C
#define CRET		0x0D
#define SO		0x0E
#define SI		0x0F
#define DLE		0x10
#define XON     0x11
#define DC1		0x11
#define DC2		0x12
#define DC3		0x13
#define XOFF    0x13
#define DC4		0x14
#define NAK	    0x15
#define ETB	    0x17
#define DEL	    0x18
#define CAN		0x18
#define WAIT	0x1b
#define ESC	    0x1b
#define FS		0x1C
#define GS		0x1D

#define CWORD(a) (*(WORD*)&a)
#define CLONG(a) (*(ULONG*)&a)

/*Attributes for graphics:
    ͼƬ��ͷ��Ϊ�ı�����,���ֽ�������Ϊ (cLabels) * (cByteALine + 1);
�ı��Ĵ洢��ʽΪ: cByteALine���ֽ�Ϊ�ַ�����,������һ���ֽڱ�ʾ��Ч�ַ�����

Graphic:Offset_of_Dots = (cLabels) * (cByteALine + 1);ͼ�������ͼƬ�е�λ��
Graphic:Size_In_Bytes = cGrapSize-Offset_of_Dots;   ͼ�������ֽ���
Graphic:Width_In_Bytes = cGrapCols*cWidthAChar/8;   ÿ��ͼ�������ֽ���
Graphic:Dots_Line_Max = Size_In_Bytes / Width_In_Bytes; ͼ���������

*/
struct GRAPH_DEFINE
{
    unsigned short cGrapCols;   // ͼƬ���(���ַ���λ,ÿ���ַ��Ŀ��ΪcWidthAChar)
    unsigned short cLabels;     // ͼƬ�а����ĵ�����������
    unsigned short cPrintAt;    // ͼƬĬ�ϴ�ӡλ��
    unsigned short cWidthAChar; // �����ַ��Ŀ��(����)
    unsigned short cHighAChar;  // �ַ�����߶�(��ʱû��ʹ��)
    unsigned short cByteALine;  // ��ӡֽ�Ŀ��(���ַ���λ)
    unsigned long cGrapSize;    // ͼ�������ֽ���=ͼ������ֽ���+(cByteALine+1)*cLabels
                                // ͼ�����ʼλ��Ϊ:(cByteALine+1)*cLabels
};

/*
    ���տ��ͼƬ.GRB���ļ�ͷ����,�޵�������ʱ,û��6,7,8,9����(5�ֽ�).
*/
#pragma pack(1)
struct GRB_DEFINE
{
    BYTE cTextFlag;         //0 �����ı��ı�־��#80h��ʾ��
    BYTE cWidth;            //1 ͼ�ο�ȣ��ֽ���
    BYTE cHeight;           //2 ͼ��������ʵ�ʸ߶�ΪcHeight*cHighAChar����
    BYTE cPrintAt;          //3 ͼ�δ�ӡλ��(����߽����)
    BYTE cLabels;           //4 ͼ�����ַ�����
    WORD cTextOffset;       //5,6 �ı����ĵ�ַ
    BYTE cHighAChar;        //7 �иߣ�����
    WORD cGraSize;          //8,9 ����:ͼ������ֽ���
    char cName[128];        //10 �ļ���������
};
#pragma pack(4)
#endif  /* __TYPE_H__ */
