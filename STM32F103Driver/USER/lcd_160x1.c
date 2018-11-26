/****************************************Copyright (c)**************************************************
**                               Hunan EUTRON information Equipment Co.,LTD.
**
**                                 http://www.eutron.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:       LCD_Drv.c
** Descriptions:    S6A0069����
**
**------------------------------------------------------------------------------------------------------
** Created by:      Ruby
** Created date:    2011-12-05
** Version:         1.0
** Descriptions:    The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
********************************************************************************************************/
#include "stm32f10x.h"
#include "lcd_160x1.h"
#include "fsmc_sram.h"
#include "SysTick.h"

#include <string.h>  //ouhs 20140815

#define LCD_D0	GPIO_Pin_8
#define LCD_D1	GPIO_Pin_9
#define LCD_D2	GPIO_Pin_10
#define LCD_D3	GPIO_Pin_11
#define LCD_DataPort	GPIOF

#define LCDC_E	GPIO_Pin_15//GPIO_Pin_14  //Customer
#define LCDO_E	GPIO_Pin_14//GPIO_Pin_15  //Operator
#define LCD_E_Port		GPIOG

#define LCD_RS	GPIO_Pin_7
#define LCD_RW	GPIO_Pin_6
#define LCD_BL	GPIO_Pin_2

#define	RS_Low()	GPIOF->BRR =	LCD_RS
#define	RS_High()	GPIOF->BSRR =	LCD_RS

#define	RW_Low()	GPIOF->BRR =	LCD_RW
#define	RW_High()	GPIOF->BSRR =	LCD_RW

#define	C_E_Low()		LCD_E_Port->BRR =	LCDC_E
#define	C_E_High()	LCD_E_Port->BSRR =	LCDC_E
#define	O_E_Low()		LCD_E_Port->BRR =	LCDO_E
#define	O_E_High()	LCD_E_Port->BSRR =	LCDO_E
#if defined(CASE_ITALIA)
const char  Disp[] = "   ECR - 1001   ";
#elif defined(CASE_MALTA)
const char  Disp[] = "                ";
#else
const char  Disp[] = "LCD System Ready";
#endif
char SaveDispO[DISLEN],SaveDispC[DISLEN];//������ʾ����

volatile uint8_t LCD_BL_CTRL;

void LCD_CheckBusy(uint8_t LCDn);
void LCD_ModeInit4Bit(uint8_t LCDn);
void PutsO_Only(const char *str);
void PutsC_Only(const char *str);
void LCD160x_Test(void);

// ��ʱ1ms
void LCD160x_Delay_ms(uint16_t cnt)
{
	uint16_t i;
	while (cnt--)
		for(i=0; i<12000; i++);
}

void LCD160x_Dly80ns(uint8_t cnt)
{
	while(cnt--)
		__NOP(); // __NOP()Լ80ns
}

// ����4bit����
void LCD_Sendbit(uint16_t ch)
{
	ch <<= 8;
	LCD_DataPort->BSRR = ch;
	LCD_DataPort->BRR = (~ch)&0xF00;

}

// �������ݵ�LCD
void LCD_SendData(uint8_t LCDn, uint8_t data)
{
	if(LCDn)
		C_E_Low();
	else
		O_E_Low();

	LCD_Sendbit(data);
	//LCD160x_Dly80ns(1);
	if(LCDn)
		C_E_High();
	else
		O_E_High();
	LCD160x_Dly80ns(5);	 //410ns

	if(LCDn)
		C_E_Low();
	else
		O_E_Low();
	LCD160x_Dly80ns(1);
}

// ����4λ������ģʽ
void LCD_ModeInit4Bit(uint8_t LCDn)
{
	RW_Low();
	RS_Low();
	LCD_SendData(LCDn, 0x02);		// ���0x28  4bit,16x1-line,5x8dots
	LCD_SendData(LCDn, 0x08);
}

// ��ȡ״̬��־
void LCD_CheckBusy(uint8_t LCDn)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	uint8_t ReadData, ReadData_H, ReadData_L;
	uint16_t temp = 0xfff;

  LCD_DataPort->BSRR = LCD_D0 | LCD_D1 | LCD_D2 | LCD_D3; //����1�ٶ�ȡ

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = LCD_D0 | LCD_D1 | LCD_D2 | LCD_D3;
	GPIO_Init(LCD_DataPort, &GPIO_InitStructure);
	RW_High();
	RS_Low();
	do{

		if(LCDn)
			C_E_High();
		else
			O_E_High();
		LCD160x_Dly80ns(5);
		ReadData_H = (LCD_DataPort->IDR)>>4;	// Pin11|Pin10|Pin9|Pin8

		if(LCDn)
			C_E_Low();
		else
			O_E_Low();
		LCD160x_Dly80ns(5);
	   	if(LCDn)
			C_E_High();
		else
			O_E_High();
		LCD160x_Dly80ns(5);
		ReadData_L = (LCD_DataPort->IDR)>>8;	// Pin11|Pin10|Pin9|Pin8
		
		if(LCDn)
			C_E_Low();
		else
			O_E_Low();
		LCD160x_Dly80ns(5);

		ReadData = ((ReadData_H) | (ReadData_L & 0x0F));
	}while((ReadData & 0x80) && (temp--));

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LCD_DataPort, &GPIO_InitStructure);
}


// д����
uint8_t LCD_WRCmd(uint8_t LCDn, uint8_t commmand)
{
	LCD_CheckBusy(LCDn);
	RW_Low();
	RS_Low();
   	LCD_SendData(LCDn, commmand>>4);	   // �ȷ��͸�4λ
	LCD_SendData(LCDn, commmand&0x0F);	   // ���͵�4λ
	return 1;
}

// д����
uint8_t LCD_WRData(uint8_t LCDn, uint8_t data)
{
	LCD_CheckBusy(LCDn);
	RW_Low();
	RS_High();
   	LCD_SendData(LCDn, data>>4);	   // �ȷ��͸�4λ
	LCD_SendData(LCDn, data&0x0F);	   // ���͵�4λ
	return 1;
}

void LCD_Pos(uint8_t LCDn, uint8_t pos)
{
	pos &= 0x0f;
	if(pos<8)
		LCD_WRCmd(LCDn, pos | 0x80);
	else
		LCD_WRCmd(LCDn, (pos&0x07)|0xC0);
}

void LCD160x_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = LCD_D0 | LCD_D1 | LCD_D2 | LCD_D3 | LCD_RS | LCD_RW;
	GPIO_Init(LCD_DataPort, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LCD_BL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LCDC_E | LCDO_E;
	GPIO_Init(LCD_E_Port, &GPIO_InitStructure);
	O_E_Low();
	C_E_Low();
}


void LCDInit(void)
{
	LCD160x_IO_Init();

	// ��ʼ����ʾģʽ����4��
	LCD_ModeInit4Bit(0);	// 4bit, 16x1-line, 5x8dots
	LCD_ModeInit4Bit(1);
	LCD160x_Delay_ms(3);		// 3ms

	LCD_ModeInit4Bit(0);
	LCD_ModeInit4Bit(1);
	LCD160x_Delay_ms(3);
	/*
	LCD_ModeInit4Bit(0);
	LCD_ModeInit4Bit(1);
	LCD160x_Delay_ms(3);
	LCD_ModeInit4Bit(0);
	LCD_ModeInit4Bit(1);
	LCD160x_Delay_ms(3);
	*/
	LCD_WRCmd(0, 0x08);		// ����ʾ
	LCD_WRCmd(1, 0x08);
	LCD_WRCmd(0, 0x01);		// ����
	LCD_WRCmd(1, 0x01);
	LCD160x_Delay_ms(3);	// 3ms

	LCD_WRCmd(0, 0x06);		// д�������ݺ�,��������ƶ�,���治�ƶ�
	LCD_WRCmd(1, 0x06);

	LCD_WRCmd(0, 0x0c);		// ��ʾ���ܿ����й�ꡢ ����˸
	LCD_WRCmd(1, 0x0c);

	LCDOpen();			//������
    LCD_BL_CTRL |= 2;//=1,������������ʾ��ͬ������

	PutsO_Only(Disp);
	//LCD160x_Test();
}

#if 0
const char  Disp1[] = "0123456789abcdef";
void LCD160x_Test(void)
{
	uint8_t i;
	while(1)
	{
		for(i=0; i<50; i++)
		{
			PutsO_Only(Disp1);
			PutsO_Only(Disp);
		}
		LCD160x_Delay_ms(1000);

	}}
#endif

void LCDClose(void)
{
	LCD_BL_OFF();

	LCD_WRCmd(0, 0x01);
	LCD_WRCmd(1, 0x01);
}

void LCDOpen(void)
{
	LCD_BL_ON();
}

void PutsC(const char *str)
{//�ڹ˿���ʾ��Ļ����ʾ����,16λ1����ʾ
	unsigned char addr = 0;

	memset(SaveDispC,' ',DISLEN);

	LCD_WRCmd(1, 0x01);
	//LCD160x_Delay_ms(3);	// 3ms
	for(;*str!=0;str++) //��Ҫ�޸Ľ����ַ���ʶ
	{
		LCD_Pos(1, addr);
		LCD_WRData(1, *str);
		SaveDispC[addr]=*str;
        if( ++addr >= DISLEN)
			break;
	}
}

void PutsC_Only(const char *str)
{//�ڹ˿���ʾ��Ļ����ʾ����,16λ1����ʾ
	unsigned char addr = 0;

	LCD_WRCmd(1, 0x01);
	//LCD160x_Delay_ms(3);
	for(;*str!=0;str++) //��Ҫ�޸Ľ����ַ���ʶ
	{
		LCD_Pos(1, addr);
		LCD_WRData(1, *str);
        if( ++addr >= DISLEN)
			break;
	}
}

//��ʾ������������
void PutsC_Saved(void)
{
	PutsC_Only(SaveDispC);
}

//ֻ��ʾ��ͬʱ��������
void PutsO(const char *str)
{//�ڲ���Ա��ʾ��Ļ����ʾ����,16λ1����ʾ
	unsigned char addr = 0;


	PutsC(str);

	memset(SaveDispO,' ',DISLEN);
	LCD_WRCmd(0, 0x01);
	//LCD160x_Delay_ms(3);
	for(;*str!=0;str++) //��Ҫ�޸Ľ����ַ���ʶ
	{
		LCD_Pos(0, addr);
		SaveDispO[addr]=*str;
		LCD_WRData(0, *str);
		if( ++addr >= DISLEN)
			break;
	}
}

uint8_t GetsO_At(uint8_t addr)
{
    if (addr<DISLEN)
        return SaveDispO[addr];
    else
        return 0xff;
}

////ccr20131120 ����Ļ��һ��ָ��λ����ʾ�ַ�
void PutsO_At(uint8_t ch,uint8_t addr)
{//�ڲ���Ա��ʾ��Ļ����ʾ����,16λ1����ʾ

	//LCD_WRCmd(0, 0x01);
	//LCD160x_Delay_ms(3);
    if (addr<DISLEN)
    {
        SaveDispO[addr] = ch;
        addr=0;
        LCD_WRCmd(0, 0x01);
        for(addr=0;addr<DISLEN;addr++) //��Ҫ�޸Ľ����ַ���ʶ
        {
            LCD_Pos(0, addr);
            //skip LCD_Pos(0, 1, addr);
            LCD_WRData(0, SaveDispO[addr]);
        }
    }
}

//ֻ��ʾ������������
void PutsO_Only(const char *str)
{//�ڲ���Ա��ʾ��Ļ����ʾ����,16λ1����ʾ
	unsigned char addr = 0;

	PutsC_Only(str);

	LCD_WRCmd(0, 0x01);
	//LCD160x_Delay_ms(3);
	for(;*str!=0;str++) //��Ҫ�޸Ľ����ַ���ʶ
	{
		LCD_Pos(0, addr);
		LCD_WRData(0, *str);
		if( ++addr >= DISLEN)
			break;
	}
}

//��ʾ������������
void PutsO_Saved(void)
{
	PutsO_Only(SaveDispO);
	PutsC_Only(SaveDispO);
}

//������LCD����ʾ��nrong����
void Save_LCD(char *saveO,char *saveC)
{
	memcpy(saveO,SaveDispO,sizeof(SaveDispO));
	memcpy(saveC,SaveDispC,sizeof(SaveDispC));
}
/*********************************************************************************************************
** End Of File
*********************************************************************************************************/
