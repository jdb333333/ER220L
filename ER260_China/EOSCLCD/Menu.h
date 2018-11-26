#ifndef MENU_H
#define MENU_H

#if CASE_USBDISK
#define MENUUSBFUNSMAX    (3+26+3) 			//ccr �˵����ܱ���Ŀ
//.......................
//#define MENUXZREPIDX 	0
#define MENUUSBMAINIDX 	0
#define MENUUSBFILEIDX 	1
#define MENUUSBFLOWIDX 	2

#define MENUUSBITEMSMAX	3			//ccr ϵͳ�п�ʼ�õĲ˵���Ŀ//
#else
#define MENUUSBFUNSMAX  0 			//ccr �˵����ܱ���Ŀ
#define MENUUSBITEMSMAX	0			//ccr ϵͳ�п�ʼ�õĲ˵���Ŀ//
#endif
//........................

#if defined(CASE_GPRS)  //ccr2014-11-11 NEWSETUP Step-7>>>>>>>>>>>
#define MENUGPRSSEND 	    MENUUSBITEMSMAX

#define MENUGPRSFUNSMAX     (MENUUSBFUNSMAX+10)//gprsMAINITEMS)			//ccr �˵����ܱ���Ŀ
#define MENUGPRSITEMSMAX	(MENUUSBITEMSMAX+1)			//ccr ϵͳ�п�ʼ�õĲ˵���Ŀ//

#else
#define MENUGPRSFUNSMAX     MENUUSBFUNSMAX 			//ccr �˵����ܱ���Ŀ
#define MENUGPRSITEMSMAX	MENUUSBITEMSMAX			//ccr ϵͳ�п�ʼ�õĲ˵���Ŀ//
#endif //ccr2014-11-11<<<<<<<<<<<<<<<<<<<<<<<<
//.................................
#define MENUFUNSMAX     (MENUGPRSFUNSMAX) 			//ccr �˵����ܱ���Ŀ
#define MENUITEMSMAX	(MENUGPRSITEMSMAX)			//ccr ϵͳ�п�ʼ�õĲ˵���Ŀ//


#if (MENUITEMSMAX)
extern CONST struct SETUPLIST MenuList[MENUITEMSMAX+1];
#endif

extern void	DisplaySetup(BYTE keyno);

extern void ExitFile_USB(void);

extern BYTE MenuMain(int pMenuIDX);

extern void usbExportMenu(void);//Ccr�����տ���ļ�//
extern void usbInportMenu(void);    //Ccr�����տ���ļ� //

extern BYTE   MenuFuncIdx;

extern void TestSendMess(void);//ͨ��GPRSģ�鷢�Ͷ���Ϣ
extern void GPRSSendECR_LOG(void);
extern void GPRSSendECR_LOG_All(void);
extern void GPRS_SetSendMode(void);

extern void ExitGPRS_SUB(void);

extern void GPRS_DownloadPLU(void)	;      //"���ص�Ʒ�ļ�"
extern void GPRS_DownloadDEPT(void)	;      //"���ز����ļ�"
extern void GPRS_DownloadCLERK(void)	;      //"�����տ�Ա"
extern void GPRS_DownloadHEAD(void)	;      //"����Ʊͷ"
extern void GPRS_DownloadPTRAIL(void);  	    //"����Ʊβ"
extern void GPRS_DownloadALL(void);  	    //"����ȫ������"
extern void GPRS_Restart(void);             //��λGPRS

//ccr2016-01-12>>>>>>>>>>>>>>>>>>>>>>>>
//�����ļ��б�˵�
typedef struct{
    WORD     SetupIDX;    //�ļ������ñ�� //
    void    (*ReadRecord)();    //��ȡ��¼���ݵĹ��ܺ��� //
	char	*Caption;			//������Ŀ����
	WORD	*RecordIdx;			//��¼���
	WORD	*RecordMax;			//��¼�����Ŀ
    WORD    MsgIDX;             //>0ʱ,ʹ��Msg[]�е���Ϣ��Ϊ�б���Ŀ,ͬʱֱ��ʹ��RecordMax��ֵ��Ϊ����¼��
    BYTE    (*PorcessRecord)(BYTE y,WORD recNo);    //��Ӧ��ǰ��¼�Ĵ�����,=nullʱ,�޴�����,��������0xffʱ,���������� //
}    TListDef;

//Ϊ��Щû��Record������ļ��б����Ӵ�����
#define SIZENAME    35//(PRTLEN+1)  //Ӧ�ô���Ʊͷ����ʾ�Ŀ��

typedef struct{
	char	Name[SIZENAME];//������������
	WORD	Number; //���ݼ�¼���
} TListRecord;

//��������
typedef struct{
    BYTE    vKey;//Ϊ����;=0xffʱ����������
    BYTE    vLen;//�����������ݳ���
	char	vInput[SIZENAME];//������������
    char    vDispRecNo;     //=1:Itemǰ����ʾ��¼��;=0:��״̬����ʾ��¼��
} TVirtualInput;
//ccr2016-01-12<<<<<<<<<<<<<<<<<<<<<<<<


extern TListRecord ListRecord;//������Name���ļ�,�����û������

extern CONST TListDef ListDef[];

extern void ListICBlock(void);
extern void ReadKP(void);
extern void ReadHeader(void);
extern void ReadTrail(void);
extern void ReadSlipHeader(void);
extern void ReadGraphic(void);
extern void ReadXZReport(void);
extern void ReadRepUnit(void);
extern void ReadZone(void);
extern void ReadKP(void);
extern void ReadPBTable(void);
extern void ReadMGList(void);
extern void ReadFlagsList(void);

extern WORD ListItems(WORD fileType,BYTE saveSCR,const char *caption,BYTE vKey);
extern WORD ReadItemCaption(WORD fileType,WORD idx,char *caption);
extern WORD GetInputByListItems(void);
extern void VirtualInputKey(BYTE key);
extern void ClearVirtualInput(void);
extern void DeleteHeader(BYTE hIdx);
extern void DeleteTrailer(BYTE hIdx);
extern void DeleteSlipHead(BYTE hIdx);
extern void VirtualInputStr(BYTE key,char *val,BYTE sLen);
extern char* GetActiveItemStr(void);
BYTE NewProgSysFlag(BYTE y,WORD recNo);
#endif
