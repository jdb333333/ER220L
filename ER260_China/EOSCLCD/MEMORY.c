#include "king.h"
#include "flashb.h"
/************************ Application Memory Lay Out ************************/

#if defined(DEBUGBYPC)
APPLICATION_SAVE ApplVar;
APPLICATION_SAVE ApplVarSave;//��ApplVarָ���ڵ�ַADDR_EXTRAM=0x64000000��SRAM��

#if (DD_ECRVIP==1)
//.............ECRVIP���ݴ洢��....................
struct  TECRVIPVar   ECRVIPVar1[ECRVIPMAX/2];
struct  TECRVIPVar   ECRVIPVar2[ECRVIPMAX/2];
struct  TECRVIPFix   ECRVIPFix[ECRVIPMAX];
#endif

#else

#if (DD_ECRVIP==1)
//.............ECRVIP���ݴ洢��....................
struct  TECRVIPVar   ECRVIPVar1[ECRVIPMAX/2] __attribute__((at(FLASH_BASEADDR+FLASH_ECRVIPVAR1_ADDR)));//[ECRVIPMAX/2]
struct  TECRVIPVar   ECRVIPVar2[ECRVIPMAX/2] __attribute__((at(FLASH_BASEADDR+FLASH_ECRVIPVAR2_ADDR)));//[ECRVIPMAX/2]
struct  TECRVIPFix   ECRVIPFix[ECRVIPMAX]  __attribute__((at(FLASH_BASEADDR+FLASH_ECRVIPFIX_ADDR)));// [ECRVIPMAX]
#endif

#if ApplVarInSRAM
APPLICATION_SAVE ApplVar __attribute__((at(0x64000000)));//��ApplVarָ���ڵ�ַADDR_EXTRAM=0x64000000��SRAM��
#else
APPLICATION_SAVE ApplVar __attribute__ ((aligned (4)));;
APPLICATION_SAVE ApplVarSave __attribute__((at(0x64000000)));//��ApplVarָ���ڵ�ַADDR_EXTRAM=0x64000000��SRAM��
#endif
#endif

struct SETUPLIST SetList;

struct TimeDate         Now;

char
    FRegSuspend,           //���۹�����˵�,���ӹ�����˵�������������
	EntryBuffer[ENTRYSIZE],                /* entry buffer is ((max caption size) * 2) + 1 */
    PwdInput[MAXPWD],		//Save the password of input
    TimeAsci[10],                    /* holds asci time*/
    DateAsci[16],           /* holds asci date(����TIME_DATEҪ��ĸ�ʽ�洢) */
    ProgLineMes[64],            /* display program option */
    SysBuf[128];            /* System buffer max 128 positions,���Сȷ��Ϊ2�ı��� */


struct DISPLAY_RGBUF
    Appl_DispRGBuf;

WORD
      FuncLookNum,            //��ǰѡ�õ�FuncLook
      Appl_PortNumber;

short
     Appl_ProgNumber;             /* item  (plu or function #) number of programming */


// =============================================================
// Variabili globali
BYTE    KeyFrHost=0xff;       //Key code from host computer.=0xff:no keycode
BYTE 	Bios_Key0_Key;         //    key number: 00 = No key
// =============================================================

BYTE

    ApplVar_Restored=0x00,   //=0x5a,ApplVar�еı������ݱ��ָ�
    MACSwitch,  //0=MAC is off;1=MAC is on

    Appl_ProgLinePre,                /* programming type line */
    Appl_ProgLine,                /* programming type line */
    Appl_ProgStart,               /* programming started */
    Appl_ProgType,               /* programming type status */
    Appl_BitNumber,              /* used during programming */
    Appl_EntryCounter,                   /* entry counter */
    Appl_MaxEntry,               //Max length of input from keyboard
    ApplRamSaved,               //ApplVar �����־

    InActive;               /* Activity timer for displaying Time */

struct PORTRECORD   Appl_Port;

struct RGSUSPEND RGSuspend;/* ��Ź�����վ�,RGNumber=0ʱ,�޹�����վ� */

char    *StrForST0=0;         /* ������,��Ҫ��ʾ��״̬�е�һ��״̬λ�õ��ַ���.=0ʱ,����ʾ */

#if (PLUCODE_X==1)
WORD
    PLU_X_Report;// ��־,��ʾֱ�ӱ�����.=0ʱ,����ֱ�ӱ���,>0ʱ,Ϊֱ�ӱ���,��ֵΪ�����еļ�¼��  //
BYTE
    DEPT_Key_ID,
    PLU_Key_ID;// PLU1 �ڼ����е�λ��
#endif

#if (DD_ECRVIP==1)
struct TECRVIP ECRVIP;                      //��¼��ǰ��¼�Ļ�Ա,���ݵ��籣��,��˹ػ������ݻᶪʧ
#endif
//////////////////////////////////////////////////////////////////////////////////////////////
//ccr2016-03-24...���ڹ����ļ��ռ�..................................
const int sTypeList[13]={GROUPIDX,DEPTIDX,PLUIDX,TENDIDX,PORAIDX,DRAWIDX,CORRIDX,DISCIDX,CURRIDX,TAXIDX,PBIDX,PBTIDX,AGREEIDX};
/**
 * ���ݴ洢���ݵı仯,���¼����ļ��ļ�¼�ռ�
 *
 * @author EutronSoftware (2016-03-24)
 *
 * @param type :�ļ�����(sTypeList�е�ֵ);
 *             =-1ʱ,���¼���ȫ���ļ��Ŀռ�;
 */
void GetRecordSize(int type)
{
    struct REPSIZE *size;
    WORD *recordsize, i;
    ULONG rsize, newsize;
    int sLp;
    int sType=type;

    for (sLp=-1;sLp<13;)
    {
        switch (sType)
        {
        case -1 :       /* total sales recordsize */
            ApplVar.AP.Sales.RecordSize = 0;
            recordsize = (WORD*)&ApplVar.AP.Sales.RecordSize;
            size = ApplVar.AP.Sales.Size;
            break;
        case GROUPIDX :     /* group recordsize */
            ApplVar.AP.Group.RecordSize = ApplVar.AP.Group.CapSize + 2; /* add family selection */
            ApplVar.AP.Group.TotalOffSet = ApplVar.AP.Group.RecordSize; /* start of totals */
            recordsize = (WORD*)&ApplVar.AP.Group.RecordSize;
            size = ApplVar.AP.Group.Size;
            break;
        case DEPTIDX :      /* dept record size */
            ApplVar.AP.Dept.RecordSize = ApplVar.AP.Dept.RandomSize +
                                 ApplVar.AP.Dept.CapSize +
                                 ApplVar.AP.Dept.PriceSize +
                                 ApplVar.AP.Dept.PriMaxSize +
                                 5;      /* add Group + Print + Kp + Max */
            if (ApplVar.AP.Tax.Number)
                ApplVar.AP.Dept.RecordSize++;   /* add tax selection */
            ApplVar.AP.Dept.TotalOffSet = ApplVar.AP.Dept.RecordSize;   /* start of totals */
            recordsize = (WORD*)&ApplVar.AP.Dept.RecordSize;
            size = ApplVar.AP.Dept.Size;
            break;
        case PLUIDX :       /* plu record size */
            ApplVar.AP.Plu.RecordSize = ApplVar.AP.Plu.RandomSize +
                                ApplVar.AP.Plu.CapSize +
                                (ApplVar.AP.Plu.Level * ApplVar.AP.Plu.PriceSize) +
                                ApplVar.AP.Plu.InvSize + sizeof(ApplVar.Plu.Dept);  /* add dept */
            if (ApplVar.AP.Plu.Cost)    /* cost price ? */
                ApplVar.AP.Plu.RecordSize += ApplVar.AP.Plu.PriceSize;
            if (ApplVar.AP.OFFPrice.Number>0)
                ApplVar.AP.Plu.RecordSize += sizeof(ApplVar.Plu.OFFIndex);
            if (ApplVar.AP.Options.InvAmt)
                ApplVar.AP.Plu.RecordSize += ApplVar.AP.Options.InvAmt;
            if (TESTBIT(ApplVar.AP.Options.Plu,BIT0))   /* Linked Plu ? */
                ApplVar.AP.Plu.RecordSize += sizeof(ApplVar.Plu.Link);
            if (TESTBIT(ApplVar.AP.Options.Plu,BIT1))
                ApplVar.AP.Plu.RecordSize += sizeof(ApplVar.Plu.DeptHi);/* set large dept number */
            ApplVar.AP.Plu.TotalOffSet = ApplVar.AP.Plu.RecordSize; /* start of totals */
            recordsize = (WORD*)&ApplVar.AP.Plu.RecordSize;
            size = ApplVar.AP.Plu.Size;
            break;
        case TENDIDX :      /* tender record size */
            ApplVar.AP.Tend.RecordSize = ApplVar.AP.Tend.CapSize + 5;
            ApplVar.AP.Tend.TotalOffSet = ApplVar.AP.Tend.RecordSize;   /* start of totals */
            recordsize = (WORD*)&ApplVar.AP.Tend.RecordSize;
            size = ApplVar.AP.Tend.Size;
            break;
        case PORAIDX :      /* PoRa record size */
            ApplVar.AP.PoRa.RecordSize = ApplVar.AP.PoRa.CapSize + 4;
            ApplVar.AP.PoRa.TotalOffSet = ApplVar.AP.PoRa.RecordSize;   /* start of totals */
            recordsize = (WORD*)&ApplVar.AP.PoRa.RecordSize;
            size = ApplVar.AP.PoRa.Size;
            break;
        case DRAWIDX :      /* Drawer record size */
            ApplVar.AP.Draw.RecordSize = ApplVar.AP.Draw.CapSize + 2;
            ApplVar.AP.Draw.TotalOffSet = ApplVar.AP.Draw.RecordSize;   /* start of totals */
            recordsize = (WORD*)&ApplVar.AP.Draw.RecordSize;
            size = ApplVar.AP.Draw.Size;
            break;
        case CORRIDX :      /* Correc record size */
            ApplVar.AP.Correc.RecordSize = ApplVar.AP.Correc.CapSize + 2;
            ApplVar.AP.Correc.TotalOffSet = ApplVar.AP.Correc.RecordSize;   /* start of totals */
            recordsize = (WORD*)&ApplVar.AP.Correc.RecordSize;
            size = ApplVar.AP.Correc.Size;
            break;
        case DISCIDX :      /* Disc record size */
            ApplVar.AP.Disc.RecordSize = ApplVar.AP.Disc.CapSize + 10;
            ApplVar.AP.Disc.TotalOffSet = ApplVar.AP.Disc.RecordSize;   /* start of totals */
            recordsize = (WORD*)&ApplVar.AP.Disc.RecordSize;
            size = ApplVar.AP.Disc.Size;
            break;
        case CURRIDX :      /* Curr record size */
            ApplVar.AP.Curr.RecordSize = ApplVar.AP.Curr.CapSize + 12;
            ApplVar.AP.Curr.TotalOffSet = ApplVar.AP.Curr.RecordSize;   /* start of totals */
            recordsize = (WORD*)&ApplVar.AP.Curr.RecordSize;
            size = ApplVar.AP.Curr.Size;
            break;
        case TAXIDX :       /* Tax record size */
            ApplVar.AP.Tax.RecordSize = ApplVar.AP.Tax.CapSize + 4;
            ApplVar.AP.Tax.TotalOffSet = ApplVar.AP.Tax.RecordSize; /* start of totals */
            recordsize = (WORD*)&ApplVar.AP.Tax.RecordSize;
            size = ApplVar.AP.Tax.Size;
            break;
        case PBIDX :        /* PBF record size */
            ApplVar.AP.Pb.RecordSize = ApplVar.AP.Pb.CapSize + 2;
            ApplVar.AP.Pb.TotalOffSet = ApplVar.AP.Pb.RecordSize;   /* start of totals */
            recordsize = (WORD*)&ApplVar.AP.Pb.RecordSize;
            size = ApplVar.AP.Pb.Size;
            break;
        case PBTIDX :       /* PBTable record size */
            ApplVar.AP.Pb.PBTRecordSize = (ApplVar.AP.Pb.Random & 0x0f) + ApplVar.AP.Pb.Text + ApplVar.AP.Pb.AmtSize + 6;
            if (TESTBIT(PBINFO, BIT7))  /* Discount item stored ? */
                ApplVar.AP.Pb.PBTRecordSize += ((ApplVar.AP.Pb.AmtSize + 1) * 2);
            ApplVar.AP.Pb.PBTTotalOffset = ApplVar.AP.Pb.PBTRecordSize; /* start of totals */
            recordsize = (WORD*)&ApplVar.AP.Pb.PBTRecordSize;
            size = ApplVar.AP.Pb.PBTSize;
            break;
        case OFFIDX :       /* OFF recordsize */
            ApplVar.AP.OFFPrice.RecordSize = ApplVar.AP.OFFPrice.CapSize + ApplVar.AP.OFFPrice.PriUSize + 15;   /* add family selection */
            return;
        case AGREEIDX :     /* OFF recordsize */
            ApplVar.AP.Agree.RecordSize = ApplVar.AP.Agree.CapSize + 20+18+4;   /* add family selection */
            return;
        default :
            return;
        }
        newsize = *recordsize;
        for (i = 0; i < REPDEFMAX; i++)
        {
            rsize = 0L;
            size[i].Length = size[i].Cc+
                             size[i].Qty+
                             size[i].Amt+
                             size[i].RetQty+
                             size[i].Disc+
                             size[i].Cost+1;
            if (size[i].Length == 1)
                size[i].Length = 0;

            if (size[i].Length)
            {
                if (size[i].Periods & 0x01)
                    rsize += size[i].Length;
                if (size[i].Periods & 0x02)
                    rsize += size[i].Length;
                if (size[i].Periods & 0x04)
                    rsize += size[i].Length;
                if (size[i].Periods & 0x08)
                    rsize += size[i].Length;
            }
            //		if (type == -1)
            {
                if (i == 1)     /* clerk */
                    rsize *= ApplVar.AP.Clerk.Number;
                else if (i == 2)    /* time zone */
                    rsize *= ApplVar.AP.Zone.Number;
                else if (i == 3)    /* day of week */
                    rsize *= ApplVar.AP.Day.Number;
                else if (i == 4)    /* months or salespersons */
                    rsize *= ApplVar.AP.Month.Number;
                else if (i == 5)
                    rsize *= ApplVar.AP.SalPer.Number;
            }
            newsize += rsize;
        }
        *recordsize = (WORD) newsize;
        if (type != -1) break;
        sLp++;
        sType =  sTypeList[sLp];
    }
}

