
#include "king.h"
#include "appl.h"                               /* Kingtron library and I/O routines */
#include "exthead.h"
#include "message.h"
//#include "test.h"
#include "interface.h"
#include "stm32f10x_it.h"
#include "pwr_ctrl.h"
#include "rtc.h"
#include "sdio_sd.h"

#if defined(CASE_ASCIIDISPLAY)
#include "lcd_160x.h"
#include "monitor.h"
#else
extern void LED_Init(void);
extern void HT1621_Init(void);
#endif

#define YEARFrDEC 2000      //RTC���꿪ʼ���
#define YEARFrHEX 0x2000    //RTC���꿪ʼ���

DATE_BCD rtc_date;          //buffer per get/set data corrente
TIME_BCD rtc_time;          //buffer per get/set orario corrente


void KeyBoardProc(void);
void PFOInt_Init(void);

extern void Beep(uint8_t blen);
void msDelay(__IO uint32_t nTime);

volatile BYTE DrawerOpen_time = 0;

#if defined(FOR_DEBUG)
#define FORJLINK	1	//ʹ��JLINK�������غ͵���ʱ,������1
#else
#define FORJLINK	0	//ʹ��JLINK�������غ͵���ʱ,������1
#endif


/****************************************************************************
ע��:
    �տ��������ҵ�����ݵĴ�/ȡ����ͨ��ReadRam��WriteRam������,
ReadRam��WriteRam����洢�ռ�Ĺ���,�����Ŀռ��ַ��Ӧ�ó�����͸����.
��:Ӧ�ó���ֻ��ReadRam��WriteRam�ṩ��Ч�洢�ռ�������ַ����������
   ���ڴ洢�ռ��Ƿ�����,�洢������FLASHоƬ����SRAM������������,
   �� ReadRam��WriteRam�ڲ�����.

   Ӧ�ó���������������ռ䲻��ReadRam��WriteRam����֮��.
****************************************************************************/
#if FLASH_AppRAM
#if defined   (__CC_ARM)      /* ARM Compiler */
BYTE FlashCache[NOR_FLASH_SECTOR_SIZE] __attribute__ ((aligned (4)));//���ڴ�Ŵ�Nor Flash�ж�ȡ������ȡ��һ��Sector�е�����
#elif defined (__ICCARM__)    /* IAR Compiler */
#pragma data_alignment=4
BYTE FlashCache[NOR_FLASH_SECTOR_SIZE];//���ڴ�Ŵ�Nor Flash�ж�ȡ������ȡ��һ��Sector�е�����
#else
BYTE FlashCache[NOR_FLASH_SECTOR_SIZE];//���ڴ�Ŵ�Nor Flash�ж�ȡ������ȡ��һ��Sector�е�����
#endif

ULONG FlashLast=0xffffffff; //Ϊ�����FlashCatch�е����ݵ�Sector�ĵ�ַ;

#endif //FLASH_AppRAM

/**
 * ����RamOffSet��ָ���ĵ�ַ,���ļ����ݴ洢���ж�ȡlen�ֽڵ�����
 * ��ȡ���֮��,RamOffSet�Զ�+len
 * @author EutronSoftware (2014-08-26)
 *
 * @param buf :��ȡ�����ݴ����
 * @param len :��ȡ�����ֽ���,����<=NOR_FLASH_SECTOR_SIZE
 */

void ReadRam( BYTE *buf,WORD len)
{

#if FLASH_AppRAM
    WORD temp_len;
    DWORD temp_addr;

    if (RamOffSet<NOR_FLASH_SIZE)
    {
			if ((RamOffSet + len)<=NOR_FLASH_SIZE)
					NOR2_ReadBuffer(buf, RamOffSet, len);
    }

#else
    //if ((RamOffSet + len)<=ApplVar.SIZE_EXTRAM)
        SRAM_ReadBuffer(buf,RamOffSet, len);
#endif
        RamOffSet += len;
}
/**
 * ����RamOffSet��ָ���ĵ�ַ,���ļ����ݴ洢����д��len�ֽڵ�����
 *  ��Ҫд������ݿ��е����ݶ��뵽CACHE�к�,����FLASH�����ڵĿ�
 *  д�����֮��,RamOffSet�Զ�+len
 * @author EutronSoftware (2014-08-26)
 *
 * @param buf :Ҫд�������
 * @param len :�����ֽ���,����<=NOR_FLASH_SECTOR_SIZE
 */
void WriteRam( BYTE *buf, WORD len)   /* (void *from, WORD bytes) write bytes to ram banks */
{
#if FLASH_AppRAM

    WORD temp_len;
    DWORD temp_addr;

    if (RamOffSet<NOR_FLASH_SIZE)
    {
        if ((RamOffSet + len)<=NOR_FLASH_SIZE)
            NOR2_WriteBuffer(buf, RamOffSet, len);
    }

    RamOffSet += len;

#else
//    if ((RamOffSet + len)<=ApplVar.SIZE_EXTRAME)
        SRAM_WriteBuffer(buf, RamOffSet, len);
      RamOffSet += len;
#endif
}
/****************************************************************************/



void DrawerOpen(void)//��Ǯ��
{
    DRAWER_OPEN();
    DrawerOpen_time = 5;
}


//Bios���ṩ�Ĺ����о�����
//�п���ȫ���о�Ӧ�ó�����ʹ�õ��Ĺ���.���Ӧ�ó���ʹ�����ڴ�δ�г��Ĺ���,
//��ô��Ӧ��Biosģ�齫���ӡCommand XX��ʾ,��ʱӦ��ΪXX�������Ӧ�ĳ���.
WORD Bios(WORD cmd, void  *ptr, WORD par1, WORD par2)
{
    BYTE i, BCount;
    DWORD sect;
    BYTE aBuf[3];
    switch (cmd)
    {
    case BiosCmd_CC_Compare://
        //(BOOL)Result = Bios(BiosCmd_CC_Compare, (char*)SourceBuff, (WORD)ChipAdrress, (WORD)NumBytes )
        //�Ƚ�SourceBuff�е������Ƿ���IC����ַChipAdrress�г���ΪNumBytes�������Ƿ�һ��,
        break;
    case BiosCmd_CC_Read:
        //(BOOL)Result = Bios(BiosCmd_CC_Read, (char*)DestBuff, (WORD)ChipAdrress, (WORD)NumBytes )
        //��IC����ַChipAdrress�ж�ȡ����ΪNumBytes�����ݴ���DestBuff
        return 0;
    case BiosCmd_CC_Write:
        //(BOOL)Result = Bios(BiosCmd_CC_Write, (far char*)SourceBuff, (WORD)ChipAdrress, (WORD)NumBytes )
        //��SourceBuff�е�����д��IC����ַChipAdrress��
        return 0;
#if (defined(DD_MMC) || defined(CASE_EJSD))
    case BiosCmd_SD_Erase:
        //Bios(BiosCmd_SD_Erase, (far char*)SourceBuff, (WORD)GROUP_L, (WORD)GROUP_H )
        //����MMC������GROUP_H*65536+GROUP_L��ָ�����������, MMC����Ļ�����Ҫ�μ�����ֲ�
        if(SD_Detect()!= SD_PRESENT)
            return (SD_Erase(((uint32_t)par1<<16)+par2,((uint32_t)par1<<16)+par2+SDBLOCKSIZE)==SD_OK);
        else
            return false;
    case BiosCmd_SD_ReadInfo:
        //Bios(BiosCmd_SD_ReadInfo, (char*)sBuf, MMC_SEND_CID,16)
        //Bios(BiosCmd_SD_ReadInfo, (char*)sBuf, MMC_SEND_CSD,16)
        //��ȡMMC����CID��CSD,����sBuf��
        if((SD_Detect()!= SD_PRESENT) || SD_GetCardInfo(&SDCardInfo) != SD_OK)
             return false;
        if (ptr)
        {
            if(par1 == MMC_SEND_CID)
            {
                memcpy(ptr,(char*)&SDCardInfo.SD_cid,16);
            }
            else if(par1 == MMC_SEND_CSD)
            {
                memcpy(ptr,(char*)&SDCardInfo.SD_csd,16);
            }
        }

        return true;

    case BiosCmd_SD_UnProtect:
        //Bios(BiosCmd_SD_UnProtect, (far char*)SourceBuff, (WORD)GROUP_L, (WORD)GROUP_H )
        //ȡ����MMC������GROUP_H*65536+GROUP_L��ָ������, MMC����Ļ�����Ҫ�μ�����ֲ�
        break;
    case BiosCmd_SD_Init:
        //Bios(BiosCmd_SD_Init, (far char*)SourceBuff, 0, 0 )
        //��ʼ��MMC��, MMC�ĳ�ʼ��������ֲ�

        NVIC_SDConfiguration();

        if (SD_Detect()== SD_PRESENT)
        {
            //SD_PWR_ON();
            return (SD_Init () == SD_OK);
        }
        else
            return false;
    case BiosCmd_SD_ReadBlock:
        //Bios(BiosCmd_SD_ReadBlock, buf,addr_L,  addr_H)
        //��MMC���е�addr_h*65536+addr_L��ַ�ж�ȡһ������,����buf��,ͨ��һ��Ϊ512�ֽ�
//        return  SRAM23K256_RD(((par2 << 16) | par1)+0x4000, 512,(BYTE *)ptr);//testonly
        sect = ((par2 << 16) | par1);
        return SD_ReadMultiBlocks((BYTE *)ptr,sect,  SDBLOCKSIZE,2)==SD_OK;
    case BiosCmd_SD_WriteBlock:
        //Bios(BiosCmd_SD_WriteBlock, buf,addr_L,  addr_H)
        //��buf�е�һ������д���MMC���е�addr_h*65536+addr_L��ַ��,ͨ��һ��Ϊ512�ֽ�
//        return SRAM23K256_WR(((par2 << 16) | par1)+0x4000, (BYTE *)ptr, 512);//testonly
        sect = ((par2 << 16) | par1);
        return (SD_WriteMultiBlocks((BYTE *)ptr, sect,  SDBLOCKSIZE,2)==SD_OK);
    case BiosCmd_SD_CheckPresence:
        //Bios(BiosCmd_SD_CheckPresence, 0, 0, 0)
        //���MMC���Ƿ����
        return (SD_Detect()==SD_PRESENT);

#endif
    case BiosCmd_PrintGraph:
        //Bios(BiosCmd_PrintGraph, (char*)idx, option, position);
        //��ӡ��idx��ָ����ͼƬ
        //option:   bit0  =1,��GrafTexts�е����ֵ��ӵ�ͼƬ��
        //          bit1  =1,ʹ��ͼƬ�Դ������ֵ��ӵ�ͼƬ��
        //position:ָ��ͼƬ��ӡ���ַ�λ��

#if !defined(CASE_INNERDOTPRN)
        if (!TESTBIT(ApplVar.MyFlags, ENPRINTER))
        {
            aBuf[0] = (BYTE)ptr;//get the graphic index
            BCount = 2;
            if (par1 & 0x01)
            {
                if (ApplVar.GrafTexts[0][0] == 0)
                    aBuf[1] = '0';//û����Ҫ���ӵ�����
                else
                {
                    if (par2 && par2<=PRTLEN)
                    {//ָ����ӡλ��
                        aBuf[2] = par2;
                        BCount=3;
                    }
                    aBuf[1] = '1';//�����ֵ�����ͼƬ��
                    RSPrint(aBuf, BCount, CMDP_PRGRA);
                    for (i=0; i<TEXTSOFGRAPH && ApplVar.GrafTexts[i][0]; i++)
                        RSPrint(ApplVar.GrafTexts[i], PRTLEN-1, CMDP_R);
                    aBuf[0] = 0;
                    RSPrint(aBuf, 1, CMDP_R);
                    return true;
                }

            }
            else if (par1 & 0x02)
            {//ʹ��ͼƬ�Դ������ֵ��ӵ�ͼƬ��
                aBuf[1] = '2';
            }
            if (par2 && par2<=PRTLEN)
            {//ָ����ӡλ��
                aBuf[2] = par2;
                BCount=3;
            }
            RSPrint(aBuf, BCount, CMDP_PRGRA);
        }
#endif
        return true;
    case BiosCmd_PrintRestart:
        //����������ӡ,M3ϵͳ��û��ʹ��
        break;
    case BiosCmd_PrintX:
#if !defined(CASE_INNERDOTPRN)
        //Bios(BiosCmd_PrintX, char *Line, WORD Cmd , WORD DotLinesBlank);
        //���ӡ�����ʹ�ӡ����,LineΪҪ��ӡ������;CmdΪ��ӡ����;DotLinesBlankΪ��ӡ��ɺ����ֽ����
        //Cmd�������¿����ĳ�������������
        if (ptr)
        {
            BCount = strlen(ptr);
            if (BCount > PRTLEN)
                BCount = PRTLEN;
        }
        else
            BCount = 0;

        if (!TESTBIT(ApplVar.MyFlags, ENPRINTER))
            RSPrint((BYTE *)ptr, BCount, par1);//����Ҫ��ӡ��������Ҫ����
#endif
        return true;

    case BiosCmd_PrintDirect://Ŀǰ�Ĵ�ӡ���������޴˹���
        //Bios(BiosCmd_PrintDirect, char *Line, WORD Cmd , WORD DotLinesBlank);
        //���ӡ�����ʹ�ӡ����,LineΪҪ��ӡ������;CmdΪ��ӡ����;DotLinesBlankΪ��ӡ��ɺ����ֽ����
        //Cmd�������¿����ĳ�������������
        //ʹ��BiosCmd_PrintDirect����ӡʱ,��ӡ���ݲ������ӡ�����,����ֱ�Ӵ�ӡ
        break;
    default://����������������,����������δ����������ʱ,��ʾ�������,Ȼ���ٿ�����Ӧ����
        USART_printf("Command %d\n",cmd);
        break;
    }
    return 0;
}


WORD  Bios_1(WORD cmd)
{
    RTCTime sTime;

    switch (cmd)
    {
    case BiosCmd_PrintCheck:
        //Bios_1(BiosCmd_PrintCheck);
        //��ȡ��ӡ����״̬:ȱֽ/ѹ��̧��/���ȵ�
#if !defined(CASE_INNERDOTPRN)
				Get_Printer_status();
        return CWORD(Printer_Status);
#else
			  return 0;
#endif

    case BiosCmd_ResetCutter:
        //Bios_1(BiosCmd_ResetCutter)
        //��λ��ӡ���е�
#if !defined(CASE_INNERDOTPRN)
        if (!TESTBIT(ApplVar.MyFlags, ENPRINTER))
            RSPrint(0, 0, PRN_CUTRESET_Mode);
#endif
        break;
    case BiosCmd_RestDisp0:
        //Bios_1(BiosCmd_RestDisp0);
        //������ʾ��ʾ��Ļ������,ͨ�����ڹػ����ٿ���ʱ��ʾ�ػ�ǰ�������Ļ����
#if !defined(CASE_ASCIIDISPLAY)
        LED_On();
        PutsO_Saved();
#endif
        break;
    case BiosCmd_SaveDisp0:
        //������Ļ�ϵ���ʾ����.
        //��:���տ����ʾ����������Ϣ,ͻȻ��������ʱ,�Ƚ���ǰ���ݱ���,Ȼ������ʾ������Ϣ
        break;
    case BiosCmd_ClrFip0:
#if !defined(CASE_ASCIIDISPLAY)
        //���LED��ʾ
        LED_Off();
#endif
        return 0;

    case BiosCmd_AutoClickOff:
        //�رհ����Զ���������
        EnableBeep(false);
        break;
    case BiosCmd_AutoClickOn:
        //�򿪰����Զ���������
        EnableBeep(true);
        break;
    case BiosCmd_CC_Close:
        //�ر�IC��,���ر�IC����������Դ
        return 0;
    case BiosCmd_BuzzL:
        Beep(3);
        break;
    case BiosCmd_BuzzM:
        Beep(2);
        break;
    case BiosCmd_BuzzS:
        //�ֱ�Ϊ��/��/��ʱ�����
        Beep(1);
        break;
    case BiosCmd_GetDate://ccr2014-10-14>>>>>>>>>>>
        //��ȡ���ڵ�rtc_date��,���ڸ�ʽΪ
        rtc_gettime (&sTime);
		if (sTime.year<2000)
			sTime.year=0;
		else
			sTime.year -= YEARFrDEC;
        rtc_date.dd = DECtoBCD(sTime.mday);
        rtc_date.mm = DECtoBCD(sTime.mon);
        rtc_date.yy = DECtoBCD(sTime.year);
        rtc_date.w =sTime.wday;
        return 1;

    case BiosCmd_GetTime:
        //��ȡʱ�䵽rtc_time��,ʱ���ʽΪ:
        rtc_gettime (&sTime);
        rtc_time.hh = DECtoBCD(sTime.hour);
        rtc_time.mm = DECtoBCD(sTime.min);
        rtc_time.ss = DECtoBCD(sTime.sec);
        return 0;

    case BiosCmd_SetDate:
        //����rtc_date�е�������������
        rtc_gettime (&sTime);
        sTime.year        = BCDtoDEC(rtc_date.yy)+YEARFrDEC;
        sTime.mon       = BCDtoDEC(rtc_date.mm) ;
        sTime.mday        = BCDtoDEC(rtc_date.dd);
        //sTime.wday     = BCDtoDEC(rtc_date.w);
        rtc_settime(&sTime);
        return 0;
    case BiosCmd_SetTime:
        //����rtc_time�е�ʱ������ʱ��
        rtc_gettime (&sTime);
        sTime.hour       = BCDtoDEC(rtc_time.hh);
        sTime.min     = BCDtoDEC(rtc_time.mm) ;
        sTime.sec     = BCDtoDEC(rtc_time.ss) ;
        rtc_settime(&sTime);//ccr2014-10-14<<<<<<<<<<<<<<
        return 0;
    case BiosCmd_CheckKeyborad:

        //�ж��Ƿ��а�������,���ǲ���ȡ��ֵ��1���м����£�0�� �޼�����
        return CheckKeyboard();

    default://����������������,����������δ����������ʱ,��ʾ�������,Ȼ���ٿ�����Ӧ����
        USART_printf("Command_1 %d\n",cmd);
        break;
    }
    return 0;
}

WORD Bios_2(WORD cmd, void  *ptr)
{

    switch (cmd)
    {
    case BiosCmd_CC_Open:
        //��IC��,����ͨIC���ĵ�Դ,ͬʱ��ȡIC����4�ֽ�����,���سɹ����
        break;
    case BiosCmd_CC_VerifyPsw:
        //У��IC������.���سɹ����
        break;
    case BiosCmd_CC_WritePsw:
        //�޸�IC������,���سɹ����
        break;
    default://����������������,����������δ����������ʱ,��ʾ�������,Ȼ���ٿ�����Ӧ����
        USART_printf("Command_2 %d\n",cmd);
        break;
    }
    return 0;
}

WORD Bios_SetKeyboard(BYTE Code, WORD NumKeys, CONSTBYTE *TabPnt, BYTE TabRecLen)
{//���¶������
    return 0;
}

WORD Bios_SetCutter(BYTE Stato)
{//���е�,Stato=0:�ر��е�;Stato=1:���е�
    return 0;
}



void SetRTS(BYTE port)
{//���ô���port��RTS
 //0-����1,1-����2.....
    if (port == 0)
        UART0_RTS_SET();
    else if (port == 1)
        UART1_RTS_SET();
#if USART_EXTEND_EN
	else if (port == 2)
        UART2_RTS_SET();
#endif
}

//set RTS to 'L' for Serial 1,2
void ClrRTS(BYTE port)
{//������ڵ�RTS
 //1-����1,2-����2.....
    if (port == 1)
        UART0_RTS_CLR();
    else if (port == 2)
        UART1_RTS_CLR();
#if USART_EXTEND_EN
	else if (port == 3)
        UART2_RTS_CLR();
#endif
}

// ��ȡ����CTS״̬,status=0��ʾ���账������״̬
// port:1-����1,2-����2.....
BYTE GetCTS(BYTE port)
{
    int i;
    BYTE status[2];

    status[0]=status[1]=0;

    do
    {
        for (i=0;i<2;i++)
        {
            if (i)
                for (status[1]=0;status[1]<10;status[1]++);
            if (port == 1)
                status[i] = UART0_CTS_GET();
            else if (port == 2)
                status[i] = UART1_CTS_GET();
#if USART_EXTEND_EN
            else if (port == 3)
                status[i] = UART2_CTS_GET();
#endif
        }

    } while (status[0]!=status[1]);
    return(status[0]);
}



WORD Bios_SetTic(WORD Interval)
{//��
    return 0;
}

WORD Bios_SetPortBusy(BYTE NumCom, BYTE Satato, BYTE ChrRx, BYTE ChrTx)
{//��
    return 0;
}

WORD Bios_TestMAC(void)
{//����MAC������״̬

    int sMACCount=0;
    ULONG t1,t2;

    do
    {
        t1 = (MAC_PORT->IDR & MAC_PIN);
        usDelay(1000);//���1ms���һ��
        t2 = (MAC_PORT->IDR & MAC_PIN);
        if (t1==t2)
		{
            sMACCount++;
			if (t1 && sMACCount>2)
				break;//������Ϊδ�̽�MAC,ֻ�������,�ӿ쿪���ٶ�
		}
        else
            sMACCount = 0;

    } while (sMACCount<50);//�����50��

    if (!t1)
        return true;  // MAC on
    else
        return false;  // MAC OFF
}


WORD Bios_FM_BlankCheck(UnLong SrcAdr, WORD Num)
{//���˰�ش洢����ַSrcAdr�е�Num�ֽ��Ƿ�Ϊ��
#if 0
    BYTE temp_checkBuf[Num];
    BYTE i;
    M25P80_RD(SrcAdr, Num, temp_checkBuf);
    for (i=0; i<Num; i++)
    {
        if (temp_checkBuf[i] != 0xFF)
            return 0;
    }
#endif
    return 1;
}
//////

BYTE Bios_FM_CheckPresence(void)
{//���˰�ش洢���Ƿ����
    return FMDetect();
}


#define FIRMWARE_ADDR  ((uint32_t)0x08000000L)    //����ռ��ַ
#define FIRMWARE_SIZE  ((uint32_t)0x80000L)      //����ռ��С,ʵ�ʴ�СΪ0x80000,�����С������0x60000

WORD CheckSum(void)
{//���������У���

    WORD checksum=0;
    uint32_t TempAddr;

    for (TempAddr = 0; TempAddr<FIRMWARE_SIZE; TempAddr+=2) /* while there is data to write */
    {
        /* Transfer data to the memory */
        checksum += *(WORD *) (FIRMWARE_ADDR + TempAddr);
    }

    return checksum;
}

long TestRam(void)
{//���RAM
    return 0x20000l;//sizeof the RAM in MCU
}
//���ֽڲ�����ʽ������չRAM�Ķ�д��ȷ��
long TestLMM(WORD lmmPage)
{

    BYTE temp_save,temp_check;
    long i,SizeOfSRAM;
    BYTE *pSRAM;

    SizeOfSRAM=ApplVar.SIZE_EXTRAM;
    if (SizeOfSRAM)
    {//װ����SRAM,ÿ���ڴ�256K
        pSRAM = (BYTE *)SRAM_ADDR;
        for (i=0;i<SizeOfSRAM;i++)
        {
            temp_check = 0x55;
            temp_save = *pSRAM;
            *pSRAM = temp_check;
            temp_check = 0xaa;
            temp_check = *pSRAM;

            if (temp_check != 0x55)
            {
                *pSRAM = temp_save;
                return(-i);
            }
            temp_check = 0xAA;
            *pSRAM = temp_check;
            temp_check = 0x55;
            temp_check = *pSRAM;
            if (temp_check != 0xAA)
            {
                *pSRAM = temp_save;
                return(-i);
            }
            *pSRAM++ = temp_save;
        }
        return SizeOfSRAM;
    }
   return 0;

/*
#define TESTSIZE    sizeof(EntryBuffer)
#define TESTALIGN   1
           //������չSRAM���Ķ�д����ReadRam/WriteRam
                for (RamOffSet=0;RamOffSet<ApplVar.SIZE_EXTRAM;)
                {
                    sAddr = TESTSIZE;
                    if (ApplVar.SIZE_EXTRAM-RamOffSet<TESTSIZE)
                        sAddr=ApplVar.SIZE_EXTRAM-RamOffSet;
                    ReadRam(SysBuf,sAddr);RamOffSet-=sAddr;
                    memset(EntryBuffer+TESTALIGN,0xaa,sAddr);
                    WriteRam(EntryBuffer+TESTALIGN,sAddr);RamOffSet-=sAddr;
                    memset(EntryBuffer+TESTALIGN,0,sAddr);
                    ReadRam(EntryBuffer+TESTALIGN,sAddr);RamOffSet-=sAddr;
                    WriteRam(SysBuf,sAddr);RamOffSet-=sAddr;
                    for (i=0;i<sAddr;i++)
                    {
                        if (EntryBuffer[i+TESTALIGN]!=0xaa)
                            break;
                    }
                    if (i<sAddr) break;
                    memset(EntryBuffer+TESTALIGN,0x55,sAddr);
                    WriteRam(EntryBuffer+TESTALIGN,sAddr);RamOffSet-=sAddr;
                    memset(EntryBuffer+TESTALIGN,0,sAddr);
                    ReadRam(EntryBuffer+TESTALIGN,sAddr);RamOffSet-=sAddr;
                    WriteRam(SysBuf,sAddr);RamOffSet-=sAddr;
                    for (i=0;i<sAddr;i++)
                    {
                        if (EntryBuffer[i+TESTALIGN]!=0x55)
                            break;
                    }
                    if (i<sAddr) break;
                    RamOffSet+=sAddr;
                }

                memset(SysBuf,' ',PRTLEN+1);
                strcpy(SysBuf,"SRAM SIZE:");
                keyno = strlen(SysBuf);
                if (i<sAddr)
                {
                    RamOffSet+=i;
                    strcpy(SysBuf+keyno-5,"ERROR AT:");
                    keyno = strlen(SysBuf);
                }

                HEXtoASC(SysBuf+keyno, (char *)&RamOffSet, 3);

                SysBuf[keyno+6] = 'H';
                SysBuf[keyno+7] = 0;
                RJPrint(0, SysBuf);

                ClearEntry(false);
                ClsState1();
                ClsState2();
                return true;
*/

}
//���Ӧ�����ݴ洢��,ͬʱ��EXTRAMN�б�ʾSRAM����(256K/��),
//��ApplVar.SIZE_EXTRAM�м�¼SRAM��С
void ClsXRam(void)
{
#if FLASH_AppRAM
    FlashOpt = 0;
    SSTF080B_EraseChip();
    FlashOpt = 1;
//testonly	SSTF080B_EraseChip();
    FlashErase = 0;
    ApplVar.SIZE_EXTRAM=0x100000L;    //size of flash
    EXTRAMN |= (ApplVar.SIZE_EXTRAM>>18);   //��ʾ��һ��SRAM
#else

//    WORD *pSRAM=(WORD*)SRAM_ADDR;

    EXTRAMN &= 0xf0;
    //����һ��SRAM�Ƿ����

//    *pSRAM = 0x55AA;

//    if (*pSRAM == 0x55AA)//����Ƿ�����չSRAM
    {
#if defined(DEBUGBYPC)
        ApplVar.SIZE_EXTRAM=0x40000L;
#else
        ApplVar.SIZE_EXTRAM=SRAMSIZE;//testonly SRAM_Detect();
#endif
        if (ApplVar.SIZE_EXTRAM)
        {
            EXTRAMN |= (ApplVar.SIZE_EXTRAM>>18);   //��ʾSRAM����(256K/ÿ��)

            //�����չRAM�е�����
#if ApplVarInSRAM
            memset((void*)(SRAM_ADDR+sizeof(WORD)+sizeof(ULONG)+sizeof(struct APPTEXT)+sizeof(struct APPLICATION)),0,
                   ApplVar.SIZE_EXTRAM-(sizeof(WORD)+sizeof(ULONG)+sizeof(struct APPTEXT)+sizeof(struct APPLICATION)));
#else
            memset((void*)SRAM_ADDR,0,ApplVar.SIZE_EXTRAM);
#endif
        }
        else
        {//����չ�ڴ�,ϵͳ�޷�����
            while (KbHit()) Getch();//����Ѱ���
            while (!KbHit())
            {
                Beep(3);
#if defined(CASE_ASCIIDISPLAY)
                PutsO(SRAMNOTFOUND);
#else
                mClearScreen();
                Delay(500);
                DispStrXY(SRAMNOTFOUND,0,0);
                Delay(500);
#endif
            }
        }
    }

#endif
}



short Bell(short len)
{//����len�ֱ����峤/��/��ʱ��
    Beep(len);
    return 0;
}


WORD CC_Insert(void)
{//���IC���Ƿ����
//  return 1;//����
    return 0;//û�в忨
}


//------------------------------------------------------------------



void CutRPaper(short lines)
{//��ӡ����ֽ
#if DD_CUTTER
    if (CUTTER & 0x03)
    {
        RFeed(lines);
#if !defined(CASE_INNERDOTPRN)
        if (!TESTBIT(ApplVar.MyFlags, ENPRINTER))
            RSPrint(0, 0, PRN_CUTH_Mode);
#endif
    }
#endif
}


///////////////////////////////////////////////////////////////////////////////////////////////

#define TIMER_INTERVAL 	500

__IO uint32_t AsynchPrediv = 0, SynchPrediv = 0;


#if !defined(DEBUGBYPC)

    #if uCOSII==0
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 1 ms.
  * @retval None
  */
extern volatile uint16_t msTimer_Delay3;
void msDelay(__IO uint32_t nTime)
{
	msTimer_Delay3 = nTime;
	while (msTimer_Delay3) ;

#if 0	//ouhs20160726
    if (nTime)
    {
        TIM5->SR = (uint16_t)~TIM_FLAG_Update;
        //ouhs 20140905 TIM5->ARR = uSECOND * nTime * 1000;
				TIM5->ARR = (6 * nTime * 1000) - 1;
        TIM_Cmd(TIM5, ENABLE);
        while (!(TIM5->SR & TIM_FLAG_Update))
        {
        };
        TIM_Cmd(TIM5, DISABLE);
    }
#endif
}
    #endif

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 1 us.
  * @retval None
  */
void usDelay(__IO uint32_t nTime)
{
    if (nTime)
    {
        TIM5->SR = (uint16_t)~TIM_FLAG_Update;
        //ouhs 20140905 TIM5->ARR = uSECOND * nTime ;
				TIM5->ARR = (6 * nTime) - 1 ;
        TIM_Cmd(TIM5, ENABLE);
        while (!(TIM5->SR & TIM_FLAG_Update))
        {
        };
        TIM_Cmd(TIM5, DISABLE);

    }
}


//extern void USB_Init(void);
//extern void USB_TEST(void);
extern void USB_Start(void);

void STM32_Initial(void)
{
    RCC_ClocksTypeDef RCC_Clocks;

    /******** �����ļ����ѵ���SystemInit()������ƵΪ72MHz*********/
	//HCLK:72MHz, PCLK1:36MHz,  PCLK2:72MHz
	/*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
	*/

    // �δ�ʱ��SysTickÿ1ms�ж�һ�Σ�72000000/1000*(1/72)us=1ms
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);//1ms for SysTick


    UARTInit(1,115200,8,0,1); 	//��Ӧ�ⲿ����RS232-I
    UARTInit(2,115200,8,0,1);	//��Ӧ�ⲿ����RS232-II
#if USART_EXTEND_EN
#if defined(CASE_INNERDOTPRN)
    UARTInit(DOTPRNPORT+1,19200,8,0,1);	//��Ӧ�ڲ�����(�������)
#else
	UARTInit(3,115200,8,0,1);	//��Ӧ�ڲ�����(MFRICard)
#endif
#endif

	HW_GPIOInit();

    pwr_Init();

    FSMC_Init();
    //BackupReg_Init(); //BKPSRAM_Init();//��ʼ���ڲ�RAM ccr2014-03-25

#if !defined(CASE_ASCIIDISPLAY)
    mInitialLCD();
#endif

	rtc_init();

    TIM5_Init();
    KeyBoardInit();
#if defined(FISCAL)
    FM_Init();
#endif

#if defined(CASE_ASCIIDISPLAY)
    LCDInit();
#else
	TIM6_Init();
#if defined(LCD10_DISP)
    HT1621_Init();
#else
	LED_Init(); 	// ע�⣺ ER-220����LED���Խӿ���JTAG(SW)���Խӿڸ���,ʹ��LED����ʱ������ͨJTAG(SW)���س�������
#endif
#endif

	SD_LowLevel_Init();
	/**   NVIC PreemptionPriority���ȼ����䣺SD=0, ��ӡ����ʱ��TIM2��TIM3=1,
	                                        ����=2, ���̶�ʱ���ж�TIM7=3, ���̰����ж�=3,
											�����ж�=0, LED���Զ�ʱ��TIM6=3,
	**/
    NVIC_SDConfiguration();// For SD

	SD_Init();

	Beep(1);

#if defined(STM32F10X_HD_USBCOMM)
    USB_Start();
#endif


#if defined(CASE_GPRS)
	GPRS_PWR_HIGH();//GPRS_OnOff();
#endif

}

void Beep(uint8_t blen)
{
    BEEP_ON();
    if (blen == 1)
        beep_len = 10;
    else if (blen == 2)
        beep_len = 40;
    else if (blen == 3)
        beep_len = 80;
    else
        beep_len = 10;
}

//***************************************************//
void HW_GPIOInit(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	// ����GPIO����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
												 RCC_APB2Periph_GPIOC |	RCC_APB2Periph_GPIOD |
												 RCC_APB2Periph_GPIOF |	RCC_APB2Periph_GPIOF |	RCC_APB2Periph_GPIOG , ENABLE);

#if (defined(CASE_ER220) || defined(CASE_ER260)) && (FORJLINK == 0)
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//SWJ ��JTAG���ر�
#else
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);// ����SWJ,�ر�JTAG
#endif


	// ����GPIO������������������ٶ�100MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //GPIO_Speed_2MHz;

	// ������
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// UART0_RTS,UART1_RTS,UART2_RTS
	GPIO_InitStructure.GPIO_Pin = UART0_RTS;
	GPIO_Init(UART0_RTS_PORT, &GPIO_InitStructure);

#if (FORJLINK == 0)
	GPIO_InitStructure.GPIO_Pin = UART1_RTS;
	GPIO_Init(UART1_RTS_PORT, &GPIO_InitStructure);
#endif

#ifndef CASE_GPRS
	GPIO_InitStructure.GPIO_Pin = UART2_RTS;
	GPIO_Init(UART2_RTS_PORT, &GPIO_InitStructure);
#else
	GPIO_InitStructure.GPIO_Pin = GPRS_PWR | GPRS_RST;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif

	// Ǯ��
	GPIO_InitStructure.GPIO_Pin = DRAWER_PIN;
	GPIO_Init(DRAWER_PORT, &GPIO_InitStructure);
	DRAWER_OFF();

	// UART0_CTS, UART1_CTS, UART2_CTS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = UART0_CTS;
	GPIO_Init(UART0_CTS_PORT, &GPIO_InitStructure);

#if (FORJLINK == 0)
	GPIO_InitStructure.GPIO_Pin = UART1_CTS;
	GPIO_Init(UART1_CTS_PORT, &GPIO_InitStructure);
#endif

#ifndef CASE_GPRS
	GPIO_InitStructure.GPIO_Pin = UART2_CTS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //Ĭ������Ϊ����,������Ƶˢ����ʱ���п�����ʱ���⵽�ߵ�ƽ
	GPIO_Init(UART2_CTS_PORT, &GPIO_InitStructure);
#endif

	// MAC (Init)
	GPIO_InitStructure.GPIO_Pin = MAC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(MAC_PORT, &GPIO_InitStructure);
	BEEP_OFF();

}

#endif


#ifdef CASE_GPRS
//GPRSģ�鿪�ػ�����
//Ӧ���ӷ���AT���GPRSģ���״̬�����ƿ��ػ�����
//���Ƶ�ƽ60ms,���ڹػ�״̬������Կ��������ǿ���״̬����ģ���ػ�.
void GPRS_OnOff(void)
{
		GPRS_PWR_HIGH();
		msDelay(100);
		GPRS_PWR_LOW();
		GPRS_RST_LOW();
		//msDelay(3000);	//ģ�鿪��3��󷽿���������
}
#endif



/*********************************************************************************************************
** Function name:      TIM7_Init
** Descriptions:      ��ʱ��7��ʼ������,10ms�жϣ����ڷ�������Ǯ�䡢����
*********************************************************************************************************/
void TIM7_Init(void)
{
    uint16_t PrescalerValue = 0;

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

    /* Compute the prescaler value */
	/* -----------------------------------------------------------------------
    The TIMxCLK frequency is set to SystemCoreClock (Hz), to get TIMx counter
    clock at 24 MHz the Prescaler is computed as following:
     - Prescaler = (TIMxCLK / TIMx counter clock) - 1
    SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
    and Connectivity line devices and to 24 MHz for Low-Density Value line and
    Medium-Density Value line devices

    The TIMx is running at 36 KHz: TIMx Frequency = TIMx counter clock/(ARR + 1)
	--------------------------------------------------------------------------*/

	PrescalerValue = (uint16_t) ((SystemCoreClock) / 1000000) - 1;

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 9999;    //10ms�ж�һ��
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;//0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

    /* Prescaler configuration */
    //TIM_PrescalerConfig(TIM7, PrescalerValue, TIM_PSCReloadMode_Immediate);

    /* Enable the TIM gloabal Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //ouhs 20140814 =3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* TIM Interrupts enable */
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);

    /* Enable counter */
    TIM_Cmd(TIM7, ENABLE);
}


/*********************************************************************************************************
** Function name:      TIM5_Init,������ʱ�ȴ�
** Descriptions:      ��ʱ��5��ʼ������,
*********************************************************************************************************/
void TIM5_Init(void)
{
	uint16_t PrescalerValue = 0;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    /* Enable TIM5 clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	PrescalerValue = (uint16_t) ((SystemCoreClock) / 6000000) - 1;	//6MHz

    /* TIM5 configuration */
    //TIM_TimeBaseStructure.TIM_Period = uSECOND * 5000*1000; //1ms
	TIM_TimeBaseStructure.TIM_Period = 5; //1us
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
    TIM_ARRPreloadConfig(TIM5,DISABLE);// ��ʹ��Ӱ�ӼĴ��� //
    TIM_OCStructInit(&TIM_OCInitStructure);

    /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStructure.TIM_Pulse = 0x0;
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);

    /* One Pulse Mode selection */
    TIM_SelectOnePulseMode(TIM4, TIM_OPMode_Single);
    /* Clear TIM5 update pending flags */
    TIM_ClearFlag(TIM5, TIM_FLAG_Update);

    /* TIM5 enable counters */
//  TIM_Cmd(TIM5, ENABLE);

}

/*********************************************************************************************************
** Function name:      TIM6_Init
** Descriptions:      ��ʱ��6��ʼ������1ms�жϣ�����LED���ԣ�LCD���
*********************************************************************************************************/
void TIM6_Init(void)
{
    uint16_t PrescalerValue = 0;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	/* Compute the prescaler value */
    PrescalerValue = (uint16_t) ((SystemCoreClock) / 1000000) - 1; //1MHz

	/* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 499; //500us�ж�һ��
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	/* Prescaler configuration */
    TIM_PrescalerConfig(TIM6, PrescalerValue, TIM_PSCReloadMode_Immediate);

	/* Enable the TIM gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //ouhs 20140814 =2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM Interrupts enable */
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

	/* Enable counter */
	TIM_Cmd(TIM6, ENABLE);
}

#if (defined(DD_MMC) || defined(CASE_EJSD))
/*****************************************************************
  ��SD���Ŀ��СΪ1024ʱ��ÿ�ζ�дSD��������1024�ֽ�
  ���ǣ�������512�ֽ�Ϊ��ı߽�
*****************************************************************/
//��SD���϶�ȡһ������ ����ĵĴ�СΪSDCardInfo.CardBlockSize
BYTE MMC_ReadBlock(char *buf,DWORD addr)
{
	return (SD_ReadBlock(buf,addr, SDBLOCKSIZE)==SD_OK);
}
//��SD����д��һ�����ݣ���ĵĴ�СΪSDCardInfo.CardBlockSize
BYTE MMC_WriteBlock(char *buf,DWORD addr)
{
	return (SD_WriteBlock((BYTE *)buf, addr, SDBLOCKSIZE)==SD_OK);
}

//ccr2014-08-13>>>>>>>>>>>>>>>>
/*****************************************************************
  ��SD���Ŀ��СΪ1024ʱ��ÿ�ζ�дSD��������1024�ֽ�
  ���ǣ�������512�ֽ�Ϊ��ı߽�
*****************************************************************/
//��SD���϶�ȡһ������ ����ĵĴ�СΪSDCardInfo.CardBlockSize
BYTE MMC_Read2Blocks(char *buf,DWORD addr)
{
	return (SD_ReadMultiBlocks(buf,addr, SDBLOCKSIZE,2)==SD_OK);
}
//��SD����д��һ�����ݣ���ĵĴ�СΪSDCardInfo.CardBlockSize
BYTE MMC_Write2Blocks(char *buf,DWORD addr)
{
    return (SD_WriteMultiBlocks((BYTE *)buf, addr, SDBLOCKSIZE,2)==SD_OK);
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif



#if 0
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
uint8_t Buffer_Block_Tx[1024]  __attribute__ ((aligned (4)));
uint8_t Buffer_Block_Rx[1024]  __attribute__ ((aligned (4)));

void Test_SD_CCR(char mode)
{
    SD_Error SD_Status = SD_OK;
	uint32_t CardCapacity,ret,i,j;

	NVIC_SDConfiguration();

	xputs(" SD Initial.... \n");
	SD_Status = SD_Init(); //ouhs test 20140620
	if (SD_Detect()== SD_PRESENT)
	{
		//SD_PWR_ON();
		SD_Status = SD_Init();
		xputs(" SD is present. \n");

		if ((SD_Status == SD_OK))
		{
            CardCapacity = SDCardInfo.CardCapacity;
			USART_printf("\r\n SD Init success ");

			USART_printf( " \r\n SD_GetCardInfo is OK ");
			USART_printf( " \r\n CardType is ..%d ", SDCardInfo.CardType );
			USART_printf( " \r\n CardCapacity is ..0x%x", CardCapacity);
            //USART_printf( " \r\n CardCapacity is ..0x%x", (SDCardInfo.CardCapacity % 0x100000000));
			USART_printf( " \r\n CardBlockSize is ..%d ", SDCardInfo.CardBlockSize );
			USART_printf( " \r\n RCA is ..%d ", SDCardInfo.RCA);
			USART_printf( " \r\n ManufacturerID is ..%d ", SDCardInfo.SD_cid.ManufacturerID );
#if 0

			if (mode=='s')
			{
					for (i=0;i<CardCapacity;i+=SD_BLOCKSIZE)
					{
							sprintf(Buffer_Block_Rx,"Addr=%lX",i);
							PutsO(Buffer_Block_Rx);
							ret = SD_SingleBlockTest(i);
							if (ret)
							{
									USART_printf( " \r\n SD_SingleBlockTest Error at:%d \n", i+ret-1);
									break;
							}
					}
			}
			else if (mode=='S') //����д�ض��������ֽڲ���
			{
				for (i=0;i<CardCapacity;i+=1024)
                {
					for (j=0; j<1024; j++) //��д512�ֽ�
					  Buffer_Block_Tx[j] = i+j;
					ret = SD_ReadMultiBlocks((BYTE *)Buffer_Block_Rx, i, SD_BLOCKSIZE, 2); //ʹ��SD_ReadMultiBlocks�ȶ���д�ٶ����׳���
					memset(Buffer_Block_Rx, 0x5A, 1024);
					//USART_printf( " \r\n SD Write&Read:1...\n");
					if (ret == SD_OK)
					{
						ret = SD_WriteMultiBlocks((BYTE *)Buffer_Block_Tx, i, SD_BLOCKSIZE, 2);
						//USART_printf( " \r\n SD_WriteMultiBlocks ret=%d \n", ret);
					}
					if (ret == SD_OK)
					{
						ret = SD_ReadMultiBlocks((BYTE *)Buffer_Block_Rx, i, SD_BLOCKSIZE, 2);
						//USART_printf( " \r\n SD_ReadMultiBlocks ret=%d \n", ret);
						//USART_printf( " \r\n SD Write&Read:2...\n");
					}
					if (ret == SD_OK)
						ret = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, 1024);

					if (ret)
						{
								USART_printf( " \r\n SD Write&Read  Error at:%d \n", i+ret-1);
								break;
						}
					sprintf(Buffer_Block_Rx,"Addr=%lX",i);
					PutsO(Buffer_Block_Rx);
				}
				USART_printf( " \r\n SD Write&Read  END ");
			}
#endif
		}
		else
		{
			USART_printf("\r\n ERROR:SD Init failed! ");
			xprintf("\r\n SD_Status=%d \r\n", SD_Status);
		}
	}
	else
	{
		xputs(" SD is not present. \n");
	}
	while (1) {};
}

#endif

