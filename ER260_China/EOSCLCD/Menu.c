/*********************************************************************************
 �˵���ʾ�Ͳ����������
  �����д:�³���
  ��д����:2004��2����7��
  ��������:2004��10��
  �޸�����:2013��6��
*********************************************************************************/
#define MENU_C
#include "king.h"                               /* Kingtron library and I/O routines */
#include "exthead.h"
#include "exth.h"
#include "Message.h"

#if (!defined(DEBUGBYPC))
//#include "USBDriver.h"
#endif
//============================================================

BYTE   MenuFuncIdx;//������¼��ѡ��Ĳ˵����ܺ�

#if (MENUITEMSMAX && MENUFUNSMAX)
/****************************************************************
    ��Ҫ�����²˵�ʱ,��Ҫ�������±��:
    1.�� Msg[]�����Ӳ˵�����Ӧ�˵������Ϣ��
    2.��CHNMess.h�����Ӳ˵�����Msg[]���������
    3.��MenuTaxTab[]����Ӳ˵�������Ϣ
    4.�� MenuTaxTab[]�����Ӳ˵�������Ӧ�Ĺ��ܺ���
****************************************************************/
CONST KbdTabStruct  MenuTaxTab[MENUFUNSMAX]=
{//�˵����ܱ�:
#if (CASE_USBDISK)//SETUP
/*   �˵����ܺ�    ��ȷ��ʱִ�й���     ���˳�ʱִ�еĹ���        */
    {usbDAOCHU     ,(*usbExportMenu),   (0)},                   //Ccr�����տ���ļ�//
    {usbDAORU      ,(*usbInportMenu),   (0)},                   //Ccr�����տ���ļ�//
    //���²˵�����û��ָ��ȷ�Ϻ���,�Զ�����MenuList[]ָ������һ���˵�
    {usbFLOW       ,(0),                (*ExitFile_USB)},       //Ccr����������ˮ//

    {usbALL        ,(*usbALLTheFile),    (*ExitFile_USB)},       //Ccrȫ���ļ�//
    {usbBULEI      ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"����",
    {usbDANPIN     ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"��Ʒ",
    {usbSHUILV     ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"˰��",
    {usbPIAOTOU    ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"Ʊͷ",
    {usbZHEKOU     ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"�ۿ�",
#if (salNumber)
    {usbYYYUAN     ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"ӪҵԱ",
#endif
    {usbSTSHZHI    ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"ϵͳ����",
    {usbTXKOU1     ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"ͨѶ��1",
    {usbTUXIN      ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"ͼ�δ�ӡ",
    {usbGUIZU      ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"����",
    {usbICKA       ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"IC��",
    {usbZHJIANG    ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"�н�����",
    {usbCANYINGN   ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"��������",
    {usbSHKYUAN    ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"�տ�Ա",
    {usbSHUOMIN    ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"˵������",
    {usbZHUOTAI    ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"��̨",
    {usbSHIDUANG   ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"ʱ��",
    {usbJIANPAN    ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"����",
    {usbTSHCHJIA   ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"�������",
    {usbCHJRJIN    ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"�������",
    {usbPIAOWEI    ,(*usbALLTheFile),   (*ExitFile_USB)},       //Ccr"Ʊβ",
    {usbPIAOJTOU   ,(*usbALLTheFile),   (*ExitFile_USB)},       //Lyq"Ʊ��Ʊͷ",
    {usbICCAGUASHI ,(*usbALLTheFile),   (*ExitFile_USB)},       //ccr"IC����ʧ",
    //���²˵�����û��ָ���˳�����,�Զ��ص�MenuList[]ָ������һ���˵�
    {usbFLOWNEW    ,(*usbExportNew),   (0)},                    // ����������,
    {usbFLOWALL    ,(*usbExportALL),   (0)},                    // ����ȫ������
    {usbFLOWALLDEL ,(*usbExportDel),   (0)},                    // ����ȫ�����ݺ����
#endif
#if defined(CASE_GPRS)//ccr2014-11-11 NEWSETUP Step-5
    {gprsSETMODE   ,   (*GPRS_SetSendMode),   (0)},                 //Ccr���÷��ͷ�ʽ//
    {gprsSendECRLogAll,(*GPRSSendECR_LOG_All),   (0)},                  //Ccr����ȫ����ˮ//

    {gprsDownloadPLU,  (*GPRS_DownloadPLU),   (0)},         //"���ص�Ʒ�ļ�"
    {gprsDownloadDEPT, (*GPRS_DownloadDEPT),   (0)},            //"���ز����ļ�"
    {gprsDownloadCLERK,(*GPRS_DownloadCLERK),   (0)},           //"�����տ�Ա"
    {gprsDownloadHEAD, (*GPRS_DownloadHEAD),   (0)},            //"����Ʊͷ"
    {gprsDownloadTRAIL,(*GPRS_DownloadPTRAIL),   (0)},          //"����Ʊβ"
    {gprsDownloadALL,   (*GPRS_DownloadALL),   (0)},          //"����ȫ������"
    {gprsRestart,      (*GPRS_Restart),   (0)},          //"��λGPRS"    //gprsRestart //ccr2016-08-26
    {gprsSENDMESS  ,   (*TestSendMess),   (0)},                    //Ccr���Ͷ���Ϣ//

#endif

};


// MenuListΪ�˵�������,ÿ�ж�Ӧһ���˵��б�:MsgIdx=�˵��ĵ�һ����Ϣ,usbMAINITEMSΪ�˵���Ŀ��
// ÿ���˵���Ŀ��Ӧ�Ĵ����ܺ�����MenuTaxTab�ж���:
//    ��ȷ�ϲ˵���ʱ,ִ��MenuTaxTab.EnterOperate
//    ��ȡ���˵���ʱ,ִ��MenuTaxTab.ExitOperate
// MenuList.*Varָʾ��ǰѡ��Ĳ˵����;*Var>=Rec1st && *Var<=RecMax
// ����ȷ�ϼ����˳���ʱ��MenuMain������MenuList�е�MsgIdxֵ����MenuTaxTab���Ҷ�Ӧ�Ĺ��ܺ���ִ��
// MainMenu=0xffʱ,���ϼ��˵�,�����˳�ʱ,�ص���һ���˵�
CONST struct SETUPLIST MenuList[MENUITEMSMAX+1]={
//	    MsgIdx;   Cols;Rows;     RecMax;    Rec1st;  *Var;      SubNo;SubMax;isSub;	MainVar;MainMenu;       SubMenu;
#if (CASE_USBDISK)//SETUP
    {usbDAOCHU,   1,SCREENLN-1,usbMAINITEMS,0,      &MenuFuncIdx,0,     0,      0,      0,      0xff,           MENUUSBFLOWIDX},    //ccr MENUUSBMAINIDX //
    {usbALL,      1,SCREENLN-1,usbFILEITEMS,0,      &MenuFuncIdx,0,     0,      0,      0,      0xff,           0xff},              //ccr MENUUSBFILEIDX //
    {usbFLOWNEW,  1,SCREENLN-1,usbFLOWITEMS,0,      &MenuFuncIdx,0,     0,      1,      3,      MENUUSBMAINIDX, 0xff},              //ccr MENUUSBFLOWIDX //
#endif

#if defined(CASE_GPRS)//ccr2014-11-11 NEWSETUP Step-5
    {gprsSETMODE,1,SCREENLN-1,gprsMAINITEMS,0,     &MenuFuncIdx,0,     0,      0,      0,      0xff,           0xff},  //ccr MENUGPRSSEND //
#endif
    {SETSYSFLAG,  1,SCREENLN-1,MENUSYSMAX,    0,    &Appl_ProgType,0,     0,      0,      0,      0xff,      0xff},     //ccr MENUSETUPIDX //
//		{XZTITLE,	  1,SCREENLN-1,XZNUM,       0,      &ApplVar.ReportNumber,0,    0,     0,0,      0xff,      0xff},	//ccr MENUXZREPIDX //
};


/******************************************************************
�˵��������pMenuIDX��MenuList�е�һ����¼
����MenuMain��,�����ᴦ��
*******************************************************************/
BYTE MenuMain(int pMenuIDX)
{
    BYTE    NumricInput;// ��������ּ���Ϊ0ʱ��û�����룬 Ϊ��0��������9��ʱΪ��һ�����֡��������˵ڶ�������ʱ������������ɲ˵���� //

    unsigned int    sMsgID,j;
    void    (*ExitFuncPtr)();    //ccr ��������ָ��*///
    void    (*EnterFuncPtr)();    //ccr ��������ָ��*///
    BYTE i,keycode;

    keycode=0;


    SetList = MenuList[pMenuIDX];
    *SetList.Var = 1;
    DisplaySetup(0xff);
    NumricInput = 0;

//	if (ApplVar.FTrain)	  //ccr080728
//		DispSt1C(Msg[PEIXUN].str);


    SetLoop();

    while (1)//keycode<190) ccr080319
    {
        if (!KbHit())
        {

#if !defined(DEBUGBYPC)
            if (!ApplVar.ErrorNumber)
                CheckTime(true);
#endif
#if defined(CASE_GPRS)
            if (pMenuIDX==gprsSENDMESS)
                  GPRSWaitForReady(false);
#endif

            CheckError(0);
            continue;
        }
        keycode=Getch();InActive = 0;

        if (keycode<128)
        {
            i = GetFirmkeyID(keycode);
        }
#if defined(DD_LOCK)
#ifdef TR
        else if (keycode==SET || keycode==RG || keycode==TR || keycode==MG || keycode==X || keycode==Z || keycode==OFF)// ccr080403>>>>
#else
        else if (keycode==SET || keycode==RG || keycode==MG || keycode==X || keycode==Z || keycode==OFF)// ccr080403>>>>
#endif

        {
            KeyFrHost = keycode;
            i = ID_CANCEL;
        }
#endif
        else
            continue;//<<<<<<<<<<

        if (i<FIRMKEYS)
        {
            switch (i)
            {
            case ID_CLEAR:
                ApplVar.ErrorNumber=0;
                ClsState2();
                break;
            case ID_RJFEED:
                RFeed(1);
                break;
            case ID_ENTER:
                if (ApplVar.ErrorNumber)
                    break;
            case ID_CANCEL:
                sMsgID = MenuFuncIdx-1+SetList.MsgIdx;
                for (j=0;j<MENUFUNSMAX;j++)
                    if (sMsgID==MenuTaxTab[j].MsgIndex)
                        break;
                if (j<MENUFUNSMAX)
                {
                    ExitFuncPtr = MenuTaxTab[j].ExitOperate;
                    EnterFuncPtr = MenuTaxTab[j].EnterOperate;
                } else
                {
                    ExitFuncPtr = 0;
                    EnterFuncPtr = 0;
                }
                if (i==ID_CANCEL)
                {
                    ApplVar.ErrorNumber=0;
                    ClsState2();
                    if (ExitFuncPtr)
                    {
                        (*ExitFuncPtr)();//ccr ִ���˳�����*///
                        NumricInput = 0;
                    } else
                    {// ���˳��������ʱ��ֱ�ӷ��ص���һ�����ú��� //
                        if (SetList.MainMenu<MENUITEMSMAX)
                        {// ���ص���һ���˵� //
                            SetList = MenuList[SetList.MainMenu];
                            *SetList.Var = 1;
                            DisplaySetup(0xff);
                            NumricInput = 0;
                        } else
                        {//����һ���˵�(SetList.MainMenu=0xff),�˳�
                            ResetLoop();
                            mClearScreen();
                            return 0;
                        }
                    }
                } else
                {
                    mClearScreen();
                    MemSet(SysBuf,6,' ');
                    SysBuf[6] = 0;
                    DispStrXY(SysBuf,SCREENWD-6, SCREENLN-1);

                    if (EnterFuncPtr)
                        (*EnterFuncPtr)();//ccr ִ��ȷ�ϵĲ���*///
                    else if (SetList.SubMenu<MENUITEMSMAX)
                    {//������һ���˵�
                        SetList = MenuList[SetList.SubMenu];
                        *SetList.Var = 1;
                    }
                    NumricInput = 0;
                    DisplaySetup(0xff);
                }
                break;
            case ID_UP:
            case ID_DOWN:
            case ID_LEFT:
            case ID_RIGHT:
            case ID_SELECT:
                if (ApplVar.ErrorNumber)
                    break;
                DisplaySetup(i);
                break;
            default:
                Bell(1);
                break;
            }
        } else
        {
            keycode = ApplVar.AP.KeyTable[keycode];//			i = GetNumric(keycode);
            if (keycode>='0' && keycode <='9')
            {
                switch (NumricInput)
                {
                default://����һ��������������
                    i = NumricInput * 10 + keycode-'0';
                    if (i<=SetList.RecMax)
                    {
                        keycode=i+'0';
                        NumricInput = 0;
                        break;
                    }
                case 0:
                    NumricInput = keycode-'0';
                    break;
                }

                DisplaySetup(keycode);
            } else
                Bell(1);
        }
    }

    ResetLoop();
    return 0;

}

//ccr /******************************************************************
//ccr ��ʾ��������˵�//
//ccr *******************************************************************/

    #if (CASE_USBDISK)

//ccr /*�˳�����˵�*///
void ExitFile_USB()
{
    SetList = MenuList[MENUUSBMAINIDX];
    *SetList.Var = 1;
    DisplaySetup(0xff);
}


////////////////////////////////////////////////////////////////
void usbExportMenu()//Ccr�����տ���ļ�//
{
    SetList = MenuList[MENUUSBFILEIDX];
    *SetList.Var = 1;
    Backup_Restore= BACKUPECR;
}
//////////////////////////////////////////////
void usbInportMenu()    //Ccr�����տ���ļ� //
{
    SetList = MenuList[MENUUSBFILEIDX];
    *SetList.Var = 1;
    Backup_Restore = RESTOREECR;
}

    #endif

    #if defined(CASE_GPRS)
//ccr /*�˳�����˵�*///
void ExitGPRS_SUB()
{
    SetList = MenuList[MENUITEMSMAX];
    *SetList.Var = 1;
    DisplaySetup(0xff);
}
    #endif
#else
BYTE MenuMain(int pMenuIDX)
{
    ResetLoop();
    mClearScreen();
    return 0;
}
#endif

//>>>>>>>>>>>>>>>ccr2016-01-11>>>�����ӵĹ���>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/**
 * �������֤����
 *
 * @author EutronSoftware (2016-01-11)
 *
 * @param pass :Ϊ��Ҫ��֤������
 *
 * @return char :����true-��֤�ɹ�,false-��֤ʧ��
 */
char CheckPassWord(char *pass)
{

}
//.......................................................................

extern void ReadKP();
void ReadFromMsg();
//......................................................................
TListRecord ListRecord;//������Name���ļ�,�����û������


TVirtualInput VirtualInput;

CONST WORD  MaxNum8=8,//������ӡ,�վ�Ʊͷ
            MaxNum6=6,//�վ�Ʊβ,Ʊ��Ʊͷ
            MaxNumFL=FUNCLOOK_KEYS,
            MaxNumGR=GRAFESTMAX,
            MaxNumMG=MGFUNCS,//=7
            MaxNumXZ=XZNUM,
            MaxNumFlags=SYSUSED,
            MaxKeyDes=KEYDESMAX,
            MaxNum10=10,//ʮ������
            MaxRepType=15,//����Ԫ
            MaxNumKM=KEYMACROMAX;
#define EJInfoMAX   14
//...............................................................................
int ListID;       //ָ��ListDef�еĵ�ǰ��¼

CONST TListDef ListDef[]={
//���ڲ������ڴ˱��е���Ŀ,��ʾ�޼�¼����,ֱ�ӽ������ý���
//***********************************************************************
    { SETGROUP  ,(*ReadGroup),  (char*)ApplVar.Group.Name, (WORD*)&ApplVar.GroupNumber,  (WORD*)&ApplVar.AP.Group.Number,0,0},   //���� //ccr2014-11-11 NEWSETUP Step-3<<<<<<
    { SETDEPT   ,(*ReadDept),   (char*)ApplVar.Dept.Name,  (WORD*)&ApplVar.DeptNumber,   (WORD*)&ApplVar.AP.Dept.Number,0,0},    //����
    { SETPLU    ,(*ReadPlu),    (char*)ApplVar.Plu.Name,   (WORD*)&ApplVar.PluNumber,    (WORD*)&ApplVar.AP.Plu.RNumber,0,0},     //��Ʒ

/* MENUCOMMAX:ͨѶ������˵�*/
//{ SETCOMPUTER  ,(*),ApplVar..Name,&number,&Max,0,0},	//ͨѶ��1
//{ SETBARCODE  ,(*),ApplVar..Name,&number,&Max,0,0},//ͨѶ��2
//{ SETBALANCE  ,(*),ApplVar..Name,&number,&Max,0,0},//ͨѶ��3
//{ SETPORT4  ,(*),ApplVar..Name,&number,&Max,0,0},//ͨѶ��4
//{ SETIP		,(*),ApplVar..Name,&number,&Max,0,0},//IP��ַ
//{ SETSP     ,(*),ApplVar..Name,&number,&Max,0,0},		//Ʊ�ݴ�ӡ
    { SETKP     ,(*ReadKP),     (char*)ListRecord.Name,     (WORD*)&ListRecord.Number,      (WORD*)&MaxNum8,0,0},//������ӡ

/* MENUMANMAX:���۹�������*/
    { SETOFF    ,(*ReadOFFPrice),(char*)ApplVar.OFFPrice.Name,(WORD*)&ApplVar.OFFNumber,    (WORD*)&ApplVar.AP.OFFPrice.Number,0,0},//�Żݼ�
//{ SETPROM   ,(*),ApplVar..Name,&number,&Max,0,0},//�н�����
    { SETDISC   ,(*ReadDisc),   (char*)ApplVar.Disc.Name,   (WORD*)&ApplVar.DiscNumber,     (WORD*)&ApplVar.AP.Disc.Number,0,0},          //***BYTE //�ۿ�
    { SETPORA   ,(*ReadPoRa),   (char*)ApplVar.PoRa.Name,   (WORD*)&ApplVar.PoRaNumber,     (WORD*)&ApplVar.AP.PoRa.Number,0,0},          //***BYTE //�������
    { SETCORR   ,(*ReadCorrec), (char*)ApplVar.Correc.Name, (WORD*)&ApplVar.CorrecNumber,   (WORD*)&ApplVar.AP.Correc.Number,0,0},  //***BYTE //��������
    { SETTEND   ,(*ReadTender), (char*)ApplVar.Tend.Name,   (WORD*)&ApplVar.TendNumber,     (WORD*)&ApplVar.AP.Tend.Number,0,0},            //***BYTE //���ʽ
    { SETCURR   ,(*ReadCurr),   (char*)ApplVar.Curr.Name,   (WORD*)&ApplVar.CurrNumber,     (WORD*)&ApplVar.AP.Curr.Number,0,0},         //***BYTE //���
    { SETDRAWER ,(*ReadDrawer), (char*)ApplVar.Draw.Name,   (WORD*)&ApplVar.DrawNumber ,    (WORD*)&ApplVar.AP.Draw.Number,0,0},           //***BYTE //Ǯ��
#if !defined(CASE_FORHANZI)
    { SETTAX    ,(*ReadTax),    (char*)ApplVar.Tax.Name,    (WORD*)&ApplVar.TaxNumber,      (WORD*)&ApplVar.AP.Tax.Number,0,0},  //***BYTE//˰��
#endif
/* MENUICCMAX:IC������*/
//{ SETVIPIC     ,(*),ApplVar..Name,&number,&Max,0,0},//IC������
    { SETBLOCKIC,(*ListICBlock),(char*)ListRecord.Name,     (WORD*)&ApplVar.ICBlockNumber,  (WORD*)&ApplVar.AP.ICBlock.Number,0,0},//IC����ʧ
//{ SETPRINTIC,(*),ApplVar..Name,&number,&Max,0,0},	//��ӡ����Ϣ

/* MENUTICMAX:ƱͷƱβ*/
    { SETHEAD   ,(*ReadHeader), (char*)ListRecord.Name,     (WORD*)&ListRecord.Number,      (WORD*)&MaxNum8,0,0},    //�վ�Ʊͷ
    { SETTRAIL  ,(*ReadTrail),  (char*)ListRecord.Name,     (WORD*)&ListRecord.Number,      (WORD*)&MaxNum6,0,0},//�վ�Ʊβ
    { SETSHEAD  ,(*ReadSlipHeader),(char*)ListRecord.Name,  (WORD*)&ListRecord.Number,      (WORD*)&MaxNum6,0,0},    //Ʊ��Ʊͷ
    { SETGRAP   ,(*ReadGraphic),(char*)ListRecord.Name,     (WORD*)&ListRecord.Number,      (WORD*)&MaxNumGR,0,0},  //ƱβͼƬ
//{ SETPRTGRAP,(*),ApplVar..Name,&number,&Max,0,0},		//��ӡͼƬ

/* MENUREPMAX:������*/
    { SETREPORT ,(*ReadXZReport),(char*)ListRecord.Name,    (WORD*)&ListRecord.Number,      (WORD*)&MaxNumXZ,0,0},   //���ñ�������
    { SETREPTYPE,(*ReadRepUnit),(char*)ListRecord.Name,     (WORD*)&ListRecord.Number,      (WORD*)&MaxRepType,0,0},  //����Ԫ
    { SETZONES  ,(*ReadZone),   (char*)ListRecord.Name,     (WORD*)&ListRecord.Number,      (WORD*)&ApplVar.AP.Zone.Number,0,0},    //***BYTE  //����ʱ������
//{ SETCLRREP ,(*),ApplVar..Name,&number,&Max,0,0},	//���屨��
//{ SETPRTJOUR,(*),ApplVar..Name,&number,&Max,0,0},	//��ӡ��ˮ

/* MENUTBLMAX:��������*/
    { SETPBINF  ,(*ReadPBTable),(char*)ApplVar.PB.Text,     (WORD*)&ApplVar.PbNumber,       (WORD*)&ApplVar.AP.Pb.NumberOfPb,0,0},   //��̨
    { SETPBF    ,(*ReadPbF),    (char*)ApplVar.PbF.Name,    (WORD*)&ApplVar.PbFNumber,      (WORD*)&ApplVar.AP.Pb.Number,0,0},   //***BYTE //��������
    { SETMODIF  ,(*ReadModi),   (char*)ApplVar.Modi.Name,   (WORD*)&ApplVar.ModiNumber ,    (WORD*)&ApplVar.AP.Modi.Number,0,0},           //�˵�˵��
#if (agreeNumber)
    { SETAGREE  ,(*ReadAgree),  (char*)ApplVar.Agree.Name,  (WORD*)&ApplVar.AgreeNumber ,   (WORD*)&ApplVar.AP.Agree.Number,0,0},//ǩ��
#endif

/* MENUPWDMAX:Ȩ������*/
    { SETCLERK  ,(*ReadClerk),  (char*)ApplVar.Clerk.Name,  (WORD*)&ApplVar.ClerkNumber ,   (WORD*)&ApplVar.AP.Clerk.Number,0,0},   //(ApplVar.ClerkNumber>=1)�տ�Ա
#if (salNumber)
    { SETSALER  ,(*ReadSalPer), (char*)ApplVar.SalPer.Name, (WORD*)&ApplVar.SalPerNumber ,  (WORD*)&ApplVar.AP.SalPer.Number,0,0},  //(ApplVar.SalPerNumber>=1)ӪҵԱ
#endif
    { SETSYSFLAG,(*ReadFlagsList),(char*)ListRecord.Name,   (WORD*)&ListRecord.Number,      (WORD*)&MaxNumFlags,0,(*NewProgSysFlag)},  //ϵͳ����
    { SETPOINTTYPE,(*ReadFromMsg),(char*)ListRecord.Name,   (WORD*)&ListRecord.Number,      (WORD*)MsgPOINTMAX,MsgPOINTTYPE1,0},  //С����ʽѡ��
    { LISTMGFUNC,(*ReadFromMsg), (char*)ListRecord.Name,    (WORD*)&ListRecord.Number,      (WORD*)MsgMGMMAX,MsgMGADDINV,0},  //�����¹��ܲ˵�
    { LISTKEYDES,(*ReadKeyDesList),(char*)ListRecord.Name,  (WORD*)&ListRecord.Number,      (WORD*)&MaxKeyDes,0,0},  //���̹������б�
    { SETTEST,   (*ReadFromMsg), (char*)ListRecord.Name,    (WORD*)&ListRecord.Number,      (WORD*)MENUTSTMAX,SETTSTDISP,0},  //ϵͳ���Թ���
    { LISTNUMRIC,(*ReadNumric),  (char*)ListRecord.Name,    (WORD*)&ListRecord.Number,      (WORD*)&MaxNum10,0,0},  //ʮ������
/* ������־��ѯ��ӡ */
    { MsgALLLOG,  (*ReadFromMsg), (char*)ListRecord.Name,    (WORD*)&ListRecord.Number,      (WORD*)MsgPRNLOGMAX,MsgALLLOG,0},  //��ӡ���ۼ�¼
    { MsgALLCASH,(*ReadFromMsg), (char*)ListRecord.Name,    (WORD*)&ListRecord.Number,      (WORD*)2,MsgALLCASH,0},  //ѡ�񸶿ʽ
    { MsgALLDEPT,(*ReadFromMsg), (char*)ListRecord.Name,    (WORD*)&ListRecord.Number,      (WORD*)2,MsgALLDEPT,0},  //ѡ����
    { MsgALLPLU, (*ReadFromMsg), (char*)ListRecord.Name,    (WORD*)&ListRecord.Number,      (WORD*)2,MsgALLPLU,0},  //ѡ��Ʒ
    { SETREST,   (*ReadFromMsg), (char*)ListRecord.Name,    (WORD*)&ListRecord.Number,      (WORD*)KEYTYPEMAX,SETREST,0},  //����ģʽѡ��
    { SETKEYMACRO,(*ReadKeyMacro),(char*)ListRecord.Name,    (WORD*)&ListRecord.Number,     (WORD*)&MaxNumKM,0,0},  //���̺궨��
/* ѡ���ܱ��еĹ��� */
    { FUNCLOOK1, (*ReadFuncLook),  (char*)ListRecord.Name,    (WORD*)&ListRecord.Number,    (WORD*)&MaxNumFL,0,0},  //���ܱ�
/* EJ��ѯ��ӡ */
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
    { MsgEJMESSAGES, (*ReadFromMsg), (char*)ListRecord.Name,    (WORD*)&ListRecord.Number,  (WORD*)MsgPRNEJMAX,MsgEJMESSAGES,0},  //��ӡEJ��¼
    { MENUXEJOURNAL, (*ReadEJInfo), (char*)ListRecord.Name,    (WORD*)&ListRecord.Number,   (WORD*)EJInfoMAX,MENUXEJOURNAL,0},  //��ӡEJ��¼
#endif
    { MsgMGPRINTSTOCK,(*ReadPluStock), (char*)ListRecord.Name,   (WORD*)&ApplVar.PluNumber,    (WORD*)&ApplVar.AP.Plu.RNumber,0,0},     //���ĵ�Ʒ���

    { 0xffff  ,0,0,0,0,0,0},        //����
};
//****************************************************************************************
/**
 * ����Ҫ��ȡ�ļ�¼��
 *
 * @author EutronSoftware (2016-01-14)
 *
 * @param idx :��¼��ָ��
 * @param val :��¼��
 * @param b_w :=trueΪBYTE����,=falseΪWORD����
 */
void SetRecIndex(WORD *idx,WORD val,BYTE b_w)
{
    if (b_w)
        *(BYTE*)idx=val;
    else
        *idx=val;
}

void IncRecIndex(WORD *idx,BYTE b_w)
{
    if (b_w)
        (*(BYTE*)idx)++;
    else
        (*idx)++;
}
void DecRecIndex(WORD *idx,BYTE b_w)
{
    if (b_w)
        (*(BYTE*)idx)--;
    else
        (*idx)--;
}

WORD ReadRecIndex(WORD *idx,BYTE b_w)
{
    if (b_w)
        return (*(BYTE*)idx);
    else
        return (*idx);
}

void ClearVirtualInput()
{
    VirtualInput.vLen=0;
    VirtualInput.vKey=0xff;
}
/**
 * �������ⰴ��
 *
 * @author EutronSoftware (2016-01-28)
 *
 * @param key :=0xff,��������������
 */
void VirtualInputKey(BYTE key)
{
    VirtualInput.vLen = 0;
    VirtualInput.vKey=key;
}
/**
 *
 *
 * @author EutronSoftware (2016-01-28)
 *
 * @param key :=0xff,��������������
 * @param val :=0xffffʱ,����������
 */
void VirtualInputWord(BYTE key,WORD val)
{
    if (val!=0xffff)
        VirtualInput.vLen=WORDtoASCL(VirtualInput.vInput,val);
    else
        VirtualInput.vLen = 0;
    VirtualInput.vKey=key;
}
/**
 *
 *
 * @author EutronSoftware (2016-01-28)
 *
 * @param key :=0xff,��������������
 * @param val :�������������
 * @param sLen :������������ݳ���.
 */
void VirtualInputStr(BYTE key,char *val,BYTE sLen)
{
    if (val && sLen)
    {
        if (sLen>sizeof(VirtualInput.vInput))
            sLen=sizeof(VirtualInput.vInput);
        memcpy(VirtualInput.vInput,val,sLen);
        VirtualInput.vLen=sLen;
    }
    else
        VirtualInput.vLen=0;
    VirtualInput.vKey=key;
}

/**
 *
 *
 * @author EutronSoftware (2016-01-28)
 *
 * @return BYTE:�������ⰴ��,=0xffʱ,�����ⰴ��
 */
BYTE CheckVirtualKey()
{
    return VirtualInput.vKey;
}

/**
 * ��ȡ��ListItems���õ�ѡ������
 *
 * @author EutronSoftware (2016-01-14)
 *
 * @return WORD :=0,������;����Ϊ(����+1),ͬʱ���ú�����������
 */
WORD GetInputByListItems()
{
    if (VirtualInput.vKey!=0xff)
    {
        if (VirtualInput.vLen)
        {
            ClearEntry(0);
            Appl_EntryCounter = VirtualInput.vLen;
            memcpy(EntryBuffer + ENTRYSIZE - Appl_EntryCounter - 1,VirtualInput.vInput, Appl_EntryCounter);
        }
        KeyFrHost=VirtualInput.vKey;
        VirtualInput.vKey=0xff;
        VirtualInput.vLen=0;
        return (KeyFrHost+1);
    }
    else
        return 0;
}
/**
 * ��ȡ��ѡ�����Ŀ���ƴ�
 *
 * @author EutronSoftware (2016-02-15)
 *
 * @return char*
 */
char* GetActiveItemStr()
{
    return VirtualInput.vInput;
}
/**
 *
 *
 * @author EutronSoftware (2016-01-26)
 *
 * @param x :�����ʾλ��
 * @param y
 * @param val :���
 *
 * @return int :��ʾ�ļ�¼���λ��
 */
int DispIndex(BYTE x,BYTE y,WORD val)
{
    WORD temp;
    char decBuff[7];

    if (VirtualInput.vDispRecNo)//�Ƿ���ʾ���
    {
        temp = WORDtoASCL(decBuff,val);
        decBuff[temp++]='.';decBuff[temp]=0;
        DispStrXY(decBuff,x,y);
        return temp;
    }
    else
        return 0;
}
/**
 * ֱ�Ӵ�Msg[]�ж�ȡ��Ϣ�����б�
 *
 * @author EutronSoftware (2016-02-17)
 */
void ReadFromMsg()
{
    strcpy(ListRecord.Name,Msg[ListRecord.Number+ListDef[ListID].MsgIDX].str);
}
/***************************************************************
 * ���б����ʾ�о�ָ�������ļ������е����ݲ�ѡ������һ�������༭
 *
 * @author EutronSoftware (2016-01-11)
 *
 * @param fileType:��Ʒ/����/���������ID
 * @param saveSCR: �Ƿ񱣻���Ļ����
 * @param caption: ��״̬����ʾ�˵�������Ϣ
 * @param vKey: =true,�˳�ʱ�������ⰴ��
 *
 *
 * @return int:=0���б�����
 *             =It_PLU_MG(-1)Ϊ��ȷ�ϼ�,ȷ��PLU�����MGѡ����;
 *             =It_EXIT(-2)Ϊ���˳���.
 *             ����ֵ,������ѡ��ļ�¼���(1..0xfffd);
 ***************************************************************/

#define LISTLINES   (SCREENLN-1)    //��Ļ�Ͽ���ʾ������
#define ACTIVEITEM  TESTBIT(ApplVar.ScreenStat, INVATTR)  //Ϊ��ǰ��¼

WORD ListItems(WORD fileType,BYTE saveSCR,const char* caption,BYTE vKey)
{
    static WORD fileLast=0; //�����´ν���ʱ,ֱ�Ӷ�Ϊ����ǰ��¼
    static WORD recLast=0;  //�����´ν���ʱ,ֱ�Ӷ�Ϊ����ǰ��¼

    BYTE byteNum;
    WORD *recIDX;
    char *sStr;
    WORD recFrom,recMAX;//��¼�ſ�ʼ��ź������Ŀ
    WORD recCurrent;    //��ǰѡ��ļ�¼��
    WORD recList[LISTLINES];//���浱ǰ�ҵ��ļ�¼ (recFrom..n)
    WORD recCount,recCountX;          //recList�еļ�¼��Ŀ
    BYTE keyID;
    WORD keyCode,temp;
    int  sLp;

    void    (*ReadFromFile)();
    BYTE    (*PorcessRecord)(BYTE y,WORD recNo);    //��Ӧ��ǰ��¼�Ĵ�����,=nullʱ,�޴�����,��������0ʱ,û�д����� //

    //...................................................

    VirtualInputStr(0xff,0,0);//�����������
    ListID=0;
    do
    {
        if (ListDef[ListID].SetupIDX==0xffff)
            return 0;
        if (ListDef[ListID].SetupIDX==fileType)
            break;
        ListID++;
    } while (true);

    recFrom=0;
    VirtualInput.vDispRecNo=1;
    switch (fileType)
    {
    case SETDISC:          //***BYTE //�ۿ�
    case SETPORA:          //***BYTE //�������
    case SETCORR:          //***BYTE //��������
    case SETTEND:          //***BYTE //���ʽ
    case SETCURR:          //***BYTE //���
    case SETDRAWER:        //***BYTE //Ǯ��
#if !defined(CASE_FORHANZI)
    case SETTAX:           //***BYTE//˰��
#endif                           //
    case SETZONES:         //***BYTE  //����ʱ������
    case SETPBF:           //***BYTE //��������
        byteNum=true;
        break;
    case SETPLU:
    case MsgMGPRINTSTOCK://ccr2017-01-10
        if (ApplVar.AP.Plu.RandomSize==0)//ccr2016-06-06
            ApplVar.AP.Plu.RNumber = ApplVar.AP.Plu.Number;
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
    case MENUXEJOURNAL:
#endif
    case SETSYSFLAG:
        VirtualInput.vDispRecNo=0;
        byteNum=false;
        break;
    case SETGRAP:
        VirtualInput.vDispRecNo=0;
    case SETPBINF: //��Ŵ�1��ʼ
    case SETCLERK://�տ�Ա��ӪҵԱ�Ŀ�ʼ��Ŵ�1��ʼ
#if (salNumber)
    case SETSALER:
#endif
        recFrom=1;
    default:
        byteNum=false;
        break;
    }
    if (ListDef[ListID].MsgIDX==0)
        recMAX=ReadRecIndex(ListDef[ListID].RecordMax,byteNum)+recFrom;
    else
        recMAX=(WORD)ListDef[ListID].RecordMax+recFrom;

    //�����б�������

    ReadFromFile=ListDef[ListID].ReadRecord;
    PorcessRecord=ListDef[ListID].PorcessRecord;
    recIDX=ListDef[ListID].RecordIdx;
    sStr=ListDef[ListID].Caption;


    keyCode=ID_DOWN;
    if (fileType==fileLast && recLast<recMAX)
        SetRecIndex(recIDX,recLast,byteNum);
    else
        SetRecIndex(recIDX,recFrom,byteNum);
    recCount=0;
    Appl_EntryCounter=0;
    memset((BYTE*)recList,0,sizeof(recList));

    if (saveSCR)
        BackupScreen(1);
    ClsState12();
    if (caption && VirtualInput.vDispRecNo==1)
        DispSt1((BYTE *)caption);
//    else
//        ClsArea(PROMDISPX,STATELINE,SCREENWD-PROMDISPX);
    while (true)//keycode<190) ccr080319
    {
        //��ȡһ���¼���ݲ�����Ļ����ʾ
        //DispSt0(ApplVar.ModeHead);
        mClearScreen();
        mSetInvAttr();
        recCountX=recCount;
        recCurrent=0;
        recCount=0;
        switch (keyCode)
        {
        case ID_UP://��ǰ���Ҽ�¼
        case ID_LEFT:
            if (recList[0]>recFrom)
            {
                SetRecIndex(recIDX,recList[0]-1,byteNum);
                while (recCount<LISTLINES)
                {
                    if (ReadRecIndex(recIDX,byteNum)>=recFrom)
                    {
                        //(*ReadFromFile)();
                        //DispStrXY(sStr,0,recCount);
                        //mClearInvAttr();
                            recList[recCount++]=ReadRecIndex(recIDX,byteNum);
                            if (ReadRecIndex(recIDX,byteNum)==recFrom)
                                break;
                            DecRecIndex(recIDX,byteNum);
                    }
                    else
                        break;
                }
                //���ҵ������ݼ�¼˳����з�ת
                for (sLp=0;sLp<recCount / 2;sLp++)
                {
                    temp=recList[sLp];
                    recList[sLp]=recList[recCount-sLp-1];
                    recList[recCount-sLp-1]=temp;
                }
                //��ʾ��¼����
                for (sLp=0;sLp<recCount;sLp++)
                {
                    SetRecIndex(recIDX,recList[sLp],byteNum);
                    (*ReadFromFile)();
                    DispStrXY(sStr,DispIndex(0,sLp,recList[sLp]+(1-recFrom)),sLp);
                    if (ACTIVEITEM)
                        strncpy(VirtualInput.vInput,sStr,sizeof(VirtualInput.vInput));//ccr2016-02-15
                    mClearInvAttr();
                }
                //����DOWN����ʱ�ظ����һ����¼
                IncRecIndex(recIDX,byteNum);
                break;
            }
//            if (recCount<LISTLINES && recMAX>=LISTLINES)
            {
                SetRecIndex(recIDX,recFrom,byteNum);
                recCount=0;
            }
        case ID_DOWN://�����Һ�����¼
        case ID_RIGHT:
        case ID_SELECT:
            while (recCount<LISTLINES)
            {
                if (ReadRecIndex(recIDX,byteNum)<recMAX)
                {
                    (*ReadFromFile)();

                    recList[recCount]=ReadRecIndex(recIDX,byteNum);
                    DispStrXY(sStr,DispIndex(0,recCount,recList[recCount]+(1-recFrom)),recCount);
                    if (ACTIVEITEM)
                        strncpy(VirtualInput.vInput,sStr,sizeof(VirtualInput.vInput));//ccr2016-02-15

                    mClearInvAttr();
                    recCount++;
                    IncRecIndex(recIDX,byteNum);
                }
                else if (recCount==0 && recCountX>0)//��ʾ��һ�β��ҵ�������
                {
                    recCount=recCountX;
                    //��ʾ��¼����
                    //mSetInvAttr();
                    for (sLp=0;sLp<recCount;sLp++)
                    {
                        SetRecIndex (recIDX,recList[sLp],byteNum);
                        (*ReadFromFile)();
                        if (ACTIVEITEM)
                            strncpy(VirtualInput.vInput,sStr,sizeof(VirtualInput.vInput));//ccr2016-02-15

                        DispStrXY(sStr,DispIndex(0,sLp,recList[sLp]+(1-recFrom)),sLp);
                        mClearInvAttr();
                    }
                    break;
                }
                else
                    break;
            }
            break;
        }
        //���´���ѡ���¼
        recCurrent=0;
        sLp=true;
        while (sLp)
        {//��һ���¼��ѡ��
            if (Appl_EntryCounter==0 && VirtualInput.vDispRecNo==0)
                DisplayDecXY(recList[recCurrent]+(1-recFrom),SCREENWD-6,SCREENLN,6);//��״̬����ʾ��¼��
            if (PorcessRecord)
            {//����????
                keyID=keyCode=(*PorcessRecord)(recCurrent,recList[recCurrent]-recFrom);
                if (keyID==0)
                    break;
            }
            else
            {
                SetLoop();
                while (!KbHit())
                {

    #if !defined(DEBUGBYPC)
                    if (!ApplVar.ErrorNumber)
                        CheckTime(true);
                    if (fileType==SETPLU && BarCode())
                        break;
                    Computer();//communicate with computer
    #endif
                    CheckError(0);
                    //continue;
                }
                keyID=keyCode=Getch();
                ResetLoop();
            }
            InActive = 0;

            if (keyCode<127)
            {
                keyCode = GetFirmkeyID(keyCode);
            }

#if defined(DD_LOCK)
#ifdef TR
            else if (keyCode==SET || keyCode==RG || keyCode==TR || keyCode==MG || keyCode==X || keyCode==Z || keyCode==OFF)// ccr080403>>>>
#else
            else if (keyCode==SET || keyCode==RG || keyCode==MG || keyCode==X || keyCode==Z || keyCode==OFF)// ccr080403>>>>
#endif
            {
                KeyFrHost = keyCode;
                //ccr2016-06-16>>>>>>>>>>>>>>
                ClsArea(PROMDISPX,SCREENLN,PROMPTWD);
                if (saveSCR)
                    RecallScreen();
                else
                    mClearScreen();
                mClearInvAttr();

                return It_EXIT;//Ϊ�˳�����־
                //ccr2016-06-16<<<<<<<<<<<<<<<<<
            }
#endif
            else
                continue;//<<<<<<<<<<

            if (keyCode<FIRMKEYS)
            {
                switch (keyCode)
                {
                case ID_CLEAR:
                    ApplVar.ErrorNumber=0;
                    ClearEntry(true);
                    break;
                case ID_DELETE://�� ID_RJFEED ��ͬ
                    if ((fileType==SETHEAD || fileType==SETTRAIL || fileType==SETSHEAD || fileType==SETPLU)
                        && InputYesNo(Msg[SHANCHU].str,PROMDISPX+1,SCREENLN,1)=='Y')
                    {//ɾ����Ʒ/Ʊͷ��

                        SetRecIndex(recIDX,recList[recCurrent],byteNum);
                        if (fileType==SETHEAD)
                            DeleteHeader(recList[recCurrent]);
                        else if (fileType==SETTRAIL)
                            DeleteTrailer(recList[recCurrent]);
                        else if (fileType==SETSHEAD)
                            DeleteSlipHead(recList[recCurrent]);
                        else if (fileType==SETPLU)
                        {
                            GetPluOffSet();
                            CheckRandomPlu(1,1);
                        }

                        keyCode=ID_DOWN;
                        sLp=false;//�ж�ѭ��
                    }
                    else
                        RFeed(1);
                    break;
                case ID_ENTER:
                    ClsArea(PROMDISPX,SCREENLN,PROMPTWD);
                    if (saveSCR)
                        RecallScreen();
                    else
                        mClearScreen();
                    fileLast=fileType;
                    recLast=recList[recCurrent];

                    temp = recLast+(1-recFrom);//�տ�Ա�ȵļ�¼�Ŵ�1��ʼ
                    if (fileType==LISTMGFUNC && temp<=7)
                    {
                        if ((keyID = PosOfFuncKey(SUB))!=0xff)
                        {//����1/2/3/4/5/6/7+С��
                            VirtualInputWord(keyID,temp);
                            temp = It_PLU_MG;
                        }
                    }
                    else if (fileType==SETPLU && Appl_EntryCounter)
                    {//������������༭��Ʒ
                        VirtualInputStr(ApplVar.AP.FirmKeys[ID_ENTER],EntryBuffer + ENTRYSIZE - Appl_EntryCounter - 1,Appl_EntryCounter);
                        ClearEntry(false);
                        mClearInvAttr();
                        return It_PLU_MG;
                    }
                    if (Appl_EntryCounter)
                        ClearEntry(false);

                    if (recMAX)
                    {
                        mClearInvAttr();
                        return temp;
                    }
                case ID_CANCEL:
                case ID_LOCK://ccr2016-11-15
                    if (keyCode==ID_LOCK &&
                        Appl_EntryCounter && ApplVar.NumberEntry>0 && ApplVar.NumberEntry<=5 &&
                        (ApplVar.CentralLock==SET || ApplVar.CentralLock==X || ApplVar.CentralLock==Z ))
                        VirtualInputStr(ApplVar.AP.FirmKeys[ID_LOCK],EntryBuffer + ENTRYSIZE - Appl_EntryCounter - 1,Appl_EntryCounter);//���ⰴ��ʽ����
                    else if (vKey)
                    {
                         VirtualInputStr(ApplVar.AP.FirmKeys[ID_CANCEL],0,0);//���ⰴȡ����
                    }

                    ClsArea(PROMDISPX,SCREENLN,PROMPTWD);
                    if (saveSCR)
                        RecallScreen();
                    else
                        mClearScreen();
                    mClearInvAttr();
                    return It_EXIT;//Ϊ�˳�����־
                case ID_UP://������ʾ
                case ID_LEFT:
                    if (recCurrent>0)
                    {//��ʾ��һ����¼����
                        SetRecIndex(recIDX,recList[recCurrent],byteNum);
                        (*ReadFromFile)();
                        mClearInvAttr();

                        DispStrXY(sStr,DispIndex(0,recCurrent,recList[recCurrent]+(1-recFrom)),recCurrent);
                        recCurrent--;

                        SetRecIndex(recIDX,recList[recCurrent],byteNum);
                        (*ReadFromFile)();
                        mSetInvAttr();

                        strncpy(VirtualInput.vInput,sStr,sizeof(VirtualInput.vInput));//ccr2016-02-15
                        DispStrXY(sStr,DispIndex(0,recCurrent,recList[recCurrent]+(1-recFrom)),recCurrent);
                        mClearInvAttr();
                    }
                    else
                        sLp=false;//�ж�ѭ��
                    break;
                case ID_SELECT:
                    sLp=false;//��ҳ��ʾ,�ж�ѭ��//recCurrent=recCount-1;
                    break;
                case ID_DOWN:
                case ID_RIGHT:
                    if (recCurrent<recCount-1)
                    {//��ʾ��һ����¼����
                        SetRecIndex(recIDX,recList[recCurrent],byteNum);

                        (*ReadFromFile)();
                        mClearInvAttr();

                        DispStrXY(sStr,DispIndex(0,recCurrent,recList[recCurrent]+(1-recFrom)),recCurrent);
                        recCurrent++;

                        SetRecIndex(recIDX,recList[recCurrent],byteNum);
                        (*ReadFromFile)();
                        mSetInvAttr();

                        strncpy(VirtualInput.vInput,sStr,sizeof(VirtualInput.vInput));//ccr2016-02-15
                        DispStrXY(sStr,DispIndex(0,recCurrent,recList[recCurrent]+(1-recFrom)),recCurrent);
                        mClearInvAttr();
                    }
                    else
                    {
                        SetRecIndex(recIDX,recList[recCurrent],byteNum);
                        IncRecIndex(recIDX,byteNum);
                        sLp=false;//�ж�ѭ��
                    }
                    break;
                default:
                    Bell(1);
                    break;
                }
                Appl_EntryCounter=0;
            }
            else
            {
                keyCode = ApplVar.AP.KeyTable[keyID];//			i = GetNumric(keycode);
                if (keyCode>='0' && keyCode <='9' && Appl_EntryCounter<13)
                {
                    AppendEntry(keyCode);
#if defined(CASE_FORHANZI)
                    DispStrXY(EntryBuffer + ENTRYSIZE - 12 - 1 ,SCREENWD-12,STATELINE);
#else
                    DispStrXY(EntryBuffer + ENTRYSIZE - 13 - 1 ,SCREENWD-13,STATELINE);
#endif
                    GetEntry();
                    if ((WORD)ApplVar.NumberEntry>=recFrom && (WORD)ApplVar.NumberEntry<=recMAX)
                    {
                        SetRecIndex(recIDX,(WORD)ApplVar.NumberEntry-(1-recFrom),byteNum);
                        keyCode=ID_DOWN;
                        sLp=false;
                    }
                }
                else
                {
                    if (keyCode>DEPT && keyCode<PLU1 && fileType==SETDEPT)
                    {//�������ʱ,ֱ�ӽ����Ӧ�Ĳ���
                        keyCode -= DEPT;
                    }
                    else if (keyCode>PLU1 && keyCode<PLU3 && fileType==SETPLU)
                    {//��Ʒ,������ͨ����ֱ�ӵ�Ʒ����
                        keyCode -= PLU1;
                    }
                    /*else if (keyCode>DISC && keyCode<DRAW && fileType==SETDISC)
                    {//�ۿ�
                        keyCode -= DISC;
                    }
                    else if (keyCode>TEND && keyCode<MODI && fileType==SETTEND)
                    {//���ʽ
                        keyCode -= TEND;
                    }*/
                    else
                        keyCode=0;
                    if (keyCode)
                    {
                        ClsArea(PROMDISPX,SCREENLN,PROMPTWD);
                        if (saveSCR)
                            RecallScreen();
                        else
                            mClearScreen();
                        return keyCode;
                    }
                    else
                        Bell(1);
                }
            }
        }//while (sLp)
    }//while (true)
}

/**
 * �����ļ����ͺ�ָ���ļ�¼��,���տ���ļ��л�ȡ��¼����
 *
 * @author EutronSoftware (2016-02-25)
 *
 * @param fileType:�ļ�����
 * @param idx:��¼���
 * @param caption:���صļ�¼�е�����
 *
 * @return word:true-�ж�Ӧ������;false-�޶�Ӧ������
 */
WORD ReadItemCaption(WORD fileType,WORD idx,char *caption)
{
    BYTE byteNum;
    WORD *recIDX;
    char *sStr;
    int  sListIdx;
    WORD recFrom,recMAX;//��¼�ſ�ʼ��ź������Ŀ
    void    (*ReadFromFile)();
    //...................................................

    sListIdx=0;
    do
    {
        if (ListDef[sListIdx].SetupIDX==0xffff)
        {
            caption[0]=0;
            return 0;
        }
        if (ListDef[sListIdx].SetupIDX==fileType)
            break;
        sListIdx++;
    } while (true);

    recFrom=0;

    switch (fileType)
    {
    case SETDISC:          //***BYTE //�ۿ�
    case SETPORA:          //***BYTE //�������
    case SETCORR:          //***BYTE //��������
    case SETTEND:          //***BYTE //���ʽ
    case SETCURR:          //***BYTE //���
    case SETDRAWER:        //***BYTE //Ǯ��
#if !defined(CASE_FORHANZI)
    case SETTAX:           //***BYTE//˰��
#endif                           //
    case SETZONES:         //***BYTE  //����ʱ������
    case SETPBF:           //***BYTE //��������
        byteNum=true;
        break;
    case SETGRAP:
    case SETCLERK://�տ�Ա��ӪҵԱ�Ŀ�ʼ��Ŵ�1��ʼ
#if (salNumber)
    case SETSALER:
#endif
        recFrom=1;
    default:
        byteNum=false;
        break;
    }
    if (ListDef[sListIdx].MsgIDX==0)
        recMAX=ReadRecIndex(ListDef[sListIdx].RecordMax,byteNum)+recFrom;
    else
        recMAX=(WORD)ListDef[sListIdx].RecordMax+recFrom;

    if (idx<recMAX)
    {
        ReadFromFile=ListDef[sListIdx].ReadRecord;
        recIDX=ListDef[sListIdx].RecordIdx;
        sStr=ListDef[sListIdx].Caption;
        SetRecIndex(recIDX,idx,byteNum);
        (*ReadFromFile)();
        strcpy(caption,sStr);
        return true;
    }
    else
    {
        caption[0]=0;
        return false;
    }

}
/**
 * ��ӡXZ���ܲ˵�
 *
 * @author EutronSoftware (2016-11-16)
 *
 * @param xz
 */
void PrintXZMenu(BYTE xz)
{
    MenuDefine *ItemXZReport;
    int msgFr,msgTo,msgLp;
    WORD recFrom,recMAX;//��¼�ſ�ʼ��ź������Ŀ
    WORD recCurrent;    //��ǰѡ��ļ�¼��
    WORD *recIDX;
    char *sStr,pBuf[PRTLEN+3];
    WORD recCount,recCountX;          //recList�еļ�¼��Ŀ
    void    (*ReadFromFile)();


    if (xz==X)
    {
        msgFr = MENUXREPORT;
        msgTo = msgFr+MENUXITEMMAX-1;
        ItemXZReport = (MenuDefine *)&ItemXReport;
        pBuf[0]='X';
    }
    else if (xz==Z)
    {
        msgFr = MENUZREPORT;
        msgTo = msgFr+MENUZITEMMAX-1;
        ItemXZReport = (MenuDefine *)&ItemZReport;
        pBuf[0]='Z';
    }
    else
        return;

    pBuf[1]=' ';
    strcpy(pBuf+2,cMESSSETMENU);
    PrintLine2('.');
    PrintStr_Center(pBuf,true);
    PrintLine2('=');
    for (msgLp=msgFr;msgLp<=msgTo;msgLp++)
    {

        //��ӡ�ϻ��˵�����
        recFrom = msgLp-msgFr+1;

        memset(pBuf,' ',sizeof(pBuf));
        if (recFrom>9) pBuf[3]=recFrom/10+'0';
        pBuf[4]=recFrom % 10+'0';
        pBuf[5]='.';
        strncpy(pBuf+6,Msg[msgLp].str,sizeof(pBuf)-6);
        pBuf[PRTLEN+3-1]=0;
        RJPrint(0,pBuf+3);


        recFrom=0;
        do
        {
            if (ItemXZReport[recFrom].MenuFrom==0)
            {
                recFrom = 0xffff;
                break;
            }
            else if (ItemXZReport[recFrom].MenuFrom==msgLp)
                break;
            recFrom++;
        } while (true);
        if (recFrom == 0xffff || ((recFrom = ItemXZReport[recFrom].MenuItems)==0))
            continue;

        ListID=0;
        do
        {
            if (ListDef[ListID].SetupIDX==0xffff)
            {
                ListID = 0xffff;
                break;
            }
            else if (ListDef[ListID].SetupIDX==recFrom)
                break;
            ListID++;
        } while (true);
        if (ListID == 0xffff)
            continue;

        if (ListDef[ListID].MsgIDX==0)
            recMAX=ReadRecIndex(ListDef[ListID].RecordMax,true);
        else
            recMAX=(WORD)ListDef[ListID].RecordMax;

        //�����б�������

        recIDX=ListDef[ListID].RecordIdx;
        ReadFromFile=ListDef[ListID].ReadRecord;
        sStr=ListDef[ListID].Caption;

        recFrom=1;
        SetRecIndex(recIDX,0,true);

        while (recFrom<=recMAX)
        {
            if (ReadRecIndex(recIDX,true)<recMAX)
            {
                (*ReadFromFile)();
                if (recFrom>9)
                    pBuf[6]=recFrom/10+'0';
                else
                    pBuf[6]=' ';
                pBuf[7]=recFrom % 10+'0';
                pBuf[8]='.';
                strncpy(pBuf+9,sStr,sizeof(pBuf)-9);
                pBuf[PRTLEN-1]=0;
                RJPrint(0,pBuf);
                recFrom++;
                IncRecIndex(recIDX,true);
            }
        }
    }
}
/**
 * ��ӡ�����µĲ��������б�
 *
 * @author EutronSoftware (2016-11-18)
 */
void PrintMGMenu()
{
    int i;
    char pBuf[PRTLEN+3];

    PrintLine2('.');
    PrintStr_Center(Msg_MANAGEMENT,true);
    PrintLine2('=');
    memset(pBuf,' ',PRTLEN);
    for (i=1;i<=MsgMGMMAX;i++)
    {
        if (i>9)
            pBuf[0]=i/10+'0';
        else
            pBuf[0]=' ';
        pBuf[1]=i % 10+'0';
        pBuf[2]='.';
        strncpy(pBuf+3,Msg[i+MsgMGADDINV-1].str,PRTLEN-3);
        RJPrint(0,pBuf);
    }
}
