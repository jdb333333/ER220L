
#include <stdint.h>
#include "king.h"
#include "exthead.h"
//#include "exth.h"

#include "stm32f10x.h"
#include "TypeDef.h"
#include "lcd_st7565r.h"
#include "Flashb.h"

#ifdef CHAR_6X8

#define Y_Height	8
#define X_Width		6
extern const uint8_t ASCIITAB_5x8[ ];

#else
#define Y_Height	16			// ����߶�
#define X_Width		8				// ������С���
#endif

uint8_t ActiveLines = SCREENLN;

uint8_t DotBuffer[8][128]; //page addr:8  column addr:128

const uint8_t pagemap[8] = {3, 2, 1, 0, 7, 6, 5, 4,};
extern const uint8_t ASCIITAB_8x16[];
extern const uint8_t RByte[256];

void ST7565R_IO_Init(void);
void ST7565R_WR_CMD(uint8_t cmd);
void ST7565R_WR_DATA(uint8_t dat);
void st7565SetXY(uint8_t pos_x,uint8_t pos_y);
void st7565DrawPixel( uint8_t x, uint8_t y );
void st7565ClearPixel( uint8_t x, uint8_t y );
void st7565Refresh( void );
void mDispLogo(void);


extern uint8_t NorFlash_WReadBuffer(uint16_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead);

/**************************************************************************/
/*  ��ʱԼ1ms
***************************************************************************/
void ST7565R_Delay_ms(uint16_t cnt)
{
	uint16_t i;
	while (cnt--)
		for(i=0; i<20000; i++);
}

void ST7565R_NOP(void)
{
	uint8_t cnt=30/*20*/;
	while(cnt--)
		__NOP(); // __NOP()Լ5~6ns
}
/**************************************************************************/
/* SPI�ӿڳ�ʼ��	ST7565R :SCLK\SI\CS\A0
***************************************************************************/
void ST7565R_IO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE);

	//GPIOF: CLK--GPIO_Pin_6, A0--GPIO_Pin_7, SID--GPIO_Pin_8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	//GPIOG: CS--GPIO_Pin_15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	//GPIOB: BL--GPIO_Pin_2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/**************************************************************************/
/* ��ʼ������ģ��
***************************************************************************/
extern void SysDelay_ms(uint16_t delay_ms);
void mInitialLCD(void)
{

	ApplVar.ScreenStat = 0;

	ST7565R_IO_Init();

	ST7565R_WR_CMD(ST7565R_CMD_RESET);
	ST7565R_NOP();//ST7565R_Delay_ms(1);

	ST7565R_WR_CMD(ST7565R_CMD_ADC_NORMAL);
	ST7565R_WR_CMD(ST7565R_CMD_NORMAL_SCAN_DIRECTION);

	ST7565R_WR_CMD(ST7565R_CMD_LCD_BIAS_9);

	ST7565R_WR_CMD(ST7565R_CMD_POWER_CTRL_ALL_ON);
	//ST7565R_WR_CMD(ST7565R_CMD_POWER_CTRL_ALL_ON+1); //??

	ST7565R_WR_CMD(ST7565R_CMD_VOLTAGE_RESISTOR_RATIO_4);

	ST7565R_WR_CMD(ST7565R_CMD_ELECTRONIC_VOLUME_MODE_SET);
	ST7565R_WR_CMD(ST7565R_CMD_ELECTRONIC_VOLUME(0x0C/*0x24*/));

	ST7565R_WR_CMD(ST7565R_CMD_BOOSTER_RATIO_SET);
	ST7565R_WR_CMD(ST7565R_CMD_BOOSTER_RATIO_5X);

	ST7565R_WR_CMD(ST7565R_CMD_DISPLAY_ON);

	mSetContrast(6);
	mClearScreen();
  mLightLCDOn();
	mDispLogo();
}

/**************************************************************************/
/* GPIOģ��SPIͨѶ����λ����
***************************************************************************/

void ST7565R_SendData(uint8_t dat)
{
	uint8_t i;

	ST7565R_CLK_LOW();
	for (i=0; i<8; i++)
	{
		if ((dat<<i) & 0x80) //�ߵ�����
			ST7565R_SID_HIGH();
		else
			ST7565R_SID_LOW();
		ST7565R_NOP();
		ST7565R_CLK_HIGH();
		ST7565R_NOP();
		ST7565R_CLK_LOW();
	}
	//ST7565R_NOP();
	//ST7565R_CLK_HIGH();
}


/**************************************************************************/
/* д����
***************************************************************************/
void ST7565R_WR_CMD(uint8_t cmd)
{

	ST7565R_CS_LOW();
	ST7565R_A0_CMD();
	ST7565R_SendData(cmd);
	ST7565R_CS_HIGH();


}

/**************************************************************************/
/* д����
***************************************************************************/
void ST7565R_WR_DATA(uint8_t dat)
{

	ST7565R_CS_LOW();
	ST7565R_A0_DATA();
	ST7565R_SendData(dat);
	ST7565R_CS_HIGH();
}

/*************************************************************************
 ������ʾ�Աȶ�
***************************************************************************/
void mSetContrast(uint8_t contrast)
{//������ʾ�Աȶ�

	    // 0x00-0x3f�Աȶ���ǳ���� //
		contrast *= 4;// (ApplVar.AP.Flag[CONTRAST] & 0x0f) * 5;
		ST7565R_WR_CMD(ST7565R_CMD_ELECTRONIC_VOLUME_MODE_SET);
		ST7565R_WR_CMD(ST7565R_CMD_ELECTRONIC_VOLUME(contrast));
}

/**************************************************************************/
/* ����ʾ����
***************************************************************************/
void mLightLCDOn(void)
{
	ST7565R_BL_ON();
	ApplVar.ScreenStat |= LIGHTON;
}

/**************************************************************************/
/* �ر���ʾ����
***************************************************************************/
void mLightLCDOff(void)
{
	ST7565R_BL_OFF();
	ApplVar.ScreenStat &= ~LIGHTON;
}

/**************************************************************************/
/* ������ʾ���
***************************************************************************/
void mEnCursor(uint8_t NewState )
{

	if(NewState)
	{//�򿪹��
        SETBIT(ApplVar.ScreenStat,CURSOREN);
	}
	else
	{
        if (TESTBIT(ApplVar.ScreenStat,CURSOREN |CURSORON)==(CURSOREN |CURSORON))
            mDispCursor();//�رչ��
        RESETBIT(ApplVar.ScreenStat,(CURSOREN | CURSORON));
	}
}

/**************************************************************************/
/* ��ʾ���
***************************************************************************/
void mDispCursor(void)
{
	uint8_t valh,vall;
	int x,y;

	if(TESTBIT(ApplVar.ScreenStat,CURSOREN))
	{
		SETBIT(ApplVar.ScreenStat,CRITICAL);
		x = ApplVar.sCursor.x;
		y = ApplVar.sCursor.y;
#ifndef CHAR_6X8
    y *= 2;
		x *= X_Width;
#else
		x *= X_Width;
		if(SCREENWD>x>0)
			x -= 1;
#endif

		if (ApplVar.sCursor.x>=SCREENWD)
			x--;//����Ļ���ұ߽�����ʾ���

		INVERTBIT(ApplVar.ScreenStat,CURSORON);
		if(TESTBIT(ApplVar.ScreenStat,CURSORON))
		{
			valh = vall = 0xff;
		}
		else /*ccr2013 if (ApplVar.sCursor.x<SCREENWD)*/ //����Ļ���ڴ���ʾ���
		{
			valh = DotBuffer[y][x];
#ifndef CHAR_6X8
			vall = DotBuffer[y+1][x];
#endif
		}
/*ccr2013		else //����Ļ���ұ߽�����ʾ���
		{
			valh = 0;
			vall = 0;
		}
*/

		st7565SetXY(x, pagemap[y]);
        if(x==0)
            ST7565R_WR_DATA(valh);	//???? ȥ����ᵼ�·��͵ĵ�1��8bit����û����ʾ,	���͵����ݿ�Ϊ�����ֽ�
		ST7565R_WR_DATA(valh);
#ifndef CHAR_6X8
		st7565SetXY(x, pagemap[y+1]);
        if(x==0)
            ST7565R_WR_DATA(vall);	//???? ȥ����ᵼ�·��͵ĵ�1��8bit����û����ʾ,	���͵����ݿ�Ϊ�����ֽ�
		ST7565R_WR_DATA(vall);
#endif
		RESETBIT(ApplVar.ScreenStat,CRITICAL);
	}
}

/**************************************************************************/
/* �ƶ����	�ڵ�y(0~3)��,��x(0~15)��λ����ʾ��꣬��꿿�Ҷ���
***************************************************************************/
void mMoveCursor(uint8_t x, uint8_t y)
{
	uint8_t i;
    uint8_t cur=TESTBIT(ApplVar.ScreenStat,CURSOREN);

    if (cur)
        mEnCursor(DISABLE);//�رչ��

	for(i = 0; i < x; )
	{
		if(ApplVar.ScreenMap[y][i]<0xA1)  //���ֻ�ASCII
			i++;
		else
			i += 2;
	}
	ApplVar.sCursor.x = i;
	ApplVar.sCursor.y = y;
    if (cur)
        mEnCursor(ENABLE);
}
/**************************************************************************/
/* �����������
***************************************************************************/
//void mClearInvAttr(void)
//{
//	RESETBIT(ApplVar.ScreenStat,INVATTR);
//}

/**************************************************************************/
/* ���÷�������,�˺��������ʾ���Է�����ʾ
***************************************************************************/
//void mSetInvAttr(void)
//{
//	SETBIT(ApplVar.ScreenStat,INVATTR);
//}

/**************************************************************************/
/* �򿪻�ر�״̬��
***************************************************************************/
void mSetState(uint8_t NewState)
{
	if(NewState)
	{
		SETBIT(ApplVar.ScreenStat,STATEON);
		ActiveLines = (SCREENLN-STATELN);
	}
	else
	{
		RESETBIT(ApplVar.ScreenStat,STATEON);
		ActiveLines = SCREENLN;
	}
}
/**************************************************************************/
/* �����Ļ����
***************************************************************************/
void mClearScreen(void)
{
	uint8_t p, pn;
	uint16_t c;

    SETBIT(ApplVar.ScreenStat,CRITICAL);

	if (TESTBIT(ApplVar.ScreenStat,STATEON))
	{//״̬�д�ʱ��ֻ���������ʾ�У������״̬��
#ifndef CHAR_6X8
		pn = 6;
#else
		pn = 7;
#endif
		memset(ApplVar.ScreenMap,' ',(SCREENLN-1)*SCREENWD);
	}
	else
	{
		pn = 8;
		memset(ApplVar.ScreenMap,' ',sizeof(ApplVar.ScreenMap));
	}

	for(p=0; p<pn; p++)
	{
		st7565SetXY(0, pagemap[p]);
        ST7565R_WR_DATA(0x0);
		for(c = 0; c < 129; c++)
		{
			ST7565R_WR_DATA(0x0);
		}
	}
	memset(DotBuffer,0,pn*128);//���buffer����
	GotoXY(0,0);
    RESETBIT(ApplVar.ScreenStat,CRITICAL);

}

/**************************************************************************/
/* �����Ļ
***************************************************************************/
void mBalnkScreen(void)
{
	uint8_t p, pn;
	uint16_t c;

    SETBIT(ApplVar.ScreenStat,CRITICAL);

	for(p=0; p<8; p++)
	{
		st7565SetXY(0, pagemap[p]);
        ST7565R_WR_DATA(0x0);
		for(c = 0; c < 129; c++)
		{
			ST7565R_WR_DATA(0x0);
		}
	}
    RESETBIT(ApplVar.ScreenStat,CRITICAL);

}

/**************************************************************************/
/* ������ʾλ�� x=(0..127), y=(0..63)
***************************************************************************/
void st7565SetXY(uint8_t pos_x,uint8_t pos_y)
{
    if (pos_x) pos_x++;//ccr2016-05-11�����2���ַ������������????????
	ST7565R_WR_CMD(ST7565R_CMD_PAGE_ADDRESS_SET(pos_y));				// ҳ��ַ
	ST7565R_WR_CMD(ST7565R_CMD_COLUMN_ADDRESS_SET_MSB(pos_x >> 4));  	// �е�ַ��4λ
	ST7565R_WR_CMD(ST7565R_CMD_COLUMN_ADDRESS_SET_LSB(pos_x & 0x0f));	// �е�ַ��4λ
}

/**************************************************************************/
/* ��DotBuffer��ָ����LinNum(0~3),��ColNumλ�õ��ַ�����������ʾ����Ļ��,
���ã�������ָ��λ��һ���ַ�ʱʹ��
hzFlag:=0,��ʾascii�ַ�;=1,��ʾ�����ַ�
***************************************************************************/
void mDrawChar(uint8_t ColNum, uint8_t LinNum,uint8_t hzFlag)
{
	uint8_t j;
	uint8_t *pDot;
	uint8_t num;

	num = ColNum;//ouhs20160227
	ColNum = ColNum*X_Width;

#ifndef CHAR_6X8
	LinNum *= 2;
#endif

#if defined(CASE_FORHANZI)
	if(hzFlag)	 // ����ģʽ��ʾΪ16λ���
		hzFlag = 16;
	else
#endif
		hzFlag = X_Width;

	//��ʾ�ϰ벿��
	pDot = &DotBuffer[LinNum][ColNum];
    SETBIT(ApplVar.ScreenStat,CRITICAL);

#ifdef CHAR_6X8
	if(TESTBIT(ApplVar.ScreenStat,DOUBLEWIDTH))//�ַ������ַ���಻�� ouhs20160227
	{
		if(ColNum==0)	//״̬����˿�5���㣬���Ҷ��� ouhs20160229
		{
			st7565SetXY(0, pagemap[LinNum]);
			ST7565R_WR_DATA(0x80);ST7565R_WR_DATA(0x9c);ST7565R_WR_DATA(0x9c);
			ST7565R_WR_DATA(0x9c);ST7565R_WR_DATA(0x9c);ST7565R_WR_DATA(0x80);
		}
		st7565SetXY(ColNum*2-num+5, pagemap[LinNum]);
//		else
//			st7565SetXY(ColNum*2-num, pagemap[LinNum]);
	}
	else
#endif
		st7565SetXY(ColNum, pagemap[LinNum]);

	if(ColNum==0)
		ST7565R_WR_DATA(0x80);	//???? ȥ����ᵼ�·��͵ĵ�1��8bit����û����ʾ,	���͵����ݿ�Ϊ�����ֽ�

	for(j = 0; j < hzFlag; j++)
	{
#ifdef CHAR_6X8
		if(TESTBIT(ApplVar.ScreenStat,DOUBLEWIDTH) && (j<(hzFlag-1)))//ouhs20160227
			ST7565R_WR_DATA(*pDot);
#endif
		ST7565R_WR_DATA(*pDot++);
	}



#ifndef CHAR_6X8
	//��ʾ�°벿��
	LinNum++;
	pDot = &DotBuffer[LinNum][ColNum];
	st7565SetXY(ColNum, pagemap[LinNum]);
	if(ColNum==0)
		ST7565R_WR_DATA(0x80);	//???? ȥ����ᵼ�·��͵ĵ�1��8bit����û����ʾ,	���͵����ݿ�Ϊ�����ֽ�
	for(j = 0; j < hzFlag; j++)
		ST7565R_WR_DATA(*pDot++);

#endif
    RESETBIT(ApplVar.ScreenStat,CRITICAL);

}

/**************************************************************************/
/* ��DotBuffer��ָ����LinNum(0~3)���ַ�����������ʾ����Ļ��,
   ������Ļ�ϵĵ�LinNum��������ʾһ��,���ã���Ҫ����ָ���ж���ַ�ʱʹ��
***************************************************************************/
void mDraw1Line(uint8_t LinNum)
{
	uint8_t i, j;

    SETBIT(ApplVar.ScreenStat,CRITICAL);
#ifndef CHAR_6X8
	for(i = 0; i < 2; i++)
	{
		st7565SetXY(0, pagemap[LinNum*2+i]);
		ST7565R_WR_DATA(0xff);	//???? ȥ����ᵼ�·��͵ĵ�1��8bit����û����ʾ,	���͵����ݿ�Ϊ�����ֽ�
		for(j = 0; j < 128; j++)
		{
			ST7565R_WR_DATA(DotBuffer[LinNum*2+i][j]);
		}
	}
#else
		st7565SetXY(0, pagemap[LinNum]);
		ST7565R_WR_DATA(0xff);	//???? ȥ����ᵼ�·��͵ĵ�1��8bit����û����ʾ,	���͵����ݿ�Ϊ�����ֽ�
		for(j = 0; j < 128; j++)
		{
			ST7565R_WR_DATA(DotBuffer[LinNum][j]);
		}
#endif
    RESETBIT(ApplVar.ScreenStat,CRITICAL);

}

/**************************************************************************/
/* ���͵�������
***************************************************************************/
void st7565Refresh(void)
{
	uint8_t c, p;

    SETBIT(ApplVar.ScreenStat,CRITICAL);
	for(p = 0; p < 8; p++)
	{
		st7565SetXY(0, pagemap[p]);
		ST7565R_WR_DATA(0xff);	//???? ȥ����ᵼ�·��͵ĵ�1��8bit����û����ʾ,	���͵����ݿ�Ϊ�����ֽ�
		for(c = 0; c < 128; c++)
		{
			ST7565R_WR_DATA(DotBuffer[p][c]);
		}
	}
    RESETBIT(ApplVar.ScreenStat,CRITICAL);
}

/**************************************************************************/
/* ���� x=(0..127), y=(0..63)
***************************************************************************/
void st7565DrawPixel(uint8_t x, uint8_t y)
{
	if ((x >= 128) || (y >= 64))
		return;

	DotBuffer[y/8][x] |= (1 << (7-(y%8)));
}

/**************************************************************************/
/* ��� x=(0..127), y=(0..63)
***************************************************************************/
void st7565ClearPixel(uint8_t x, uint8_t y)
{
	if ((x >= 128) || (y >= 64))
		return;

	DotBuffer[y/8][x] &= ~(1 << (7-(y%8)));
}

/**************************************************************************/
/* ָ��λ����ʾһ���ַ�ch
   ��LCD��Ļ��y(0~3)��,��x(0~15)��λ����ʾ�ַ�ch�ĵ���
   ch������ASCII���ߺ���
***************************************************************************/
void mDispCharXY(WORD ch, BYTE x, BYTE y)
{
	uint8_t col, ch_l, x_c, y_p,hzFlag;
	uint32_t addr;
	uint8_t *fontH,*fontL;

	if(y==SCREENLN)
	{
		if (TESTBIT(ApplVar.ScreenStat,STATEON))
			y--;
		else
			return;
	}

	x_c = x*X_Width;	// column address
#ifndef CHAR_6X8
	y_p = y*2;		 	  // page
#else
	y_p = y;
#endif


#if defined(CASE_FORHANZI)
	if ((ch <= 128))
#else
    ch &= 0xff;    //ccr2016-08-31
#endif
	{/* ASCII���� */
		hzFlag = 0;
        if (ch < 0x20) ch =0x20;
#ifndef CHAR_6X8
		addr = (ch - 0x20) * 16;
		fontH = &DotBuffer[y_p][x_c];
		fontL = &DotBuffer[y_p+1][x_c];
		memcpy(fontH,ASCIITAB_8x16+addr,8); 	 // �ϰ벿��
		memcpy(fontL,ASCIITAB_8x16+addr+8,8); 	 // �°벿��
#else
		addr = (ch - 0x20) * 5;
		fontH = &DotBuffer[y_p][x_c];
		memcpy(fontH,ASCIITAB_5x8+addr,5);
#endif

		if(TESTBIT(ApplVar.ScreenStat,INVATTR))
		{
			for (col = 0; col < X_Width; col++)
			{
				*fontH++ ^= 0xff; 	 // �ϰ벿��
#ifndef CHAR_6X8
				*fontL++ ^= 0xff;	 //�°벿��
#endif
			}

			fontH -= X_Width;
		}
#ifdef CHAR_6X8
		if(TESTBIT(ApplVar.ScreenStat,INVATTR))
			*(fontH + 5) = 0xff;
		else
			*(fontH + 5) = 0x00;
#endif

		if((y>=(SCREENLN-1)) && (TESTBIT(ApplVar.ScreenStat,STATEON)))		   // ״̬����ʾ�ָ���
		{
			for (col = 0; col < X_Width; col++)
			{
				*fontH++ |= 0x80; 	// �ϰ벿��
			}
		}

	}
#if defined(CASE_FORHANZI)
	else
	{/* ���ִ��� CCLIB16  */
		hzFlag = 1;
		ch -= 0xA1A1;
		ch_l = ch & 0xff;
		if (ch_l >= 15)
			ch_l -= 1;

		//�ֿ�оƬ�ǰ��ֽ��б�ַ,��˱���32/2,64ΪASCII����(����ASCII=һ������):128/2
		addr = (uint32_t)(ch_l*94 + (ch>>8)+64)*32 + FLASH_HZK16_ADDR;		// ��ƫ�Ƶ�ַ(����ַ+ƫ�Ƶ�ַ,16bit)

		fontH = &DotBuffer[y_p][x_c];
		fontL = &DotBuffer[y_p+1][x_c];


		//������벿��
		wFlashReadBuffer((WORD*)fontH, addr, 4); 	//���ϲ���, ��ȡ8���ֽ�
		wFlashReadBuffer((WORD*)fontL, addr+8, 4); 	//���²���, ��ȡ8���ֽ�
		fontH+=8;fontL+=8;addr+=16;
		//�����Ұ벿��
		wFlashReadBuffer((WORD*)fontH, addr, 4); 	//���ϲ���, ��ȡ8���ֽ�
		wFlashReadBuffer((WORD*)fontL, addr+8, 4); 	//���²���, ��ȡ8���ֽ�


		fontH -= 8;fontL -= 8;
		if(TESTBIT(ApplVar.ScreenStat,INVATTR))
		{
			for (col = 0; col < 16; col++)
			{
				*fontH++ ^= 0xff; 	 // �ϰ벿��
				*fontL++ ^= 0xff;	 //�°벿��
			}
			fontH -= 16;
		}
		if((y>=(SCREENLN-1)) && (TESTBIT(ApplVar.ScreenStat,STATEON)))		   // ״̬����ʾ�ָ���
		{
			for (col = 0; col < 16; col++)
			{
				*fontH++ |= 0x80; 	// �ϰ벿��
			}
		}
	}
#endif

	mDrawChar(x, y,hzFlag);
}

/**************************************************************************/
/* ָ��λ����ʾ�ַ���
***************************************************************************/
void mDispStringXY(BYTE* str, BYTE x, BYTE y)
{
	uint8_t i;
	uint8_t *pstr;

	pstr = str;

	for (i = 0; i < SCREENWD && *pstr; )
	{
#if defined(CASE_FORHANZI)
		if(*pstr>=0xA1)
		{//HZK
			mDispCharXY(CWORD(pstr[0]), (x + i) , y);
			pstr+=2;
			i += 2;
		}
		else
#endif
		{//ASCII
			mDispCharXY(*pstr, (x + i) , y);
			pstr++;
			i++;
		}
	}
}

/**************************************************************************
��ApplVar.ScreenMap�е�ָ����������ʾ����Ļ��
***************************************************************************/
void  mRefreshLine(BYTE y)
{
	if(y < (SCREENLN - (ApplVar.ScreenStat & STATEON)))
		mDispStringXY((uint8_t *)ApplVar.ScreenMap[y], 0, y);
	else if	((ApplVar.ScreenStat & STATEON) && (y==SCREENLN))
	{
		mDispStringXY((uint8_t *)ApplVar.ScreenMap[SCREENLN], 0, SCREENLN);
	}
}



/**************************************************************************
 ����Ļָ����ASCII�ַ�λ�����Ͻ���˸��ʾGPRS��ʾ
***************************************************************************/
void mDrawGPRS(uint8_t ColNum, uint8_t LinNum,uint8_t force)
{
	uint8_t j;
	uint8_t *pDot;
    static uint8_t gFlash=0x40;

    if ((force || (GetSystemTimer() & 0x100) == 0) && !TESTBIT(ApplVar.ScreenStat,CRITICAL))
    {
		if (!(gFlash & 1))
		{
			ColNum = ColNum*X_Width;
			LinNum *= 2;

			//��ʾ�ϰ벿��
			pDot = &DotBuffer[LinNum][ColNum]+5;
			SETBIT(ApplVar.ScreenStat,CRITICAL);

			st7565SetXY(ColNum+5, pagemap[LinNum]);
			for(j = 0; j < 8-5; j++)
			{
				gFlash ^= 0xc0;
				ST7565R_WR_DATA((*pDot | gFlash));
				pDot++;
			}
            RESETBIT(ApplVar.ScreenStat,CRITICAL);
			if (!force)
                gFlash |= 1;
		}
    }
	else
		gFlash &=0xc0;

}

/**
 * ����Ļָ����ASCII�ַ�λ����ʾ�������
 *
 * @author EutronSoftware (2014-12-31)
 *
 * @param ctrl :0-����ʾ;=1���Բ���ʾ;=2��ʾ
 * @param ColNum
 * @param LinNum
 */
extern void DisplayDecXY(WORD pDec,int x,int y,int pWdith);
#define VIN_FULL  VIN_8V7 //8.7V---3075mV---0xEE8   +����ֵ0x6B
#define VIN_NONE  VIN_7V0 //7.0V---1375mV---0x6AA
void mDrawPower(BYTE ctrl, uint8_t ColNum,uint8_t LinNum)
{
#if POWERCTRL
    static WORD gPower=0;

    uint8_t sByte;
	WORD pDot,j;

    //if (BatteryExist())//&& !DC_DET_GET())//ֻ���ڵ�ع���ʱ,����ʾ�������
    {
        if (ctrl==0)
        {
            gPower = 0;
            return;
        }
        else if (ctrl==1)
        {
            if (gPower==0)
                return;
        }
        gPower = Vin_Vrtc_Val[0];
        //DisplayDecXY(gPower,ColNum+1,4,6);//testonly

        if (gPower>=VIN_FULL)
            j=Y_Height;
        else if (gPower<=VIN_NONE)
            j = 0;
        else
            j = ((gPower-VIN_NONE)*Y_Height)/(VIN_FULL-VIN_NONE);

        pDot = (1<<j)-1;

        ColNum = ColNum*X_Width;
        LinNum *= 2;

        //��ʾ�ϰ벿��

        SETBIT(ApplVar.ScreenStat,CRITICAL);

        sByte = (pDot>>8) | 0x80;
        st7565SetXY(ColNum, pagemap[LinNum]);
        ST7565R_WR_DATA(0xff);
        ST7565R_WR_DATA(sByte | 0x40);
        for(j = 0; j < 4; j++)
            ST7565R_WR_DATA(sByte);
        ST7565R_WR_DATA(sByte | 0x40);
        ST7565R_WR_DATA(0xff);

        sByte = (pDot & 0xff);
        st7565SetXY(ColNum, pagemap[LinNum+1]);
        ST7565R_WR_DATA(0xff);
        for(j = 0; j < 6; j++)
            ST7565R_WR_DATA(sByte);
        ST7565R_WR_DATA(0xff);
    }
#endif
}

/*****************************************************************
 * ����Ļָ����ASCII�ַ�λ����ʾGPRS�ź�ǿ��
 *
 * @author EutronSoftware (2014-12-31)
 *
 * @param Signal:2-30,�ź�ǿ��
 * @param ColNum
 * @param LinNum
 ****************************************************************/
void mDrawGPRSSignal(BYTE Signal,uint8_t ColNum,uint8_t LinNum)
{
#if defined(CASE_GPRS)

    static BYTE gSignal=0xff;

    uint8_t sByte;
	WORD pDot,j,pH;

    //if (BatteryExist())//&& !DC_DET_GET())//ֻ���ڵ�ع���ʱ,����ʾ�������
    if (gSignal!=Signal)
    {
        gSignal=Signal;

        Signal &= 0x1f;
        j= Signal >> (3-Y_Height/8);//�߶�

        pDot = (1<<j)-1;//�߶ȶ�Ӧ�ĵ���ֵ

        SETBIT(ApplVar.ScreenStat,CRITICAL);

        ColNum = ColNum*X_Width;
#ifndef CHAR_6X8
        LinNum *= 2;

        //��ʾ�ϰ벿��

        st7565SetXY(ColNum, pagemap[LinNum]);
        pH=1;
        for(j = 0; j < 8; j++)
        {
            ST7565R_WR_DATA((pH>>8)|0x80);
            if (pH)
            {
               pH=(pH<<2) | 3;
               if (pH>pDot)
                   pH=0;
            }
        }


        st7565SetXY(ColNum, pagemap[LinNum+1]);
        pH=1;
        for(j = 0; j < 8; j++)
        {
            ST7565R_WR_DATA(pH);
            if (pH)
            {
               pH=(pH<<2) | 3;
               if (pH>pDot)
                   pH=0;
            }
        }
#else
        st7565SetXY(ColNum, pagemap[LinNum]);
        pH=1;
        for(j = 0; j < 8; j++)
        {
            ST7565R_WR_DATA(pH | 0x80);
            if (pH)
            {
               pH=(pH<<1) | 1;
               if (pH>pDot)
                   pH=0;
            }
        }
#endif
        RESETBIT(ApplVar.ScreenStat,CRITICAL);
    }
#endif
}


/**
 * ���ַ���LinrFrom��LineTo֮�仭һ������
 *
 * @author EutronSoftware (2016-02-24)
 *
 * @param LinFrom
 * @param LinTo
 */


#ifdef CHAR_6X8
void mDrawABox(BYTE LinFrom,BYTE LinTo)
{
    static BYTE LinNum;
    static BYTE maxLine;
    BYTE j;
    BYTE lin1LR,lin1C,lin1XOR;


    SETBIT(ApplVar.ScreenStat,CRITICAL);
    if (LinFrom==LinTo)
    {//�ظ������ǵ���
        for (j=LinNum;j<=maxLine;j++)
            mRefreshLine(j);
        LinNum=1;maxLine=0;
    }
    else
    {
        maxLine=LinTo;
        if (maxLine>(SCREENLN-TESTBIT(ApplVar.ScreenStat,STATEON)-1))
            maxLine=(SCREENLN-TESTBIT(ApplVar.ScreenStat,STATEON)-1);

        for (LinNum=LinFrom;LinNum<=maxLine;LinNum++)
        {
            if (LinNum==LinFrom)
            {//��������
                lin1LR=0x0f,lin1C=0x08+0x02;lin1XOR=0x07;
            }
            else if (LinNum==LinTo)
            {//��������
                lin1LR=0xf0,lin1C=0x10+0xa0;lin1XOR=0xe0;

            }
            else
            {//���м���
                lin1LR=0xff,lin1C=0x00+0xaa;lin1XOR=0xff;
            }
            st7565SetXY(0, pagemap[LinNum]);
            ST7565R_WR_DATA(0xff);  //???? ȥ����ᵼ�·��͵ĵ�1��8bit����û����ʾ, ���͵����ݿ�Ϊ�����ֽ�
            ST7565R_WR_DATA(lin1LR);
            for(j = 1; j < SCREENWD*6-1; j++)
            {
                 if (lin1XOR==0xff && j>5 && j<(SCREENWD-1)*6)
                     ST7565R_WR_DATA(0x00);
                 else
                 {
                     ST7565R_WR_DATA(lin1C);
                     lin1C ^= lin1XOR;
                 }
            }
            ST7565R_WR_DATA(lin1LR);
            ST7565R_WR_DATA(0);ST7565R_WR_DATA(0);
        }
        LinNum=LinFrom;
    }
    RESETBIT(ApplVar.ScreenStat,CRITICAL);
}
#else//font size=8*8
void mDrawABox(BYTE LinFrom,BYTE LinTo)
{
    static BYTE LinNum;
    static BYTE maxLine;
    BYTE j;
    BYTE lin1LR,lin1C,lin1XOR;
    BYTE lin2LR,lin2C,lin2XOR;


    SETBIT(ApplVar.ScreenStat,CRITICAL);
    if (LinFrom==LinTo)
    {//�ظ������ǵ���
        for (j=LinNum;j<=maxLine;j++)
            mRefreshLine(j);
        LinNum=1;maxLine=0;
    }
    else
    {
        maxLine=LinTo;
        if (maxLine>(SCREENLN-TESTBIT(ApplVar.ScreenStat,STATEON)-1))
            maxLine=(SCREENLN-TESTBIT(ApplVar.ScreenStat,STATEON)-1);

        for (LinNum=LinFrom;LinNum<=maxLine;LinNum++)
        {
            if (LinNum==LinFrom)
            {//��������
                lin1LR=0x0f,lin1C=0x08+0x02;lin1XOR=0x07;
                lin2LR=0xff,lin2C=0x00+0xaa;lin2XOR=0xff;

            }
            else if (LinNum==LinTo)
            {//��������
                lin1LR=0xff,lin1C=0x00+0xaa;lin1XOR=0xff;
                lin2LR=0xf0,lin2C=0x10+0xa0;lin2XOR=0xe0;

            }
            else
            {//���м���
                lin1LR=0xff,lin1C=0x00+0xaa;lin1XOR=0xff;
                lin2LR=0xff,lin2C=0x00+0xaa;lin2XOR=0xff;

            }
            st7565SetXY(0, pagemap[LinNum*2]);
            ST7565R_WR_DATA(0xff);  //???? ȥ����ᵼ�·��͵ĵ�1��8bit����û����ʾ, ���͵����ݿ�Ϊ�����ֽ�

            ST7565R_WR_DATA(lin1LR);
            for(j = 1; j < SCREENWD*8-1; j++)
            {
                if (lin1XOR==lin2LR && j>6 && j<(SCREENWD*8-7))
                    ST7565R_WR_DATA(0x00);
                else
                {
                    ST7565R_WR_DATA(lin1C);
                    lin1C ^= lin1XOR;
                }
            }
            ST7565R_WR_DATA(lin1LR);

            ST7565R_WR_DATA(0);ST7565R_WR_DATA(0);

            st7565SetXY(0, pagemap[LinNum*2+1]);
            ST7565R_WR_DATA(0xff);  //???? ȥ����ᵼ�·��͵ĵ�1��8bit����û����ʾ, ���͵����ݿ�Ϊ�����ֽ�

            ST7565R_WR_DATA(lin2LR);
            for(j = 1; j < SCREENWD*8-1; j++)
            {
                if (lin1XOR==lin2LR && j>6 && j<(SCREENWD*8-7))
                    ST7565R_WR_DATA(0x00);
                else
                {
                    ST7565R_WR_DATA(lin2C);
                    lin2C ^= lin2XOR;
                }
            }
            ST7565R_WR_DATA(lin2LR);

            ST7565R_WR_DATA(0);ST7565R_WR_DATA(0);
        }
        LinNum=LinFrom;
    }
    RESETBIT(ApplVar.ScreenStat,CRITICAL);
}
#endif


/**************************************************************************/
/* ��ʾһ��ͼƬ
***************************************************************************/
const uint8_t EUTRON_LOGO_128064[8][128]= {
{0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x1F,0x3F,0x3E,0x7D,0x7B,0x77,0x6F,0x5F,0x3F,0x7E,0x7D,0x7B,0x77,0x6F,0x1F,0x3F,0x3F,0x1E,0x0D,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x1F,0x7E,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7E,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F,0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7E,0xFD,0xFB,0xF7,0xEF,0xDF,0x3F,0x1F,0x00,0x00,0x00,0x30,0x30,0x3F,0x3F,0x3F,0x3F,0x30,0x30,0x37,0x38,0x3C,0x3E,0x00,0x00,0x00,0x30,0x3F,0x3F,0x3F,0x3F,0x30,0x30,0x00,0x00,0x30,0x30,0x3F,0x3F,0x30,
0x00,0x00,0x3E,0x38,0x30,0x30,0x3F,0x3F,0x3F,0x3F,0x30,0x30,0x38,0x38,0x3E,0x00,0x30,0x30,0x3F,0x3F,0x3F,0x3F,0x30,0x30,0x38,0x3F,0x1F,0x0F,0x07,0x00,0x00,0x00,0x01,0x07,0x0F,0x1F,0x1F,0x38,0x30,0x30,0x30,0x30,0x1C,0x1F,0x0F,0x07,0x03,0x00,0x00,0x30,0x30,0x3F,0x3E,0x3F,0x1F,0x0F,0x03,0x01,0x00,0x30,0x3F,0x3F,0x30,0x00},
{0x00,0x7C,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F,0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7E,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F,0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7E,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x61,0xF1,0xFD,0x01,0x03,0x07,0x0F,0x00,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0x07,0x01,0x01,0x01,0x03,0x07,0xFE,0xF8,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x60,0x78,0x7C,0xFF,0xFF,0xCF,0x87,0x01,0x00,0x00,0xF0,0xFC,0xFE,0xFF,0xFF,0x03,0x01,0x00,0x00,0x01,0x07,0xFF,0xFF,0xFE,0xF8,0x00,0x00,0x00,0x01,0xFF,0x01,0x00,0xC0,0xE0,0xF0,0xF8,0xFC,0x7E,0xFF,0xFF,0x00,0x00},
{0x00,0x00,0x80,0xC0,0xE0,0xE0,0xD8,0xBC,0x7E,0xFC,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F,0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F,0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC7,0xC0,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xC3,0xC3,0xC3,0xC3,0xC3,0xC3,0xE7,0xFF,0xFF,0xFE,0x7C,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x00,0x00,0x00,0x18,0x38,0x38,0x78,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x0F,0x7F,0xFF,0xFF,0xF0,0xC0,0xC0,0xC0,0xE0,0xFF,0xFF,0x7F,0x0F,0x00,0x00,0x00,0x0F,0x7F,0xFF,0xFF,0xF0,0xC0,0xC0,0xC0,0xE0,0xFF,0xFF,0x7F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x07,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xFE,0xFF,0xFF,0x7F,0x01,0x00,0x00,0x00,0x00,0xE0,0xE0,0xE0,0xE0,
0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xF0,0xFE,0xFF,0xFF,0x0F,0x03,0x03,0x03,0x0F,0xFF,0xFF,0xFE,0xF0,0x00,0x00,0x00,0xF0,0xFE,0xFF,0xFF,0x0F,0x03,0x03,0x03,0x0F,0xFF,0xFF,0xFE,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

void mDispLogo(void)
{
#ifdef  CASE_ER100
	uint8_t p, pn;
	uint16_t c;

	pn = 8;

	for(p=0; p<pn; p++)
	{
		st7565SetXY(0, pagemap[p]);
		for(c = 0; c < 129; c++)
		{
			ST7565R_WR_DATA(EUTRON_LOGO_128064[p][c]);
		}
	}
#endif
}



