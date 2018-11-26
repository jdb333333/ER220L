/*********************************************************************************
*  �����д:�³���                                                               *
*  ��д����:2009��7����7��                                                       *
*  �޸�����:2013��9�� (STM32-Cortex-M3) 										 *
*  �ڵ����������ˮ����ʱ,����ļ�����,�Ͱ�������׷�ӵ��ļ�ĩβ,����д�����	 *
*  ��������ļ�,���ڵ�һ��д�����  											 *
*  �������ܺ�����ʹ�����¹��ô洢������Ϊ������:								 *
*  1.EntryBuffer:��������ʱ,�����ݴ汨�����ݵ�����/�տ����/���̺� 			     *
*  2.CCDBuff:��FormatToCSV�����ݴ��ʽ������		                             *
*  3.SysBuf:��ʱ������.������ˮ����ʱ,�����洢��ˮ���ݵ�����/�տ�Ա/ӪҵԱ����Ϣ *
*  4.ProgLineMes:��ʱ������                                                      *
*********************************************************************************/
#define USBDISKAPP_C


#include "king.h"                               /* Kingtron library and I/O routines */
#include "exthead.h"
#include "exth.h"
#include "message.h"

#include "USBDiskApp.h"

#if (CASE_USBDISK)

#define SAME_RECEIPT    //ccr2016-09-05 �����վݴ�����ͬ�ĸ�ʽ������ˮ
/* SAME_RECEIPT
  �����������ݸ�ʽ��Ϊ������ʽ����:
    ���е�һ�а����վݺ�/�տ�Ա/ʱ��/�տ����,
    �����"����   ����    ���"����ʽ����������Ŀ
*/

#if !defined(SAME_RECEIPT)
const char cCSVFLOETITL[]=CSVFLOETITL;
#else
const char cCSVFLOETITL[]=CSV_TITLE;
#endif


#if (!defined(DEBUGBYPC))
//#include "USBDriver.h"

/***************************************************************
  Definitions for Disk IO
***************************************************************/
BYTE FolderString[15]  = {0};//��ŵ����ļ��ı����ļ���(LR******)
FATFS fatfs;
FIL USBfile;
DIR USBdir;


DWORD DiskCapacity;

///////////////////////////////////////////////////////////////////////
// ����ΪU���ļ���������,��Բ�ͬ��ƽ̨,�޸���Щ��������ʵ����ֲ /////
//////////////////////////////////////////////////////////////////////
/********************************************************************
* ģ�鹦��: �����ļ�������
* ģ������: U_ResetFolder
* ����˵��: ��//
* �ļ���LR+���̺�+�տ�������
*********************************************************************/
void U_ResetFolder(void)
{
    sprintf(FolderString,"0:LR%03u%03u",LOCATION,REGISTER);
}


/********************************************************************
* ģ�鹦��: ���U��׼����//
* ģ������: U_DiskReady//
* ����˵��: ��//
*
* ����ֵ: ��ȷ����0�����󷵻ط�0//
*********************************************************************/
short U_DiskReady(void)
{// ���U���Ƿ�׼����,�����U�̲���Ҫ��һ��, ����ĳЩU�̱���Ҫִ����һ�����ܹ���//
    return (USB_DiskReady()==false);
}

/********************************************************************
* ģ�鹦��: ��U����Ĭ���ļ����µ��ļ�,Ĭ���ļ�����FolderStringָ��
* ģ������: U_OpenFile
* ����˵��: filename:�ļ���//
*           mode �ļ��򿪷�ʽ:
*           FA_READ: ָ�������ʶ��󡣿��Դ��ļ��ж�ȡ���ݡ���FA_WRITE��Ͽ��Խ��ж�д���ʡ�
*           FA_WRITE: ָ��д���ʶ��󡣿������ļ���д�����ݡ���FA_READ��Ͽ��Խ��ж�д���ʡ�
*           FA_OPEN_EXISTING: ���ļ�������ļ������ڣ����ʧ�ܡ�(Ĭ��)
*           FA_OPEN_ALWAYS: ����ļ����ڣ���򿪣����򣬴���һ�����ļ���
*           FA_CREATE_NEW: ����һ�����ļ�������ļ��Ѵ��ڣ��򴴽�ʧ�ܡ�
*           FA_CREATE_ALWAYS: ����һ�����ļ�������ļ��Ѵ��ڣ����������ضϲ����ǡ�
* ����ֵ: ��ȷ����0�����󷵻ط�0//
*********************************************************************/
short U_OpenFile(char *filename,BYTE mode)
{
    FRESULT res;

      /* Register work area for logical drives */
      f_mount(0, &fatfs);

	  f_chdir("0:");

      if (Backup_Restore==RESTOREECR && f_open(&USBfile, filename,mode)==FR_OK)
          return FR_OK;//��Ŀ¼����Ҫ������ļ�ʱ,ֱ�ӵ���

      res = f_opendir(&USBdir, FolderString);
      if (res != FR_OK)
          f_mkdir(FolderString);

	  f_chdir(FolderString);

      return (f_open(&USBfile, filename,mode));
}


/********************************************************************
* ģ�鹦��: �����ļ�,����ļ�����,������ļ�//
* ģ������: U_CreateFile
* ����˵��: filename:�ļ���//
*
* ����ֵ: ��ȷ����0�����󷵻ط�0//
*********************************************************************/
short U_CreateFile(char *filename)
{
	FRESULT res;

    /* Register work area for logical drives */
    f_mount(0, &fatfs);

	f_chdir("0:");

    res = f_opendir(&USBdir, FolderString);
    if (res != FR_OK)
        f_mkdir(FolderString);

    f_chdir(FolderString);

    return (f_open(&USBfile, filename,(FA_WRITE | FA_CREATE_ALWAYS)));
}


/********************************************************************
* ģ�鹦��: ��U���ϵ��ļ�//
* ģ������: U_ReadFile
* ����˵��: nbyte:Ҫ�����ݵĳ���, buf:�������ݴ�ŵĻ�����ָ��//
* ����ֵ: ��ȷʱ����ʵ�ʶ�ȡ�����ݳ���,����ʱ���� -1
*********************************************************************/
INT U_ReadFile(char *buf, UINT nbyte)
{
    UINT i;

    if(f_read(&USBfile,buf,nbyte,&i)==FR_OK)
        return i;
    else if (f_eof(&USBfile))
        return 0;
    else
        return -1;

}

/********************************************************************
* ģ�鹦��: �ж�U���ϵ��ļ��Ƿ�ĩβ//
* ģ������: U_Eof
* ����ֵ: True:�ѵ��ļ�β
*********************************************************************/
BYTE U_Eof()
{
    return f_eof(&USBfile);
}
//********************************************************************
//* ģ�鹦��: дU���ϵ��ļ�//
//* ģ������: U_WriteFile
//* ����˵��: nbyte:Ҫд���ݵĳ���, buf:Ҫд�����ݵĻ�����ָ��//
//*
//* ����ֵ: ��ȷ���س���,���󷵻� -1//
//*********************************************************************/

INT U_WriteFile(const char *buf, UINT nbyte)
{
    UINT i;

    if (f_write(&USBfile,buf,nbyte,&i)==FR_OK)
        return i;
    else
        return -1;
}


/********************************************************************
* ����ģ��: �ر�U���ļ�//
* ģ������: 	U_Close
* ����˵��: ��
*
* ����ֵ: ��ȷ����0�����󷵻ط�0//
*********************************************************************/
short U_CloseFile(void)
{
    FRESULT res;         /* FatFs function common result code */

    res = f_close(&USBfile);
    f_mount(0, &fatfs);
    return res;

}


//********************************************************************
//* ģ�鹦��: ��λ�ļ�ָ��//
//* ģ������: U_Locate
//* ����˵��: offset:׼���ƶ���ƫ������0xffffffffʱ���Ƶ�ĩβ//
//*
//* ����ֵ: ��ȷ����0�����󷵻ط�0//
//*********************************************************************/

short U_LocateFile(ULONG locate_addr)
{
    if (locate_addr==0xffffffff)
        return f_lseek(&USBfile,USBfile.fsize);
    else
        return f_lseek(&USBfile,locate_addr);
}

/********************************************************************
* ����ģ��: �ر�U���ļ�//
* ģ������: 	U_FileSize
* ����˵��: ��
*
* ����ֵ: �ļ���С(�ֽ���//
*********************************************************************/
DWORD U_FileSize(void)
{
    return USBfile.fsize;
}
//********************************************************************
//* ģ�鹦��: ɾ��U���ļ�//
//* ģ������: U_Delete
//* ����˵��: filename:�ļ���//
//*
//* ����ֵ: ��ȷ����0�����󷵻ط�0//
//*********************************************************************/

short U_DeleteFile(char *filename)
{
    return 0;
}
#else
void U_ResetFolder(void)
{
}
//////////////////////////////////////////////////////////
#endif

/********************************************************************
//numDECΪС��λ��,=0xffʱ,��ָ��С��λ��
********************************************************************/
void FormatBCD_DEC(char *to, BCD *pBCD,BYTE numDEC)
{
    BCD sBCD;

    sBCD = *pBCD;

    if (numDEC<7)
        SETDECIMAL(sBCD.Sign,numDEC);
    FormatBCD(to, &sBCD,(BCDLEN * 2) + 0x6400);
}

/********************************************************************
* ѡ�����ݵ�����ʽ ��ϵͳ�������ʱ,��ʾ������ʾ,������1(����)��0(�˳�) ////
* ��CSV_FORMAT:1-CSV��ʽ;0-BIN��ʽ
* return:true-ѡ���˸�ʽ, false-û��ѡ���ʽ
*********************************************************************/
BYTE SelectCSV_BIN()
{
	char sInput;
    BYTE keyno;


	ClearLine(0);
    DispStrXY((char*)cEXPORTCSV,0,0);
    if (CSV_FORMAT)
        sInput='1';
    else
        sInput='2';

    GotoXY(SCREENWD-1,0);
    DispCharXY(sInput,SCREENWD-1,0);

    while (1)
    {
        if (KbHit())
        {
            keyno = Getch();        /* read key */

            if (keyno==ApplVar.AP.FirmKeys[ID_CANCEL])
                return false;
            else if (keyno==ApplVar.AP.FirmKeys[ID_ENTER])
            {
                SETBIT(ApplVar.MyFlags,CONFIGECR);
                if (sInput=='1')
                    SETBIT(APPLCTRL,1);//          CSV_FORMAT
                else if (sInput=='2')
                    RESETBIT(APPLCTRL,1);//          BINCSV_FORMAT
                else
                    return false;
                return true;
            }
            else
            {
                keyno = ApplVar.AP.KeyTable[keyno];
                if (keyno>='0' || keyno<='2')
                    sInput = keyno;
                DispCharXY(sInput,SCREENWD-1,0);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////
BYTE TitleFlag;//���������Ƿ�д�뱨�����
//////////////////////////////////////////////////////////////////////////////////////
void ReadPBTotal();
void WritePBTotal();
BYTE BackupECRFiles(int fileID);
//////////////////////////////////////////////////////////////////////////////////////

CONST ECRFILEClass EcrFileObj[usbFILEITEMS-1] = {
{DEPTREC     ,cDEPTCAP    ,(*Inport_DEPT),    (*Export_DEPT),    (char*)&ApplVar.Dept,       sizeof(ApplVar.Dept),           (WORD*)&ApplVar.AP.Dept.Number,    (WORD*)&ApplVar.DeptNumber,	(*ReadDept),(*WriteDept)},  //DEPTREC �����ļ�//
{PLUREC      ,cPLUCAP     ,(*Inport_PLU),     (*Export_PLU),     (char*)&ApplVar.Plu,        sizeof(ApplVar.Plu),            (WORD*)&ApplVar.AP.Plu.Number,     (WORD*)&ApplVar.PluNumber,	(*ReadPlu),(*WritePlu)},  		//PLUREC   ��Ʒ�ļ�//
{TAXREC		 ,cTAXCAP     ,(*Inport_TAX),     (*Export_TAX),     (char*)&ApplVar.Tax,        sizeof(ApplVar.Tax),            (WORD*)&ApplVar.AP.Tax.Number,     (WORD*)&ApplVar.TaxNumber,	(*ReadTax),(*WriteTax)},  		//TAXREC  ˰�� //BYTE
{HEADERREC   ,cHEADERCAP  ,(*Inport_HEADER),  (*Export_HEADER),  (char*)&ApplVar.TXT.Header, sizeof(ApplVar.TXT.Header),     0,0,(0),(0)},  						//HEADERREC Ʊͷ��������//
{DISCREC     ,cDISCCAP    ,(*Inport_DISC),    (*Export_DISC),    (char*)&ApplVar.Disc,       sizeof(ApplVar.Disc),           (WORD*)&ApplVar.AP.Disc.Number,    (WORD*)&ApplVar.DiscNumber,	(*ReadDisc),(*WriteDisc)},  //DISCREC �ۿ��ļ�//BYTE
#if (salNumber)
{SALPERREC   ,cSALPERCAP  ,(*Inport_SALPER),  (*Export_SALPER),  (char*)&ApplVar.SalPer,     sizeof(ApplVar.SalPer),         (WORD*)&ApplVar.AP.SalPer.Number,  (WORD*)&ApplVar.SalPerNumber,(*ReadSalPer),(*WriteSalPer)},  //SALPERREC ����Ա�ļ�//
#endif
{SYSTEMREC   ,cSYSTEMCAP  ,(*Inport_SYSTEM),  (*Export_SYSTEM),  (char*)&ApplVar.AP.Flag,    sizeof(ApplVar.AP.Flag),        0,0,(0),(0)},  						//SYSTEMREC  ϵͳ�����ļ�//
{COMMREC	 ,cCOMMCAP    ,(*Inport_COMM),    (*Export_COMM),    (char*)&Appl_Port,          sizeof(Appl_Port),              (WORD*)&ApplVar.AP.Port.Number,    (WORD*)&Appl_PortNumber,     (*ReadPort),(*WritePort)},  //COMMREC   ͨѶ�� //
{GRAPPRNREC  ,cGRAPPRNCAP ,(*Inport_GRAPPRN), (*Export_GRAPPRN), (char*)&ApplVar.Graph,      sizeof(ApplVar.Graph),          0,0,(0),(0)},  						//GRAPPRNREC   ƱͷƱβ��ӡͼƬ˵��//
{GROUPREC    ,cGROUPCAP   ,(*Inport_GROUP),   (*Export_GROUP),   (char*)&ApplVar.Group,      sizeof(ApplVar.Group),          (WORD*)&ApplVar.AP.Group.Number,   (WORD*)&ApplVar.GroupNumber,	(*ReadGroup),(*WriteGroup)},  //GROUPREC     �����ļ�//
{ICCARDREC   ,cICCARDCAP  ,(*Inport_ICCARD),  (*Export_ICCARD),  (char*)&ApplVar.ICCardSet,  sizeof(ApplVar.ICCardSet),      0,0,(0),(0)},						//ICCARDREC IC��ʹ���ļ�//
{PROMREC     ,cPROMCAP    ,(*Inport_PROM),    (*Export_PROM),    (char*)&ApplVar.AP.Promotion,sizeof(ApplVar.AP.Promotion),  0,0,(0),(0)},  						//PROMREC �н�˵��//
{PBFUNCREC   ,cPBFUNCCAP  ,(*Inport_PBFUNC),  (*Export_PBFUNC),  (char*)&ApplVar.PbF,        sizeof(ApplVar.PbF),            (WORD*)&ApplVar.AP.Pb.Number,      (WORD*)&ApplVar.PbFNumber, 	(*ReadPbF),(*WritePbF)},  			//PBFUNCREC ��������˵���ļ�//BYTE
{CLERKREC    ,cCLERKCAP   ,(*Inport_CLERK),   (*Export_CLERK),   (char*)&ApplVar.Clerk,      sizeof(ApplVar.Clerk),          (WORD*)&ApplVar.AP.Clerk.Number,   (WORD*)&ApplVar.ClerkNumber,	(*ReadClerk),(*WriteClerk)},  //CLERKREC     �տ�Ա�ļ�//
{MODIREC     ,cMODICAP    ,(*Inport_MODI),    (*Export_MODI),    (char*)&ApplVar.Modi,       sizeof(ApplVar.Modi),           (WORD*)&ApplVar.AP.Modi.Number,    (WORD*)&ApplVar.ModiNumber,	(*ReadModi),(*WriteModi)},  //MODIREC      ��ζ˵���ļ�//
{PBTOTALREC  ,cPBTOTALCAP ,(*Inport_PBTOTAL), (*Export_PBTOTAL), (char*)&ApplVar.PB,         sizeof(ApplVar.PB),             (WORD*)&ApplVar.AP.Pb.NumberOfPb,  (WORD*)&ApplVar.PbNumber,  	(*ReadPBTotal),(*WritePBTotal)},  	//PBTOTALREC   ��̨�ļ�//
{ZONEREC     ,cZONECAP    ,(*Inport_ZONE),    (*Export_ZONE),    (char*)&ApplVar.AP.Zone,    sizeof(ApplVar.AP.Zone),        0,0,(0),(0)},						//ZONEREC ��ʱͳ�Ƶ�ʱ��ֶ�˵��//
{KEYBOARDREC ,cKEYBOARDCAP,(*Inport_KEYBOARD),(*Export_KEYBOARD),(char*)&ApplVar.AP.KeyTable,sizeof(ApplVar.AP.KeyTable),    0,0,(0),(0)},						//KEYBOARDREC	 ���� //
{OFFREC      ,cOFFCAP     ,(*Inport_OFF),     (*Export_OFF),     (char*)&ApplVar.OFFPrice,   sizeof(ApplVar.OFFPrice),       (WORD*)&ApplVar.AP.OFFPrice.Number,(WORD*)&ApplVar.OFFNumber, 	(*ReadOFFPrice),(*WriteOFFPrice)},  //OFFREC       ��������ļ�//
{PORAREC     ,cPORACAP    ,(*Inport_PORA),    (*Export_PORA),    (char*)&ApplVar.PoRa,       sizeof(ApplVar.PoRa),(WORD*)    (WORD*)&ApplVar.AP.PoRa.Number,    (WORD*)&ApplVar.PoRaNumber,	(*ReadPoRa),(*WritePoRa)},  	//PORAREC      �������//BYTE
{TRAILERREC  ,cTRAILERCAP ,(*Inport_TRAILER), (*Export_TRAILER), (char*)&ApplVar.TXT.Trailer,sizeof(ApplVar.TXT.Trailer),    0,0,(0),(0)},  						//TRAILERREC   Ʊβ��������//
{SLIPHEADREC ,cSLIPHEADCAP,(*Inport_SLIPHEAD),(*Export_SLIPHEAD),(char*)&ApplVar.TXT.SlipHeader,sizeof(ApplVar.TXT.SlipHeader),0,0,(0),(0)}, 					//SLIPHEADREC	 Ʊ�ݴ�ӡͷ //
{ICBLOCKREC  ,cICBLOCKCAP ,(*Inport_ICBLOCK), (*Export_ICBLOCK), (char*)&ApplVar.ICBlock,    sizeof(ApplVar.ICBlock),        (WORD*)&ApplVar.AP.ICBlock.Number, (WORD*)&ApplVar.ICBlockNumber,(*ReadICBlock),(*WriteICBlock)},  //ICBLOCKREC   IC���������ļ�//

//{DRAWERREC     ,(char*)&,sizeof,&ApplVar.AP..Number,&,(*),(*)},  //DRAWERREC    Ǯ�䶨���ļ�//
//{CORRECTREC    ,(char*)&,sizeof,&ApplVar.AP..Number,&,(*),(*)},  //CORRECTREC   �����ļ�//
//{TENDREC       ,(char*)&,sizeof,&ApplVar.AP..Number,&,(*),(*)},//TENDREC      ���ʽ//
};

#define FILETOCSV   0   //�Ƿ������ļ���CSV��ʽ����

#if (!defined(DEBUGBYPC))
#define xCHECKUSBDISK()  	if (USB_DiskReady()==false) {ApplVar.ErrorNumber = ERROR_ID(CWXXI76);return;}
#define vCHECKUSBDISK(ret) 	if (USB_DiskReady()==false) {ApplVar.ErrorNumber = ERROR_ID(CWXXI76);return ret;}
#else
#define xCHECKUSBDISK()  	{}
#define vCHECKUSBDISK(ret) 	{}
#endif

#if FILETOCSV
#define vCHECKCSV(ret) 	{}
#else
#define vCHECKCSV(ret) 	{return ret;}
#endif


BYTE Backup_Restore;// 0-���룬1������ //

/////////////////////////////////////////////////////////////
void ReadPBTotal()
{

	RamOffSet =  (UnLong)ApplVar.PbNumber* ApplVar.AP.Pb.PBTRecordSize + ApplVar.AP.StartAddress[AddrPBt] + sizeof(ApplVar.PB.Block);

	MemSet(&ApplVar.PB, sizeof(ApplVar.PB), 0);
    if (ApplVar.AP.Pb.Random & 0x0f)
    {
	    ReadRam((char *)ApplVar.PB.Random, ApplVar.AP.Pb.Random & 0x0f);
    }
    if (ApplVar.AP.Pb.Text)
    {
	    ReadRam((char *)ApplVar.PB.Text, ApplVar.AP.Pb.Text);
    }
}
/////////////////////////////////////////////////////////////
void WritePBTotal()
{
    WORD newblock, recsize;
	UnLong save;

	RamOffSet =  (UnLong)ApplVar.PbNumber* ApplVar.AP.Pb.PBTRecordSize + ApplVar.AP.StartAddress[AddrPBt] + sizeof(ApplVar.PB.Block);

    if (ApplVar.AP.Pb.Random & 0x0f)
    {
	    WriteRam((char *)ApplVar.PB.Random, ApplVar.AP.Pb.Random & 0x0f);
    }
    if (ApplVar.AP.Pb.Text)
    {
	    WriteRam((char *)ApplVar.PB.Text, ApplVar.AP.Pb.Text);
    }
}


//ccr20130827>>>>>>>>>
////////////////////////////////////////////////////////////////////////////////////
// ����Ϊ�����������ݵĹ��ܺ�����,�������ݵĸ�ʽ����CSV�ļ���ʽ,������֮����','����
// �������ݵĵ�����ʹ��PCBffer�����ݻ���  //
///////////////////////////////////////////////////////////////////////////////////
#define LEFTALIGN		20		// ��һ��ͳ����������˵ľ��� //
#define NUMWIDTH		13		// �������� 999999999.99 //

// ��ӡ����ı�����,ʹ��SysBuf //
void usbPrintTitlel()
{
	int i;

	if (TitleFlag)
		return;
	TitleFlag = 1;

	memset(SysBuf,' ',sizeof(SysBuf));
    strcpy(SysBuf,cUSBREPNAME);
    i = strlen(SysBuf);
    SysBuf[i++]=',';

	if (ApplVar.Size.Cc)
	{
		strcpy(SysBuf+i, Msg[JIAOYISHU].str);
		i = strlen(SysBuf);
        SysBuf[i++]=',';

	}
	if (ApplVar.Size.Qty)
	{
		strcpy(SysBuf+i, Msg[SHULIANG].str);
        i = strlen(SysBuf);
        SysBuf[i++]=',';
	}
	if (ApplVar.Size.RetQty)
	{
		strcpy(SysBuf+i, Msg[TUIHUO].str);
        i = strlen(SysBuf);
        SysBuf[i++]=',';
	}
	if (ApplVar.Size.Amt)
	{
		strcpy(SysBuf+i, Msg[JINE].str);
        i = strlen(SysBuf);
        SysBuf[i++]=',';
	}
	if (ApplVar.Size.Disc)
	{
		strcpy(SysBuf+i, Msg[SETDISC].str);
        i = strlen(SysBuf);
        SysBuf[i++]=',';
		strcpy(SysBuf+i, Msg[JINGE].str);
        i = strlen(SysBuf);
        SysBuf[i++]=',';
	}
	if (ApplVar.Size.Cost)
	{
		strcpy(SysBuf+i, Msg[CHENBEN].str);
        i = strlen(SysBuf);
        SysBuf[i++]=',';
		strcpy(SysBuf+i, Msg[MAOLI].str);
        i = strlen(SysBuf);
        SysBuf[i++]=',';
	}

	if (ApplVar.Report.Type == 8 || ApplVar.Report.Type == 13)
	{
		if (ApplVar.Report.PointerType == 1)
		{
			strcpy(SysBuf+i, cSetupCaption38);
            i = strlen(SysBuf);
            SysBuf[i++]=',';
		}
		else if (ApplVar.Report.PointerType == 5)
		{
			strcpy(SysBuf+i, cSetupCaption39);
            i = strlen(SysBuf);
            SysBuf[i++]=',';
		}
	}

	if (i)
	{
		strcpy(SysBuf+i,cCSVREPTITL);
		i = strlen(SysBuf);//		CWORD(SysBuf[i])=0x0a0d;
		if (U_WriteFile(SysBuf, i)==-1)
            ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
	}

}

//-------------------------------------------------------------------
//��ͳ��������string��ʽ����CCDBuff,�������LEFTALIGN��Χ�ڴ������Ŀ����
void usbPrintTotal()
{
	BYTE saveTaxNumber; 	//cc 20070306
	BCD saveAmt,TaxRate,saveDiscAmt;	//cc 20070306
	int i=LEFTALIGN+NUMWIDTH;

	memset(CCDBuff+i,' ',sizeof(CCDBuff)-i);
	if (ApplVar.Size.Cc)
	{//qty����
		FormatBCD(CCDBuff+i, &ApplVar.Total.Cc,(BCDLEN * 2) + 0x6400);
        CCDBuff[++i] = ',';
		i += NUMWIDTH;
	}
	if (ApplVar.Size.Qty)
	{//qty����
		FormatBCD(CCDBuff+i, &ApplVar.Total.Qty,(BCDLEN * 2) + 0x6400);
        CCDBuff[++i] = ',';
		i += NUMWIDTH;
	}
	if (ApplVar.Size.RetQty)
	{//qty����
		FormatBCD(CCDBuff+i, &ApplVar.Total.RetQty,(BCDLEN * 2) + 0x6400);
        CCDBuff[++i] = ',';
		i += NUMWIDTH;
	}
	if (ApplVar.Size.Amt)
	{
		if (ApplVar.Report.Type == 10)       /* tax report ? */
		{
			FormatBCD_DEC(CCDBuff+i, &ApplVar.Total.Amt,1);//��λС��
            CCDBuff[++i] = ',';
			i += NUMWIDTH;
		}
		else if (ApplVar.Report.Type == 11 && (ApplVar.PbF.Options & 0x0f) == 10)       /* ApplVar.PB info report */
		{
            FormatBCD_DEC(CCDBuff+i, &ApplVar.Total.Amt,2);
            CCDBuff[++i] = ',';
			i += NUMWIDTH;
		}
		else if (!ApplVar.Size.Disc)
		{
			if (ApplVar.Report.Type == 6)    /* drawer report */
			{
				if (TESTBIT(ApplVar.Draw.Options, BIT1))
				{
					FormatBCD(CCDBuff+i, &ApplVar.Total.Amt,(BCDLEN * 2) + 0x6400);
                    CCDBuff[++i] = ',';
					i += NUMWIDTH;
				}
				else
				{
#if (0) //ccr2016-11-07>>>>>>>>С������ϵͳ����һ��
					if (TESTBIT(ApplVar.Draw.Options, BIT2))
						ApplVar.AmtDecimal = 2;
					else
						ApplVar.AmtDecimal = 0;
					ApplVar.AmtDecimal += ApplVar.Draw.Options & BIT0;
#endif //ccr2016-11-07<<<<<<<<<<
                     if (ApplVar.AmtDecimal == 2)
                        FormatBCD_DEC(CCDBuff+i, &ApplVar.Total.Amt,3);//Decimal Length=3 (bit15)
                    else if (ApplVar.AmtDecimal == 3)
                        FormatBCD_DEC(CCDBuff+i, &ApplVar.Total.Amt,1);//Decimal Length=1 (bit15,bit11)
                    else
                        FormatBCD_DEC(CCDBuff+i, &ApplVar.Total.Amt,2);//Decimal Length=2

                    CCDBuff[++i] = ',';
					i += NUMWIDTH;
					ApplVar.AmtDecimal = NO_DECIMAL;
				}
			}
			else
			{
                FormatBCD_DEC(CCDBuff+i, &ApplVar.Total.Amt,2);//��λС��
                CCDBuff[++i] = ',';
				i += NUMWIDTH;
			}
		}
		else
		{
			ApplVar.Amt = ApplVar.Total.Amt;
			Subtract(&ApplVar.Amt, &ApplVar.Total.Disc);       /* calculate gross */
			if(((ApplVar.Total.Amt.Sign & 0x80)==0) && ((ApplVar.Total.Disc.Sign & 0x80)!=0))
				ApplVar.Amt.Sign = ApplVar.Total.Amt.Sign;

            FormatBCD_DEC(CCDBuff+i, &ApplVar.Amt,2);
            CCDBuff[++i] = ',';
			i += NUMWIDTH;
		}
	}
	if (ApplVar.Size.Disc)
	{
		FormatBCD_DEC(CCDBuff+i, &ApplVar.Total.Disc,2);
        CCDBuff[++i] = ',';
		i += NUMWIDTH;
		FormatBCD_DEC(CCDBuff+i, &ApplVar.Total.Amt,2);
        CCDBuff[++i] = ',';
		i += NUMWIDTH;
	}
	if (ApplVar.Size.Cost)
	{
		if (ApplVar.Report.Type == 10)
		{
            FormatBCD_DEC(CCDBuff+i, &ApplVar.Total.Disc,2);
            CCDBuff[++i] = ',';
			i += NUMWIDTH;

			FormatBCD_DEC(CCDBuff+i, &ApplVar.Total.Cost,2);
            CCDBuff[++i] = ',';
			i += NUMWIDTH;
		}
		else
		{
            FormatBCD_DEC(CCDBuff+i, &ApplVar.Total.Cost,2);
            CCDBuff[++i] = ',';
			i += NUMWIDTH;

            ApplVar.Amt = ApplVar.Total.Amt;

			Subtract(&ApplVar.Amt, &ApplVar.Total.Cost);

			FormatBCD_DEC(CCDBuff+i, &ApplVar.Amt,2);
            CCDBuff[++i] = ',';
			i += NUMWIDTH;
		}
	}
    i -= NUMWIDTH;//pointo ','
	if (ApplVar.Report.Type == 8 || ApplVar.Report.Type == 13)
	{
		if (ApplVar.Report.PointerType == 1)
		{
            i++;
			strcpy(CCDBuff+i, ApplVar.Clerk.Name);
            i = strlen(CCDBuff);
		}
		else if (ApplVar.Report.PointerType == 5)
		{
            i++;
			strcpy(CCDBuff+i, ApplVar.SalPer.Name);
            i = strlen(CCDBuff);
		}
	}

	if (i>LEFTALIGN)
	{
        CCDBuff[i++]=',';//
        strcpy(CCDBuff+i,EntryBuffer);//׷������/�տ��/����
        i = strlen(CCDBuff);
		CWORD(CCDBuff[i])=0x0a0d;
		if (U_WriteFile(CCDBuff, i+2)==-1)
            ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
	}
}




void usbPrintReportType()
{
    int i;

    memset(SysBuf, ' ', sizeof(SysBuf));
    memcpy(SysBuf + 4, ApplVar.TXT.ReportType[ApplVar.Report.Type], sizeof(ApplVar.TXT.ReportType[0]));
    i = strlen(SysBuf);
    CWORD(SysBuf[i])=0x0a0d;
    if (U_WriteFile(SysBuf, i+2)==-1)
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
}
//��ȡ����������Ŀ����:����,����CCDBuff�������LEFTALIGN��Χ��
void usbPrintGroup(WORD number)
{
    ApplVar.GroupNumber = number;
    ReadGroup();

    if (ApplVar.AP.Group.CapSize)
	{
		ApplVar.Group.Name[sizeof(ApplVar.Group.Name)-1] = 0;
		CopyFrStr(CCDBuff,ApplVar.Group.Name);
        CCDBuff[strlen(ApplVar.Group.Name)]=',';
	}
}
//��ȡ����������Ŀ��������,����CCDBuff�������LEFTALIGN��Χ��
void usbPrintDept(WORD number)
{
    ApplVar.DeptNumber = number;
    ReadDept();
/*
    if (ApplVar.AP.Dept.RandomSize)
    {
		if (!SysBuf[0])
		    SysBuf[0] = ' ';
		Htoa(SysBuf + 10, ApplVar.Dept.Random, ApplVar.AP.Dept.RandomSize);
		SysBuf[9] = '#';
    }
*/
    if (ApplVar.AP.Dept.CapSize)
	{
		ApplVar.Dept.Name[sizeof(ApplVar.Dept.Name)-1]=0;
		CopyFrStr(CCDBuff,ApplVar.Dept.Name);
        CCDBuff[strlen(ApplVar.Dept.Name)]=',';
	}
}


void usbPrintPlu(WORD number)
{
    BYTE i;
    char temp[10];
    BCD price;

    ApplVar.PluNumber = number;
    ReadPlu();
/*
    if (ApplVar.AP.Plu.RandomSize)
    {
		Htoa(SysBuf + 10, ApplVar.Plu.Random, ApplVar.AP.Plu.RandomSize);
		SysBuf[9] = SysBuf[0];          // copy number sign
	    PrintStr(SysBuf);
	    if (ApplVar.AP.Plu.CapSize)
			PrintStr(ApplVar.Plu.Name);
    }
	else
*/
	{
    	if (ApplVar.AP.Plu.CapSize)
   		{
			CopyFrStr(CCDBuff,ApplVar.Plu.Name);
            CCDBuff[strlen(ApplVar.Plu.Name)]=',';
   		}
	}
/*
	if (ApplVar.AP.Plu.InvSize && ApplVar.Report.Type == 3)
	{
		if (TESTBIT(ART_LEVEL, BIT6))
	    	PrintQty(Msg[KCSHLIANG].str, &PluInventory);    // qty
	}

    if (ApplVar.AP.Plu.PriceSize)
    {
		price = ZERO;
		strcpy(temp, Msg[JIAGE].str);
		temp[9] = 0;
		for(i = 0; i < ApplVar.AP.Plu.Level; i++)
		{
		    if (ApplVar.AP.Plu.Level > 1)
			Itoa(temp + 8, i + 1);
		    memcpy(price.Value, ApplVar.Plu.Price[i], ApplVar.AP.Plu.PriceSize);
		    PrintAmt(temp, &price);
		}
    }
*/
}


void usbPrintTender(WORD number)
{
    ApplVar.TendNumber = number;
    ReadTender();
    if (ApplVar.AP.Tend.CapSize)
    {
		ApplVar.Tend.Name[sizeof(ApplVar.Tend.Name)-1] = 0;
		CopyFrStr(CCDBuff,ApplVar.Tend.Name);
        CCDBuff[strlen(ApplVar.Tend.Name)]=',';

	} /* print number+name */
}



void usbPrintCorrec(WORD number)
{
	int i,j;

    ApplVar.CorrecNumber = number;
    ReadCorrec();

	if (ApplVar.AP.Correc.CapSize)
    {
	    j=0;
		if (ApplVar.Correc.Name[0]=='@')
			i=1;
		else
			i=0;
		for (;i<ApplVar.AP.Correc.CapSize && ApplVar.Correc.Name[i];i++)
		{
			if (ApplVar.Correc.Name[i] != '~')
			{
				CCDBuff[j] = ApplVar.Correc.Name[i];
				j++;
			}
		}
        CCDBuff[j]=',';
	}
}

void usbPrintDisc(WORD number)
{
    ApplVar.DiscNumber = number;
    ReadDisc();
    if (ApplVar.AP.Disc.CapSize)
   	{
		ApplVar.Disc.Name[sizeof(ApplVar.Disc.Name)-1] = 0;
		CopyFrStr(CCDBuff,ApplVar.Disc.Name);
        CCDBuff[strlen(ApplVar.Disc.Name)]=',';
    }
}


void usbPrintPb(WORD number)
{
    ApplVar.PbNumber = number;
    PbTotal(number+1,0);

    if (ApplVar.AP.Pb.Text && ApplVar.PB.Text[0])
   	{
		ApplVar.PB.Text[sizeof(ApplVar.PB.Text)-1] = 0;
		strcpy(CCDBuff,ApplVar.PB.Text);
    }
    else
    {
        sprintf(CCDBuff,"%s%d",Msg[ZUOHAO].str,number+1);
    }
    CCDBuff[strlen(CCDBuff)]=',';
}


void usbPrintReport(int RepFor,struct REPSIZE *S)
{
    BYTE temp, periods, periodnumber;

    WORD skip, total;
    UnLong save ;     /* unsigned long save; */
	UnLong TempL ;

	if (ApplVar.Report.Type != REPORTTYPE_MAX)          /* ApplVar.Plu inventory ? */ //lyq
	{
	    skip = 0;
		if (ApplVar.Report.PointerType)
	    {
		    skip += PeriodSkip(S, 1);
			S++;
	    }
		if (ApplVar.Report.PointerType > 1)
	    {
		    skip += PeriodSkip(S, ApplVar.AP.Clerk.Number);
			S++;
	    }
		if (ApplVar.Report.PointerType > 2)
	    {
		    skip += PeriodSkip(S, ApplVar.AP.Zone.Number);
			S++;
		}
	    if (ApplVar.Report.PointerType > 3)
		{
			skip += PeriodSkip(S, ApplVar.AP.Day.Number);
		    S++;
	    }
		if (ApplVar.Report.PointerType > 4)
	    {
		    skip += PeriodSkip(S, ApplVar.AP.SalPer.Number);
			S++;
	    }
		memcpy(&ApplVar.Size, S, sizeof(ApplVar.Size));    /* copy CONSTruction to work */
	    if (!ApplVar.Size.Length)     /* not active report */
	    	return;
	    if (!(ApplVar.Size.Periods & (0x01 << ApplVar.Report.Period))) /* not active */
	    	return;
	    temp = 0x01;
		periods = 0;
	    periodnumber = 0;
		do
	    {
		    if (temp & (0x01 << ApplVar.Report.Period))
			    periodnumber = periods;
		    if (ApplVar.Size.Periods & temp)
			    periods++;
		    temp <<= 1;
	    } while (temp < 0x10);
	    RamOffSet = ApplVar.AP.StartAddress[RepFor] + ApplVar.Report.OffSet + skip +
					(WORD)ApplVar.Report.Pointer * ApplVar.Size.Length * periods +
					(WORD)ApplVar.Size.Length * periodnumber +
					(WORD)ApplVar.Report.Start * ApplVar.Report.Size;
	}

	usbPrintTitlel();

    for (total = ApplVar.Report.Start; total < ApplVar.Report.End; total++)
    {
		save = RamOffSet;
		ReadTotal();     /* read correct total */
		if (CheckNotZero(&ApplVar.Total.RetQty))   /* Not Zero then */
		    SETBIT(ApplVar.Total.RetQty.Sign, BIT7); /* Always negative */

		if (TESTBIT(ApplVar.Total.Qty.Sign, BIT2))     /* used ? */
		{
		    ApplVar.Total.Qty.Sign &= 0x83;

		    if(ApplVar.Report.Type!=0)//ApplVar.Report.PointerType != 5 &&  ApplVar.Report.PointerType != 1)
				MemSet(CCDBuff, sizeof(CCDBuff), ' ');//Ϊ��ӡ������,�տ�Ա����,ӪҵԱ���۱���

			if (ApplVar.Report.Type != REPORTTYPE_MAX)  /* not inventory ? */ //lyq
			{
			    Add(&ApplVar.SaleQty, &ApplVar.Total.Qty);
				Add(&ApplVar.SaleAmt, &ApplVar.Total.Amt);
			}
		    switch(ApplVar.Report.Type)    {
            case 0:     /* total Sales */
                for (temp = sizeof(CCDBuff)-10;temp>0;temp--)
                {
                    if (CCDBuff[temp] && CCDBuff[temp]!=' ')
                    {
                        CCDBuff[++temp] = ',';//����CSV��ʽ�ķָ�����
                        break;
                    }
                }
			    break;
			case 1:     /* group sales */
			    usbPrintGroup(total);//��ȡ����������Ŀ����
			    break;
			case 2:     /* dept sales*/
			    usbPrintDept(total);
			    break;
			case 3:     /* plu sales*/
			    usbPrintPlu(total);
			    break;
			case 4:     /* tender */
			    usbPrintTender(total);
			    break;
//			case 5:     /* Po & Ra */
//			    PrintPoRa(total);
//			    break;
//			case 6:     /* drawer */
//			    PrintDrawer(total);
//			    break;
			case 7:     /* correction */
			    usbPrintCorrec(total);
			    break;
			case 8:     /* discount*/
			    usbPrintDisc(total);
			    break;
//			case 9:     /* foreign currency */
//			    PrintCurrency(total);
//			    break;
//			case 10: /* tax */
//			    PrintTax(total);
//			    break;
//			case 11: /* pb info */
//			    PrintPbF(total);
//			    break;
			case 13:
				usbPrintPb(total);
				break;
			default:
			    return;
		    }
		    usbPrintTotal();//��ӱ���������

			RamOffSet = save;       /* reset address pointer */

            //ccr20140403 Ӣ�İ����ͨ�տ����Ҫ����Grand Total�ۼ������ü�������ÿ��Z-report�����
            if (ApplVar.Report.Type!=0 || ApplVar.Report.Period!=0 || (TESTBIT(DBLHIPRN,BIT6))) //ccr2016-02-23
                ResetReport();
		}

        RamOffSet = save + ApplVar.Report.Size;
    }
}


void usbPrintPluReport(int RepFor)
{
    ApplVar.Report.End = ApplVar.AP.Plu.Number;
    if (ApplVar.AP.Plu.RandomSize)
		ApplVar.Report.End =ApplVar.AP.Plu.RNumber;     /* calculate bytes to move 2nd part */
    if (!ApplVar.Report.End)
		return;
    ApplVar.Report.OffSet = ApplVar.AP.Plu.TotalOffSet;
    ApplVar.Report.Size = ApplVar.AP.Plu.RecordSize;
    usbPrintReport(RepFor,ApplVar.AP.Plu.Size);
}


void usbPrintDeptReport()
{
    if (!ApplVar.AP.Dept.Number)
	return;
    ApplVar.Report.End = ApplVar.AP.Dept.Number;
    ApplVar.Report.OffSet = ApplVar.AP.Dept.TotalOffSet;
    ApplVar.Report.Size = ApplVar.AP.Dept.RecordSize;
    usbPrintReport(AddrDept,ApplVar.AP.Dept.Size);
}

void usbPrintGroupReport()
{
    if (!ApplVar.AP.Group.Number)
	return;
    ApplVar.Report.End = ApplVar.AP.Group.Number;
    ApplVar.Report.OffSet = ApplVar.AP.Group.TotalOffSet;
    ApplVar.Report.Size = ApplVar.AP.Group.RecordSize;
    usbPrintReport(AddrGroup,ApplVar.AP.Group.Size);
}


void usbPrintTendReport()
{
    if (!ApplVar.AP.Tend.Number)
	return;
    ApplVar.Report.End = ApplVar.AP.Tend.Number;
    ApplVar.Report.OffSet = ApplVar.AP.Tend.TotalOffSet;
    ApplVar.Report.Size = ApplVar.AP.Tend.RecordSize;
    usbPrintReport(AddrTend,ApplVar.AP.Tend.Size);
}

/*
void usbPrintPoRaReport()
{
    if (!ApplVar.AP.PoRa.Number)
	return;
    ApplVar.Report.End = ApplVar.AP.PoRa.Number;
    ApplVar.Report.OffSet = ApplVar.AP.PoRa.TotalOffSet;
    ApplVar.Report.Size = ApplVar.AP.PoRa.RecordSize;
    usbPrintReport(AddrPoRa,ApplVar.AP.PoRa.Size);
}


void usbPrintCurrReport()
{
    if (!ApplVar.AP.Curr.Number)
	return;
    ApplVar.Report.End = ApplVar.AP.Curr.Number;
    ApplVar.Report.OffSet = ApplVar.AP.Curr.TotalOffSet;
    ApplVar.Report.Size = ApplVar.AP.Curr.RecordSize;
    usbPrintReport(AddrCurr,ApplVar.AP.Curr.Size);
}


void usbPrintDrawReport()
{
    if (!ApplVar.AP.Draw.Number)
	return;
    ApplVar.Report.End = ApplVar.AP.Draw.Number;
    ApplVar.Report.OffSet = ApplVar.AP.Draw.TotalOffSet;
    ApplVar.Report.Size = ApplVar.AP.Draw.RecordSize;
    usbPrintReport(AddrDrawer,ApplVar.AP.Draw.Size);
}
*/

void usbPrintCorrecReport()
{
    if (!ApplVar.AP.Correc.Number)
	return;
    ApplVar.Report.End = ApplVar.AP.Correc.Number;
    ApplVar.Report.OffSet = ApplVar.AP.Correc.TotalOffSet;
    ApplVar.Report.Size = ApplVar.AP.Correc.RecordSize;
    usbPrintReport(AddrCorr,ApplVar.AP.Correc.Size);
}

void usbPrintDiscReport()
{
    if (!ApplVar.AP.Disc.Number)
	return;
    ApplVar.Report.End = ApplVar.AP.Disc.Number;
    ApplVar.Report.OffSet = ApplVar.AP.Disc.TotalOffSet;
    ApplVar.Report.Size = ApplVar.AP.Disc.RecordSize;
    usbPrintReport(AddrDisc,ApplVar.AP.Disc.Size);
}

/*
void usbPrintTaxReport()
{
    if (!ApplVar.AP.Tax.Number)
	return;
    ApplVar.Report.End = ApplVar.AP.Tax.Number;
    ApplVar.Report.OffSet = ApplVar.AP.Tax.TotalOffSet;
    ApplVar.Report.Size = ApplVar.AP.Tax.RecordSize;
    usbPrintReport(AddrTax,ApplVar.AP.Tax.Size);
}


void usbPrintPbFReport()
{
    if (!ApplVar.AP.Pb.Number || !ApplVar.AP.Pb.NumberOfPb)
	return;
    ApplVar.Report.End = ApplVar.AP.Pb.Number;
    ApplVar.Report.OffSet = ApplVar.AP.Pb.TotalOffSet;
    ApplVar.Report.Size = ApplVar.AP.Pb.RecordSize;
    usbPrintReport(AddrPBf,ApplVar.AP.Pb.Size);
}
*/
void usbPrintPbtReport()
{
    if (!ApplVar.AP.Pb.Number || !ApplVar.AP.Pb.NumberOfPb)
		return;
    ApplVar.Report.End = ApplVar.AP.Pb.NumberOfPb;
    ApplVar.Report.OffSet = ApplVar.AP.Pb.PBTTotalOffset;
    ApplVar.Report.Size = ApplVar.AP.Pb.PBTRecordSize;
    usbPrintReport(AddrPBt,ApplVar.AP.Pb.PBTSize);
}


void usbPrintPointReport()
{
	int i=1;

    ApplVar.SaleAmt = ZERO;
    ApplVar.SaleQty = ZERO;
    switch(ApplVar.Report.Type) {
	case 0://Print TOTALSALES recordes
	    ApplVar.Report.End = 1;
	    ApplVar.Report.Size = ApplVar.AP.Sales.RecordSize;
	    ApplVar.Report.OffSet = 0;
	    usbPrintReport(AddrTotl,ApplVar.AP.Sales.Size);
	    break;
	case 1:
	    usbPrintGroupReport();
	    break;
	case 2:
	    usbPrintDeptReport();
	    break;
	case 3:
	    usbPrintPluReport(AddrPLU);
	    break;
	case 4:
	    usbPrintTendReport();
	    break;
/*
	case 5:
	    PrintPoRaReport();
	    break;
	case 6:
	    PrintDrawReport();
	    break;
*/
	case 7:
	    usbPrintCorrecReport();
	    break;
	case 8:
	    usbPrintDiscReport();
	    break;
/*
	case 9:
	    PrintCurrReport();
	    break;
	case 10:
	    PrintTaxReport();
	    break;
	case 11:
	    PrintPbFReport();
	    break;
	case 12:
	    PrintOpenPb();
	    break;
*/
	case 13:
		usbPrintPbtReport();
		break;
//	case REPORTTYPE_MAX:                         /* open table */
//	    usbPrintPluReport(AddrRPLU);
//	    break;
	default :
	    break;
    }
}

//////////////////////////////////////////////////////////////
//ʹ��CCDBuff���������ɵ�һ�б�������
//ʹ��SysBuf��ProgLineMes��Ϊ��ʱ���ݹ�����
void usbGetReport(BYTE repnum)
{
#define TITLELEFT	25  //TITLELEFT֮ǰΪ���ں�ʱ��"2000��01��02�� 22:44:23,"

	int i;
    char flag;


    ApplVar.SaveClerk = ApplVar.ClerkNumber;
	ApplVar.SaveSalPer = ApplVar.SalPerNumber;


	//WORDtoASCZero(SysBuf+7, ApplVar.AP.Flag[15]);//�տ������
	ApplVar.Report.System= 0;	ApplVar.Report.Period= 0;	ApplVar.Report.Start = 0;
	ApplVar.Report.PointerType = 0;	ApplVar.Report.Pointer = 0;
    ApplVar.Report.PointerEnd = 1;

    memset(ProgLineMes,' ',sizeof(ProgLineMes));

	switch (repnum){
	case usbReportType0 :				//"   ��  ��  ��   ",
		ApplVar.Report.Type = 0;
		CopyFrStr(SysBuf,TOTALREP);     //�ļ�����
		strcpy(ProgLineMes+TITLELEFT,cReportType0);//�������
	    break;
	case usbReportType1 :        //" ��  ��  ��  �� ",//1
		ApplVar.Report.Type = 1;
		CopyFrStr(SysBuf,GROUPREP);
		strcpy(ProgLineMes+TITLELEFT,cReportType1);
	    break;
	case usbReportType2 :        //" ��  ��  ��  �� ",//2
		ApplVar.Report.Type = 2;
		CopyFrStr(SysBuf,DEPTREP);
		strcpy(ProgLineMes+TITLELEFT,cReportType2);
	    break;
	case usbReportType3 :        //" ��  Ʒ  ��  �� ",      /* 3 Used with ApplVar.Plu ApplVar.Report */
		ApplVar.Report.Type = 3;
		CopyFrStr(SysBuf,PLUREP);
		strcpy(ProgLineMes+TITLELEFT,cReportType3);
	    break;
//	case usbReportType4 :        //" ��  ��  ��  Ϣ ",//4
//		ApplVar.Report.Type = 3;
//		CopyFrStr(SysBuf,TENDREP);
//		strcpy(ProgLineMes,ReportType4);
	    break;
	case usbReportType7 :        //" ��  ��  ��  Ϣ ",//7
		ApplVar.Report.Type = 7;
		CopyFrStr(SysBuf,CORREPTREP);
		strcpy(ProgLineMes+TITLELEFT,cReportType7);
	    break;
	case usbReportType8 :        //" ��  ��  ��  Ϣ ",//8
		ApplVar.Report.Type = 8;
		CopyFrStr(SysBuf,DISCREP);
		strcpy(ProgLineMes+TITLELEFT,cReportType8);
	    break;
//	case usbReportType11:        //" ��  ��  ��  Ϣ ",//11
//	case usbReportType12:        //" ��  ̨  ��  Ϣ ",//12
	case usbReportType13:        //" ��  ̨  ��  Ϣ ",//13
		ApplVar.Report.Type = 13;
		CopyFrStr(SysBuf,PBTOTALREP);
		strcpy(ProgLineMes+TITLELEFT,cReportType13);
		break;
	case usbReportType17:       	//"    �� �� Ա ͳ ��   ",
		ApplVar.Report.Type = 0;
		ApplVar.Report.PointerType = 1;
        ApplVar.Report.PointerEnd = ApplVar.AP.Clerk.Number;

		CopyFrStr(SysBuf,CLERKREP);
		strcpy(ProgLineMes+TITLELEFT,cReportType17);
		break;
	case usbReportType18:  				//"    Ӫ ҵ Ա ͳ ��   ",
		ApplVar.Report.Type = 0;
		ApplVar.Report.PointerType = 5;
        ApplVar.Report.PointerEnd = ApplVar.AP.SalPer.Number;
		CopyFrStr(SysBuf,SALPERREP);
		strcpy(ProgLineMes+TITLELEFT,cReportType18);
		break;
	case usbReportType19:       	//"  �տ�Ա �ۿ� ͳ ��   ",
		ApplVar.Report.Type = 8;
		ApplVar.Report.PointerType = 1;
        ApplVar.Report.PointerEnd = ApplVar.AP.Clerk.Number;

		CopyFrStr(SysBuf,CLERKREP);
		CopyFrStr(ProgLineMes+TITLELEFT,cSetupCaption38);
		strcpy(ProgLineMes+8+TITLELEFT,cReportType8);
		break;
	case usbReportType20:  				//"  ӪҵԱ �ۿ� ͳ ��   ",
		ApplVar.Report.Type = 8;
		ApplVar.Report.PointerType = 5;
        ApplVar.Report.PointerEnd = ApplVar.AP.SalPer.Number;

		CopyFrStr(SysBuf,SALPERREP);
		CopyFrStr(ProgLineMes+TITLELEFT,cSetupCaption39);
		strcpy(ProgLineMes+8+TITLELEFT,cReportType8);
		break;
	case usbReportType21:       	//"  �տ�Ա ��̨ ͳ ��   ",
		ApplVar.Report.Type = 13;
		ApplVar.Report.PointerType = 1;
        ApplVar.Report.PointerEnd = ApplVar.AP.Clerk.Number;

		CopyFrStr(SysBuf,CLERKREP);
		CopyFrStr(ProgLineMes+TITLELEFT,cSetupCaption38);
		strcpy(ProgLineMes+8+TITLELEFT,cReportType13);
		break;
	case usbReportType22:  				//"  ӪҵԱ ��̨ ͳ ��   ",
		ApplVar.Report.Type = 13;
		ApplVar.Report.PointerType = 5;
        ApplVar.Report.PointerEnd = ApplVar.AP.SalPer.Number;

		CopyFrStr(SysBuf,SALPERREP);
		CopyFrStr(ProgLineMes+TITLELEFT,cSetupCaption39);
		strcpy(ProgLineMes+8+TITLELEFT,cReportType13);
		break;
	default:
		return;

	}


    //CSV�ļ�����Ϊ****_D/P/R.CSV, D-�ۿ�ͳ�Ʊ���,P-��̨ͳ��,R-���۱���
//    if (CSV_FORMAT)
    {
        switch (repnum){
            case usbReportType19:
            case usbReportType20:
                SysBuf[7]='D';//	SysBuf[10]='I';SysBuf[11]='S';SysBuf[12]=0;
                break;
            case usbReportType21:
            case usbReportType22:
                SysBuf[7]='P';//	SysBuf[10]='B';SysBuf[11]='T';SysBuf[12]=0;
                break;
            default:
                SysBuf[7]='R';//	SysBuf[10]='E';SysBuf[11]='P';SysBuf[12]=0;
                break;
        }
        SysBuf[8]='.';	SysBuf[9]='C';	SysBuf[10]='S';SysBuf[11]='V';SysBuf[12]=0;
    }
/*    else
    {
        SysBuf[7]='R';SysBuf[8]='.';

        switch (repnum){
            case usbReportType19:
            case usbReportType20:
                SysBuf[9]='D';	SysBuf[10]='I';SysBuf[11]='S';SysBuf[12]=0;
                break;
            case usbReportType21:
            case usbReportType22:
                SysBuf[9]='P';	SysBuf[10]='B';SysBuf[11]='T';SysBuf[12]=0;
                break;
            default:
                SysBuf[9]='R';	SysBuf[10]='E';SysBuf[11]='P';SysBuf[12]=0;
                break;
        }
    }
*/

	DispSt1(SysBuf);
	//�򿪻򴴽���ű������ݵ��ļ�
//	if (ApplVar.FReport==X || U_OpenFile(SysBuf,(FA_OPEN_ALWAYS|FA_WRITE)))//==Xʱ,�����ļ�; ==Zʱ׷���ļ� //
	if (U_OpenFile(SysBuf,(FA_OPEN_ALWAYS|FA_WRITE)))
	{
		ApplVar.ErrorNumber = ERROR_ID(CWXXI77);
		return;
	}
	else if (U_FileSize())
	{//�ļ�����ʱ,��λ���ļ������
		if (U_LocateFile(0xffffffff))
		{
			U_CloseFile();
			ApplVar.ErrorNumber=ERROR_ID(CWXXI77);
			return;
		}
		TitleFlag = 1;//��д�����
	}
    else//Ϊ���ļ�,д�뱨������
    {
        i = strlen(ProgLineMes);
        ProgLineMes[i++]='(';
        if (ApplVar.CentralLock == X)
            ProgLineMes[i++]='X';
        else
            ProgLineMes[i++]='Z';
        ProgLineMes[i++]=')';

        CWORD(ProgLineMes[i])=0x0a0d;

        if (U_WriteFile(ProgLineMes, i+2)==-1)// д�뱨������ //
        {
			U_CloseFile();
            ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
            return;
        }
		TitleFlag = 0;//��Ҫ���ļ��п�ʼλ��д�����
    }

//    if (!SetUpReport())
    {
		for(ApplVar.Report.Pointer = 0;ApplVar.Report.Pointer < ApplVar.Report.PointerEnd; ApplVar.Report.Pointer++)
		{
		    if (ApplVar.Report.PointerType == 1)
		    {//report for clerk(�տ�Ա����)
				ApplVar.ClerkNumber = ApplVar.Report.Pointer + 1;
				ReadClerk();
				if (TRAINING &&
					TESTBIT(ApplVar.AP.ReportList[repnum].Options, BIT1) &&
					!TESTBIT(CLERKFIX, BIT6))
				       /* all pointers then skip training clerk ? */
				    continue;
		    }
			 memset(CCDBuff,' ',sizeof(CCDBuff));
		    if((ApplVar.Report.PointerType == 5 || ApplVar.Report.PointerType == 1))
	     	{
//			 	if (ApplVar.Report.Type!=8 && ApplVar.Report.Type!=13 && CheckTotal() == 0)
			 	if (ApplVar.Report.Type==0 && CheckTotal() == 0)
			     	continue;

			    if(ApplVar.Report.PointerType == 1)
		    	{
		    		if (ApplVar.AP.Clerk.Number)
		    		{
			            ApplVar.ClerkNumber = ApplVar.Report.Pointer + 1;
			            ReadClerk();
		    	        CopyFrStr(CCDBuff,ApplVar.Clerk.Name);
		    		}
			    }
				else
				{
#if (salNumber)
                    if (ApplVar.AP.SalPer.Number)
                    {
                        ApplVar.SalPerNumber = ApplVar.Report.Pointer + 1;
                        ReadSalPer();
                        CopyFrStr(CCDBuff,ApplVar.SalPer.Name);
                    }
                    else
#endif
                    {
                        CCDBuff[0] = '-';CCDBuff[1] = '-';
                    }
				}
	    	}
            else if (ApplVar.Report.Type == 0)//������
            {
                CopyFrStr(CCDBuff,ApplVar.TXT.ReportType[0]);
            }
			usbPrintPointReport();
		    if (ApplVar.ErrorNumber)
				 break;
		}
    }

    ApplVar.ClerkNumber = ApplVar.SaveClerk;
	ReadClerk();
#if (salNumber)
	ApplVar.SalPerNumber = ApplVar.SaveSalPer;
	ReadSalPer();
#endif
	U_CloseFile();
}

//////////////////////////////////////////////////////////////////////////////////
//ʹ��EntryBuffer��������,�տ���ź͵��̺�,����׷�ӵ�ÿ������������֮��.
//���,����ȷ���������ط�û��ʹ��EntryBuffer
//////////////////////////////////////////////////////////////////////////////////
void ReportToUSB()
{
	int i;

	xCHECKUSBDISK();
	U_ResetFolder();
    Backup_Restore= BACKUPECR;
	memset(SysBuf,' ',SCREENWD-4);
	DispSt1(SysBuf);

    memset(EntryBuffer,' ',ENTRYSIZE);

    i=DateTimeToStr(EntryBuffer,3);//��ȡ����ʱ��
    EntryBuffer[i++]=',';//CSV�ָ�����
    sprintf(EntryBuffer+i,"%u,%u",REGISTER & 0xff,LOCATION  & 0xff);

	usbGetReport(usbReportType0 );				//"   ��  ��  ��   ",
    xCHECKUSBDISK();
	usbGetReport(usbReportType1 );        //" ��  ��  ��  �� ",//1
    xCHECKUSBDISK();
	usbGetReport(usbReportType2 );        //" ��  ��  ��  �� ",//2
    xCHECKUSBDISK();
	usbGetReport(usbReportType3 );        //" ��  Ʒ  ��  �� ",
    xCHECKUSBDISK();
	usbGetReport(usbReportType7 );        //" ��  ��  ��  Ϣ ",//7
    xCHECKUSBDISK();
	usbGetReport(usbReportType17);       	//"    �� �� Ա ͳ ��   ",
    xCHECKUSBDISK();
	usbGetReport(usbReportType18);  		//"    Ӫ ҵ Ա ͳ ��   ",
    xCHECKUSBDISK();

	usbGetReport(usbReportType8 );        //" ��  ��  ��  Ϣ ",//8
    xCHECKUSBDISK();
	usbGetReport(usbReportType19);       	//"    �� �� Ա �ۿ� ͳ ��   ",
    xCHECKUSBDISK();
	usbGetReport(usbReportType20);  		//"    Ӫ ҵ Ա �ۿ� ͳ ��   ",
    xCHECKUSBDISK();

	usbGetReport(usbReportType13);        //" ��  ̨  ��  Ϣ ",//13
    xCHECKUSBDISK();
	usbGetReport(usbReportType21);       	//"    �� �� Ա ��̨ ͳ ��   ",
    xCHECKUSBDISK();
	usbGetReport(usbReportType22);  		//"    Ӫ ҵ Ա ��̨ ͳ ��   ",
}


//////////////////////////////////////////////////////////////////////////////
///���������ļ����ܺ�����
//////////////////////////////////////////////////////////////////////////////
void usbALLTheFile()    //Ccrȫ���ļ�  //
{
 	BYTE i;

	xCHECKUSBDISK();

#if FILETOCSV
    if (!SelectCSV_BIN()) return;
#else
    APPLCTRL &= 0xfe;//BIN Format only, disable CSV_FORMAT
#endif


	switch (Backup_Restore){
	case BACKUPECR:
        DispStrXY(Msg[usbDAOCHU].str,0,0);
		RJPrint(0,Msg[usbDAOCHU].str);
		break;
	case RESTOREECR:
		DispStrXY(Msg[usbDAORU].str,0,0);
        RJPrint(0,Msg[usbDAORU].str);
		break;
	}

	U_ResetFolder();

	if (MenuFuncIdx==1)
 	{// ����ȫ���ļ� //
 		for (i=0;i<usbFILEITEMS-1;i++)
		{
			BackupECRFiles(i);
		}
 	}
	else
		BackupECRFiles(MenuFuncIdx-2);
    SETBIT(ApplVar.MyFlags,PRNHEADMUST);
	CutRPaper(3);
}

/*��CSV�ı��ļ��е����ļ�����*/
int Inport_DEPT()
{
    vCHECKCSV(-1);
}
int Inport_PLU()
{
    vCHECKCSV(-1);
}
int Inport_TAX()
{
    vCHECKCSV(-1);
}
int Inport_HEADER()
{
    vCHECKCSV(-1);
}
int Inport_DISC()
{
    vCHECKCSV(-1);
}
int Inport_SALPER()
{
    vCHECKCSV(-1);
}
int Inport_SYSTEM()
{
    vCHECKCSV(-1);
}
int Inport_COMM()
{
    vCHECKCSV(-1);
}
int Inport_GRAPPRN()
{
    vCHECKCSV(-1);
}
int Inport_GROUP()
{
    vCHECKCSV(-1);
}
int Inport_ICCARD()
{
    vCHECKCSV(-1);
}
int Inport_PROM()
{
    vCHECKCSV(-1);
}
int Inport_PBFUNC()
{
    vCHECKCSV(-1);
}
int Inport_CLERK()
{
    vCHECKCSV(-1);
}
int Inport_MODI()
{
    vCHECKCSV(-1);
}
int Inport_PBTOTAL()
{
    vCHECKCSV(-1);
}
int Inport_ZONE()
{
    vCHECKCSV(-1);
}
int Inport_KEYBOARD()
{
    vCHECKCSV(-1);
}
int Inport_OFF()
{
    vCHECKCSV(-1);
}
int Inport_PORA()
{
    vCHECKCSV(-1);
}
int Inport_TRAILER()
{
    vCHECKCSV(-1);
}
int Inport_SLIPHEAD()
{
    vCHECKCSV(-1);
}
int Inport_ICBLOCK()
{
    vCHECKCSV(-1);
}


/*��CSV�ı���ʽ���������ļ��е�����*/
int Export_DEPT()
{
    int i,j;

    vCHECKCSV(-1);
    FormatToCSV(ApplVar.Dept.Random,     HEXTYPE,sizeof(ApplVar.Dept.Random),0);/* max 7 bytes is 14 digits */
    FormatToCSV(ApplVar.Dept.Name,       STRTYPE,sizeof(ApplVar.Dept.Name),1); /* max 24 with terminator */
    FormatToCSV(&ApplVar.Dept.Group,     BYTETYPE,sizeof(BYTE),6);
    FormatToCSV(&ApplVar.Dept.Print,     BYTETYPE,sizeof(BYTE),6);
    FormatToCSV(&ApplVar.Dept.Options,   OPTTYPE,sizeof(BYTE),6);
    FormatToCSV(&ApplVar.Dept.Tax,       OPTTYPE,sizeof(BYTE),6);
    FormatToCSV(&ApplVar.Dept.Kp,        OPTTYPE,sizeof(BYTE),6);
    FormatToCSV(ApplVar.Dept.Price,      HAMTTYPE,sizeof(ApplVar.Dept.Price),4);/* max price is 10 digits is 5 bytes */
    i = FormatToCSV(ApplVar.Dept.PriceMax,HAMTTYPE,sizeof(ApplVar.Dept.PriceMax),0xff); /* max 4 levels with 1 cost price */


    if ((j=U_WriteFile(CCDBuff,i))==-1)
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
        return -1;
    }
    else
        return j;
}
//����һ�ʵ�Ʒ��CSV��ʽ����
//�ɹ�ʱ�������ɵ��ַ����ĳ���
//ʧ��ʱ����-1
int Export_PLU()
{
    int i,j;
    WORD Plu_Dept;

    vCHECKCSV(-1);
    FormatToCSV(ApplVar.Plu.Random,     HEXTYPE,sizeof(ApplVar.Plu.Random),0);/* max 7 bytes is 14 digits */
    FormatToCSV(ApplVar.Plu.Name,       STRTYPE,sizeof(ApplVar.Plu.Name),1); /* max 24 with terminator */
	Plu_Dept = ApplVar.Plu.OFFIndex;
    FormatToCSV(&Plu_Dept,  WORDTYPE,sizeof(WORD),1);// Index of OFFPrice
    Plu_Dept = (ApplVar.Plu.DeptHi<<8) + ApplVar.Plu.Dept;//�Թ�������������.
    FormatToCSV(&Plu_Dept,              WORDTYPE,sizeof(WORD),2);/* department selection max 0xff */
    for (i=0;i<4;i++)
        FormatToCSV(ApplVar.Plu.Price[i],HAMTTYPE,5,4);/* max price is 10 digits is 5 bytes */
    FormatToCSV(ApplVar.Plu.Cost,       HAMTTYPE,sizeof(ApplVar.Plu.Cost),5); /* max 4 levels with 1 cost price */

	Plu_Dept = ApplVar.Plu.Link;
    FormatToCSV(&Plu_Dept,      WORDTYPE,sizeof(WORD),6);/* PLU Link */
    i = FormatToCSV(&ApplVar.Plu.Inventory,QTYTYPE,sizeof(ApplVar.Plu.Inventory),0xff);/* plu inventory */

    if ((j=U_WriteFile(CCDBuff,i))==-1)
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
        return -1;
    }
    else
        return j;
}

int Export_TAX()
{
    int i,j;

    vCHECKCSV(-1);
    FormatToCSV(ApplVar.Tax.Name,       STRTYPE,sizeof(ApplVar.Tax.Name),0);
    FormatToCSV(ApplVar.Tax.Rate,       HAMTTYPE,sizeof(ApplVar.Tax.Rate),1);
    i = FormatToCSV(&ApplVar.Tax.Options,OPTTYPE,sizeof(ApplVar.Tax.Options),0xff);

    if ((j=U_WriteFile(CCDBuff,i))==-1)
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
        return -1;
    }
    else
        return j;
}

int Export_HEADER()
{
    int j,k;
    WORD i;

    vCHECKCSV(-1);
    for (k=0;k<8;k++)
    {
        if (ApplVar.TXT.Header[k][0])
        {
            i=k+1;
            FormatToCSV(&i,      WORDTYPE,sizeof(WORD),0);
            j = FormatToCSV(ApplVar.TXT.Header[k],STRTYPE,PRTLEN+1,0xff);
            if ((j=U_WriteFile(CCDBuff,i))==-1)
            {
                ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
                return -1;
            }
        }
        else
            break;
    }
    return k;
}

int Export_DISC()
{
    int i,j;

    vCHECKCSV(-1);
    FormatToCSV(ApplVar.Disc.Name,       STRTYPE,sizeof(ApplVar.Disc.Name),0);
    FormatToCSV(&ApplVar.Disc.Print,     BYTETYPE,sizeof(BYTE),1);
    FormatToCSV(&ApplVar.Disc.Options,   OPTTYPE,1,2);
    FormatToCSV(ApplVar.Disc.Fixed,      HAMTTYPE,sizeof(ApplVar.Disc.Fixed),3);
    FormatToCSV(&ApplVar.Disc.Tax,       OPTTYPE,1,4);
    i = FormatToCSV(ApplVar.Disc.Max,    HAMTTYPE,sizeof(ApplVar.Disc.Max),0xff);

    if ((j=U_WriteFile(CCDBuff,i))==-1)
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
        return -1;
    }
    else
        return j;
}

int Export_SALPER()
{
    int i,j;

    vCHECKCSV(-1);
    FormatToCSV(ApplVar.SalPer.Name,        STRTYPE,sizeof(ApplVar.SalPer.Name),0);
    i = FormatToCSV(&ApplVar.SalPer.Options,OPTTYPE,1,0xff);

    if ((j=U_WriteFile(CCDBuff,i))==-1)
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
        return -1;
    }
    else
        return j;
}

//========================================================
#if FILETOCSV
CONST FSTRING SYSTEMFLAGS[64]={
"NO_DECIMAL",     //ApplVar.AP.Flag[0]
"COMMA",          //ApplVar.AP.Flag[1]
"AM_PM",          //ApplVar.AP.Flag[2]
"TIME_DATE",      //ApplVar.AP.Flag[3]
"KEYTONE",        //ApplVar.AP.Flag[4]
"PRN_ITEMS",      //(ApplVar.AP.Flag[5]
"SLIP_TOP",       //ApplVar.AP.Flag[6]
"SLIP_MAX",       //ApplVar.AP.Flag[7]
"SLIPINFO",       //ApplVar.AP.Flag[8]
"CLERKFIX",       //ApplVar.AP.Flag[9]
"PREFIX_1",       //ApplVar.AP.Flag[10]
"PREFIX_2",       //ApplVar.AP.Flag[11]
"PRICE_LEVEL",    //ApplVar.AP.Flag[12]
"PVAT",           //ApplVar.AP.Flag[13]
"LOCATION",       //ApplVar.AP.Flag[14]
"REGISTER",       //ApplVar.AP.Flag[15]
"SECOND",         //ApplVar.AP.Flag[16]
"DENSITY",        //ApplVar.AP.Flag[17]
"PBINFO",         //ApplVar.AP.Flag[18]
"PBPRINT",        //ApplVar.AP.Flag[19]
"COMPUTER_1",       //ApplVar.AP.Flag[20]
"ACTIVE",         //ApplVar.AP.Flag[21]
"CUTTER",         //ApplVar.AP.Flag[22]
"ART_LEVEL",      //ApplVar.AP.Flag[23]
"PLU_PRINT",      //ApplVar.AP.Flag[24]
"DOT",            //ApplVar.AP.Flag[25]
"DBLHIPRN",       //ApplVar.AP.Flag[26]
"PROMOTION",      //ApplVar.AP.Flag[27]
"BALANCE",        //ApplVar.AP.Flag[28]
"LMARGE",         //ApplVar.AP.Flag[29]
"BARCODE",        //ApplVar.AP.Flag[30]
"SLIP",           //ApplVar.AP.Flag[31]
"SLIPPORT_1",       //ApplVar.AP.Flag[32]
"CHARSET",        //ApplVar.AP.Flag[33]

"KP1_Type",       //ApplVar.AP.Flag[34]
"KP1_PORT",       //ApplVar.AP.Flag[35]
"KP1_ALTER",      //ApplVar.AP.Flag[36]
"KP2_Type",       //ApplVar.AP.Flag[37]
"KP2_PORT",       //ApplVar.AP.Flag[38]
"KP2_ALTER",      //ApplVar.AP.Flag[39]
"KP3_Type",       //ApplVar.AP.Flag[40]
"KP3_PORT",       //ApplVar.AP.Flag[41]
"KP3_ALTER",      //ApplVar.AP.Flag[42]
"KP4_Type",       //ApplVar.AP.Flag[43]
"KP4_PORT",       //ApplVar.AP.Flag[44]
"KP4_ALTER",      //ApplVar.AP.Flag[45]
"KP5_Type",       //ApplVar.AP.Flag[46]
"KP5_PORT",       //ApplVar.AP.Flag[47]
"KP5_ALTER",      //ApplVar.AP.Flag[48]
"KP6_Type",       //ApplVar.AP.Flag[49]
"KP6_PORT",       //ApplVar.AP.Flag[50]
"KP6_ALTER",      //ApplVar.AP.Flag[51]
"KP7_Type",       //ApplVar.AP.Flag[52]
"KP7_PORT",       //ApplVar.AP.Flag[53]
"KP7_ALTER",      //ApplVar.AP.Flag[54]
"KP8_Type",       //ApplVar.AP.Flag[55]
"KP8_PORT",       //ApplVar.AP.Flag[56]
"KP8_ALTER",      //ApplVar.AP.Flag[57]

"KPPRICE",        //ApplVar.AP.Flag[58]
"EXTREMAIN",      //ApplVar.AP.Flag[59]
"SLFLAG",         //ApplVar.AP.Flag[60]
"EXTRAMN",        //ApplVar.AP.Flag[61]
"COPYRECEIP",     //ApplVar.AP.Flag[62]
"ROUNDMASK"      //ApplVar.AP.Flag[63]
};
#endif

//========================================================
int Export_SYSTEM()
{
    vCHECKCSV(-1);
}
int Export_COMM()
{
    vCHECKCSV(-1);
}
int Export_GRAPPRN()
{
    vCHECKCSV(-1);
}
int Export_GROUP()
{
    vCHECKCSV(-1);
}
int Export_ICCARD()
{
    vCHECKCSV(-1);
}
int Export_PROM()
{
    vCHECKCSV(-1);
}
int Export_PBFUNC()
{
    vCHECKCSV(-1);
}
int Export_CLERK()
{
    vCHECKCSV(-1);
}
int Export_MODI()
{
    vCHECKCSV(-1);
}
int Export_PBTOTAL()
{
    vCHECKCSV(-1);
}
int Export_ZONE()
{
    vCHECKCSV(-1);
}
int Export_KEYBOARD()
{
    vCHECKCSV(-1);
}
int Export_OFF()
{
    vCHECKCSV(-1);
}
int Export_PORA()
{
    vCHECKCSV(-1);
}
int Export_TRAILER()
{
    vCHECKCSV(-1);
}
int Export_SLIPHEAD()
{
    vCHECKCSV(-1);
}
int Export_ICBLOCK()
{
    vCHECKCSV(-1);
}
/////////////////////////////////////////////////////////////////////////////
// Back up Depart data from ECR to UDisk
BYTE BackupECRFiles(int fileID)
{
	WORD sSaveNumber;
	WORD *sRecIndex;
	WORD sRacMax;
	WORD sRecSize;
	char *sRcrBuffer;
	void    (*ReadFromFile)();
	void    (*WriteToFile)();
    int    (*BackupToCSV)();
    int    (*RestoreFromCSV)();


	INT i,j;

    vCHECKUSBDISK(-1);

    BackupToCSV = EcrFileObj[fileID].ExportECRFile;
    RestoreFromCSV = EcrFileObj[fileID].InportECRFile;

	ReadFromFile = EcrFileObj[fileID].ReadECRFile;
	WriteToFile = EcrFileObj[fileID].WriteECRFile;
	sRecIndex = EcrFileObj[fileID].RECIndex;

	if (sRecIndex)
    {
		sSaveNumber = *(EcrFileObj[fileID].RECIndex);
    	sRacMax = *(EcrFileObj[fileID].RECMax);
    }
    sRecSize = EcrFileObj[fileID].RECSize;
    sRcrBuffer =  EcrFileObj[fileID].RECBuffer;

    ProgLineMes[0]=' ';
	strcpy(ProgLineMes+1,EcrFileObj[fileID].FileName);
    i = strlen(ProgLineMes);
    ProgLineMes[i++] = '.';
    if (CSV_FORMAT)
    {//CSV�ļ���ʽ****.CSV
        ProgLineMes[i++]='C';ProgLineMes[i++]='S';ProgLineMes[i++]='V';
    }
    else
    {//�������ļ���ʽ****.REC
        ProgLineMes[i++]='R';ProgLineMes[i++]='E';ProgLineMes[i++]='C';
    }
    ProgLineMes[i]=0;

	switch (Backup_Restore){
	case BACKUPECR:
		if (U_CreateFile(ProgLineMes+1))
		{
			ApplVar.ErrorNumber=ERROR_ID(CWXXI80);
			return FALSE;
		}
		ProgLineMes[0]='>';

		if (fileID==usbDANPIN-usbBULEI && ApplVar.AP.Plu.RandomSize)
			sRacMax = ApplVar.AP.Plu.RNumber;
		DispStrXY(Msg[usbDAOCHU].str,0,0);
		break;

	case RESTOREECR:
		if (U_OpenFile(ProgLineMes+1,FA_READ))
		{//���ļ�����ʱ,��Ϊû�д��ļ�,�����е�����ļ������ݵĴ���
			//ApplVar.ErrorNumber=ERROR_ID(CWXXI77);
			return FALSE;
		}
		ProgLineMes[0]='<';
		DispStrXY(Msg[usbDAORU].str,0,0);
		break;
	}

    PrintStr_Center((char*)Msg[fileID+usbBULEI].str,1);
	DispCharXY('-',4,1);	DispStrXY(Msg[fileID+usbBULEI].str,5,1);
	ClsState2();	j = 1;
	DispSt1C(ProgLineMes);
    if (CSV_FORMAT)
    {//���������
        switch (Backup_Restore){
        case BACKUPECR:
            if (EcrFileObj[fileID].CSVTitle &&
                 U_WriteFile(EcrFileObj[fileID].CSVTitle,strlen(EcrFileObj[fileID].CSVTitle))==-1)//д��һ��(������
            {
                U_CloseFile();
                ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
                return false;
            }
            break;
        case RESTOREECR:
            if ((i=U_ReadFile(sRcrBuffer,sRecSize))<=0)//�޳���һ��
            {
                if (i==0)
                {
                    U_CloseFile();
                    return true;
                }
                else
                {
                    ApplVar.ErrorNumber=ERROR_ID(CWXXI78);
                    return false;
                }
            }
            break;
        }
    }



	if (sRecIndex==0)
	{//���ļ�û�л��ּ�¼,��:ʱ��,ƱͷƱβ��
		switch (Backup_Restore){
		case BACKUPECR:
            if (CSV_FORMAT)
            {
                if ((*BackupToCSV)()==-1)
                {
                    U_CloseFile();
                    *(BYTE*)sRecIndex = sSaveNumber & 0xff;
                    return false;
                }
            }
			else if ((i=U_WriteFile(sRcrBuffer,sRecSize))!=sRecSize)// || i!=sizeof(ApplVar.Dept))
			{
				U_CloseFile();

				ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
				return false;
			}
			break;
		case RESTOREECR:
            if (CSV_FORMAT)
            {
                i = (*RestoreFromCSV)();
            }
			else if ((i=U_ReadFile(sRcrBuffer,sRecSize))==-1)
			{
                ApplVar.ErrorNumber=ERROR_ID(CWXXI78);
			}
			break;
		}
		U_CloseFile();
		return true;
	}

	if (fileID==usbSHUILV-usbBULEI ||
        fileID==usbZHEKOU-usbBULEI ||
        fileID==usbCHJRJIN-usbBULEI ||
        fileID==usbCANYINGN-usbBULEI)
	{//  ������NumberΪ�ֽ�BYTE���� //
		sRacMax &= 0xff;
		switch (Backup_Restore){
		case BACKUPECR:
		    for (*(BYTE*)sRecIndex = 0; *(BYTE*)sRecIndex < sRacMax; (*(BYTE*)sRecIndex)++)
		   	{
				DisplayDecXY(j,SCREENWD-6,SCREENLN,5);j++;
		   		(*ReadFromFile)();
                if (CSV_FORMAT)
                {
                    if ((*BackupToCSV)()==-1)
                    {
                        U_CloseFile();
                        *(BYTE*)sRecIndex = sSaveNumber & 0xff;
                        return false;
                    }
                }
				else if ((i=U_WriteFile(sRcrBuffer,sRecSize))!=sRecSize)// || i!=sizeof(ApplVar.Dept))
				{
					U_CloseFile();
					ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
					*(BYTE*)sRecIndex = sSaveNumber & 0xff;
					return FALSE;
				}
		   	}
			break;

		case RESTOREECR:
		    for (*(BYTE*)sRecIndex = 0; *(BYTE*)sRecIndex < sRacMax; (*(BYTE*)sRecIndex)++)
		   	{
				DisplayDecXY(j,SCREENWD-6,SCREENLN,5);j++;

                if (CSV_FORMAT)
                {
                    i = (*RestoreFromCSV)();
                }
				else if ((i=U_ReadFile(sRcrBuffer,sRecSize))==-1)
				{
                    ApplVar.ErrorNumber=ERROR_ID(CWXXI78);
				}
				if (i<=0)
					break;
		   		(*WriteToFile)();
		   	}
			break;
		}
		U_CloseFile();
		*(BYTE*)sRecIndex = sSaveNumber & 0xff;
		return true;
	}
    else
    {//  ������NumberΪ��WORD���� //
        switch (Backup_Restore){
        case BACKUPECR:
            for (*sRecIndex = 0; *sRecIndex < sRacMax; (*sRecIndex)++)
            {
                DisplayDecXY(j,SCREENWD-6,SCREENLN,5);j++;

                (*ReadFromFile)();
                if (CSV_FORMAT)
                {
                    if ((*BackupToCSV)()==-1)
                    {
                        U_CloseFile();
                        *sRecIndex = sSaveNumber;
                        return false;
                    }
                }
                else if ((i=U_WriteFile(sRcrBuffer,sRecSize))!=sRecSize)// || i!=sizeof(ApplVar.Dept))
                {
                    U_CloseFile();
                    ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
                    *sRecIndex = sSaveNumber;
                    return false;
                }
            }
            break;

        case RESTOREECR:
            for (*sRecIndex = 0; *sRecIndex < sRacMax; (*sRecIndex)++)
            {
                DisplayDecXY(j,SCREENWD-6,SCREENLN,5);j++;
                if (CSV_FORMAT)
                {
                    i = (*RestoreFromCSV)();
                }
                else if ((i=U_ReadFile(sRcrBuffer,sRecSize))==-1)
                {
                    ApplVar.ErrorNumber=ERROR_ID(CWXXI78);
                }

                if (i<=0)
                    break;
                if (fileID==usbDANPIN-usbBULEI && ApplVar.AP.Plu.RandomSize)
                {
                    for (i=0;i<ApplVar.AP.Plu.RandomSize;i++)
                        if (ApplVar.Plu.Random[i]!=0)
                            break;
                    if (i<ApplVar.AP.Plu.RandomSize)
                        ApplVar.AP.Plu.RNumber = (*sRecIndex)+1;
                    else
                        break;
                }
                (*WriteToFile)();
            }
            break;
        }
        U_CloseFile();
        *sRecIndex = sSaveNumber;
        return true;
    }
}
/************************************************************
  ��data�������ͽ���ת��Ϊsring,����CCDBufer�в���0Ϊ������־
  lenΪdata���ֽ���,
  flag=0:Ϊת����һ������;
      =0xff:Ϊת�����һ������
      ����ֵΪת���м�����
  dTypeΪ��������(BYTETYPE~OPTTYPE),BIT7=1ʱ,׷��'%'
����:����ת����������ܳ���
�˺�����ʹ��CCDBuff��Ϊ�������ɴ洢��,ʹ��ProgLineMes��Ϊ��ʱ������
************************************************************/
int FormatToCSV(void *data,BYTE dType,int len,BYTE flag)
{
    static int length;
    char    *strType;
    ULONG   ulongType;
    BYTE    byteType;
    BCD     bcdType;
    int     i,j,k;

    if (flag==0)
        length = 0;
    else if (dType!=ADD0D0A)//ccr2016-09-06
        CCDBuff[length++]=',';//���ӷָ�����

    switch(dType & 0x7f)
    {
    case  BYTETYPE:// 1       //�ֽ�����
        ulongType = *(BYTE*)data;
        length += sprintf(CCDBuff+length,"%4u",ulongType);
        break;
    case  WORDTYPE:// 2       //������
        ulongType = *(WORD*)data;
        length += sprintf(CCDBuff+length,"%6u",ulongType);
        break;
    case  LONGTYPE:// 3       //˫������
        ulongType = *(ULONG*)data;
        length += sprintf(CCDBuff+length,"%8u",ulongType);
        break;
    case  CHARTYPE:// 4       //�ַ�����
        CCDBuff[length++]=*(BYTE*)data;
        break;
    case  STRTYPE :// 5       //�ַ�������
        strType = (char*)data;
        i = strlen(strType);
        if (i>len) i = len;
        memcpy(CCDBuff+length,strType,i);
        length+=i;
        break;
    case  QTYTYPE :// 6       //BCD��������,�̶���λС��
        bcdType = *(BCD*)data;
        //bcdType.Sign &= 0xfc;  bcdType.Sign |= 0x03;
        memset(ProgLineMes,' ',BCDLEN * 2);
        i = FormatBCD(ProgLineMes+BCDLEN * 2, &bcdType,(BCDLEN * 2) + 0x6400);
        memcpy(CCDBuff+length,ProgLineMes+BCDLEN * 2 + 1 - i,i);
        length+=i;
        break;
    case  AMTTYPE :// 7       //BCD�������,�̶���λС��
        bcdType = *(BCD*)data;
        SETDECIMAL(bcdType.Sign, 0x02);
        memset(ProgLineMes,' ',BCDLEN * 2);
        i = FormatBCD(ProgLineMes+BCDLEN * 2, &bcdType,(BCDLEN * 2) + 0x6400);
        memcpy(CCDBuff+length,ProgLineMes+BCDLEN * 2 + 1 - i,i);
        length+=i;
        break;
    case  HQTYTYPE:// 8       //Hex.BCD��������,�̶���λС��,����BCD��Sign
        bcdType = ZERO;
        memcpy(bcdType.Value,data,len);
        SETDECIMAL(bcdType.Sign, 0x03);
        memset(ProgLineMes,' ',BCDLEN * 2);
        i = FormatBCD(ProgLineMes+BCDLEN * 2, &bcdType,(BCDLEN * 2) + 0x6400);
        memcpy(CCDBuff+length,ProgLineMes+BCDLEN * 2 + 1 - i,i);
        length+=i;
        break;
    case  HAMTTYPE:// 9       //Hex.BCD�������,�̶���λС��,����BCD��Sign
        bcdType = ZERO;
        memcpy(bcdType.Value,data,len);
        SETDECIMAL(bcdType.Sign, 0x02);
        memset(ProgLineMes,' ',BCDLEN * 2);
        i = FormatBCD(ProgLineMes+BCDLEN * 2, &bcdType,(BCDLEN * 2) + 0x6400);
        memcpy(CCDBuff+length,ProgLineMes+BCDLEN * 2 + 1 - i,i);
        length+=i;
        break;
    case  HEXTYPE :// 10       //HEX����,����ָ��������ת��ΪHEX,�����λ0
        bcdType = ZERO;
        memcpy(bcdType.Value,data,len);
        memset(ProgLineMes,' ',BCDLEN * 2);
        i = FormatBCD(ProgLineMes+BCDLEN * 2, &bcdType,(BCDLEN * 2) + 0x6400);
        memcpy(CCDBuff+length,ProgLineMes+BCDLEN * 2 + 1 - i,i);
        length+=i;
        break;
    case  OPTTYPE :// 11       //ѡ������(�����ݰ�λ�任 Ϊ245,��ʾBit1,Bit3,Bit4Ϊ1
        byteType = *(BYTE*)data;
        memset(ProgLineMes,' ',NUMWIDTH);
        ProgLineMes[7]='-';
        j=7;
        for (i=0;i<8;i++)
        {
            if (byteType & 1)
                ProgLineMes[j--]=i+'1';
            byteType >>= 1;
        }
        memcpy(CCDBuff+length,ProgLineMes,8);
        length+=8;
        break;
    case ADD0D0A://ccr2016-09-06
        CCDBuff[length++]=CRET;
        CCDBuff[length++]=LF;
        break;
    default:
        length = 0;
        break;
    }
    if (TESTBIT(dType,BIT7))
        CCDBuff[length++] ='%';

    if (flag==0xff)
    {//���ӻ��б�־
        CCDBuff[length++]=CRET;
        CCDBuff[length++]=LF;
    }
    return length;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/// ����Ϊ��CSV��ʽ������ˮ���ݹ��ܺ�����
/////////////////////////////////////////////////////////////////////////////////////

void CSV_NULL(void);                              //reserved
void CSV_Dept(void);
void CSV_Plu(void);
void CSV_End(void);
void CSV_TAX(void);
void CSV_NonAdd(void);
void CSV_PoRa(void);
void CSV_Operator(void);
void CSV_Tender(void);
void CSV_ModeLock(void);
void CSV_PercentDisc(void);
void CSV_SubTotalDisc(void);
void CSV_DirectDisc(void);
void CSV_SubTotalDirDisc(void);
void CSV_New(void);
void CSV_SubTotals(void);
void CSV_Message(void);
void CSV_RPEnd(void);
void CSV_InsertIC(void);
void CSV_RefreshIC(void);
void CSV_SetPrice(void);
void CSV_EcrNum(void);          //only send to manage systyem
void CSV_Void(void);            //record the operation of close table
void CSV_PbClose(void);         //record the operation of close table
void CSV_PbOpen(void);          //record the operation of close table
void CSV_PbTransTo(void);           //record the operation of close table

void ClearLogFor(ULONG sSize);
void Clear_FlowBuff(void);

CONST struct ECRLOGDES CSV_LogSize[LOGTYPEMAX]={
    {1,                              &CSV_NULL},                              //reserved
    {sizeof(struct CDC_DPT),         &CSV_Dept},
    {sizeof(struct CDC_ART),         &CSV_Plu},
    {sizeof(struct CDC_END),         &CSV_End},
    {sizeof(struct CDC_NOADD),       &CSV_NonAdd},
    {sizeof(struct CDC_OPER),        &CSV_Operator},
    {sizeof(struct CDC_GIVEN),       &CSV_Tender},
    {sizeof(struct CDC_LOCK),        &CSV_ModeLock},
    {sizeof(struct CDC_DISCADD),     &CSV_PercentDisc},
    {sizeof(struct CDC_SUBDISCADD),  &CSV_SubTotalDisc},
    {sizeof(struct CDC_DIRECT),      &CSV_DirectDisc},
    {sizeof(struct CDC_SUBDIRECT),   &CSV_SubTotalDirDisc},
    {sizeof(struct CDC_REGIS),       &CSV_New},
    {sizeof(struct CDC_SUBTOTAL),    &CSV_SubTotals},
    {sizeof(struct CDC_MESSAGE),     &CSV_Message},
    {sizeof(struct CDC_SLIPEnd),     &CSV_RPEnd},
    {sizeof(struct CDC_EnterIC),     &CSV_InsertIC},
    {sizeof(struct CDC_REFRESHIC),   &CSV_RefreshIC},
    {sizeof(struct CDC_PRICELIST),   &CSV_SetPrice},
	{sizeof(struct CDC_ECRNUM),		 &CSV_EcrNum},			//only send to manage systyem

	{sizeof(struct CDC_VOID),	 	 &CSV_Void},			//record the operation of close table
	{sizeof(struct CDC_PBCLOSE),	 &CSV_PbClose},			//record the operation of close table
	{sizeof(struct CDC_PBOPEN),	 	 &CSV_PbOpen},			//record the operation of close table
	{sizeof(struct CDC_PBTT),	 	 &CSV_PbTransTo},			//record the operation of close table
	{sizeof(struct CDC_PORA),	 	 &CSV_PoRa},			//record the operation of close table
    {sizeof(struct CDC_NETID),	 	 &CSV_NULL},			//record the NetID
    {sizeof(struct CDC_TAX),	 	 &CSV_TAX},			//record the TAX
};

/////////////////////////////////////////////////////////////
///������ˮ�����ļ�
BYTE CreateFlowFile()
{
    int i,j;

    if (!SelectCSV_BIN()) return false;

	U_ResetFolder();
	Backup_Restore= BACKUPECR;

    ProgLineMes[0]='>';
    strcpy(ProgLineMes+1,BILLREC);
//    WORDtoASCZero(ProgLineMes+20, ApplVar.AP.Flag[15]);// EcrID

    i = strlen(ProgLineMes);

//    ProgLineMes[i++]=ProgLineMes[18];//�տ�����
//    ProgLineMes[i++]=ProgLineMes[19];//�տ�����
//    ProgLineMes[i++]=ProgLineMes[20];//�տ�����

    j=i;
    if (CSV_FORMAT)
    {
        ProgLineMes[i++]='.';	ProgLineMes[i++]='C';	ProgLineMes[i++]='S';	ProgLineMes[i++]='V';
    }
    else
    {
        ProgLineMes[i++]='.';	ProgLineMes[i++]='L';	ProgLineMes[i++]='O';	ProgLineMes[i++]='G';
    }
    ProgLineMes[i]=0;
    if (U_OpenFile(ProgLineMes+1,(FA_OPEN_ALWAYS|FA_WRITE)))
    {
        ApplVar.ErrorNumber = ERROR_ID(CWXXI80);
		return false;
    }
    else if(U_FileSize() && U_LocateFile(0xffffffff))
    {//��λ���ļ�ĩβ
		U_CloseFile();
		ApplVar.ErrorNumber=ERROR_ID(CWXXI76);
		return false;
    }
    ProgLineMes[j]=0;//ProgLineMes������������ʾ
    return true;
}
/////////////////////////////////////////////////////////////////////
///usbFLOWNEW    1-����������
/////////////////////////////////////////////////////////////////////
void usbExportNew()
{
    int i,j;
    BYTE cpClerk,cpSaler;

    xCHECKUSBDISK();

    if (!CreateFlowFile()) return;

    ClsState2();	DispSt1C(ProgLineMes);

	if (CSV_FORMAT)
	{
#if !defined(SAME_RECEIPT)
		if (!U_FileSize() && U_WriteFile((char*)cCSVFLOETITL,strlen(cCSVFLOETITL))==-1)
		{//Ϊ���ļ�ʱ,д�����
			ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
			U_CloseFile();
			return;
		}
#endif
		CSV_ReceipLog(true);//��ʼ��
	}

    j = 1;
    cpClerk = ApplVar.ClerkNumber;
    cpSaler = ApplVar.SalPerNumber;

    //ccr2015-05-05>>>>>>>>>>>>>>>>>>>
    i = 0;
    if (!CSV_FORMAT)
    {
        ApplVar.FlowBuff.CDC_EcrNum.FunN = ECRNOLOG;
        ApplVar.FlowBuff.CDC_EcrNum.EcrNumber = (WORD)LOCATION * 256 + REGISTER;
        i = U_WriteFile((char*)&ApplVar.FlowBuff,sizeof(ApplVar.FlowBuff.CDC_EcrNum));
    }
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if (i>=0)
    {
        while ((i = Read_Flow((char*)&ApplVar.FlowBuff))>0)
        {
            DisplayDecXY(j,SCREENWD-6,SCREENLN,5);j++;
            if (CSV_FORMAT)
            {
                if (!CSV_ReceipLog(0))
                {
                    SUB_SCANFP(i);
                    break;
                }
            }
            else if (U_WriteFile((char*)&ApplVar.FlowBuff,i)==-1)// || i!=sizeof(ApplVar.Dept))
            {
                SUB_SCANFP(i);
                ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
                break;
            }
        }
    }

    if (CSV_FORMAT)
    {
        ApplVar.ClerkNumber = cpClerk;
        ReadClerk();
#if (salNumber)
        ApplVar.SalPerNumber = cpSaler;
        ReadSalPer();
#endif
    }
    U_CloseFile();
}
////////////////////////////////////////////////////////////////
///������ˮ�����ļ����ܺ�����
////////////////////////////////////////////////////////////////
void usbExportALL()          //usbFLOWALL    2-����ȫ������
{
    int i,j;
    BYTE cpClerk,cpSaler;

    xCHECKUSBDISK();

    if (!CreateFlowFile()) return;

    ClsState2();	DispSt1C(ProgLineMes);

	if (CSV_FORMAT)
	{
#if !defined(SAME_RECEIPT)
		if (!U_FileSize() && U_WriteFile((char*)cCSVFLOETITL,strlen(cCSVFLOETITL))==-1)
		{//Ϊ���ļ�ʱ,д�����
			ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
			U_CloseFile();
			return;
		}
#endif
		CSV_ReceipLog(true);//��ʼ��
	}

    ApplVar.FlowHeader.ReadP = ApplVar.FlowHeader.HeadP;
    j = 1;

    cpClerk = ApplVar.ClerkNumber;
    cpSaler = ApplVar.SalPerNumber;

    //ccr2015-05-05>>>>>>>>>>>>>>>>
    i = 0;
    if (!CSV_FORMAT)
    {
        ApplVar.FlowBuff.CDC_EcrNum.FunN = ECRNOLOG;
        ApplVar.FlowBuff.CDC_EcrNum.EcrNumber = (WORD)LOCATION * 256 + REGISTER;
        i = U_WriteFile((char*)&ApplVar.FlowBuff,sizeof(ApplVar.FlowBuff.CDC_EcrNum));
    }
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if (i>=0)
    {
        while ((i = Read_Flow((char*)&ApplVar.FlowBuff))>0)
        {
            DisplayDecXY(j,SCREENWD-6,SCREENLN,5);j++;
            if (CSV_FORMAT)
            {
                if (!CSV_ReceipLog(0))
                {
                    SUB_SCANFP(i);
                    break;
                }
            }
            else if (U_WriteFile((char*)&ApplVar.FlowBuff,i)==-1)// || i!=sizeof(ApplVar.Dept))
            {
                SUB_SCANFP(i);
                ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
                break;
            }
        }
    }
    U_CloseFile();
    if (CSV_FORMAT)
    {
        ApplVar.ClerkNumber = cpClerk;
        ReadClerk();
#if (salNumber)
        ApplVar.SalPerNumber = cpSaler;
        ReadSalPer();
#endif
    }

}
////////////////////////////////////////////////////////////////
void usbExportDel()  //usbFLOWALLDEL 3-����ȫ�����ݺ������ˮ����
{
    int i,j;
    BYTE sMode;
    BYTE cpClerk,cpSaler;

    xCHECKUSBDISK();

    if (!CreateFlowFile()) return;

    ClsState2();	DispSt1C(ProgLineMes);

	if (CSV_FORMAT)
	{
#if !defined(SAME_RECEIPT)
		if (!U_FileSize() && U_WriteFile((char*)cCSVFLOETITL,strlen(cCSVFLOETITL))==-1)
		{//Ϊ���ļ�ʱ,д�����
			ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
			U_CloseFile();
			return;
		}
#endif
		CSV_ReceipLog(true);//��ʼ��
	}

    ApplVar.FlowHeader.ReadP = ApplVar.FlowHeader.HeadP;
    j = 1;
    cpClerk = ApplVar.ClerkNumber;
    cpSaler = ApplVar.SalPerNumber;

    //ccr2015-05-05>>>>>>>>>>>>
    i = 0;
    if (!CSV_FORMAT)
    {
        ApplVar.FlowBuff.CDC_EcrNum.FunN = ECRNOLOG;
        ApplVar.FlowBuff.CDC_EcrNum.EcrNumber = (WORD)LOCATION * 256 + REGISTER;
        i = U_WriteFile((char*)&ApplVar.FlowBuff,sizeof(ApplVar.FlowBuff.CDC_EcrNum));
    }
    //<<<<<<<<<<<<<<<<<<<<<<<<<<
    if (i>=0)
    {
        while ((i = Read_Flow((char*)&ApplVar.FlowBuff))>0)
        {
            DisplayDecXY(j,SCREENWD-6,SCREENLN,5);j++;
            if (CSV_FORMAT)
            {
                if (!CSV_ReceipLog(0))
                {
                    SUB_SCANFP(i);
                    break;
                }
            }
            else if (U_WriteFile((char*)&ApplVar.FlowBuff,i)==-1)// || i!=sizeof(ApplVar.Dept))
            {
                SUB_SCANFP(i);
                ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
                break;
            }
        }
    }
	U_CloseFile();
    if (!ApplVar.ErrorNumber)
        Init_Flow();
    if (CSV_FORMAT)
    {
        ApplVar.ClerkNumber = cpClerk;
        ReadClerk();
#if (salNumber)
        ApplVar.SalPerNumber = cpSaler;
        ReadSalPer();
#endif
    }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//��CCDBuff����������-����-�����Ϣ,ͬʱ��SysBuf �е���Ϣ���ӵ����
//typeΪ��Ŀ��������(��Ӧ�տ��������):
//��Ʒ��������(PLU1)/������������(DEPT)/����/�������(PORA)/�����޸�����(CORREC)/
//������������(PBF)/�ۿ�/�ӳ�����(DISC)/С������(CUB1)/��������(TEND)/���۽���(ENDREC)/
///////////////////////////////////////////////////////////////////////////////
BYTE CSV_FlowQtyAmt(CONSTCHAR *str,BCD *qty,BCD *amt,WORD type)
{
    int rlen,i;

	if (str)
        FormatToCSV((void*)str,STRTYPE,strlen(str),0);
    else
		FormatToCSV((void*)"-",STRTYPE,1,0);

    if (qty)
        FormatToCSV(qty,QTYTYPE,sizeof(BCD),1);
    else
        FormatToCSV((void*)SPACE,STRTYPE,1,1);

    if (amt)
        rlen = FormatToCSV(amt,AMTTYPE,sizeof(BCD),2);
    else
        rlen = FormatToCSV((void*)SPACE,STRTYPE,1,2);

#if !defined(SAME_RECEIPT)
    //�����վݺ�,�տ�Ա,ӪҵԱ,����,�տ��,����
    FormatToCSV(SysBuf,STRTYPE,strlen(SysBuf),3);

    rlen = FormatToCSV(&type,WORDTYPE,2,0xff);
#else
    rlen = FormatToCSV(0,ADD0D0A,0,3);
#endif

    if ((i=U_WriteFile(CCDBuff,rlen))==-1)
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
        return -1;
    }
    else
        return i;

}
//-----------------------------------------------------------------------------
void CSV_NULL()
{
}
//-----------------------------------------------------------------------------
void CSV_PoRa()
{
	BCD sAmt;

	ApplVar.PoRaNumber = ApplVar.FlowBuff.CDC_PoRa.PoRaN-1;
	ReadPoRa();

	ApplVar.PoRa.Name[sizeof(ApplVar.PoRa.Name)-1] = 0;

	sAmt = ZERO;

	memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_PoRa.FAmt,sizeof(ApplVar.FlowBuff.CDC_PoRa.FAmt));

	SETDECIMAL(sAmt.Sign, 2);
	CSV_FlowQtyAmt(ApplVar.PoRa.Name,0,&sAmt,PORA);
}
//-----------------------------------------------------------------------------
void CSV_Dept()
{
    BCD sQty,sAmt;
    short i;

	ApplVar.DeptNumber = ApplVar.FlowBuff.CDC_dpt.DeptN-1;
	ReadDept();

	sQty = ZERO;
	sAmt = ZERO;

	memcpy(sQty.Value,(char *)&ApplVar.FlowBuff.CDC_dpt.FQty,sizeof(ApplVar.FlowBuff.CDC_dpt.FQty));
	memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_dpt.FAmt,sizeof(ApplVar.FlowBuff.CDC_dpt.FAmt));

	SETDECIMAL(sQty.Sign, 3);
	for (i=0;i<3;i++)
	{
		if (!(sQty.Value[0] & 0x0f))
		{
			BcdDiv10(&sQty);
			sQty.Sign--;
		}
		else
			break;
	}
	SETDECIMAL(sAmt.Sign, 2);

	if (ApplVar.FlowBuff.CDC_dpt.FunN & 0x40)
	{
		sQty.Sign |= 0x80;
        sAmt.Sign |= 0x80;
        CSV_FlowQtyAmt(Msg[QUXIAO].str,0,&sAmt,CORREC);
		ApplVar.FlowBuff.CDC_dpt.FunN |= 0x80;
	}
	else if (ApplVar.FlowBuff.CDC_art.FunN & 0x80)
    {
        sQty.Sign |= 0x80;
        sAmt.Sign |= 0x80;
        CSV_FlowQtyAmt(Msg[TUIHUO].str,0,&sAmt,CORREC);
    }

	CSV_FlowQtyAmt(ApplVar.Dept.Name,&sQty,&sAmt,DEPT);
}
//-----------------------------------------------------------------------------
void CSV_Plu()
{
    BCD sQty,sAmt;
    short i;

	if (ApplVar.AP.Plu.RandomSize)
	{
		ApplVar.PluNumber = GetPluNumber(1, ApplVar.FlowBuff.CDC_art.ArtN);
		if (ApplVar.PluNumber)
			ApplVar.PluNumber--;
	}
	else
	{
		ApplVar.PluNumber = Bcd2Long((char *)&ApplVar.FlowBuff.CDC_art.ArtN,sizeof(ApplVar.FlowBuff.CDC_art.ArtN));
	}

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
		}
		else
			break;
	}
	SETDECIMAL(sAmt.Sign, 2);

	if (ApplVar.FlowBuff.CDC_art.FunN & 0x40)
	{
        sQty.Sign |= 0x80;
        sAmt.Sign |= 0x80;
        CSV_FlowQtyAmt(Msg[QUXIAO].str,0,&sAmt,CORREC);
		ApplVar.FlowBuff.CDC_art.FunN |= 0x80;
	}
	else if (ApplVar.FlowBuff.CDC_art.FunN & 0x80)
    {
        sQty.Sign |= 0x80;
        sAmt.Sign |= 0x80;
        CSV_FlowQtyAmt(Msg[TUIHUO].str,0,&sAmt,CORREC);
    }
	CSV_FlowQtyAmt(ApplVar.Plu.Name,&sQty,&sAmt,PLU1);

}
//-----------------------------------------------------------------------------
void CSV_TAX()
{
    BCD sTax,sAmt,sRate;
    short i,rlen;
    WORD sWord;

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


    if (TESTBIT(ApplVar.Tax.Options, BIT4))	   /* print taxable? */
    {
        strcpy(ProgLineMes,ApplVar.Tax.Name);
        strcpy(ProgLineMes+strlen(ProgLineMes),Msg[XSHOUE].str);
        CSV_FlowQtyAmt(ProgLineMes,0,&sAmt,TAX);/* ��ӡ˰�ֵ����۾��� */
    }

    FormatToCSV((void*)ApplVar.Tax.Name,STRTYPE,strlen(ApplVar.Tax.Name),0);
    FormatToCSV(&sRate,(AMTTYPE | BIT7),sizeof(BCD),1);
    rlen = FormatToCSV(&sTax,(AMTTYPE),sizeof(BCD),2);

#if !defined(SAME_RECEIPT)
    //�����վݺ�,�տ�Ա,ӪҵԱ,����,�տ��,����
    FormatToCSV(SysBuf,STRTYPE,strlen(SysBuf),3);

    sWord = TAX;
    rlen = FormatToCSV(&sWord,(WORDTYPE),sizeof(WORD),0xff);
#else
    rlen = FormatToCSV(0,ADD0D0A,0,3);
#endif

    if ((i=U_WriteFile(CCDBuff,rlen))==-1)
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
        return;
    }
    else
        return;


    memset(ProgLineMes, ' ', sizeof(ProgLineMes));
    CopyFrStr(ProgLineMes,ApplVar.Tax.Name);
    FormatQty(ProgLineMes+16,&sRate);//cr070424
    ProgLineMes[17] = '%';      //ProgLineMes[13] = '%';
    ProgLineMes[18] = 0;        //ccr090113
    PrintAmt(ProgLineMes,&sTax);/* ��ӡ��˰��� */
}
//-----------------------------------------------------------------------------
void CSV_End()
{
	BCD sAmt;

	sAmt = ZERO;
	memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_end.FAmt,sizeof(ApplVar.FlowBuff.CDC_end.FAmt));
	CSV_FlowQtyAmt(Msg[YINGFU].str,0,&sAmt,ENDREC);
}
//-----------------------------------------------------------------------------
void CSV_NonAdd()
{
}
//-----------------------------------------------------------------------------
void CSV_Operator()
{
/*
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
*/
}
//-----------------------------------------------------------------------------
void CSV_Tender()
{
	BCD sAmt;
	short j;

	j = ApplVar.TendNumber;
	for (j=0;j<ApplVar.FlowBuff.CDC_given.Counter;j++)
	{
		ApplVar.TendNumber = ApplVar.FlowBuff.CDC_given.GivenData[j].FTType-1;
		ReadTender();
		ApplVar.Tend.Name[sizeof(ApplVar.Tend.Name)-1] = 0;
		sAmt = ZERO;
		memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_given.GivenData[j].FAmt,sizeof(ApplVar.FlowBuff.CDC_given.GivenData[j].FAmt));
		CSV_FlowQtyAmt(ApplVar.Tend.Name,0,&sAmt,TEND);
	}
#if defined(SAME_RECEIPT)
    CSV_FlowQtyAmt(0,0,0,0);
#endif
	ApplVar.TendNumber = j;
}
//-----------------------------------------------------------------------------
void CSV_ModeLock()
{
}
//-----------------------------------------------------------------------------
void CSV_PercentDisc()
{
	BCD sQty,sAmt;
	int i,rlen;
	WORD sWord;

	sQty = sAmt = ZERO;
	memcpy(sQty.Value,(char *)&ApplVar.FlowBuff.CDC_discadd.Percent,sizeof(ApplVar.FlowBuff.CDC_discadd.Percent));
	memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_discadd.FAmt,sizeof(ApplVar.FlowBuff.CDC_discadd.FAmt));

	if (ApplVar.FlowBuff.CDC_discadd.FunN & 0x80)
	{
		sQty.Sign |= 0x80;
		sAmt.Sign |= 0x80;
		i = 1;//�ۿ�
	}
	else
	{
		i = 0;//�ӳ�
	}
    FormatToCSV((void*)Def.Disc[i].Name,STRTYPE,strlen(Def.Disc[i].Name),0);
    FormatToCSV(&sQty,(AMTTYPE | BIT7),sizeof(BCD),1);
    rlen = FormatToCSV(&sAmt,(AMTTYPE),sizeof(BCD),2);

#if !defined(SAME_RECEIPT)
    //�����վݺ�,�տ�Ա,ӪҵԱ,����,�տ��,����
    FormatToCSV(SysBuf,STRTYPE,strlen(SysBuf),3);

    sWord = DISC;
    rlen = FormatToCSV(&sWord,(WORDTYPE),sizeof(WORD),0xff);
#else
    rlen = FormatToCSV(0,ADD0D0A,0,3);
#endif
    if ((i=U_WriteFile(CCDBuff,rlen))==-1)
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
        return;
    }
    else
        return;

}
//-----------------------------------------------------------------------------
void CSV_SubTotalDisc()
{
    int i,rlen;
	BCD sQty,sAmt;
    WORD sWord;


	sQty = sAmt = ZERO;
	memcpy(sQty.Value,(char *)&ApplVar.FlowBuff.CDC_subdiscadd.Percent,sizeof(ApplVar.FlowBuff.CDC_subdiscadd.Percent));
	memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_subdiscadd.FAmt,sizeof(ApplVar.FlowBuff.CDC_subdiscadd.FAmt));

	if (ApplVar.FlowBuff.CDC_subdiscadd.FunN & 0x80)
	{

		sQty.Sign |= 0x80;
		sAmt.Sign |= 0x80;
        i = 5;//С���ۿ�
	}
	else
	{
        i = 4;//С�Ƽӳ�
	}

    FormatToCSV((void*)Def.Disc[i].Name,STRTYPE,strlen(Def.Disc[i].Name),0);
    FormatToCSV(&sQty,(AMTTYPE | BIT7),sizeof(BCD),1);
    rlen = FormatToCSV(&sAmt,(AMTTYPE),sizeof(BCD),2);
#if !defined(SAME_RECEIPT)
    //�����վݺ�,�տ�Ա,ӪҵԱ,����,�տ��,����
    FormatToCSV(SysBuf,STRTYPE,strlen(SysBuf),3);
    sWord = DISC;
    rlen = FormatToCSV(&sWord,(WORDTYPE),sizeof(WORD),0xff);
#else
    rlen = FormatToCSV(0,ADD0D0A,0,3);
#endif
    if ((i=U_WriteFile(CCDBuff,rlen))==-1)
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
        return ;
    }
    else
        return ;
}
//-----------------------------------------------------------------------------
void CSV_DirectDisc()
{
	BCD sAmt;
    int i,rlen;

	sAmt = ZERO;
	memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_direct.FAmt,sizeof(ApplVar.FlowBuff.CDC_direct.FAmt));

	if (ApplVar.FlowBuff.CDC_subdiscadd.FunN & 0x80)
	{
		sAmt.Sign |= 0x80;
        i=3;// "����ۿ�"
	}
	else
	{
        i=2;//"���ӳ�"
	}
	CSV_FlowQtyAmt(Def.Disc[i].Name,0,&sAmt,DISC);

}
//-----------------------------------------------------------------------------
void CSV_SubTotalDirDisc()
{
	BCD sAmt;
    int i,rlen;

	sAmt = ZERO;
	memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_subdirect.FAmt,sizeof(ApplVar.FlowBuff.CDC_subdirect.FAmt));

	if (ApplVar.FlowBuff.CDC_subdiscadd.FunN & 0x80)
	{
		sAmt.Sign |= 0x80;
        i=7;// "С�ƽ��-"
	}
	else
	{
		i=6;// "С�ƽ��+"
	}

	CSV_FlowQtyAmt(Def.Disc[i].Name,0,&sAmt,DISC);
}
//-----------------------------------------------------------------------------
//���տ�Ա,ӪҵԱ,����,�տ��,�������ݴ���SysBuf��,�����ɴ������ʹ��
void CSV_New()
{
	short i;

//	PrintLine('*');
	memset(SysBuf,0,sizeof(SysBuf));
    i = 0;
    SysBuf[i++] = '#';
    HEXtoASC(SysBuf+i,ApplVar.FlowBuff.CDC_regis.ReceiptNum,RECEIPTLEN);//�վݺ�
    i += (RECEIPTLEN*2);
    SysBuf[i++]=',';

	if (ApplVar.FlowBuff.CDC_regis.OperNo>0)
	{
		ApplVar.ClerkNumber = ApplVar.FlowBuff.CDC_regis.OperNo;
		ReadClerk();
		strncpy(SysBuf+i,ApplVar.Clerk.Name,sizeof(ApplVar.Clerk.Name));//�տ�Ա����
		i = strlen(SysBuf);
        SysBuf[i++]=',';
	}
#if (salNumber)
	if (ApplVar.FlowBuff.CDC_regis.SalesPer>0)
	{
		ApplVar.SalPerNumber = ApplVar.FlowBuff.CDC_regis.SalesPer;
		ReadSalPer();
		strncpy(SysBuf+i,ApplVar.SalPer.Name,sizeof(ApplVar.SalPer.Name));//ӪҵԱ����
        i = strlen(SysBuf);
        SysBuf[i++]=',';

	}
#endif
    //����

    BCDDateTimeToStr(SysBuf+i,ApplVar.FlowBuff.CDC_regis.FYear,ApplVar.FlowBuff.CDC_regis.FMonth,ApplVar.FlowBuff.CDC_regis.FDay,
                          ApplVar.FlowBuff.CDC_regis.FHour,ApplVar.FlowBuff.CDC_regis.FMinute,ApplVar.FlowBuff.CDC_regis.FSecond);

    i = strlen(SysBuf);

    SysBuf[i++]=',';
    SysBuf[i++]=' ';

    sprintf(SysBuf+i,"ECR#:%u/%u",REGISTER & 0xff,LOCATION  & 0xff);

#if defined(SAME_RECEIPT)
    //�վݺ�,�տ�Ա,ӪҵԱ,����,�տ��,����
    i = strlen(SysBuf);
    SysBuf[i++]=CRET;
    SysBuf[i++]=LF;
    if (U_WriteFile(SysBuf,i)==-1 || U_WriteFile((char*)cCSVFLOETITL,strlen(cCSVFLOETITL))==-1)
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
#endif===

}
//-----------------------------------------------------------------------------
void CSV_SubTotals()
{
	BCD sAmt;

	sAmt = ZERO;
	memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_subtotal.FAmt,sizeof(ApplVar.FlowBuff.CDC_subtotal.FAmt));
	CSV_FlowQtyAmt(Msg[XIAOJI].str,0,&sAmt,SUB);
}
//-----------------------------------------------------------------------------
//ccr2016-09-13>>>>>>>>>>>>>>>>>>>>>>>
void CSV_Message()
{
    int i,rlen;
#if defined(CASE_PERU)
    FormatToCSV((void*)cMsgCUSTOMER,STRTYPE,strlen(cMsgCUSTOMER),0);
    rlen = FormatToCSV((void*)ApplVar.FlowBuff.CDC_Message.Message,STRTYPE,strlen(ApplVar.FlowBuff.CDC_Message.Message),0xff);

    if ((i=U_WriteFile(CCDBuff,rlen))==-1)
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
        return;
    }
    else
        return;
#endif

}//ccr2016-09-13<<<<<<<<<<<<<<<<<<<
//-----------------------------------------------------------------------------
void CSV_RPEnd()
{
}
//-----------------------------------------------------------------------------
void CSV_InsertIC()
{
}
//-----------------------------------------------------------------------------
void CSV_RefreshIC()
{
}
//-----------------------------------------------------------------------------
void CSV_SetPrice()
{
}
//---------------------------------------------------------------------------

void CSV_EcrNum()
{
}
//---------------------------------------------------------------------------
void CSV_Void()
{
	BCD sAmt;

	sAmt = ZERO;
	memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_Void.FAmt,sizeof(ApplVar.FlowBuff.CDC_Void.FAmt));
	sAmt.Sign |= 0x80;
	CSV_FlowQtyAmt(Msg[QXJYIXZHI].str,0,&sAmt,CORREC);

}
//---------------------------------------------------------------------------
void CSV_PbClose()
{
	BCD sAmt;

	sAmt = ZERO;
	memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_PbClose.FAmt,sizeof(ApplVar.FlowBuff.CDC_PbClose.FAmt));

	CSV_FlowQtyAmt(Msg[KTZHJIE].str,0,&sAmt,PBF);
}
//---------------------------------------------------------------------------
void CSV_PbOpen()
{
    int i,rlen;
    WORD sWord;

    FormatToCSV((void*)Msg[ZUOHAO].str,STRTYPE,10,0);
    FormatToCSV((void*)SPACE,STRTYPE,2,1);
	sWord = ApplVar.FlowBuff.CDC_PbOpen.PBNo;
    rlen = FormatToCSV(&sWord,WORDTYPE,sizeof(WORD),2);

#if !defined(SAME_RECEIPT)
    //�����վݺ�,�տ�Ա,ӪҵԱ,����,�տ��,����
    FormatToCSV(SysBuf,STRTYPE,strlen(SysBuf),3);
    sWord = PBF;
    rlen = FormatToCSV(&sWord,(WORDTYPE),sizeof(WORD),0xff);
#else
    rlen = FormatToCSV(0,ADD0D0A,0,3);
#endif

    if ((i=U_WriteFile(CCDBuff,rlen))==-1)
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
        return;
    }
    else
        return;
}
//---------------------------------------------------------------------------
void CSV_PbTransTo()
{
    int i,rlen;
    char sTmpBuf[20];
	BCD sAmt;
	WORD sWord;

	sAmt = ZERO;
	memcpy(sAmt.Value,(char *)&ApplVar.FlowBuff.CDC_PbTt.FAmt,sizeof(ApplVar.FlowBuff.CDC_PbTt.FAmt));
    i = sprintf(sTmpBuf,"%s(%u)",Msg[ZHUANZHANG].str,
                ApplVar.FlowBuff.CDC_PbTt.PBFNo & 0xffff);
    FormatToCSV(sTmpBuf,STRTYPE,i,0);
	sWord = ApplVar.FlowBuff.CDC_PbTt.PBTNo;
    FormatToCSV(&sWord,WORDTYPE,sizeof(WORD),2);
    rlen = FormatToCSV(&sAmt,AMTTYPE,sizeof(BCD),3);

#if !defined(SAME_RECEIPT)
    //�����վݺ�,�տ�Ա,ӪҵԱ,����,�տ��,����
    FormatToCSV(SysBuf,STRTYPE,strlen(SysBuf),3);
    sWord = PBF;
    rlen = FormatToCSV(&sWord,(WORDTYPE),sizeof(WORD),0xff);
#else
    rlen = FormatToCSV(0,ADD0D0A,0,3);
#endif

    if ((i=U_WriteFile(CCDBuff,rlen))==-1)
    {
        ApplVar.ErrorNumber=ERROR_ID(CWXXI79);
        return;
    }
    else
        return;

}
////////////////////////////////////////////////////////////////////////////////
//init:1-��ʼ���ڲ�����
////////////////////////////////////////////////////////////////////////////////
BYTE CSV_ReceipLog(BYTE init)
{
	short sFunc;
	static char	sActLog=false;
    static short sLast=0;
    int i;

    if (init)
    {
        sActLog=false;
        sLast=0;
        return true;
    }
    else
    {

        ApplVar.PrintLayOut = 0x02;

        sFunc = ApplVar.FlowBuff.CDC_dpt.FunN & 0x1f;
        //PrnBuffer(&sFunc, 1);	//hf test

        switch (sFunc) {
            case ECRNOLOG:
                CSV_EcrNum();
                break;
            case REGISLOG://��ʼһ�����վ�
                //sRecno = Bcd2Long((char *)&ApplVar.FlowBuff.CDC_regis.ReceiptNum,sizeof(ApplVar.FlowBuff.CDC_regis.ReceiptNum));
                sActLog = true;
                sLast = 0;
                CSV_New();
                break;
            case ENDLOG:
            case DEPTLOG:
            case PLULOG:
            case DISCADDLOG:
            case SUBDISCADDLOG:
            case DIRECTLOG:
            case SUBDIRECTLOG:
            case SUBTOTALLOG:
            case PBCLOSELOG:        //		22			//��̨�ݽ� //
            case TVOIDLOG:		    //      21
            case PBOPENLOG:         //		23			//��̨ //
            case TRTABLELOG:        //		24			//transfer table
            case TENDLOG:
            case TAXLOG:
                if (sActLog)
                {// ��һ����Ч���վ��ϵ����� //
                    if (sFunc==ENDLOG && sLast!=TVOIDLOG || sFunc!=ENDLOG)//Ϊȡ������ʱ,����ʾӦ������
                        (*CSV_LogSize[sFunc-1].Get1Record)();
                }
                sLast = sFunc;
                break;
        }
        if (sLast==TENDLOG)
        {
            sActLog = false;
            sLast = 0;
        }

        ApplVar.OldClerk = 0;
        return (ApplVar.ErrorNumber==0);
    }
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif

