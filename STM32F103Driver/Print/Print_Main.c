/****************************************Copyright (c)**************************************************
*        EUTRON Human Information Equipment Co.,Ltd.
*                    www.eutron.com.cn
* File name:		Print_Main.c
* Descriptions:     ��ӡ����������
*------------------------------------------------------------------------------------------------------
*  Created by:			chen churong
* Created date:        2011-10-01
* Version: 1.0
********************************************************************************************************/

#if !defined(CASE_INNERDOTPRN)

#include "king.h"                               /* Kingtron library and I/O routines */
#include "appl.h"
#include "exthead.h"
#include "Font12x24cy.h"
#include "Flashb.h"

#include "lcd_160x.h"  //ouhs 20140815
#define DELAY_CONST 5   //ccr2014-09-12 ���ֽ�źŵ��ӳټ������� //

#if DEBUGONPC
    #include <stdio.h>
    #include <mem.h>
#endif


void ReadHZKU(ULONG addr,BYTE *hzBuf);
void ChangeGRBToMyself(void);

extern APPLICATION_SAVE  ApplVar;


/**************************** modules for printer ******************/
#include "Print_PT486F.h"

///////////////////////////////////////////////////////////////////


//ouhs 20140814
#if defined   (__CC_ARM)      /* ARM Compiler */
  struct GRB_DEFINE GRB_Define __attribute__((at(DOWN_GR_ADDR)));//=BKPSRAM_BASE;�û����ص�GRBͼƬ���ݴ洢��
#elif defined (__ICCARM__)    /* IAR Compiler */
  __no_init struct GRB_DEFINE  GRB_Define @DOWN_GR_ADDR;
#endif


/*********************************************************************************************************
** Function name:      PrnTIMER_Config
** Descriptions:      ��ʱ��2���ڴ�ӡ�������,��ʱ��3���ڼ��ȿ���
*********************************************************************************************************/
/**
  * @brief  Configures the used Timers.
  * @param  None
  * @retval None
  */
void PRNTIMER_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;

  /* Enable TIM2, TIM3 clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);

  /* .............................................*/

  /* TIM2 configuration */

  TIM_TimeBaseStructure.TIM_Period = uSECOND * 5000; //5ms
  TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/1000000) - 1);;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM2,DISABLE);// ��ʹ��Ӱ�ӼĴ��� //
  TIM_OCStructInit(&TIM_OCInitStructure);

  /* Output CompareBCDValue Timing Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_Pulse = 0x0;
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);

  /* Immediate load of TIM2 Precaler values */
  //ccr TIM_PrescalerConfig(TIM2, ((SystemCoreClock/1200) - 1), TIM_PSCReloadMode_Immediate);
  /* Clear TIM2 update pending flags */
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);

  /* Enable the TIM2 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* .............................................*/

  /* TIM3 configuration */
  //ccr TIM_TimeBaseStructure.TIM_Period = 0x95F;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* Output CompareBCDValue Timing Mode configuration: Channel1 */
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  /* Immediate load of TIM3 Precaler values */
  //ccr TIM_PrescalerConfig(TIM3, ((SystemCoreClock/1200) - 1), TIM_PSCReloadMode_Immediate);

  /* Clear TIM3 update pending flags */
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);

  /* Configure two bits for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);


  /* Enable the TIM3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);

  /* .............................................*/

  /* Enable TIM2  Update interrupts */
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  /* TIM2 enable counters */
//  TIM_Cmd(TIM2, ENABLE);

  /* Enable TIM3  Update interrupts */
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  /* TIM3 enable counters */
//  TIM_Cmd(TIM3, ENABLE);
}


/********* ADC2  Channel 10 ���ڼ���¶� ***************************************
  * @brief  ADC2 Channel 10 configuration (DMA, ADC, CLK)
  * @param  None
  * @retval None
********************************************************************************/
void PRNTempPort_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStructure;
  ADC_InitTypeDef ADC_InitStructure;

  /* Enable peripheral clocks *************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  /* ADC Channel 10 -> PC0  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStructure);


  /* ADC2 regular channels 10 configuration*/

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channels 10, 11 configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_13Cycles5);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);


}

/*******************************************************************************************
** �������ƣ�PRNData_Init
** ����˵������ʼ���������ݶ˿ڵ�SPI��
** ��ڲ�������
** ���ڲ�������
*******************************************************************************************/
/**
  * @brief  Initializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void PRNDataPort_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;

  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< Enable the SPI clock */
  PRNData_SPI_CLK_INIT(PRNData_SPI_CLK, ENABLE);

  /*!< Enable GPIO clocks */
  RCC_APB2PeriphClockCmd(PRNData_SPI_SCK_GPIO_CLK | PRNData_SPI_MOSI_GPIO_CLK | PRNData_LATCH_GPIO_CLK, ENABLE);

  /*!< SPI pins configuration *************************************************/

  /*!< Connect SPI pins to AF5 */

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  /*!< SPI SCK pin configuration */
  /*!< SPI MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin = PRNData_SPI_SCK_PIN | PRNData_SPI_MOSI_PIN;
  GPIO_Init(PRNData_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure LATCH pin in output pushpull mode ********************/
  GPIO_InitStructure.GPIO_Pin = PRNData_LATCH_PIN;// LATCHBIT
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PRNData_LATCH_GPIO_PORT, &GPIO_InitStructure);

  /*!< Deselect the FLASH: Chip Select high */
  PRNData_LATCH_HIGH();

  /*!< SPI configuration for Printer data port*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
#if WORDorBYTE
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
#else
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
#endif
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; // ouhs SPI_BaudRatePrescaler_4;

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(PRNData_SPI, &SPI_InitStructure);

  /*!< Enable the PRNData_SPI  */
  SPI_Cmd(PRNData_SPI, ENABLE);

}
/* ��ʼ����ӡ����ֽ������ƶ˿� */
void PRNFeedPort_Init(void)
{
}

/* ��ʼ����ӡ�����ֽ,��Դ���ƶ˿� */
void PRNPePwPort_Init(void)
{
  GPIO_InitTypeDef      GPIO_InitStructure;

	/* GPIOB Pin0,1,6,7,8 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* ��ֽ, ���ȿ��� */
	GPIO_InitStructure.GPIO_Pin = PHOEBIT | HOTBIT;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* ��ӡ����Դ���� */
	GPIO_InitStructure.GPIO_Pin = POWERBIT;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

 	/* ��ֽ��� */
	GPIO_InitStructure.GPIO_Pin = PAPERBIT;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOG, &GPIO_InitStructure);


}

//��ʼ����ӡ����صĿ��ƶ˿�
void  SPI_For_Printer(void)
{
    PRNTempPort_Init();
    PRNDataPort_Init();
    PRNFeedPort_Init();
    PRNPePwPort_Init();
    PRNTIMER_Init();

}

/************************************************************************
** ��������: Send_Byte
** �������ܣ�ͨ��Ӳ��SPI����һ���ֽڵ�SST25VF016B
** ��ڲ���:data
** ���ڲ���:��
************************************************************************/
void Send_Byte(uint8_t data)
{
  /*!< Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(PRNData_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /*!< Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(PRNData_SPI, data);

  /*!< Wait to receive a byte */
  //ccr testonly while (SPI_I2S_GetFlagStatus(PRNData_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /*!< Return the byte read from the SPI bus */
  //ccr return SPI_I2S_ReceiveData(PRNData_SPI);

}
/************************************************************************
** ��������: Send_Word
** �������ܣ�ͨ��Ӳ��SPI����һ���ֽڵ�SST25VF016B
** ��ڲ���:data
** ���ڲ���:��
************************************************************************/
void Send_Word(uint16_t data)
{
  /*!< Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(PRNData_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /*!< Send Half Word through the sFLASH peripheral */
  SPI_I2S_SendData(PRNData_SPI, data);

  /*!< Wait to receive a Half Word */
  while (SPI_I2S_GetFlagStatus(PRNData_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /*!< Return the Half Word read from the SPI bus */
  //ccr return SPI_I2S_ReceiveData(PRNData_SPI);
}

void Print_Initial( void )
{
//    memset(&InfoSelf_Graph,0,sizeof(InfoSelf_Graph));//ccr2014-03-25

    InfoSelf_Graph.cGrapCols = 0;
    InfoSelf_Graph.cGrapSize = 0;

    CWORD(Prn_Status) = 0;

#if ENCUTTER
    CWORD(Cut_Status) = 0;
    Cut_Status.g_bFirst = 1;
#endif

    Prn_Status.g_bPrintOver = true;//not any data in POOL, POOL is empty
    Prn_Status.g_bGraphicOver = true;  //  A task for print graphic finished
#if defined(CASE_FORHANZI)
    Prn_HZTime = 0;
#endif
    memset(&DataFromHost,0,sizeof(DataFromHost));
    memset(&InfoSelf_Graph,0,sizeof(InfoSelf_Graph));
#if DEBUGONPC
#else
    SPI_For_Printer(); //initial for printer

    PrnHotOFF();

    Drive_Off();
    PrnPowerOFF();

    Reset_printer();

#endif

//    uSECOND = SystemCoreClock / 4000000;
}

/****************************************************************
  Name: TESTPAPER  ����Ƿ���ֽ;
 return: true-��ֽ; false-��ֽ
*****************************************************************/
BYTE TESTPAPER(void)
{
    ULONG t1,t2;

#if (CASE_PT486F)
    do {
        t1 = (GPIOG->IDR & PAPERBIT);
        for (t2=10;t2>0;t2--);//�ӳ�
        t2 = (GPIOG->IDR & PAPERBIT);
    } while (t1!=t2);

   	if (t1)
        return true;  // ��ֽ
   	else
        return false;  // ��ֽ

#elif (CASE_PT723F_RJ)
    do {
        t1 = (GPIOG->IDR & (PAPERBIT | PAPER_J_BIT));
        for (t2=10;t2>0;t2--);//�ӳ�
        t2 = (GPIOG->IDR & (PAPERBIT | PAPER_J_BIT));
    } while (t1!=t2);

	if (t1 == (PAPERBIT | PAPER_J_BIT))
        return true;  // ��ֽ
   	else
        return false;  // ��ֽ
#endif


}

#if CASE_HANDUP
/****************************************************************
  Name: TESTHAND  ���ѹ��״̬
 return: true-ѹ������; false-ѹ���쳣
*****************************************************************/
BYTE TESTHAND(void)
{
    ULONG t1,t2;
        return true;  //hand down
//    do {
//        t1 = (LPC_GPIO0->FIOPIN & CASE_HANDUP);????
//        t2 = t1;
//        t2 = (LPC_GPIO0->FIOPIN & CASE_HANDUP);????
//    } while (t1!=t2);


}
#endif
// read status of the print
void Check_Print()
{

    Prn_Status.g_bHANDUP = 0;

    if (!TESTPAPER())//paper out
    {
        Prn_FeedCount = 0;
        Prn_Status.g_bNOPAPER = true;
        Prn_Status.g_bPaperIn = false;
    }
    else
    {
        if (Prn_Status.g_bNOPAPER)
        {
            Prn_FeedCount = 0;
            Prn_Status.g_bPaperIn = true;
            Prn_Status.g_bWaitPaper = false;
        }
        Prn_Status.g_bNOPAPER = false;
    }

    if (Prn_FeedCount>FEEDMAX)
        Prn_Status.g_bTOOHOT = true;

#if CASE_HANDUP
    if (!TESTHAND())//paper out
    {
        Prn_Status.g_bHANDUP = true;
        Prn_Status.g_bHANDDN = false;
    }
    else
    {
        if (Prn_Status.g_bHANDUP)
        {
            Prn_Status.g_bWaitPaper = false;
            Prn_Status.g_bHANDDN = true;
        }
        Prn_Status.g_bHANDUP = false;
    }
#endif
}
/***********************************************************************
  Combine a BYTE with full byte if needed
  comFor:XXXX|....| >>>>> XXXXnnnn
  comWith:   |nnnn|mmmm   >>>>> mmmm....
************************************************************************/
void CombineWith8(BYTE *comFor,BYTE comWith,BYTE comFlag)
{
    if (comFlag)
    {// must combine withe the last byte
        comFor[0] = comFor[0] | (comWith>>4);
        comFor[1] = comWith<<4;
    }
    else
    {// don't combine with the last byte
        comFor[0] = comWith;
    }
}
/***********************************************************************
  Combine a BYTE with half byte if needed
  comFor:XXXX|....| >>>>> XXXXnnnn
  comWith:   |nnnn|....
************************************************************************/
BYTE CombineWith4(BYTE *comFor,BYTE comWith,BYTE *comFlag)
{
    if (*comFlag)
    {// must combine withe the last byte
        *comFor |=  (comWith>>4);
        *comFlag = false;// don't combine withe the last byte next time
        return 1;
    }
    else
    {// don't combine with the last byte
        *comFor = comWith;
        *comFlag = true;// must combine withe the last byte next ime
        return 0;
    }
}
/***********************************************************************
  Create dots for  the characters
************************************************************************/
void Create384Dots(void)
{
#if (defined(CASE_FORHANZI) )
    BYTE HanZiKu_Data[3];
#endif
    BYTE temp[2];

    int i,j;
    ULONG idx;
    BYTE bCombine=false;//must Combine with the last BYTE if it is true

    //Prn_LineDots = 0;

    memset(DotsOfCurrent,0,sizeof(DotsOfCurrent));
    if (Prn_LineIndex<TEXT_HIGH)
    {
        for (i=j=0;i<Prn_LineChars && j<BYTES_OF_PAPER_LINE;i++)
        {
            idx = FontsOffset[i];//get the FontsOffset of the fonts
#if (defined(CASE_FORHANZI) )
            if ((idx & HANZFLAG))//it is a chinese
            {
                idx += Prn_LineIndex*3;
                ReadHZKU(idx & 0x03fffff,HanZiKu_Data);
                if (idx & DBWFLAG)//double with print mode
                {
                    i+=3;
//                    idx &= 0x00ffffff;
                    CWORD(temp[0]) = DoubleByte[HanZiKu_Data[0]];
                    CombineWith8(&DotsOfCurrent[j],temp[1],bCombine);
                    if (++j>=BYTES_OF_PAPER_LINE) break;
                    CombineWith8(&DotsOfCurrent[j],temp[0],bCombine);
                    if (++j>=BYTES_OF_PAPER_LINE) break;
                    CWORD(temp[0]) = DoubleByte[HanZiKu_Data[1]];
                    CombineWith8(&DotsOfCurrent[j],temp[1],bCombine);
                    if (++j>=BYTES_OF_PAPER_LINE) break;
                    CombineWith8(&DotsOfCurrent[j],temp[0],bCombine);
                    if (++j>=BYTES_OF_PAPER_LINE) break;
                    CWORD(temp[0]) = DoubleByte[HanZiKu_Data[2]];
                    CombineWith8(&DotsOfCurrent[j],temp[1],bCombine);
                    if (++j>=BYTES_OF_PAPER_LINE) break;
                    CombineWith8(&DotsOfCurrent[j],temp[0],bCombine);
                    ++j;
                }
                else
                {
                    i++;
//                    idx &= 0x00ffffff;

                    CombineWith8(&DotsOfCurrent[j],HanZiKu_Data[0],bCombine);
                    if (++j>=BYTES_OF_PAPER_LINE) break;
                    CombineWith8(&DotsOfCurrent[j],HanZiKu_Data[1],bCombine);
                    if (++j>=BYTES_OF_PAPER_LINE) break;
                    CombineWith8(&DotsOfCurrent[j],HanZiKu_Data[2],bCombine);
                    ++j;
                }
            }
            else//It is a ASCII
#endif
            {
                idx += Prn_LineIndex*ASCIINUM;
                if (idx & DBWFLAG)//double with print mode
                {
                    i++;
                    idx &= 0x00ffffff;
                    CWORD(temp[0]) = DoubleByte[ASCII12x24[idx++]];
                    CombineWith8(&DotsOfCurrent[j],temp[1],bCombine);
                    if (++j>=BYTES_OF_PAPER_LINE) break;
                    CombineWith8(&DotsOfCurrent[j],temp[0],bCombine);
                    if (++j>=BYTES_OF_PAPER_LINE) break;

                    CWORD(temp[0]) = DoubleByte[ASCII12x24[idx]];
                    CombineWith8(&DotsOfCurrent[j],temp[1],bCombine);
                    ++j;
                }
                else//normal width print mode
                {
                    //|******** xxxx....|(765432107654....)
                    idx &= 0x00ffffff;
                    temp[0] = ASCII12x24[idx++];//get the 8 dots for the left
                    CombineWith8(&DotsOfCurrent[j],temp[0],bCombine);
                    if (++j>=BYTES_OF_PAPER_LINE) break;
                    temp[0] = ASCII12x24[idx];// get the 4 dots for the right
                    j+=CombineWith4(&DotsOfCurrent[j],temp[0],&bCombine);
                }
            }
        }
#if CASE_PT723F_RJ

#define DotsOfCurrent_Stubs ((BYTE *)(DotsOfCurrent+ (BYTES_OF_HEAT_LINE-BYTES_OF_PAPER_LINE) ) )

		//HJ ѡ��Ʊ�ݴ�ӡ��//
		if(BIT(ApplVar.Prn_Command, PRN_RECEIPT_Mode))
		{
		    memcpy(DotsOfCurrent_Stubs, DotsOfCurrent, BYTES_OF_PAPER_LINE);
		}

		//HJ ��ѡ������ӡ��//
		if(!BIT(ApplVar.Prn_Command, PRN_STUB_Mode))
		{
		    memset(DotsOfCurrent, 0, BYTES_OF_PAPER_LINE);
		}
#endif
    }
}

/***********************************************************************
  Create font offset of all of the characters current
************************************************************************/
void SetFontOffset_char(BYTE count)
{
    WORD qh,ql;
    BYTE *lineDots = ApplVar.PoolForPrint[Prn_PoolCurrent].data;
    int i,j=0;

#if (FOR_POS)
#define dbW  BIT(ApplVar.Prn_Command,PRN_DBLW_Mode)
#else
    BYTE dbW=false;   //double wodth falg for '~'
#endif

#if defined(CASE_FORHANZI)
    Prn_HZTime = PDATATIME;
#endif

    for (i=0;i<count && j<PRNWIDTH;i++)
    {
        qh = lineDots[0];

#if (FOR_POS==0)
        if (qh=='~' && !dbW)
            dbW = true;
        else
#endif
        {
#if defined(CASE_FORHANZI)
            if (qh >= 0xa0)//IT is a HANZI
            {//0xb0+1+4;//"��":0xb0a1
                Prn_HZTime += HZTIMES;

                lineDots++;
                ql =lineDots[0]-0xa1;
                qh -= 0xa1;
                if (qh>3) qh -= (15-4);

                qh= qh * 94 + ql;

                FontsOffset[j]=(128*ASCII_SIZE + ((ULONG)qh*HZ_SIZE)+ FLASH_HZK24_ADDR) | HANZFLAG;

                if (dbW)
                {//double width for hanzi
                    FontsOffset[j] |= DBWFLAG;
                    j+=2;//skip 2 characters
                }
                j++;
                i++;
            }
            else
#endif
            {
#if defined(CASE_FORHANZI)
                Prn_HZTime += ASCTIMES;
#endif
                if (qh>=ASCIIFROM)
                    qh -= ASCIIFROM;
                FontsOffset[j] = qh*2;
                if (dbW)
                {
                    FontsOffset[j] |= DBWFLAG;
                    j++;
                }
            }
            j++;
#if (FOR_POS==0)
            dbW= false;
#endif
        }
        lineDots++;
    }
    if (j>=PRNWIDTH)
        j = PRNWIDTH;
    if (BIT(ApplVar.Prn_Command,PRN_DBLH_Mode))
    {//set double high flag
        SETBIT(FontsOffset[0],DBHFLAG);
    }
    Prn_LineChars = j;
}
#if CASE_PT723F_RJ
#define BYTES_OF_SHUANG_ZHAN_GAP (BYTES_OF_HEAT_LINE - BYTES_OF_PAPER_LINE - BYTES_OF_PAPER_LINE)
void Send_blank_dot (BYTE dotNum )
{
	BYTE i;
#if (WORDorBYTE)
    for(i=0; i<dotNum; i++)
    {
    	Set_Hot_DataW( (WORD)0, i++);
	}
#else
    for(i=0; i<dotNum; i++)
    {
    	Set_Hot_Data( (BYTE)0, i);
	}
#endif
}
#endif
/**********************************************************************
  Get dots from the graphic
**********************************************************************/
void CreateGraphicDots()
{
    int i,j;
#if CASE_PT723F_RJ
    BYTE f_repeatOnce = 1;
#endif

#if defined(CASE_FORHANZI)
    Prn_HZTime = PDATATIME;
#endif
    //Prn_LineDots = 0;
    if (Graph_DotsLineMax || Graph_Remain)
    {
        j = Graph_LineCurrent*Graph_Width-Graph_PosX+Graph_Offset;
        if (Graph_DotsLineMax==0)
        {
            Graph_Width = Graph_Remain;
            Graph_Remain = 0;
        }
        else
        {
            Graph_LineCurrent++;
            Graph_DotsLineMax--;
        }
        //��ʼ�͵���֮ǰ,���б�Ҫ�ĳ�ʼ��
        Prn_LineDots = 0;
#if GROUPMODE==2
        memset(Prn_GroupDots,0,sizeof(Prn_GroupDots));
#endif

#if CASE_PT723F_RJ
		//HJ �������ӡ��࣬���Ϳհ׵�������//
		if(!BIT(ApplVar.Prn_Command, PRN_STUB_Mode))
		{
			Send_blank_dot(BYTES_OF_PAPER_LINE + BYTES_OF_SHUANG_ZHAN_GAP);
			f_repeatOnce = 0;
		}
		else
		{
			f_repeatOnce = 1;
		}
#endif

		//HJ ���Ϳɼ���������//
#if WORDorBYTE
CreateGraphicDots_1:
        for (i=0;i<BYTES_OF_PAPER_LINE;i+=2,j+=2)
        {
            if ((i>=Graph_PosX)&&(i<(Graph_Width+Graph_PosX)))
            {
                if ((i+1-Graph_PosX)<Graph_Width)
                    Set_Hot_DataW( ((WORD)pGraBuf[j]<<8)+pGraBuf[j+1] , i);
                else
                    Set_Hot_DataW( ((WORD)pGraBuf[j]<<8) , i);
            }
            else
            {
                Set_Hot_DataW( 0 , i );
            }
        }

#if CASE_PT723F_RJ
		//HJ ��ӡ��ͬ������//
		if(f_repeatOnce == 1)
		{
			f_repeatOnce = 0;

			Send_blank_dot(BYTES_OF_SHUANG_ZHAN_GAP);
			j -= BYTES_OF_PAPER_LINE;
			goto CreateGraphicDots_1;
		}
#endif

#else //HJ �ֽ�SPI��ʽ//
CreateGraphicDots_2:

        for (i=0;i<BYTES_OF_PAPER_LINE;i++,j++)
        {
            if ((i>=Graph_PosX)&&(i<(Graph_Width+Graph_PosX)))
            {
                Set_Hot_Data( pGraBuf[j] , i);
            }
            else
            {
                Set_Hot_Data( 0 , i );
            }
        }

#if CASE_PT723F_RJ
		//HJ ��ӡ��ͬ������//
		if(f_repeatOnce == 1)
		{
			f_repeatOnce = 0;

			Send_blank_dot(BYTES_OF_SHUANG_ZHAN_GAP);
			j -= BYTES_OF_PAPER_LINE;
			goto CreateGraphicDots_2;

		}
#endif

#endif


#if GROUPMODE==2
        //�������һ���ֽ�ʱ,�趨��������������
        Set_Hot_Group();
#endif

		//HJ ���桢���Ȳ���ʱ
        Start_Hot();
    }
    if ((!Graph_DotsLineMax)&&(!Graph_Remain))
    {
        Graph_LineCurrent = 0;
        Prn_Status.g_bGraphicOver = true;//  A task for print graphic finished
    }
}

/**********************************************************************
  Attch text dots on the graphic HJ ��ͼ����,�����ı���
**********************************************************************/
void CreatGraphicWithText()
{
    int i,j;
#if WORDorBYTE
    WORD char_temp = 0;
#endif

    BYTE char_flag = 0;
    BYTE *linep=DotsOfCurrent;

#if CASE_PT723F_RJ
    BYTE f_repeatOnce = 1;
#endif

    if ((!Prn_LineIndex)&&(!Feed_BlankLines))
    {
        if (TextIdx_ForGraph < Prn_GraphTextMax)
        {
//			if(ApplVar.PoolPushIn != ApplVar.PoolPopOut)
            {
                if (++Prn_PoolCurrent>=MAX_PRNPOOL) Prn_PoolCurrent = 0;
                SetFontOffset_char(ApplVar.PoolForPrint[Prn_PoolCurrent].Length);
                TextIdx_ForGraph++;
                Prn_LineIndex=0;
            }
        }
    }
    if (TextIdx_ForGraph <= Prn_GraphTextMax)
    {
        if (Prn_LineIndex<TEXT_HIGH)
        {
            Create384Dots();
            Prn_LineIndex++;
            char_flag = 1;
        }
        else
        {
            memset(DotsOfCurrent,0,sizeof(DotsOfCurrent));

            if (Feed_BlankLines<LINE_BLANK)
                Feed_BlankLines++;
            else
            {
                Feed_BlankLines = 0;
                Prn_LineIndex = 0;
            }
            if (TextIdx_ForGraph == Prn_GraphTextMax)
            {//��Ҫ���ӵ��ַ��е������
                TextIdx_ForGraph = Prn_GraphTextMax = 0;
            }
            char_flag = 0;
        }
    }
    //Prn_LineDots = 0;
    if (Graph_DotsLineMax || Graph_Remain)
    {
        j = Graph_LineCurrent*Graph_Width-Graph_PosX+Graph_Offset;
        if (Graph_DotsLineMax==0)
        {
            Graph_Width = Graph_Remain;
            Graph_Remain = 0;
        }
        else
        {
            Graph_LineCurrent++;
            Graph_DotsLineMax--;
        }

        //��ʼ�͵���֮ǰ,���б�Ҫ�ĳ�ʼ��
        Prn_LineDots = 0;
#if GROUPMODE==2
        memset(Prn_GroupDots,0,sizeof(Prn_GroupDots));
#endif

#if CASE_PT723F_RJ
		//HJ �������ӡ��࣬���Ϳհ׵�������//
		if(!BIT(ApplVar.Prn_Command, PRN_STUB_Mode))
		{
			Send_blank_dot(BYTES_OF_PAPER_LINE + BYTES_OF_SHUANG_ZHAN_GAP);
			f_repeatOnce = 0;
		}
		else
		{
			f_repeatOnce = 1;
		}
#endif

#if WORDorBYTE
CreatGraphicWithText_1:
        for (i=0;i<BYTES_OF_PAPER_LINE;i+=2,j+=2)
        {
            if (char_flag)
                char_temp = ((WORD)linep[0]<<8)+linep[1];
            if ((i>=Graph_PosX)&&(i<(Graph_Width+Graph_PosX)))
            {
                if (((i+1)-Graph_PosX)<Graph_Width)
                    Set_Hot_DataW( ((WORD)pGraBuf[j]<<8)+pGraBuf[j+1] | char_temp, i);
                else
                    Set_Hot_DataW( ((WORD)pGraBuf[j]<<8) | char_temp , i);
            }
            else
            {
                Set_Hot_DataW( char_temp , i );
            }
            linep+=2;
        }

#if CASE_PT723F_RJ
		//HJ ��ӡ��ͬ������//
		if(f_repeatOnce == 1)
		{
			f_repeatOnce = 0;

			Send_blank_dot(BYTES_OF_SHUANG_ZHAN_GAP);
			j -= BYTES_OF_PAPER_LINE;
			linep -= BYTES_OF_PAPER_LINE;
			goto CreatGraphicWithText_1;

		}
#endif

#else //HJ SPI�����ֽڷ���//
CreatGraphicWithText_2:
		//HJ ����һ��������
        for (i=0;i<BYTES_OF_PAPER_LINE;i++,j++)
        {
            if ((i>=Graph_PosX)&&(i<(Graph_Width+Graph_PosX)))
            {
                Set_Hot_Data( *linep | pGraBuf[j] , i );
            }
            else
            {
                Set_Hot_Data( *linep , i );
            }
            linep++;
        }

#if CASE_PT723F_RJ
		//HJ ��ӡ��ͬ������//
		if(f_repeatOnce == 1)
		{
			f_repeatOnce = 0;

			Send_blank_dot(BYTES_OF_SHUANG_ZHAN_GAP);
			j -= BYTES_OF_PAPER_LINE;
			linep -= BYTES_OF_PAPER_LINE;
			goto CreatGraphicWithText_2;

		}
#endif

#endif


#if GROUPMODE==2
        //�������һ���ֽ�ʱ,�趨��������������
        Set_Hot_Group();
#endif

    }
    else
    {

        //��ʼ�͵���֮ǰ,���б�Ҫ�ĳ�ʼ��
        Prn_LineDots = 0;
#if GROUPMODE==2
        memset(Prn_GroupDots,0,sizeof(Prn_GroupDots));
#endif

        if (char_flag)
        {

#if CASE_PT723F_RJ
			//HJ �������ӡ��࣬���Ϳհ׵�������//
			if(!BIT(ApplVar.Prn_Command, PRN_STUB_Mode))
			{
				Send_blank_dot(BYTES_OF_PAPER_LINE + BYTES_OF_SHUANG_ZHAN_GAP);
				f_repeatOnce = 0;
			}
			else
			{
				f_repeatOnce = 1;
			}
#endif

#if WORDorBYTE
CreatGraphicWithText_3:
			for (i=0;i<BYTES_OF_PAPER_LINE;i+=2)
            {
                Set_Hot_DataW( ((WORD)linep[0]<<8)+ linep[1], i );
                linep+=2;
            }

#if CASE_PT723F_RJ
			//HJ ��ӡ��ͬ������//
			if(f_repeatOnce == 1)
			{
				f_repeatOnce = 0;

				Send_blank_dot(BYTES_OF_SHUANG_ZHAN_GAP);
				linep -= BYTES_OF_PAPER_LINE;
				goto CreatGraphicWithText_3;
			}
#endif

#else //HJ �ֽ�SPI��ʽ//
CreatGraphicWithText_4:

            for (i=0;i<BYTES_OF_PAPER_LINE;i++)
            {
                Set_Hot_Data( *linep , i );
                linep++;
            }

#if CASE_PT723F_RJ
			//HJ ��ӡ��ͬ������//
			if(f_repeatOnce == 1)
			{
				f_repeatOnce = 0;

				Send_blank_dot(BYTES_OF_SHUANG_ZHAN_GAP);
				linep -= BYTES_OF_PAPER_LINE;
				goto CreatGraphicWithText_4;
			}
#endif

#endif
        }


        else
        {
#if WORDorBYTE
            for (i=0;i<BYTES_OF_HEAT_LINE;i+=2)
            {
                Set_Hot_DataW( 0 , i );
            }
#else
            for (i=0;i<BYTES_OF_HEAT_LINE;i++)
            {
                Set_Hot_Data( 0 , i );
            }
#endif
        }


#if GROUPMODE==2
        //�������һ���ֽ�ʱ,�趨��������������
        Set_Hot_Group();
#endif

        if (TextIdx_ForGraph >= Prn_GraphTextMax && !Prn_LineIndex && !Feed_BlankLines)
        {
            TextIdx_ForGraph = 0;
            Graph_LineCurrent = 0;
            Prn_GraphTextMax = 0;
            Prn_Status.g_bGraphicOver = true;//  A task for print graphic finished
        }
//		TextIdx_ForGraph = 0;
//		Graph_LineCurrent = 0;
    }

	//HJ ���桢���Ȳ���ʱ
    Start_Hot();
}

void GetTaskFromPool()
{

    BYTE sGraph_idx,char_cnt,sGrphPos;
    struct GRAPH_DEFINE * sGraInfo;


#if POWERCTRL
    pwrGetStatus(GET_VIN_STATUS);//ccr20131015
#endif

    Prn_LineIndex = 0;///////////////

    if (ApplVar.PoolPushIn == ApplVar.PoolPopOut)
    {
        Prn_Status.g_bPrintOver = true;
        Prn_FeedCount = 0;
    }
    else
    {
        Prn_PoolCurrent = (ApplVar.PoolPopOut + 1);
        if (Prn_PoolCurrent>=MAX_PRNPOOL) Prn_PoolCurrent = 0;

        sGraph_idx = ApplVar.PoolForPrint[Prn_PoolCurrent].GraphicNo;
        char_cnt = ApplVar.PoolForPrint[Prn_PoolCurrent].Length;
        ApplVar.Prn_Command = ApplVar.PoolForPrint[Prn_PoolCurrent].Prn_Command;

        if (sGraph_idx)// && BIT(ApplVar.Prn_Command,PRN_GRAPHIC_Mode) //print graphic
        {
            if (sGraph_idx>1 && sGraph_idx<=GRAPHICMAX)
            {
                pGraBuf = (BYTE*)Graphic_Data[sGraph_idx-1];
                sGraInfo =(struct GRAPH_DEFINE *)gra_info[sGraph_idx-1];
            }
            else if (InfoSelf_Graph.cGrapCols)
            {//=1ʱ��Ϊ�û��Զ���ͼƬ
                pGraBuf = Self_Graph;
                sGraInfo =&InfoSelf_Graph;
            }
            else//���Զ���ͼƬ,Ĭ�ϴ�ӡ��һ��ͼƬ
            {
                pGraBuf = (BYTE*)Graphic_Data[0];
                sGraInfo =(struct GRAPH_DEFINE *)gra_info[0];
            }

            if (sGraInfo->cGrapCols)
            {//Ϊ��ЧͼƬ����
                Prn_Status.g_bPrintGraph = true;
                Prn_Status.g_bGraphicOver = false;
                sGrphPos = ApplVar.PoolForPrint[Prn_PoolCurrent].data[0];

                Prn_GraphTextMax = char_cnt;//text lines for graphic

                Graph_Offset = (sGraInfo->cLabels) * (sGraInfo->cByteALine + 1);
                Graph_SizeInBytes = sGraInfo->cGrapSize-Graph_Offset;
                Graph_Width = sGraInfo->cGrapCols*sGraInfo->cWidthAChar/8;//Ϊ���ֽ�Ϊ��λ��ͼƬ���
                if (sGrphPos)
                    Graph_PosX = sGrphPos*sGraInfo->cWidthAChar/8;//ʹ��ָ����ӡλ��(�ֽ�λ��)
                else
                    Graph_PosX = sGraInfo->cPrintAt*sGraInfo->cWidthAChar/8;//ʹ��Ĭ�ϴ�ӡλ��
                Graph_DotsLineMax = Graph_SizeInBytes / Graph_Width;
                Graph_Remain = Graph_SizeInBytes % Graph_Width;
                Graph_LineCurrent = 0;
                TextIdx_ForGraph = 0;
                Feed_BlankLines = 0;

                if (Prn_GraphTextMax)
                    CreatGraphicWithText();
                else
                    CreateGraphicDots();
            }
            //Ϊ��ЧͼƬ��Prn_LineIndex=0, ��ֽ����
/*
            else
            {//Ϊ��ЧͼƬ����ӡһ������
                ApplVar.PoolForPrint[Prn_PoolCurrent].data[0]=' ';
                ApplVar.PoolForPrint[Prn_PoolCurrent].Length = 1;
                ApplVar.PoolForPrint[Prn_PoolCurrent].Prn_Command = CMDP_R;
                ApplVar.Prn_Command = CMDP_R;
                SetFontOffset_char(1);
            }
*/
        }
#if ENCUTTER
        else if (BIT(ApplVar.Prn_Command,PRN_CUTRESET_Mode | PRN_CUTF_Mode | PRN_CUTH_Mode))
        {//reset cutter,cut paper
            Start_Motor(ApplVar.Prn_Command);
        }
#endif
        else
        {
            SetFontOffset_char(char_cnt);
        }
    }
}
//����ӡֽ����ʾ������ʾ
void Check_Paper(void)
{
    //ȱֽ���ʹ���
    Get_Printer_status();
    if (Printer_Status.g_bNOPAPER)
    {//��ֽ
        Bell(0);
#if !defined(CASE_ASCIIDISPLAY)
        DispSt1C(Msg[CWXXI40].str);
#else
        PutsO_Only(Msg[ERROR_ID(CWXXI40)].str);
#endif

#if defined(FISCAL)
        if (TESTBIT(ApplVar.Fiscal_PrintFlag,(BIT0 | BIT2)))
        {//��ӡZ����ʱ���ȱֽ,��Ҫ���´�ӡZ����
            SETBIT(ApplVar.Fiscal_PrintFlag,BIT7);
        }
#endif

    }
    else if (Printer_Status.g_bPaperIn)
    {//����װ���ӡֽ
#if defined(CASE_ASCIIDISPLAY)
        PutsO_Saved();
#else
        ClsState1();
#endif
        Printer_Status.g_bPaperIn = 0;
    }
#if CASE_HANDUP
    else if (Printer_Status.g_bHANDUP)
    {//ѹ��̧��
        Bell(0);
#if defined(CASE_ASCIIDISPLAY)
        PutsO_Only(Msg[ERROR_ID(CWXXI39)].str);
#else
        DispSt1C(Msg[CWXXI39].str);
#endif
    }
    else if (Prn_Status.g_bHANDDN)
    {//ѹ��̧���ѹ��
#if defined(CASE_ASCIIDISPLAY)
        PutsO_Saved();
#else
        ClsState1();
#endif
        Printer_Status.g_bHANDDN = 0;
    }
#endif
}
/***********************************************************************************
// push data into the POOL
// INPUT:
//      *buf:   Text data for print
//      count:  Bytes in *buf must be print out
//      prnCMD: Command for TEXT ,must be one of:
                -PRN_DBLW_Mode        //double with print mode for text
                -PRN_DBLH_Mode        //double high print mode for text
                -PRN_RECEIPT_Mode     //print on receipt printer
                -PRN_STUB_Mode        //print on stub printer
                -PRN_GRAPHIC_Mode     //print a graphic
                -PRN_CUTF_Mode        //Cut paper full
                -PRN_CUTH_Mode        //Cut paper half
                -PRN_CUTRESET_Mode    //Cutter reset


// return:<0;POOL is full & the data don't push in
//        >=0;data has pushed into the pool and the value is the
//        length of the data

//REMARK:
//    if prnCMD is the GRAPHIC command:
//        buf[0] must be the number of the graphic.(1,2,3....)
//               buf[0]=0,stop attach the text;
//        buf[1] must be '0'(don't attache text)
//              or '1' (8 lines of Text must attache for the graphic)
//              or '2' (copy text from graphic)
//       buf[2] Postion by character of the graphic on paper(0,1,2,..,32), It's not the must,
//              =0,Print at the default position defind by the graphic
//    if prnCMD is the CUT PAPER command:
//        buf[0] must be the FULL(1) cut or HALF cut(0).
//
********************************************************************************/
int RSPrint(BYTE *buf, int count, BYTE prnCMD)
{
    struct GRAPH_DEFINE *sGraInfo;
    BYTE *sGraph;
    struct TPRN_POOL *sPrnPool;

    BYTE i;
    int  retval; /* value used in "goto out" statements */

#if (0)	//ccr2014-10-23testonly>>>>>>>>>>>>>>>
    PrnPowerOFF();
	if (buf) {
        xputs(buf);	xputc('\n');
	}
	return 1;
#else  //<<<<<<<<<<<<<<<<ccr2014-10-23testonly

    Check_Paper();
    if ((ApplVar.PoolPushIn + Graph_TextCount + 1)%MAX_PRNPOOL == ApplVar.PoolPopOut)
    {
        do
        {
//            rtc_Delayms(10);
//			msDelay(1000);

            i = (ApplVar.PoolPushIn + Graph_TextCount + 1)%MAX_PRNPOOL;
            if (i>ApplVar.PoolPopOut)
                i -= ApplVar.PoolPopOut;
            else
                i = ApplVar.PoolPopOut - i;
            Check_Paper();
        } while (i<3);//�ȴ����п���3���ռ�
    }

    if (count > PRNWIDTH+1)//include double high flag '@'
        count = PRNWIDTH+1;

    retval = 0;//set the flag: does not copy to pool

#if ENCUTTER
    if (BIT(prnCMD,PRN_CUTF_Mode | PRN_CUTH_Mode | PRN_CUTRESET_Mode))//Print graphic
    {
        if (++ApplVar.PoolPushIn>=MAX_PRNPOOL) ApplVar.PoolPushIn = 0;
        sPrnPool = &ApplVar.PoolForPrint[ApplVar.PoolPushIn];

        sPrnPool->Prn_Command = prnCMD;
        sPrnPool->GraphicNo = 0;
        sPrnPool->Length = 0;

        Start_Motor(prnCMD);
        return retval;

    }
#endif
    if (BIT(prnCMD,PRN_GRAPHIC_Mode) && !Prn_Status.g_bTextForGraph)//Print graphic
    {
        {//Ϊ��ӡͼƬ����
            if (count<=2)
                buf[2] = 0;// Use the default position
            if (count>=2 && buf[0]>0)
            {
                if (buf[1] == '0')//Print graphic  without textor
                {
                    Prn_Status.g_bTextForGraph = false;//no text fot over-print
                }
                else if (buf[1] == '1' || buf[1] == '2')//Print graphic with text
                {
                    Prn_Status.g_bTextForGraph = true;//set the flag for over-print text
                }
                memset(&GraphForPrint,0,sizeof(GraphForPrint));
#if (DOWN_GR_SIZE)
                if (buf[0]==1 //=1ʱ��Ϊ�û��Զ���ͼƬ
                    && GRB_Define.cGraSize>0 && GRB_Define.cTextFlag==0x80 //���û��Զ���ͼƬ����
                    && InfoSelf_Graph.cGrapCols==0) //ͼƬ����δת��
                    ChangeGRBToMyself();//��ת��ͼƬ����
#endif
                if (Prn_Status.g_bTextForGraph && buf[0]<=GRAPHICMAX)//=1ʱ��Ϊ�û��Զ���ͼƬ
                {// ����ӡ��ͼ����Ҫ��������ʱ,�Ѵ�ӡ������ʱ�洢��GraphForPrint��
                 // GraphForPrint[0]����Ҫ��ӡ��ͼ������,����GraphForPrint������ӵ�����
                    Graph_TextCount = 0;
                    GraphForPrint[0].Length = 1;    //flag-1: for some text must attached with the graphic
                    GraphForPrint[0].GraphicNo =  buf[0];//index of graphic
                    GraphForPrint[0].Prn_Command = prnCMD;
                    GraphForPrint[0].data[0] = buf[2];//Position of graphic


                    if (buf[0]==1 && InfoSelf_Graph.cGrapCols>0)//=1ʱ��Ϊ�û��Զ���ͼƬ
                        sGraInfo = &InfoSelf_Graph;
                    else
                        sGraInfo =(struct GRAPH_DEFINE *) gra_info[GraphForPrint[0].GraphicNo-1];

                    if ( buf[1] == '2' && (sGraInfo->cLabels>0))
                    {//copy text from graphic area
                        //��ȡͼ������Я�����ַ�����
                        Graph_TextLineMax = sGraInfo->cLabels;
                        if (Graph_TextLineMax>TEXTSOFGRAPH)
                            Graph_TextLineMax=TEXTSOFGRAPH;
                        sGraph = (BYTE*)Graphic_Data[GraphForPrint[0].GraphicNo-1];
                        retval = sGraInfo->cByteALine;
                        if (retval>PRNWIDTH)//GraphForPrint[].data[]
                            retval = PRNWIDTH;
                        for (i=1;i<(Graph_TextLineMax+1);i++)//*(sGraInfo->cByteALine+1))
                        {
                            memcpy(GraphForPrint[i].data,sGraph,retval);
                            sGraph+=sGraInfo->cByteALine;
                            GraphForPrint[i].Length = *sGraph++;
                            GraphForPrint[i].GraphicNo = 0;
                        }
                        Graph_TextCount=Graph_TextLineMax;
                        retval = 1;//exit after copy to pool
                    }
                    else
                    {
                        //����ͼ��߶�
                        retval = ((sGraInfo->cGrapSize-((sGraInfo->cLabels) * (sGraInfo->cByteALine + 1))) / (sGraInfo->cGrapCols*sGraInfo->cWidthAChar/8));
                        //����ͼ��������ӵ��ַ�����
                        Graph_TextLineMax = retval / (LINE_BLANK+TEXT_HIGH);

                        if (retval % (LINE_BLANK+TEXT_HIGH))	 //ͼ��߶ȳ����ַ�������ʱ
                            Graph_TextLineMax++;

                        if (Graph_TextLineMax>TEXTSOFGRAPH)
                            Graph_TextLineMax=TEXTSOFGRAPH;
                        return count;
                    }
                }
                else
                {
                    if (++ApplVar.PoolPushIn>=MAX_PRNPOOL) ApplVar.PoolPushIn = 0;
                    ApplVar.PoolForPrint[ApplVar.PoolPushIn].Length = 0;//flag-0: none text for graphic
                    ApplVar.PoolForPrint[ApplVar.PoolPushIn].GraphicNo = buf[0];
                    ApplVar.PoolForPrint[ApplVar.PoolPushIn].Prn_Command = prnCMD;
                    ApplVar.PoolForPrint[ApplVar.PoolPushIn].data[0] = buf[2];//Position of graphic
                    Start_Motor(prnCMD);
                    return count;
                }
            }
        }
    }

    if (Prn_Status.g_bTextForGraph)
    {//Ϊͼ���ӡ���ܵ��ӵ�����

        if (count==1 && buf[0]==0)
        {// ��ֹ���ܵ������� //

/*
            for (;Graph_TextCount<(Graph_TextLineMax);)//(sGraInfo->cByteALine+1))
            {
                Graph_TextCount++;
                GraphForPrint[Graph_TextCount].Length = 1;
                GraphForPrint[Graph_TextCount].GraphicNo = 0;
                GraphForPrint[Graph_TextCount].data[0] = ' ';
            }
*/
            Graph_TextLineMax = Graph_TextCount;
            retval = 1;//exit after copy to pool
        }

        if (Graph_TextCount>=Graph_TextLineMax)
        {//The maxim Count of the text for graphic is 7
            Prn_Status.g_bTextForGraph = false;//clean the over-print text flag

            GraphForPrint[0].Length = Graph_TextCount;//lines of Text for graphic

            for (i=0;i<=Graph_TextCount;i++)
            {
                if (++ApplVar.PoolPushIn>=MAX_PRNPOOL) ApplVar.PoolPushIn = 0;
                while (ApplVar.PoolPushIn==ApplVar.PoolPopOut)
                {//wait for a empty
                    Check_Paper();
                }
                memcpy(&ApplVar.PoolForPrint[ApplVar.PoolPushIn],&GraphForPrint[i],sizeof(GraphForPrint[i]));
            }

            Graph_TextCount = 0;

            if (retval)//exit after copy to pool
            {
                Start_Motor(prnCMD);
                return 1;
            }
        }
        else
            Graph_TextCount++;
    }
    if (Prn_Status.g_bTextForGraph)
    {// The text recived used for over-print on graphic
        sPrnPool = &GraphForPrint[Graph_TextCount];
    }
    else
    {
        if (++ApplVar.PoolPushIn>=MAX_PRNPOOL) ApplVar.PoolPushIn = 0;
        sPrnPool = &ApplVar.PoolForPrint[ApplVar.PoolPushIn];
    }
    // copy data to pool
#if FOR_POS

    (count<=PRNWIDTH)?(retval=count):(retval=PRNWIDTH);
    memcpy(sPrnPool->data,buf,retval);
    sPrnPool->Prn_Command = prnCMD;
    sPrnPool->GraphicNo = 0;

#else//for ECR>>>>>>>>>>>>>>

    sPrnPool->Prn_Command = prnCMD;
    sPrnPool->GraphicNo = 0;
    for (i=retval=0;i<count && buf[i] == ' ' && retval<PRNWIDTH;i++)
    {

        sPrnPool->data[retval] = buf[i];
        retval++;
    }
    if (i<count)
    {
        if (buf[i] == '@')//double high flag
        {
            SETBIT(sPrnPool->Prn_Command,PRN_DBLH_Mode);
            i++;
        }
//        else
//        {
//            CLRBIT(sPrnPool->Prn_Command,PRN_DBLH_Mode);
//        }


        for (;i<count && retval<PRNWIDTH;i++)
        {
            sPrnPool->data[retval] = buf[i];
            retval++;
        }
    }

#endif//FOR_POS

    sPrnPool->Length = retval;

    if (!Prn_Status.g_bTextForGraph)
    {
        Start_Motor(prnCMD);
    }

    return retval;
#endif
}


/*************************************************************************
  ���硢�ص硢ȱֽ�������δ��ӡ��ϵĵ����ݣ���ô������ɴ�ӡ
  ���ǣ��ڵ�һ��׷�ӵ�������ӡ��ϢRe-Print When Power ON
**************************************************************************/
void Start_When_Ready(const char *str)
{

    BYTE pushIDX,cmd;

    //�����δ��ɵĴ�ӡ�������������ӡ
    if (ApplVar.PoolPopOut!=ApplVar.PoolPushIn)
    {
        cmd = ApplVar.Prn_Command;
        if (str)
        {
            //������׷�ӵ�������ӡ��־��
            if (ApplVar.PoolPopOut==0)
                pushIDX = MAX_PRNPOOL-1;
            else
                pushIDX = ApplVar.PoolPopOut-1;

            if (pushIDX != ApplVar.PoolPushIn)
            {//��ӡ����δ��,׷������
                ApplVar.PoolForPrint[ApplVar.PoolPopOut].GraphicNo = 0;
                ApplVar.PoolForPrint[ApplVar.PoolPopOut].Length = PRNWIDTH-1;
                ApplVar.PoolForPrint[ApplVar.PoolPopOut].Prn_Command = CMDP_R;
                strncpy(ApplVar.PoolForPrint[ApplVar.PoolPopOut].data,str,PRNWIDTH);;
                ApplVar.PoolPopOut = pushIDX;
                cmd = CMDP_R;
			}
        }
        Prn_TaskNow = 0xff;
        Start_Motor(cmd);
    }
}
// get the printer status:Prn_Status
PRNSTATUS Get_Printer_status(void)
{

    Printer_Status.g_bHANDUP = 0;

    if (!TESTPAPER())//paper out
    {
        Prn_FeedCount = 0;
        Printer_Status.g_bNOPAPER = true;
        Printer_Status.g_bPaperIn = false;
    }
    else
    {
        if (Printer_Status.g_bNOPAPER)
        {
            Prn_FeedCount = 0;
            Printer_Status.g_bPaperIn = true;
            Printer_Status.g_bWaitPaper = false;
        }
        Printer_Status.g_bNOPAPER = false;
    }

    if (Prn_FeedCount>FEEDMAX)
        Printer_Status.g_bTOOHOT = true;

#if CASE_HANDUP
    if (!TESTHAND())//paper out
    {
        Printer_Status.g_bHANDUP = true;
        Printer_Status.g_bHANDDN = false;
    }
    else
    {
        if (Printer_Status.g_bHANDUP)
        {
            Printer_Status.g_bWaitPaper = false;
            Printer_Status.g_bHANDDN = true;
        }
        Printer_Status.g_bHANDUP = false;
    }
#endif

    return Printer_Status;
}

#if GROUPMODE==2
//===========================================================================
//���ݸ���ļ��ȵ���,���ɿ�����ϵļ�����,����޶ȼ��ټ��ȴ���
//Prn_GroupHot[n]�е�һλ��Ӧһ��������,
//�����������Գ�����ͬһ��Prn_GroupHot[n]��,��һ�ο��Լ��ȶ����.
//��Prn_GroupHot[n]=0ʱ,��ʾ���Ƚ���(��ֻ�����n��.
//===========================================================================

void  Set_Hot_Group()
{
//    WORD hot;
//    BYTE i,j;

    memset(Prn_GroupHot,0,sizeof(Prn_GroupHot));

#if DCPOWER //���õ�Դ���磬������������м���


#if (0)//POWERCTRL //HJ ���ü��ȷ���
    if (TESTBIT(PowerFlags,PWR_BY_BAT))
    {//ccr20131015��ع���,��������м���
        Prn_HotMAX = 6;
        Prn_GroupHot[0] = (PRN_DS1);
        Prn_GroupHot[1] = (PRN_DS2);
        Prn_GroupHot[2] = (PRN_DS3);
        Prn_GroupHot[3] = (PRN_DS4);
        Prn_GroupHot[4] = (PRN_DS5);
        Prn_GroupHot[5] = (PRN_DS6);
    }
    else
#endif
	{
	    Prn_HotMAX = 2;
	    Prn_GroupHot[0] = (PRN_DS1 | PRN_DS2 | PRN_DS3 );
	    Prn_GroupHot[1] = (PRN_DS4 | PRN_DS5 | PRN_DS6);
	}


#elif 1 //����Ҫ���ȵ����ݰ������ȵ������з������
    Prn_HotMAX = 0;

    for (i=0;i<GROUPS;i++)
    {
        hot =  Prn_GroupDots[i];

        if (hot)
        {//����Ҫ���ȵĵ�
            Prn_GroupDots[i] = 0;//��ʾ���鴦�����
            Prn_GroupHot[Prn_HotMAX] |= (1<<i);//��λ��i��Ҫ���ȱ�־,
            for (j=i+1;j<GROUPS;j++)
            {
                if (Prn_GroupDots[j])
                {
                    if ((hot+Prn_GroupDots[j])<=DOTS1GROUP)//ÿ�������ȵ���
                    {
                        hot += Prn_GroupDots[j];
                        Prn_GroupDots[j] = 0;   //��ʾ���鴦�����
                        Prn_GroupHot[Prn_HotMAX] |= (1<<j);//��λ��j��Ҫ���ȱ�־
                    }
                }
            }
            Prn_HotMAX++;
        }
    }
#else //��ȫ����DITRON�ķ��鷽ʽ
    Prn_HotMAX = 0;
    if (Prn_LineDots<=DOTS1GROUP)
    {//�ܵ���<=һ�����
        if (Prn_LineDots!=0)
        {//6��ȫ��һ�μ���,���ǽ������μ������
            Prn_HotMAX = 1;
            Prn_GroupHot[0] = (PRN_DS1 | PRN_DS2 | PRN_DS3 | PRN_DS4 | PRN_DS5 | PRN_DS6);
        }
    }
    else//�ܵ���>һ�����
    {
        i = Prn_GroupDots[0]+Prn_GroupDots[1]+Prn_GroupDots[2];//����ܵ���
        if (i<=DOTS1GROUP)
        {//����ܵ���<=һ�����
            if (i!=0)
            {//���ȫ������
                Prn_HotMAX = 1;
                Prn_GroupHot[0] = (PRN_DS1 | PRN_DS2 | PRN_DS3);
            }
        }
        else//����ܵ���>һ�����
        {
            Prn_HotMAX = 2;
            Prn_GroupHot[0] = (PRN_DS1);//�ȼ��ȵ�һ��
            Prn_GroupHot[1] = (PRN_DS2 | PRN_DS3);//�ټ��ȵڶ�,����
        }
        i = Prn_GroupDots[3]+Prn_GroupDots[4]+Prn_GroupDots[5];//�Ұ��ܵ���
        if (i<=DOTS1GROUP)
        {//�Ұ��ܵ���<=һ�����
            if (i!=0)
            {//�Ұ�ȫ������
                Prn_GroupHot[Prn_HotMAX++] = ((1<<(GROUPS/2))-1)<<(GROUPS/2);
            }
        }
        else//�Ұ��ܵ���>һ�����
        {
            if(Prn_GroupDots[3]+Prn_GroupDots[4]!=0)
            {
                Prn_GroupHot[Prn_HotMAX++] = (PRN_DS4 | PRN_DS5);//���ȵ�4,5��
            }
            Prn_GroupHot[Prn_HotMAX++] = (PRN_DS6);//���ȵ�6��

        }
    }
#endif
}
//=====================================================================
//����Prn_GroupHot���趨�ļ��Ȳ���,ʹ�ܼ��ȹܽ�
void Set_HotPIN()
{
    *(WORD *)PRT_DST_ADDR=Prn_GroupHot[Prn_HotIndex] & 0x7f;

}
#elif GROUPMODE==1

//---------------------------------------------------------------------------
//ÿ��ֻ���ӡ�����ͼ���һ���������������(��:64��),������Ϻ�,�ٷ�����һ��,
//ֱ�����е������ݷ��Ͳ���ɼ���. ���ּ��ȷ�ʽ���ŵ���,����޶ȼ��ټ��ȴ���
//һ������һ������������ݵ���,Prn_LineDots����һ�е�������,Prn_LineDots=0ʱ,����ȫ���������
void    Shift_Hot_Data()
{
    WORD hot;
    BYTE i,j,k,d;

    hot = 0;
    for (i=0;i<DOTSBUFF;i++)
    {
       d = BitsInByte[DotsOfCurrent[i]];
       if ((hot+d)<DOTS1GROUP)
       {
           Prn_LineDots-=d;//����ʣ�����
           hot += d;//ͳ�Ƶ�ǰ�����
           Send_Byte(DotsOfCurrent[i]);//�������͸���ӡ��
           DotsOfCurrent[i] = 0;

       }
       else
            break;//����һ�����
    }
    if (i<DOTSBUFF && hot<DOTS1GROUP)
    {//δ����һ������
        d=0x80;
        k = DotsOfCurrent[i];
        for (j=0;j<8;j++)
        {
            if (k & d)
            {//���Ե�Ϊ1
                hot++;//����1���ȵ�
                Prn_LineDots--;//�����ܵ���
                if (hot==DOTS1GROUP)
                {//һ����
                    d--;
                    DotsOfCurrent[i] &= d;//������ͳ��ĵ�
                    d = ~d;
                    k &= d;//����Ҫ�ͳ��ĵ�
                    break;
                }
            }
            d >>= 1;//������һ���Ƿ�Ϊ1
        }
        Send_Byte(k);//�������͸���ӡ��
        i++;
    }
    for (;i<DOTSBUFF;i++)
        Send_Byte(0);//ʣ�ಿ����0
}

#endif

#if (DEBUGONPC==0)

#if (defined(CASE_FORHANZI) )
/*******************************************************************
  ���ֿ�оƬ�ж�ȡ3�ֽڵĺ��ֵ���
  *****************************************************************/
void ReadHZKU(ULONG addr,BYTE *hzBuf)
{
    addr+=NOR_FLASH_ADDR;
    hzBuf[0]=FlashReadByte(addr);addr++;
    hzBuf[1]=FlashReadByte(addr);addr++;
    hzBuf[2]=FlashReadByte(addr);
}
#endif

#if (WORDorBYTE)
//��WORD��ʽ�����ݷ��͸���ӡ�� Send FONTS-Data to printer(384dots)
void    Set_Hot_DataW(WORD dot,BYTE pos)
{
     Send_Word(dot);

    Prn_LineDots += BitsInByte[dot & 0xff];//ͳ����Ҫ���ȵ��ܵ���
    Prn_LineDots += BitsInByte[dot>>8];//ͳ����Ҫ���ȵ��ܵ���

#if GROUPMODE==2
    Prn_GroupDots[pos/BYTES1GROUP]+=BitsInByte[dot>>8];//ͳ�Ƹ�����ȵ���
    Prn_GroupDots[(pos+1)/BYTES1GROUP]+=BitsInByte[dot & 0xff];//ͳ�Ƹ�����ȵ���
#endif

}

#else
//��BYTE��ʽ�����ݷ��͸���ӡ�� Send FONTS-Data to printer(384dots)
void    Set_Hot_Data(BYTE dot,BYTE pos)
{
    Send_Byte(dot);//���ֽڷ�ʽ��������

    Prn_LineDots += BitsInByte[dot];//ͳ����Ҫ���ȵ��ܵ���

#if GROUPMODE==2
    Prn_GroupDots[pos/BYTES1GROUP]+=BitsInByte[dot];//ͳ�Ƹ�����ȵ���
#endif

}
#endif

// Drive printer motor by one step:GPIO1
void  Drive_Motor(WORD phase)
{
    Prn_FeedCount++;
    Drive_On(phase);
}

#if ENCUTTER
// Drive printer motor by one step:GPIO1
void  Drive_CutMotor(WORD phase)
{
    Prn_FeedCount++;
    CutDrive_On(phase);
}
#endif
// Set the speed of motor: RIT
void Set_Motor_Speed(ULONG speed)
{
#if defined(CASE_FORHANZI)
    (speed<Prn_HZTime)?(TIM2->ARR = Prn_HZTime):(TIM2->ARR = speed);
#else
    TIM2->ARR = speed;
#endif
    /* Generate an update event to reload the Prescaler */
    //TIM2->EGR = TIM_PSCReloadMode_Immediate;
    StartTimer(TIM2);
}

// Set the hot time
void Start_Hot()
{
Latch_Data();

    if (Prn_LineDots)//Prn_LineDots=0ʱ,�������
    {
//        Latch_Data();
        Prn_CalcHotTime();
        if (Prn_HotIndex>=Prn_HotMAX)//��һ�����ݼ������
        {
            Prn_HotIndex=0;
#if GROUPMODE==0
#if GROUPS>1
        Hot_On0(HOT1_PIN);//�ֶ������
#else
        Hot_On0(HOTMASK0);//ֻ����һ�μ���
#endif
#elif GROUPMODE==1
        Hot_On0(HOTMASK0);//ֻ����һ�μ���
#else//GROUPMODE==2
        Set_HotPIN();//����ϲ�����
#endif

        Set_HotTime(Prn_HotTime);
    }
        else//���ڼ�����,��������Ϊ0xff��,��TIM3_IRQHandler�лὫ����Ϊ0,��˻�������һ�����
            Prn_HotIndex=0xff;
    }
    else
        PrnHotOFF();//!!!!@@@@@@@@@!!!!!!
}


#endif

//Stop print motor
void Stop_Motor()
{
    Set_Motor_Speed( TIMESTOP );
    Prn_AccStep = 0;
    Prn_TaskNow = TASK00_Stop;
}

//Pause print motor when too hot or to far
void Suspend_Motor()
{
    PrnHotOFF();
    Drive_Off(); //stop print motor
    Set_Motor_Speed( TIMESTOP );
    PrnPowerOFF();
    Prn_AccStep = 0;
    Prn_Jphase = 0;
    Prn_Status.g_bSuspend = true;//suspend when too hot or too far of feed
    Prn_Delay = 1;//��ӡ����ͣ��ʱ��ʼ
}

//start motor
void Start_Motor(BYTE prnCMD)
{
    if (Prn_TaskNow<=0)
//        && !Prn_Status.g_bNOPAPER
//        && !Prn_Status.g_bHANDUP
//        && !Prn_Status.g_bTOOHOT
//        && !Prn_Status.g_bTOOHOT)//motor stoped
    {
        Prn_FeedCount = Prn_Delay = 0;
        Prn_Status.g_bPrintOver = false;//some data must be print out
        ApplVar.Prn_Command = prnCMD;
#if ENCUTTER
        if (BIT(prnCMD,PRN_CUTRESET_Mode | PRN_CUTF_Mode | PRN_CUTH_Mode))
        {
            PrnPowerON();
            Drive_CutMotor(CPHSTART);//out
        }
        else
#endif
			if (!Prn_Status.g_bWaitPaper)
            {
                PrnPowerON();
             	Drive_Motor(PHSTART);//out
            }
        Set_Motor_Speed( TIMESTART );
        Prn_Jphase = 0;
        Prn_AccStep = 0;
        Prn_TaskNow = TASK01_Start;
#if DEBUGONPC
        pcStart_Motor();
#endif
    }
    else
        StartTimer(TIM2);//ccr2014-08-19 ʹ�ܼ�ʱ��
}
//Restart motor after motor paused
void Restart_Motor()
{
    Prn_Status.g_bTOOHOT = false;
    Prn_Status.g_bSuspend = false;
    Prn_FeedCount = Prn_Delay = 0;
    {
        PrnPowerON();
        Drive_Motor(PHSTART);//out
        Set_Motor_Speed( TIMESTART );
        Prn_Jphase = 0;
        Prn_AccStep = 0;

#if DEBUGONPC
        pcStart_Motor();
#else
//?????        LPC_RIT->RICTRL |= RIT_CTRL_TEN;//Enable counter
#endif

    }
}

//POS command ---------------------------------------------------------------------------------------------------
#if DEBUGONPC==0

void Excute_data(BYTE ch);

/*********************************************************************************
*
* File: ESCPOS.C
*
*********************************************************************************/
void Excute_ESC(void);		   	// ESC sequence
void Excute_GS(void);		   		// GS sequence
void Excute_LF(void);		   		//LF (Line-feed)
void Excute_FF(void);		   		//FF (form-feed)
void Excute_CR(void);		   		//CR
void Excute_DLE(void);		   	//**DLE (real time status trasmission)

#define MAINCOMMAX  6

const type_Command  MAINCOMMAND[MAINCOMMAX]=
{
		 {0x1B,		*Excute_ESC},		   	// ESC sequence
		 {0x1D,		*Excute_GS},		   		// GS sequence
		 {0x0A,		*Excute_LF},		   		//LF (Line-feed)
		 {0x0C,		*Excute_FF},		   		//FF (form-feed)
		 {0x0D,		*Excute_CR},		   		//CR
		 {0x10,		*Excute_DLE},		   	//**DLE (real time status trasmission)

};

#define ESCCOMMAX  5	//58 20051013 test

void sel_print_mode(void);                                 // Select print mode
void turn_underline_mode(void);                            //Turn underline mode on/off
void total_cut(void);                                      //*Total cut
void partial_cut(void);                                    //*Partial cut
void tx_printer_status(void);                              //** Trasmit printer status


const type_Command  ESCCOMMAND[ESCCOMMAX]=
{
		{'!',		*sel_print_mode},                                 // Select print mode
		{'-',		*turn_underline_mode},                            //Turn underline mode on/off
		{'i',		*total_cut},                                      //*Total cut
		{'m',		*partial_cut},                                    //*Partial cut
		{'v',		*tx_printer_status},                              //** Trasmit printer status

};


#define GSCOMMAX  5
void tx_status(void);              // Trasmit status
void sel_raster_bit_image(void);		  // Block inmage mode
void Download_Image(void);              // download image
void Print_Download_Image(void);              // print download image
void Cut_Paper(void);               //cut paper
//void TestFlashBWrite(void);               //Send CCLIB to host

const type_Command  GSCOMMAND[GSCOMMAX]=
{
		{ 'r',		*tx_status},              // Trasmit status
		{ 'v',		*sel_raster_bit_image},		  // Block inmage mode
		{ '*',		*Download_Image},              // download image
		{ '/',		*Print_Download_Image},              // print download image
        { 'V',      *Cut_Paper},                 //cut paper
//        { 0xff,     *TestFlashBWrite}                 //cut paper
};



//////////////////////////////////////////////////////////////////////////////
// ESC+ command from Host
void Print_ESC_Command()
{
    BYTE carattere;
    int	sLp;

    while (true)
    {
        if (UARTGet(PORTHOST,&carattere,0)==true)
        {
            for (sLp=0;sLp<MAINCOMMAX;sLp++)
                if (carattere==MAINCOMMAND[sLp].Command)
                {
                    (*(MAINCOMMAND[sLp].Procedure))();

                    break;
                }
            if (sLp==MAINCOMMAX)
                Excute_data(carattere);	//gestione dati da stampare
        }
    }// end for(;;) loop
}


/******************************************************************
 Function:����Ҫ��ӡ������
 Input	: riceve in ch il carattere da da caricare nella riga di stampa
 Describe::   Gestisce i dati da stampare
******************************************************************/
void Excute_data(BYTE ch)
{

//	if(ch <' ')	return;// ���ô����,�����ܽ��ܴ���Ӵ��ڷ����Ĵ�ӡͼƬ������


    if (DataFromHost.Length>PRNWIDTH)
        DataFromHost.Length = PRNWIDTH;
    if (DataFromHost.Length==PRNWIDTH)
    {
        Excute_CR();
    }

    if (DataFromHost.Length<PRNWIDTH)
    {
        DataFromHost.data[DataFromHost.Length]=ch;
        DataFromHost.Length++;
    }

}



/******************************************************************
 Function: void Excute_ESC(void)
 Describe::   Elabora tutte le sequenze di ESCAPE
******************************************************************/
void Excute_ESC()
{
	BYTE ch;
	int	sLp;

	// attende un carattere con un timeout di 60 secondi
	if(UARTGet(PORTHOST,&ch,DELAYHOST)==false)
		return;

	for (sLp=0;sLp<ESCCOMMAX;sLp++)
		if (ch==ESCCOMMAND[sLp].Command)
		{
			(*(ESCCOMMAND[sLp].Procedure))();
			return;
		}
    Excute_data(ch);
}


/******************************************************************
 Function: void Excute_GS(void)
 Describe::   Elabora tutte le sequenze di GS
******************************************************************/
void Excute_GS(void)
{

	BYTE 	ch;
	int		sLp;
	// attende un carattere con un timeout di 60 secondi

	if(UARTGet(PORTHOST,&ch,DELAYHOST)==false)
		return;

	for (sLp=0;sLp<GSCOMMAX;sLp++)
		if (ch==GSCOMMAND[sLp].Command)
		{
			(*(GSCOMMAND[sLp].Procedure))();
			return;
		}
    Excute_data(ch);

}



/******************************************************************
 Function: void Excute_LF(void)
 Describe: print out and then feed 1 line
******************************************************************/
void Excute_LF(void)
{
    BYTE cpMode = DataFromHost.Prn_Command;
    if (DataFromHost.Length)
        Excute_CR();
    else
    {
        DataFromHost.Prn_Command = CMDP_R;
        Excute_CR();
        DataFromHost.Prn_Command = cpMode;
    }
}




/******************************************************************
 Function: void Excute_FF(void)
 Describe: Feed 15 lines
******************************************************************/
void Excute_FF(void)
{
    BYTE cpMode = DataFromHost.Prn_Command;
    int i;

    if (DataFromHost.Length)
        Excute_CR();

    DataFromHost.Prn_Command = CMDP_R;
    for (i=0;i<15;i++)
    {
        Excute_CR();
    }
    DataFromHost.Prn_Command = cpMode;
}


/******************************************************************
 Function: void Excute_CR(void)
 Describe:
******************************************************************/
void Excute_CR(void)
{
    SETBIT(DataFromHost.Prn_Command,CMDP_R);
    CLRBIT(DataFromHost.Prn_Command,PRN_GRAPHIC_Mode | PRN_CUTF_Mode | PRN_CUTH_Mode);
    DataFromHost.GraphicNo = 0;
    RSPrint(DataFromHost.data,DataFromHost.Length,DataFromHost.Prn_Command);
    DataFromHost.Length = 0;

}



/******************************************************************
 Function: void Excute_DLE(void)
 Describe::   Gestisce il DLE (real time status trasmission)

******************************************************************/
void Excute_DLE(void)
{
	BYTE ch;
	WORD PrnStatus=0;

	// attende un carattere (EOT) con un timeout di 60 secondi
	if(UARTGet(PORTHOST,&ch,DELAYHOST)==false || ch != EOT)
		return;
	if(UARTGet(PORTHOST,&ch,DELAYHOST)==false || ch <1 || ch>6)
		return;
    Get_Printer_status();

	switch (ch){
	case 2:
		if (Printer_Status.g_bHANDUP)
			PrnStatus |= 0x04;
	case 1:
		PrnStatus |= 0x12;
		if (Printer_Status.g_bNOPAPER || Printer_Status.g_bHANDUP )
			PrnStatus |= 0x40;
		break;
	case 3:
		if (Printer_Status.g_bHANDUP)
			PrnStatus |= 0x20;
		break;
	case 4:
		if (Printer_Status.g_bNOPAPER)
			PrnStatus |= 0x6c;
		break;
	}
	UARTSend(PORTHOST,PrnStatus);
}


//*****************************************************************************************************


/* [ ESC + '!' + n ]
* void sel_print_mode(void)
*
*  Select print mode
*  Attende altro carattere.
*/
void sel_print_mode(void)
{
    BYTE ch;

	if(UARTGet(PORTHOST,&ch,DELAYHOST)==false)
		return;

	if(ch & 0x10){
		SETBIT(DataFromHost.Prn_Command,PRN_DBLH_Mode);
	}else{
        CLRBIT(DataFromHost.Prn_Command,PRN_DBLH_Mode);
	}
	if(ch & 0x20){
        SETBIT(DataFromHost.Prn_Command,PRN_DBLW_Mode);
	}else{
        SETBIT(DataFromHost.Prn_Command,PRN_DBLW_Mode);
	}
}



/* [ ESC + '-' + n ]
* void turn_underline_mode(void)
*
*  Turn underline mode on/off
*  Attende altro carattere.
*/
void turn_underline_mode(void)
{
    BYTE ch;
				// attende un carattere con un timeout di 60 secondi
	if(UARTGet(PORTHOST,&ch,DELAYHOST)==false)
		return;

	return;
}


/* [ ESC + '@']
* void Reset_printer(void)
*
*  inizialize printer
*  Attende altro carattere.
*/
void Reset_printer(void)
{
#if ENCUTTER
    RSPrint(0,0,PRN_CUTRESET_Mode);
#endif
}





/* [ ESC + 'i']
* void total_cut(void)
*
*  Total cut
*  .
*/
void total_cut(void)
{

    BYTE cpMode = DataFromHost.Prn_Command;
    if (DataFromHost.Length)
        Excute_CR();

    DataFromHost.Prn_Command = PRN_CUTF_Mode;
    RSPrint(DataFromHost.data,0,DataFromHost.Prn_Command);
    DataFromHost.Prn_Command = cpMode;
	return;
}



/* [ ESC + 'm']
* void partial_cut(void)
*
*  Partial cut
*  .
*/
void partial_cut(void)
{
// qui deve gestire la sequenza di escape come total_cut()
    BYTE cpMode = DataFromHost.Prn_Command;
    if (DataFromHost.Length)
        Excute_CR();

    DataFromHost.Prn_Command = PRN_CUTH_Mode;
    RSPrint(DataFromHost.data,0,DataFromHost.Prn_Command);
    DataFromHost.Prn_Command = cpMode;
    return;

}

/* [ GS + 'V' + m + n]
* void Cut_Paper(void)
*
*  Partial cut
*  .
*/
void Cut_Paper()
{

    BYTE ch;
    BYTE cpMode = DataFromHost.Prn_Command;

    if(UARTGet(PORTHOST,&ch,DELAYHOST)==false)
        return;

    if (DataFromHost.Length)
        Excute_CR();

    if (ch==0 || ch=='0' || ch==65)
    {//Executes a full cut (cuts the paper completely).
        DataFromHost.Prn_Command = PRN_CUTF_Mode;
    }
    else if (ch==1 || ch=='1' || ch==66)
    {// Executes a partial cut (one point left uncut)
        DataFromHost.Prn_Command = PRN_CUTH_Mode;
    }
    else if (ch==2 || ch=='2')
    {//reset cutter
        DataFromHost.Prn_Command = PRN_CUTRESET_Mode;
    }
    else
        return;

    RSPrint(DataFromHost.data,0,DataFromHost.Prn_Command);
    DataFromHost.Prn_Command = cpMode;
    return;

}



/* [ ESC + 'v']
* void tx_printer_status(void)
*
*  Trasmit printer status
*  .
*/
void tx_printer_status(void)
{

	WORD PrnStatus=0;


    Get_Printer_status();

    if (Printer_Status.g_bNOPAPER)
		PrnStatus |= 0x05;
	if (Printer_Status.g_bHANDUP)
		PrnStatus |= 0x42;

    UARTSend(PORTHOST,PrnStatus);

}


/* [ GS + 'V' + m + n ]
* void sel_cut_mode_cut_paper(void)
*
*  Set printing area width
*  Attende altri 2 caratteri.
*/
void sel_cut_mode_cut_paper(void)
{
	BYTE m,n;

	if(UARTGet(PORTHOST,&m,DELAYHOST)==false)
		return;
	if(m==66 || m==65){
		if(UARTGet(PORTHOST,&n,DELAYHOST)==false)
			return;

	}

    total_cut();//ccr 060331
}




/* [ GS + 'r' + n ]
* void tx_status(void)
*
*  Trasmit status
*  Attende altro carattere.
*/
void tx_status(void)
{
	BYTE ch;
	WORD PrnStatus;

				// attende un carattere con un timeout di 60 secondi
	if(UARTGet(PORTHOST,&ch,DELAYHOST)==false)
		return;

	if( (ch != 1) && (ch !=2) && (ch!=49) && (ch !=50))
		return;

	ch &= 0x0f;

    Get_Printer_status();

    if (Printer_Status.g_bNOPAPER)/* ��ֽ */
        PrnStatus |= 0x03;
    if (Printer_Status.g_bHANDUP)/* ѹ��̧�� */
        PrnStatus |= 0x0c;

    UARTSend(PORTHOST,PrnStatus);
}


//esegue l'operazione inversa della funzione AToH()
BYTE *HToA(BYTE ch, BYTE *ptr)
{
	BYTE	h;
	h=(ch>>4);
	if(h<=9)
		*ptr=h+'0';
	else
		*ptr=h+'A'-0xA;

	h=(ch & 0x0F);
	if(h<=9)
		*(ptr+1)=h+'0';
	else
		*(ptr+1)=h+'A'-0xA;

	*(ptr+2)=NULL;

	return(ptr);
}



// converte buffer binario 'src' in buffer ASCII-HEX 'dst' e termina la stringa con NULL
void BuffHToA(BYTE *src, BYTE *dst, BYTE len,BYTE space)
{
	BYTE i,j,ch;
	for(i=0,j=0;i<len;i++){
		ch=src[i];
		(void)HToA(ch, (BYTE *)(&dst[j]));
		if(space==TRUE){
			dst[j+2]=' ';
			j++;
		}
		//i++;
		j +=2;
	}
	dst[j]=0;

}

// elabora buffer binario in ASCI convertendo i caratteri non visualizzabili in '.'
BYTE *ConvAsci(BYTE *src,BYTE *dst,BYTE len)
{
	BYTE i;
	for(i=0;i<len;i++){
		if((src[i] <' ') || (src[i] > '~'))
			dst[i]='.';
		else
			dst[i]=src[i];

	}
	dst[i]=NULL;
	return(dst);
}



// converte intero in stringa ASCII nel buffer puntato da buff, termina stringa con NULL
// omette i zeri a sinistra
void itoa(WORD n,BYTE *buff)
{
	WORD i;
	BYTE j,flag;

	j=0;
	for(i=10000;i;i/=10){
		flag = n/i;
		buff[j]=flag+0x30;
		n=n- flag * i;	//n=resto della divisione fatta in precedenza
		if((j>0)||(buff[0]!='0'))
			j++;
	}
	if(j==0){
//		buff[j]='0';
		j++;
	}
	buff[j]=0;
}



/* [ GS + 'v' + c +m+xl+xh+yl+yh d1+...+dk] ��ӡһ�������ͼ��  //
* void sel_raster_bit_image(void)
* _______xl+xh*256(ÿ���ֽ���)________
 /                                    \
*--------------------------------------\
*-------------------------------------- |
*-------------------------------------- |
*-------------------------------------- |
*-------------------------------------- |yl+yh*256 (����)
*-------------------------------------- |
*-------------------------------------- |
*-------------------------------------- |
*-------------------------------------- |
*--------------------------------------/
*k=(xl+xh*256)*(yl+yh*256)
*  Graphic command in emulaztion TM-T88II
*  wait for ather 6 char
*
* To adapt T88II resolution (180 dpi)  to our printer resolution (203 dpi)
* add 1 dot every 9 dot
*
* To adapt T88II graphic line to our printer 60 mm 2 dot every 7 dot are in logic OR
*
*/

void sel_raster_bit_image(void)
{

	BYTE 	c,m,xl,xh,yl,yh;
	WORD	LineByte,TotBytes,i;

	if(UARTGet(PORTHOST,&c,DELAYHOST)==false)
		return;


	if(UARTGet(PORTHOST,&m,DELAYHOST)==false)
		return;
	if(UARTGet(PORTHOST,&xl,DELAYHOST)==false)
		return;
	if(UARTGet(PORTHOST,&xh,DELAYHOST)==false)
		return;
	if(UARTGet(PORTHOST,&yl,DELAYHOST)==false)
		return;
	if(UARTGet(PORTHOST,&yh,DELAYHOST)==false)
		return;


	LineByte=xl+xh*256;// һ�����ݵ��ֽ���Ŀ //
	TotBytes = LineByte * (yl+yh*256);// �ܹ����� //
    if (TotBytes<SELFGRASIZE && LineByte<BYTES_OF_PAPER_LINE)
    {

        InfoSelf_Graph.cGrapCols = LineByte;
        InfoSelf_Graph.cLabels = 0;
        InfoSelf_Graph.cPrintAt = 0;
        InfoSelf_Graph.cWidthAChar = 8;
        InfoSelf_Graph.cHighAChar = 24;
        InfoSelf_Graph.cByteALine = 0;
        InfoSelf_Graph.cGrapSize = TotBytes;

        for (i=0;i<TotBytes;i++)
        {
            if(UARTGet(PORTHOST,&Self_Graph[i],DELAYHOST)==false)
                return;
        }

        xl = DataFromHost.Prn_Command;
        if (DataFromHost.Length)
            Excute_CR();

        DataFromHost.Prn_Command = PRN_GRAPHIC_Mode;
        DataFromHost.data[0] = 1;
        DataFromHost.data[1] = '0';


        RSPrint(DataFromHost.data,2,DataFromHost.Prn_Command);
        DataFromHost.Prn_Command = xl;
        return;


    }

}

/* [GS+*+x+y+d1+.....+dx*y*8]
*Defines a downloaded bit image using (x*8) dots in the
*horizontal direction and (y*8) dots in the vertical direction.
* d indicates the bit image data.
*/
void Download_Image()              // download image
{


    BYTE 	xl,yl;
    WORD	LineByte,TotBytes,i;

    if(UARTGet(PORTHOST,&xl,DELAYHOST)==false)
        return;
    if(UARTGet(PORTHOST,&yl,DELAYHOST)==false)
        return;


    LineByte=xl;// һ�����ݵ��ֽ���Ŀ //
    TotBytes = LineByte * (yl*8);// �ܹ����� //
    if (TotBytes<SELFGRASIZE && LineByte<BYTES_OF_PAPER_LINE)
    {
        InfoSelf_Graph.cGrapCols = LineByte;
        InfoSelf_Graph.cLabels = 0;
        InfoSelf_Graph.cPrintAt = 0;
        InfoSelf_Graph.cWidthAChar = 8;
        InfoSelf_Graph.cHighAChar = 24;
        InfoSelf_Graph.cByteALine = 0;
        InfoSelf_Graph.cGrapSize = TotBytes;

        for (i=0;i<TotBytes;i++)
        {//recive graphic data from host
            if(UARTGet(PORTHOST,&Self_Graph[i],DELAYHOST)==false)
                return;
        }
    }

}


/* [GS+/+m+t]
* Print bit image
* if m<=GRAPHICMAX, Print bitmap from ROM
* if m=1,Print downloaded bit image by Download_Image
* if m<>0 and m<=GRAPHICMAX, t is the text flag
*      t = '0',don't attach text
*      t = '1',Attach 8 lines of text from host
*      t = '2',Attach text from graphic
*/
void Print_Download_Image()              // print download image
{
	BYTE m,t,j;

	if(UARTGet(PORTHOST,&m,DELAYHOST)==false)
		return;

    if (m==1)
    {//print graphic dowload from host
        if(UARTGet(PORTHOST,&t,DELAYHOST)==false)
            return;//text attribute:'0'-no text;'1'-attached text from host;'2'-attached text from grphia

        if (InfoSelf_Graph.cGrapSize)
        {
            m = DataFromHost.Prn_Command;//save Prn_mode
            if (DataFromHost.Length)
                Excute_CR();// print out the text recived

            DataFromHost.Prn_Command = CMDP_PRGRA;
            DataFromHost.data[0] = 1;
            DataFromHost.data[1] = t;
            Prn_Status.g_bTextForGraph = false;

            RSPrint(DataFromHost.data,2,DataFromHost.Prn_Command);
            DataFromHost.Length = 0;
            DataFromHost.Prn_Command = m;
        }
    }
    else if (m<=GRAPHICMAX)
    {
        j = DataFromHost.Prn_Command;
        if (DataFromHost.Length)
            Excute_CR();

        if (m!=0)
        {// print a graphic from ROM
            if(UARTGet(PORTHOST,&t,DELAYHOST)==false)
                return;

            DataFromHost.data[1] = t;
            DataFromHost.Length = 2;
            Prn_Status.g_bTextForGraph = false;
        }
        else//stop the text from host
            DataFromHost.Length = 1;
        DataFromHost.Prn_Command = CMDP_PRGRA;
        DataFromHost.data[0] = m;

        RSPrint(DataFromHost.data,DataFromHost.Length,DataFromHost.Prn_Command);
		DataFromHost.Length = 0;
        DataFromHost.Prn_Command = j;
    }
    return;
}
#endif
//GS+0xFF: send falsh to host

// ��ȡ��ӡ�����¶� //
WORD PrnTemperature()
{
    //return ADC_GetConversionValue(ADC1);
    return ADC1->DR & 0x0fff;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// ����Ƿ��д�ӡ�������ڽ����� //
BYTE  TestPrintGoingOn()
{
    return !(ApplVar.PoolPushIn == ApplVar.PoolPopOut &&  //�޴�ӡ����
             (Prn_Status.g_bSuspend   //��ӡ�����ڹ���״̬
             || Prn_Status.g_bWaitPaper   //��ӡ�����ȴ���ӡֽ״̬
             || Prn_TaskNow<=TASK00_Stop
             || Prn_TaskNow>=TASK05_FeedHalf)  //�����漰���ֿ�
            );//ccr2016-05-17
}


/**
 * �����տ����GRBͼƬ����ת��Ϊ���տ����ͼƬ����,
 * ��ͼƬ�����б����������(cTextFlag=0x80)
 * �������ͼƬ���ݴ���Self_Graph��
 *
 * @author EutronSoftware (2014-03-25)
 */
void ChangeGRBToMyself(void)
{
#if (DOWN_GR_SIZE)
    char *GRBBuff=(char *)DOWN_GR_ADDR;
    int newLength,textFrom,sGRBSize;
    int i,j,k;
    int sPOS;//�����ݵĴ��λ��
    BYTE TextC;//�ı���¼��
    BYTE TextL;//�ı�����


//    if (GRB_Define.cGraSize>0 && GRB_Define.cTextFlag==0x80 //���û��Զ���ͼƬ����
//        && InfoSelf_Graph.cGrapCols==0) //ͼƬ����δת��
    {
            //GRB_Define.cGraSizeΪGRB���ݳ���
            //��GRB���ݽ���ת��,ת��ΪER260��ͼƬ��ʽ
            if (GRB_Define.cTextFlag==0)//���ı�����
            {
              newLength=5;//ָ���ļ����ƴ��λ��
              GRB_Define.cTextOffset=0;
              GRB_Define.cHighAChar=24;
			  sGRBSize = GRB_Define.cGraSize;
            }
            else
			{
			  sGRBSize = GRB_Define.cTextOffset;
              newLength=10;//ָ���ļ����ƴ��λ��
			}

            for (i=0;GRBBuff[newLength]!=0;newLength++)//��ȡ�ļ���������
            {
//              if (i<sizeof(GRB_Define.cName))
//                  GRB_Define.cName[i++]=GRBBuff[newLength];
//              if (GRBBuff[newLength]==0)
//                break;
            }
            newLength++;//Ϊͼ�����ʼλ��

            InfoSelf_Graph.cGrapCols = GRB_Define.cWidth * 8 / 12;//��ͼƬ����ռ�ַ����,�ַ��ĵ�����Ϊ12
            InfoSelf_Graph.cPrintAt = GRB_Define.cPrintAt;
            InfoSelf_Graph.cWidthAChar = 12;
            InfoSelf_Graph.cHighAChar = 24;
            InfoSelf_Graph.cByteALine = 24; //���ȹ̶�Ϊ24 !!!!!!!

            sPOS=0;TextC=0;
            //�Ƚ����ı�����
            if (GRB_Define.cTextOffset)
            {//���ı�����
                InfoSelf_Graph.cLabels=0;
                textFrom=GRB_Define.cTextOffset;
                j=0;//Ϊÿ���ַ���������
//                for (;textFrom<GRB_Define.cGraSize && InfoSelf_Graph.cLabels<GRB_Define.cLabels;)
                for (;textFrom<GRB_Define.cGraSize;)//&& TextC<GRB_Define.cLabels;)
                {
                    i = sPOS;
                    if (GRBBuff[textFrom]==0)//Ϊ����
                    {
                      memset(Self_Graph+sPOS,' ',InfoSelf_Graph.cByteALine);
                      sPOS+=InfoSelf_Graph.cByteALine;
                      Self_Graph[sPOS++]=0;//��Ч��ӡ����Ϊ0
                      textFrom++;
                      InfoSelf_Graph.cLabels++;//������1;
                    }
                    else if (GRBBuff[textFrom]==1)
                    {
                        textFrom+=2;//�߳����Ǳ�־�ͼ�¼��
                    }
                    else
                    {
                        for (j = 0;textFrom<GRB_Define.cGraSize && GRBBuff[textFrom]!=0;textFrom++)
                        {
                            if (j<InfoSelf_Graph.cByteALine)
                            {
                                Self_Graph[sPOS++]=GRBBuff[textFrom];
                                j++;
                            }
                        }
                        textFrom++;//skip \0
                        TextL = j;
                        for (;j<InfoSelf_Graph.cByteALine;j++)
                            Self_Graph[sPOS++]=' ';

                        Self_Graph[sPOS++]=TextL;
                        InfoSelf_Graph.cLabels++;//������1;
                        TextC++;
                    }
                }
                InfoSelf_Graph.cGrapSize = (InfoSelf_Graph.cLabels) * (InfoSelf_Graph.cByteALine + 1);
            }
            else
            {
                InfoSelf_Graph.cLabels = 0;
                InfoSelf_Graph.cGrapSize = 0;
            }
            //�ַ����ݽ������.��ʼ����ͼ�����
            textFrom=sPOS; //������ER260Grp_Def�еĿ�ʼλ��

            //sGRBSize = (int)GRB_Define.cWidth*GRB_Define.cHeight*24;//�̶�24����� GRB_Define.cHighAChar;//
            for (i=0;i<sGRBSize && sPOS<sizeof(Self_Graph);)
            {
                j = i + newLength;
                if (GRBBuff[j]==0)
                {
                  j++;
                  for (k=0;k<GRBBuff[j] && sPOS<sizeof(Self_Graph);k++)
                     Self_Graph[sPOS++]=0;
                     i+=2;
                }
                else
                {
                    Self_Graph[sPOS++]=GRBBuff[j];
                    i++;
                }
            }
            InfoSelf_Graph.cGrapSize += (sPOS-textFrom);
    }
#endif
}

/******************************************************************
 Function: void Excute_LF(void)
 Describe: print out and then feed 1 line
******************************************************************/
void Excute_feed_hj(void)
{
    BYTE cpMode = DataFromHost.Prn_Command;
	BYTE i;

	//HJ ��������
    for (i=0; i<PRNWIDTH; i++)
    {
//      DataFromHost.data[i] = '0' + i;
//        DataFromHost.data[i] = 'A' ;
        DataFromHost.data[i] = 'M' ;
    }

     DataFromHost.Length = PRNWIDTH;

    if (DataFromHost.Length)
	{
        Excute_CR();
 	}
    else
    {
        DataFromHost.Prn_Command = CMDP_R;
        Excute_CR();

        DataFromHost.Prn_Command = cpMode;
    }
}
#endif
