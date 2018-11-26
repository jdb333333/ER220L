#define  MAIN_C 4

// =============================================================
// Riferimenti esterni
// =============================================================

#include "king.h"                               /* Kingtron library and I/O routines */
#include "exthead.h"
#include "exth.h"
#include "message.h"
#if (CASE_MFRIC==1)
    #include "MFRCard.h"
#endif
#if PC_EMUKEY
    #include "FEcrTest.h"
#endif

#if (defined(CASE_GPRS))
    #include "Gprs.h"
#endif


#if defined(CASE_ETHERNET)
void Ethernet_Init(uint8_t IP1,uint8_t IP2,uint8_t IP3,uint8_t IP4);
void tcp_server_init(uint16_t port);
void udp_server_init(uint16_t port);
void Set_ETHERNET_Ready(void);//ccr2015-01-22
    #if defined(DEBUGBYPC)
        #define LwIP_Periodic_Handle(localtime,fromINT) {}
    #else
void LwIP_Periodic_Handle(__IO uint32_t localtime,uint8_t fromINT);
    #endif
void Set_ETHERNET_Ready(void);
#endif

// ===========================================================
// Funzioni definite in questo file
// ===========================================================


void OutPrint(WORD Cmd, char *Line); //Lancia stampa (standard)
void OutPrintEx(WORD Cmd, char *Line, WORD DotLinesBlank);   //Lancia stampa (comando generico)

void ProcessKey(void);
WORD KeyInput(WORD  keyno);

short  KbHit(void);

BYTE CheckPrinter(BYTE mode);
void CheckICCard(void);


//Main program>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#if defined(DEBUGBYPC)

BYTE LoopInput=0;

void main_pc()
#else

extern void Print_Initial(void);
extern void STM32_Initial(void);
extern void USB_COMM_TEST(void);

void main()
#endif
{

#if defined(DEBUGBYPC)
    if (LoopInput)  return;
#else
    InitMonitor(MONITOR_RS232);

    STM32_Initial();
#if !defined(CASE_INNERDOTPRN)
    Print_Initial();
#endif
    Delay(5);//�ڻ����ϵ縴λ���к����Լ3ms����ʱ����Ϊ�������硢��λ100ms�󣬸�λ�ź���Чʱ��ϵͳ���ٴ�����Լ1.5ms

    RESETBIT(ApplVar.MyFlags,(HANZIMODE | PWDMODE | MENUMODE | KEYFROMHOST |CONFIGECR));//ccr20140514 ���������������������־  //

    InitApplication(false);     /* Initialise application program */

#if defined(CASE_ETHERNET)
    Ethernet_Init(ApplVar.IP.IPAddress[0],    //192
                  ApplVar.IP.IPAddress[1],    //168
                  ApplVar.IP.IPAddress[2],    //1
                  ApplVar.IP.IPAddress[3]);   //218
    tcp_server_init(ApplVar.IP.ClientPort);
    udp_server_init(ApplVar.IP.ClientPort+1);
    Set_ETHERNET_Ready();//ccr2015-01-22
    LwIP_Periodic_Handle(GetSystemTimer(),1);//ccr2015-01-29 it is must
#endif
    OpenMess(1);
#if defined(CASE_INNERDOTPRN)
    CheckPrinter(0);
#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    for (;;)         /* Exit loop only with power fail */
#endif
    {
        ApplRamSaved = 0x5a;//Appl Ram δ����
        ApplVar_Restored = 0x5a;
#if PC_EMUKEY
        FisTestProc();
#endif

#if defined(CASE_GPRS)
        GPRSWaitForReady(false);
#if (defined(CASE_INDONESIA))
        GPRSSendECR_HeartBeat(0);//ccr2015-08-03 ECR����ʱ����heartbeat����
#endif
#endif


#if (!defined(DEBUGBYPC))
#if POWERCTRL
        if (!DC_DET_GET() && ApplVar.PoolPushIn==ApplVar.PoolPopOut)//!TestPrintGoingOn())
        {
            mDrawPower(1,POWER_X,SCREENLN-1);//�����Ƿ���ʾ���
            pwrGetStatus(GET_VIN_STATUS);
            if (BATTERYTooLow(PWR_WARNING2 | PWR_BY_BAT))
            {
                while (BatteryVoltage()<VIN_LOW && !DC_DET_GET())
                {//�ȴ���絽ָ����ѹ��������
                    Bell(1);
                    DispStrXY(cCHARGEBATNOW,0,1);
                    Delay(500);
                    pwrGetStatus(GET_VIN_STATUS);
                }
            }
            if (BATTERYTooLow(PWR_BY_BAT | PWR_WARNING1))
                ApplVar.ErrorNumber = ERROR_ID(CWXXI74);
        }
#endif
#if defined(CASE_GPRS)
        if (!ApplVar.FRegi && ApplVar.PoolPushIn==ApplVar.PoolPopOut)//!TestPrintGoingOn())
            GPRS_DrawSignal();
#endif
#endif

#if (DD_CHIPC==1)
        CheckICCard();//ccr2014-03-21 ���IC���Ƿ���������
#endif
        Computer(); //communicate with computer

        BarCode();
        BalanceWeight();
        if (KeyInput(0))
            ProcessKey();
        else
        {
#if !defined(CASE_INNERDOTPRN)
            CheckPrinter(1);//ccr2017-09-06�ڴ�ӡ�����лᱨ��ӡ����(��ӡ������ȱ��)
#endif
            CheckTime(FALSE);            /* display time after 5 minutes */
        }
        CheckError(0);
    }
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}

//==================================================================
//Test if has some key for read
//Return True if a key pressed
short   KbHit()
{
    WORD i;
#if (defined(DEBUGBYPC))
    ProcessMessages();
#elif (CASE_USBDISK)
    USB_Detect();//ѭ�����USB�豸
#endif


#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
    EJ_Exist();//���EJ�Ƿ����
#endif
//ccr2015-03-12>�����ѯ��ʽ>>>>>>>>>>>>>>>>>>>
#if (0)//defined(CASE_ETHERNET)
#if !defined(CASE_ASCIIDISPLAY)
    mDrawGPRS(SCREENWD-1,0,0);//ccr2015-01-29 testonly
#endif
    LwIP_Periodic_Handle(GetSystemTimer(),0);//ccr2015-01-20
#endif
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    i =Bios_1(BiosCmd_CheckKeyborad);//����Ƿ��а���

#if (PC_EMUKEY)
    if (i && (i==ApplVar.AP.FirmKeys[ID_LOCK]+1))// && ApplVar.CentralLock==RG)
    {
        if (FisTestTask.Going)//�ڶ��ΰ����Լ�ʱ���رմ�ӡ��
        {
            if (FisTestTask.PrnOFF == 0)
                FisTestTask.PrnOFF = 1;
            else
                FisTestTask.Going = FisTestTask.PrnOFF = 0;//�رպ������Լ�ʱ���򿪴�ӡ��
            Getch();
            return 0;
        } else if (Appl_EntryCounter==0  && ApplVar.CentralLock==RG)
        {
            FisTestTask.Going = 0x01;
            Getch();
            return 0;
        }
    }
#endif
    if (i==0)
    {//�ް���
        if (KeyFrHost!=0xff)
        {
            SETBIT(ApplVar.MyFlags, KEYFROMHOST);
            i = Bios_Key0_Key = KeyFrHost+1;
            KeyFrHost = 0xff;
#if (defined(DEBUGBYPC) && PC_EMUKEY)
            if ((i==ApplVar.AP.FirmKeys[ID_LOCK]+1) && ApplVar.CentralLock==RG)
            {
                if (FisTestTask.Going)//�ڶ��ΰ����Լ�ʱ���رմ�ӡ��
                {
                    if (FisTestTask.PrnOFF == 0)
                        FisTestTask.PrnOFF = 1;
                    else
                        FisTestTask.Going = FisTestTask.PrnOFF = 0;//�رպ������Լ�ʱ���򿪴�ӡ��
                    Getch();
                    return 0;
                } else if (Appl_EntryCounter==0)
                {
                    FisTestTask.Going = 0x01;
                    Getch();
                    return 0;
                }
            }
#endif
        }
    } else if ((i-1) != ApplVar.AP.FirmKeys[ID_DATE])
        InActive = 0;
    return i;
}

//==================================================================
//Get the keyCode pressed by operator
//Return keycode pressed
#if (defined(DEBUGBYPC))
BYTE   Getch()
{
    short   i;

    if (TESTBIT(ApplVar.MyFlags, KEYFROMHOST))
    {
        RESETBIT(ApplVar.MyFlags, KEYFROMHOST);
        return(Bios_Key0_Key-1);
    } else
    {
        switch (Bios_Key0_Key-1)
        {

#if (fDATE!=0xff)
        case fDATE:
#endif
            //case fSHIFTHZ_ASC:
#if (!defined(DD_LOCK) && fLOCK!=0xff)
        case fLOCK:
#endif
        case fRJFEED:
            break;
        }
    }
    return(Bios_Key0_Key-1);


}
#endif
//==================================================================

#if !defined(CASE_INNERDOTPRN) //ccr2017-08-31
//--------------------------------------------------------
//����ӡ���Ĺ���״̬    			//
//return:0-Error found  1-no error //
BYTE CheckPrinter(BYTE mode)
{
    BYTE newErr;
#if !defined(DEBUGBYPC)

    newErr = 0;
    Get_Printer_status();//test power or printer
/*	if (sDot & 0x28)
    {
        ApplVar.ErrorNumber=0;
        PutsO(" LO BAT");
        InActive = 0;
        return;
    }
    else */
    if (Printer_Status.g_bNOPAPER)                       /* Near End */
    {
        newErr = ERROR_ID(CWXXI40);
    }
#if(CASE_HANDUP)	//    cc 20070827
    else if (Printer_Status.g_bHANDUP)                       /* Near End */
    {
        newErr = ERROR_ID(CWXXI39);
    }
#endif
    else if (Printer_Status.g_bTOOHOT)                       /* Near End */
    {
        newErr = ERROR_ID(CWXXI41);
    }
    if (newErr!=0)
    {
        if (newErr!=(ApplVar.ErrorNumber&0x7f))
            ApplVar.ErrorNumber=newErr;
        return false;
    } else if ((ApplVar.ErrorNumber&0x7f)>=ERROR_ID(CWXXI39) && (ApplVar.ErrorNumber&0x7f)<=ERROR_ID(CWXXI41))
    {
        Start_When_Ready(" ");
        ApplVar.ErrorNumber=0;
        ClsState2();
    }
#endif
    return TRUE;
}
#endif

// test chipcard                  //
void CheckICCard()
{//ccr050316
#if ((DD_CHIPC==1))
#if (CASE_MFRIC==1)
    if (((ApplVar.CentralLock & 0xff) == MG || ApplVar.CentralLock == RG) && ChipCard())// ���Կ��Ƿ�ȡ��  //
    {
        InActive = 0;
/*ccr20140420>>>>>
        if (ApplVar.CentralLock == (SETUPMG | MG))
        {//  �ڽ����˶�IC�������ò���ʱ������γ������Զ��Ƴ�����   //
            ClearEntry(false);
            ApplVar.KeyNo =  ApplVar.AP.FirmKeys[ID_CANCEL];
            CheckFirmKey();
        }
        if ((ApplVar.IC.REC_Customer[CC_CLIST] & 3)>0 && (ApplVar.IC.REC_Customer[CC_CLIST] & 3)<ApplVar.AP.Plu.Level)//ccr chipcard
            ApplVar.PluPriceLevel = 0;
<<<<<<*/
        if (!ApplVar.ErrorNumber)
        {
            mRefreshLine(STATELINE);
            PrintChipCard(0);
            Bell(1);
        }
    }
#else
    if (TESTBIT(ApplVar.IC.ICState,IC_INSERT) && !CC_Insert())// ���Կ��Ƿ�ȡ��  //
    {
        if ((ApplVar.IC.REC_Customer[CC_CLIST] & 3)>0 && (ApplVar.IC.REC_Customer[CC_CLIST] & 3)<ApplVar.AP.Plu.Level)//ccr chipcard
            ApplVar.PluPriceLevel = 0;
        ApplVar.IC.CHIP_Flag = IC_ILLERR;
        if (ApplVar.CentralLock == (SETUPMG | MG))// ���Կ��Ƿ�ȡ��  //
        {
            //  �ڽ����˶�IC�������ò���ʱ������γ������Զ��Ƴ�����   //

            ClearEntry(false);
            ApplVar.KeyNo =  ApplVar.AP.FirmKeys[ID_CANCEL];
            CheckFirmKey();
        }
    }
    if (((ApplVar.CentralLock & 0xff) == MG || ApplVar.CentralLock == RG)  && ChipCard())//ccr chipcard
    {
        InActive = 0;
        if (!ApplVar.ErrorNumber)
            PrintChipCard(0);
    }
#endif
#endif
}
//==========================================================================
short CheckFunctionEntry()
{
    if (ApplVar.Key.Code < 1000 && !(ApplVar.Key.Code % 100))
    {   /* number function key */
        if (!ApplVar.NumberEntry || ApplVar.NumberEntry > 99)
        {
            ApplVar.ErrorNumber=ERROR_ID(CWXXI01);
            return 1;
        }
#if defined(CASE_INDIA)//ccr2016-06-14
        if (ApplVar.Key.Code!=PORA)
#endif
        {
            ApplVar.Key.Code += ApplVar.NumberEntry;
            if (ApplVar.MultiplyCount)
            {
                ApplVar.DecimalPoint = ApplVar.Qty.Sign & 0x03;
                ApplVar.Entry = ApplVar.Qty;
                ApplVar.MultiplyCount = 0;
                GetWordEntry(); /* make word from entry to ApplVar.NumberEntry */
            } else
                Appl_EntryCounter = 0;
        }
    }
    return 0;
}


/*
void PowerUp(BYTE lock)
{
    BYTE save4 ;
    if (lock == SET)          // clear working memory //
        MemSet(DateAsci, (char *)&ApplVar.PluInventory + sizeof(ApplVar.PluInventory) - DateAsci, 0);      // clear working memory //
    if (!TESTBIT(KEYTONE, BIT3))    // print power up message ? //
    {
        ApplVar.PrintLayOut = 0x02;
        if (lock == SET)
        {
            strcpy(SysBuf,"    W-MEMORY CLEARED");
            PrintStr(SysBuf);
        }
        memcpy(SysBuf, Release, sizeof(Release));
        strcpy(SysBuf + sizeof(Release) - 1, Msg[JIADIAN].str);
        PrintStr(SysBuf);
        ApplVar.FReceipt = 0;
    }
//    if(TESTBIT(CLERKFIX, BIT5) && !ApplVar.FRegi)
//		ApplVar.ClerkNumber = 0 ;
//    else
    if ((!ApplVar.ClerkNumber || ApplVar.ClerkNumber > ApplVar.AP.Clerk.Number) && !TESTBIT(CLERKFIX, BIT0))  // Not Compulsory //
    {
        ApplVar.ClerkNumber = 1;
        ReadClerk();
    }
    if(TRAINING)
    {
        ApplVar.FTrain = 1 ;
    }
    if (!ApplVar.SalPerNumber && !TESTBIT(KEYTONE, BIT6))       // compulsory ? //
    {
        ApplVar.SalPerNumber = 1;
        ReadSalPer();
    }

    ClearEntry(false);
    PutsO(EntryBuffer + ENTRYSIZE - DISLEN - 1);
    InActive = ACTIVE + 1;  // set time on display //
    CheckTime(FALSE);
    Prefix1 = PREFIX_1;
    Prefix2 = PREFIX_2;
    ApplVar.AmtDecimal = NO_DECIMAL;

    save4 = ApplVar.SlipLines;
    ApplVar.SlipLines = 0;
    if (!TESTBIT(KEYTONE, BIT3))    // print power up message ? //
        ReceiptIssue(1);
    ApplVar.SlipLines = save4;

}
*/

void GetEntry()
{
    if (ApplVar.DecimalPoint)
        ApplVar.DecimalPoint--;
    ApplVar.Entry.Sign = ApplVar.DecimalPoint;
    StrToBCDValue(ApplVar.Entry.Value, &EntryBuffer[ENTRYSIZE - 2], BCDLEN);
    GetWordEntry(); /* make word from entry to ApplVar.NumberEntry */
}
//---------------- ��������ҵ���� ccr20130425----------------------//
// ��ڲ���:ApplVar.Key.Code=ҵ������
void   ProcessFunctions()
{
#if (defined(CASE_GPRS) && defined(CASE_INDONESIA))
    if (ApplVar.FRegi)
        GPRSSendECR_HeartBeat(0xff);//ccr2015-08-03 ECR����ʱ����heartbeat����
#endif

#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
    if (CheckEJError(true) &&   //EJ�д�ʱ,��ֹ���۲���
        (ApplVar.Key.Code<FIXED || ApplVar.Key.Code>FIXED_END))//����������������,�Խ�����������
    {
        ClearEntry(true);
        return;
    }
#endif

#if defined(DD_LOCK)
    //ccr2016-12-06>>>>>>
#ifdef TR
    if (ApplVar.FRegi && (GetchLockVal()!=(TR) && GetchLockVal()!=(RG) && GetchLockVal()!=(MG)))
#else
    if (ApplVar.FRegi && (GetchLockVal()!=(RG) && GetchLockVal()!=(MG)))
#endif
    {//Կ�׵�λ��
        ApplVar.ErrorNumber=ERROR_ID(CWXXI31);
        ClearEntry(true);
        return;
    }
    //ccr2016-12-06<<<<<<
#endif

#if defined(TEND_PREFIX)//ccr2016-08-08
    Prefix1 = 0;
    Prefix2 = 0;
#endif

    if (ApplVar.Key.Code < CORREC + 100)    /* correction functions 300 - 399 */
    {
        Correction();
#if (SCREENLN>6)
        DispStrXY(FormatQtyStr(Msg[XIANGSHU].str, &ApplVar.SaleQty, SCREENWD),0,SCREENLN-2);//ccr2016-03-03
#endif
    } else if (ApplVar.Key.Code < CURR + 100)    /* currency functions 400 - 499 */
        Currency();
    else if (ApplVar.Key.Code < DISC + 100)    /* discount functions 500 - 599 */
        Discount();
    else if (ApplVar.Key.Code < DRAW + 100)    /* drawer functions 600 - 699 */
        Drawer();
    else if (ApplVar.Key.Code < PBF + 100)    /* pb functions 700 - 799 */
        PbFunction();
    else if (ApplVar.Key.Code < PORA + 100)    /* ApplVar.PoRa functions 800 - 899 */
        PaidOutRa();
    else if (ApplVar.Key.Code < TEND + 100)   /* Tendering Functions 900 - 999 */
    {
        Tender();
#if (SCREENLN>6)
        DispStrXY(FormatQtyStr(Msg[XIANGSHU].str, &ApplVar.SaleQty, SCREENWD),0,SCREENLN-2);//ccr2016-03-03
#endif
    } else if (ApplVar.Key.Code < MODI + 1000)    /* Modifiers  1000 - 1999 */
        GetModifier();
    else if (ApplVar.Key.Code < FIXED + 100)   /* fixed functions 2000 - 2099 */
    {
        if (ApplVar.Key.Code>=MACROFUNC1 && ApplVar.Key.Code<=MACROFUNC20)
            ProcessKeyMacro(ApplVar.Key.Code);
        else if (ApplVar.Key.Code==FUNCLOOK1 || ApplVar.Key.Code==FUNCLOOK2)
            ProcessFuncLook(ApplVar.Key.Code);
        else
            Fixed();
        return;                        /* don't clear entry */
    } else if (ApplVar.Key.Code >= SALPER && ApplVar.Key.Code < SALPER+256)
        SelectSalPer();
    else if (ApplVar.Key.Code < CLERK)
        ApplVar.ErrorNumber=ERROR_ID(CWXXI42);
    else if (ApplVar.Key.Code < OFFER)
        SelectClerk(0);
    else if (ApplVar.Key.Code < PLU1)
    {
        ProcessDept();
#if (SCREENLN>6)
        DispStrXY(FormatQtyStr(Msg[XIANGSHU].str, &ApplVar.SaleQty, SCREENWD),0,SCREENLN-2);//ccr2016-03-03
#endif
    } else if (ApplVar.Key.Code < PLU3)
    {
        ProcessPlu();
#if (SCREENLN>6)
        DispStrXY(FormatQtyStr(Msg[XIANGSHU].str, &ApplVar.SaleQty, SCREENWD),0,SCREENLN-2);//ccr2016-03-03
#endif
    }
//  else if (ApplVar.Key.Code < 60000)
    else
        ApplVar.ErrorNumber=ERROR_ID(CWXXI42);
    ClearEntry(false);
}
/**
 * ����ApplVar.Key.Code�����Ƿ���Ҫ����������ݽ���С��ת��
 *
 * @author EutronSoftware (2016-05-28)
 *
 * @return BYTE:=true,��Ҫת��;=false,������������ݽ���С��ת��
 */
BYTE TestChangePointMust()
{
    return((ApplVar.Key.Code != MULT &&
            ApplVar.Key.Code!=CLERK &&
            ApplVar.Key.Code!=SALPER &&
            ApplVar.Key.Code!=VIPLOGIN &&
            ApplVar.Key.Code != NUMBER &&
            ApplVar.Key.Code != NUMBER1 &&
            ApplVar.Key.Code != NUMBER2 &&
            (ApplVar.Key.Code < DISC || ApplVar.Key.Code > PORA) &&
            ApplVar.Key.Code < PLU1) ||
           (ApplVar.Key.Code == MULT && ApplVar.CentralLock==MG && ApplVar.FInv == 3));
}
//Process the input from keyboard
//��������ҵ����
void ProcessKey()
{


    if (ApplVar.Key.Code == CLEAR)                     /* clear key ? */
    {
        Fixed();
        if (ApplVar.CentralLock==RG || ApplVar.CentralLock==MG)
            Appl_MaxEntry=ENTRYSIZE-1;
#if POWERCTRL
        if (!DC_DET_GET() && !ApplVar.FRegi)
            mDrawPower(2,POWER_X,SCREENLN-1);//��ʾ���
#endif
        return;
    } else if (ApplVar.ErrorNumber || !ApplVar.Key.Code)  /* Error Condition ? */
        return;
#if POWERCTRL
    if (!DC_DET_GET())
        mDrawPower(0,POWER_X,SCREENLN-1);//����ʾ���
#endif

    ApplVar.NumberEntry = 0;
    if (Appl_EntryCounter)          /* ApplVar.Entry ? */
    {
        if (Appl_EntryCounter <= (BCDLEN * 2))
            GetEntry();
        else
        {
            ApplVar.ErrorNumber=ERROR_ID(CWXXI01);                /* maximum 16 digits entry */
            return;
        }
    }
    if (ApplVar.FCorr || ApplVar.FRefund)
    {
        if (ApplVar.Key.Code >= TEND &&  ApplVar.Key.Code < (TEND + 100))
        {
            if (ApplVar.FRegi)
            {
                ApplVar.ErrorNumber=ERROR_ID(CWXXI01);
                return;
            }
        } else if (ApplVar.Key.Code >= PBF &&  ApplVar.Key.Code < (PBF + 100))
        {
        } else if (ApplVar.Key.Code >= DISC &&  ApplVar.Key.Code < (DISC + 100))
        {
        } else if (ApplVar.Key.Code >= PORA &&  ApplVar.Key.Code < (PORA + 100))
        {
        } else if (ApplVar.Key.Code != MULT && ApplVar.Key.Code != NPRICE && ApplVar.Key.Code < DEPT)
        {
            ApplVar.ErrorNumber=ERROR_ID(CWXXI01);
            return;
        }
    }
    if (CheckFunctionEntry())
        return;
    if ((ApplVar.MultiplyCount || ApplVar.FPrice) && ApplVar.Key.Code < DEPT
        && ApplVar.Key.Code != MULT && (ApplVar.Key.Code < PORA || ApplVar.Key.Code > PORA+99))
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI01);    /* multiply only on article, pora and X key */
        return;
    }
    if ((ApplVar.Key.Code < DISC || ApplVar.Key.Code > DISC + 100) &&
        (ApplVar.Key.Code < TEND || ApplVar.Key.Code > TEND + 100))
        ApplVar.FSub = 0;       /* reset subtotal flag */

//ccr090526>>>>>>>>>>>>>>>
    if (ApplVar.DecimalPoint && //������С�����,��ֹ���¹���>>>>
        ((ApplVar.Key.Code>=DRAW && ApplVar.Key.Code<=PORA ||
          ApplVar.Key.Code>=MODI && ApplVar.Key.Code<MULT ||
          ApplVar.Key.Code>=LEVEL1 && ApplVar.Key.Code<FUNCLOOK1 ||
          ApplVar.Key.Code>FUNCLOOK2 && ApplVar.Key.Code<=DEPT ||
          ApplVar.Key.Code % 100==0)//<<<<
         || //ccr2016-04-05>>>>>������Ϊ��С����ʱ,���¹��ܽ�ֹ����С��>>>>>>
         (NO_DECIMAL==1 && ApplVar.Key.Code != MULT &&
          ApplVar.Key.Code != NUMBER && ApplVar.Key.Code != NUMBER1 && ApplVar.Key.Code != NUMBER2 &&
          (ApplVar.Key.Code < DISC || ApplVar.Key.Code > DISC + 100) && (ApplVar.Key.Code < PLU1 + 1))//<<<<<<
        )
       )
    //<<<<<<<<<<<<<<<<<<<<<<<<
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI01);
        ClearEntry(false);
        return;
    }

    if (TestChangePointMust())
    {//���Ϲ��ܲ�Ҫ��С������ת��
        if (!ChangePoint())
        {
            ApplVar.ErrorNumber=ERROR_ID(CWXXI01);
            return;
        }
        SETBIT(ApplVar.MyFlags,DOTCHANGED);//ccr2016-05-28
    } else
        RESETBIT(ApplVar.MyFlags,DOTCHANGED);//ccr2016-05-28

//cc 20070718>>>>>>>>>>>>>>
    if (ApplVar.CentralLock!=RG && ApplVar.CentralLock!=MG)
        return;
//cc 20070718>>>>>>>>>>>>>>

    if (ApplVar.Key.Code < 300)    /* 256 to 299 not used */
        ApplVar.ErrorNumber=ERROR_ID(CWXXI42);
    else if (ApplVar.FInv && ApplVar.Key.Code < PLU1 && ApplVar.Key.Code != SUB && ApplVar.Key.Code != CLEAR
             && ApplVar.Key.Code != SUB1 && ApplVar.Key.Code != MULT
             && (ApplVar.Key.Code < LEVEL1 || ApplVar.Key.Code > LIST) && ApplVar.Key.Code != LEVEL
             && ApplVar.Key.Code != ARTLEVEL)
    {
        DispStrXY(ININVENTORY,0,0);//ccr2016-01-18
        ApplVar.ErrorNumber=ERROR_ID(CWXXI01);/* Ϊ�������½�ֹ�İ������� */
    } else if ((ApplVar.KeyNo==ApplVar.AP.FirmKeys[ID_LEFT] || ApplVar.KeyNo==ApplVar.AP.FirmKeys[ID_RIGHT])
               && ApplVar.FRegi && Appl_EntryCounter==0)
    /* Ϊ�����������,ֻ�ڴ������վݺ�����ô˹��� */
    {
        if (ApplVar.KeyNo==ApplVar.AP.FirmKeys[ID_LEFT] || !TESTBIT(ApplVar.MyFlags,RGREVIEW))
            Display_RGBuf(-1);
        else
            Display_RGBuf(1);
        SETBIT(ApplVar.MyFlags,RGREVIEW);//ccr2016-03-03
    } else
    {
        if (TESTBIT(ApplVar.MyFlags,RGREVIEW))
        {
            mClearScreen();
            RESETBIT(ApplVar.MyFlags,RGREVIEW);
        }
        ProcessFunctions();
    }
}


WORD KeyInput(WORD  keyno)
{
    BYTE   saveRet;

    if (keyno==0)
    {

        GetInputByListItems();//ccr2016-01-14��ListItems�����л�ȡ���ⰴ��

        keyno = ChnInput(0);

        if (!keyno)
            return 0;
        if (StrForST0)
        {
#if (SCRSTATDBL)
            DispOnStatDBL(StrForST0,0);
#else
            ClsState1();  //RG-DISPLAY
            DispSt0(StrForST0); //RG-DISPLAY
#endif
            StrForST0 = 0;
        }
        saveRet = keyno & 0x00ff;

        ApplVar.FBarcode = 0;
        //FGprs=0; //initial FPprs.     090803

        if (TESTBIT(ApplVar.MyFlags,CLSSCREEN) &&
            (saveRet != ApplVar.AP.FirmKeys[ID_LOCK] || Appl_EntryCounter!=0)
           )
        {
            mClearScreen();
            RESETBIT(ApplVar.MyFlags,CLSSCREEN);
        }

        if (keyno==0x3030 && Appl_EntryCounter==0 && ApplVar.CentralLock == SET && Appl_ProgStart==0)
        {//�ڽ������ú�����˵�������,����'00'����ӡϵͳ�˵�
            PrintSetupMenu();
            PrintXZMenu(X);
            PrintXZMenu(Z);
            PrintMGMenu();
            RFeed(6);//�ߵ�˺ֽλֵ
            return false;
        }

        if ((keyno & 0xff00)==0x0100 &&
            (!TESTBIT(ApplVar.ScreenStat,HZINPUTMODE) || TESTBIT(ApplVar.ScreenStat,HZSELECT)))//ccr2016-06-12@@@@@ �Ѿ�ѡ�������ʱ
        {
            //�Ѿ�ѡ����һ������ ʱ //
            keyno &= 0x00ff;

#if !defined(DD_LOCK)
            if (keyno < MAXKEYB)                 /* if keyno larger 63 then Lock Code */
#endif
            {
                if (ApplVar.AP.KeyTable[ApplVar.KeyNo] != CLEAR)
                    ApplVar.OldKey.Code = ApplVar.Key.Code;       /* save previous key */
                ApplVar.Key.Code = ApplVar.AP.KeyTable[ApplVar.KeyNo];
                keyno = CheckMode();//�����ж��Ƿ�Ϊ��ʽ�л�����
                if (keyno || (ApplVar.CentralLock != MG && ApplVar.CentralLock != RG && CheckFirmKey()))
                {
                    if (ApplVar.KeyNo == ApplVar.AP.FirmKeys[ID_ENTER])
                        ApplVar.DispKey.Code = ApplVar.KeyNo;
                    ApplVar.Key.Code = 0;
                    return FALSE;
                } else if (ApplVar.Key.C.High && ApplVar.CentralLock == RG && ApplVar.Key.Code != CLEAR &    /* function ? */
                           (ApplVar.AP.Manager[keyno >> 3] & (0x01 << (keyno & 7))))       //used only in MG
                {
                    ApplVar.ErrorNumber=ERROR_ID(CWXXI28);
                    return FALSE;
                } else
                    keyno = 0x0100 | saveRet;
            }
#if !defined(DD_LOCK)
            else if (!ApplVar.ErrorNumber)
            {
//				HEXtoASC(sBuf,&keyno,1);sBuf[2] = 0;
//				DispSt1(sBuf);
                return FALSE;
            }
#endif
        } else
        {
            if ((keyno & 0xff00)==0x0100)
            {
                if (ApplVar.AP.KeyTable[ApplVar.KeyNo] != CLEAR)
                    ApplVar.OldKey.Code = ApplVar.Key.Code;       /* save previous key */
                ApplVar.Key.Code = ApplVar.AP.KeyTable[ApplVar.KeyNo];
            } else
            {
                ApplVar.OldKey.Code = ApplVar.Key.Code;       /* save previous key */
/*ccr2014-03-11>>>>>>>>>>
                if (keyno==0x3030 && Appl_EntryCounter==0)//�����������������°�˫00��,ǿ��Ϊ�ҵ�����
                {
                    ApplVar.Key.Code = SUSPEND;       // ǿ��Ϊ�ҵ�����
                    return true;
                }
                else*/
                ApplVar.Key.Code = keyno;       /* save previous key */
            }
        }
    }
    Editor.EditBuff = EntryBuffer;
    Editor.BuffSize = ENTRYSIZE-1;

    if ((ApplVar.CentralLock==SET || ApplVar.CentralLock==(SETUPMG | MG)) &&  Appl_ProgLine>1)
    {//Appl_ProgLine>1ʱ,�����������ʾ����Ļ������
        if (TESTBIT(ApplVar.MyFlags,HANZIMODE))
        {
            Appl_EntryCounter = Editor.EditCount;
            Editor.DispY = CursY;
        } else
        {
            //GotoXY(SCREENWD,CursY);
            {
                Editor.DispY = CursY;
            }
            Editor.EditOffs=0;
            Editor.EditCount = Appl_EntryCounter;
        }

    } else
    {
        SetEditPosition(INPUTDISPX,SCREENLN,Appl_EntryCounter,NULL);
    }
    saveRet = LineEditor(*((union KEY *)&keyno));//�༭��������
    if (saveRet!=0xff)
    {
        Appl_EntryCounter = saveRet;
        if (ApplVar.CentralLock==SET || ApplVar.CentralLock==X || ApplVar.CentralLock==Z)
        {//ΪSET/X/Z��,��Ļ����ʾ���ǲ˵�
            if (Editor.DispY==STATELINE)//&&Appl_EntryCounter==1)
                ClsState1();//����˵������ʾ��
            GetInputForMenu(keyno);//ѡ��˵���Ŀ
        }

    } else if ((keyno & 0xff00)==0x0100)// && !ApplVar.ErrorNumber)
    {
        return true;
    }
    return FALSE;
}


/* return 1 incase of error */
BYTE AmtInputMask()
{
/*    if (Appl_EntryCounter && TESTBIT(ROUNDMASK, BIT0))
    {       // entry must end with 0 or 5
        switch(ApplVar.Entry.Value[0] & 0x0f)
        {
            case 0:
            case 5:
                break;
            default:
                ApplVar.ErrorNumber=ERROR_ID(CWXXI01);
                return 1;
        }
    }*/
    return 0;
}



//
// Funzione OutPrint
// -----------------
//
// Lancia un comando di stampa standard sulla stampante
//
// Inputs :   Cmd              = Comando di stampa (CMDP_xx)
//            *Line            = Pointer a linea di dati da stampare
//


void OutPrint(WORD Cmd, char *Line)
{
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
    if (ApplVar.CentralLock==SET && TESTBIT(ApplVar.EJVar.ContFlag,EJDOCHEAD) && !CheckEJError(true))
    {//SET���д�ӡʱ
        RefreshEJStart(true);
        StoreEJData(CEJ_DOCEND,Msg_ENTERSETUP);//������ӡ
#if defined(DEBUGBYPC)
        OutPrintExForDebug(Cmd, Msg_ENTERSETUP, 0);
#endif
        //StoreEJEnd();//ccr070609pm
    }
#endif
    //if (!TESTBIT(ApplVar.MyFlags, PRNONPB+ENPRINTER))     //lyq20040223 added for control the printing of pb message
    {
        if (Line && Line[0]=='@')
            OutPrintEx(CMDP_DR, Line+1, 0);
        else
            OutPrintEx(Cmd, Line, 0);
    }
}




//
// Funzione OutPrintEx
// -------------------
//
// Lancia un comando di stampa esteso sulle stampanti interne (Scontrino e/o Giornale)
//
// Inputs :   Cmd              = Comando di stampa (CMDP_xx)
//            *Line            = Pointer a linea di dati da stampare
//            DotLinesBlank    = #dot line post-stampa addizionali
//


void OutPrintEx(WORD Cmd, char *Line, WORD DotLinesBlank)
{
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
    if (Line && TestSaveEJ())
    {
        if (Cmd==CMDP_R)
            StoreEJData(CEJ_STARTLN,Line);//������ӡ
        else if (Cmd==CMDP_DR)
            StoreEJData(CEJ_STARTLND,Line);//���ߴ�ӡ
    }
#endif

//ccr2016-12-14 ExtPrinter>>>>>>>>>>>
    if (ApplVar.ExtPrinter.port)
    {
        SendExtPrinter(Cmd,Line,1);
    }
//ccr2016-12-14<<<<<<<<<<<<<<<<<<<<<<
#if defined(DEBUGBYPC)
    OutPrintExForDebug(Cmd, Line, DotLinesBlank);
#if defined(CASE_INNERDOTPRN)
    SendExtPrinter(Cmd,Line,0);
#endif

#else

#if (PC_EMUKEY)
    if (!FisTestTask.PrnOFF || !FisTestTask.Going)
#endif
        if (!TESTBIT(ApplVar.MyFlags, PRNONPB+ENPRINTER))     //lyq20040223 added for control the printing of pb message
#if defined(CASE_INNERDOTPRN)
        {
            if (Cmd!=CMDP_LFR)
                CheckPrinter(2);
            SendExtPrinter(Cmd,Line,0);
        }
#else
            Bios(BiosCmd_PrintX, (void*)Line, Cmd , DotLinesBlank);
#endif
#endif
}



