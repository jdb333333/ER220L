#define   INITAPPL_C  6
#include "king.h"
#include "exthead.h"
#include "exth.h"
#include "pwr_ctrl.h"
#include "Message.h"
#include "flashb.h"
#if PC_EMUKEY
#include "FEcrTest.h"
#endif

/***************************************************************/
void ClsXRam(void);

//����Ҫ�����ı���������籣����RAM��

void Save_ConfigApplVar(void)
{
#if ApplVarInSRAM
    ApplVar.InitFlags[0] = 0x55aa;
    ApplVar.InitFlags[2]=Config_SIZE;//ccr2017-11-30
    ApplVar.InitFlags[3]=AppVAR_SIZE;//ccr2017-11-30
#else
    int i;
    BYTE j;
    BYTE *applVar;

//    if (TESTBIT(ApplVar.MyFlags,CONFIGECR))
    {
        applVar= (BYTE*)&ApplVar.SIZE_EXTRAM;
//        RESETBIT(ApplVar.MyFlags,CONFIGECR);
        ApplVar.InitFlags[1] = 0;
        ApplVar.InitFlags[2]=Config_SIZE;//ccr2017-11-30
        ApplVar.InitFlags[3]=AppVAR_SIZE;//ccr2017-11-30

        for (i=0;i<Config_SIZE-sizeof(ApplVar.InitFlags);i++)
        {
            ApplVar.InitFlags[1] += *applVar;
            applVar++;
        }
        ApplVar.InitFlags[1] = ~ApplVar.InitFlags[1];
        ApplVar.InitFlags[1]++;
        ApplVar.InitFlags[0] = 0x55aa;
//......................................

        applVar= (BYTE*)ApplVar.ZCount;

        ApplVar.ApplVarCRC = j = 0;
        for (i=0;i<AppVAR_SIZE;i++)
        {
            j += *applVar;
            applVar++;
        }
        ApplVar.ApplVarCRC = ~j;
        ApplVar.ApplVarCRC++;

        RamOffSet = RamOfApplVar;
        WriteRam((BYTE*)&ApplVar,sizeof(APPLICATION_SAVE));
    }
//    else
//	{
//        Save_ApplRam();
//	}
#endif
}

//����������д���ڴ汣����
void Save_Config(BYTE enSave)
{
#if (ApplVarInSRAM)
    ApplVar.InitFlags[0] = 0x55aa;
    ApplVar.InitFlags[2]=Config_SIZE;//ccr2017-11-30
    ApplVar.InitFlags[3]=AppVAR_SIZE;//ccr2017-11-30
#else
    int i;
    BYTE *applVar= (BYTE*)&ApplVar.SIZE_EXTRAM;

    if (TESTBIT(ApplVar.MyFlags,CONFIGECR) || enSave)
    {
        RESETBIT(ApplVar.MyFlags,CONFIGECR);
        ApplVar.InitFlags[1] = 0;
        ApplVar.InitFlags[2]=Config_SIZE;//ccr2017-11-30
        ApplVar.InitFlags[3]=AppVAR_SIZE;//ccr2017-11-30

        for (i=0;i<Config_SIZE-sizeof(ApplVar.InitFlags);i++)
        {
            ApplVar.InitFlags[1] += *applVar;
            applVar++;
        }
        ApplVar.InitFlags[1] = ~ApplVar.InitFlags[1];
        ApplVar.InitFlags[1]++;

        RamOffSet = RamOfApplVar;
        ApplVar.InitFlags[0] = 0x55aa;

        WriteRam((BYTE*)&ApplVar,Config_SIZE);

    }
#endif
}
//
//......................................................................
//�ٿ���ʱ,���ڴ汣������ȡ��������
//������ݳ���,����false,���򷵻�true
//......................................................................
BOOL Recall_Config(void)
{
    WORD i,err=0;

#if (ApplVarInSRAM==0)
    BYTE *applVar= (BYTE*)&ApplVar.SIZE_EXTRAM;

    __disable_irq();    //��ֹ�жϣ�����У������е����ݱ仯

    RamOffSet = RamOfApplVar;
    ReadRam((BYTE*)&ApplVar,Config_SIZE);

    for (i=0;i<Config_SIZE-sizeof(ApplVar.InitFlags);i++)
    {
        err += *applVar;
        applVar++;
    }

    err+=ApplVar.InitFlags[1];

    __enable_irq();

#endif
    if (ApplVar.InitFlags[0]==0x55aa)
    {
        if (ApplVar.InitFlags[2]!=Config_SIZE || err)
        {
            //RJPrint(0,"Error when Recall Config!");//testonly
            DispStrXY("Error on:\n  Restore Config!",0,0);//testonly
            return false;
        }
        else
            return true;
    }
    return false;
}
//////////////////////////////////////////////////////////////////////////////
//�ڹػ����ߵ���ʱ,����ҵ����صı������ݴ������ʧ�洢��
//��:�ܵ�ر�����RAM����FLASH��
//......................................................................

void Save_ApplRam()
{
#if (ApplVarInSRAM==0)
    static WORD Saved1=00;

    int i;
    WORD j;

    BYTE *applVar= (BYTE*)ApplVar.ZCount;


    if (ApplRamSaved==0x5a)
    {
        __disable_irq();    //��ֹ�жϣ����Ᵽ������е����ݱ仯
        ApplRamSaved = 0xa5;//��ʾ���ڱ���ApplRAM
        j = 0;
        ApplVar.ApplVarCRC = 0;//����ApplVarCRCҲ����ͳ��,��˱�����0,
        ApplVar.ApplFlags=0x5aa5;
        for (i=0;i<AppVAR_SIZE;i++)
        {
            j += *applVar;
            applVar++;
        }
        ApplVar.ApplVarCRC = ~(j & 0xff);
        ApplVar.ApplVarCRC++;

        if (Saved1 != j)//�������ʱ�ظ�����
        {
            Saved1=j;
#if defined(DEBUGBYPC)
            RamOffSet = RamOfApplVar + Config_SIZE;
            WriteRam((BYTE*)ApplVar.ZCount,AppVAR_SIZE);
#else
            SRAM_WriteBuffer((BYTE*)ApplVar.ZCount,RamOfApplVar + Config_SIZE,AppVAR_SIZE);
#endif
        }
        ApplRamSaved = 0;//���ݱ������
        __enable_irq();
    }
#endif
}
//......................................................................
//�ٿ���ʱ,�ѱ�������ҵ����صı������ݻָ��������ռ���
//��:�ܵ�ر�����RAM����FLASH��
//������ݳ���,����false,���򷵻�true
//......................................................................
BYTE Recall_ApplRam()
{
#if (ApplVarInSRAM==0)
    WORD i;
    BYTE err;
    BYTE *applVar= (BYTE*)ApplVar.ZCount;

	__disable_irq();    //��ֹ�жϣ�����У������е����ݱ仯
//	__disable_fault_irq();

    RamOffSet = RamOfApplVar + Config_SIZE;
    ReadRam((BYTE*)ApplVar.ZCount,AppVAR_SIZE);

#if (0)//testonly>>>>>�������ݽ���У��>>>
    if (ApplVar.ApplFlags==0x5aa5)
        return true;
    else
        return false;
//<<<<<<<<<<<<<<<<<<<<<<<<<
#else// �����ݽ���У��
    err = 0;
    if (ApplVar.InitFlags[3]!=AppVAR_SIZE)
    {
        memset((BYTE*)&ApplVar.ZCount,0,AppVAR_SIZE);
    }
    else
    {
        for (i=0;i<AppVAR_SIZE;i++)
        {
            err += *applVar;
            applVar++;
        }
        if (err==0)
        {
            ApplVar_Restored = 0x5a;
        }
        else
        {
            DispStrXY("Error on:\n  Restore Appl!",0,0);//testonly
        }
    }
    __enable_irq();
//    __enable_fault_irq();

    return (err==0);//j>0ʱ,�����д�.
#endif
#else
    if (ApplVar.InitFlags[3]!=AppVAR_SIZE)
    {
        memset((BYTE*)&ApplVar.ZCount,0,AppVAR_SIZE);
    }
    return true;
#endif
}
/**
 *
 *
 * @author EutronSoftware (2016-03-29)
 *
 * @param clTotal:��ʼ��ʱ,�Ƿ����ͳ������
 */
void InitPlu(BYTE clTotal)
{
    int i,j;

	memcpy(&ApplVar.Plu, &Def.Plu,sizeof(ApplVar.Plu));
    i=strlen(Def.Plu.Name);
    if (ApplVar.AP.Plu.RandomSize)
#if (defined(DEBUGBYPC) || PC_EMUKEY)
	   	ApplVar.AP.Plu.RNumber = ApplVar.AP.Plu.Number/2;	 //set all used
    for (ApplVar.PluNumber = 0; ApplVar.PluNumber < ApplVar.AP.Plu.RNumber; ApplVar.PluNumber++)
#else
	   	ApplVar.AP.Plu.RNumber = 0;
    for (ApplVar.PluNumber = 0; ApplVar.PluNumber < ApplVar.AP.Plu.Number; ApplVar.PluNumber++)
#endif
    {
    	ApplVar.Plu.Dept = ApplVar.PluNumber & 0x3f;
        ApplVar.Plu.Link = ApplVar.Plu.OFFIndex = 0;
		if (ApplVar.AP.Plu.CapSize && i<sizeof(ApplVar.Plu.Name)-5)//ccr2016-07-21
        {
            j = WORDtoASCL(ApplVar.Plu.Name+i, ApplVar.PluNumber+1);
            ApplVar.Plu.Name[i+j]=0;
        }

		if (ApplVar.AP.Plu.RandomSize)
		    WORDtoBCD(ApplVar.Plu.Random, ApplVar.PluNumber + 1);

		if (ApplVar.AP.Plu.PriceSize)
		{
		    for (j = 0; j < ApplVar.AP.Plu.Level; j++)
#if (defined(DEBUGBYPC) || PC_EMUKEY)
				WORDtoBCD(ApplVar.Plu.Price[j], ApplVar.PluNumber+10000);
#else
				WORDtoBCD(ApplVar.Plu.Price[j], 0);
#endif
		}
		if (ApplVar.AP.Plu.Cost)
#if (defined(DEBUGBYPC) || PC_EMUKEY)
				WORDtoBCD(ApplVar.Plu.Cost, ApplVar.PluNumber+5000);
#else
				WORDtoBCD(ApplVar.Plu.Cost, 0);
#endif

		WritePlu();
        //ccr2016-03-29���ͳ����
        if (clTotal)
        {
            memset(SysBuf,0,ApplVar.AP.Plu.RecordSize-ApplVar.AP.Plu.TotalOffSet);
            WriteRam(SysBuf, ApplVar.AP.Plu.RecordSize-ApplVar.AP.Plu.TotalOffSet);
        }
    }
}

void InitDept(BYTE clTotal)
{
    int i,j;

	memcpy(&ApplVar.Dept, &Def.Dept,sizeof(ApplVar.Dept));
    i=strlen(Def.Dept.Name);
    for (ApplVar.DeptNumber = 0; ApplVar.DeptNumber < ApplVar.AP.Dept.Number; ApplVar.DeptNumber++)
    {
    	ApplVar.Dept.Group = ApplVar.DeptNumber & 0x07;
		if (ApplVar.AP.Dept.RandomSize)
		    WORDtoBCD(ApplVar.Dept.Random, ApplVar.DeptNumber + 1);
		if (ApplVar.AP.Dept.CapSize  && i<sizeof(ApplVar.Dept.Name)-4)//ccr2016-07-21
        {
            j = WORDtoASCL(ApplVar.Dept.Name+i, ApplVar.DeptNumber+1);
            ApplVar.Dept.Name[i+j]=0;
        }
		if (ApplVar.AP.Dept.PriceSize)
#if (defined(DEBUGBYPC) || PC_EMUKEY)
				WORDtoBCD(ApplVar.Dept.Price, ApplVar.DeptNumber+25);
#else
				WORDtoBCD(ApplVar.Dept.Price, 0);
#endif
;
		for (j=0;j<ApplVar.AP.Dept.PriMaxSize;j++)
			ApplVar.Dept.PriceMax[j] = 0x99;
		WriteDept();
        //ccr2016-03-29���ͳ����
        if (clTotal)
        {
            memset(SysBuf,0,ApplVar.AP.Dept.RecordSize-ApplVar.AP.Dept.TotalOffSet);
            WriteRam(SysBuf, ApplVar.AP.Dept.RecordSize-ApplVar.AP.Dept.TotalOffSet);
        }

    }
}


void InitGroup()
{
    int i,j;

	memcpy(&ApplVar.Group,&Def.Group,sizeof(ApplVar.Group));
    i=strlen(Def.Group.Name);

    for (ApplVar.GroupNumber = 0; ApplVar.GroupNumber < ApplVar.AP.Group.Number; ApplVar.GroupNumber++)
    {
		if (ApplVar.AP.Group.CapSize && i<sizeof(ApplVar.Group.Name)-2)//ccr2016-07-21
        {
            j = WORDtoASCL(ApplVar.Group.Name+i, ApplVar.GroupNumber+1);
            ApplVar.Group.Name[i+j]=0;
        }
		WriteGroup();
    }
}


void InitTender()
{
    for (ApplVar.TendNumber = 0; ApplVar.TendNumber < ApplVar.AP.Tend.Number; ApplVar.TendNumber++)
    {
		memcpy(&ApplVar.Tend,(char*)&Def.Tend+ApplVar.TendNumber*sizeof(ApplVar.Tend),sizeof(ApplVar.Tend));	/* copy default */
		WriteTender();
    }
}


void InitDrawer()
{
    for (ApplVar.DrawNumber = 0; ApplVar.DrawNumber < ApplVar.AP.Draw.Number; ApplVar.DrawNumber++)
    {
		memcpy(&ApplVar.Draw, (char*)&Def.Draw+ApplVar.DrawNumber*sizeof(ApplVar.Draw),sizeof(ApplVar.Draw));
		WriteDrawer();
    }
}



void InitCorrec()
{
    for (ApplVar.CorrecNumber = 0; ApplVar.CorrecNumber < ApplVar.AP.Correc.Number; ApplVar.CorrecNumber++)
    {
		memcpy(&ApplVar.Correc, (char*)&Def.Correc+ApplVar.CorrecNumber*sizeof(ApplVar.Correc),sizeof(ApplVar.Correc));
		WriteCorrec();
    }
}


void InitCurr()
{
    for (ApplVar.CurrNumber = 0; ApplVar.CurrNumber < ApplVar.AP.Curr.Number; ApplVar.CurrNumber++)
    {
		memcpy(&ApplVar.Curr, (char*)&Def.Curr+ApplVar.CurrNumber*sizeof(ApplVar.Curr),sizeof(ApplVar.Curr));
		WriteCurr();
    }
}


void InitDisc()
{
    for (ApplVar.DiscNumber = 0; ApplVar.DiscNumber < ApplVar.AP.Disc.Number; ApplVar.DiscNumber++)
    {
		memcpy(&ApplVar.Disc,(char*)&Def.Disc+ApplVar.DiscNumber*sizeof(ApplVar.Disc),sizeof(ApplVar.Disc));
		WriteDisc();
    }
}

void InitPoRa()//ccr040809
{
    for (ApplVar.PoRaNumber = 0; ApplVar.PoRaNumber < ApplVar.AP.PoRa.Number; ApplVar.PoRaNumber++)
    {
		memcpy(&ApplVar.PoRa,(char*)&Def.PoRa+ApplVar.PoRaNumber*sizeof(ApplVar.PoRa),sizeof(ApplVar.PoRa));
		WritePoRa();
    }
}


void InitTax()
{
    for (ApplVar.TaxNumber = 0; ApplVar.TaxNumber < ApplVar.AP.Tax.Number; ApplVar.TaxNumber++)
    {
		memcpy(&ApplVar.Tax,(char*)&Def.Tax+ApplVar.TaxNumber*sizeof(ApplVar.Tax),sizeof(ApplVar.Tax));
		WriteTax();
    }
}


void InitPbF()
{
    for (ApplVar.PbFNumber = 0; ApplVar.PbFNumber < ApplVar.AP.Pb.Number; ApplVar.PbFNumber++)
    {
		memcpy(&ApplVar.PbF ,(char*)&Def.PbF+ApplVar.PbFNumber*sizeof(ApplVar.PbF),sizeof(ApplVar.PbF));
		WritePbF();
    }
    if ((ApplVar.AP.Pb.Random & 0x0f) || ApplVar.AP.Pb.Text)
    {
		MemSet(ApplVar.PB.Text, sizeof(ApplVar.PB.Text), ' ');
		CopyFrStr(ApplVar.PB.Text, Msg[ZUOHAO].str);
		for (ApplVar.PbNumber = 1; ApplVar.PbNumber <= ApplVar.AP.Pb.NumberOfPb; ApplVar.PbNumber++)
		{
		    if (ApplVar.AP.Pb.Random & 0x0f)
				WORDtoBCD(ApplVar.PB.Random, ApplVar.PbNumber);
		    if (ApplVar.AP.Pb.Text)
				WORDtoASCL(&ApplVar.PB.Text[strlen(Msg[ZUOHAO].str)], ApplVar.PbNumber);
		    PbTotal(ApplVar.PbNumber, 1);	/* write info */
		}
		ApplVar.PbNumber = 0;
    }
}



void InitClerk()
{
    int i,j;
	memcpy(&ApplVar.Clerk,&Def.Clerk,sizeof(ApplVar.Clerk));
    i=strlen(Def.Clerk.Name);
    for (ApplVar.ClerkNumber = 1; ApplVar.ClerkNumber <= ApplVar.AP.Clerk.Number; ApplVar.ClerkNumber++)
    {
        if (i<sizeof(ApplVar.Clerk.Name)-2)//ccr2016-07-21
        {
            j = WORDtoASCL(ApplVar.Clerk.Name+i, ApplVar.ClerkNumber);
            ApplVar.Clerk.Name[i+j]=0;
        }
        WriteClerk();
    }
}



void InitSalPer()
{
#if (salNumber)
    int i,j;
	memcpy(&ApplVar.SalPer,&Def.SalPer,sizeof(ApplVar.SalPer));
    i=strlen(Def.SalPer.Name);
    for (ApplVar.SalPerNumber = 1; ApplVar.SalPerNumber <= ApplVar.AP.SalPer.Number; ApplVar.SalPerNumber++)
    {
        if (i<sizeof(ApplVar.SalPer.Name)-2)//ccr2016-07-21
        {
            j = WORDtoASCL(ApplVar.SalPer.Name+i, ApplVar.SalPerNumber);
            ApplVar.SalPer.Name[i+j]=0;
        }
		WriteSalPer();
    }
#endif
}


void InitModifier()
{
    int i,j;
	memcpy(&ApplVar.Modi,&Def.Modi,sizeof(ApplVar.Modi));
    i=strlen(Def.Modi.Name);
    for (ApplVar.ModiNumber = 0; ApplVar.ModiNumber < ApplVar.AP.Modi.Number; ApplVar.ModiNumber++)
    {
        if (i<sizeof(ApplVar.Modi.Name)-2)//ccr2016-07-21
        {
            j = WORDtoASCL(ApplVar.Modi.Name+i, ApplVar.ModiNumber+1);
            ApplVar.Modi.Name[i+j]=0;
        }
		WriteModi();
    }
}


void InitOFFPrice()
{
	memcpy(&ApplVar.OFFPrice, &Def.OFFPrice,sizeof(ApplVar.OFFPrice));
    for (ApplVar.OFFNumber = 0; ApplVar.OFFNumber < ApplVar.AP.OFFPrice.Number; ApplVar.OFFNumber++)
    {
        WORDtoASC(&ApplVar.OFFPrice.Name[9], ApplVar.OFFNumber + 1);
		WriteOFFPrice();
    }
}

void InitPort()
{
    for (Appl_PortNumber = 0; Appl_PortNumber < ApplVar.AP.Port.Number; Appl_PortNumber++)
	{
		memcpy(&Appl_Port, &Def.Port,sizeof(Appl_Port));
    	Appl_Port.Type =  Appl_PortNumber+'1';
		WritePort();
	}
}


void InitAgree()
{
#if (agreeNumber)
	memcpy(&ApplVar.Agree, &Def.Agree,sizeof(ApplVar.Agree));
    for (ApplVar.AgreeNumber = 0; ApplVar.AgreeNumber < ApplVar.AP.Agree.Number; ApplVar.AgreeNumber++)
    {
		WriteAgree();
    }
#endif
}


void InitGraph()
{
	short i;
    for (i = 0; i<GRAFESTMAX+2;i++)
		memcpy(&ApplVar.Graph[i], &Def.Graph,sizeof(Def.Graph));
}
//������б�����������
void ClearApplMemory()
{
#if defined(CASE_PERU)
    //ccr2016-12-27 ��³����:�ӵ縴λʱ,�����վݺź�Z������
    TCOUNTER rzCounter;
#if ApplVarInSRAM
    if (ApplVar.InitFlags[0] == 0x55aa)
    {
        memcpy(&rzCounter,ApplVar.ZCount,sizeof(TCOUNTER));
    }
#else

    if (ApplVarSave.InitFlags[0] == 0x55aa)
    {
        memcpy(&rzCounter,ApplVarSave.ZCount,sizeof(TCOUNTER));
    }
#endif
#endif
	memset(ApplVar.ZCount, 0, (BYTE *)&ApplVar.ApplVarCRC + sizeof(ApplVar.ApplVarCRC) - ApplVar.ZCount) ;
#if defined(CASE_PERU)
    memcpy(ApplVar.ZCount,&rzCounter,sizeof(TCOUNTER));
#endif
}
//����sizeof(APPLICATION_SAVE),������StartAddress
//toActual:=true,ת��Ϊʵ�ʵ�ַ,StartAddress[AddrEndP]=sizeof(APPLICATION_SAVE);
//        =false,ת��Ϊ��Ե�ַ,StartAddress[AddrEndP]=0
//return:=true,��ַδԽ��;=false,��ַԽ��
BYTE ResetStartAddress(BYTE toActual)
{
    int i;
    switch (toActual)
    {
        case true:
            if (ApplVar.AP.StartAddress[0]==0)
            {
                for (i=0;i<AddrMAX;i++)
                {
                    ApplVar.AP.StartAddress[i]+=RamOfTotal;
                }
            }
            if (ApplVar.AP.StartAddress[AddrEndP]>=ApplVar.SIZE_EXTRAM)
                return false;
            else
                return true;
        case false:
            if (ApplVar.AP.StartAddress[0]>=RamOfTotal)
            {
                for (i=0;i<AddrMAX;i++)
                {
                    ApplVar.AP.StartAddress[i]-=(RamOfTotal);
                }
            }
            if (ApplVar.AP.StartAddress[AddrEndP]>=ApplVar.SIZE_EXTRAM-RamOfTotal)
                return false;
            else
                return true;
        default:
           break;
    }
    return true;
}

//ccr2016-03-15>>>>������̺�>>>>>
void InitKeyMacro()
{
    int i,len;
    memset(ApplVar.AP.KeyMacros,0,sizeof(ApplVar.AP.KeyMacros));
    len=sizeof(MESSMACRO)-1;
    for (i=0;i<KEYMACROMAX;i++)
    {
        strcpy(ApplVar.AP.KeyMacros[i].Name,MESSMACRO);
        WORDtoASCL(ApplVar.AP.KeyMacros[i].Name+len,i+1);
    }
}
//ccr2016-03-15<<<<<<<<<<<<<<<<<<<
/***************************************************************/
//��ʼ����,�û��������տ�״̬��
//initMust:=true,����MACSwitch����,ǿ�ƽ��г�ʼ��
/***************************************************************/
void InitApplication(BYTE initMust)
{
	UnLong  sAddr;
	WORD	sCmp,i;
    BYTE    sRePrint=1;//�Ƿ���Ҫ��ӡ�ػ�ǰδ��ӡ��ϵ�����

#if (defined(DD_LOCK) || defined(STM32F10X_HD))
    BYTE    sKey1st=0;//��ſ���ʱ��Կ������λ�ü�ֵ

    if (KbHit()) //����ȷ�������׸���Ч����ΪԿ������λ�õļ���,�˼��뿪��ʱ�Զ�����.
        sKey1st=Getch();

#endif
    CleanKeyboard();//�������Զ��а���,���֮
    ClearVirtualInput();

#if (defined(CHAR_6X8) && !defined(DEBUGBYPC))
    mBalnkScreen();
#endif

    MACSwitch=Bios_TestMAC();
/*
    if (!MACSwitch)
    {
        if (KbHit())
        {//������סLOCK+ENTER,���г�ʼ��

            if (Getch()==ApplVar.AP.FirmKeys[ID_LOCK])
            {
                if (KbHit())
                {//������סLOCK,���г�ʼ��
                    if (Getch()==ApplVar.AP.FirmKeys[ID_ENTER])
                    {
                        MACSwitch = 1;
                    }
                }
            }
        }
    }
*/

    if (!initMust)
    {
        sCmp = Recall_Config();
        if (sCmp)//����������ȷʱ
            sCmp = (ApplVar.AP.StartAddress[0]==Default.StartAddress[0]);//�ж��ļ���ַ�ռ��Ƿ��쳣
    }
    else
        sCmp = false;//�����ʼ������

    ApplVar.ScreenStat = 0;

#if (DD_ECRVIP==1)
#if defined(DEBUGBYPC)
    RecallECRVIP();
#endif

    if (MACSwitch &&
        (ECRVIPFix[0].VipDate!=0xffff || ECRVIPVar1[0].VipPoints!=0xffffffffL  || ECRVIPVar2[0].VipPoints !=0xffffffffL))
    {//�Ƿ������Ա����
        mSetInvAttr();
        DispStrXY((char*)cCLEANALLECRVIP,0,SCREENLN-1);
        mClearInvAttr();
        SetLoop();
        while (KbHit()) Getch();
        while (!KbHit()) {};
        ResetLoop();
        if (Getch()==Default.FirmKeys[ID_ENTER])
        {
            InitECRVIP();
        }
    }
    ECRVIP.CurrentVIPVar=0;
    ECRVIP.ECRVIPState=0;
#endif


#if (!defined(DEBUGBYPC))
    pwrGetStatus(GET_VIN_STATUS);
#endif

    if (MACSwitch || !sCmp)// || initMust)  //initMust��!sCmp�ȼ�
    {//��Ҫ����ϵͳ��ʼ��

        if (!initMust)
            initMust = (ApplVar.InitFlags[0] != 0x55aa);//initMust=false,��ʾ����ʹ�ù�,��������ˮ����

        MACSwitch = 1;//It's the first time for use

        ClearApplMemory();

        /*ʹ��Ĭ�ϵļ���*/
        memcpy(ApplVar.AP.KeyTable, Default.KeyTable, sizeof(Default.KeyTable));
        memcpy(ApplVar.AP.FirmKeys, Default.FirmKeys, sizeof(Default.FirmKeys));

        GetTimeDate(&Now);              //* read timer
        if (Now.year<=0x2009)
        {//Ϊ�»���,���û��������ں�ʱ��
            do  {
                ApplVar.ErrorNumber = 0;
                Initial_DateTime(0);//��ʾ��������
                if (GetStrFrKBD('9',0,1,8,0)>0)
                {
                    Initial_DateTime(1);
                    if (GetStrFrKBD('9',0,3,6,0)>0)
                        Initial_DateTime(2);
                }
            } while (ApplVar.ErrorNumber);
        }

#if (defined(CASE_INDONESIA) && (defined(CASE_GPRS)))
        ApplVar.LastDaysLog = GetDaysFrom1900(Now.year,Now.month,Now.day);
#endif

        if (!initMust && //initMust=false,��ʾ����ʹ�ù�,�п�ʹ�õ��ļ�����
            (ApplVar.AP.StartAddress[0]==Default.StartAddress[0]))//�ļ��ռ���ȷ
        {
            mClearScreen();
            if (!sCmp)//��ʾ֮ǰ��������ļ�ʱ�д�,���ܰ���ApplVar.SIZE_EXTRAM
            {//���������Ѹı�,�����ļ����ݿ���������������쳣
                DispStrXY((char*)cMESSCONFIGERR,0,0);
            }
            mSetInvAttr();
            DispStrXY((char*)cMESSCLEANFILES,0,SCREENLN-1);
            mClearInvAttr();
            SetLoop();
            while (KbHit()) Getch();//��������쳣����
            while (!KbHit()) {};
            ResetLoop();
            sCmp = (Getch()!=Default.FirmKeys[ID_ENTER]);//sCmp=falseʱ,����ļ�����
        }
        else
            sCmp = false;//���ļ�����,ʹ��Ĭ�����ݳ�ʼ���ļ�����

        sRePrint =  0;

        if (!sCmp)
        {//������������ļ�
            sRePrint=3;//ccr2017-01-13��Ҫ��ӡƱͷ
            memset(&ApplVar.ICCardSet, 0, sizeof(ApplVar.ICCardSet));
            memcpy(&ApplVar.TXT, &DefaultText, sizeof(struct APPTEXT));
            memcpy(&ApplVar.AP, &Default, sizeof(struct APPLICATION));
    //	    InitConfig(&ApplVar.AP.Config, sizeof(struct CCONFIG));  /* Set Configuration */

            ClsXRam();//�����չ�ڴ�,ͬ�����չ�ڴ�Ĵ�С,���ܷ��õ�memcpy(&ApplVar.AP....)���֮ǰ����

            mClearScreen();

            DispStrLF(Msg[EUTRONMSG].str);

            memset(SysBuf,'=',SCREENWD);
            SysBuf[SCREENWD] = 0;
            DispStrXY(SysBuf,0,2);


            sAddr = ApplVar.SIZE_EXTRAM;
            if (sAddr && (sAddr > ApplVar.AP.StartAddress[AddrEndP] - SIZE_FLOWRAM))
            {//���¼����ڴ��п����ɵĵ�Ʒ��Ŀ
                sAddr -= ApplVar.AP.StartAddress[AddrEndP] - SIZE_FLOWRAM;//

                sAddr /= pluRecordSize;
                sCmp = sAddr;
                sAddr *= pluRecordSize;
                ApplVar.AP.Plu.Number += sCmp;

                for (sCmp = AddrPLU+1;sCmp<AddrMAX;sCmp++)
                    ApplVar.AP.StartAddress[sCmp] += sAddr;
            }
            else
            {
                mSetInvAttr();
                DispStrXY((char*)cMESSRAMOUT,0,SCREENLN-1);
                mClearInvAttr();
                while (1);
            }
            SETBIT(MACSwitch,BIT1);
            i = 0;
            sCmp = '>';	        DispCharXY(sCmp,i++,2);

            InitTender();		DispCharXY(sCmp,i++,2);
            InitPoRa();			DispCharXY(sCmp,i++,2);
            InitDrawer();		DispCharXY(sCmp,i++,2);
            InitPlu(false);	    DispCharXY(sCmp,i++,2);
            InitDept(false);	DispCharXY(sCmp,i++,2);
            InitGroup();		DispCharXY(sCmp,i++,2);
            InitCorrec();		DispCharXY(sCmp,i++,2);
            InitCurr();			DispCharXY(sCmp,i++,2);
            InitDisc();			DispCharXY(sCmp,i++,2);
            InitTax();			DispCharXY(sCmp,i++,2);
            if (ApplVar.AP.Pb.NumberOfPb)
            {
                InitPbF();		DispCharXY(sCmp,i++,2);
            }
            InitClerk();		DispCharXY(sCmp,i++,2);
            InitSalPer();		DispCharXY(sCmp,i++,2);
            InitModifier();		DispCharXY(sCmp,i++,2);     if (i>=SCREENWD) {i=0;sCmp='=';}

            InitOFFPrice();		DispCharXY(sCmp,i++,2);     if (i>=SCREENWD) {i=0;sCmp='=';}
            InitPort();			DispCharXY(sCmp,i++,2);		if (i>=SCREENWD) {i=0;sCmp='=';}
            InitAgree();		DispCharXY(sCmp,i++,2);	    if (i>=SCREENWD) {i=0;sCmp='=';}
            InitGraph();
            InitKeyMacro();
#if (DD_ECRVIP)
            RecallECRVIP();     DispCharXY(sCmp,i++,2);	    if (i>=SCREENWD) {i=0;sCmp='=';}
#endif

            ApplVar.ICCardSet.Options = 0;

            //ApplVar.IP.IPAddress[0]=0;//192;
            //ApplVar.IP.IPAddress[1]=0;//168;
            //ApplVar.IP.IPAddress[2]=0;//1;
            //ApplVar.IP.IPAddress[3]=0;//5;
#if defined(CASE_GPRS)
            ApplVar.IP.APN[0]=0;//ccr2015-03-11
            ApplVar.IP.UserName[0]=0;//ccr2015-03-11
            ApplVar.IP.Password[0]=0;//ccr2015-03-11
#endif
        }
        else if (ApplVar.AP.StartAddress[AddrTotl]<(RamOfTotal))
        {//�����ļ�����,����,�³���ı����ռ�������,��Ҫ������Ʒ��Ŀ�͵�ַ�ռ�

            sAddr = (RamOfTotal)-ApplVar.AP.StartAddress[AddrTotl];

            sAddr /= pluRecordSize;
            sAddr++;//���ٵĿռ���Ŀ
            sCmp = sAddr;//���ٵĵ�Ʒ��Ŀ
            sAddr *= pluRecordSize;
            ApplVar.AP.Plu.Number -= sCmp;
            //�ƶ�����,ɾ��sCmp����Ʒ������
            SRAM_Move(ApplVar.AP.StartAddress[AddrPort]-1,
                      ApplVar.AP.StartAddress[AddrPort]-sAddr-1,
                      -(ApplVar.AP.StartAddress[AddrPort]-ApplVar.AP.StartAddress[AddrTotl]-sAddr));

            for (i = AddrTotl;i<=AddrPLU;i++)
                ApplVar.AP.StartAddress[i] += sAddr;
            mClearScreen();
            DispStrXY((char*)cMESSDELPLU,0,0);
            i=WORDtoASC(SysBuf+4,sCmp);SysBuf[5]=0;
            DispStrXY(SysBuf+5-i,0,1);
            memset(SysBuf,'=',SCREENWD);
            SysBuf[SCREENWD] = 0;
            DispStrXY(SysBuf,0,2);
            i = 0;
        }
#if defined(CASE_EJFLASH)
        RecallEJHead();
#endif
#if (FLASH_LOG_BLOCKS)
        if (!initMust)
        {//���ܴ�����ˮ,��ʾ�Ƿ������ˮ
            mSetInvAttr();
            DispStrXY((char*)cMESSCLEANLOG,0,SCREENLN-1);
            mClearInvAttr();
            SetLoop();
            while (KbHit()) Getch();
            while (!KbHit()) {};
            ResetLoop();

            if (Getch()==Default.FirmKeys[ID_ENTER])
                initMust = true;
        }
#endif

        if (initMust)// || Bios_TestMAC())
        {
            DispCharXY('*',i++,2);
            Init_Flow();//��ȫ�����ˮ����
        }
        else
        {
            DispCharXY('#',i++,2);
            RecallFlowHead();//���������ˮ,������ˮָ������д�,����������ˮָ��,������ˮ����
        }

#if (DD_ECRVIP==1)
        //�����ָ�ECRVIP������
#endif
        DispCharXY('|',i++,2);

        ACTIVE = 5;

        InitSysFlag();

        Save_Config(true);

        ClearLine(2);
        Bell(2);
//ccr2017-01-13>>>>>>>>>>>>>
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
        if (TESTBIT(ApplVar.EJVar.ContFlag,EJDOCHEAD))
        {
            RefreshEJStart(true);
            StoreEJData(CEJ_DOCEND,(BYTE *)Msg[CHXCHSHHUA].str);
            //StoreEJEnd();
        }
#endif
//ccr2017-01-13<<<<<<<<<<<<
        RJPrint(0,Msg[CHXCHSHHUA].str);
        PrintVersion();
        sRePrint=3;//ccr2017-01-13��Ҫ��ӡƱͷ

        SETBIT(ApplVar.MyFlags,CLSSCREEN);

	}//<<<<<<< End of Initial System <<<<<<<<<<<<<<
    else
    {//�������ϵͳ��ʼ��
        if (!Recall_ApplRam())//�ٶ���������
        {//���������д�
            ClearApplMemory();
            sRePrint=2;//��ʾ��ӡ�ָ����ݳ���
#if (defined(CASE_INDONESIA) && (defined(CASE_GPRS)))
            GetTimeDate(&Now);              /* read timer */
            ApplVar.LastDaysLog = GetDaysFrom1900(Now.year,Now.month,Now.day);
#endif

        }

        RecallFlowHead();//���������ˮ,������ˮָ������д�,����������ˮָ��

        GetTimeDate(&Now);              /* read timer */
        //sRePrint = true;

        if (ApplVar.CentralLock != RG)
        {//2.������ڷ�����״̬,��ҪԤ��ӡƱͷ
            mClearScreen();
        }
        else
        {//1.���Ϊ����״̬,�ָ��ػ�ǰ����Ļ,
            for (i=0;i<SCREENLN-1;i++)
            {
                mRefreshLine(i);
            }
        }

    }

    CWORD(EXTREMAIN) &= 0x8000;//����EXTREMAIN��SLFLAG��bit0..bit6
    CWORD(EXTREMAIN) |= (RamOfTotal);


    RESETBIT(ApplVar.MyFlags,(HANZIMODE | PWDMODE | MENUMODE | KEYFROMHOST |CONFIGECR));//ccr20140514 ���������������������־  //
    RESETBIT(ApplVar.ScreenStat,HZINPUTMODE);
    SETBIT(ApplVar.ScreenStat,(HZSELECT | STATEON));//��״̬��
    mEnCursor(DISABLE);//�رչ��
#if defined(CASE_FORHANZI)
    CHNMode=PYBH_MODE;    //ccr2016-07-04
#endif
    ApplVar.ModeHead = (char*)Msg[SHOUKUAN].str;
    mLightLCDOn();

    ApplVar.CentralLock = RG;
    ClearEntry(TRUE);

    if (TESTBIT(KEYTONE,BIT0))
        Bios_1(BiosCmd_AutoClickOff);
    else
        Bios_1(BiosCmd_AutoClickOn);

#if (SCRSTATDBL)
    DispOnStatDBL((char *)Msg[SHOUKUAN].str,0);
#else
    ClsState1();
    DispSt0(Msg[SHOUKUAN].str);//RG-DISPLAY
#endif

    ARROWS = 0x01;     /* Clear Arrows and receipt on */
//	DENSITY = ApplVar.AP.Config.RDensity;

    CHARSET &= 0x0f;
    CHARSET += ApplVar.AP.Config.Country * 0x10;     /* set char set */
    ApplVar.AmtDecimal = NO_DECIMAL;
    Prefix1 = PREFIX_1;
    Prefix2 = PREFIX_2;


	COMPUTER = ApplVar.ePosPort = 0;     //cc epos
	BARCODE &= 0xf8;
    BALANCE &= 0xf8;
    ApplVar.ExtPrinter.port = 0;
#if (CASE_EPOS)
    ApplVar.ePosPort = 0;
#endif

	for (Appl_PortNumber = 0;Appl_PortNumber < ApplVar.AP.Port.Number;Appl_PortNumber++)
	{
	    ReadPort();
        //ccr2016-12-14>>>>>>>>>>>>>>>>>>>>>>>>>
        switch (Appl_Port.Type-'1')
        {
            case FORHOST:
                COMPUTER = Appl_PortNumber+1;
                break;
            case FORBARCODE:
                BARCODE = (BARCODE & 0xf8 ) | (Appl_PortNumber+1);
                break;
            case FORBALANCE:
                BALANCE = (BALANCE & 0xf8) | (Appl_PortNumber+1);
                break;
            case FOREXTPRN:   //ccr2016-12-14 ExtPrinter����
                ApplVar.ExtPrinter.port = (Appl_PortNumber+1);//ccr2016-12-14 ExtPrinter����
                break;
#if (CASE_EPOS)
            case FOREPOS:
                ApplVar.ePosPort = Appl_PortNumber+1;
#endif
            //case FORKPRINTER:
            //case FORSLIPPRN:
            default:
                break;
        }//ccr2016-12-14<<<<<<<<<<<<<<<<<<<
		SetComm(Appl_PortNumber) ;
	}

	if(ApplVar.ClerkNumber==0 || ApplVar.ClerkNumber>ApplVar.AP.Clerk.Number)
	{
		ApplVar.Key.Code = CLERK;
		ApplVar.Entry = ONE;
		ApplVar.NumberEntry = 1;
		SelectClerk(0);

	}
#if (salNumber)
   	if(ApplVar.SalPerNumber>ApplVar.AP.SalPer.Number)
        ApplVar.SalPerNumber = 0;
#endif
/*
	if(ApplVar.AP.SalPer.Number!=0)
	{
		ApplVar.Key.Code = SALPER;
		ApplVar.Entry = ONE;
		ApplVar.NumberEntry = 1;
		SelectSalPer();

	}
*/

	InActive = 0;
	DeptPluKeysCount();

    RGSuspend.SuspendItems.RGNumber=0;/* ��Ź�����վ�,RGNumber=0ʱ,�޹�����վ� */
	ApplVar.FBalance = 0;		//cc 2006-06-29 for Balance
    Appl_MaxEntry=ENTRYSIZE-2;
    Appl_ProgType = Appl_ProgLine = Appl_ProgStart = Appl_BitNumber = 0;

    ApplVar.FReport = 0;        /* reset flag else keyb. checked during printing */

    FRegSuspend = 0;

#if PC_EMUKEY
    memset(&FisTestTask,0,sizeof(FisTestTask));
    chkAutoReceiptKey();
#endif

#if (!defined(DEBUGBYPC))

    if ((DENSITY & 0x0f)==0)
        DENSITY |= (Default.Flag[CONTRAST] & 0x0f);

    mSetContrast((DENSITY & 0x0f));
    //ccr20131015>>>>>>
    pwrGetStatus(GET_VRTC_STATUS);
    if (BATTERYTooLow(PWR_BUT_WARNING2))
    {
        Bell(2);
        DispStrXY(cBUTTONBATLOW,0,0);
    }

#if POWERCTRL
    pwrGetStatus(GET_VIN_STATUS);
    while (BATTERYTooLow(PWR_WARNING2 | PWR_BY_BAT))
    {
        Bell(1);
        DispStrXY(cCHARGEBATNOW,0,1);
        Delay(500);
        pwrGetStatus(GET_VIN_STATUS);
    }
    if (BATTERYTooLow(PWR_BY_BAT | PWR_WARNING1))
        ApplVar.ErrorNumber = ERROR_ID(CWXXI74);
#endif
    //<<<<<<<<<<<<<<<
#if !defined(CASE_INNERDOTPRN)
    if (sRePrint==1)
    {//��ӡ�ػ�ǰ���жϵ�δ��ӡ����
        if (TESTBIT(ApplVar.MyFlags,NEWFIRMWARE))
        {
            ApplVar.PoolPushIn=0;
            ApplVar.PoolPopOut=0;
        }
        else
            Start_When_Ready(REPRN_PWON);
    }
    else if (sRePrint==2)
    {//���ݻָ�ʧ�ܣ���ӡ��ʾ��Ϣ
        RJPrint(0,"Error When Restore Application!");//testonly
//        Start_When_Ready("Error When Restore Appl.Vars!");
    }
    RESETBIT(ApplVar.MyFlags,NEWFIRMWARE);
#endif
#if (0)//defined(CASE_FORHANZI))
    if (CLONG(BASE_ADDRB[0x10010])!= 0x2129201f || CLONG(BASE_ADDRB[0x481c4])!= 0xfc240088)
        DispStrXY("ERROR: CHN-FONT",0,2);
#endif


#endif

#if (PLUCODE_X==1)
     PLU_X_Report=0;
#endif
     KeyFrHost=0xff;
#if defined(DD_LOCK)
    if (sKey1st && ApplVar.FRegi==0)//���������,����Կ�����ڵĵ�λ��
        KeyFrHost = sKey1st;//����ʱ��Կ������λ�ü�ֵ
#endif

#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
    CheckEJ();
#if defined(CASE_PERU)
    if (sRePrint==3)
    {//ccr2017-01-13 ��Ҫ��ӡƱͷ
        SETBIT(ApplVar.EJVar.ContFlag, (EJSTOREMUST+EJHEADMUST));
        PrePrintHead(PREHEADER);
    }
#endif
#endif


}

//����ʱ,���Ϊ�»���,���������ں�ʱ��
void Initial_DateTime(BYTE idx)
{

    short   i,j;

    switch (idx)
    {
    case 0://��ʾ��������
        ClearEntry(0);
        mClearScreen();
        Appl_MaxEntry=8;
        memset(SysBuf,0,SCREENWD+1);
        DateTimeToStr(SysBuf,0xf1);
        DispStrXY(Msg[RIQIF].str,0,0);
        DispStr_Right(SysBuf,1);
        break;
    case 1:
        if (Appl_EntryCounter)
        {
            NewTimeDate(0xf1);
            if (ApplVar.ErrorNumber)
                DispStr_Right((char*)Msg[ApplVar.ErrorNumber+CWXXI01-1].str,1);
            else if (Now.year<YEARFrHEX) Now.year |= YEARFrHEX;
        }

        memset(SysBuf,0,SCREENWD+1);
        HEXtoASC(SysBuf,(char*)(&Now.hour),1);SysBuf[2]=':';
        HEXtoASC(SysBuf+3,(char*)(&Now.min),1);SysBuf[5]=':';
        HEXtoASC(SysBuf+6,(char*)(&Now.sec),1);
        DispStrXY(Msg[SHIJIANF].str,0,2);
        DispStr_Right(SysBuf,3);
        ClearEntry(0);
        Appl_MaxEntry=6;
        break;
    case 2:// input time
        if (Appl_EntryCounter)
        {
            NewTimeDate(0xf2);
            if (ApplVar.ErrorNumber)
            {
                DispStr_Right((char*)Msg[ApplVar.ErrorNumber+CWXXI01-1].str,3);
                break;
            }
        }
        SetTimeDate(2,&Now);
        ClearEntry(0);
        break;
    }
}


