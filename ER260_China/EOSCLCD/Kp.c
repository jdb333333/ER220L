#define KP_C
#include "king.h"
#include "exthead.h"
#include "exth.h"

/***************************************************************/
/* ������ӡ�������� */
//#define KP_NORMAL   0   //������ӡ
//#define KP_DBLWIDTH 1   //�����ӡ
//#define KP_BLACK    2   //��ɫ����
//#define KP_RED      3   //��ɫ����
//#define KP_CUTF     4   //ȫ��ֽ
//#define KP_CUTH     5   //����ֽ
//#define KP_DBLHIGH  6   //���ߴ�ӡ
//#define KP_FEED     7   //��ֽһ��

/* ������ӡ������(0-�޳�����ӡ��,1-���ô�ӡ��) */
//#define	T58A_C	(0+2)       //��58mm A���壬���е�,32�ַ���
//#define	T80A_C	(T58A_C+1)  //��80mm��A���壬���е�,48�ַ�)
//#define	T58B_C	(T80A_C+1)  //��58mm B���壬���е�,42�ַ���
//#define	D76A_C	(T58B_C+1)  // 76mm���42�ַ���A���壬���е������ӵ��ͺ�
//#define	CITIZEN	(D76A_C+1)  //�����Ǵ�ӡ��, 30�ַ����
//#define	T58A	(CITIZEN+1) //��58mm A���壬���е���
//#define	KPMAX	(T58A-T58A_C+1)


//�����ô�ӡ����������cmd :KP_NORMAL/KP_DBLHIGH...
#define CmdKp(cmd) CmdExtPrinter(ApplVar.KP.Prt->port-1,ApplVar.KP.Prt->type & 0x0f,cmd) //ccr2017-02-08
//for defined(CASE_INNERDOTPRN)-----v��Ϊ21
CONST BYTE KPWidth[KPMAX]={16,24,21,21,16,16};//ccr2014-04-01,KPWidthΪ�����ӡʱ���ַ���
CONST BYTE KPCutFeed[KPMAX]={5,3,5,0,6,6};//ccr2017-02-08 ��ֽλ����ֽ����

#if defined(CASE_FORHANZI)
CONST BYTE KpCmd[KPMAX][7][4] = {
    {//EPSON��ӡ��,ʹ��A����, 32�ַ����
		{3, 0x1b, '!', 0x00},    /* normal width */
		{3, 0x1b, '!', 0x20},    /* Double width */
		{0, 0x1b, 0x72, 0},    /* black */
		{0, 0x1b, 0x72, 1},    /* red */
		{2, 0x1b, 'i',  0},    /* Full Cut ESC i + 0*/
		{2, 0x1b, 'm',  0},    /* partial  Cut ESC m */
        {3, 0x1b, '!', 0x10},    /* Double heigth */
    },
    {//EPSON��ӡ��,ʹ��A����, 42�ַ����             /* Epson A normal height */
		{3, 0x1d, '!', 0x00},    /* normal width */
		{3, 0x1d, '!', 0x10},    /* Double width */
		{0, 0x1b, 0x72, 0},    /* black */
		{0, 0x1b, 0x72, 1},    /* red */
		{2, 0x1b, 'i',  0},    /* Full Cut ESC i + 0*/
		{2, 0x1b, 'm',  0},    /* partial  Cut ESC m */
        {3, 0x1d, '!', 0x01},    /* Double heigth */
    },
    {//EPSON��ӡ��,ʹ��B����, 42�ַ����             /* Epson B double height */
		{3, 0x1d, '!', 0x00},    /* normal width */
		{3, 0x1d, '!', 0x10},    /* Double width */
		{0, 0x1b, 0x72, 0},    /* black */
		{0, 0x1b, 0x72, 1},    /* red */
		{2, 0x1b, 'i',  0},    /* Full Cut ESC i + 0*/
		{2, 0x1b, 'm',  0},    /* partial  Cut ESC m */
        {3, 0x1d, '!', 0x01},    /* Double heigth */
    },
    {//��ʽ��ӡ��,���е�, 32�ַ����
		{3, 0x1b, '!', 0x01},    /* normal width */
		{3, 0x1b, '!', 0x21},    /* Double width */
		{0, 0x1b, 0x72, 0},    /* black */
		{0, 0x1b, 0x72, 1},    /* red */
        {3, 0x1d, 'V',  '0'},    /* Full Cut ESC i + 0 */
        {3, 0x1d, 'V',  '1'},    /* partial  Cut ESC m */
        {3, 0x1d, '!', 0x01},    /* Double heigth */
    },
    {//�����Ǵ�ӡ��, 30�ַ����              /* Citizen iDP3540, iDP3541 */
        {3, 0x1d, '!', 0x00},    /* normal width */
        {3, 0x1d, '!', 0x10},    /* Double width */
		{0, 0, 0, 0},    /* black */
		{0, 0, 0, 0},    /* red */
        {3, 0x1d, 'V',  '0'},    /* Full Cut ESC i + 0 */
        {3, 0x1d, 'V',  '1'},    /* partial  Cut ESC m */
        {3, 0x1d, '!', 0x01},    /* Double heigth */
    },
    {//T58A��ӡ��,���е�,30�ַ����               /* T58A */
		{3, 0x1d, '!', 0x00},    /* normal width */
		{3, 0x1d, '!', 0x10},    /* Double width */
		{0, 0x1b, 0x72, 0},    /* black */
		{0, 0x1b, 0x72, 1},    /* red */
		{0, 0x1b, 'i',  0},    /* Full Cut ESC i + 0*/
		{0, 0x1b, 'm',  0},    /* partial  Cut ESC m */
        {3, 0x1d, '!', 0x01},    /* Double heigth */
    },
};
#else
CONST BYTE KpCmd[KPMAX][7][4] = {
    {//"  T58A-C",   //��58mm A���壬���е�,32�ַ���
		{3, 0x1b, '!', 0x01},    /* normal width */
		{3, 0x1b, '!', 0x21},    /* Double width */
		{0, 0x1b, 0x72, 0},    /* black */
		{0, 0x1b, 0x72, 1},    /* red */
		{2, 0x1b, 'i',  0},    /* Full Cut ESC i + 0*/
		{2, 0x1b, 'm',  0},    /* partial  Cut ESC m */
        {3, 0x1b, '!', 0x11},    /* Double heigth */
    },
    {//"  T80A-C",   //��80mm��A���壬���е�)
		{3, 0x1b, '!', 0x01},    /* normal width */
		{3, 0x1b, '!', 0x21},    /* Double width */
		{0, 0x1b, 0x72, 0},    /* black */
		{0, 0x1b, 0x72, 1},    /* red */
		{2, 0x1b, 'i',  0},    /* Full Cut ESC i + 0*/
		{2, 0x1b, 'm',  0},    /* partial  Cut ESC m */
        {3, 0x1b, '!', 0x11},    /* Double heigth */
    },
    {//"  T58B-C",   //��58mm B���壬���е�,42�ַ���
		{3, 0x1b, '!', 0x01},    /* normal width */
		{3, 0x1b, '!', 0x21},    /* Double width */
		{0, 0x1b, 0x72, 0},    /* black */
		{0, 0x1b, 0x72, 1},    /* red */
		{2, 0x1b, 'i',  0},    /* Full Cut ESC i + 0 */
		{2, 0x1b, 'm',  0},    /* partial  Cut ESC m */
        {3, 0x1b, '!', 0x11},    /* Double heigth */
    },
//#if defined(CASE_INNERDOTPRN)
    {//"  D76A-C",   // 76mm���42�ַ���A���壬���е�),�������(CASE_INNERDOTPRN)
        {3, 0x1b, '!', 0x01},    /* normal width */
        {3, 0x1b, '!', 0x21},    /* Double width */
		{0, 0, 0, 0},    /* black */
		{0, 0, 0, 0},    /* red */
        {3, 0x1d, 'V',  '0'},    /* Full Cut ESC i + 0 */
        {3, 0x1d, 'V',  '1'},    /* partial  Cut ESC m */
        {3, 0x1b, '!', 0x11},    /* Double heigth */
    },
//#endif
    {//" CITIZEN",   //�����Ǵ�ӡ��iDP3540, iDP3541, 30�ַ����
        {3, 0x1d, '!', 0x00},    /* normal width */
        {3, 0x1d, '!', 0x10},    /* Double width */
        {0, 0, 0, 0},    /* black */
        {0, 0, 0, 0},    /* red */
        {3, 0x1d, 'V',  '0'},    /* Full Cut ESC i + 0 */
        {3, 0x1d, 'V',  '1'},    /* partial  Cut ESC m */
        {3, 0x1d, '!', 0x01},    /* Double heigth */
    },
    {//"  T58A  ",   //��58mm A���壬���е���
		{3, 0x1b, '!', 01},    /* normal width */
		{3, 0x1b, '!', 0x21},    /* Double width */
		{0, 0x1b, 0x72, 0},    /* black */
		{0, 0x1b, 0x72, 1},    /* red */
		{0, 0x1c, 0x49, 0},    /* Full Cut */
		{0, 0x1c, 0x49, 1},    /* Partial Cut */
        {3, 0x1b, '!', 0x11},    /* Double heigth */
    },
};
#endif

/**
 * �����ô�ӡ����������
 *
 * @author EutronSoftware (2016-12-14)
 *
 * @param port :0,1,2,...,��ӡ�����ڴ���
 * @param type
 *             :��ӡ���ͺ�.����>=2(0-�޳�����ӡ��,1-���ô�ӡ��)
 * @param cmd :KP_NORMAL/KP_DBLHIGH...
 */
void CmdExtPrinter(BYTE port,BYTE type,BYTE cmd)
{
    CONSTCHAR *p;
    BYTE l;

    if (cmd==KP_FEED)
        SendComm(port, LF);
    else
    {
        if (type >= KPMAX+2)
            p = KpCmd[KPMAX-1][cmd];
        else
            p = KpCmd[type - 2][cmd];
        l = p[0];     /* command length */
        while(l)
        {
            p++;
            SendComm(port, p[0]);
            l--;
        }
   }
}

/**
 * ��Ҫ��ӡ����������������ӡ��
 *
 * @author EutronSoftware (2014-04-01)
 *
 * @param cmd=0 normal print
 *        cmd=1 is double
 *        cmd=2 is double, red
 *        cmd=3 receipt issue
 * @param str :Ҫ��ӡ������
 */
void PrintKp(BYTE cmd,CONSTCHAR *str)
{
	BYTE l, type;

    type = ApplVar.KP.Prt->type & 0x0f;
    if (!str || !type)     /* empty string or not programmed */
        return;
    if (type == 1)  /* internal */
    {
		PrintStr(str);
		return;
    }
    l = KPWidth[type-2];

    if (l<20)
    {//�߳���ʼ�Ŀո�,�Ա㾡���ܶ�ش�ӡ����
        while (*str == ' ')
            str++;
    }
	//ccr2014-04-01>>>>>>
	if (cmd==KP_DBLHIGH)
	{
		CmdKp(KP_DBLHIGH);      /* ���ߴ�ӡ */
        l *= 2;
	}
    else if (cmd)
    {
        if (KpCmd[type-2][KP_DBLWIDTH][0]==0) //ccr2017-02-07
            l *= 2;
        else
            CmdKp(KP_DBLWIDTH);      /* Ĭ��Ϊ�����ӡdouble width */
    }
    else
    {
		CmdKp(KP_NORMAL);
        l *= 2;
	}
	//<<<<<<<<<<<
    if (cmd == 2)
		CmdKp(KP_RED);       /* red */
    else
		CmdKp(KP_BLACK);       /* black */

    while(l && *str)
    {
		if (*str == '~')    /* double size char */
			SendComm(ApplVar.KP.Prt->port-1, ' ');
		else
			SendComm(ApplVar.KP.Prt->port-1, CheckChar(*str));
		str++;          /* ApplVar.KP's are all Epson Compatible now */
		l--;
    }
//ccr2015-04-01    if (type == D76A_C)  /* Sprint */
//ccr2015-04-01		SendComm(ApplVar.KP.Prt->port-1, 0x0d);
//ccr2015-04-01    else
		SendComm(ApplVar.KP.Prt->port-1, LF);

}

void PrintPbKp(BYTE kp)
{
    BCD num;
    BYTE type;

    MemSet(SysBuf, sizeof(SysBuf), ' ');
    if (ApplVar.PbNumber)
    {
		type = ApplVar.KP.Prt->type & 0x0f;
        {
            num = ZERO;
            SysBuf[0] = 15;
            if (ApplVar.AP.Pb.Random & 0x0f)
            {
                memcpy(num.Value, ApplVar.PB.Random, ApplVar.AP.Pb.Random & 0x0f);
                if ((ApplVar.AP.Pb.Random & 0x0f) > 3)
                    SysBuf[0] = 20;
            }
            else
                WORDtoBCD(num.Value, ApplVar.PbNumber);
            FormatQtyStr(Msg[ZUOHAO].str, &num, SysBuf[0]);
        }
		if (type == 1 || !kp)  /* internal */
		    PrintStr(SysBuf);
		else
		    PrintKp(KP_DBLWIDTH, SysBuf);
//ccr2017-02-07		if (ApplVar.AP.Pb.Text && TESTBIT(KPPRICE, BIT6))
        if (ApplVar.AP.Pb.Text && ApplVar.PB.Text[0] && TESTBIT(KPPRICE, BIT6))
		{
		    RESETBIT(ApplVar.PrintLayOut, BIT2);
		    PrintKp(KP_NORMAL, ApplVar.PB.Text);
		}
    }
/*ccr2014-04-01>>>>>>>
    else
    {//δ��̨ʱ����ӡ������Ϣ
		strcpy(SysBuf, Msg[CWXXI11].str);//ccr2014-04-01
		PrintKp(KP_NORMAL, SysBuf);
		DispSt1C(SysBuf);//hf 20060105 DispSt2C(SysBuf);
    }
<<<<<*/
}
/**
 * �ڳ�����ӡ���ϴ�ӡƱͷ
 *
 * @author EutronSoftware (2014-04-01)
 */
void KpHeader()
{
    BYTE type;
    int l,i,w;

    type = ApplVar.KP.Prt->type & 0x0f;
    if (type > 1)  /* epson compatible external */
    {//����Ϊ������ӡ
		w = KPWidth[type-2]*2;
		CmdKp(KP_NORMAL);//ccr2017-02-08
//		SendComm(ApplVar.KP.Prt->port-1, 0x1b);
//		{
//			SendComm(ApplVar.KP.Prt->port-1, 'R');
//			SendComm(ApplVar.KP.Prt->port-1, CHARSET & 0x0f);
//		}
    }
    else if (type)
	{
		w = PRTLEN;

		PrintHead1(PREHEADER);
		RFeed(1);
	}
    else //ccr2017-02-07
        return;
    ApplVar.PrintLayOut = 0x02;     /* for ApplVar.KP no double heigth */
    if (TESTBIT(KPPRICE, BIT1))
    {
        //ccr2014-04-01>>>>>>>>
        if (PRNINDEX)
        {//��ӡȡ�˺�
            memset(ProgLineMes,' ',w);
            l = strlen(Msg[mPRNINDEX].str)+10;
            i = (w-l)/2;//���õ��м�
            CopyFrStr(ProgLineMes+i,Msg[mPRNINDEX].str);
            l = l-10+i+1;
//ccr2016-04-20            l+=WORDtoASCL(ProgLineMes+l,REGISTER);
//ccr2016-04-20            ProgLineMes[l]='-';
//ccr2016-04-20            l++;
            HEXtoASC(ProgLineMes+l, ApplVar.ReceiptNumber, 3);
            ProgLineMes[l+6]=0;
            PrintKp(KP_DBLHIGH, ProgLineMes);//���ߴ�ӡ
        }
        //<<<<<<<<<<<<<<<<<<<<<
		//ccr2014-04-01 if (ApplVar.PbNumber || Msg[CWXXI19].str[0]) /* text programmed */
		{
		    PrintPbKp(1);
		    MemSet(SysBuf, sizeof(SysBuf), '=');
		    PrintKp(KP_NORMAL, SysBuf);
		}
    }
    else //ccr2017-02-07if (Msg[CHFDYJHAO].str[0])
    {
		MemSet(SysBuf, sizeof(SysBuf), '-');
		PrintKp(KP_NORMAL, SysBuf);
    }
    //ccr2017-02-07if (Msg[CHFDYJHAO].str[0])
    {
		MemSet(SysBuf, sizeof(SysBuf), ' ');
        l = strlen(Msg[CHFDYJHAO].str);
		memcpy(SysBuf + 2, Msg[CHFDYJHAO].str,l);
		WORDtoASC(SysBuf + 2 + l,ApplVar.KP.Number+1);
		PrintKp(KP_NORMAL, SysBuf);
		MemSet(SysBuf, sizeof(SysBuf), '-');
		PrintKp(KP_NORMAL, SysBuf);
    }
    if (type > 1)
		SendComm(ApplVar.KP.Prt->port-1, LF);
}

void IssueKp()
{
    BYTE type;
    int i;

    type = ApplVar.KP.Prt->type & 0x0f;// (0-�޳�����ӡ��,1-���ô�ӡ��)
    if (!type)     /* not programmed */
        return;
    if (ApplVar.FTrain)     /* training ? */
    {
		MemSet(SysBuf, sizeof(SysBuf), ' ');
		strcpy(SysBuf + 5, Msg[PXZHTAI].str);
		PrintKp(KP_BLACK, SysBuf);
    }
    MemSet(SysBuf, sizeof(SysBuf), ' ');
    GetReceiptNumber(SysBuf);
    i = 8;
	if (type == T80A_C)//Ϊ���д�ӡ
    {
        if (REGISTER)
        {
            SysBuf[i++] = 'R';      /* register number */
            i+=WORDtoASCL(SysBuf + i, REGISTER);
            i++;
        }
        if (LOCATION)
        {
            SysBuf[i++] = 'L';      /* location number */
            i+=WORDtoASCL(SysBuf + i, LOCATION);
            i++;
        }
    }
    CopyFrStr(SysBuf + i, ApplVar.Clerk.Name);
	PrintKp(KP_NORMAL, SysBuf);

    MemSet(SysBuf, sizeof(SysBuf), ' ');
	i = DateTimeToStr(SysBuf,false)+1;

    if (type != T80A_C)  /* Sprint */
    {
        if (REGISTER)
        {
            SysBuf[i++] = 'R';      /* register number */
            i+=WORDtoASCL(SysBuf + i, REGISTER);
            i++;
        }
		if (LOCATION)
		{
		    SysBuf[i++] = 'L';      /* location number */
		    i+=WORDtoASCL(SysBuf + i, LOCATION);
		}
		SysBuf[i] = 0;
    }
    PrintKp(KP_NORMAL, SysBuf);
    //ccr2017-02-08>>>>>
    if (KpCmd[type-2][KP_CUTF][0])
    {//���е�,��ֽ����ֽλ��
        i=KPCutFeed[type-2];
        while(i)
        {
    		SendComm(ApplVar.KP.Prt->port-1, LF);
    		i--;
        }
        CmdKp(KP_CUTF);   /* Cute paper */
        Delay(100);             /* delay incase all ApplVar.KP got to same PHYSICAL ApplVar.KP */
    }
    else
    {//���е�ʱ,�ߵ�˺ֽλ��
        for (i=0;i<8;i++)
        {
            SendComm(ApplVar.KP.Prt->port-1, LF);
        }
    }
    //ccr2017-02-07<<<<<<<
	WaitOnLine(ApplVar.KP.Prt->port-1);
}

void KpEnd(BYTE kp)
{
    BYTE type;
    char Nil[1];

    Nil[0]=0;

    type = ApplVar.KP.Prt->type & 0x0f;
    if (type == 1 || !kp)
		RFeed(1);
    else if (type)
		PrintKp(KP_NORMAL, Nil);     /* empty line normal heigth */
    if (!TESTBIT(KPPRICE, BIT1) || !kp)
		PrintPbKp(kp);
    if (type == 1 || !kp)
    {
		ApplVar.PrintLayOut = 0x02;
		ReceiptIssue(0);
    }
    else if (type)//ccr2017-02-07
		IssueKp();
}

void PrintArticle(BYTE cmd, BYTE kp)
{
    char temp[18];
    int i;
    BYTE *item;

    MemSet(SysBuf, sizeof(SysBuf), ' ');
    if (!TESTBIT(KPPRICE, BIT1)) /* new German System? */
    {
		item = (BYTE *)ApplVar.Dept.Name;
        i=16;  temp[0]=cmd;//ccr2017-02-07
		if (ApplVar.RGRec.Key.Code > PLU1) /* plu ? */
		{
		    if (ApplVar.AP.Plu.CapSize)         /* when programmed always print PLU  */
					item = (BYTE *)ApplVar.Plu.Name;
		    if (TESTBIT(KPPRICE, BIT3) /* Print PLU Number on KP*/
				&& ApplVar.AP.Plu.RandomSize < 3)
		    {
                i = 22; temp[0]=KP_NORMAL;//ccr2017-02-07
				if (ApplVar.AP.Plu.RandomSize)
				    HEXtoASC(SysBuf + sizeof(SysBuf) - 20,
				     ApplVar.Plu.Random, ApplVar.AP.Plu.RandomSize);
				else
				    WORDtoASCZero(SysBuf + sizeof(SysBuf) - 17, ApplVar.PluNumber + 1);
				if ((CHARSET & 0xf0) == 0x10 || (SLIP != 4 &&
				    ((CHARSET & 0x0f) == 3 || (CHARSET & 0x0f) == 7)
				     ))  /* number sign not available */
				    SysBuf[sizeof(SysBuf) - 21] = 'N';
				else
				    SysBuf[sizeof(SysBuf) - 21] = '#';
		    }
		}
		if ((ApplVar.Qty.Sign & 0x03) || (CompareBCD(&ApplVar.Qty, (BCD*)&ONE) > 0)
		    || TESTBIT(KPPRICE, BIT2+BIT3))  /* print price */
		{
		    FormatQty(SysBuf + sizeof(SysBuf) - 11, &ApplVar.Qty);
		    if (TESTBIT(KPPRICE, BIT2))  /* print price */
				FormatAmt(SysBuf + sizeof(SysBuf) - 2, &ApplVar.Price);
		    SysBuf[sizeof(SysBuf) - 9] = 'X';
		    SysBuf[sizeof(SysBuf) - 1] = 0;
		    if (kp)
				PrintKp(temp[0], SysBuf + sizeof(SysBuf) - i);
		    else
				PrintStr(SysBuf + sizeof(SysBuf) - i);
		    MemSet(SysBuf, sizeof(SysBuf), ' ');
		}
		if (!TESTBIT(KPPRICE, BIT3) /* Not Print PLU Number on ApplVar.KP */
		    && ApplVar.RGRec.Key.Code > PLU1)
				item = (BYTE *)GetPluPrint(temp, cmd);
		if (kp)
		    PrintKp(cmd, item);
		else
		    PrintStr(item);
	}
    else
    {
		if ((ApplVar.Qty.Sign & 0x03) || (CompareBCD(&ApplVar.Qty, (BCD*)&THOUSAND) >= 0))
		{//��С����������>1000ʱ,��������һ��
		    FormatQty(SysBuf + sizeof(SysBuf) - 10, &ApplVar.Qty);
		    SysBuf[sizeof(SysBuf) - 8] = 'X';
		    SysBuf[sizeof(SysBuf) - 7] = 0;
		    if (kp)
				PrintKp(cmd, SysBuf + sizeof(SysBuf) - 20);
		    else
				PrintStr(SysBuf + sizeof(SysBuf) - 20);
		    MemSet(SysBuf, sizeof(SysBuf), ' ');
		}
		else
		    FormatQty(SysBuf + 2 , &ApplVar.Qty);
		if (ApplVar.RGRec.Key.Code > PLU1) /* plu ? */
			memcpy(SysBuf + 4, (BYTE *)GetPluPrint(temp, cmd), ApplVar.AP.Plu.CapSize);
		else
			memcpy(SysBuf + 4, ApplVar.Dept.Name, ApplVar.AP.Dept.CapSize);
		SysBuf[PRTLEN] = 0; /* terminate */
		if (kp)
		    PrintKp(cmd, SysBuf);//�ڳ�����ӡ���ϴ�ӡ������
		else
		    PrintStr(SysBuf);
    }
}
//ccr2016-01-12>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void ReadKP()
{
    struct PRINTER *SetKP;
    SetKP = (struct PRINTER *) &KPSTART;
    SetKP = SetKP+ListRecord.Number;
    strcpy(ListRecord.Name,KPType[SetKP->type & 0x0f]);//ccr2014-04-01
}

//ccr2016-12-14>>>>>>>>>>>>>>>>>>>>>>>>>
/*****************************************************************************
 * ��Ҫ��ӡ�����ݷ��͸����ô�ӡ��
 *
 * @param cmd :���߻�����
 * @param str :Ҫ��ӡ���ַ���
 * @param selePRN :0-Ϊ�������,1-Ϊ���ô��ڴ�ӡ��(ӭ���������)
 ***************************************************************************/
void SendExtPrinter(BYTE cmd,BYTE *str,BYTE selePRN)
{
	BYTE ch,dbl,doublFlag=0,port,type;
	int l;
#if (defined(CASE_FORHANZI))
    int  hz=0;
#endif
#if defined(CASE_INNERDOTPRN)
    if (selePRN==0)//ccr2017-08-31>>>>>>
    {
        port=DOTPRNPORT;
        type=DOTPRNTYPE;//������0�Ŵ�ӡ����ͬ
    }
    else
#endif
    {
        port=ApplVar.ExtPrinter.port-1;
        type=ApplVar.ExtPrinter.type;
        if (type<T58A_C)//�������ô�ӡ��
            return;       /* empty string */
    }//ccr2017-08-31<<<<<<<<<<<<<<<<<<<<

    if (str)
    {
        if (str[0]=='@')
        {
            cmd=KP_DBLHIGH;
            str++;
        }

        l = KPWidth[type-2]*2;//��ӡ���

        if (cmd==KP_DBLHIGH || cmd==CMDP_DR || TESTBIT(ApplVar.PrintLayOut,BIT2))
        {
            CmdExtPrinter(port,type,KP_DBLHIGH);/* ���ߴ�ӡ */
            doublFlag=1;
            dbl = KP_DBLHIGH;
        }
        else
        {
            dbl = KP_NORMAL;
        }

        ch = *str;
        while(ch && l>0)
        {
            if (!TESTBIT(doublFlag,BIT1) && ch == '~')    /* double size char */
            {
                CmdExtPrinter(port,type,KP_DBLWIDTH);/* �����ӡ */
                SETBIT(doublFlag,BIT1+BIT0);
            }
            else
            {
    #if (defined(CASE_FORHANZI))
                if (ch==' ')
                {
                    if (hz==0)
                        SendComm(port, ch);
                    else
                        hz--;
                }
                else
    #endif
                    SendComm(port, ch);
    #if (defined(CASE_FORHANZI))
                if (ch>0xa0)
                {
                    INVERTBIT(doublFlag,BIT7);
                    if (TESTBIT(doublFlag,BIT1+BIT7)==BIT1)
                    {
                        hz++;//ͳ�Ʊ����ָ���
                        l--;
                    }
                }
                else
                    RESETBIT(doublFlag,BIT7);
    #endif
                if (TESTBIT(doublFlag,BIT1+BIT7)==BIT1)    /* double size char */
                {
                    CmdExtPrinter(port,type,dbl);/* ������ӡ */
                    RESETBIT(doublFlag,BIT1);
                }
                l--;
            }
            str++;          /* ApplVar.KP's are all Epson Compatible now */
            ch = *str;
        }
        if (TESTBIT(doublFlag,BIT1+BIT0) || dbl!=KP_NORMAL)
            CmdExtPrinter(port,type,KP_NORMAL);/* ������ӡ */

    }
    //ccr2017-02-15>>>>>>>Ϊ����ָ���������ֽʱ����ֽ
    else if (type==D76A_C && selePRN)
        return;//����ֽ
    //ccr2017-02-15<<<<<<<�˴�ӡ������ֽǰ���Զ���ֽ����
    SendComm(port, LF);
}
/**
 * ���ô�ӡ����ֽ
 *
 * @author EutronSoftware (2017-02-15)
 */
void CutExtPrinter()
{
    if (ApplVar.ExtPrinter.port && KpCmd[ApplVar.ExtPrinter.type-2][KP_CUTF][0])
    {
        switch (ApplVar.ExtPrinter.type)
        {
        case CITIZEN:
            CmdExtPrinter(ApplVar.ExtPrinter.port-1,ApplVar.ExtPrinter.type,KP_FEED);
            CmdExtPrinter(ApplVar.ExtPrinter.port-1,ApplVar.ExtPrinter.type,KP_FEED);
        case T58B_C:
        case T58A_C:
        case T80A_C:
            CmdExtPrinter(ApplVar.ExtPrinter.port-1,ApplVar.ExtPrinter.type,KP_FEED);
            break;
        }
         CmdExtPrinter(ApplVar.ExtPrinter.port-1,ApplVar.ExtPrinter.type,KP_CUTF);/* ���ô�ӡ����ֽ */
    }
}

//ccr2017-08-31>>>>>>>>���ô��ڴ�ӡ��(ȡ��������ӡ��)�����ܺ�����>>>>>>>>>>>>
#if defined(CASE_INNERDOTPRN) //ccr2017-08-31

/**
 * �����ô�ӡ������һ���ֽ�����
 *
 * @author EutronSoftware (2014-12-15)
 *
 * @param byte
 */
void EXTPrnterSendByte(BYTE byte)
{
    Bios_PortWrite(DOTPRNPORT+1, &byte, 1, 1);
}
/****************************************************************************
 * ����ӡ���Ĺ���״̬
 *
 * @author EutronSoftware (2017-08-31)
 *
 * @param mode :0-�������ʵʱ�临λ
 *              1-ʵʱ����ӡ��,����״̬ѯ��ʱ,���ȴ���ӡ��Ӧ��
 *              2-��ʱ����ӡ��,����״̬ѯ��ʱ,�ȴ���ӡ��Ӧ��
 *
 * @return BYTE :return:0-Error found  1-no error
 *****************************************************************************/
BYTE CheckPrinter(BYTE mode)
{
//#define DOTPRNPORT 0	//testonly
#if !defined(DEBUGBYPC)
    static int chkTime=0;
    static BYTE chkState=0;
    int ret;

    while (GetCTS(DOTPRNPORT+1))
    {
        //�ȴ���ӡ���޴�
        chkTime=GetSystemTimer();
        if (ApplVar.ErrorNumber!=ERROR_ID(CWXXI39))
            ApplVar.ErrorNumber=ERROR_ID(CWXXI39);//��ӡ��æ
        CheckError(0);
    }
    if (ApplVar.ErrorNumber==ERROR_ID(CWXXI39))
        ApplVar.ErrorNumber=0;

    if (mode==0)
    {//��ʼ��
        chkTime=GetSystemTimer();
        chkState=0;
    }
    if (chkState==0)
    {//���ͼ���ӡֽ������
		EmptyComm(DOTPRNPORT);
        SendComm(DOTPRNPORT, ESC);
        SendComm(DOTPRNPORT,'v');
        chkState=1;//��ʾ�Ѿ����ͻ�ȡ��ӡֽ����
        chkTime=GetSystemTimer();
    }
    //chkState<>0ʱ.��ʾ�Ѿ������˼������
    if (mode==1)//Ϊʵʱ���,���ȴ���ӡ��Ӧ��
    {
        if (CheckComm(DOTPRNPORT) && (ret = ReadComm(DOTPRNPORT))!=-1)
        {
            if (ret==0x0c)//��ӡ����ֽ
                ApplVar.ErrorNumber=ERROR_ID(CWXXI40);
            else if (ret==0x00 && (ApplVar.ErrorNumber==ERROR_ID(CWXXI40) || ApplVar.ErrorNumber==ERROR_ID(CWXXI38)))//��ӡ����ֽ
                ApplVar.ErrorNumber=0;
            chkState=0;//��Ҫ���·��ͼ������
        }
        else if (GetSystemTimer()-chkTime>SECONDS(2))//��������Ӧ��,��Ϊ��ӡ������
        {
            ApplVar.ErrorNumber=ERROR_ID(CWXXI38);
            chkState=0;//��Ҫ���·��ͼ������
        }
    }
    else if (mode==2)//Ϊʵʱ���,����ȴ���ӡ��Ӧ����������
    {
        do
        {
            if (chkState==0)
            {
                EmptyComm(DOTPRNPORT);
                SendComm(DOTPRNPORT, ESC);
                SendComm(DOTPRNPORT,'v');
            }
            chkTime=GetSystemTimer();
            if ((ret = ReadComm(DOTPRNPORT))!=-1)
            {
                if (ret==0x0c)//��ӡ����ֽ
                    ApplVar.ErrorNumber=ERROR_ID(CWXXI40);
                else if (ret==0x00 && (ApplVar.ErrorNumber==ERROR_ID(CWXXI40) || ApplVar.ErrorNumber==ERROR_ID(CWXXI38)))//��ӡ����ֽ
                {
                    ApplVar.ErrorNumber=0;
                    CheckError(0);
                }
            }
            else// if (GetSystemTimer()-chkTime>2000)//��������Ӧ��,��Ϊ��ӡ������
            {
                ApplVar.ErrorNumber=ERROR_ID(CWXXI38);
            }

            chkState=0;//��Ҫ���·��ͼ������
            if (ApplVar.ErrorNumber==ERROR_ID(CWXXI40) || ApplVar.ErrorNumber==ERROR_ID(CWXXI38))
            {
                if (KbHit() && Getch()==ApplVar.AP.FirmKeys[ID_RJFEED])
                {
                    RFeed(1);
                }
                CheckError(0);
            }
            else
                break;
        } while (true);
    }
#endif
    return TRUE;
}
#endif

//ccr2017-08-31<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
