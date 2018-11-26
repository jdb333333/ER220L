#include "king.h"
#include "exthead.h"
#include "exth.h"
#include "flashb.h"
#include "message.h"
//the commmand of collect flow

#if (PC_EMUKEY)
#include "FEcrtest.h"
extern void SendALong(long pLInt);
#endif

void  DispDateRecNo(BYTE line);

void LoadReceipLog(void);
void DispNULL(void);                              //reserved
void DispDept(void);
void DispPlu(void);
void DispEnd(void);
void DispNonAdd(void);
void DispPoRa(void);
void DispOperator(void);
void DispTender(void);
void DispModeLock(void);
void DispPercentDisc(void);
void DispSubTotalDisc(void);
void DispDirectDisc(void);
void DispSubTotalDirDisc(void);
void DispNew(void);
void DispSubTotals(void);
void DispMessage(void);
void DispRPEnd(void);
void DispInsertIC(void);
void DispRefreshIC(void);
void DispSetPrice(void);
void DispEcrNum(void);          //only send to manage systyem
void DispVoid(void);            //record the operation of close table
void DispPbClose(void);         //record the operation of close table
void DispPbOpen(void);          //record the operation of close table
void DispPbTransTo(void);           //record the operation of close table
void DispTAX(void);
#if defined(CASE_INDIA)//ccr2016-06-03>>>>>>>
void DispPluData(void);         //��¼�޸�PLU������־
void DispDeptData(void);         //��¼�޸�Dept������־
#endif//ccr2016-06-03<<<<<<

void ClearLogFor(ULONG sSize);
void Clear_FlowBuff(void);
void Init_Flow(void);

struct CDC_REGIS	CDC_regis_cp;	//start register record//ccr2015-06-15

CONST struct ECRLOGDES LogSize[LOGTYPEMAX]={
    {RESERVERLOG,                    &DispNULL},           //reserved
    {sizeof(struct CDC_DPT),         &DispDept},
    {sizeof(struct CDC_ART),         &DispPlu},
    {sizeof(struct CDC_END),         &DispEnd},
    {sizeof(struct CDC_NOADD),       &DispNonAdd},
    {sizeof(struct CDC_OPER),        &DispOperator},
    {sizeof(struct CDC_GIVEN),       &DispTender},
    {sizeof(struct CDC_LOCK),        &DispModeLock},
    {sizeof(struct CDC_DISCADD),     &DispPercentDisc},
    {sizeof(struct CDC_SUBDISCADD),  &DispSubTotalDisc},
    {sizeof(struct CDC_DIRECT),      &DispDirectDisc},
    {sizeof(struct CDC_SUBDIRECT),   &DispSubTotalDirDisc},
    {sizeof(struct CDC_REGIS),       &DispNew},
    {sizeof(struct CDC_SUBTOTAL),    &DispSubTotals},
    {sizeof(struct CDC_MESSAGE),      &DispMessage},
    {sizeof(struct CDC_SLIPEnd),     &DispRPEnd},
    {sizeof(struct CDC_EnterIC),     &DispInsertIC},
    {sizeof(struct CDC_REFRESHIC),   &DispRefreshIC},
    {sizeof(struct CDC_PRICELIST),   &DispSetPrice},
    {sizeof(struct CDC_ECRNUM),      &DispEcrNum},          //only send to manage systyem

    {sizeof(struct CDC_VOID),        &DispVoid},            //record the operation of close table
    {sizeof(struct CDC_PBCLOSE),     &DispPbClose},         //record the operation of close table
    {sizeof(struct CDC_PBOPEN),      &DispPbOpen},          //record the operation of close table
    {sizeof(struct CDC_PBTT),        &DispPbTransTo},           //record the operation of close table
    {sizeof(struct CDC_PORA),        &DispPoRa},            //record the operation of close table
    {sizeof(struct CDC_NETID),       &DispNULL},            //record the NetID
    {sizeof(struct CDC_TAX),         &DispTAX},         //record the TAX
#if defined(CASE_INDIA)//ccr2016-06-03>>>>>>>
    {sizeof(struct CDC_EDITPLU),     &DispPluData},         //��¼�޸�PLU������־
    {sizeof(struct CDC_EDITDEPT),     &DispDeptData},         //��¼�޸�Dept������־
#endif//ccr2016-06-03<<<<<<
};


struct LOGCOND LogDefine;


//==========================================================================
/**
 * �����ָ���ˮ��ȡָ��
 *
 * @author EutronSoftware (2015-08-25)
 *
 * @param Size :=0,�����ȡλ��,>0,�ָ���ȡλ��
 */
void SUB_SCANFP(BYTE Size)
{
    static ULONG ReadP;
    if (Size)
        ApplVar.FlowHeader.ReadP = ReadP;
    else
        ReadP = ApplVar.FlowHeader.ReadP;
}

void ChangeQty(BCD *sBcd)
{
    BYTE Sign;

    Sign = sBcd->Sign;
    switch (Sign&0xf)
    {
    case 0:
        BcdMul10(sBcd);
    case 1:
        BcdMul10(sBcd);
    case 2:
        BcdMul10(sBcd);
    }
    sBcd->Sign = Sign;
}

void Collect_Given()
{
    if (ApplVar.TendNumber < ApplVar.AP.Tend.Number && ApplVar.GCouter<TENDLOGMAX)
    {
        ApplVar.CollectGiven[ApplVar.GCouter].FTType = ApplVar.TendNumber+1;
        memcpy(ApplVar.CollectGiven[ApplVar.GCouter].FAmt, ApplVar.Amt.Value, sizeof(ApplVar.CollectGiven[0].FAmt));
        if ((ApplVar.GCouter == 0) && (ApplVar.Amt.Sign & 0x80))
        {
            ApplVar.CollectGiven[ApplVar.GCouter].FTType |= 0x80;
        }
        ApplVar.GCouter++;
    }
}
//���LOG�洢���Ƿ������Ż�ʣ��ռ��С
UnLong CheckLogBuff()
{
    UnLong sFreeMem;

    if (ApplVar.FlowHeader.NextNP>= ApplVar.FlowHeader.HeadP)
        sFreeMem = ApplVar.FlowHeader.MAXNUMB - (ApplVar.FlowHeader.NextNP- ApplVar.FlowHeader.HeadP);
    else
        sFreeMem = ApplVar.FlowHeader.HeadP - ApplVar.FlowHeader.NextNP;

    if (sFreeMem<LOGALARMON && ApplVar.FlowHeader.OverCount<2)
    {
#if (SCRSTATDBL)
        DispOnStatDBL((char *)Msg[RZQMAN].str,0);
#else
        DispSt2C(Msg[RZQMAN].str);//RG-DISPLAY
#endif
        Bell(3);
        while (!KbHit() || Getch()!=ApplVar.AP.FirmKeys[ID_CLEAR])//�ȴ�����
        {
            if (CheckComm(COMPUTER_1))//����м����ͨ��,Ҳ�˳��ȴ�
                break;
        }

        ApplVar.FlowHeader.OverCount++;
#if (FLOW_IN_EXTRAM==1)//�ͷſռ�
        ApplVar.FlowHeader.HeadP = ApplVar.FlowHeader.ReadP;
        if (ApplVar.FlowHeader.NextNP>= ApplVar.FlowHeader.HeadP)
            sFreeMem = ApplVar.FlowHeader.MAXNUMB - (ApplVar.FlowHeader.NextNP- ApplVar.FlowHeader.HeadP);
        else
            sFreeMem = ApplVar.FlowHeader.HeadP - ApplVar.FlowHeader.NextNP;
#endif
    }
#if (FLOW_IN_EXTRAM==1)//��ŵ�FLASH��ʱ�����Զ��������ͷų�64K�������ڴ��ͷſռ�
    if (sFreeMem<LOGALARMON)
        ClearLogFor(LOGALARMON);
#endif
    if (ApplVar.FlowHeader.NextNP>= ApplVar.FlowHeader.HeadP)
        return(ApplVar.FlowHeader.MAXNUMB - (ApplVar.FlowHeader.NextNP- ApplVar.FlowHeader.HeadP));
    else
        return(ApplVar.FlowHeader.HeadP - ApplVar.FlowHeader.NextNP);
}
//��ReadP��ʼ�ͷ�sSize�ֽ�
void ClearLogFor(ULONG sSize)
{
    ULONG   sLength;
    short   i;
    char    sBuf[1];
    BYTE    sCtrl;

    sLength = 0;
    sCtrl = (ApplVar.FlowHeader.ReadP<ApplVar.FlowHeader.NextNP)?1:2;

    while (sLength<=sSize && ApplVar.FlowHeader.ReadP!=ApplVar.FlowHeader.NextNP)
    {
        ReadFrLogRam(sBuf,ApplVar.FlowHeader.ReadP,1);
        i = sBuf[0] & 0x1f;
        if (i>0 && i<=LOGTYPEMAX)
        {
            if (i==TENDLOG)
            {
                ReadFrLogRam(sBuf,ApplVar.FlowHeader.ReadP+1,1);
                i = (sBuf[0] & 0x0f) * sizeof(struct GIVEN_DATA)+2;
            } else
                i = LogSize[i-1].RecSize;
            sLength += i;
            ApplVar.FlowHeader.ReadP = ApplVar.FlowHeader.ReadP + i;
            ADJLOGADDR(ApplVar.FlowHeader.ReadP);
            if (ApplVar.FlowHeader.ReadP>ApplVar.FlowHeader.NextNP)
            {
                if (sCtrl & 1)
                {
                    ApplVar.FlowHeader.ReadP= ApplVar.FlowHeader.NextNP;
                    ApplVar.FlowHeader.OverCount = 0;
                    break;
                } else
                    sCtrl |= 2;
            }
            if (ApplVar.FlowHeader.ReadP<ApplVar.FlowHeader.NextNP)
                sCtrl |= 1;
        } else
        {
            ApplVar.FlowHeader.ReadP++;//�����Ƿ���ˮ����
            sLength++;
            //break;
        }
    }
    ApplVar.FlowHeader.HeadP = ApplVar.FlowHeader.ReadP;
}
//Read block data from log area
//pFrom:address for read
//pTo:Address for write
//pSize
//ccr20110707>>>>>>>>
void ReadFrLogRam(char *pTo,UnLong pFrom,short pSize)
{
    short      skip;
#if (FLOW_IN_EXTRAM==1)
    skip = pSize;
    if ((UnLong)pFrom+pSize>=ApplVar.FlowHeader.EndAddr)
    {//����Ҫ��ȡ�������з���
        skip = ApplVar.FlowHeader.EndAddr - (UnLong)pFrom;

        RamOffSet = (UnLong)pFrom;
        ReadRam(pTo,skip);
        pTo = pTo + skip;
        skip = pSize - skip;
        pFrom = ApplVar.FlowHeader.FromAddr;
    }
    RamOffSet = (UnLong)pFrom;
    ReadRam(pTo,skip);
#else
    skip = pSize;
    if ((UnLong)pFrom+pSize>=ApplVar.FlowHeader.EndAddr)
    {//����Ҫ��ȡ�������з���
        skip = ApplVar.FlowHeader.EndAddr - (UnLong)pFrom;

        bFlashReadBuffer((BYTE*)pTo, pFrom, skip);

        pTo = pTo + skip;
        skip = pSize - skip;
        pFrom = ApplVar.FlowHeader.FromAddr;
    }
    bFlashReadBuffer((BYTE*)pTo, pFrom, skip);

#endif
}

//Read block data from log area
//pFrom:address for read
//pTo:Address for write
//pSize
void WriteToLogRam(ULONG pTo,char *pFrom,short pSize)
{
    ULONG   skip;
#if (FLOW_IN_EXTRAM==1)
    if (ApplVar.FlowHeader.MAXNUMB<LOGALARMON)
        return;
    if ((UnLong)pTo+pSize>=ApplVar.FlowHeader.EndAddr)
    {//����Ҫ��ȡ�������з���
        skip = ApplVar.FlowHeader.EndAddr - (UnLong)pTo;

        RamOffSet = (UnLong)pTo;
        WriteRam(pFrom,skip);
        pTo = (char*)ApplVar.FlowHeader.FromAddr;
        pFrom = pFrom+skip;
        skip = pSize - skip;
    } else
        skip = pSize;
    RamOffSet = (UnLong)pTo;
    WriteRam(pFrom,skip);
#else
    char sAddrF,sAddrT;

    if (ApplVar.FlowHeader.MAXNUMB<LOGALARMON
        || ApplVar.FlowHeader.NextNP<FLASH_LOG_ADDR)//����д���ַ������ˮ�ռ���
        return;
    sAddrF = ((UnLong)pTo>>16);//д�����ݿ�ʼ��
    sAddrT = (((UnLong)pTo+pSize)>>16);//д�����ݽ�����
    if (sAddrT>sAddrF)
    {//���ݿ��,��Ҫ����sAddrT���ڵĿ�
        if (sAddrT==(ApplVar.FlowHeader.EndAddr>>16))//��Ҫд��������з���
            sAddrT = (ApplVar.FlowHeader.FromAddr>>16);
        if (sAddrT==sAddrF)
        {//64K only
            Init_Flow();
            pTo = ApplVar.FlowHeader.NextNP;
        } else
        {
            if (sAddrT==(ApplVar.FlowHeader.HeadP>>16))//�����Ҫ�����Ŀ��뽫��ˮͷ���ڵ����ݿ��ص�
                ApplVar.FlowHeader.HeadP = ApplVar.FlowHeader.ReadP;

            if (sAddrT==(ApplVar.FlowHeader.ReadP>>16))
            {//�����Ҫ�����Ŀ��뽫Ҫ��ȡ�����ݿ��ص�
                skip = 0x10000L-(ApplVar.FlowHeader.ReadP & 0xffff);//������Ҫ��sAddrT���ͷŵĿռ��С
                ClearLogFor(skip);//�ƶ���ˮ���ݶ�ȡָ��,ʹ��ָ��һ���Ϸ��ļ�¼
            }

#if MX29LV160DBTI==1
#if (FLASH_LOG_BLOCKFr==0)
            if (sAddrT>0)
#endif
            {
                sAddrT+=3;//���ɿ����(ΪMX29LV160DBTI,ǰ��������С��)
            }
#endif
#if (FLASH_LOG_BLOCKFr==0 && FLASH_LOG_BLOCKS>1)//ccr2016-11-28
            if (sAddrT==0)
                bFlashMBlockErase(sAddrT,4);//����ʵ��ַ��ʼ����4��(64k)
            else
#endif
                bFlashMBlockErase(sAddrT,1);//����64K,�ͷŴ洢�ռ�
            ApplVar.FlowHeader.OverCount=0;//�����ٱ���
        }
    }
    if ((UnLong)pTo+pSize>=ApplVar.FlowHeader.EndAddr)
    {//�洢�ռ䷭��
        skip = ApplVar.FlowHeader.EndAddr - (UnLong)pTo;

        bFlashProgram((UnLong)pTo,skip,pFrom);//����д�����һ��ʣ��ռ���
        pTo = ApplVar.FlowHeader.FromAddr;
        pFrom = pFrom+skip;
        skip = pSize - skip;
    } else
        skip = pSize;
    bFlashProgram((UnLong)pTo,skip,pFrom);
#endif
}

//read a log record to the buffer Area
//return:0--no log record
//	     -1--error on log record
short Read_Flow(BYTE *Area)
{
    short sLength;
    short     i;

    SUB_SCANFP(0);//ccr2015-08-25

    if (ApplVar.FlowHeader.ReadP==ApplVar.FlowHeader.NextNP)
        return 0;//no Log record

    ReadFrLogRam(Area,ApplVar.FlowHeader.ReadP,1);
    i = Area[0] & 0x1f;
    if (i>0 && i<=LOGTYPEMAX)
    {
        Area++;
        if (i==TENDLOG)
        {
            ReadFrLogRam(Area,ApplVar.FlowHeader.ReadP+1,1);
            sLength = (Area[0] & 0x0f) * sizeof(struct GIVEN_DATA);
            Area++;
            i = 2;
        } else
        {
            sLength = LogSize[i-1].RecSize-1;
            i = 1;
        }
        if (sLength)
        {
            ReadFrLogRam(Area,ApplVar.FlowHeader.ReadP+i,sLength);
        }
        ApplVar.FlowHeader.ReadP = ApplVar.FlowHeader.ReadP + i + sLength;
        ADJLOGADDR(ApplVar.FlowHeader.ReadP);
        return i+sLength;
    } else
        return -1;
}


short Collect_Data(BYTE cmd)
{
    struct TimeDate sDate;

    WORD     Length,i;                           // write flow record size every time
    BCD     sBCD;
    UINT64  Long64;
    ULONG  uLong;

    if ((!TESTBIT(DOT,BIT2)&&(cmd==OPERLOG || cmd==LOCKLOG))
        || ApplVar.FlowHeader.MAXNUMB<LOGALARMON)
        return 1;
    Length = 0;
    ApplVar.FlowBuff.CDC_dpt.FunN = cmd;
    switch (cmd)
    {
    case PORALOG:
        if (!TESTBIT(ApplVar.PoRa.Options, BIT3))
            ApplVar.FlowBuff.CDC_PoRa.FunN |= 0x80;
        ApplVar.FlowBuff.CDC_PoRa.PoRaN = ApplVar.PoRaNumber+1;
        memcpy(ApplVar.FlowBuff.CDC_PoRa.FAmt, ApplVar.Amt.Value, sizeof(ApplVar.FlowBuff.CDC_PoRa.FAmt));
        Length = sizeof(ApplVar.FlowBuff.CDC_PoRa);
        break;
    case DEPTLOG:
        if (ApplVar.FRefund || ApplVar.FTrvoid)
            ApplVar.FlowBuff.CDC_dpt.FunN |= 0x80;
        if ((ApplVar.FVoid || ApplVar.FCorr) && TESTBIT(ApplVar.Qty.Sign,BIT7))
            ApplVar.FlowBuff.CDC_dpt.FunN |= 0xc0;
        ApplVar.FlowBuff.CDC_dpt.DeptN = ApplVar.DeptNumber+1;
        sBCD = ApplVar.Qty;
        ChangeQty(&sBCD);
        memcpy(ApplVar.FlowBuff.CDC_dpt.FQty, sBCD.Value, sizeof(ApplVar.FlowBuff.CDC_dpt.FQty));
        memcpy(ApplVar.FlowBuff.CDC_dpt.FAmt, ApplVar.Amt.Value, sizeof(ApplVar.FlowBuff.CDC_dpt.FAmt));
        Length = sizeof(ApplVar.FlowBuff.CDC_dpt);
        break;
    case PLULOG:
        if (ApplVar.FRefund || ApplVar.FTrvoid)
            ApplVar.FlowBuff.CDC_art.FunN |= 0x80;
        if ((ApplVar.FVoid || ApplVar.FCorr) && TESTBIT(ApplVar.Qty.Sign,BIT7))
            ApplVar.FlowBuff.CDC_art.FunN |= 0xc0;
        memcpy(ApplVar.FlowBuff.CDC_art.ArtN, ApplVar.Plu.Random, sizeof(ApplVar.Plu.Random));
        ApplVar.FlowBuff.CDC_art.DeptN = ApplVar.DeptNumber+1;
        sBCD = ApplVar.Qty;
        ChangeQty(&sBCD);
        memcpy(ApplVar.FlowBuff.CDC_art.FQty, sBCD.Value, sizeof(ApplVar.FlowBuff.CDC_art.FQty));
        memcpy(ApplVar.FlowBuff.CDC_art.FAmt, ApplVar.Amt.Value, sizeof(ApplVar.FlowBuff.CDC_art.FAmt));
        if (ApplVar.OFFNumber < ApplVar.AP.OFFPrice.Number)
            ApplVar.FlowBuff.CDC_art.OffNum = ApplVar.OFFNumber+1;
        else
            ApplVar.FlowBuff.CDC_art.OffNum = 0;
        Length = sizeof(ApplVar.FlowBuff.CDC_art);
        break;
    case TAXLOG://ccr2014-12-30>>>>>>>>>>
        if (TESTBIT(ApplVar.Amt.Sign,BIT7)) //ccr2015-08-14
            ApplVar.FlowBuff.CDC_Tax.FunN |= 0x80;

        ApplVar.FlowBuff.CDC_Tax.TaxID = ApplVar.TaxNumber+1;
        memcpy(ApplVar.FlowBuff.CDC_Tax.FRate, ApplVar.Tax.Rate, sizeof(ApplVar.FlowBuff.CDC_Tax.FRate));

        if (!TESTBIT(ApplVar.Tax.Options, BIT0)) /*ccr20130927 add on ? */
            memcpy(ApplVar.FlowBuff.CDC_Tax.FAmt, ApplVar.Amt.Value, sizeof(ApplVar.FlowBuff.CDC_Tax.FAmt));  /* ��ӡ˰�ֵ����۽�� */
        else
            memcpy(ApplVar.FlowBuff.CDC_Tax.FAmt, ApplVar.DiscAmt.Value, sizeof(ApplVar.FlowBuff.CDC_Tax.FAmt)); /* ��ӡ˰�ֵ����۾��� */
        memcpy(ApplVar.FlowBuff.CDC_Tax.FTax, ApplVar.Cost.Value, sizeof(ApplVar.FlowBuff.CDC_Tax.FTax)); /* ��ӡ˰�ֵ����۾��� */

        Length = sizeof(ApplVar.FlowBuff.CDC_Tax);
        break;//<<<<<<<<<<<<<<<<<<<
    case ENDLOG:
        if (ApplVar.FTrvoid || (ApplVar.SubTotal.Sign & 0x80))
            ApplVar.FlowBuff.CDC_end.FunN |= 0x80;
        memcpy(ApplVar.FlowBuff.CDC_end.ReceiptNum, ApplVar.ReceiptNumber, sizeof(ApplVar.FlowBuff.CDC_end.ReceiptNum));
        memcpy(ApplVar.FlowBuff.CDC_end.FAmt, ApplVar.SaleAmt.Value, sizeof(ApplVar.FlowBuff.CDC_end.FAmt));
        GetTimeDate(&sDate);
        ApplVar.FlowBuff.CDC_end.FDay = sDate.day;
        ApplVar.FlowBuff.CDC_end.FMonth = sDate.month;
        ApplVar.FlowBuff.CDC_end.FYear = (BYTE)sDate.year;
        ApplVar.FlowBuff.CDC_end.FHour = sDate.hour;
        ApplVar.FlowBuff.CDC_end.FMinute = sDate.min;
        Length = sizeof(ApplVar.FlowBuff.CDC_end);
        break;
    case NOADDLOG://ccr2016-05-04
        Long64 = BCDValueToLong64(ApplVar.NumberEntered.Value);//ccr2016-05-31
        memcpy(ApplVar.FlowBuff.CDC_noadd.Num,(char*)&Long64,sizeof(ApplVar.FlowBuff.CDC_noadd.Num));
        Length = sizeof(ApplVar.FlowBuff.CDC_noadd);
        break;
    case OPERLOG:
        ApplVar.FlowBuff.CDC_oper.OperN=(BYTE)ApplVar.ClerkNumber;
        Length = sizeof(ApplVar.FlowBuff.CDC_oper);
        break;
    case TENDLOG:
        ApplVar.FlowBuff.CDC_given.Counter = ApplVar.GCouter;
        if (ApplVar.FTrvoid || (ApplVar.CollectGiven[0].FTType & 0x80))
        {
            ApplVar.FlowBuff.CDC_given.FunN |= 0x80;
            ApplVar.CollectGiven[0].FTType &= 0x7f;
        }
        for (i=0;i<ApplVar.GCouter;i++)
            ApplVar.FlowBuff.CDC_given.GivenData[i] = ApplVar.CollectGiven[i];
        Length = sizeof(struct GIVEN_DATA)*ApplVar.GCouter+2;
        ApplVar.GCouter = 0;
        break;
    case LOCKLOG:
        ApplVar.FlowBuff.CDC_lock.NoModeLock = ApplVar.NumberEntry;
        Length = sizeof(ApplVar.FlowBuff.CDC_lock);
        break;
    case DISCADDLOG://  �ۿۼӳ�   //
        if (!TESTBIT(ApplVar.Disc.Options,BIT3))//ccr20130905
            ApplVar.FlowBuff.CDC_discadd.FunN |= 0x80;
        if (ApplVar.FVoid)
            ApplVar.FlowBuff.CDC_discadd.FunN ^= 0xc0;
//        	if (ApplVar.FRefund==1)	//ccr 050608 �˻�����  //
//				ApplVar.FlowBuff.CDC_discadd.FunN |= 0x40;

        memcpy(ApplVar.FlowBuff.CDC_discadd.Percent, ApplVar.Entry.Value, sizeof(ApplVar.FlowBuff.CDC_discadd.Percent));// percent
        memcpy(ApplVar.FlowBuff.CDC_discadd.FAmt, ApplVar.Amt.Value, sizeof(ApplVar.FlowBuff.CDC_discadd.FAmt));
        memcpy(ApplVar.FlowBuff.CDC_discadd.ArtN, ApplVar.Plu.Random, sizeof(ApplVar.Plu.Random));
        Length = sizeof(ApplVar.FlowBuff.CDC_discadd);
        break;
    case SUBDISCADDLOG:// С���ۿۼӳ�  //
        if (!TESTBIT(ApplVar.Disc.Options,BIT3))//ccr20130905
            ApplVar.FlowBuff.CDC_subdiscadd.FunN |= 0x80;
        if (ApplVar.FVoid)
            ApplVar.FlowBuff.CDC_subdiscadd.FunN ^= 0xc0;
//        	if (ApplVar.FRefund==1)	//ccr 050608 �˻�����  //
//				ApplVar.FlowBuff.CDC_discadd.FunN |= 0x40;

        memcpy(ApplVar.FlowBuff.CDC_subdiscadd.Percent, ApplVar.Entry.Value, sizeof(ApplVar.FlowBuff.CDC_subdiscadd.Percent));// percent
        memcpy(ApplVar.FlowBuff.CDC_subdiscadd.FAmt, ApplVar.Amt.Value, sizeof(ApplVar.FlowBuff.CDC_subdiscadd.FAmt));
        Length = sizeof(ApplVar.FlowBuff.CDC_subdiscadd);
        break;
    case DIRECTLOG:
        if (!TESTBIT(ApplVar.Disc.Options,BIT3))
            ApplVar.FlowBuff.CDC_direct.FunN |= 0x80;
        if (ApplVar.FVoid)
            ApplVar.FlowBuff.CDC_direct.FunN ^= 0xc0;
        memcpy(ApplVar.FlowBuff.CDC_direct.FAmt, ApplVar.Amt.Value, sizeof(ApplVar.FlowBuff.CDC_direct.FAmt));
        memcpy(ApplVar.FlowBuff.CDC_direct.ArtN, ApplVar.Plu.Random, sizeof(ApplVar.Plu.Random));
        Length = sizeof(ApplVar.FlowBuff.CDC_direct);
        break;
    case SUBDIRECTLOG:
        if (!TESTBIT(ApplVar.Disc.Options,BIT3))
            ApplVar.FlowBuff.CDC_subdirect.FunN |= 0x80;
        if (ApplVar.FVoid)
            ApplVar.FlowBuff.CDC_subdirect.FunN ^= 0xc0;
        memcpy(ApplVar.FlowBuff.CDC_subdirect.FAmt, ApplVar.Amt.Value, sizeof(ApplVar.FlowBuff.CDC_subdirect.FAmt));
        Length = sizeof(ApplVar.FlowBuff.CDC_subdirect);
        break;
    case REGISLOG:
        ApplVar.FlowBuff.CDC_regis.EcrNumber = ((WORD)LOCATION*256)+REGISTER;//ccr2014-11-14
        ApplVar.FlowBuff.CDC_regis.OperNo = (BYTE)ApplVar.ClerkNumber;
        ApplVar.FlowBuff.CDC_regis.SalesPer = (BYTE)ApplVar.SalPerNumber;

        //ccr2016-09-06>>>>>>>>>>
		sBCD = ZERO;
		memcpy(sBCD.Value, ApplVar.ReceiptNumber, 3);
		if (ApplVar.FPb && TESTBIT(PBINFO, BIT4))
            Add(&sBCD, (BCD*)&ONE);
        memcpy(ApplVar.FlowBuff.CDC_regis.ReceiptNum, sBCD.Value, sizeof(ApplVar.FlowBuff.CDC_regis.ReceiptNum));
        //ccr2016-09-06<<<<<<<<<<
        GetTimeDate(&sDate);
        ApplVar.FlowBuff.CDC_regis.FDay = sDate.day;
        ApplVar.FlowBuff.CDC_regis.FMonth = sDate.month;
        ApplVar.FlowBuff.CDC_regis.FYear =  (BYTE)sDate.year;
        ApplVar.FlowBuff.CDC_regis.FHour = sDate.hour;
        ApplVar.FlowBuff.CDC_regis.FMinute = sDate.min;
        ApplVar.FlowBuff.CDC_regis.FSecond = sDate.sec;
        Length = sizeof(ApplVar.FlowBuff.CDC_regis);
        break;
    case SUBTOTALLOG:
        if ((ApplVar.SubTotal.Sign & 0x80) == 0x80)
            ApplVar.FlowBuff.CDC_subtotal.FunN |= 0x80;
        memcpy(ApplVar.FlowBuff.CDC_subtotal.ReceiptNum, ApplVar.ReceiptNumber, sizeof(ApplVar.FlowBuff.CDC_subtotal.ReceiptNum));
        memcpy(ApplVar.FlowBuff.CDC_subtotal.FAmt, ApplVar.SubTotal.Value, sizeof(ApplVar.FlowBuff.CDC_subtotal.FAmt));
        GetTimeDate(&sDate);
        ApplVar.FlowBuff.CDC_subtotal.FDay = sDate.day;
        ApplVar.FlowBuff.CDC_subtotal.FMonth = sDate.month;
        ApplVar.FlowBuff.CDC_subtotal.FYear = (BYTE)sDate.year;
        ApplVar.FlowBuff.CDC_subtotal.FHour = sDate.hour;
        ApplVar.FlowBuff.CDC_subtotal.FMinute = sDate.min;
        Length = sizeof(ApplVar.FlowBuff.CDC_subtotal);
        break;
    case PRICELISTLOG:
        ApplVar.FlowBuff.CDC_pricelist.PListNo = ApplVar.PluPriceLevel+1;
        Length = sizeof(ApplVar.FlowBuff.CDC_pricelist);
        break;
    case TVOIDLOG:
        memcpy(ApplVar.FlowBuff.CDC_Void.FAmt, ApplVar.SubTotal.Value, sizeof(ApplVar.FlowBuff.CDC_Void.FAmt));
        GetTimeDate(&sDate);
        ApplVar.FlowBuff.CDC_Void.FDay = sDate.day;
        ApplVar.FlowBuff.CDC_Void.FMonth = sDate.month;
        ApplVar.FlowBuff.CDC_Void.FYear = (BYTE)sDate.year;
        ApplVar.FlowBuff.CDC_Void.FHour = sDate.hour;
        ApplVar.FlowBuff.CDC_Void.FMinute = sDate.min;
        Length = sizeof(ApplVar.FlowBuff.CDC_Void);
        break;
    case PBCLOSELOG:
        ApplVar.FlowBuff.CDC_PbClose.PBNo = ApplVar.PbNumber;
        memcpy(ApplVar.FlowBuff.CDC_PbClose.FAmt, ApplVar.PB.Amt.Value, sizeof(ApplVar.FlowBuff.CDC_PbClose.FAmt));
        GetTimeDate(&sDate);
        ApplVar.FlowBuff.CDC_PbClose.FDay = sDate.day;
        ApplVar.FlowBuff.CDC_PbClose.FMonth = sDate.month;
        ApplVar.FlowBuff.CDC_PbClose.FYear = (BYTE)sDate.year;
        ApplVar.FlowBuff.CDC_PbClose.FHour = sDate.hour;
        ApplVar.FlowBuff.CDC_PbClose.FMinute = sDate.min;
        Length = sizeof(ApplVar.FlowBuff.CDC_PbClose);
        break;
    case PBOPENLOG:
        ApplVar.FlowBuff.CDC_PbOpen.PBNo = ApplVar.NumberEntry;
        GetTimeDate(&sDate);
        ApplVar.FlowBuff.CDC_PbOpen.FDay = sDate.day;
        ApplVar.FlowBuff.CDC_PbOpen.FMonth = sDate.month;
        ApplVar.FlowBuff.CDC_PbOpen.FYear = (BYTE)sDate.year;
        ApplVar.FlowBuff.CDC_PbOpen.FHour = sDate.hour;
        ApplVar.FlowBuff.CDC_PbOpen.FMinute = sDate.min;
        Length = sizeof(ApplVar.FlowBuff.CDC_PbOpen);
        break;
    case TRTABLELOG:
        ApplVar.FlowBuff.CDC_PbTt.PBFNo = ApplVar.PbNumber;
        ApplVar.FlowBuff.CDC_PbTt.PBTNo = ApplVar.NumberEntry;
        memcpy(ApplVar.FlowBuff.CDC_PbTt.FAmt, ApplVar.Amt.Value, sizeof(ApplVar.FlowBuff.CDC_PbTt.FAmt));
        GetTimeDate(&sDate);
        ApplVar.FlowBuff.CDC_PbTt.FDay = sDate.day;
        ApplVar.FlowBuff.CDC_PbTt.FMonth = sDate.month;
        ApplVar.FlowBuff.CDC_PbTt.FYear = (BYTE)sDate.year;
        ApplVar.FlowBuff.CDC_PbTt.FHour = sDate.hour;
        ApplVar.FlowBuff.CDC_PbTt.FMinute = sDate.min;
        Length = sizeof(ApplVar.FlowBuff.CDC_PbTt);
        break;
#if (DD_CHIPC==1 || DD_ECRVIP==1)//ccr050316
/*		case INSERTICLOG://ccr chipcard>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            if (ApplVar.IC.CHIP_Flag>=0)
            {
                GetTimeDate(&sDate);
                ApplVar.FlowBuff.CDC_enteric.Serialum = ApplVar.IC.CardNo;
                ApplVar.FlowBuff.CDC_enteric.ICType = ApplVar.IC.CHIP_Flag;
                ApplVar.FlowBuff.CDC_enteric.ICFlag = ApplVar.IC.REC_INIT[CC_FTIPO];
                ApplVar.FlowBuff.CDC_enteric.FYear = (BYTE)sDate.year;
                ApplVar.FlowBuff.CDC_enteric.FMonth = sDate.month;						 //
                ApplVar.FlowBuff.CDC_enteric.FDay = sDate.day;							 // date
                memcpy(ApplVar.FlowBuff.CDC_enteric.Custname,&ApplVar.IC.REC_Customer[CC_CNOME],sizeof(ApplVar.FlowBuff.CDC_enteric.Custname));
                CWORD(ApplVar.FlowBuff.CDC_enteric.Custflag) = CWORD(ApplVar.IC.REC_Customer[CC_CFLAGS]);
                CWORD(ApplVar.FlowBuff.CDC_enteric.Discount) = CWORD(ApplVar.IC.REC_Customer[CC_CPERC]);

                icBCD2EcrBCD(&sBCD,&ApplVar.IC.REC_VALATT[CC_VAL],CC_PRGVEN-CC_VAL);
                memcpy(ApplVar.FlowBuff.CDC_enteric.Value,sBCD.Value,sizeof(ApplVar.FlowBuff.CDC_enteric.Value));
                icBCD2EcrBCD(&sBCD,&ApplVar.IC.REC_VALATT[CC_PUNTI],CC_FORE-CC_PUNTI);
                memcpy(ApplVar.FlowBuff.CDC_enteric.Point,sBCD.Value,sizeof(ApplVar.FlowBuff.CDC_enteric.Point));
                Length = sizeof(ApplVar.FlowBuff.CDC_enteric);
                break;
            }
            else
                return 0;
*/
    case REFRESHICLOG:
#if (DD_CHIPC==1)
        if (ApplVar.IC.CHIP_Flag>=0)
        {
            GetTimeDate(&sDate);

//ccr2015-05-21				if (ApplVar.FRefund==1)	//ccr 050608 �˻�����  //
            if (ApplVar.FlowBuff.CDC_refreshic.OpType == IC_OP_SUB || ApplVar.FlowBuff.CDC_refreshic.OpType == IC_OP_DECHARGE)//ccr2015-05-21
                ApplVar.FlowBuff.CDC_refreshic.FunN |= 0x80;
            if (ApplVar.FlowBuff.CDC_refreshic.OpType == IC_OP_DECHARGE)//ccr2015-05-22
                ApplVar.FlowBuff.CDC_refreshic.OpType = IC_OP_CHARGE;
            ApplVar.FlowBuff.CDC_refreshic.Serialum = ApplVar.IC.CardNo;

            ApplVar.FlowBuff.CDC_refreshic.ICType = ApplVar.IC.CHIP_Flag;
            ApplVar.FlowBuff.CDC_refreshic.ICFlag = ApplVar.IC.REC_INIT[CC_FTIPO];
            ApplVar.FlowBuff.CDC_refreshic.FYear = (BYTE)sDate.year;
            ApplVar.FlowBuff.CDC_refreshic.FMonth = sDate.month;                      //
            ApplVar.FlowBuff.CDC_refreshic.FDay = sDate.day;                          // date
            if (ApplVar.IC.REC_Customer[CC_CNOME])
                memcpy(ApplVar.FlowBuff.CDC_refreshic.Custname,&ApplVar.IC.REC_Customer[CC_CNOME],sizeof(ApplVar.FlowBuff.CDC_refreshic.Custname));
            else
                ULongtoASCL(ApplVar.FlowBuff.CDC_refreshic.Custname,ApplVar.IC.CardNo);

//				CWORD(ApplVar.FlowBuff.CDC_refreshic.Custflag) = CWORD(ApplVar.IC.REC_Customer[CC_CFLAGS]);
            ApplVar.FlowBuff.CDC_refreshic.FTime[0] = sDate.hour;//ccr2015-04-30
            ApplVar.FlowBuff.CDC_refreshic.FTime[1] = sDate.min;//ccr2015-04-30

            CWORD(ApplVar.FlowBuff.CDC_refreshic.Discount) = CWORD(ApplVar.IC.REC_Customer[CC_CPERC]);
            icBCD2EcrBCD(&sBCD,&ApplVar.IC.REC_VALATT[CC_VAL],CC_PRGVEN-CC_VAL);
            memcpy(ApplVar.FlowBuff.CDC_refreshic.CValue,sBCD.Value,sizeof(ApplVar.FlowBuff.CDC_refreshic.CValue));
            icBCD2EcrBCD(&sBCD,&ApplVar.IC.REC_VALATT[CC_PUNTI],CC_FORE-CC_PUNTI);
            memcpy(ApplVar.FlowBuff.CDC_refreshic.CPoint,sBCD.Value,sizeof(ApplVar.FlowBuff.CDC_refreshic.CPoint));
            Length = sizeof(ApplVar.FlowBuff.CDC_refreshic);
            break;
        }
#else
        if (0)
        {
        }
#endif
#if (DD_ECRVIP==1)
        else if (TESTBIT(ECRVIP.ECRVIPState,VIP_LOGIN))
        {//ΪECRVIP�Ƶ�
            GetTimeDate(&sDate);

            //��5���ֽڱ����������ʽ�Ļ�Ա��
            memset(sBCD.Value,0,BCDLEN);
            memcpy(sBCD.Value,ECRVIP.VipFix.VipTEL,sizeof(ECRVIP.VipFix.VipTEL));
            //ICType�����λ����,Serialum��λ4�ֽڳ�����
            ApplVar.FlowBuff.CDC_refreshic.ICType = BCDtoDEC(sBCD.Value[5])*10+(sBCD.Value[4]>>4);
            CWORD(sBCD.Value[4]) &= 0x000f;CWORD(sBCD.Value[6])=0;
            BCDValueToULong(sBCD.Value,&uLong);
            ApplVar.FlowBuff.CDC_refreshic.Serialum = uLong;

            memcpy(ApplVar.FlowBuff.CDC_refreshic.Custname,ECRVIP.VipFix.VipName,sizeof(ECRVIP.VipFix.VipName));

            ApplVar.FlowBuff.CDC_refreshic.ICFlag = 'V';
            ApplVar.FlowBuff.CDC_refreshic.FYear = (BYTE)sDate.year;
            ApplVar.FlowBuff.CDC_refreshic.FMonth = sDate.month;                      //
            ApplVar.FlowBuff.CDC_refreshic.FDay = sDate.day;                          // date

            ApplVar.FlowBuff.CDC_refreshic.FTime[0] = sDate.hour;//ccr2015-04-30
            ApplVar.FlowBuff.CDC_refreshic.FTime[1] = sDate.min;//ccr2015-04-30

//            i = ECRVIP.ECRVIPNumber & (ECRVIPMAX/2-1);
            Length = sizeof(ApplVar.FlowBuff.CDC_refreshic);
            break;

        }
#endif
        else
            return 0;//ccr chipcard<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif
#if defined(CASE_INDIA)
    case EDITPLULOG:
        GetTimeDate(&sDate);
        ApplVar.FlowBuff.CDC_EditPlu.FunN=EDITPLULOG;
        ApplVar.FlowBuff.CDC_EditPlu.FDay = sDate.day;
        ApplVar.FlowBuff.CDC_EditPlu.FMonth = sDate.month;
        ApplVar.FlowBuff.CDC_EditPlu.FYear = (BYTE)sDate.year;
        ApplVar.FlowBuff.CDC_EditPlu.FHour = sDate.hour;
        ApplVar.FlowBuff.CDC_EditPlu.FMinute = sDate.min;
        Length = sizeof(ApplVar.FlowBuff.CDC_EditPlu);
        break;
    case EDITDEPTLOG:
        GetTimeDate(&sDate);
        ApplVar.FlowBuff.CDC_EditDept.FunN=EDITDEPTLOG;
        ApplVar.FlowBuff.CDC_EditDept.FDay = sDate.day;
        ApplVar.FlowBuff.CDC_EditDept.FMonth = sDate.month;
        ApplVar.FlowBuff.CDC_EditDept.FYear = (BYTE)sDate.year;
        ApplVar.FlowBuff.CDC_EditDept.FHour = sDate.hour;
        ApplVar.FlowBuff.CDC_EditDept.FMinute = sDate.min;
        Length = sizeof(ApplVar.FlowBuff.CDC_EditDept);
        break;
#endif
    case SLIPENDLOG:
    default:
        return 0;
    }
#if (FLOW_IN_EXTRAM)
    i = 0;
    while (CheckLogBuff()<Length && i<3) i++;
    if (i<3)
#else
    CheckLogBuff();//ʹ��flashʱ�����Զ������洢�����ͷ�64K
#endif
    {
        WriteToLogRam(ApplVar.FlowHeader.NextNP,(char *)&ApplVar.FlowBuff,Length);
        ApplVar.FlowHeader.NextNP = ApplVar.FlowHeader.NextNP + Length;
        ADJLOGADDR(ApplVar.FlowHeader.NextNP);

#if (PC_EMUKEY==1)// && PCREMOTE==0)
        if (cmd==ENDLOG && COMPUTER)
        {//�����վݺź��վݵĴ洢������ַ
            sBCD=ZERO;
            memcpy(sBCD.Value,ApplVar.ReceiptNumber,RECNUM);
            SendComm(COMPUTER_1,'L');SendALong(ApplVar.FlowHeader.NextNP);
					  SendComm(COMPUTER_1,'-');SendABCD(&sBCD);SendComm(COMPUTER_1,'\n');
            //xprintf("%06XL\n",ApplVar.FlowHeader.NextNP);
        }
#endif

//		Calcu_Checksum();
    }
    memset((BYTE *)&ApplVar.FlowBuff,0,Length);
    return 1;
}

//�����Flash�ռ������ˮ,��64KΪ�鵥λ
void Init_Flow()
{
#if (FLOW_IN_EXTRAM==1)
    //��ˮ���ݴ�����տ�������ļ�β��ʣ��ռ�
    ApplVar.FlowHeader.FromAddr = ApplVar.AP.StartAddress[AddrEndP]+8;
    ApplVar.FlowHeader.EndAddr = ApplVar.SIZE_EXTRAM;

    if (ApplVar.FlowHeader.EndAddr <= ApplVar.FlowHeader.FromAddr
        || (ApplVar.FlowHeader.EndAddr-ApplVar.FlowHeader.FromAddr)<4*LOGALARMON)
    {//��ˮ�ռ�̫С,�޷��洢��ˮ����
        ApplVar.FlowHeader.FromAddr = 0;
        ApplVar.FlowHeader.EndAddr = 0;
        ApplVar.FlowHeader.ReadP = 0;
        ApplVar.FlowHeader.NextNP = 0;
        ApplVar.FlowHeader.HeadP = 0;
        ApplVar.FlowHeader.MAXNUMB = 0;
    } else
    {
        ApplVar.FlowHeader.ReadP =  ApplVar.FlowHeader.FromAddr;
        ApplVar.FlowHeader.NextNP = ApplVar.FlowHeader.FromAddr;
        ApplVar.FlowHeader.HeadP =  ApplVar.FlowHeader.FromAddr;
        ApplVar.FlowHeader.MAXNUMB = ApplVar.FlowHeader.EndAddr - ApplVar.FlowHeader.FromAddr+1;
    }

#else//��ˮ���ݴ����Flash�е�ָ������
    if (FLASH_LOG_BLOCKS>0)
    {
#if (FLASH_LOG_BLOCKFr==0 && FLASH_LOG_BLOCKS>1)//ccr2016-11-28
        bFlashMBlockErase(FLASH_LOG_BLOCKFr,4);//����ʼ��ַ��ʼ����4��(64k)
#else
        bFlashMBlockErase(FLASH_LOG_BLOCKFr,1);
#endif
        //��ˮ���ݴ����ָ����ַ����
        ApplVar.FlowHeader.FromAddr = FLASH_LOG_ADDR;
        ApplVar.FlowHeader.EndAddr = FLASH_LOG_ADDR+FLASH_LOG_SIZE;
        ApplVar.FlowHeader.ReadP =  FLASH_LOG_ADDR;
        ApplVar.FlowHeader.NextNP =     FLASH_LOG_ADDR;
        ApplVar.FlowHeader.HeadP =  FLASH_LOG_ADDR;
        ApplVar.FlowHeader.MAXNUMB = FLASH_LOG_SIZE;
    }
    else
    {
        ApplVar.FlowHeader.FromAddr = 0;
        ApplVar.FlowHeader.EndAddr = 0;
        ApplVar.FlowHeader.ReadP = 0;
        ApplVar.FlowHeader.NextNP = 0;
        ApplVar.FlowHeader.HeadP = 0;
        ApplVar.FlowHeader.MAXNUMB = 0;
    }
#endif
    ApplVar.FlowHeader.OverCount = 0;

    ApplVar.GCouter = 0;
    memset((BYTE *)&ApplVar.FlowBuff,0,sizeof(ApplVar.FlowBuff));
    memset((BYTE *)&ApplVar.CollectGiven,0,sizeof(ApplVar.CollectGiven));
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

BYTE PrintFlowQtyAmt(BCD *qty,CONSTCHAR *str,BCD *amt)
{
    BYTE rlen;

    if  (CDC_regis_cp.FunN)
    {//��ӡʱ����վݺ�
        DispDateRecNo(false);//sFunc!=TENDLOG);
        CDC_regis_cp.FunN = 0;
    }

    if (amt)
    {
        if (qty)
        {
            rlen = strlen(str);
            while (*(str+rlen -1)==' ' && rlen)
                rlen--;

            if ((rlen+BCDWidth(qty))>13+(pSHIFTx>>1))
            {
                PrintRJ(str);
                MemSet(SysBuf, sizeof(SysBuf), ' ');
                FormatAmt(SysBuf +PRTLEN - 1, amt);
                FormatQty(SysBuf + 6+pSHIFTx, qty);
                PrintRJ(SysBuf);
            } else
                PrintRJ(FormatStrQtyPriAmt(str, qty, 0, amt, PRTLEN));
        } else
            PrintRJ(FormatAmtStr(str, amt, PRTLEN));
    } else if (qty)
        PrintRJ(FormatQtyStr(str, qty, PRTLEN));
    else
        PrintRJ(str);
    return 0;
}
//-----------------------------------------------------------------------------
void DispNULL()
{
}
//-----------------------------------------------------------------------------
void DispPoRa()
{
    BCD sAmt;

#if defined(TEND_PREFIX)//ccr2016-08-08
    Prefix1 = PREFIX_1;
    Prefix2 = PREFIX_2;
#endif

    ApplVar.PoRaNumber = ApplVar.FlowBuff.CDC_PoRa.PoRaN-1;
    ReadPoRa();

    ApplVar.PoRa.Name[sizeof(ApplVar.PoRa.Name)-1] = 0;

    sAmt = ZERO;

    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_PoRa.FAmt,sizeof(ApplVar.FlowBuff.CDC_PoRa.FAmt));

    SETDECIMAL(sAmt.Sign, 2);
    PrintFlowQtyAmt(0,ApplVar.PoRa.Name,&sAmt);
}
//-----------------------------------------------------------------------------
void DispDept()
{
    BCD sQty,sAmt;
    short i;

    ApplVar.DeptNumber = ApplVar.FlowBuff.CDC_dpt.DeptN-1;

    //ccr2016-03-09>>��ѯָ����Ʒ������>>>>>
    if (LogDefine.FuncCode && LogDefine.FuncCode!=ApplVar.DeptNumber+DEPT+1)
        return;
    //ccr2016-03-09<<<<<<<

    ReadDept();

    sQty = ZERO;
    sAmt = ZERO;

    memcpy(sQty.Value,(char *)&ApplVar.FlowBuff.CDC_dpt.FQty,sizeof(ApplVar.FlowBuff.CDC_dpt.FQty));
    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_dpt.FAmt,sizeof(ApplVar.FlowBuff.CDC_dpt.FAmt));

    SETDECIMAL(sQty.Sign,3);
    for (i=0;i<3;i++)
    {
        if (!(sQty.Value[0] & 0x0f))
        {
            BcdDiv10(&sQty);
            sQty.Sign--;
        } else
            break;
    }
    SETDECIMAL(sAmt.Sign, 2);

    if (ApplVar.FlowBuff.CDC_dpt.FunN & 0x40)
    {
        RJPrint(CMDP_DR,Msg[QUXIAO].str);
        ApplVar.FlowBuff.CDC_dpt.FunN |= 0x80;
    } else if (ApplVar.FlowBuff.CDC_art.FunN & 0x80)
        RJPrint(CMDP_DR,Msg[TUIHUO].str);
    if (ApplVar.FlowBuff.CDC_dpt.FunN & 0x80)
    {
        sQty.Sign |= 0x80;
        sAmt.Sign |= 0x80;
    }
    if (LogDefine.LogType)
    {
        PrintFlowQtyAmt(0,ApplVar.Dept.Name,&sAmt);
        Add(&ApplVar.SubTotal,&sAmt);//ccr2015-06-15
    }
    else
        PrintFlowQtyAmt(&sQty,ApplVar.Dept.Name,&sAmt);
//	EcrLogForm->QtyTotal = EcrLogForm->QtyTotal + sQty;
//	EcrLogForm->AmtTotal = EcrLogForm->AmtTotal + sAmt;
}
//-----------------------------------------------------------------------------
void DispPlu()
{
    BCD sQty,sAmt;
    short i;

    if (ApplVar.AP.Plu.RandomSize)
    {
        ApplVar.PluNumber = GetPluNumber(1, ApplVar.FlowBuff.CDC_art.ArtN);
        if (ApplVar.PluNumber)
            ApplVar.PluNumber--;
    } else
    {
        ApplVar.PluNumber = Bcd2Long((char *)&ApplVar.FlowBuff.CDC_art.ArtN,sizeof(ApplVar.FlowBuff.CDC_art.ArtN));
    }

    //ccr2016-03-09>>��ѯָ����Ʒ������>>>>>
    if (LogDefine.FuncCode && LogDefine.FuncCode!=ApplVar.PluNumber+PLU1+1)
        return;
    //ccr2016-03-09<<<<<<<
    ReadPlu();

    sQty = ZERO;
    sAmt = ZERO;

    memcpy(sQty.Value,(char *)&ApplVar.FlowBuff.CDC_art.FQty,sizeof(ApplVar.FlowBuff.CDC_art.FQty));
    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_art.FAmt,sizeof(ApplVar.FlowBuff.CDC_art.FAmt));

    SETDECIMAL(sQty.Sign, 3);
    for (i=0;i<3;i++)
    {
        if (!(sQty.Value[0] & 0x0f))
        {
            BcdDiv10(&sQty);
            sQty.Sign--;
        } else
            break;
    }
    SETDECIMAL(sAmt.Sign , 2);


    if (ApplVar.FlowBuff.CDC_art.FunN & 0x40)
    {
        RJPrint(CMDP_DR,Msg[QUXIAO].str);
        ApplVar.FlowBuff.CDC_art.FunN |= 0x80;
    } else if (ApplVar.FlowBuff.CDC_art.FunN & 0x80)
        RJPrint(CMDP_DR,Msg[TUIHUO].str);
    if (ApplVar.FlowBuff.CDC_art.FunN & 0x80)
    {
        sQty.Sign |= 0x80;
        sAmt.Sign |= 0x80;
    }
    if (LogDefine.LogType)
    {
        PrintFlowQtyAmt(0,ApplVar.Plu.Name,&sAmt);
        Add(&ApplVar.SubTotal,&sAmt);//ccr2015-06-15
    }
    else
        PrintFlowQtyAmt(&sQty,ApplVar.Plu.Name,&sAmt);

//	EcrLogForm->QtyTotal = EcrLogForm->QtyTotal + sQty;
//	EcrLogForm->AmtTotal = EcrLogForm->AmtTotal + sAmt;

}
//-----------------------------------------------------------------------------
void DispTAX()
{
    BCD sTax,sAmt,sRate;
    short len;

    ApplVar.TaxNumber = ApplVar.FlowBuff.CDC_Tax.TaxID-1;
    ReadTax();

    sTax = ZERO;
    sAmt = ZERO;
    sRate = ZERO;

    memcpy(sTax.Value,(char *)&ApplVar.FlowBuff.CDC_Tax.FTax,sizeof(ApplVar.FlowBuff.CDC_Tax.FTax));
    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_Tax.FAmt,sizeof(ApplVar.FlowBuff.CDC_Tax.FAmt));
    memcpy(sRate.Value,(char *)&ApplVar.FlowBuff.CDC_Tax.FRate,sizeof(ApplVar.FlowBuff.CDC_Tax.FRate));

    SETDECIMAL(sAmt.Sign, 2);
    SETDECIMAL(sTax.Sign, 2);
    SETDECIMAL(sRate.Sign, 2);


    if (TESTBIT(ApplVar.Tax.Options, BIT4))    /* print taxable? */
    {
        strcpy(ProgLineMes,ApplVar.Tax.Name);
        len = strlen(ProgLineMes);
        ProgLineMes[len++] = ' ';
        strcpy(ProgLineMes+len,Msg[XSHOUE].str);
        PrintAmt(ProgLineMes, &sAmt);/* ��ӡ˰�ֵ����۾��� */
    }
    memset(ProgLineMes, ' ', sizeof(ProgLineMes));
    CopyFrStr(ProgLineMes,ApplVar.Tax.Name);
    FormatQty(ProgLineMes+16,&sRate);//cr070424
    ProgLineMes[17] = '%';      //ProgLineMes[13] = '%';
    ProgLineMes[18] = 0;        //ccr090113
    PrintAmt(ProgLineMes,&sTax);/* ��ӡ��˰��� */
}
//-----------------------------------------------------------------------------
void  DispEnd()
{
    BCD sAmt;

#if defined(TEND_PREFIX)//ccr2016-08-08
    Prefix1 = PREFIX_1;
    Prefix2 = PREFIX_2;
#endif

    sAmt = ZERO;
    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_end.FAmt,sizeof(ApplVar.FlowBuff.CDC_end.FAmt));

//20130709�ָ���û�ж������壬�ͻ�����Ҳ�˷�ֽ	PrintLine('-');
    PrintFlowQtyAmt(0,Msg[YINGFU].str,&sAmt);
//	EcrLogForm->AmtTotal = EcrLogForm->AmtTotal + sAmt;
}
//-----------------------------------------------------------------------------
void  DispNonAdd()
{//ccr2016-05-31>>>>>>>>>>>>>>>>
    UINT64 Long64;
    char sTmpBuf[PRTLEN+1];

    Long64=0;

    memset(sTmpBuf,' ',PRTLEN);
    memcpy((char*)&Long64,ApplVar.FlowBuff.CDC_noadd.Num,sizeof(ApplVar.FlowBuff.CDC_noadd.Num));
    ULong64toASC(sTmpBuf+PRTLEN-1,Long64);
    CopyFrStr(sTmpBuf,Msg[HAOMA].str);
    sTmpBuf[PRTLEN]=0;
    RJPrint(0,sTmpBuf);//Msg[DKQXIANG].str);
    //ccr2016-05-31<<<<<<<<<<<<<<<<<<<<<<<
}
//-----------------------------------------------------------------------------
void  DispOperator()
{
    char sTmpBuf[20];
    short i = ApplVar.ClerkNumber;

    memset(sTmpBuf,' ',sizeof(sTmpBuf));
    ApplVar.ClerkNumber = ApplVar.FlowBuff.CDC_oper.OperN;
    ReadClerk();
    ApplVar.Clerk.Name[sizeof(ApplVar.Clerk.Name)-1] = 0;
    CopyFrStr(sTmpBuf,Msg[SHKYUANF].str);
    CopyFrStr(sTmpBuf+8,ApplVar.Clerk.Name);
    RJPrint(0,sTmpBuf);

    ApplVar.ClerkNumber = i;
}
//-----------------------------------------------------------------------------
void  DispTender()
{
    BCD sAmt;
    short j;

#if defined(TEND_PREFIX)//ccr2016-08-08
    Prefix1 = PREFIX_1;
    Prefix2 = PREFIX_2;
#endif

    for (j=0;j<ApplVar.FlowBuff.CDC_given.Counter;j++)
    {
        ApplVar.TendNumber = ApplVar.FlowBuff.CDC_given.GivenData[j].FTType-1;
        if (LogDefine.FuncCode==0 || LogDefine.FuncCode==ApplVar.TendNumber+TEND+1)
        {
            ReadTender();
            ApplVar.Tend.Name[sizeof(ApplVar.Tend.Name)-1] = 0;
            sAmt = ZERO;
            memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_given.GivenData[j].FAmt,sizeof(ApplVar.FlowBuff.CDC_given.GivenData[j].FAmt));
            PrintFlowQtyAmt(0,ApplVar.Tend.Name,&sAmt);
            if (LogDefine.LogType)
                Add(&ApplVar.SubTotal,&sAmt);//ccr2015-06-15
        }
    }
    if (LogDefine.LogType==0)
        PrintLine('*');
}
//-----------------------------------------------------------------------------


void  DispModeLock()
{
}
//-----------------------------------------------------------------------------
void  DispPercentDisc()
{
    BCD sQty,sAmt;
    short i;
    char sTmpBuf[40];

    sQty = sAmt = ZERO;
    memcpy(sQty.Value,(char *)&ApplVar.FlowBuff.CDC_discadd.Percent,sizeof(ApplVar.FlowBuff.CDC_discadd.Percent));
    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_discadd.FAmt,sizeof(ApplVar.FlowBuff.CDC_discadd.FAmt));

    if (ApplVar.FlowBuff.CDC_discadd.FunN & 0x80)
    {
        sQty.Sign |= 0x80;
        sAmt.Sign |= 0x80;
        i = PZHEKOU;
//		EcrLogForm->sDiscPerTotal = EcrLogForm->sDiscPerTotal + sAmt;
    } else
    {
        i = PJIACHEN;
//		EcrLogForm->aDiscPerTotal = EcrLogForm->aDiscPerTotal + sAmt;
    }
    memset(sTmpBuf,' ',sizeof(sTmpBuf));
    sQty.Sign|=0x02;
    strcpy(sTmpBuf,FormatQtyStr(Msg[i].str,&sQty,15));

    i = strlen(sTmpBuf)-1; //ccr2016-11-07
    sTmpBuf[i++] = '%';
    sTmpBuf[i] = 0;
    PrintFlowQtyAmt(0,sTmpBuf,&sAmt);
    if (LogDefine.LogType)
        Add(&ApplVar.SubTotal,&sAmt);//ccr2015-06-15

//	EcrLogForm->QtyTotal = EcrLogForm->QtyTotal + sQty;
//	EcrLogForm->AmtTotal = EcrLogForm->AmtTotal + sAmt;
}
//-----------------------------------------------------------------------------
void  DispSubTotalDisc()
{
    BCD sQty,sAmt;
    short i;
    char sTmpBuf[20];

    sQty = sAmt = ZERO;
    memcpy(sQty.Value,(char *)&ApplVar.FlowBuff.CDC_subdiscadd.Percent,sizeof(ApplVar.FlowBuff.CDC_subdiscadd.Percent));
    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_subdiscadd.FAmt,sizeof(ApplVar.FlowBuff.CDC_subdiscadd.FAmt));

    memset(sTmpBuf,' ',sizeof(sTmpBuf));
    strncpy(sTmpBuf,Msg[XIAOJI].str,sizeof(sTmpBuf));

    if (ApplVar.FlowBuff.CDC_subdiscadd.FunN & 0x80)
    {
        strncpy(sTmpBuf+4,Msg[PZHEKOU].str,sizeof(sTmpBuf)-4);
        sQty.Sign |= 0x80;
        sAmt.Sign |= 0x80;
//		EcrLogForm->sDiscPerTotalS = EcrLogForm->sDiscPerTotalS + sAmt;
    } else
    {
        strncpy(sTmpBuf+4,Msg[PJIACHEN].str,sizeof(sTmpBuf)-4);
//		EcrLogForm->aDiscPerTotalS = EcrLogForm->aDiscPerTotalS + sAmt;
    }
    sTmpBuf[sizeof(sTmpBuf)-4]=0;
    sQty.Sign|=0x02;
    strcpy(sTmpBuf,FormatQtyStr(sTmpBuf,&sQty,15));

    i = strlen(sTmpBuf)-1;
    sTmpBuf[i++] = '%';
    sTmpBuf[i] = 0;
    PrintFlowQtyAmt(0,sTmpBuf,&sAmt);
    if (LogDefine.LogType)
        Add(&ApplVar.SubTotal,&sAmt);//ccr2015-06-15
//	EcrLogForm->QtyTotal = EcrLogForm->QtyTotal + sQty;
//	EcrLogForm->AmtTotal = EcrLogForm->AmtTotal + sAmt;
}
//-----------------------------------------------------------------------------
void  DispDirectDisc()
{
    BCD sAmt;
    char sTmpBuf[20];

    sAmt = ZERO;
    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_direct.FAmt,sizeof(ApplVar.FlowBuff.CDC_direct.FAmt));

    memset(sTmpBuf,' ',sizeof(sTmpBuf));
    strncpy(sTmpBuf,Msg[JINE].str,sizeof(sTmpBuf));

    if (ApplVar.FlowBuff.CDC_subdiscadd.FunN & 0x80)
    {
        strncpy(sTmpBuf+4,Msg[PZHEKOU].str+1,sizeof(sTmpBuf)-4);
        sAmt.Sign |= 0x80;
//		EcrLogForm->sDiscDirTotal = EcrLogForm->sDiscDirTotal + sAmt;
    } else
    {
        strncpy(sTmpBuf+4,Msg[PJIACHEN].str+1,sizeof(sTmpBuf)-4);
//		EcrLogForm->aDiscDirTotal = EcrLogForm->aDiscDirTotal + sAmt;
    }
    sTmpBuf[sizeof(sTmpBuf)-4]=0;
    PrintFlowQtyAmt(0,sTmpBuf,&sAmt);
    if (LogDefine.LogType)
        Add(&ApplVar.SubTotal,&sAmt);//ccr2015-06-15
//	EcrLogForm->AmtTotal = EcrLogForm->AmtTotal + sAmt;
}
//-----------------------------------------------------------------------------
void  DispSubTotalDirDisc()
{
    BCD sAmt;
    char sTmpBuf[20];

    sAmt = ZERO;
    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_subdirect.FAmt,sizeof(ApplVar.FlowBuff.CDC_subdirect.FAmt));

    memset(sTmpBuf,' ',sizeof(sTmpBuf));
    strncpy(sTmpBuf,Msg[XIAOJI].str,sizeof(sTmpBuf));
    strncpy(sTmpBuf+4,Msg[JINE].str,sizeof(sTmpBuf)-4);

    if (ApplVar.FlowBuff.CDC_subdiscadd.FunN & 0x80)
    {
        strncpy(sTmpBuf+8,Msg[PZHEKOU].str+1,sizeof(sTmpBuf)-8);
        sAmt.Sign |= 0x80;
//		EcrLogForm->sDiscDirTotalS = EcrLogForm->sDiscDirTotalS + sAmt;
    } else
    {
        strncpy(sTmpBuf+8,Msg[PJIACHEN].str+1,sizeof(sTmpBuf)-8);
//		EcrLogForm->aDiscDirTotalS = EcrLogForm->aDiscDirTotalS + sAmt;
    }
    sTmpBuf[sizeof(sTmpBuf)-4]=0;
//	EcrLogForm->AmtTotal = EcrLogForm->AmtTotal + sAmt;
    PrintFlowQtyAmt(0,sTmpBuf,&sAmt);
    if (LogDefine.LogType)
        Add(&ApplVar.SubTotal,&sAmt);//ccr2015-06-15
}
//-----------------------------------------------------------------------------
void  DispNew()
{
    short i;
    BYTE cpClerk,cpSaler;

    cpClerk = ApplVar.ClerkNumber;
    cpSaler = ApplVar.SalPerNumber;

//	PrintLine('*');
    memset(SysBuf,' ',sizeof(SysBuf));
    i = 0;
    if (ApplVar.FlowBuff.CDC_regis.OperNo>0)
    {
        ApplVar.ClerkNumber = ApplVar.FlowBuff.CDC_regis.OperNo;
        ReadClerk();
        strcpy(SysBuf,Msg[SHKYUANF].str);
        strcpy(SysBuf+strlen(SysBuf),ApplVar.Clerk.Name);
        i = strlen(SysBuf);
    }
#if (salNumber)
    if (ApplVar.FlowBuff.CDC_regis.SalesPer>0)
    {
        ApplVar.SalPerNumber = ApplVar.FlowBuff.CDC_regis.SalesPer;
        ReadSalPer();
        strcpy(SysBuf+i,Msg[YYYUANF].str);
        strncpy(SysBuf+7+i,ApplVar.SalPer.Name,8);
        i = 1;
    }
#endif
    if (i)
    {
        RJPrint(0,SysBuf);
    }

    BCDDateTimeToStr(SysBuf,ApplVar.FlowBuff.CDC_regis.FYear,ApplVar.FlowBuff.CDC_regis.FMonth,ApplVar.FlowBuff.CDC_regis.FDay,
                     ApplVar.FlowBuff.CDC_regis.FHour,ApplVar.FlowBuff.CDC_regis.FMinute,ApplVar.FlowBuff.CDC_regis.FSecond);

    SysBuf[strlen(SysBuf)]=' ';

    SysBuf[25] = '#';
    HEXtoASC(SysBuf+26,ApplVar.FlowBuff.CDC_regis.ReceiptNum,RECEIPTLEN);
    RJPrint(0,SysBuf);
    PrintLine('.');
    RJPrint(0,Msg[TITLEQTYAMT].str);
//20130709�ָ���û�ж������壬�ͻ�����Ҳ�˷�ֽ	PrintLine('=');

    ApplVar.ClerkNumber = cpClerk;
    ApplVar.SalPerNumber = cpSaler;
}
//ccr2015-06-15>>>>>>>>>>>>>>>>>
/**
 * ��ӡʱ����վݺ�
 *
 * @author EutronSoftware (2016-03-08)
 *
 * @param line :=true,��ӡ�ָ���
 */
void  DispDateRecNo(BYTE line)
{
    char prnBuff[PRTLEN+1];
    if (line)
        PrintLine('.');

    memset(prnBuff,' ',PRTLEN);

#if 1
    sprintf(prnBuff,"20%02x%s%02x%s%02x%s %02x:%02x:%02x",CDC_regis_cp.FYear,Msg[NIAN].str,
                                                        CDC_regis_cp.FMonth,Msg[YUE].str,
                                                        CDC_regis_cp.FDay,Msg[RI].str,
                                                        CDC_regis_cp.FHour,CDC_regis_cp.FMinute,CDC_regis_cp.FSecond);
    prnBuff[strlen(prnBuff)]=' ';
#else
    prnBuff[0] = '2';prnBuff[1] = '0';
    HEXtoASC(prnBuff+2,&CDC_regis_cp.FYear,1);CopyFrStr(prnBuff+4,Msg[NIAN].str);
    HEXtoASC(prnBuff+6,&CDC_regis_cp.FMonth,1);CopyFrStr(prnBuff+8,Msg[YUE].str);
    HEXtoASC(prnBuff+10,&CDC_regis_cp.FDay,1);CopyFrStr(prnBuff+12,Msg[RI].str);

    HEXtoASC(prnBuff+14,&CDC_regis_cp.FHour,1);prnBuff[16] = ':';
    HEXtoASC(prnBuff+17,&CDC_regis_cp.FMinute,1);prnBuff[19] = ':';
    HEXtoASC(prnBuff+20,&CDC_regis_cp.FSecond,1);
#endif
    prnBuff[25] = '#';
    HEXtoASC(prnBuff+26,CDC_regis_cp.ReceiptNum,RECEIPTLEN);
    prnBuff[PRTLEN]=0;
    RJPrint(0,prnBuff);
}///ccr2015-06-15<<<<<<<<<<<<<<<<<<<<<<
//-----------------------------------------------------------------------------
void  DispSubTotals()
{
    BCD sAmt;

    sAmt = ZERO;
    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_subtotal.FAmt,sizeof(ApplVar.FlowBuff.CDC_subtotal.FAmt));
    PrintFlowQtyAmt(0,Msg[XIAOJI].str,&sAmt);
}
//-----------------------------------------------------------------------------
void  DispMessage()
{

}
//-----------------------------------------------------------------------------
void  DispRPEnd()
{
}
//-----------------------------------------------------------------------------
void  DispInsertIC()
{
}
//-----------------------------------------------------------------------------
void  DispRefreshIC()
{

    BCD sVal1;
    int i;
    int opType;
    UINT64 temp64;

//	PrintLine('*');
    memset(SysBuf,' ',PRTLEN);
    //����������
    SysBuf[0] = '2';SysBuf[1] = '0';
    HEXtoASC(SysBuf+2,&ApplVar.FlowBuff.CDC_refreshic.FYear,1);SysBuf[4]='-';
    HEXtoASC(SysBuf+5,&ApplVar.FlowBuff.CDC_refreshic.FMonth,1);SysBuf[7]='-';
    HEXtoASC(SysBuf+8,&ApplVar.FlowBuff.CDC_refreshic.FDay,1);

    HEXtoASC(SysBuf+11,&ApplVar.FlowBuff.CDC_refreshic.FTime[0],1);SysBuf[13] = ':';
    HEXtoASC(SysBuf+14,&ApplVar.FlowBuff.CDC_refreshic.FTime[1],1);
    //����������
    if (ApplVar.FlowBuff.CDC_refreshic.ICFlag=='V')
    {//ΪECRVIP��Ա,ֻ�л������ݺ������ܶ�
        SysBuf[PRTLEN]=0;
        RJPrint(0, SysBuf);
        memset(SysBuf,' ',PRTLEN);
        CopyFrStr(SysBuf, Msg[TMHYHAO].str);
        sprintf(SysBuf+16,"%3u%09lu",ApplVar.FlowBuff.CDC_refreshic.ICType,ApplVar.FlowBuff.CDC_refreshic.Serialum);
        RJPrint(0, SysBuf);
    }
    else
    {
        strcpy(SysBuf+17, Msg[ZHEKOUCA+ApplVar.FlowBuff.CDC_refreshic.ICType].str);
        i = strlen(SysBuf);
        //����
        SysBuf[i++] = '#';
        ULongtoASCL(SysBuf+i,ApplVar.FlowBuff.CDC_refreshic.Serialum);
        RJPrint(0, SysBuf);
    }

    opType = ApplVar.FlowBuff.CDC_refreshic.OpType;

#if defined(TEND_PREFIX)//ccr2016-08-08
    Prefix1 = PREFIX_1;
    Prefix2 = PREFIX_2;
#endif

    if (opType && opType<=IC_OP_DECHARGE)
    {
        sVal1 = ZERO;
        memcpy(sVal1.Value,ApplVar.FlowBuff.CDC_refreshic.RValue,sizeof(ApplVar.FlowBuff.CDC_refreshic.RValue));
        if (ApplVar.FlowBuff.CDC_refreshic.FunN & 0x80)
        {
            sVal1.Sign |= 0x80;
            if (opType==IC_OP_CHARGE)
                opType=IC_OP_DECHARGE;
        }
        FormatAmtStr(Msg[CLEARIC+opType-1].str, &sVal1, PRTLEN);
        RJPrint(0, SysBuf);

        sVal1 = ZERO;
        memcpy(sVal1.Value,ApplVar.FlowBuff.CDC_refreshic.CValue,sizeof(ApplVar.FlowBuff.CDC_refreshic.CValue));
        if (CheckNotZero(&sVal1))
        {
            FormatAmtStr(Msg[KNJE].str, &sVal1, PRTLEN);
            RJPrint(0, SysBuf);
        }
        sVal1 = ZERO;
        memcpy(sVal1.Value,ApplVar.FlowBuff.CDC_refreshic.CPoint,sizeof(ApplVar.FlowBuff.CDC_refreshic.CPoint));
        if (CheckNotZero(&sVal1))
            RJPrint(0, FormatQtyStr(Msg[VIPPOINTS].str, &sVal1, PRTLEN));

    }
    else if (opType>=IC_OP_ADDPOINT)
    {
        sVal1 = ZERO;
        memcpy(sVal1.Value,ApplVar.FlowBuff.CDC_refreshic.RValue,sizeof(ApplVar.FlowBuff.CDC_refreshic.RValue));
        if (ApplVar.FlowBuff.CDC_refreshic.FunN & 0x80)
        {
            sVal1.Sign |= 0x80;
            if (opType==IC_OP_CHARGE)
                opType=IC_OP_DECHARGE;
        }
        FormatAmtStr(Msg[XFJE].str, &sVal1, PRTLEN);
        RJPrint(0, SysBuf);
        sVal1 = ZERO;
        memcpy(sVal1.Value,ApplVar.FlowBuff.CDC_refreshic.CValue,sizeof(ApplVar.FlowBuff.CDC_refreshic.CValue));
        if (CheckNotZero(&sVal1))
        {
            FormatAmtStr((char*)cVIPTOTALA, &sVal1, PRTLEN);
            RJPrint(0, SysBuf);
            sVal1 = ZERO;
        }
        memcpy(sVal1.Value,ApplVar.FlowBuff.CDC_refreshic.RPoint,sizeof(ApplVar.FlowBuff.CDC_refreshic.RPoint));
        if (CheckNotZero(&sVal1))
        {
            RJPrint(0, FormatQtyStr(Msg[CLEARIC+opType-1].str, &sVal1, PRTLEN));
            sVal1 = ZERO;
        }
        memcpy(sVal1.Value,ApplVar.FlowBuff.CDC_refreshic.CPoint,sizeof(ApplVar.FlowBuff.CDC_refreshic.CPoint));
        if (CheckNotZero(&sVal1))
            RJPrint(0, FormatQtyStr(Msg[VIPPOINTS].str, &sVal1, PRTLEN));
    }


    PrintLine('.');
}
//-----------------------------------------------------------------------------
void  DispSetPrice()
{
}
//---------------------------------------------------------------------------

void DispEcrNum()
{
}
//---------------------------------------------------------------------------
void DispVoid()
{
    BCD sAmt;

    sAmt = ZERO;
    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_Void.FAmt,sizeof(ApplVar.FlowBuff.CDC_Void.FAmt));
    sAmt.Sign |= 0x80;
    PrintFlowQtyAmt(0,Msg[QXJYIXZHI].str,&sAmt);
//	EcrLogForm->AmtTotal = EcrLogForm->AmtTotal + sAmt;
}
//---------------------------------------------------------------------------
void DispPbClose()
{
    BCD sAmt;

    sAmt = ZERO;
    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_PbClose.FAmt,sizeof(ApplVar.FlowBuff.CDC_PbClose.FAmt));
//	EcrLogForm->AmtTotal = EcrLogForm->AmtTotal + sAmt;
    PrintFlowQtyAmt(0,Msg[KTZHJIE].str,&sAmt);
}
//---------------------------------------------------------------------------
void DispPbOpen()
{
    memset(SysBuf,' ',sizeof(SysBuf));
    CopyFrStr(SysBuf,Msg[KAITAI].str);
    CopyFrStr(SysBuf+6,Msg[ZUOHAO].str);
    WORDtoASC(SysBuf+15,ApplVar.FlowBuff.CDC_PbOpen.PBNo);
    RJPrint(0,SysBuf);
}
//---------------------------------------------------------------------------
void DispPbTransTo()
{
    BCD sAmt;

    char sTmpBuf[20];

    sAmt = ZERO;
    memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_PbTt.FAmt,sizeof(ApplVar.FlowBuff.CDC_PbTt.FAmt));

    CopyFrStr(sTmpBuf,Msg[ZUOHAO].str);
    WORDtoASC(sTmpBuf+6,ApplVar.FlowBuff.CDC_PbTt.PBFNo);

    CopyFrStr(sTmpBuf+7,Msg[ZHUANZHANG].str);

    CopyFrStr(sTmpBuf+11,Msg[ZUOHAO].str);
    WORDtoASC(sTmpBuf+17,ApplVar.FlowBuff.CDC_PbTt.PBTNo);
    sTmpBuf[18]=0;

    PrintFlowQtyAmt(0,sTmpBuf,&sAmt);

//	EcrLogForm->AmtTotal = EcrLogForm->AmtTotal + sAmt;
}

#if defined(CASE_INDIA)//ccr2016-06-03>>>>>>>
void DispPluData()         //�޸�PLU������־
{
    memset(SysBuf,' ',PRTLEN);
    //��������
    SysBuf[0] = '2';SysBuf[1] = '0';
    HEXtoASC(SysBuf+2,&ApplVar.FlowBuff.CDC_EditPlu.FYear,1);SysBuf[4]='-';
    HEXtoASC(SysBuf+5,&ApplVar.FlowBuff.CDC_EditPlu.FMonth,1);SysBuf[7]='-';
    HEXtoASC(SysBuf+8,&ApplVar.FlowBuff.CDC_EditPlu.FDay,1);
    HEXtoASC(SysBuf+11,&ApplVar.FlowBuff.CDC_EditPlu.FHour,1);SysBuf[13] = ':';
    HEXtoASC(SysBuf+14,&ApplVar.FlowBuff.CDC_EditPlu.FMinute,1);
    strcpy(SysBuf+18,MsgEDITPLU);
    RJPrint(0,SysBuf);
    memset(SysBuf,' ',PRTLEN);
    ApplVar.FlowBuff.CDC_EditPlu.Plu.Name[ApplVar.AP.Plu.CapSize]=0;
    if (ApplVar.AP.Plu.RandomSize)
    {
        HEXtoASC(SysBuf,ApplVar.FlowBuff.CDC_EditPlu.Plu.Random,ApplVar.AP.Plu.RandomSize);
        strcpy(SysBuf+14,ApplVar.FlowBuff.CDC_EditPlu.Plu.Name);
    }
    else
    {
        WORDtoASCL(SysBuf,ApplVar.FlowBuff.CDC_EditPlu.Code-PLU1);
        strcpy(SysBuf+8,ApplVar.FlowBuff.CDC_EditPlu.Plu.Name);
    }
    RJPrint(0,SysBuf);
}

void DispDeptData()         //�޸�Dept������־
{
    memset(SysBuf,' ',PRTLEN);
    //��������
    SysBuf[0] = '2';SysBuf[1] = '0';
    HEXtoASC(SysBuf+2,&ApplVar.FlowBuff.CDC_EditDept.FYear,1);SysBuf[4]='-';
    HEXtoASC(SysBuf+5,&ApplVar.FlowBuff.CDC_EditDept.FMonth,1);SysBuf[7]='-';
    HEXtoASC(SysBuf+8,&ApplVar.FlowBuff.CDC_EditDept.FDay,1);
    HEXtoASC(SysBuf+11,&ApplVar.FlowBuff.CDC_EditDept.FHour,1);SysBuf[13] = ':';
    HEXtoASC(SysBuf+14,&ApplVar.FlowBuff.CDC_EditDept.FMinute,1);
    strcpy(SysBuf+18,MsgEDITDEPT);
    RJPrint(0,SysBuf);
    memset(SysBuf,' ',PRTLEN);
    ApplVar.FlowBuff.CDC_EditDept.Dept.Name[ApplVar.AP.Dept.CapSize]=0;
    WORDtoASCL(SysBuf,ApplVar.FlowBuff.CDC_EditDept.Code-DEPT);
    strcpy(SysBuf+8,ApplVar.FlowBuff.CDC_EditDept.Dept.Name);
    RJPrint(0,SysBuf);
}
#endif//ccr2016-06-03<<<<<<


/*********************************************************
 * ��ѯ��ӡ��ˮ����
 *
 * @author EutronSoftware (2016-03-08)
 *
 * @param logType :ָ����ˮ����(DEPTLOG..TAXLOG);=0ʱ,����������.
 */
void LoadReceipLog()
{
    WORD sFunc,sLast;
    UnLong sRecno,sSaveP,sReadP;
    UnLong sDateLog;
    char   sTitle=false, sActLog,logFound=false;
    BYTE   sDiscAddLog,sCorrectLog;

    if (ApplVar.FlowHeader.MAXNUMB<LOGALARMON)
        return;//����ˮ�ռ�

    sLast = 0;

    sActLog = false;
    sSaveP = ApplVar.FlowHeader.ReadP;
    ApplVar.FlowHeader.ReadP = ApplVar.FlowHeader.HeadP;
    CDC_regis_cp.FunN = 0;
    ApplVar.SubTotal = ZERO;//ccr2015-06-15
    ApplVar.SubTotal.Sign = 2;//ccr2016-03-10

    while (Read_Flow((BYTE *)&ApplVar.FlowBuff)>0)
    {
        sReadP = ApplVar.FlowHeader.ReadP;
        ApplVar.FlowHeader.ReadP = sSaveP;//�ָ�,һ��ǿ�ƹػ���������
        ApplVar.PrintLayOut = 0x02;

        sFunc = ApplVar.FlowBuff.CDC_dpt.FunN & 0x1f;
        //PrnBuffer(&sFunc, 1);	//hf test
        sCorrectLog=sDiscAddLog=0;

        switch (sFunc)
        {
        case ECRNOLOG:
            DispEcrNum();
            break;
        case REGISLOG:
#if defined(TEND_PREFIX)//ccr2016-08-08
            Prefix1 = 0;
            Prefix2 = 0;
#endif
            sDateLog = (((UnLong)ApplVar.FlowBuff.CDC_regis.FYear)<<24) + ((UnLong)ApplVar.FlowBuff.CDC_regis.FMonth<<16) + ((UnLong)ApplVar.FlowBuff.CDC_regis.FDay<<8) + ApplVar.FlowBuff.CDC_regis.FHour;
            if (sDateLog>=LogDefine.DateFr && sDateLog<=LogDefine.DateTo)
            {
                sRecno = Bcd2Long((char *)&ApplVar.FlowBuff.CDC_regis.ReceiptNum,sizeof(ApplVar.FlowBuff.CDC_regis.ReceiptNum));
                if ((LogDefine.RecNum ==0 || LogDefine.RecNum == sRecno || LogDefine.LogType ==0xff) && LogDefine.LogType!=REFRESHICLOG)//ccr2015-06-15
                {//�վݺ�һ�� //
                    sActLog = true;
                    logFound = true;
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
                    if (!logFound && TestSaveEJ())
                    {
                        RefreshEJStart(true);
                        StoreEJEnd();
                        RESETBIT(ApplVar.EJVar.ContFlag,EJSTOREMUST);
                    }
#endif
                    if (LogDefine.LogType)
                        CDC_regis_cp = ApplVar.FlowBuff.CDC_regis;//�����վ���Ϣ
                    else
                        DispNew();
                }
            }
            break;
        case REFRESHICLOG://ccr2015-06-15>>>>>>>>>>>>>
            if (LogDefine.LogType==REFRESHICLOG)
            {
                sDateLog = (((UnLong)ApplVar.FlowBuff.CDC_refreshic.FYear)<<24) + ((UnLong)ApplVar.FlowBuff.CDC_refreshic.FMonth<<16) +
                    ((UnLong)ApplVar.FlowBuff.CDC_refreshic.FDay<<8) + ApplVar.FlowBuff.CDC_refreshic.FTime[0];
                if (sDateLog>=LogDefine.DateFr && sDateLog<=LogDefine.DateTo)
                {
                    //sRecno = ApplVar.FlowBuff.CDC_refreshic.Serialum;
                    if (LogDefine.RecNum ==0 || LogDefine.RecNum == ApplVar.FlowBuff.CDC_refreshic.Serialum)
                    {
                        logFound = true;
                        DispRefreshIC();
                    }
                }
            }
            break;//ccr2015-06-15<<<<<<<<<<<<<<<<<<<<<<<<
#if defined(CASE_INDIA)
        case EDITPLULOG:
            if (LogDefine.LogType==EDITPLULOG || LogDefine.LogType==EDITDEPTLOG)
                DispPluData();
            break;
        case EDITDEPTLOG:
            if (LogDefine.LogType==EDITPLULOG || LogDefine.LogType==EDITDEPTLOG)
                DispDeptData();
            break;
#endif
        case DEPTLOG:
        case PLULOG:
            if (LogDefine.LogType==0xff)//ccr2016-03-09>>>>>>>>>
            {
                if (sActLog && (ApplVar.FlowBuff.CDC_art.FunN & 0xc0))
                {//���˻���ȡ��
                    sCorrectLog = 1;
                    if (!sTitle)
                    {
                        RJPrint(0,Msg[TITLEAMT].str);
                        sTitle = true;
                    }
                }
                else
                    break;
            }//ccr2016-03-09<<<<<<<<<<<<<<<<
        case DISCADDLOG:
        case SUBDISCADDLOG:
        case DIRECTLOG:
        case SUBDIRECTLOG:
        case TENDLOG:
        case TAXLOG:
            if (!sTitle && LogDefine.LogType && sActLog && LogDefine.LogType!=0xff)//ccr2015-06-15>>>>>
            {
                RJPrint(0,Msg[TITLEAMT].str);
                sTitle = true;
            }//ccr2015-06-15<<<<<<<<<
        case SUBTOTALLOG:
        case PBCLOSELOG:        //		22			//��̨�ݽ� //
        case TVOIDLOG:          //      21
        case PBOPENLOG:         //		23			//��̨ //
        case TRTABLELOG:        //		24			//transfer table
        case PORALOG:
        case NOADDLOG://ccr2016-05-31
        case ENDLOG:
            if (sActLog)
            {// ��һ����Ч���վ��ϵ����� //
                sDiscAddLog = (LogDefine.LogType==DISCADDLOG && LogDefine.FuncCode==SUBDIRECTLOG //ccr2016-03-10��ѯ�����ۿۼӳ���Ŀ
                               && sFunc>=DISCADDLOG && sFunc<=SUBDIRECTLOG);//ccr2016-03-10�����ۿۼӳ���Ŀ
#if (0)//ccr2016-03-10>>>>
                if  (CDC_regis_cp.FunN &&
                    (LogDefine.LogType==sFunc
                     || sCorrectLog    //ccr2016-03-10��ѯ���൥Ʒ�˻���Ŀ
                     || sDiscAddLog))   //ccr2016-03-10��ѯ�����ۿ���Ŀ
                {//��ӡʱ����վݺ�
                    DispDateRecNo(false);//sFunc!=TENDLOG);
                    CDC_regis_cp.FunN = 0;
                }
#endif//ccr2016-03-10<<<<<
                // ֻͳ����Ч���������ܶ�ʱ������ʾ��������   //

//ccr2016-03-10                if (sFunc==TVOIDLOG && !LogDefine.LogType)
//ccr2016-03-10                    PrintLine('-');

                if ((sFunc!=ENDLOG || (sLast!=TVOIDLOG && sLast!=PORALOG)) &&   //ccr2016-08-11
                    (LogDefine.LogType==0 || LogDefine.LogType==sFunc || sCorrectLog || sDiscAddLog))//ccr2015-06-15
                    (*LogSize[sFunc-1].Get1Record)();

                if (sFunc==TENDLOG)
                    sActLog = false;
            }
            break;
        }
        sLast = sFunc;
        ApplVar.FlowHeader.ReadP = sReadP;
    }
    ApplVar.FlowHeader.ReadP = sSaveP;
    ApplVar.OldClerk = 0;
    if (logFound)
    {
        if (LogDefine.LogType && CheckNotZero(&ApplVar.SubTotal))
        {
//ccr2016-03-10            PrintLine('-');
            if (!ApplVar.SubTotal.Sign & 0x07)
                BcdMul100(&ApplVar.SubTotal);
            PrintRJ(FormatAmtStr(Msg[ZONGJI].str, &ApplVar.SubTotal, PRTLEN));
            PrintLine('-');
        }
        RFeed(3);
        SETBIT(ApplVar.MyFlags,PRNHEADMUST);
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
        SETBIT(ApplVar.EJVar.ContFlag,EJSTOREMUST);
#endif
    } else
        Beep(3);//û���ҵ��վݣ�����
    return ;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//����ˮ���лָ���ˮ�������ApplVar.FlowHeader
void RecallFlowHead()
{

    UnLong sSaveP;
    BYTE i,j;
    WORD ch;

    if (ApplVar.FlowHeader.MAXNUMB==0 && ApplVar.FlowHeader.EndAddr==0)
    {
#if (FLOW_IN_EXTRAM==1)
        //��ˮ���ݴ�����տ�������ļ�β��ʣ��ռ�
        ApplVar.FlowHeader.FromAddr = ApplVar.AP.StartAddress[AddrEndP]+8;
        ApplVar.FlowHeader.EndAddr = ApplVar.SIZE_EXTRAM;

        if (ApplVar.FlowHeader.EndAddr <= ApplVar.FlowHeader.FromAddr
            || (ApplVar.FlowHeader.EndAddr-ApplVar.FlowHeader.FromAddr)<4*LOGALARMON)
        {//��ˮ�ռ�̫С,�޷��洢��ˮ����
            ApplVar.FlowHeader.FromAddr = 0;
            ApplVar.FlowHeader.EndAddr = 0;
            ApplVar.FlowHeader.ReadP = 0;
            ApplVar.FlowHeader.NextNP = 0;
            ApplVar.FlowHeader.HeadP = 0;
            ApplVar.FlowHeader.MAXNUMB = 0;
            return;
        } else
        {
            ApplVar.FlowHeader.ReadP =  ApplVar.FlowHeader.FromAddr;
            ApplVar.FlowHeader.NextNP = ApplVar.FlowHeader.FromAddr;
            ApplVar.FlowHeader.HeadP =  ApplVar.FlowHeader.FromAddr;
            ApplVar.FlowHeader.MAXNUMB = ApplVar.FlowHeader.EndAddr - ApplVar.FlowHeader.FromAddr+1;
        }

#else//��ˮ���ݴ����Flash�е�ָ������

        if (FLASH_LOG_BLOCKS>0)
        {
            //��ˮ���ݴ����ָ����ַ����
            ApplVar.FlowHeader.FromAddr = FLASH_LOG_ADDR;
            ApplVar.FlowHeader.EndAddr = FLASH_LOG_ADDR+FLASH_LOG_SIZE;
            ApplVar.FlowHeader.ReadP =  FLASH_LOG_ADDR;
            ApplVar.FlowHeader.NextNP =     FLASH_LOG_ADDR;
            ApplVar.FlowHeader.HeadP =  FLASH_LOG_ADDR;
            ApplVar.FlowHeader.MAXNUMB = FLASH_LOG_SIZE;
        } else
        {
            ApplVar.FlowHeader.FromAddr = 0;
            ApplVar.FlowHeader.EndAddr = 0;
            ApplVar.FlowHeader.ReadP = 0;
            ApplVar.FlowHeader.NextNP = 0;
            ApplVar.FlowHeader.HeadP = 0;
            ApplVar.FlowHeader.MAXNUMB = 0;
            return;
        }
#endif
        sSaveP = ApplVar.FlowHeader.ReadP;

        ApplVar.FlowHeader.NextNP = ApplVar.FlowHeader.ReadP+1;
        mClearScreen();
        mSetInvAttr();
        DispStrXY((char*)cRECALLFLOW,0,0);
        mClearInvAttr();

        i = j = 0;  ch = '>';
        while (Read_Flow((BYTE *)&ApplVar.FlowBuff)>0)
        {
            i++;
            if (i==0)
                DispCharXY(ch,j++,1);
            if (j==SCREENWD)
            {
                j=0;
                ch ^= 0x02;//<��>�л�
            }

            ApplVar.FlowHeader.NextNP = ApplVar.FlowHeader.ReadP+sizeof(ApplVar.FlowBuff);//��Read_Flow���Զ�ȡ��ˮ����
        }
        ApplVar.FlowHeader.NextNP = ApplVar.FlowHeader.ReadP;
        ReadFrLogRam((char *)&ApplVar.FlowBuff,ApplVar.FlowHeader.ReadP,4);
#if (FLOW_IN_EXTRAM==0)
        if (CLONG(ApplVar.FlowBuff)!=0xffffffffL)
        {//���ܺŷǷ�,��ʾ��ˮ���ݴ���
#if (FLASH_LOG_BLOCKFr==0 && FLASH_LOG_BLOCKS>1)//ccr2016-11-28
            bFlashMBlockErase(FLASH_LOG_BLOCKFr,4);//����ʼ��ַ��ʼ����4��(64k)
#else
            bFlashMBlockErase(FLASH_LOG_BLOCKFr,1);//����64K,�ͷŴ洢�ռ�
#endif
            ApplVar.FlowHeader.NextNP = sSaveP;
        }
#else
        if (CLONG(ApplVar.FlowBuff)!=0x00000000L)
        {//���ܺŷǷ�,��ʾ��ˮ���ݴ���
            ApplVar.FlowHeader.NextNP = sSaveP;
        }
#endif

        ApplVar.FlowHeader.OverCount = 0;

        ApplVar.GCouter = 0;
        memset((BYTE *)&ApplVar.FlowBuff,0,sizeof(ApplVar.FlowBuff));
        memset((BYTE *)&ApplVar.CollectGiven,0,sizeof(ApplVar.CollectGiven));
        ApplVar.FlowHeader.ReadP = sSaveP;
    }
}
/**
 * ����ˮ��ȡָ��ָ��ʼλ��
 *
 * @author EutronSoftware (2014-12-01)
 */
void ResetECRFlow()
{
    ApplVar.FlowHeader.ReadP = ApplVar.FlowHeader.HeadP;
}
//ccr2016-02-20>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * �����ѯ����,Ȼ���ѯ��ӡ��ˮ����
 *
 * @author EutronSoftware (2016-03-08)
 */
void ExploreLog()
{
    WORD sInput;
	ULONG temp;

    while (true)
    {
        memset((char *)&LogDefine,0,sizeof(LogDefine));
        LogDefine.DateTo=0xffffffff;
        sInput = ListItems(MsgALLLOG,0,It_SELELOG,false);
        switch (sInput)
        {
        case (MsgALLLOG-MsgALLLOG+1)://   MsgALLLOG         "ȫ���վ�"
            //����ָ���վݺ�,�����վݺ�
            DispStrXY(Msg[SHJHAOF].str,0,0);
            if (GetStrFrKBD('9',SCREENWD-7,0,6,0)<0)
                continue;
            ScreenFeed(1);
            LogDefine.RecNum=0;
            if (Appl_EntryCounter)
            {
                StrToBCDValue(ApplVar.Entry.Value, &EntryBuffer[ENTRYSIZE - 2], BCDLEN);
                //ccr2016-05-24Ϊ�˼���ECRVIP��ic����Ա��,ֻ����9λ��Ա��
                CWORD(ApplVar.Entry.Value[4]) &= 0x000f;CWORD(ApplVar.Entry.Value[6])=0;
                BCDValueToULong(ApplVar.Entry.Value,&temp);
				LogDefine.RecNum=temp;
            }
            break;
        case (MsgDATERANGE-MsgALLLOG+1)://   MsgDATERANGE     "���ڷ�Χ"
            break;
        case (MsgMESSVIPLOG-MsgALLLOG+1)://MESSVIPLOG        "��Ա���Ѽ�¼"
            LogDefine.LogType=REFRESHICLOG;
            //����ָ����Ա��
            DispStrXY(Msg[TMHYHAO].str,0,0);
            if (GetStrFrKBD('9',SCREENWD-7,0,12,0)<0)
                continue;
            ScreenFeed(1);
            if (Appl_EntryCounter)
            {//ccr2016-06-02��Ա��ֻȡ9λ,������Ϊ999999999
                StrToBCDValue(ApplVar.Entry.Value, &EntryBuffer[ENTRYSIZE - 2], BCDLEN);
                CWORD(ApplVar.Entry.Value[4]) &= 0x000f;CWORD(ApplVar.Entry.Value[6])=0;
                BCDValueToULong(ApplVar.Entry.Value,&temp);
  				LogDefine.RecNum=temp;
            }
            break;
        case (MsgPRNCASH-MsgALLLOG+1)://   MsgPRNCASH       "��ӡ�����¼"
            LogDefine.LogType=TENDLOG;
            switch (ListItems(MsgALLCASH,0,It_SELETEND,false))
            {
            case 1:
                DispStrLF(Msg[MsgALLCASH].str);
                break;
            case 2:
                sInput = ListItems(SETTEND,0,It_SELETEND,false);
                if (sInput>0 && sInput<99)
                {
                    DispStrLF(GetActiveItemStr());
                    LogDefine.FuncCode = sInput+TEND;
                    break;
                }
            default:
                continue;
            }
            break;
        case (MsgPRNDEPART-MsgALLLOG+1)://   MsgPRNDEPART     "��ӡ�����¼"
            LogDefine.LogType=DEPTLOG;
            switch (ListItems(MsgALLDEPT,0,It_SELEDEPT,false))
            {
            case 1:
                DispStrLF(Msg[MsgALLDEPT].str);
                break;
            case 2:
                sInput = ListItems(SETDEPT,0,It_SELEDEPT,false);
                if (sInput>0 && sInput<PLU1-DEPT)
                {
                    DispStrLF(GetActiveItemStr());
                    LogDefine.FuncCode = sInput+DEPT;
                    break;
                }
            default:
                continue;
            }
            break;
        case (MsgPRNPLU-MsgALLLOG+1)://   MsgPRNPLU        "��ӡ��Ʒ��¼"
            LogDefine.LogType=PLULOG;
            switch (ListItems(MsgALLPLU,0,It_SELEPLU,false))
            {
            case 1:
                DispStrLF(Msg[MsgALLPLU].str);
                break;
            case 2:
                sInput = ListItems(SETPLU,0,It_SELEPLU,false);
                if (sInput==It_PLU_MG)
                {//ɨ���˵�Ʒ����
                    if (GetInputByListItems() && ApplVar.AP.Plu.RandomSize)
                    {
                        KeyFrHost=0xff;
                        StrToBCDValue(ApplVar.Entry.Value, &EntryBuffer[ENTRYSIZE - 2], ApplVar.AP.Plu.RandomSize);
                        ApplVar.PluNumber = GetPluNumber(0, ApplVar.Entry.Value);
                        if (!ApplVar.PluNumber)
                        {
                            DisplayPrompt((char*)Msg[CWXXI05].str);
                            continue;
                        }
                        else
                        {
                            LogDefine.FuncCode = ApplVar.PluNumber+PLU1;
                            ApplVar.PluNumber--;
                            ReadPlu();
                            DispStrLF(ApplVar.Plu.Name);
                            break;
                        }
                    }
                    else
                    {
                        KeyFrHost=0xff;
                        continue;
                    }
                }
                else if (sInput>0 && sInput<PLU3-PLU1)
                {
                    DispStrLF(GetActiveItemStr());
                    LogDefine.FuncCode = sInput+PLU1;
                    break;
                }
            default:
                continue;
            }
            break;
        case (MsgPRNDISCOUNT-MsgALLLOG+1)://   MsgPRNDISCOUNT   "��ӡ�ۿۼӳ�"
            //ָ���ۿۼӳ���־��Χ
            DispStrLF(Msg[MsgPRNDISCOUNT].str);
            LogDefine.LogType=DISCADDLOG;
            LogDefine.FuncCode=SUBDIRECTLOG;
            break;
        case (MsgPRNRAPO-MsgALLLOG+1)://   MsgPRNRAPO       "��ӡ�����"
            DispStrLF(Msg[MsgPRNRAPO].str);
            LogDefine.LogType=PORALOG;
            break;
        case (MsgPRNCORRECT-MsgALLLOG+1)://   MsgPRNCORRECT    "��ӡ��������"
            DispStrLF(Msg[MsgPRNCORRECT].str);
            LogDefine.LogType=0xff;//��ѯ��Щ����Ϊ���ĵ�Ʒ����
            break;
        case (MsgPRNCANCEL-MsgALLLOG+1)://  MsgPRNCANCEL    "��ӡȡ������"
            DispStrLF(Msg[MsgPRNCANCEL].str);
            LogDefine.LogType=TVOIDLOG;
            break;
        case (MsgPRNNOSALE-MsgALLLOG+1)://   MsgPRNNOSALE     "��ӡ������"
            DispStrLF(Msg[MsgPRNNOSALE].str);
            LogDefine.LogType=NOADDLOG;
            break;
        case 0:
        case It_EXIT:
        default:
            return;
        }
        if (sInput!=(MsgALLLOG-MsgALLLOG+1))
        {//ָ�����ڷ�Χ,���뿪ʼ����
            DispStrXY(Msg[KSHRQIF].str,0,0xff);
#if SCREENWD<18
            ScreenFeed(1);
            DispStrXY("YYMMDDHH",0,0xff);
#else
            DispStrXY("YYMMDDHH",SCREENWD-8,0xff);
#endif
            if (GetStrFrKBD('9',SCREENWD-8,0xff,8,0)<0)
                continue;
            if (Appl_EntryCounter)
            {
                StrToBCDValue(ApplVar.Entry.Value, &EntryBuffer[ENTRYSIZE - 2], BCDLEN);
                LogDefine.DateFr = (((UnLong)ApplVar.Entry.Value[3])<<24) + (((UnLong)ApplVar.Entry.Value[2])<<16) + ((UnLong)ApplVar.Entry.Value[1]<<8) + ApplVar.Entry.Value[0];
            }
            ScreenFeed(1);
            DispStrXY(Msg[JSHRQIF].str,0,0xff);
#if SCREENWD<18
            ScreenFeed(1);
            DispStrXY("YYMMDDHH",0,0xff);
#else
            DispStrXY("YYMMDDHH",SCREENWD-8,0xff);
#endif
            if (GetStrFrKBD('9',SCREENWD-8,0xff,8,0)<0)
                continue;
            if (Appl_EntryCounter)
            {
                StrToBCDValue(ApplVar.Entry.Value, &EntryBuffer[ENTRYSIZE - 2], BCDLEN);
                LogDefine.DateTo = (((UnLong)ApplVar.Entry.Value[3])<<24) + (((UnLong)ApplVar.Entry.Value[2])<<16) + ((UnLong)ApplVar.Entry.Value[1]<<8) + ApplVar.Entry.Value[0];
            }

        }
        LoadReceipLog();
    }
    return ;
}
//ccr2016-02-20<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


/*****************************************************************
 * ��������ˮ���ݴ����һ��250�ֽڷ�Χ�ڵĴ�����з���
 * �ڰ���ͷ�����տ���ı��,��β��׷�������ֽ�0,��ʾ�޺�����ˮ����
 * ���������ʹ��  SysBuf  ������
 * @author EutronSoftware (2016-04-12)
 ***************************************************************/
void SendMultiLog()
{
    short i,size;
    ULONG sendCount=0;//���ͼ�����
    ULONG logReadCopyNext=0;//��һ������Ҫ��ȡ����ˮ����
    ULONG logReadCopyLast=0;//��ǰ��ȡ����ˮ����
    BYTE OK_Send;

    ULONG logSize;//����ָ��������͵���־���ݰ���С
    int  sendFlag;//���ͼ�����
#if defined(DEBUGBYPC)
#if (sizeof(SysBuf)<sizeof(ApplVar.FlowBuff))
#error ("������SysBuf�ĳ���!");
#endif
#else
//      if (sizeof(SysBuf)<sizeof(union FLOWREC))
//				("������SysBuf�ĳ���!");
#endif
    PCBuffer[0]='F';
    PCBuffer[1]=ECRNOLOG;
    PCBuffer[2]=REGISTER;
    PCBuffer[3]=LOCATION;
    sendFlag = 1;//������ʾÿ������е���ˮ����

    logSize = 4;
    //����PCBuffer,һ�η��Ͳ�����1024�ֽڵ���ˮ����
    do  {//�ڴ�ѭ����,���ȫ����ˮ���ݵķ���
        if (logReadCopyNext!=0)
            ApplVar.FlowHeader.ReadP = logReadCopyNext;//ָ����һ��Ҫ��ȡ�ͷ��͵���ˮ
        logReadCopyLast = ApplVar.FlowHeader.ReadP;//���浱ǰ��ȡ����ˮ���ݵ�ַ
        logReadCopyNext = logReadCopyLast;//ccr2016-04-18
        do {//�ڴ�ѭ����,���һ������ͷ���
            size = Read_Flow(SysBuf);//��ȡһ����ˮ
            if (size>0 && (size+logSize)<=250)
            {//�����ݴ���PCBuffer,��ɴ��

                PCBuffer[logSize++]='F';
                memcpy(PCBuffer+logSize,SysBuf,size);
                logSize+=size;
                sendFlag++;
            }
            else if (size>=0)// || (size+logSize)>250)
            {//���������,�ȷ�������
                if (size)//����ȡ��LOG�������,�޸ĵ�ַ
                    SUB_SCANFP(size);
                if (sendFlag)
                {//��Ҫ���͵�����,�����ݷ��ͳ�ȥ
                    memset(SysBuf,' ',SCREENWD);
                    OK_Send = ULongtoASC(SysBuf+SCREENWD-1,sendFlag);
                    SysBuf[SCREENWD]=0;
                    if (ApplVar.CentralLock==SET)
                        DispStrXY(SysBuf,0,2);//��ʾ�ѷ���������Ŀ
                    else
                    {
                        SysBuf[0] = OK_Send;
                        DispStrXY(SysBuf+SCREENWD-SysBuf[0],SCREENWD-SysBuf[0],STATELINE);
                    }

                    logReadCopyLast = logReadCopyNext;
                    logReadCopyNext = ApplVar.FlowHeader.ReadP;//���ͳɹ�ʱ,�´δӴ˵�ַ����
                    ApplVar.FlowHeader.ReadP = logReadCopyLast;//���ͳ���ʱ,�´δӴ����·���
                    if (size==0 && logSize<=250)
                    {//���׷�������ֽ�0,��ʾ�޺�����ˮ����
                        PCBuffer[logSize++]=0;
                        PCBuffer[logSize++]=0;
                    }
                    if(!(SendRecord(PCBuffer, logSize)))
                    {//����ʧ��ʱ
                        OK_Send = false;
                        CheckError(ERROR_ID(CWXXI84));
                        size = 0;//��������.
                    }
                    else
                    {//���ͳɹ�
                        ApplVar.FlowHeader.ReadP = logReadCopyNext;//���ͳɹ�,�´δӴ˷���
                        //ccr2016-04-18 logReadCopyNext = 0;
                        sendCount+=sendFlag;
                        OK_Send = true;
                    }
                    logSize = 0;
                }
                break;//һ�����������
            }
            else
                CheckError(ERROR_ID(CWXXI48));
        } while (size>0);
        sendFlag = 0;//������ʾÿ������е���ˮ����
    } while (size>0);

    memset(SysBuf,' ',SCREENWD);
    SysBuf[0] = ULongtoASC(SysBuf+SCREENWD-1,sendCount);
    SysBuf[SCREENWD]=0;
    DispStrXY(SysBuf+SCREENWD-SysBuf[0],SCREENWD-SysBuf[0],STATELINE);
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

