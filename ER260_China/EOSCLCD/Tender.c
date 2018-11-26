#define TENDER_C 5
#include "king.h"                               /* Kingtron library and I/O routines */
#include "exthead.h"
#include "exth.h"
#include "ePosCard.h"//cc epos
#if (defined(CASE_GPRS))
#include "Gprs.h"
#endif
#include "Message.h"


/*******************************************************************/

void GetTenderOffSet()
{
	RamOffSet = ApplVar.TendNumber * ApplVar.AP.Tend.RecordSize + ApplVar.AP.StartAddress[AddrTend];
}

void AddTenderTotal()
{
    GetTenderOffSet();
    RamOffSet += ApplVar.AP.Tend.TotalOffSet;
    for (ApplVar.PointerType = 0; ApplVar.PointerType < REPDEFMAX; ApplVar.PointerType++)
    {
		ApplVar.Size = ApplVar.AP.Tend.Size[ApplVar.PointerType];
		AddPointerTotal();
    }
}

void WriteTender()
{
    if (ApplVar.TendNumber < ApplVar.AP.Tend.Number)
    {
		GetTenderOffSet();

		WriteRam((BYTE*)&ApplVar.Tend, ApplVar.AP.Tend.TotalOffSet);      /* write function options */
    }
}

void ReadTender()
{
    GetTenderOffSet();

    ReadRam((BYTE*)&ApplVar.Tend, ApplVar.AP.Tend.TotalOffSet);	/* write function options */
	ApplVar.Tend.Name[ApplVar.AP.Tend.CapSize] = 0 ;
}


void Tender()
{
	BYTE	payIC=0;//ccr chipcard cc epos:=1ΪIC�� ��2 ΪePos //
	BCD		sSave,sTotal;
	BYTE	sEntryCou;
	WORD	sKeyCode;
#if (DD_CHIPC==1)
    BCD		sIC_AMT;//���IC�ڵĽ������,
#endif


//ccr2016-06-22..........................................
#if (defined(CASE_QRCODE) && !defined(DEBUGBYPC))
#if !defined(CASE_INNERDOTPRN)
    if (ApplVar.Key.Code==TEND_WXPAY || ApplVar.Key.Code==TEND_ALPAY)
    {
        sKeyCode=ApplVar.Key.Code-TEND_WXPAY;
        if (ApplVar.QRCode[sKeyCode][0])
        {
            Create_QR_MAP(ApplVar.QRCode[sKeyCode]);
            sKeyCode=QRCODE_GRP_ID;
            Bios(BiosCmd_PrintGraph, (void*)sKeyCode, 0 , 0); //Stampa msg ram
            RFeed(3);
            if (!WaitForYesNo(MESSWXPAY,false))
            {
                return;
            }
        }
    }
#endif
#endif


	if (TESTBIT(CLERKFIX,BIT7) && !ApplVar.FSub && !ApplVar.FTend)//ccr101111
	{
		ApplVar.ErrorNumber=ERROR_ID(CWXXI46);
		return;
	}

	if (ApplVar.FRefund==1 && ApplVar.FRegi==0)
	{//ccr 050111
		ApplVar.ErrorNumber=ERROR_ID(CWXXI01);
		ApplVar.FRefund = 0;
		return;
	}

#if (CASE_EPOS)
    if (ApplVar.Key.Code == (TEND + 5) && !ApplVar.ePosPort)
	{//cc epos
		ApplVar.ErrorNumber=ERROR_ID(CWXXI01);
		return;
	}
#endif

#if (DD_CHIPC==1)
//Ccr chipcard>>auto discount>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    //����ʹ���ֽ����ȡ��IC������
    if (ApplVar.IC.CHIP_Flag>0 && !Appl_EntryCounter && ApplVar.Key.Code==TEND+1  && TESTBIT(ApplVar.IC.ICState,IC_INSERT)//ccr2014-03-21
		&& TESTBIT(ApplVar.ICCardSet.Options,IC_TOT_CC))//ccr chipcard
		ApplVar.Key.Code = TEND_CHIPC;//ChipCard payment
	else if (ApplVar.Key.Code == TEND_CHIPC && (ApplVar.IC.CHIP_Flag<=0 || !TESTBIT(ApplVar.IC.ICState,IC_INSERT)))//ccr2014-03-21
	{
		ApplVar.ErrorNumber=ERROR_ID(CWXXI50);
		return;
	}

#if defined(TEND_PREFIX)//ccr2016-08-08
    Prefix1 = PREFIX_1;
    Prefix2 = PREFIX_2;
#endif

	if ((ApplVar.IC.CHIP_Flag==0 || (ApplVar.IC.CHIP_Flag==1 || ApplVar.IC.CHIP_Flag==2) && ApplVar.Key.Code == TEND_CHIPC)
		 && !TESTBIT(ApplVar.IC.ICState,IC_DISCOUNT) && TESTBIT(ApplVar.ICCardSet.Options,IC_DISCOUNT)  && ApplVar.FRegi//ccr040809
		&& CWORD(ApplVar.IC.REC_Customer[CC_CPERC])!=0 ) //ccr chipcard
	{
			SETBIT(ApplVar.IC.ICState,IC_DISCOUNT);
			sSave = ApplVar.Entry;
			sEntryCou = Appl_EntryCounter;
			sKeyCode = ApplVar.Key.Code;
			Appl_EntryCounter = 0;
			if (!ApplVar.FSub)
			{
				ApplVar.Key.Code = SUB;
				Fixed();
			}
			for (ApplVar.DiscNumber=0;ApplVar.DiscNumber<ApplVar.AP.Disc.Number;ApplVar.DiscNumber++)
			{
				GetDiscOffSet();
				ReadDisc();
				if (ApplVar.Disc.Options==0x11)  //Discount %
					break;
			}
			if (ApplVar.DiscNumber >= ApplVar.AP.Disc.Number);
				ApplVar.DiscNumber = 1;

			ApplVar.Key.Code = ApplVar.DiscNumber + DISC + 1;
			Appl_EntryCounter = 0;
			icBCD2EcrBCD(&ApplVar.Entry,(char*)&ApplVar.IC.REC_Customer[CC_CPERC], 2);
			Discount();
			ApplVar.Key.Code = sKeyCode;
			Appl_EntryCounter = sEntryCou;
			ApplVar.Entry = sSave;
	}
#endif

#if (BARCUSTOMER==1)
	if ((ApplVar.Key.Code != TEND_CHIPC) && ApplVar.BarCustomer.OFFIndex>0 && ApplVar.BarCustomer.DeptHi==0 && !TESTBIT(ApplVar.BarCustomer.Dept,BIT0))
	{// ʹ�������Ա���ۿ۹���  //
			SETBIT(ApplVar.BarCustomer.Dept,BIT0);
			sSave = ApplVar.Entry;
			sEntryCou = Appl_EntryCounter;
			sKeyCode = ApplVar.Key.Code;
			Appl_EntryCounter = 0;
			if (!ApplVar.FSub)
			{
				ApplVar.Key.Code = SUB;
				Fixed();
			}
			for (ApplVar.DiscNumber=0;ApplVar.DiscNumber<ApplVar.AP.Disc.Number;ApplVar.DiscNumber++)
			{
				GetDiscOffSet();
				ReadDisc();
				if (ApplVar.Disc.Options==0x11)  //Discount %
					break;
			}
			if (ApplVar.DiscNumber >= ApplVar.AP.Disc.Number);
				ApplVar.DiscNumber = 1;

			ApplVar.Key.Code = ApplVar.DiscNumber + DISC + 1;
			Appl_EntryCounter = 0;
			ApplVar.Entry = ZERO;
			ApplVar.Entry.Value[0] = ApplVar.BarCustomer.Price[1][0];
			ApplVar.Entry.Value[1] = ApplVar.BarCustomer.Price[1][1];

			Discount();
			ApplVar.Key.Code = sKeyCode;
			Appl_EntryCounter = sEntryCou;
			ApplVar.Entry = sSave;
	}
#endif
	if (ApplVar.FSub || ApplVar.FTend)//ccr2014-12-22
		sSave = ApplVar.SubTotal;
	else
		sSave = ApplVar.SaleAmt;

#if (BARCUSTOMER==1)
	if ((ApplVar.Key.Code != TEND_CHIPC) && ApplVar.BarCustomer.OFFIndex>0)
	{// ͳ�������Ա�������ܶ�  //
		sTotal = ZERO;
		memcpy(sTotal.Value,&ApplVar.BarCustomer.Price[0],5);
		Add(&sTotal,&sSave);
		memcpy(&ApplVar.BarCustomer.Price[0],sTotal.Value,5);
		ApplVar.PluNumber = ApplVar.BarCustomer.OFFIndex-1;
		ApplVar.Plu = ApplVar.BarCustomer;
		WritePlu();
	}
#endif


#if (DD_CHIPC==1)
    if ((ApplVar.IC.CHIP_Flag==0 || (ApplVar.IC.CHIP_Flag>0 && ApplVar.Key.Code == TEND_CHIPC)) &&
        ApplVar.FRegi && CheckNotZero(&sSave))//Chipcard payment 040805
   	{
	    if (!Appl_EntryCounter)//Chipcard payment 040805
		{
            //ccr2014-12-26>>>>>>>>>>>>>>>>>>>>>>
            PayByChipCard(&sSave,&sIC_AMT,FALSE);//���Կ��Ͻ���Ƿ��㹻���� //
			if (ApplVar.ErrorNumber)
            {
                if(ApplVar.ErrorNumber==ERROR_ID(CWXXI69) && CheckNotZero(&sIC_AMT))
                {//�Ƿ�ʹ�ÿ��ڽ���������
                    CheckError(0);
                    ScrollScreen(1);
                    DispStrXY((char*)cMESS_PAYALSO,0,SCREENLN-2);
                    SetLoop();
                    while (!KbHit())
                    {
#if (CASE_MFRIC==1)
                        if(!CC_MFRCard())// ���Կ��Ƿ�ȡ��  //
#else
                        if (!CC_Insert())// ���Կ��Ƿ�ȡ��  //
#endif
                        {
                            ResetLoop();
                            ClearLine(SCREENLN-2);
                            ApplVar.ErrorNumber=ERROR_ID(CWXXI72);
                            return;
                        }
                    }
                    sEntryCou = Getch();
                    ResetLoop();
                    if (sEntryCou==ApplVar.AP.FirmKeys[ID_ENTER])
                        ApplVar.ErrorNumber =0;
                    else
                        return;
                }
                else
    				return;
            }
            else
            {
                sIC_AMT.Sign=0xff;//��ʶ����㹻����
            }//ccr2014-12-26<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		}

		if (!TESTBIT(ApplVar.IC.ICState,IC_POINTS))//ccr 040805
		{
			if (!TESTBIT(sSave.Sign, BIT7))
			{
				if (TESTBIT(ApplVar.ICCardSet.Options,IC_REPORT))
					payIC = 1;
				PointsByChipCard(&sSave);
                ECRVIP.ECRVIPState=0;//����IC��Ա��ECRVIP��Ա�ظ��Ƶ�
			}
		}
   	}
//ccr chipcard<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif
#if (DD_ECRVIP==1)
    if (TESTBIT(ECRVIP.ECRVIPState,VIP_LOGIN+VIP_POINTS)==VIP_LOGIN && TESTBIT(ApplVar.ICCardSet.Options,IC_POINTS) &&
        ApplVar.FRegi && CheckNotZero(&sSave) && !TESTBIT(sSave.Sign, BIT7))//Chipcard payment 040805
    {
        PointsByECRVIP(&sSave);
    }
#endif

    ApplVar.TendNumber = ApplVar.Key.Code - TEND - 1;
    if (ApplVar.TendNumber < ApplVar.AP.Tend.Number)
	{
		ReadTender();		/* read function */
	}
    else
    {
		ApplVar.ErrorNumber=ERROR_ID(CWXXI42);
		return;
    }
    if ((TESTBIT(PBINFO, BIT3) && ApplVar.FPb) || TESTBIT(ApplVar.FNoPb, BIT1))       /* pb used ? */
    {
		ApplVar.ErrorNumber=ERROR_ID(CWXXI07);
		return;
    }

    if (!Appl_EntryCounter)
    {
		if(TESTBIT(ApplVar.Tend.Options, BIT1) && !ApplVar.FRefund)   /* entry compulsory ? */
		{
			if (!TESTBIT(ApplVar.SaleAmt.Sign, BIT7))	/* negative then allowed */
			{
			    ApplVar.ErrorNumber=ERROR_ID(CWXXI43);
				return;
			}
		}
    }
    else
    {
		if (TESTBIT(ApplVar.Tend.Options, BIT2) && !ApplVar.FRefund)   /* no entry allowed ? */
		{
		    ApplVar.ErrorNumber=ERROR_ID(CWXXI04);
		    return;
		}
    }
    if (AmtInputMask())
		return;
    if (ApplVar.FRegi)
    {
		if (TESTBIT(ApplVar.Tend.Options, BIT3) && !ApplVar.FNum)   /* number entry ? */
		{
#if defined(CASE_INDIA)//ccr2016-05-31>>>>>>>>>>>>>
            //��Ҫ�������,����ApplVar.NumberEntered��
            //sSave = ApplVar.Entry;
            //sKeyCode = ApplVar.Key.Code;

            sEntryCou = Appl_EntryCounter;
            mClearScreen();
            DispStrXY(Msg[SHRHMA].str,0,0);
            if  (GetStrFrKBD('9',SCREENWD-12,1,12,0)>0)
            {
                StrToBCDValue(ApplVar.NumberEntered.Value, &EntryBuffer[ENTRYSIZE - 2], BCDLEN);
                Collect_Data(NOADDLOG);
                ApplVar.FNum=1;
                Appl_EntryCounter=sEntryCou;
                //ApplVar.Entry=sSave;
                //ApplVar.Key.Code=sKeyCode;
            }
            else
#endif//ccr2016-05-31<<<<<<<<<<<<<<<<<
            {
                ApplVar.ErrorNumber=ERROR_ID(CWXXI30);
                return;
            }
		}
    }
    if (ApplVar.FRefund)
    {
		if (ApplVar.FCurr || ApplVar.FCanc || !Appl_EntryCounter)
		{
		    ApplVar.ErrorNumber=ERROR_ID(CWXXI01);
		    return;
		}
		if (RegiStart())
		{
		    return;
		}
		ApplVar.SubTotal = ApplVar.Entry;
		Add(&ApplVar.SubTotal, &ApplVar.Entry);
		ApplVar.FTend = 1;
		ApplVar.FRegi = 1;
		Collect_Data(REGISLOG);
    }

    if (ApplVar.PbNumber)
		ApplVar.Tend.Print = ApplVar.PbF.Print;

    ApplVar.PrintLayOut = ApplVar.Tend.Print;
    if (TESTBIT(ApplVar.Tend.Options, BIT5))   /* if set no tax calc */
		ApplVar.FNoTax = 1;

#if (CASE_EPOS)
    //cc epos>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	if (!Appl_EntryCounter && ApplVar.Key.Code == TEND + 5  && ApplVar.ePosPort
		&& CheckNotZero(&sSave) && ApplVar.FRegi && ApplVar.FRefund==0)
	{//ʹ��ePos ���� //

		AmtRound(0, &sSave); 	/* total sales rounding */
		if ((sSave.Sign & 0x80) || BCDWidth(&sSave)>=8 || PayByePosCard(&sSave)!=SUCCESS)
		{
			ApplVar.ErrorNumber=ERROR_ID(CWXXI70);
			return;
		}
		else
			payIC = 2;//ΪePos����  //
	}
//cc epos<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif

    if (!ApplVar.FTend)   /* already in tender ? */
    {
        mClearScreen();
		if (ApplVar.FRegi)   /* registration */
		{
		    CalculateTax(0);	    /* calculate and add report */
		    ApplVar.BufKp = 1;		    /* set ApplVar.KP not printed yet */
		    if (ApplVar.PbNumber)
		    {
				ClearPb();
				if (TESTBIT(PBINFO, BIT4))
				    AddReceiptNumber();
				AmtRound(0, &ApplVar.SubTotal); 	/* total sales rounding */
				if (TESTBIT(ApplVar.FNoPb, BIT2))   /* store ApplVar.PbInvoice ? */
				{
				    StorePbInvoice(0);
				}
		    }
		}
		else
		    CalculateTax(1);	    /* calulate and not add report */
    }


    if (!Appl_EntryCounter)
    {
#if (DD_CHIPC==1)
//ccr2014-12-26 chipcard>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	    if (ApplVar.IC.CHIP_Flag>0 && (ApplVar.Key.Code == TEND_CHIPC) && ApplVar.FRegi
			&& CheckNotZero(&ApplVar.SubTotal))//Chipcard payment 040805
		{
            if (sIC_AMT.Sign!=0xff)
            {//ʹ��IC���е�ȫ�������и���
                PayByChipCard(&sIC_AMT,0,TRUE);
                Appl_EntryCounter=1;//BCDWidth(&sIC_AMT);//�������������
                ApplVar.Entry=sIC_AMT;
                ApplVar.Amt=sIC_AMT;
            }
            else//IC��������Ը���.
                PayByChipCard(&ApplVar.SubTotal,0,TRUE);
			if (ApplVar.ErrorNumber)
			{
				ApplVar.IC.CHIP_Flag = RD_ChipCard();
				return;
			}
			if (TESTBIT(ApplVar.ICCardSet.Options,IC_REPORT))
				payIC = 1;
		}
        if (!Appl_EntryCounter)//<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif
        {
            ApplVar.Entry = ApplVar.SubTotal;
            ApplVar.Amt = ApplVar.SubTotal;
            if (ApplVar.FCurr)
                GetCurrency(0, &ApplVar.Entry);	  /* subtotal to currency */
        }
    }
    else
    {
//		ApplVar.Entry.Sign = ApplVar.SubTotal.Sign;
		ApplVar.Amt = ApplVar.Entry;	/* entry has sign of total positive */
		if (ApplVar.FCurr)
		    GetCurrency(1, &ApplVar.Amt);	/* entry to local */
    }
    if (ApplVar.FCurr)
		ApplVar.AmtDecimal = ApplVar.Curr.Options & BIT0;   /* decimal in amount ? */
    if (Appl_EntryCounter)
    {
		if (CompareBCD(&ApplVar.SubTotal, &ApplVar.Amt) < 1)	/* overtendering ? */
		{
		  RESETBIT(ARROWS, BIT1); /* reset RG led */
		    if (TESTBIT(ApplVar.Tend.Options, BIT4))   /* overtender is tipp? */
		    {
#if defined(LCD10_DISP)
                LCD10_SetFlag(FLAG_TOTAL);
                PutsO(DispAmtStr(0, &ApplVar.Entry,DISLEN));//C-DISPLAY
#else
				if (ApplVar.FCurr)
				{
				    PutsO(DispAmtStr(Msg[CURRENCY].str, &ApplVar.Entry,DISLEN));//C-DISPLAY????
				}
				else
				{
				    PutsO(DispAmtStr(Msg[TOTALMSG].str, &ApplVar.Entry,DISLEN));//C-DISPLAY????
				}
#endif
		    }
		    else
		    {//��ʾ������
				ApplVar.AmtDecimal = NO_DECIMAL;     /* local format */
				ApplVar.Price = ApplVar.Amt;
				Subtract(&ApplVar.Price, &ApplVar.SubTotal);

#if defined(LCD10_DISP)
                LCD10_SetFlag(FLAG_CHANGE);
                PutsO(DispAmtStr(0, &ApplVar.Price,DISLEN));//C-DISPLAY
#else
				PutsO(DispAmtStr(Msg[CHANGE].str, &ApplVar.Price,DISLEN));//C-DISPLAY????
#endif
		    }
		    if (!ApplVar.FRegi)       /* registration */
				ApplVar.FTend = 0;
		}
		else
		{		    /* undertendering */
		    ApplVar.Price = ApplVar.SubTotal;
		    ApplVar.AmtDecimal = NO_DECIMAL;
		    Subtract(&ApplVar.Price, &ApplVar.Amt);
#if defined(LCD10_DISP)
            LCD10_SetFlag(FLAG_TOTAL);
            PutsO(DispAmtStr(0, &ApplVar.Price,DISLEN));//C-DISPLAY
#else
		    PutsO(DispAmtStr(Msg[SUBTOTAL].str, &ApplVar.Price,DISLEN)); /* ��ʾ������� *///C-DISPLAY
#endif
#if (SCRSTATDBL)
            DispOnStatDBL(DispAmtStr(Msg[DAIFU].str, &ApplVar.Price,SCRDBLWD),0);
#else
            DispSt0(DispAmtStr(Msg[DAIFU].str, &ApplVar.Price,SCREENWD));/* ��ʾ������� */ //RG-DISPLAY
//ccr2016-03-04            StrForST0 = ApplVar.ModeHead;//(char*)Msg[SHURU].str;
#endif
		    if (!ApplVar.FRegi)
		    {
				ApplVar.FTend = 1;
				ApplVar.SubTotal = ApplVar.Price;
		    }
		}
    }
    else if (ApplVar.FRegi || ApplVar.FTend) /* registration or tender ? */
    {
		RESETBIT(ARROWS, BIT1); /* reset RG led */
#if defined(LCD10_DISP)
        LCD10_SetFlag(FLAG_TOTAL);
        PutsO(DispAmtStr(0, &ApplVar.Entry,DISLEN));//C-DISPLAY
#else
		if (ApplVar.FCurr)
		{
		    PutsO(DispAmtStr(Msg[CURRENCY].str, &ApplVar.Entry,DISLEN));//C-DISPLAY????
		}
		else
		{
		    PutsO(DispAmtStr(Msg[TOTALMSG].str, &ApplVar.Amt,DISLEN));//C-DISPLAY????
		}
#endif
		if (!ApplVar.FRegi)
		    ApplVar.FTend = 0;
    }

    if (ApplVar.FRegi)	 /* registration */
	{
		ApplVar.AmtDecimal = NO_DECIMAL;
		if (TESTBIT(ApplVar.Tend.Options, BIT0)) /* open drawer ? */
		    ApplVar.OpDraw = 1;
		if (ApplVar.FRecIssue)
		{
		    NewReceipt();
		    RESETBIT(ApplVar.PrintLayOut, BIT1);
		    RESETBIT(ApplVar.Tend.Print, BIT1);
		}
		ApplVar.FRecIssue = 0;
		StoreInBuffer();//��������۵���Ŀ����RGBuf��
		ApplVar.RGRec.Key.Code = 0;
		if (!ApplVar.FTend)   /* already in tender ? */
		{

		    ApplVar.Price = ApplVar.Amt;    /* save ApplVar.Amt */
		    RegiEnd();
			ApplVar.FSale = 0;
		    ApplVar.Amt = ApplVar.Price;
		    ApplVar.PrintLayOut = ApplVar.Tend.Print;	    /* restore print */
		    ApplVar.RGRec.Key.Code = 299;    /* end transaction */
		    StoreInBuffer();
		    ApplVar.RGRec.Key.Code = 0;
		    ApplVar.FTend = 1;
		}

		if (TESTBIT(ApplVar.Tend.Options, BIT3) && ApplVar.FNum == 1)	 /* number entry ? */
		    PrintNumber(&ApplVar.NumberEntered);
		ApplVar.FNum = 0;

		ApplVar.Price = ZERO;
		if (Appl_EntryCounter)
		{
		    if (CompareBCD(&ApplVar.SubTotal, &ApplVar.Amt) < 1 ||((ApplVar.SubTotal.Sign & 0x80) == 0x80 && (ApplVar.Amt.Sign & 0x80) == 0))	/* overtendering ? */
		    {//���踶��������(����Ľ���������֧�����)
				Subtract(&ApplVar.Amt, &ApplVar.SubTotal);  /* calculate change */

				if (ApplVar.Tend.Over && TESTBIT(ApplVar.Tend.Options, BIT4))	/* overtender is tipp? */
				{
				    ApplVar.DrawNumber = ApplVar.Tend.Over - 1;    /* add tip */
				    ReadDrawer();
				    PrintAmt(ApplVar.Draw.Name, &ApplVar.Amt);
					ApplVar.RGRec.Key.Code = DRAW+ApplVar.Tend.Over;	/* store overtender */
					ApplVar.RGRec.Amt = ApplVar.Amt;
					ApplVar.RGRec.Amt.Sign ^= 0x80;
					ApplVar.RGRec.Qty = ONE;
					StoreInBuffer();
					ApplVar.RGRec.Key.Code = 0;
				    ApplVar.Price = ApplVar.Entry;
					if (ApplVar.FCurr)
						Add(&ApplVar.Price, &ApplVar.Amt);	/* Add ApplVar.Entry in ApplVar.Report */
				}
				else
			    	ApplVar.Price = ApplVar.SubTotal;
				if (ApplVar.FCurr)
				{
				    PrintStr(ApplVar.Curr.Name);
				    ApplVar.AmtDecimal = ApplVar.Curr.Options & BIT0;
				    Prefix1 = ApplVar.Curr.Prefix1;
				    Prefix2 = ApplVar.Curr.Prefix2;
				    GetCurrency(0, &ApplVar.Price); /* calculate currency */
				}


				if (!TESTBIT(ApplVar.Tend.Options, BIT4))   /* overtender is tipp? */
				    PrintAmt(Msg[SHOUQU].str, &ApplVar.Entry);  //��ӡ��ȡ�Ľ��
				else//ccr20130417
					PrintAmt(ApplVar.Tend.Name, &ApplVar.Price);  //��ʾ��һ���տ��Ĳ��

				ApplVar.AmtDecimal = NO_DECIMAL;
				Prefix1 = PREFIX_1;
				Prefix2 = PREFIX_2;
				ApplVar.Price = ApplVar.Amt;	/* change */
				if (TESTBIT(ApplVar.Tend.Options, BIT4))   /* overtender is tipp? */
				    ApplVar.Amt = ApplVar.Entry;
				else
				{
				    SETBIT(ApplVar.PrintLayOut, BIT2);	/* double height */
				    ApplVar.SlipDouble = 1;
				    PrintAmt(Msg[ZHAOLING].str, &ApplVar.Price);   //��ӡ������
				    ApplVar.PrintLayOut = ApplVar.Tend.Print;	    /* restore print */
				    if (ApplVar.FCurr)	    /* print change in currency ? */
				    {
				      if (TESTBIT(ApplVar.Curr.Options, BIT1))
				      {
						  GetCurrency(2, &ApplVar.Price);
						  ApplVar.AmtDecimal = ApplVar.Curr.Options & BIT0;
						  Prefix1 = ApplVar.Curr.Prefix1;
						  Prefix2 = ApplVar.Curr.Prefix2;
						  PrintAmt(ApplVar.Curr.Name, &ApplVar.Price);
						  Subtract(&ApplVar.Entry, &ApplVar.Price);
				      }
				    }
				    ApplVar.Amt = ApplVar.SubTotal;
				}
				ApplVar.FTend = 0;
				ApplVar.FRegi = 0;
		    }
		    else
		    {			/* undertendering */
				if (!ApplVar.FBuffer)	/* buffer full then must */
				{		/* finalise without split */
				    if (ApplVar.FCurr)
				    {
						PrintStr(ApplVar.Curr.Name);
						ApplVar.AmtDecimal = ApplVar.Curr.Options & BIT0;
						Prefix1 = ApplVar.Curr.Prefix1;
						Prefix2 = ApplVar.Curr.Prefix2;
				    }
				    if (ApplVar.FRefund)
						ApplVar.Entry.Sign ^= 0x80;
				    PrintAmt(ApplVar.Tend.Name, &ApplVar.Entry);
				    Subtract(&ApplVar.SubTotal, &ApplVar.Amt);
				    if (ApplVar.FCurr)
				    {
						ApplVar.AmtDecimal = NO_DECIMAL;
						Prefix1 = PREFIX_1;
						Prefix2 = PREFIX_2;
						PrintAmt(Msg[XIAOJI].str, &ApplVar.SubTotal);
				    }
				}
				else
				{
				    ApplVar.ErrorNumber=ERROR_ID(CWXXI44);	/* must finalise without split */
				    return;
				}
		    }
		}
		else//û������������,Ĭ��ȫ���,���踶��������
		{
		    if (ApplVar.FCurr)
		    {
				PrintStr(ApplVar.Curr.Name);
				ApplVar.AmtDecimal = ApplVar.Curr.Options & BIT0;
				Prefix1 = ApplVar.Curr.Prefix1;
				Prefix2 = ApplVar.Curr.Prefix2;
		    }
		    PrintAmt(ApplVar.Tend.Name, &ApplVar.Entry);
		    ApplVar.FRegi = 0;
		    ApplVar.FTend = 0;
		}

#if (DD_CHIPC==1)
		if (payIC==1 && (!Appl_EntryCounter || sIC_AMT.Sign!=0xff))//ccr2014-12-26
		{
			PrintChipCard(payIC);
			ApplVar.PluPriceLevel = 0;
			Bell(2);
		}
        else   //cc epos
#endif

#if (CASE_EPOS)
//cc ePos>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        if (payIC==2)
        {
            PrintePosTAC();
        }
//cc epos<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#else
        {
        }
#endif
		if (ApplVar.FRefund)
		{
		    ApplVar.FRefund = 0;
		    ApplVar.Amt.Sign ^= 0x80;
		}
		ApplVar.Qty = ONE;
		if (ApplVar.FCurr)
		    AddCurrTotal();
		else
		{
			Collect_Given(); //lyq2003
		    AddTenderTotal();
		}
		if (ApplVar.PbNumber)
			AddPbtTotal();
		ApplVar.RGRec.Key.Code = ApplVar.Key.Code;
		ApplVar.RGRec.Amt = ApplVar.Amt;
		ApplVar.RGRec.Qty = ZERO;
		ApplVar.BufCmd = 0;		/* don't consolidate tendering functions */


		if (ApplVar.FCurr || ApplVar.Tend.Over)
		    ApplVar.Amt = ApplVar.Entry;
		if (ApplVar.FCurr)
		    *((WORD *)ApplVar.RGRec.Qty.Value) = CURR + ApplVar.CurrNumber;
		StoreInBuffer();

		ApplVar.RGRec.Key.Code = 0;

		if (ApplVar.FCurr)
		{
		    if (ApplVar.Curr.Drawer)
		    {
				ApplVar.DrawNumber = ApplVar.Curr.Drawer - 1;
				AddDrawerTotal();
			    ApplVar.RGRec.Key.Code = DRAW+ApplVar.Curr.Drawer;	  /* store drawer */
				ApplVar.RGRec.Amt = ApplVar.Amt;
				ApplVar.RGRec.Qty = ZERO;
			    StoreInBuffer();
				ApplVar.RGRec.Key.Code = 0;
		    }
		    ApplVar.Amt = ZERO;
		    if (!TESTBIT(ApplVar.Curr.Options, BIT1))	 /* change in local */
		    {
				if (!ApplVar.Tend.Over)
				{
				    ApplVar.Amt = ApplVar.Price;		    /* change in local */
				    ApplVar.Amt.Sign ^= 0x80; /* invert sign */
				}
		    }
		    else
				ApplVar.Price = ZERO;
		}

		if (ApplVar.Tend.Drawer)
		{
		    ApplVar.DrawNumber = ApplVar.Tend.Drawer - 1;
		    AddDrawerTotal();
		    ApplVar.RGRec.Key.Code = DRAW+ApplVar.Tend.Drawer;	  /* store drawer */
			ApplVar.RGRec.Amt = ApplVar.Amt;
			ApplVar.RGRec.Qty = ZERO;
		    StoreInBuffer();
			ApplVar.RGRec.Key.Code = 0;
		}
		if (ApplVar.Tend.Over)
		{

		    ApplVar.Amt = ApplVar.Price;
		    ApplVar.Amt.Sign ^= 0x80; /* invert sign */

		    ApplVar.DrawNumber = ApplVar.Tend.Over - 1;
		    AddDrawerTotal();
		    if (!TESTBIT(ApplVar.Tend.Options, BIT4))	/* overtender is not tip? */
			{
			    ApplVar.RGRec.Key.Code = DRAW+ApplVar.Tend.Over;	/* store overtender */
				ApplVar.RGRec.Amt = ApplVar.Amt;
				ApplVar.RGRec.Qty = ZERO;
			    StoreInBuffer();
				ApplVar.RGRec.Key.Code = 0;
			}
		}
		if (!ApplVar.FRegi)   /* end of registration ? */
		{//���踶����֧�����
#if (DD_ECRVIP==1)
            if (TESTBIT(ECRVIP.ECRVIPState,(VIP_POINTS+VIP_LOGIN))==(VIP_POINTS+VIP_LOGIN))
            {//��ӡ��Ա��������
                memset(SysBuf,' ',PRTLEN);
                CopyFrStr(SysBuf,Msg[JIFEN].str);
                HEXtoASC(SysBuf+10,(char*)ECRVIPFix[ECRVIP.ECRVIPNumber].VipTEL,6);
                sprintf(SysBuf+PRTLEN-7,"%7lu",ECRVIP.VipPoints);
                RJPrint(0,SysBuf);
            }
            ECRVIP.ECRVIPState = 0;//�����Ա��¼��־
#endif
#if (BARCUSTOMER==1)
			if ((ApplVar.Key.Code != TEND_CHIPC) && ApplVar.BarCustomer.OFFIndex>0)
			{// Print the customer message //
					sSave = ZERO;
					sTotal = ZERO;
					memcpy(&ApplVar.Price.Value,ApplVar.Plu.Price[0],5);
					memcpy(sSave.Value,ApplVar.Plu.Random,ApplVar.AP.Plu.RandomSize);
					strcpy(ProgLineMes,FormatQtyStr(0,&sSave,14));
					strcpy(ProgLineMes+14,Msg[ZONGJI].str);
					RJPrint(0,FormatAmtStr(ProgLineMes,&ApplVar.Price,PRTLEN));
					ApplVar.PluPriceLevel = 0;
			}
			ApplVar.BarCustomer.OFFIndex = 0;// ��ʶû�л�Ա��¼  //
#endif
		    ApplVar.AmtDecimal = NO_DECIMAL;	    /* restore local values for kp */
		    Prefix1 = PREFIX_1; 			/* and VAT print */
		    Prefix2 = PREFIX_2;
		    if (ApplVar.OpDraw)
			OpenDrawer();
		    StoreInBuffer();
		    if (ApplVar.PbNumber)
				PrintNewBal();
		    if (PVAT)
				CalculateTax(3);    /* print inclusive tax */
		    PrintSaleQty();     //��ӡ������Ŀ��Ŀ
		    PromtionCheck();
		    ReceiptIssue(1);    //���踶��������


		    ApplVar.BufCC = 1;		       /* set add Customer Count */
		    ProcessBuffer();	/* reset Customer count and print kp */
		    ApplVar.PbNumber = 0;
		    ApplVar.FNoPb = 0;		/* reset extra ApplVar.PB Trailer and NO ApplVar.PB */
		    ApplVar.FSplit = 0;

#if (defined(CASE_INDONESIA) && (defined(CASE_GPRS)))
            if (TESTBIT(ApplVar.DaysMust,BIT7))//���Զ��������ݣ�������ˮ
            {
                SETBIT(ApplVar.MyFlags,ZREPORT);
                ApplVar.FCurr = 0;
                ApplVar.AmtDecimal = NO_DECIMAL;	    /* restore local values */
                Prefix1 = PREFIX_1;
                Prefix2 = PREFIX_2;
                GPRSSendECR_LOG();
            }
            else//ccr2015-08-03>>>>>>����heartbeat����
            {
                GPRSSendECR_HeartBeat(1);//��������Heart-Beat
            }
#endif
		}
    }
	else//ccr 050301>>>>>>>>>>>>>>>>>>>>>>>>>>>
		if (TESTBIT(ApplVar.Tend.Options, BIT0) && !Appl_EntryCounter && ApplVar.CentralLock==MG)
		{
			    ApplVar.DrawNumber = ApplVar.TendNumber;
				DispDrawerTotal();
		}

    SETBIT(ApplVar.MyFlags,ZREPORT);
    ApplVar.FCurr = 0;
    ApplVar.AmtDecimal = NO_DECIMAL;	    /* restore local values */
    Prefix1 = PREFIX_1;
    Prefix2 = PREFIX_2;
}


