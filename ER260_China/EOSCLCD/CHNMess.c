//---------------------------------------------------------------------------
#include "king.h"  /* Kingtron library and I/O routines */

#include "message.h"

//#include "types.h"

CONST char SPACE[2]=" ";

//---------------------------------------------------------------------------
extern CONST struct XZREPORT XZTitle[XZNUM];
//---------------------------------------------------------------------------

CONST FSTRING Msg[]={//HZMESSMAX
//captions for current mode
"WAITING....",                       //LING
CurrentMode1,                 //SHOUKUAN//"Ӫҵ",
CurrentMode2,                 //XBBIAO//"����",
CurrentMode3,                 //ZBBIAO//"����",
CurrentMode4,                 //SHEZHI//"����",
CurrentMode5,                 //JINLI//"����",
//vvvvvvvvvvvvvvvv���õ��˵���ص���Ϣ����vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
/* ���õ�һ���˵�(���˵�) */
SetupMode2,					//MENUFILES  // "���Ϲ���",
SetupMode1,					//ZHGNSZ  // "ϵͳ����",
SetupKeyboard,               //DEFKEYBOARD  //���̶���
SetupMode6,					//PJYSSZ  // "ƱͷƱβ",
msgCOMMHOST,                //COMMHOST //ͨѶ
SetupMode3,					//TXKYWS  // "����豸",
SetupMode8,					//CYGNSZ  // "��������",
SetupMode7,					//BBGNSZ  // "������",
msgDISCOUNT,                //MENUDISC //�ۿ۴���
SetupMode4, 				//JYGLSZ  // "���۹�������",
SetupMode5,					//ICKGLI  // "IC������",
#if !defined(DD_LOCK)
SetupMode9,					//QXSZHI  // "����Ա������",
#endif
SetupMode10,				//MENUSERVICE // "�տ������",

//���õ������˵�>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/* SETECRFILES�µ��ۺϹ������ò˵� */
SysSettings1, 			         //SETSYSFLAG //"ϵͳ��������",
POINTTYPE,                       //SETPOINTTYPE "����С������"
SysSettings2,            	     //SETDATE    //"����",
SysSettings3,                 	 //SETTIME    //"ʱ��",
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
msgSETEJOURNAL,                  //SETEJOURNAL //EJOURNAL
#endif

/* DEFKEYBOARD�µ��ۺϹ������ò˵� */
SysSettings4,                 	 //SETKEYB    //"����",
MESSKEYMACRO,                   //SETKEYMACRO  "���̺�"
MESSKEYTYPE,                    //SETKEYTYPE   "����ģʽ"
PRINTKEYBOARD,                  //SETPRINTKEYB "��ӡ���̲���"

SysSettings5,	                 //SETREST    //"���������л�",
SysSettings6,	                 //SETMARKET  //"���м����л�",

SetupCaption1,                 	//SETGROUP  //"����",
SetupCaption39,                 //SETSALER  //"ӪҵԱ",

/* SPGLSZ�µ���Ʒ����˵� */
SetupCaption3,                	//SETPLU    //"��Ʒ",
SetupCaption2,                 	//SETDEPT   //"����",
#if !defined(CASE_FORHANZI)
SetupCaption20,                 //SETTAX    // "˰��",
#endif
SetupCaption38,                 //SETCLERK  //"�տ�Ա",

/* COMMHOST�µ�ͨѶ������˵� */
SetupCaption5,                  //SETCOMPUTER//"�����",
SetupCaption9,			        //SETIP  // "��������",
#if defined(CASE_GPRS)
SysSettings8,					//SETGPRS //"GPRSͨ��"  /ccr2014-11-11 NEWSETUP
#endif

/* TXKYWS�µ�ͨѶ������˵� */
SetupCaption6,                  //SETBARCODE//"����ǹ",
SetupCaption7,                  //SETBALANCE//"���ӳ�",
//ccr2016-01-22SetupCaption8,                  //SETPORT4//"ͨѶ�� 4",
SetupCaption10,                 //SETSP// "Ʊ�ݴ�ӡ",
SetupCaption11,                 //SETKP// "������ӡ",
SetupEXTPrinter,                //SETEXTPRINTER //"EXTERNAL PRINT"

SetupCaption13,                 //SETPROM   // "�н�����",

/* MENUDISC�µ����۹�������*/
SetupCaption12,                 //SETOFF    //"�Żݼ�",
SetupCaption14,                 //SETDISC   // "�ۿ�",

/* JYGLSZ�µ����۹�������*/
SetupCaption17,                 //SETTEND   // "���ʽ",
SetupCaption16,                 //SETCORR   // "��������",
SetupCaption19,                 //SETDRAWER // "Ǯ��",
SetupCaption15,                 //SETPORA   // "�������",
SetupCaption18,                 //SETCURR   // "���",

/* ICKGLI�µ�IC������*/
SetupCaption21,                 //SETVIPIC         //"IC������",
SetAddNewECRVIP,         //SETADDNEWVIP //"ADD NEW VIP"
SetPrintECRVIP,          //SETPRINTVIP //"PRINT VIP"
SetCleanALLVIP,          //SETCLEANVIP //"CLEAN VIP"

SetupCaption22,                 //SETBLOCKIC    //"IC����ʧ",
SetupCaption23,	                //SETPRINTIC    //"��ӡ����Ϣ",

/* PJYSSZ�µ�ƱͷƱβ*/
SetupCaption24,                 //SETHEAD       // "�վ�Ʊͷ",
SetupCaption25,                 //SETTRAIL      // "�վ�Ʊβ",
SetupCaption26,                 //SETSHEAD      // "Ʊ��Ʊͷ",
SetupCaption27, 		        //SETGRAP       // "ͼ��",
SetupCaption28,			        //SETPRTGRAP    //"��ӡͼ��",

/* BBGNSZ�µı�����*/
SetupCaption29,                 //SETREPORT     //"���ñ�������",
SetupCaption30,                 //SETREPTYPE    //"����Ԫ",
SetupCaption31,                 //SETZONES      //"����ʱ��",
SetupCaption32,			        //SETCLRREP    //"���屨��",
SetupCaption33,			        //SETPRTJOUR   //"��ӡ��ˮ",

/* CYGNSZ�µĲ�������*/
SetupCaption34,                 //SETPBINF  //"��̨",
SetupCaption35,                 //SETPBF    //"��������",
SetupCaption36,                 //SETMODIF  //"�˵�˵��",
#if (agreeNumber)
SetupCaption37,                 //SETAGREE  //"ǩ��",
#endif
/* QXSZHI�µ�����Ȩ������*/
#if !defined(DD_LOCK)
SetupCaption40,		            //SETSETPWD  //"���õ�����",
SetupCaption42,                 //SETXPWD    //"ֻ����������",
SetupCaption43,	                //SETZPWD    //"���ʱ�������",
#endif
SetupCaption41,		            //SETMGPWD   //"��������",

/* MENUSERVICE�µ�ϵͳ���Թ��� */
msgSETTEST,                     //SETTEST    //"ϵͳ����"
msgSETCLEARPLU,                 //SETCLEARPLU    //"�����Ʒ"
msgSETPLULIST,                  //SETPLULIST   //"��ӡ��Ʒ�嵥"
msgSETTSTVER,                  //SETTSTVER        //"��ӡ�汾"
msgSETCONFIGPLU,                //SETCONFIGPLU //"���õ�Ʒ"
msgSETCONFIGDEPT,               //SETCONFIGDEPT //"���ò���"
#if CASE_USBDISK
msgSETINSTALL,                  //SETINSTALL    //"��װ/����"
#endif
msgSETPRINTFAT,                 //SETPRINTFAT   //"��ӡ�ļ������"
msgSETPRNMENU,                  //SETPRNMENU   //��ӡ���ò˵�


/* SKJCSHI�µ�ϵͳ���Թ��� */
//SetupCaption44,	                //SETTSTVER   //"�ڴ����",
SetupCaption45,                 //SETTSTDISP  //"��ʾ����",
SetupCaption451,                 //SETTSTCUST  //"����ʾ����",
SetupCaption46,	                //SETTSTPRT   //"��ӡ�汾",
SetupCaption47,	                //SETTSTCLK   //"ʱ�Ӳ���",
SetupTestRAM,                   //SETTSTMEM	       //RAM����
SetupCaption48,	                //SETTSTBELL  //"����������",
SetupCaption49,	                //SETTSTDRAW  //"Ǯ�����",
SetupCaption50,                 //SETTSTKBD   //"���̲���",
SetupCaption51,	                //SETTSTCOMM  //"���ڲ���",
SetupCaption52,	                //SETTSTAUTO  //"�Զ�����",

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

OperationN1,			        //JLHAO//"��¼#",
OperationN2,			        //SHRDMA//"��¼?",

OperationN3,                    //ZONGJI//"�ܼ�",
OperationN4,                    //ZHHUAN//"ת��",
OperationN5,                    //XIAOJI//"С��",
OperationN6,                    //CHUJIN//"����",
OperationN7,                    //RUJIN//"���",
OperationN8,                    //BAOBIAO//"����",
OperationN9,                    //ZENJIA//"����",
OperationN10,                   //GUAQI//"����",
OperationN11,                   //QUXIAO//"ȡ��",

OperationN12,                   //MIMA//"����",
OperationN13,                   //MMQREN//"����ȷ��",
OperationN14,                   //DANJIA//"����:",
OperationN15,                   //JINEF//"���:",
OperationN16,                   //CHAOSHI//"���а�",
OperationN17,                   //CANYIN//"������",
OperationN18,                   //CEISHI//"����",
"  RAM:",                       //RAM

//captions
CaptionN1,                      //YINGFU//"Ӧ��",
CaptionN2,                      //JINGE//"����",
CaptionN3,                      //JIAGE//"�۸�",
CaptionN4,                      //JIAOYISHU//"������",
CaptionN5,                      //SHULIANG//"����",
CaptionN6,                      //JINE//"���",
CaptionN7,                      //SHOUQU//"��ȡ",
CaptionN8,                      //ZHAOLING//"����",
CaptionN9,			            //RI//"��",
CaptionN10,                     //ZHOU//"��",
CaptionN11,			            //YUE//"��",
CaptionN12,			            //NIAN//"��",
CaptionN13,                     //BIAOZHUN//"��׼",
CaptionN14,                     //SHKYUANS//"�տ�Ա",
CaptionN15,                     //SHI//"ʱ",
CaptionN16,			            //RIS//"   ��",
CaptionN17,			            //YUES//"   ��",
CaptionN18,                     //TUIHUO//"�˻�",
CaptionN19,                     //CHENBEN//"�ɱ�",
CaptionN20,                     //ZUOHAO//"����#",
CaptionN21,                     //ZHPHAO//"֧Ʊ��#",
CaptionN22,                     //XINAGSHU//"��Ŀ��",
CaptionN23,                     //HSHXSHOU//"��˰����",
CaptionN24,                     //SHUIE//"˰��",
CaptionN25,                     //YEHAO//"ҳ��",
CaptionN26,                     //HAOMA//"����:",
CaptionN27,                     //GUAZHE//"����",
CaptionN28,                     //KAITAI//"��̨",
CaptionN29,                     //QZHJSHU//"���ʼ���",
CaptionN30,                     //QINGCHU//"���",
CaptionN31,                     //SBAOBIAO//"S-����",
CaptionN32,                     //MAOLI//"ë��",
CaptionN33,                     //KCZJIA//"���ӿ��",
CaptionN331,                     //KCJIANSHAO//"���ٿ��",
CaptionN34,                     //YZHZHANG//"ԭ����:",
CaptionN35,                     //XYKHAO//"���ÿ�#",
CaptionN36,                     //XZHZHANG//"������:",
CaptionN37,                     //RENSHU//"����",
CaptionN38,                     //HUANHUO//"����",

CaptionN39,                     //ZENJIAA//"����?",
CaptionN40,                     //SHANCHU//"ɾ��?",
CaptionN41,                     //ZHKOU1//"�ۿ���1",
CaptionN42,                     //ZHKOU1//"�ۿ���2",
CaptionN43,                     //XSHOUE//"���۶�",,
CaptionN44,                     //DBYHUI//"����Ż�",
CaptionN45,                     //KCSHLIANG//"�������",
CaptionN46,                     //TJYHUI//"�ؼ��Ż�",
CaptionN47,                     //XUANXIANG//"ѡ��:",
CaptionN48,                     //GDZHKOU//"�̶�",
CaptionN49,                     //"����",
CaptionN50,                     //"��/��",

CaptionN51,                     //KTZHJIE//"��̨�ݽ�",
CaptionN55,                     //KTZJIA//"��̨����",
CaptionN53,                     //ZHANJIE//"�ݽ�",
CaptionN54,                     //QRJZHANG//"ȷ�Ͻ���",
CaptionN55,                     //DYKTAI//"��ӡ��̨",
CaptionN56,                     //DYZHDAN//"��ӡ�ʵ�",
CaptionN57,                     //QXQREN//"ȡ��ȷ��",
CaptionN58,                     //FENZHANG//"����",
CaptionN59,                     //ZHUANZHANG//"ת��",
CaptionN60,                     //GHSHKYUAN//"�����տ�Ա",
CaptionN61,                     //GKRSHU//"�˿�����",

CaptionN62,                     //ZHJSHDING//"�н��趨:",
CaptionN63,                     //JIFEN//"����",

CaptionN64,                     //GBDPJGE//"�ı䵥Ʒ�۸�",
CaptionN65,			            //CHFDYJZU//"������ӡ����"��
CaptionN66,                     //ZJKCUN//"���ӿ��",
CaptionN67,                     //JSHKCUN//"���ٿ��",
CaptionN68,                     //SHURU//"����",
CaptionN69,                     //DAIFU//"����",

CaptionE1,                      //RS232ERR//"RS232��",
CaptionE2,                      //RS232OK//"RS232��ȷ",
CaptionE3,                      //RTCERR//"RTC ��!",
CaptionE4,                      //CTCERR//"CTC ��!",
CaptionE5,                      //FPROMERR//"FPROM��!",
CaptionE6,                      //CHSHHUA//"��ʼ��...",
CaptionE7,                      //SHSHHJSHU//"��ʼ������.",
CaptionE8,                      //CHUCUO//"����-",

CaptionE9,                      //MMACUO//"����� ��",
CaptionE10,                     //BCMMA//"�����ѱ���",
CaptionE11,                     //SHKYUANF//"�տ�Ա:",
CaptionE12,                     //YYYUANF//"ӪҵԱ:",
CaptionE13,                     //SHKJHAO//"�տ����:",
CaptionE14,                     //WEIZHI//"λ��:",
CaptionE15,                     //QUERENF//"ȷ��?",
CaptionE16,                     //WANCHENG//"���",

CaptionE17,                     //FXBBEN//"���а汾:",
CaptionE18,                     //BCXFEI//"�������ѵ�",
CaptionE19,                     //ZJDPIN//"������Ʒ:",
CaptionE20,                     //SHCHDP//"ɾ����Ʒ:",
CaptionE21,                     //KSHJCE//"��ʼ���>>",
CaptionE22,                     //JCJSHU//"<<������",
CaptionE23,                     //KUCUN//"���",
CaptionE24,                     //BBQQING//"������ȫ��!",
CaptionE25,                     //GXBIOS//"���³�������ϵ�",
CaptionE26,                     //WJKJYJIE//"�ļ��ռ�Խ��",
CaptionE27,	                    //JSHDPSHL//CCr �ڴ������
CaptionE28,			            //RZQMAN//"��ˮ�洢����",
CaptionE29,			            //GHDYZHI//"�������ӡֽ",
CaptionE30,			            //KZNCCUO//"��չ�ڴ����",

CaptionE31,                     //SHUOMINF//"˵������",

CaptionE32,                     //CWXXI01//"��Ч����!",
CaptionE33,                     //CWXXI02//"��Ч����!",
CaptionE34,                     //CWXXI03//"��Чʱ��!",
CaptionE35,                     //CWXXI04//"��ֹ����!",
CaptionE36,                     //CWXXI05//"PLU����Ϊ��!",
CaptionE37,                     //CWXXI06//"PLU�ļ����!",
CaptionE38,                     //CWXXI07//"��̨��ռ��!",
CaptionE39,                     //CWXXI08//"��̨�Ѵ�!",
CaptionE40,                     //CWXXI09//"��̨�Ų���!",
CaptionE41,                     //CWXXI10//"��������̨��",
CaptionE42,                     //CWXXI11//"û�п�̨",
CaptionE43,                     //CWXXI12//"��̨�������",
CaptionE44,                     //CWXXI13//"��ֹ�޸�ʱ��",
CaptionE45,                     //CWXXI14//"����������!",
CaptionE46,                     //CWXXI15//"���ۻ�������",
CaptionE47,                     //CWXXI16//"��Ʒû���۳�",
CaptionE48,                     //CWXXI17//"���ڽ�����!",
CaptionE49,                     //CWXXI18//"�������ݳ���",
CaptionE50,                     //CWXXI19//"���ڸ���!",
CaptionE51,                     //CWXXI20//"�������!",
CaptionE52,                     //CWXXI21//"û��ȷ�Ͻ���",
CaptionE53,                     //CWXXI22//"��ֹȡ������",
CaptionE54,                     //CWXXI23//"�޲���!",
CaptionE55,                     //CWXXI24//"�޴��տ�Ա!",
CaptionE56,                     //CWXXI25//"�տ�Ա�ı�",
CaptionE57,                     //CWXXI26//"�޴��౨��!",
CaptionE58,                     //CWXXI27//"�����ӡ�ж�",
CaptionE59,                     //CWXXI28//"�����ھ���",
CaptionE60,                     //CWXXI29//"���ܷ���ʱ��",
CaptionE61,                     //CWXXI30//"�����������",
CaptionE62,                     //CWXXI31//"Կ�׵�λ��",
CaptionE63,                     //CWXXI32//"δ��Ȩ!",
CaptionE64,                     //CWXXI33//"��ָ���տ�Ա",
CaptionE65,                     //CWXXI34//"��ָ��ӪҵԱ",
CaptionE66,                     //CWXXI35//"��ֹPLU��ۣ�",
CaptionE67,                     //CWXXI36//"���벻��!",
CaptionE68,                     //CWXXI37//"������ӡ����",
CaptionE69,                     //CWXXI38//"Ʊ�ݴ�ӡ����",
CaptionE70,                     //CWXXI39//"��ӡѹ��̧��",/��ӡ��æ
CaptionE71,                     //CWXXI40//"��ӡֽ����!",
CaptionE72,                     //CWXXI41//"��ӡ�¶�̫��",
CaptionE73,                     //CWXXI42//"����δ����!",
CaptionE74,                     //CWXXI43//"����������",/* zero price not allowed enter amount */
CaptionE75,                     //CWXXI44//"��ֹ���ָ���",
CaptionE76,                     //CWXXI45//"�����޴˹���",
CaptionE77,                     //CWXXI46//"δ��С�Ƽ�!",
CaptionE78,                     //CWXXI47//"���ڹ�����",
CaptionE79,                     //CWXXI48//"������ˮ��",
CaptionE80,			            //CWXXI49//"MODEMͨѶ��!",


CaptionE81,                     //CWXXI50//"����������!"
CaptionE82,                     //CWXXI51//"POS�����!"
CaptionE83,                     //CWXXI52//"�����ݴ�!"
CaptionE84,                     //CWXXI53//"Ϊ���ڿ�!"
CaptionE85,                     //CWXXI54//"Ϊ��ʧ��!"
CaptionE86,                     //CWXXI55//"�ͻ�����!"
CaptionE87,                     //CWXXI56//"Ϊ�¿�!"
CaptionE88,                     //CWXXI57//"���ǹ��￨!"
CaptionE89,                     //CWXXI58//"д������!"
CaptionE90,                     //CWXXI59//"���Ų���!"
CaptionE91,			            //CWXXI60//"�����ۿۿ�!"
CaptionE92,			            //CWXXI61//"�����ֽ�!"
CaptionE93,			            //CWXXI62//"�������ʿ�!"
CaptionE94,			            //CWXXI63//"����IC��!"
CaptionE95,			            //CWXXI64//"�忨����!",
CaptionE96,			            //CWXXI65//"�������!",
CaptionE97,			            //CWXXI66//"IC��ֵ����!",
CaptionE98,			            //CWXXI67//"IC��ʼ������",
CaptionE99,			            //CWXXI68//"��ֹ��ʼ��!",
CaptionE100,			        //CWXXI69//"IC����!",
CaptionE101,			        //CWXXI70//"IC�������!",
CaptionE102,			        //CWXXT71//Hf "IP��ַ��"
CaptionE103,			        //CWXXI72// ccr "��IC��!",
CaptionE105,			        //CWXXI73//"�йҵ�",

CaptionERR105,     				// CWXXI74     //  20070803"��ص�����"
CaptionERR106,     				// CWXXI75     //  20070806"û������"

//ccr090715>>>>>>>>>>>>>>>>>>>>>>>>>
CaptionERR76,			     //  CWXXI76 ��U��!     //
CaptionERR77,			     //  CWXXI77 ���ļ�����     //
CaptionERR78,			     //  CWXXI78 ���ļ�����!     //
CaptionERR79,			     //  CWXXI79 д�ļ�����!     //
CaptionERR80,			     //  CWXXI80 �����ļ�����     //
CaptionERR81,			     //  CWXXI81 �ر��ļ�����     //
CaptionERR82,                //  CWXXI82 �뷢����ˮ     //

CaptionERR83,                 //CWXXI83  //GPRS����
CaptionERR84,                 //CWXXI84  //�������ݳ���
CaptionERR85,                 //CWXXI85  //�������ݴ�
CaptionERR86,                 //CWXXI86  //�޷����ӷ�����
CaptionERR87,                 //CWXXI87  //�޷�����IP��ַ
CaptionERR88,                 //CWXXI88  //��SIM��
CaptionERR89,                 //CWXXI89  //GPRSδ����
CaptionERR90,                //CWXXI90  //�ѵ������
CaptionERR91,                //CWXXI91          //�޴˻�Ա

//ccr2016-10-24 EJ >>>>>>>>>>>>>>>>>>>
EJ_CWXXI92  ,              	//CWXXI92 	"EJ DATA ERROR"
EJ_CWXXI93  ,              	//CWXXI93 	"NO SD CARD"
EJ_CWXXI94  ,              	//CWXXI94 	"EJ R/W ERROR"
EJ_CWXXI95  ,              	//CWXXI95 	"NO EJ RECORDS"
EJ_CWXXI96  ,              	//CWXXI96 	"EJ NEARLY FULL"
EJ_CWXXI97  ,              	//CWXXI97 	"EJ IS FULL"
EJ_CWXXI98  ,              	//CWXXI98 	"NEW EJ"
EJ_CWXXI99  ,              	//CWXXI99 	"RESET EJ FIRST"
EJ_CWXXI100 ,              	//CWXXI100	"EJ NOT MATCHED"

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

CaptionE104,			        //DKQXIANG//"��Ǯ��",
CaptionE106,					//YOUGUADAN "�йҵ�"    //
CaptionE107,					//SHURUQTYAMT
CaptionE108,                    //ZHUANRUDAO "ת�뵽"

"Error-",			            //ERRORMSG
"CUR",				            //CURRENCY
"TOT",				            //TOTALMSG
"CHG",				            //CHANGE
"SUB",				            //SUBTOTAL
"Dis",				            //DISCOUNT
MsgPUTOUT,   	                //PUTOUT
MsgRECIEVIN, 		            //RECIEVIN
"DRAW",  			            //OPENDRAW
"CANC",  			            //CANCEL
"MODI",				            //ADDMODI

"TABL",          		        //TABLENUM
"SER",          		        //SERVICE
"CPA",          		        //CHECKPAID
"CHK",          		        //CHECKCPAID
"COV",          		        //COVERS

"COR",    			            //CORRECT
"RET",    			            //REFUND
"CAN1",    			        //CANCEL1
"CAN2",    			        //CANCEL2

DownLoad1,			            //ZZXZZKU//"���������ֿ�",
DownLoad2,			            //ZZXZTXING//"��������ͼ��",
SpecialSymbol1,			        //DOWNLOAD//"��",
SpecialSymbol2,			        //UPLOAD//"��",

OptionN1,                       //KAI//"��",
OptionN2,                       //GUAN//"��",
OptionN3,                       //MINCHENF//"����:",
OptionN4,                       //BULEIF//"����:",
OptionN5,                       //GUIZUF//"����:",

"HOLD",                          //HOLD
OptionN6,                       //DAYINF//"��ӡ:",
OptionN7,                       //XUANXIANGF//"ѡ��:",
OptionN8,                       //LIANJIE//"����:",
OptionN9,                       //SHUILVF//"˰��:",
OptionN10,                      //WZHBHAOF//"λ�ñ��:",
OptionN11,                      //JIAGE1//"�۸� 1:",
OptionN12,                      //JIAGE2//"�۸� 2:",
OptionN13,                      //JIAGE3//"�۸� 3:",
OptionN14,                      //JIAGE4//"�۸� 4:",
OptionN15,                      //JINJIA//"����:",
OptionN16,                      //ZHKLVF//"�ۿ���(%):",
OptionN17,                      //ZDZHIF//"���ֵ:",
OptionN18,                      //FIXMSG//"�ۿ���:",
OptionN19,                      //MAXMSG//"���ֵ:",
OptionN20,                      //HUILVF//"����:",
OptionN21,                      //MRJIAF//"�����:",
OptionN22,                      //MCHJIAF//"������:",
OptionN23,                      //ZHUANGTAIF//"״̬:",
OptionN24,                      //QIANXIANGF//"Ǯ��:",
MSGOTD,                          //OTDMSG
OptionN25,                      //CHFDYINF//"������ӡ:",

MSGPERIOD,                      //PERMSG  PERIOD ����
MSGPOINTER,                     //POIMSG  POINTER ָ��
OptionN26,                      //QIANZHUIFU//"ǰ׺��",,6���ַ�
OptionN27,                      //LIANJIEF//"����:",
OptionN28,                      //GNMA//"���빦����:",
OptionN29,	                    //AGNJIAN//"�����ܼ�:",
OptionN30,                      //LEIXING//"����:",
OptionN31,                      //KSHRQIF//"��ʼ����:",
OptionN32,                      //JSHRQIF//"��������:",
OptionN33,                      //KSHSHJIANF//"��ʼʱ��:"
OptionN34,                      //JSHSHJIANF//"����ʱ��:"
OptionN35,	                    //XINGQIFF//"����:",
OptionN36,	                    //ZHEKOUF//"�ۿ�:",
OptionN37,                      //DBSHLIANGF//"�������:",
OptionN38,                      //DANJIAF//"����:",
OptionN39,                      //YHJIAF//"�Żݼ�:",
OptionN40,                      //TXXYIF//"ͨѶЭ��:",
OptionN41,                      //DHHMAF//"�绰����:",
OptionN42,	                    //MIMAF//"����:",
OptionN43,	                    //PINLV//"Ƶ��:",
OptionN44,                      //ZXJERF//"��С���:",
OptionN45,	                    //TXKHAOF//"ͨѶ��:",
OptionN46,                      //"�Ƶ���:",
OptionN47,                      //TXXHAO//"ͼ�����:",

OptionN48,                      //SHIJIANF//"ʱ��:",
OptionN49,                      //RIQIF//"����:",

OptionN50,                     //DYJXHAO//"��ӡ�ͺ�:",
OptionN51,                     //DZCHXHAO//"���ͺ�:",

#if(CASE_MACRO5150==1)
WelcomeN1,                      //"�� �� �� �� �� �� �� ��\n    ��ӭʹ���Ŵ��տ��" */
#else
WelcomeN2,                      //"���������Ŵ����\n�Ŵ�����ʯ�տ��" */
#endif

MessagesN1,			//SHKJSDING//"  �տ��������",
MessagesN2,		        //AFSHSUO//"������ʽ��������",
MessagesN3,		        //XSHFPIAO//"��ʽ��Ʊ",																							//XSHFPIAO
MessagesN4,	                //CHFDYJHAO//"������ӡ��#",																						//CHFDYJHAO
MessagesN5,                     //PXZHTAI//	"*** ��ѵ״̬ ***",
MessagesN6,                     //JIADIAN//	"***** �ӵ� *****",
MessagesN7,		        //FKFZHANG//"*** �ֿ����� ***",
MessagesN8,                     //FZHSHJU//	"*** �����վ� ***",
MessagesN9,                     //GBPLUJGE//	"*** ��Ʒ��� ***",
MessagesN10,                    //ZJIAKUCUN//	"*** ���ӿ�� ***",
MessagesN101,                   //JSHAOKUCUN//	"*** ���ٿ�� ***",
MessagesN11,                    //QUXIAOP//	"***** ȡ�� *****",
MessagesN12,                    //CHXCHSHHUA//	"** �����ʼ�� **",
MessagesN13,			//SELECT1HZ "��<ѡ��>��<ȷ��>"
MessagesN14,			//KPTOTAL ������ӡ����


TitleN1,			//TITLE
//Ʒ��   ����   ����   ���      /*123456789012345678901234567890123456*/
TitleN3,			//TITLEQTYAMT
TitleN4,			//TITLEAMT

/* ApplVar.Month Captions */
CaptionM1,			//JANUARY //"һ��",
CaptionM2,			//FEBRUARY//"����",
CaptionM3,			//MARCH   //"����",
CaptionM4,			//APRIL   //"����",
CaptionM5,			//MAY     //"����",
CaptionM6,			//JUNE    //"����",
CaptionM7,			//JULY    //"����",
CaptionM8,			//AUGUST  //"����",
CaptionM9,			//SEPTMBER//"����",
CaptionM10,			//OCTOBER //"ʮ��",
CaptionM11,			//NOVEMBER//"ʮһ��",
CaptionM12,			//DECEMBER//"ʮ����",

/* WeekDay Captios */
CaptionW1,			//MONDAY  //"����һ",
CaptionW2,			//TUESDAY //"���ڶ�",
CaptionW3,			//WEDNSDAY//"������",
CaptionW4,			//THURSDAY//"������",
CaptionW5,			//FRIDAY  //"������",
CaptionW6,			//SATURDAY//"������",
CaptionW7,			//SUNDAY  //"������",

ClueN1,			        //AQRJIAN//"��ȷ�ϼ�...",

//Option for KP
OptionS1,		        //KPDYZE//"��ӡ�ܶ�:",
OptionS2,		        //KPCXTDY//"����ͬ��ӡ",
OptionS3,		        //KPCBTDY//"�˲�ͬ��ӡ",

//Option for dept
OptionS4,		        //JZHLJGE//"��ֹ��۸�",
OptionS5,		        //DYFGXIAN//"��ӡ�ָ���",
OptionS6,		        //DXXSHOU//"��������:",
OptionS7,		        //ZHKXIANG1//"�ۿ��� 1:",
OptionS8,		        //ZHKXIANG2//"�ۿ��� 2:",

//Options for tend
OptionS9,		        //DKQXIANGF//"��Ǯ��:",
OptionS10,		        //SHRJE	//"������:",
OptionS11,		        //JZHSHRU//"��ֹ����:",
OptionS12,		        //SHRHMA//"�������:",
OptionS13,		        //ZHLXFEI//"����ΪС��",

//Options for PoRa
OptionS14,		        //DKQXIANGP//"��Ǯ��:",
OptionS15,		        //FKFSHJIAN//"���ʽ��",
OptionS16,		        //CRJE//"������:",
OptionS17,		        //RJCHJIN//"���/����",
#if defined(CASE_INDIA)
OptionS12,		        //PORANUMBER// "�������:",
#endif

//Option for ApplVar.Disc
OptionS18,		        //DYZHKE//"��ӡ�ۿ۶�",
OptionS19,		        //SHYZHK1//"ʹ���ۿ�1:",
OptionS20,		        //SHYZHK2//"ʹ���ۿ�2:",

//Options for currency
OptionS21,		        //MCHJZHLIN//"����������",

//Options for Draw
OptionS22,		        //WXSHDIAN//"��С����:",
OptionS23,		        //DKQXIANGD//"��Ǯ��:",

//Options for Tax
OptionS24,		        //YYZZHI//"Ӫҵ/��ֵ:",
OptionS25,		        //DYSHLXIANG//"��ӡ˰����",
OptionS26,		        //DYLSHXXI//"��ӡ0˰��",
OptionS27,		        //WGSTSHUI//"ΪGST��˰",
OptionS28,		        //DYSHE//"��ӡ˰��:",


//Options for clerk
OptionS29,		        //QXXZHI//"ȡ������:",
OptionS30,		        //GGXZHI//"��������:",
OptionS31,		        //QXJYIXZHI//"ȡ������:",
OptionS32,		        //THXZHI//"�˻�����:",
OptionS33,		        //BFBZHKXZHI//"%�ۿ�����:",
OptionS34,		        //BFBJCHXZHI//"%�ӳ�����:",
OptionS35,		        //JJJEXZHI//"+-�������",
OptionS36,		        //PSHMSHI//"��ѵģʽ:",
OptionS37,		        //mPRNINDEX//"ȡ�˺�:",
                        //
MESS_ECR_IP,            //ECRIPADDRESS         "IP Address:"
MESS_ECR_ID,            //"�տ��ID��:"   //ECRNETID

EditN1,                         //SHRLJHAO "<��¼��>  �¼�¼\n<ȷ��>  ��ǰ��¼",
EditN2,                         //SHRDPDMA "<����>��ɾ����Ʒ\n<ȷ��>  ��ǰ��Ʒ\n",

EditN3,                         //TCHBJI//"<�˳�>      �˳�",
EditN4,                         //BJDQJLU//"<ȷ��>      ����\n",
EditN5,                         //ANXZJIAN	//"��<ѡ��>����",
EditN6,				//XFJE//"���ѽ��",				//XFJE

EditN7,										//AJGNDYI  // "����     ->��   ",
EditN8,				//JLSHYONG//"ֻ���ھ�����",
EditN9,				//YYSHYONG//"����Ӫҵ����",
EditN10,		        //DYWZI//"��ӡ����",

EditN11,			//BAOLIU//"����",
EditN12,	                //SHGNENG//"�ļ��������",


EditN13,			//ZHZBHAO//CCr "����",
EditN14,			//MODEMLINK//CCr "MODEM ����!",
EditN15,			//DAIMA//"����:",

EditN16,			//PZHEKOU//"%�ۿ�",
EditN17,			//PJIACHEN//"%�ӳ�",
EditN18,			//SHJHAOF//"�վݺ�:",

EditN19,			//WENJSHU//	"�ļ�����"��0
EditN20,  		        //WENJKJ//	"�ļ��ռ䣺"
EditN21,		  	//TJWENJ// "ͳ���ļ�"2
EditN22,			//JISHUI// ����˰��8
EditN23,			//LIUSKJ
"RAM",                      //RAMKB
EditN24,                        //CONIFOT0    // "�ļ���      ��¼��      �ռ��С"
EditN25,                        //CONIFOT1    // "��������    ͨ�����   ͨ��Э��"

EditN26,                        //DBKHSHU//  '����������', //	DBKHSHU
EditN27,                        //MYEHSHU//  'ÿҳ����',//	MYEHSHU
EditN28,                        //DAYXXI//	'��ӡ��Ϣ',//	DAYXXI
EditN29,                        //DEZPJU			//	'�ڶ���Ʊ��', //	DEZPJU
EditN30,                        //ZUOBJU			//	'��߾�',//	ZUOBJU
EditN31,                        //PDJIXING	//	'Ʊ�����',//	PDJIXING


EditN32,		        //DYJGUAN//"��ӡ����",
EditN33,		        //DYJKAI//"��ӡ����",


//ChipCard>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
ChipCardN1,                     //ICSZMIMA//"����:",
ChipCardN2,                     //ICSZMIMAF//"����ȷ��:",
ChipCardN3,                     //POSDAIMA//"POS����:",
ChipCardN4,                     //POSDIAMAF//"����ȷ��:",
ChipCardN5,                     //BCDMA//"�����ѱ���",
ChipCardN6,                     //DMACUO//"����� ��",
ChipCardN7,                     //ICCA//"����IC��:",
ChipCardN8,                     //ZHEKOUCA//"�ۿۿ�:",
ChipCardN9,                     //XIANJINKA//"�ֽ�:",
ChipCardN10,                    //SHEZHANGKA//"���ʿ�:",
ChipCardN11,                    //DAYINICKA//"��ӡIC��",
ChipCardN12,                    //ZDZHEKOU//"�Զ��ۿ�:",
ChipCardN13,                    //XFJIFEN//"���ѻ���:",
ChipCardN14,                    //XJJIAN//"���ֽ��:",
ChipCardN15,                    // QYXYQI	"������Ч��", //
ChipCardN16,                    //GUASHIIC//"��ʧ����",      //ICCard Part ccr chipcard 2004-06-28
ChipCardN17,			//KAHAO//	"����:",
ChipCardN18,			//KLXING//	"������:",
ChipCardN19,		        //KNJE 	//hf"���"
ChipCardN20,			//KYJIN//	"��Ѻ��:",
ChipCardN21,	                //XFZE//	"����:",
ChipCardN22,			//CHZHZE//	"��ֵ�ܶ�:",
ChipCardN23,			//SHYCSHU//	"ʹ�ô���:",
ChipCardN24,			//JGLBIE//	"�۸񼶱�:",
ChipCardN25,			//PINMA//	"PIN��:",
ChipCardN26,			//BHJBIE//	"��������:",
ChipCardN27,			//ZDJZHANG//	"�Զ�����:",
ChipCardN28,			//ZHKRQI//	"�ƿ�����:",
ChipCardN29,			//KYXQI//	"����Ч��:",
ChipCardN30,			//KHMCHEN//	"�ͻ�����:",
ChipCardN31,			//CHSHHICKA//ccr	"��ʼ��IC",
ChipCardN32,			//ICKCHZHI//ccr	"IC����ֵ",
ChipCardN33,			//QCHICKA//ccr	"���IC��",
ChipCardN34,		        //CHZHTKUAN//ccr	"��ֵ/�˿�?",
ChipCardN35,		        //JDSDIAN//ccr	"�ҽ�/�ͷ�?",
ChipCardN36,			//QRCHZHI//"ȷ�ϳ�ֵ?",
ChipCardN37,			//QRTKUAN//"ȷ���˿�?",
ChipCardN38,			//QRSDIAN//"ȷ���͵�?",
ChipCardN39,			//DJQREN//"�ҽ�ȷ��?",
ChipCardN40,			//XFJDDJIANG//"���ֶҽ�",
ChipCardN41,			//ICKTKUAN//"IC���˿�",
ChipCardN42,			//ICKDJDIANG//"�ҽ�����",
ChipCardN43,			//ICKSDIAN//"���ͷ���:",
ChipCardN44,		        //QDDAI//"��ȴ�......",
ChipCardN45,		        //KNYJE//"�����н��,�����˿�....",
ChipCardN46,			//TMHYHAO//"��Ա��:",
ChipCardN47,            //BARREPORT// �� Ա �� ��
ChipCardN48,			//CHXKJI//"Ҫ�����µ�IP,�����¿���."
ChipCardN49,			//ZQBBIAO//"ȷ���屨��?",
ChipCardN50,			//WAITICARD//"�ȴ�IC��....",
ChipCardN51,                    //BGDYIN "���ߴ�ӡ",

//ccr2015-06-15>>>>>>>>>>>>>>>>>>>>>
ChipCardN52,             //CLEARIC "�忨",
ChipCardN53,             //REFUNDtoIC "�˿�",
ChipCardN54,             //PAYMENTbyIC "����",
ChipCardN55,             //CHARGEtoIC "��ֵ",
ChipCardN56,             //INITIALIC   "��ʼ��",
ChipCardN57,             //TAKECAHSfrIC "ȡ��"
ChipCardN58,            //ADDVIPPOINTS "��������"
ChipCardN59,            //DECVIPPOINTS "���ֶҽ�"
ChipCardN60,            //VIPPOINTS "�ۼƻ���"
//ccr2015-06-15<<<<<<<<<<<<<<<<<<<<<

#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
MESSEJ_X_STORE  ,       //"SAVE X DATA"//MsgEJ_X_STORE
MESSEJ_Z_STORE  ,       //"SAVE Z DATA"//MsgEJ_Z_STORE
MESSEJ_TR_STORE ,       //"SAVE TRAIN"//MsgEJ_TR_STORE
#endif

//ccr2016-02-22>>>>>>>>>>>>>>>>>>>>>
MsgMENUXREPORT    ,     //MENUXREPORT    "��ӡX����"    "X REPORT"
#if (CASE_USBDISK)
MsgMENUXEXPORT    ,     //MENUXEXPORT    "������������" "EXPORT(X)"
#endif
MsgMENUQUICKVIEW  ,     //MENUQUICKVIEW  "���ı���"     "VIEW REPORT"
MsgMENUXLOGFUNC    ,     //MENUXEJFUNC    "������ˮ��"   "VIEW LOG"
#if defined(CASE_GPRS)
MsgMENUSENDNEWLOG,      //MENUSENDNEWLOG  //��������ˮ����
#endif
MsgMENUXPASSWORD  ,     //MENUXPASSWORD  "����X����"    "X-PASSWORD"
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
MsgMENUXEJOURNAL  ,     //MENUXEJOURNAL   "E Journal"
#endif
//.......................................................

MsgMENUZREPORT    ,     //MENUZREPORT    "��ӡZ����"    "Z REPORT"
#if (CASE_USBDISK)
MsgMENUZEXPORT    ,     //MENUZEXPORT    "������������" "EXPORT(Z)"
#endif
MsgMENUCLEARLOG    ,     //MENUCLEARLOG    "�����ˮ��"   "CLEAR LOG"
MsgMENUZGRAND     ,     //MENUZGRAND     "�������ѡ��" "GRAND TOTAL"
MsgMENUZPASSWORD  ,     //MENUZPASSWORD  "����Z����"    "Z-PASSWORD"
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
MsgMENUZRESETEJ  ,     //MENUZRESETEJ   "RESET EJ"
#endif
//...................................

#if defined(DEBUGBYPC)
XZReportList1,                  //		{3, "�����ձ���"},
XZReportList2,                  //		{4, "�����±���"},
XZReportList3,                  //		{5, "��Ʒ����"},
XZReportList4,                  //		{5, "��Ʒ����"},
XZReportList5,                  //		{7, "ʱ�α���"},
XZReportList6,                  //		{1, "�տ�Ա�ձ���"},
XZReportList7,                  //		{2, "�տ�Ա�±���"},
XZReportList8,                  //		{8, "ȫ�տ�Ա�ձ���"},
XZReportList9,                  //		{9, "ȫ�տ�Ա�±���"},
#if (salNumber)
XZReportList10,                 //		{10,"ӪҵԱ�ձ���"},
XZReportList11,                 //		{11,"ӪҵԱ�±���"},
XZReportList12,                 //		{12,"ȫӪҵԱ�ձ���"},
XZReportList13,                 //		{13,"ȫӪҵԱ�±���"},
#endif
#if (BARCUSTOMER==1)
XZReportList14,                 //		{14,"��Ŀ��Ա����"},
#endif
#else
XZTitle[0].Name,	        //XZTITLE
XZTitle[1].Name,	        //XZTITLE
XZTitle[2].Name,	        //XZTITLE
XZTitle[3].Name,	        //XZTITLE
XZTitle[4].Name,	        //XZTITLE
XZTitle[5].Name,	        //XZTITLE
XZTitle[6].Name,	        //XZTITLE
XZTitle[7].Name,	        //XZTITLE
XZTitle[8].Name,	        //XZTITLE
#if (salNumber)
XZTitle[9].Name,	        //XZTITLE
XZTitle[10].Name,	        //XZTITLE
XZTitle[11].Name,	        //XZTITLE
XZTitle[12].Name,	        //XZTITLE
#endif
#if (BARCUSTOMER==1)
XZTitle[13].Name,	        //XZTITLE
#endif
#endif

#if (CASE_EPOS)
EPosN1,                         //ePOSTAC //cc epos//cc "ePOS��֤��:",
EPosN2,			        //WAITEPOS"�ȴ���ͨ��"
EPosN3,			        //ePOSCARNO//cc "��ͨ����:",
EPosN4,	                        //eCARREMAIN//cc "��ͨ�����:",
#endif

//ccr090715>>>> captions for USB Applications >>>>>>>>>>>>>>>>
#if (CASE_USBDISK)//SETUP

usbMAIN1,     // usbDAOCHU	�����տ���ļ�     //
usbMAIN2,     // usbDAORU �����տ���ļ�     //
usbMAIN3,     // usbFLOW ����������ˮ     //
// ------------

usbALLFile,     	// usbALL ȫ���ļ�     //
SetupCaption2,     //  usbBULEI     //  "����",
SetupCaption3,     //  usbDANPIN     //  "��Ʒ",
SetupCaption20,     //  usbSHUILV     //  "˰��",
SetupCaption24,     //  usbPIAOTOU     //  "Ʊͷ",
SetupCaption14,     //  usbZHEKOU     //  "�ۿ�",
#if (salNumber)
SetupCaption39,     //  usbYYYUAN     //  "ӪҵԱ",
#endif
SysSettings1,     	//  usbSTSHZHI     //  "ϵͳ����",
SetupCaption5,     //  usbTXKOU1     //  "ͨѶ��1",
SetupCaption28,     //  usbTUXIN     //  "ͼ�δ�ӡ",
SetupCaption1,     //  usbGUIZU     //  "����",
DRAWER6,     		//  usbICKA     //  "IC��",
SetupCaption13,     //  usbZHJIANG     //  "�н�����",
SetupMode8,     	//  usbCANYINGN     //  "��������",
SetupCaption38,     //  usbSHKYUAN     //  "�տ�Ա",
CaptionE31,     	//  usbSHUOMIN     //  "˵������",
SetupCaption34,     //  usbZHUOTAI     //  "��̨",
SetupCaption31,     //  usbSHIDUANG     //  "ʱ��",
SysSettings4,     	//  usbJIANPAN     //  "����",
OffRec1,     		//  usbTSHCHJIA     //  "�������",
SetupCaption15,     //  usbCHJRJIN     //  "�������",
SetupCaption25,     //  usbPIAOWEI     //  "Ʊβ",
SetupCaption26,     //  usbPIAOJTOU    // "Ʊ��Ʊͷ",
SetupCaption22,     //  usbICCAGUASHI     //  "IC����ʧ",

usbFLOWNEWMESS,     //usbFLOWNEW    ����������   //
usbFLOWALLMESS,     //usbFLOWALL    ����ȫ������
usbFLOWDELMESS,     //usbFLOWALLDEL ����ȫ�����ݺ����

//<<<<<<<<<<<<<<<
#endif

DEPTREPORTTITLE,       //HDEPTREPORT   //zengy "������     ����     ��� "
PLUREPORTTITLE,        //HPLUREPORT    //zengy "��Ʒ����     ����    ���  "
MESS_PRESSKEY,         //PRESSANYKEY
SysFlags21,            //PRICEBARCODE //ccr2016-01-22

SysFlags32,             // HEADCENTER "Ʊͷ���д�ӡ"
SysFlags33,             // TRAILCENTER "Ʊβ���д�ӡ"
SysFlags34,             // HEADDBLHIGH "Ʊͷ���ߴ�ӡ"
SysFlags35,             // TRAILDBLHIGH "Ʊβ���ߴ�ӡ"
//ccr2016-02-17>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�������ܶ���...................
MGADDINV    ,//MsgMGADDINV     "���ӵ�Ʒ���"
MGDECINV    ,//MsgMGDECINV     "���ٵ�Ʒ���"
MGSETPRICE  ,//MsgMGSETPRICE   "�޸ĵ�Ʒ�۸�"
MGCLEARIC   ,//MsgMGCLEARIC    "��Ա�˿�"
MGINITIC    ,//MsgMGINITIC     "��ʼ����Ա��"
MGCHARGE    ,//MsgMGCHARGE     "��Ա����ֵ"
MGADDPOINT  ,//MsgMGADDPOINT   "��Ա���ͻ���"
MGPRINTSTOCK ,//MsgMGPRINTSTOCK   "��ӡ��Ʒ���"
MGPASSWORD  ,//MsgMGPASSWORD    "���þ�������"
MGCLOSEPRN  ,//MsgMGCLOSEPRN    "�رմ�ӡ"
#if (!defined(DD_LOCK) || !defined(TR))
MGTRAINING  ,//MsgMGTRAINING    "��ѵģʽ"
#endif
MGGOTOMG    ,//MsgMGGOTOMG      "����"

//ccr2016-03-09>>>>��ˮ��ѯ��ӡ>>>>>>>
MESSALLLOG       ,//MsgALLLOG        "ȫ���վ�"
MESSDATERANGE   ,//MsgDATERANGE    "���ڷ�Χ"
MESSVIPLOG,     //MsgVIPLOG        "��Ա���Ѽ�¼"
MESSPRNCASH     ,//MsgPRNCASH      "��ӡ�����¼"
MESSPRNDEPART   ,//MsgPRNDEPART    "��ӡ�����¼"
MESSPRNPLU      ,//MsgPRNPLU       "��ӡ��Ʒ��¼"
MESSPRNDISCOUNT ,//MsgPRNDISCOUNT  "��ӡ�ۿۼӳ�"
MESSPRNRAPO     ,//MsgPRNRAPO      "��ӡ�����"
MESSPRNCORRECT  ,//MsgPRNCORRECT   "��ӡ��������"
MESSPRNCANCEL   ,//MsgPRNCANCEL    "��ӡȡ������"
MESSPRNNOSALE   ,//MsgPRNNOSALE    "��ӡ������"
                 //
MESSALLCASH     ,//MsgALLCASH      "ȫ�����ʽ"
MESSSELCASH     ,//MsgSELCASH      "ѡ�񸶿ʽ"
MESSALLDEPT     ,//MsgALLDEPT      "��ӡȫ������"
MESSSELDEPT     ,//MsgSELDEPT      "ѡ��һ������"
MESSALLPLU      ,//MsgALLPLU       "��ӡȫ����Ʒ"
MESSSELPLU      ,//MsgSELPLU       "ѡ��һ����Ʒ"

PLUNUMBER,       //MsgPLUNUMBER    "��¼��:"
PLURANDOMSIZE   ,//MsgPLURANDOMSIZE    	"����λ��:"
PLUNAMESIZE		,//MsgPLUNAMESIZE    	    "���Ƴ���:"
PLUPRICESIZE    ,//MsgPLUPRICESIZE       "�۸�λ��:"
PLUPRICELEVEL   ,//MsgPLUPRICELEVEL      "��Ա�ۼ���:"
PLUCOSTSIZE     ,//MsgPLUCOSTSIZE        "����λ��:"
PLUINVENTSIZE   ,//MsgPLUINVENTSIZE      "���λ��:"
PLUREPQTYSIZE   ,//MsgPLUREPQTYSIZE      "��������λ��:"
PLUREPAMTSIZE   ,//MsgPLUREPAMTSIZE      "������λ��:"
PLUREPDISCSIZE  ,//MsgPLUREPDISCSIZE     "ͳ���ۿ�λ��:"
PLUREPCOSTSIZE  ,//MsgPLUREPCOSTSIZE     "ͳ�ƽ���λ��:"
//ccr2016-02-17<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
DATETYPE ,        //MsgDATETYPE"FORMAT "
DDMMYYYY ,        //MsgDDMMYYYY"DDMMYYYY"
MMDDYYYY ,        //MsgMMDDYYYY"MMDDYYYY"
YYYYMMDD ,        //MsgYYYYMMDD"YYYYMMDD"

//ccr2016-04-05>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
POINTTYPE1          ,//MsgPOINTTYPE1 "1.000,00"  //��λС��
POINTTYPE2          ,//MsgPOINTTYPE2 "1,000.00"  //��λС��
POINTTYPE3          ,//MsgPOINTTYPE3 "1.000"     //��С��
POINTTYPE4          ,//MsgPOINTTYPE4 "1,000"     //��С��
#if !defined(CASE_FORHANZI)
POINTTYPE5          ,//MsgPOINTTYPE5 "1.000,000"  //��λС��
POINTTYPE6          ,//MsgPOINTTYPE6 "1,000.000"  //��λС��
//POINTTYPE7          ,//MsgPOINTTYPE7 "1.000,0"  //һλС��
//POINTTYPE8          ,//MsgPOINTTYPE8 "1,000.0"  //һλС��
#endif
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
MESSEJMESSAGES,  //MsgEJMESSAGES   //"EJ�洢��Ϣ"
MESSEJALLEJ     ,//MsgEJALLEJ      //"��ӡȫ��EJ"
MESSEJDATERANGE ,//MsgEJDATERANGE  // "���ڷ�ΧEJ"
MESSEJRECEIPT   ,//MsgEJRECEIPT    // "��ӡ�վ�EJ"
MESSEJXREPORT   ,//MsgEJXREPORT    // "��ӡX-EJ"
MESSEJZREPORT   ,//MsgEJZREPORT    // "��ӡZ-EJ"
MESSEJCLERK     ,//MsgEJCLERK      //"��ӡ�տ�ԱEJ"
#endif

#if defined(CASE_QRCODE)
InputQRCode,           //MsgQRCODE "��ά��"
#endif

GPRSServerIP,			//GPRSSERVERIP
GPRSServerPort,			//GPRSSERVERPORT


#if(defined(CASE_GPRS))
//ccr2014-11-11 NEWSETUP>>>>>GPRS ���ܲ˵� >>>>>>>>>>
GPRSAPNName,           //GPRSAPNNAME
GPRSUserName,           //GPRSUSERNAME
GPRSPassword,           //GPRSPASSWORD

GPRSSetMode,        //gprsSETMODE //ccr2014-11-11 NEWSETUP-step2
GPRSSendECRLogAll,        //gprsSENDECRLOGAll //ccr2014-11-11 NEWSETUP-step2
GPRSDownloadPLU   ,     //  "���ص�Ʒ"    //gprsDownloadPLU //ccr2014-11-11 NEWSETUP-step2
GPRSDownloadDEPT  ,     //  "���ز���"    //gprsDownloadDEPT //ccr2014-11-11 NEWSETUP-step2
GPRSDownloadCLERK ,     //  "�����տ�Ա"    //gprsDownloadCLERK //ccr2014-11-11 NEWSETUP-step2
GPRSDownloadHEAD  ,     //  "����Ʊͷ"       //gprsDownloadHEAD //ccr2014-11-11 NEWSETUP-step2
GPRSDownloadTRAIL ,     //  "����Ʊβ"      //gprsDownloadTRAIL //ccr2014-11-11 NEWSETUP-step2
GPRSDownloadALL ,     //  "����ȫ������"      //gprsDownloadALL //ccr2016-08-18
GPRSRestart,            //  "��λGPRSģ��"      //gprsRestart //ccr2016-08-26
GPRSSendMESS,			//gprsSENDMESS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif
0
};
//add by lqw 090802
#if(defined(CASE_GPRS))
CONST GPRSSTR GPRSMess[G_GPRSMessMax]={
	GPRSstr1,						//G_xDATATYPE 0            ccr"�������ʹ�"
	GPRSstr2,						//G_GPRSOK                 ccr"GPRS READY"
	GPRSstr3,						//G_GPRSNOTOK              ccr"GPRS ����"
	GPRSstr4,						//G_CONFIRM                ccr"��ȷ��"
	GPRSstr5,						//G_SERVERIP_NULL          ccr"������IPΪ��"
	GPRSstr6,						//G_X_IPPORT               ccr"������IP��"
	GPRSstr7,						//G_WAITFOR                ccr"�ȴ�GPRS"
	GPRSstr10,						//G_SHUJUFASONGZHONG       ccr"���ݷ�����.."
	GPRSstr11,						//G_SHUJUYIFACHU           "�����ѷ���.."
	GPRSstr28,                      //G_FASONGCHENGGONG        "���ͳɹ�.."
	GPRSstr31,                      //G_LIANJIESERVERSHIBAI    "���ӷ�����ʧ��"
	GPRSstr32,                      //G_JIESHOUSHIBAI          "����ʧ��"
	GPRSstr34,                      //G_FASONGSHIBAI           "����ʧ��"
	GPRSServerIP,                   //G_SERVERIP
	GPRSServerPort,                 //G_SERVERPORT
	GPRSstr58,                      //G_CONNECTING              "���ڽ�������.."
	GPRSstr59,                      //G_TOCONNECTING            "׼����������.."
	GPRSstr60,                      //G_FUWEIMOKUAI             "���ڸ�λģ��.."
	GPRSstr61                       //G_CHENGGONGTUICHU         "�������,���˳�.."
};
#endif
//----------�ַ�������------------------------------------------------------
const char
            cMsg_NOSTOCK[]=Msg_NOSTOCK,  //�޿������
            cMsg_DISPSTOCK[]=Msg_DISPSTOCK,//��ʾ/��ӡ?
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))//ccr2016-10-25>>>>EJ
            cMsg_RECNUMFR[]= Msg_RECNUMFR	,//"Rec_FROM"                  //��ʼ�վݺ�	//RECNUMFR
            cMsg_RECNUMTO[]= Msg_RECNUMTO	,//"Rec_TO"                    //�����վݺ�	//RECNUMTO
            cMsg_EJBBIAO[]= Msg_EJBBIAO	,//	"~E~J ~R~E~P~O~R~T"		//EJ ����			//EJBBIAO
            cMsg_EJXINXI[]= Msg_EJXINXI	,//	"EJ INFORMATIONS"            //EJ��Ϣ			//EJXINXI
            cMsg_EJBHAO[]= Msg_EJBHAO		,//"EJ MEMORY ID"						//EJ���			//EJBHAO
            cMsg_SIZEEJ[]= Msg_SIZEEJ		,//"Size of LOG"				//SIZEEJ
            cMsg_EJLEFT[]=Msg_EJLEFT,        //ʣ��ռ�
            cMsg_EJCSHUA[]= Msg_EJCSHUA	,//	"EJ INITIALISATION:"		//EJ��ʼ��		//EJCSHUA
            cMsg_FORMAT[] = Msg_FORMAT,//      "FAST FORMAT"
            cMsg_EJDATEEND[]= Msg_EJDATEEND,// "DATE LAST EJ"
            cMsg_EJRECORDS[]= Msg_EJRECORDS,// "LAST EJ#"

#endif//ccr2016-10-25<<<<<<<<
            cMESS_PAYALSO[]=MESS_PAYALSO,
            cMESSSETMENU[]=MESSSETMENU,
            cDEPTTITLE[]=DEPTTITLE,
            cPLULIST[]=PLULIST,
            cPLUTITLE1[]=PLUTITLE1,
            cPLUTITLE2[]=PLUTITLE2,
            cMESSPLUPRINTEND[]=MESSPLUPRINTEND,
            cMESS_TABLEHOLD[]=MESS_TABLEHOLD,
            cMESSPRNMENU[]=MESSPRNMENU,
            cPRTStyleN1[]=PRTStyleN1,
            cPRTStyleN2[]=PRTStyleN2,
            cPRTStyleN3[]=PRTStyleN3,
            cPRTStyleN4[]=PRTStyleN4,
            cComTestN1[]=ComTestN1,
            cComTestN2[]=ComTestN2,
            cComTestN3[]=ComTestN3,
            cComTestN4[]=ComTestN4,
            cCurrentTimeN1[]=CurrentTimeN1,
            cMESSCONFIGERR[]=MESSCONFIGERR,
            cMESSCLEANFILES[]=MESSCLEANFILES,
            cMESSRAMOUT[]=MESSRAMOUT,
            cMESSDELPLU[]=MESSDELPLU,
            cMESSCLEANLOG[]=MESSCLEANLOG,
            cMESSCLEANLOGA[]=MESSCLEANLOGA,
            cSpecialSymbol3[]=SpecialSymbol3,
            cRECALLFLOW[]=RECALLFLOW,
            cErrInfoN1[]=ErrInfoN1,
            cErrInfoN3[]=ErrInfoN3,
            cMessageE18[]=MessageE18,
            cEXPORTCSV[]=EXPORTCSV,
			cDEPTCAP[]=DEPTCAP,
			cPLUCAP[]=PLUCAP     ,
			cTAXCAP[]=TAXCAP     ,
			cHEADERCAP[]=HEADERCAP  ,
			cDISCCAP[]=DISCCAP    ,
			cSALPERCAP[]=SALPERCAP  ,
			cSYSTEMCAP[]=SYSTEMCAP  ,
			cCOMMCAP[]=COMMCAP    ,
			cGRAPPRNCAP[]=GRAPPRNCAP ,
			cGROUPCAP[]=GROUPCAP   ,
			cICCARDCAP[]=ICCARDCAP  ,
			cPROMCAP[]=PROMCAP    ,
			cPBFUNCCAP[]=PBFUNCCAP  ,
			cCLERKCAP[]=CLERKCAP   ,
			cMODICAP[]=MODICAP    ,
			cPBTOTALCAP[]=PBTOTALCAP ,
			cZONECAP[]=ZONECAP    ,
			cKEYBOARDCAP[]=KEYBOARDCAP,
			cOFFCAP[]=OFFCAP     ,
			cPORACAP[]=PORACAP    ,
			cTRAILERCAP[]=TRAILERCAP ,
			cSLIPHEADCAP[]=SLIPHEADCAP,
			cICBLOCKCAP[]=ICBLOCKCAP ,
            cUSBREPNAME[]=USBREPNAME,
            cSetupCaption38[]=SetupCaption38,
            cSetupCaption39[]=SetupCaption39,
            cCSVREPTITL[]=CSVREPTITL,
            cReportType0[]=ReportType0,
            cReportType1[]=ReportType1,
            cReportType2[]=ReportType2,
            cReportType3[]=ReportType3,
            cReportType7[]=ReportType7,
            cReportType8[]=ReportType8,
            cReportType13[]=ReportType13,
            cReportType17[]=ReportType17,
            cReportType18[]=ReportType18,
#if defined(CASE_FORHANZI)
            cInputMode1[]=InputMode1,
            cInputMode2[]=InputMode2,
            cInputMode3[]=InputMode3,
            cInputMode4[]=InputMode4,
#endif
            cBUTTONBATLOW[]=BUTTONBATLOW,
            cCHARGEBATNOW[]=CHARGEBATNOW,
            cREPRN_PWON[]=REPRN_PWON,
#if (NUMPORT==3)
            cComTestN3ERR[]=ComTestN3ERR,
            cComTestN3OK[]=ComTestN3OK,
#endif
            cSRAMNOTFOUND[]=SRAMNOTFOUND,
            cCLERKPASS[]=CLERKPASS,
            cDEPTLIST[]=DEPTLIST,
            cCLEARGRANDTOTAL[]=CLEARGRANDTOTAL,
            cMsgNET[]=MsgNET,
            cCLOSEPRINTER[]=CLOSEPRINTER,//    "�رմ�ӡ��"
            cCLEANALLECRVIP[]= CLEANALLECRVIP,//  "CLEAN ECR-VIP?"//"�����Ա����?"
            cECRVIPTITLE[]=ECRVIPTITLE,//"��Ա��      ���ѽ��     �Ƶ�"
            cCREATEDATE[]=CREATEDATE,//��������:
            cVIPLOGOUT[]=VIPLOGOUT, // �޴˻�Ա
            cVIPTOTAL[]=VIPTOTAL,// �ܶ�
            cVIPTOTALA[]=VIPTOTALA,// �����ܶ�
            cDECVIPPOINT[]=DECVIPPOINT,//�ҽ�
            cADDVIPPOINT[]=ADDVIPPOINT,//�ͷ�
            cINPUTVIPNAME[]=INPUTVIPNAME,//"�����Ա����:"
#if defined(CASE_PERU)
            cMsgCUSTOMER[]=MsgCUSTOMER,//     "CUSTOMER"
#endif
            cPRINTKEYBOARD[]=PRINTKEYBOARD;//��ӡ���̲���
//---------------------------------------------------------------------------

#if (defined(DEBUGBYPC))

#include "exthead.h"
#include "exth.h"

void PrintMsg(char* msgName,int idx)
{
    char sBuf[225];
    static int selfIDX;

    if (idx==0) selfIDX=0;
    if (idx!=selfIDX)
        sprintf(sBuf,">>>>>%s:\t%d",msgName,idx);
    else
    {
        selfIDX++;
        if (idx<HZMESSMAX)
            sprintf(sBuf,"%d:%s\t---->\t%s",idx,msgName,Msg[idx].str);
        else
            sprintf(sBuf,"%d:%s\t---->\t%s",idx,msgName,"XXXXXXXX");
    }
    RJPrint(0,sBuf);

}

void PrintChnMess()
{
// MSg[]>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
PrintMsg(("LING"),			0);				//WAIT

PrintMsg(("SHOUKUAN"),(LING+1));		//Ӫҵ
PrintMsg(("XBBIAO"),(SHOUKUAN+1));	//����
PrintMsg(("ZBBIAO"),(XBBIAO+1));		//����
PrintMsg(("SHEZHI"),(ZBBIAO+1));		//����
PrintMsg(("JINLI"),(SHEZHI+1));		//����

//vvvvvvvvvvvvvvvv���õ��˵���ص���Ϣ����vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//���õ������˵�����Ŀ���洢��SubMenuItems��

/* ���õ�һ���˵�(���˵�) */
PrintMsg(("MENUFILES"),(JINLI+1));		//���Ϲ���
PrintMsg(("ZHGNSZ"),(MENUFILES+1));	//ϵͳ����
PrintMsg(("DEFKEYBOARD"),(ZHGNSZ+1));	    //���̶���
PrintMsg(("PJYSSZ"),(DEFKEYBOARD+1));	//ƱͷƱβ
PrintMsg(("COMMHOST"),(PJYSSZ+1));      //ͨѶ
PrintMsg(("TXKYWS"),(COMMHOST+1));    //����豸
PrintMsg(("CYGNSZ"),(TXKYWS+1));		//��������
PrintMsg(("BBGNSZ"),(CYGNSZ+1));		//�������
PrintMsg(("MENUDISC"),(BBGNSZ+1));      //�ۿ۴���
PrintMsg(("JYGLSZ"),(MENUDISC+1));	//���۹�������
PrintMsg(("ICKGLI"),(JYGLSZ+1));		//IC������
#if !defined(DD_LOCK)
PrintMsg(("QXSZHI"),(ICKGLI+1));		//����Ȩ��
#else
PrintMsg(("QXSZHI"),(ICKGLI));		//����Ȩ��
#endif
PrintMsg(("MENUSERVICE"),(QXSZHI+1));		//ά��(SERVICE)
//���ڲ˵�����,Msg[]������Ϣ>>>>>>>>......
//PrintMsg(("MENUID_FILES"),(1)		//���Ϲ���
//PrintMsg(("MENUID_SYS"),(MENUID_FILES+1));	//ϵͳ����
//PrintMsg(("MENUID_DEFKB"),(MENUID_SYS+1));	    //���̶���
//PrintMsg(("MENUID_HEAD"),(MENUID_DEFKB+1));	//ƱͷƱβ
//PrintMsg(("MENUID_COMM"),(MENUID_HEAD+1));      //ͨѶ
//PrintMsg(("MENUID_DEV"),(MENUID_COMM+1));    //����豸
//PrintMsg(("MENUID_RES"),(MENUID_DEV+1));		//��������
//PrintMsg(("MENUID_REP"),(MENUID_RES+1));		//�������
//PrintMsg(("MENUID_DISC"),(MENUID_REP+1));      //�ۿ۴���
//PrintMsg(("MENUID_OP"),(MENUID_DISC+1));	//���۹�������
//PrintMsg(("MENUID_VIP"),(MENUID_OP+1));		//IC������
//#if !defined(DD_LOCK)
//PrintMsg(("MENUID_PWD"),(MENUID_VIP+1));		//����Ȩ��
//#else
//PrintMsg(("MENUID_PWD"),(MENUID_VIP)		//����Ȩ��
//#endif
//PrintMsg(("MENUID_SERVICE"),(MENUID_PWD+1));		//ά��(SERVICE)
//PrintMsg(("SUBMENTMAX"),(MENUSERVICE-MENUFILES+1));
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<........

//���õ������˵�>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//    PrintMsg(("SETIDXFROM"),(MENUSERVICE+1));           //������Ŀ�Ŀ�ʼ���

    /* ZHGNSZ�µ��ۺϹ������ò˵� */
    PrintMsg(("SETSYSFLAG"),      SETIDXFROM);        //ϵͳ��������
    PrintMsg(("SETPOINTTYPE"),(SETSYSFLAG+1));    //����С������
    PrintMsg(("SETDATE"),(SETPOINTTYPE+1));	  //��������
    PrintMsg(("SETTIME "),(SETDATE+1));  	  //����ʱ��
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
    PrintMsg(("SETEJOURNAL"),(SETTIME+1));  	  //����EJ
#endif

    /* DEFKEYBOARD�µ��ۺϹ������ò˵� */
    PrintMsg(("SETKEYB   "),(SETEJOURNAL+1)); 	  //���ü���
    PrintMsg(("SETKEYMACRO"),(SETKEYB+1));         //  MESSKEYMACRO            "���̺�"
    PrintMsg(("SETKEYTYPE"),(SETKEYMACRO+1));     //  MESSKEYTYPE             "����ģʽ"
    PrintMsg(("SETPRINTKEYB"),(SETKEYTYPE+1));     //  MESSKEYTYPE             "����ģʽ"
//    PrintMsg(("MENUKEYBMAX"),(SETKEYTYPE-SETKEYB+1));		/* ccr2014-11-11 NEWSETUP Step-3 total items of sys menu */

    /* ����ģʽѡ��*/
    PrintMsg(("SETREST   "),(SETPRINTKEYB+1));		    //���ò�������
    PrintMsg(("SETMARKET"),(SETREST+1));		        //���ó��м���
//    PrintMsg(("KEYTYPEMAX"),(SETMARKET-SETREST+1));   //����ģʽѡ��

    PrintMsg(("SETGROUP   "),(SETMARKET+1));	  //���� //ccr2014-11-11 NEWSETUP Step-3<<<<<<
    PrintMsg(("SETSALER   "),(SETGROUP+1));	    //ӪҵԱ

    /* SPGLSZ�µ���Ʒ����˵� */
    PrintMsg(("SETPLU   "),(SETSALER+1));		 //��Ʒ
    PrintMsg(("SETDEPT   "),(SETPLU+1)); 	 //����
#if !defined(CASE_FORHANZI)
    PrintMsg(("SETTAX   "),(SETDEPT+1)); 	    //˰��
    PrintMsg(("SETCLERK   "),(SETTAX+1));	    //�տ�Ա
#else
    PrintMsg(("SETCLERK   "),(SETDEPT+1));	    //�տ�Ա
#endif
//    PrintMsg(("MENUPLUMAX"),(SETCLERK-SETPLU+1));	/* total items of plu manages */

    /* COMMHOST�µ�ͨѶ�˵� */
    PrintMsg(("SETCOMPUTER"),(MENUPLUMAX+SETPLU));	    //"�����"
    PrintMsg(("SETIP"),(SETCOMPUTER+1));        //IP��ַ
    //ccr2014-11-11 NEWSETUP Step-3>>>>>>
    #if defined(CASE_GPRS)
    PrintMsg(("SETGPRS"),(SETIP+1));
    #else
    //PrintMsg(("SETGPRS         SETIP
    #endif

    /* TXKYWS�µ�����˵� */
    PrintMsg(("SETBARCODE   "),(SETGPRS+1));        //"����ǹ"
    PrintMsg(("SETBALANCE   "),(SETBARCODE+1));        //"���ӳ�"
    //ccr2016-01-22PrintMsg(("SETPORT4   "),(SETBALANCE+1));        //ͨѶ��4
    PrintMsg(("SETSP"),(SETBALANCE+1));		    //Ʊ�ݴ�ӡ
    PrintMsg(("SETKP"),(SETSP+1));           //������ӡ
    PrintMsg(("SETEXTPRINTER"),(SETKP+1));          //�н�����


    PrintMsg(("SETPROM"),(SETEXTPRINTER+1));          //�н�����

    /* MENUDISC�µ��ۿ۴�����������*/
    PrintMsg(("SETOFF"),(SETPROM+1));           //�Żݼ�
    PrintMsg(("SETDISC   "),(SETOFF+1));		    //�ۿ�

    /* JYGLSZ�µ����۹�������*/
    PrintMsg(("SETTEND   "),(SETDISC+1));		    //���ʽ
    PrintMsg(("SETCORR   "),(SETTEND+1));		    //��������
    PrintMsg(("SETDRAWER"),(SETCORR+1));		    //Ǯ��
    PrintMsg(("SETPORA   "),(SETDRAWER+1));		    //�������
    PrintMsg(("SETCURR   "),(SETPORA+1));		    //���
//    PrintMsg(("MENUMANMAX"),(SETCURR-SETTEND+1));		/* total items of comsume manages */

    /* ICKGLI�µ�IC������*/
    PrintMsg(("SETVIPIC"),(SETCURR+1));          //IC������
    PrintMsg(("SETADDNEWVIP"),(SETVIPIC+1));          //"ADD NEW VIP"
    PrintMsg(("SETPRINTVIP"),(SETADDNEWVIP+1));          //"PRINT VIP"
    PrintMsg(("SETCLEANVIP"),(SETPRINTVIP+1));          //"CLEAN VIP"

    PrintMsg(("SETBLOCKIC"),(SETCLEANVIP+1));           //IC����ʧ
    PrintMsg(("SETPRINTIC"),(SETBLOCKIC+1));	    //��ӡ����Ϣ
//    PrintMsg(("MENUICCMAX"),(SETPRINTIC-SETVIPIC+1));		/* total items of Chip Card */

    /* PJYSSZ�µ�ƱͷƱβ*/
    PrintMsg(("SETHEAD   "),(SETPRINTIC+1));	    //�վ�Ʊͷ
    PrintMsg(("SETTRAIL   "),(SETHEAD+1));         //�վ�Ʊβ
    PrintMsg(("SETSHEAD   "),(SETTRAIL+1)); 	    //Ʊ��Ʊͷ
    PrintMsg(("SETGRAP"),(SETSHEAD+1));	    //ƱβͼƬ
    PrintMsg(("SETPRTGRAP"),(SETGRAP+1));		    //��ӡͼƬ
//    PrintMsg(("MENUTICMAX"),(SETPRTGRAP-SETHEAD+1));		/* total items of tictes */

    /* BBGNSZ�µı�����*/
    PrintMsg(("SETREPORT"),(SETPRTGRAP+1));	    //���ñ�������
    PrintMsg(("SETREPTYPE"),(SETREPORT+1));	    //����Ԫ
    PrintMsg(("SETZONES   "),(SETREPTYPE+1));	    //����ʱ������
    PrintMsg(("SETCLRREP"),(SETZONES+1));	    //���屨��
    PrintMsg(("SETPRTJOUR "),(SETCLRREP+1));	    //��ӡ��ˮ
//    PrintMsg(("MENUREPMAX"),(SETPRTJOUR-SETREPORT+1));		/* total items of report */

    /* CYGNSZ�µĲ�������*/
    PrintMsg(("SETPBINF   "),(SETPRTJOUR+1));	    //��̨
    PrintMsg(("SETPBF   "),(SETPBINF+1));	    //��������
    PrintMsg(("SETMODIF   "),(SETPBF+1)); 	 	    //�˵�˵��
#if (agreeNumber)
    PrintMsg(("SETAGREE"),(SETMODIF+1));        //ǩ��
#endif
//    PrintMsg(("MENUTBLMAX"),(SETMODIF-SETPBINF+1));		/* total items of table function */

    /* QXSZHI�µ�����Ȩ������*/
    #if !defined(DD_LOCK)
    PrintMsg(("SETSETPWD"),(SETMODIF+1));	    //���õ�����
    PrintMsg(("SETXPWD   "),(SETSETPWD+1));	    //ֻ����������
    PrintMsg(("SETZPWD   "),(SETXPWD+1));		    //���ʱ�������
    #endif
    PrintMsg(("SETMGPWD   "),(SETMGPWD));	    //��������
//    PrintMsg(("MENUPWDMAX"),(SETMGPWD-SETSETPWD+1));		/* total items of password setup */

    /* MENUSERVICE�µ�ϵͳ���Թ��� */
    PrintMsg(("SETTEST"),(SETMGPWD+1));      //ϵͳ����
    PrintMsg(("SETCLEARPLU"),(SETTEST+1));      //�����Ʒ
    PrintMsg(("SETPLULIST"),(SETCLEARPLU+1));		 //��ӡ��Ʒ�嵥
    PrintMsg(("SETTSTVER"),(SETPLULIST+1));         //��ӡ�汾
    PrintMsg(("SETCONFIGPLU"),(SETTSTVER+1));      //���õ�Ʒ
    PrintMsg(("SETCONFIGDEPT"),(SETCONFIGPLU+1));              //���ò���
#if CASE_USBDISK
    PrintMsg(("SETINSTALL"),(SETCONFIGDEPT+1));    //��װ/����
    PrintMsg(("SETPRINTFAT"),(SETINSTALL+1));      //��ӡ�ļ������
#else
    PrintMsg(("SETPRINTFAT"),(SETCONFIGDEPT+1));      //��ӡ�ļ������
#endif
    PrintMsg(("SETPRNMENU"),(SETPRINTFAT+1));      //��ӡ���ò˵�
//    PrintMsg(("MENUSERVICEMAX"),(SETPRNMENU-SETTEST+1));

    /* SKJCSHI�µ�ϵͳ���Թ��� */
    PrintMsg(("SETTSTDISP"),(SETPRNMENU+1));       //��ʾ����
    PrintMsg(("SETTSTCUST"),(SETTSTDISP+1));       //���Բ���
    PrintMsg(("SETTSTPRT"),(SETTSTCUST+1));      //��ӡ����
    PrintMsg(("SETTSTCLK"),(SETTSTPRT+1));       //ʱ�Ӳ���
    PrintMsg(("SETTSTMEM"),(SETTSTCLK+1));       //����������
    PrintMsg(("SETTSTBELL"),(SETTSTMEM+1));       //RAM����
    PrintMsg(("SETTSTDRAW"),(SETTSTBELL+1));      //Ǯ�����
    PrintMsg(("SETTSTKBD"),(SETTSTDRAW+1));      //���̲���
    PrintMsg(("SETTSTCOMM"),(SETTSTKBD+1));       //���ڲ���
    PrintMsg(("SETTSTAUTO"),(SETTSTCOMM+1));      //�Զ�����

//    PrintMsg(("MENUTSTMAX"),(SETTSTAUTO-SETTSTDISP+1));		/* total items of test function */
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//    PrintMsg(("SETUPMAX	    SETTSTAUTO	//hf 20060105
    #if (SETUPMAX>254)
    #error "Error on setup IDX" //���ù��ܺŲ���>255
    #endif
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//ccr2016-02-04>>>>ר����ListMenu,Msg[]����Ϣ>>>>>>>>>>>>>>>>>>>>>>>
//PrintMsg(("LISTMGFUNC"),(SETUPMAX+1));      //ccr2016-01-15 ������ѡ��С�ƹ���ListItem���
//PrintMsg(("LISTKEYDES"),(LISTMGFUNC+1));      //ccr2016-02-04 ����������ListItem���
//PrintMsg(("LISTKEYSID"),(LISTKEYDES+1));  //ccr2016-02-04 ��������ϸ����ListItem���
//PrintMsg(("LISTNUMRIC"),(LISTKEYSID+1));  //ccr2016-02-25 �������б�
//ccr2016-02-04<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

PrintMsg(("JLHAO"),(SETUPMAX+1));	//��¼#
PrintMsg(("SHRDMA"),(JLHAO+1));		//��¼?
PrintMsg(("ZONGJI"),(SHRDMA+1));		//�ܼ�
PrintMsg(("ZHHUAN"),(ZONGJI+1));		//ת��
PrintMsg(("XIAOJI"),(ZHHUAN+1));		//С��
PrintMsg(("CHUJIN"),(XIAOJI+1));		//����
PrintMsg(("RUJIN"),(CHUJIN+1));		//���
PrintMsg(("BAOBIAO"),(RUJIN+1));		//����
PrintMsg(("ZENJIA"),(BAOBIAO+1));		//����
PrintMsg(("GUAQI"),(ZENJIA+1));		//�ҵ�
PrintMsg(("QUXIAO"),(GUAQI+1));		//ȡ��
PrintMsg(("MIMA"),(QUXIAO+1));		//����
PrintMsg(("MMQREN"),(MIMA+1));		//����ȷ��
PrintMsg(("DANJIA"),(MMQREN+1));		//����:
PrintMsg(("JINEF"),(DANJIA+1));		//���:
PrintMsg(("CHAOSHI"),(JINEF+1));		//���а�
PrintMsg(("CANYIN"),(CHAOSHI+1));		//������
PrintMsg(("CEISHI"),(CANYIN+1));		//����
PrintMsg(("RAM"),(CEISHI+1));		//  RAM:
PrintMsg(("YINGFU"),(RAM+1));		//Ӧ��
PrintMsg(("JINGE"),(YINGFU+1));		//����
PrintMsg(("JIAGE"),(JINGE+1));		//�۸�
PrintMsg(("JIAOYISHU"),(JIAGE+1));		//������
PrintMsg(("SHULIANG"),(JIAOYISHU+1));		//����
PrintMsg(("JINE"),(SHULIANG+1));		//���
PrintMsg(("SHOUQU"),(JINE+1));		//��ȡ
PrintMsg(("ZHAOLING"),(SHOUQU+1));		//����
PrintMsg(("RI"),(ZHAOLING+1));		//��
PrintMsg(("ZHOU"),(RI+1));		//��
PrintMsg(("YUE"),(ZHOU+1));		//��
PrintMsg(("NIAN"),(YUE+1));		//��
PrintMsg(("BIAOZHUN"),(NIAN+1));		//��׼
PrintMsg(("SHKYUANS"),(BIAOZHUN+1));		//�տ�Ա
PrintMsg(("SHI"),(SHKYUANS+1));		//   ʱ
PrintMsg(("RIS"),(SHI+1));		//   ��
PrintMsg(("YUES"),(RIS+1));		//   ��
PrintMsg(("TUIHUO"),(YUES+1));		//�˻�
PrintMsg(("CHENBEN"),(TUIHUO+1));		//�ɱ�
PrintMsg(("ZUOHAO"),(CHENBEN+1));		//����#
PrintMsg(("ZHPHAO"),(ZUOHAO+1));		//֧Ʊ��#
PrintMsg(("XIANGSHU"),(ZHPHAO+1));		//����:
PrintMsg(("HSHXSHOU"),(XIANGSHU+1));		//��˰����
PrintMsg(("SHUIE"),(HSHXSHOU+1));		//˰��
PrintMsg(("YEHAO"),(SHUIE+1));		//ҳ��
PrintMsg(("HAOMA"),(YEHAO+1));		//����:
PrintMsg(("GUAZHE"),(HAOMA+1));		//����
PrintMsg(("KAITAI"),(GUAZHE+1));		//��̨
PrintMsg(("QZHJSHU"),(KAITAI+1));		//���ʼ���
PrintMsg(("QINGCHU"),(QZHJSHU+1));		//���
PrintMsg(("SBAOBIAO"),(QINGCHU+1));		//S-����
PrintMsg(("MAOLI"),(SBAOBIAO+1));		//ë��
PrintMsg(("KCZJIA"),(MAOLI+1));		//�������
PrintMsg(("KCJIANSHAO"),(KCZJIA+1));		//�������
PrintMsg(("YZHZHANG"),(KCJIANSHAO+1));		//ԭ����:
PrintMsg(("XYKHAO"),(YZHZHANG+1));		//���ÿ�#
PrintMsg(("XZHZHANG"),(XYKHAO+1));		//������:
PrintMsg(("RENSHU"),(XZHZHANG+1));		//����
PrintMsg(("HUANHUO"),(RENSHU+1));		//����
PrintMsg(("ZENJIAA"),(HUANHUO+1));		//����?
PrintMsg(("SHANCHU"),(ZENJIAA+1));		//ɾ��?ZENJIAA��SHANCHU���ܼ��
PrintMsg(("ZHKOU1"),(SHANCHU+1));		//�ۿ��� 1
PrintMsg(("ZHKOU2"),(ZHKOU1+1));		//�ۿ��� 2
PrintMsg(("XSHOUE"),(ZHKOU2+1));		//���۶�
PrintMsg(("DBYHUI"),(XSHOUE+1));		//����Ż�
PrintMsg(("KCSHLIANG"),(DBYHUI+1));		//�������
PrintMsg(("TJYHUI"),(KCSHLIANG+1));		//�ؼ��Ż�
PrintMsg(("XUANXIANG"),(TJYHUI+1));		//ѡ��:
PrintMsg(("GDZHKOU"),(XUANXIANG+1));		//�̶�
PrintMsg(("FDZHKOU1"),(GDZHKOU+1));		//����
PrintMsg(("GFZHKOU1"),(FDZHKOU1+1));		//��/��
PrintMsg(("KTZHJIE"),(GFZHKOU1+1));		//��̨�ݽ�
PrintMsg(("KTZJIA"),(KTZHJIE+1));		//��ӡ��̨
PrintMsg(("ZHANJIE"),(KTZJIA+1));		//�ݽ�
PrintMsg(("QRJZHANG"),(ZHANJIE+1));		//ȷ�Ͻ���
PrintMsg(("DYKTAI"),(QRJZHANG+1));		//��ӡ��̨
PrintMsg(("DYZHDAN"),(DYKTAI+1));		//��ӡ�ʵ�
PrintMsg(("QXQREN"),(DYZHDAN+1));		//ȡ��ȷ��
PrintMsg(("FENZHANG"),(QXQREN+1));		//����
PrintMsg(("ZHUANZHANG"),(FENZHANG+1));		//ת��
PrintMsg(("GHSHKYUAN"),(ZHUANZHANG+1));		//������̨
PrintMsg(("GKRSHU"),(GHSHKYUAN+1));		//�˿�����
PrintMsg(("ZHJSHDING"),(GKRSHU+1));		//�н��趨:
PrintMsg(("JIFEN"),(ZHJSHDING+1));		//���ѻ���:
PrintMsg(("GBDPJGE"),(JIFEN+1));		//�ı䵥Ʒ�۸�
PrintMsg(("CHFDYJZU"),(GBDPJGE+1));		//������ӡ����
PrintMsg(("ZJKCUN"),(CHFDYJZU+1));		//���ӿ��
PrintMsg(("JSHKCUN"),(ZJKCUN+1));		//���ٿ��
PrintMsg(("SHURU"),(JSHKCUN+1));		//����
PrintMsg(("DAIFU"),(SHURU+1));		//����
PrintMsg(("RS232ERR"),(DAIFU+1));		//RS232��
PrintMsg(("RS232OK"),(RS232ERR+1));		//RS232��ȷ
PrintMsg(("RTCERR"),(RS232OK+1));		//RTC ��!
PrintMsg(("CTCERR"),(RTCERR+1));		//CTC ��!
PrintMsg(("FPROMERR"),(CTCERR+1));		//FPROM��!
PrintMsg(("CHSHHUA"),(FPROMERR+1));		//��ʼ��...
PrintMsg(("SHSHHJSHU"),(CHSHHUA+1));		//��ʼ������.
PrintMsg(("CHUCUO"),(SHSHHJSHU+1));		//����-
PrintMsg(("MMACUO"),(CHUCUO+1));		//����� ��
PrintMsg(("BCMMA"),(MMACUO+1));		//�����ѱ���
PrintMsg(("SHKYUANF"),(BCMMA+1));		//�տ�Ա:
PrintMsg(("YYYUANF"),(SHKYUANF+1));		//ӪҵԱ:
PrintMsg(("SHKJHAO"),(YYYUANF+1));		//�տ����:
PrintMsg(("WEIZHI"),(SHKJHAO+1));		//λ��:
PrintMsg(("QUERENF"),(WEIZHI+1));		//ȷ��?
PrintMsg(("WANCHENG"),(QUERENF+1));		//���
PrintMsg(("FXBBEN"),(WANCHENG+1));		//���а汾:
PrintMsg(("BCXFEI"),(FXBBEN+1));		//�������ѵ�
PrintMsg(("ZJDPIN"),(BCXFEI+1));		//������Ʒ:
PrintMsg(("SHCHDP"),(ZJDPIN+1));		//ɾ����Ʒ:
PrintMsg(("KSHJCE"),(SHCHDP+1));		//��ʼ���>>
PrintMsg(("JCJSHU"),(KSHJCE+1));		//<<������
PrintMsg(("KUCUN"),(JCJSHU+1));		//���
PrintMsg(("BBQQING"),(KUCUN+1));		//������ȫ��!
PrintMsg(("GXBIOS"),(BBQQING+1));		//���³�������ϵ�
PrintMsg(("WJKJYJIE"),(GXBIOS+1));		//�ļ��ռ�Խ��
PrintMsg(("JSHDPSHL"),(WJKJYJIE+1));		//�ڴ������
PrintMsg(("RZQMAN"),(JSHDPSHL+1));		//��ˮ�洢����
PrintMsg(("GHDYZHI"),(RZQMAN+1));		//�������ӡֽ
PrintMsg(("KZNCCUO"),(GHDYZHI+1));		//��չ�ڴ����
PrintMsg(("SHUOMINF"),(KZNCCUO+1));		//˵������:

PrintMsg(("CWXXI01"),(SHUOMINF+1));		//��Ч����!
PrintMsg(("CWXXI02"),(CWXXI01+1));		//��Ч����!
PrintMsg(("CWXXI03"),(CWXXI02+1));		//��Чʱ��!
PrintMsg(("CWXXI04"),(CWXXI03+1));		//��ֹ����!
PrintMsg(("CWXXI05"),(CWXXI04+1));		//PLU����Ϊ��!
PrintMsg(("CWXXI06"),(CWXXI05+1));		//PLU�ļ����!
PrintMsg(("CWXXI07"),(CWXXI06+1));		//��̨��ռ��!
PrintMsg(("CWXXI08"),(CWXXI07+1));		//��̨�Ѵ�!
PrintMsg(("CWXXI09"),(CWXXI08+1));		//��̨�Ų���!
PrintMsg(("CWXXI10"),(CWXXI09+1));		//��������̨��
PrintMsg(("CWXXI11"),(CWXXI10+1));		//��̨û�п�̨
PrintMsg(("CWXXI12"),(CWXXI11+1));		//��̨�������
PrintMsg(("CWXXI13"),(CWXXI12+1));		//��ֹ�޸�ʱ��
PrintMsg(("CWXXI14"),(CWXXI13+1));		//����������!
PrintMsg(("CWXXI15"),(CWXXI14+1));		//���ۻ�������
PrintMsg(("CWXXI16"),(CWXXI15+1));		//��Ʒû���۳�
PrintMsg(("CWXXI17"),(CWXXI16+1));		//���ڽ�����!
PrintMsg(("CWXXI18"),(CWXXI17+1));		//�������ݳ���
PrintMsg(("CWXXI19"),(CWXXI18+1));		//���ڸ���!
PrintMsg(("CWXXI20"),(CWXXI19+1));		//�������!
PrintMsg(("CWXXI21"),(CWXXI20+1));		//û��ȷ�Ͻ���
PrintMsg(("CWXXI22"),(CWXXI21+1));		//��ֹȡ������
PrintMsg(("CWXXI23"),(CWXXI22+1));		//�޲���!
PrintMsg(("CWXXI24"),(CWXXI23+1));		//�޴��տ�Ա!
PrintMsg(("CWXXI25"),(CWXXI24+1));		//�տ�Ա�ı�
PrintMsg(("CWXXI26"),(CWXXI25+1));		//�޴��౨��!
PrintMsg(("CWXXI27"),(CWXXI26+1));		//�����ӡ�ж�
PrintMsg(("CWXXI28"),(CWXXI27+1));		//�����ھ���
PrintMsg(("CWXXI29"),(CWXXI28+1));		//���ܷ���ʱ��
PrintMsg(("CWXXI30"),(CWXXI29+1));		//�����������!
PrintMsg(("CWXXI31"),(CWXXI30+1));		//ת�뵽
PrintMsg(("CWXXI32"),(CWXXI31+1));		//δ��Ȩ!
PrintMsg(("CWXXI33"),(CWXXI32+1));		//��ָ���տ�Ա
PrintMsg(("CWXXI34"),(CWXXI33+1));		//��ָ��ӪҵԱ
PrintMsg(("CWXXI35"),(CWXXI34+1));		//��ֹPLU��ۣ�
PrintMsg(("CWXXI36"),(CWXXI35+1));		//���벻��!
PrintMsg(("CWXXI37"),(CWXXI36+1));		//������ӡ����
PrintMsg(("CWXXI38"),(CWXXI37+1));		//Ʊ�ݴ�ӡ����
PrintMsg(("CWXXI39"),(CWXXI38+1));		//��ӡѹ��̧��
PrintMsg(("CWXXI40"),(CWXXI39+1));		//��ӡֽ����!
PrintMsg(("CWXXI41"),(CWXXI40+1));		//��ӡ�¶�̫��
PrintMsg(("CWXXI42"),(CWXXI41+1));		//����δ����!
PrintMsg(("CWXXI43"),(CWXXI42+1));		//����������
PrintMsg(("CWXXI44"),(CWXXI43+1));		//��ֹ���ָ���
PrintMsg(("CWXXI45"),(CWXXI44+1));		//�����޴˹���
PrintMsg(("CWXXI46"),(CWXXI45+1));		//δ��С�Ƽ�!
PrintMsg(("CWXXI47"),(CWXXI46+1));		//���ڹ�����
PrintMsg(("CWXXI48"),(CWXXI47+1));		//������ˮ��
PrintMsg(("CWXXI49"),(CWXXI48+1));		//MODEMͨѶ��
PrintMsg(("CWXXI50"),(CWXXI49+1));		//����������!
PrintMsg(("CWXXI51"),(CWXXI50+1));		//POS�����!
PrintMsg(("CWXXI52"),(CWXXI51+1));		//�����ݴ�!
PrintMsg(("CWXXI53"),(CWXXI52+1));		//Ϊ���ڿ�!
PrintMsg(("CWXXI54"),(CWXXI53+1));		//Ϊ��ʧ��!
PrintMsg(("CWXXI55"),(CWXXI54+1));		//�ͻ�����!
PrintMsg(("CWXXI56"),(CWXXI55+1));		//Ϊ�¿�!
PrintMsg(("CWXXI57"),(CWXXI56+1));		//���ǹ��￨!
PrintMsg(("CWXXI58"),(CWXXI57+1));		//д������!
PrintMsg(("CWXXI59"),(CWXXI58+1));		//���Ų���!
PrintMsg(("CWXXI60"),(CWXXI59+1));		//�����ۿۿ�!
PrintMsg(("CWXXI61"),(CWXXI60+1));		//�����ֽ�!
PrintMsg(("CWXXI62"),(CWXXI61+1));		//�������ʿ�!
PrintMsg(("CWXXI63"),(CWXXI62+1));		//�� ApplVar.IC ��!
PrintMsg(("CWXXI64"),(CWXXI63+1));		//�忨����!
PrintMsg(("CWXXI65"),(CWXXI64+1));		//�������!
PrintMsg(("CWXXI66"),(CWXXI65+1));		//IC��ֵ����!
PrintMsg(("CWXXI67"),(CWXXI66+1));		//IC��ʼ������
PrintMsg(("CWXXI68"),(CWXXI67+1));		//��ֹ��ʼ��!
PrintMsg(("CWXXI69"),(CWXXI68+1));		//IC����!
PrintMsg(("CWXXI70"),(CWXXI69+1));		//IC�������!
PrintMsg(("CWXXI71"),(CWXXI70+1));		//IP��ַ��!
PrintMsg(("CWXXI72"),(CWXXI71+1));		//��IC��!
PrintMsg(("CWXXI73"),(CWXXI72+1));		//���йҵ�

PrintMsg(("CWXXI74"),(CWXXI73+1));         //  ��ص�����"
PrintMsg(("CWXXI75"),(CWXXI74+1));         //  û������"
PrintMsg(("CWXXI76"),(CWXXI75+1));         // ��U��!     //
PrintMsg(("CWXXI77"),(CWXXI76+1));         // ���ļ�����     //
PrintMsg(("CWXXI78"),(CWXXI77+1));         // ���ļ�����!     //
PrintMsg(("CWXXI79"),(CWXXI78+1));         // д�ļ�����!     //
PrintMsg(("CWXXI80"),(CWXXI79+1));         //�����ļ�����     //
PrintMsg(("CWXXI81"),(CWXXI80+1));         // �ر��ļ�����     //
                                            //GPRS>>>>>
PrintMsg(("CWXXI82    "),(CWXXI81+1));         //���뷢����ˮ����
PrintMsg(("CWXXI83"),(CWXXI82+1));         //GPRS����
PrintMsg(("CWXXI84"),(CWXXI83+1));         //�������ݳ���
PrintMsg(("CWXXI85"),(CWXXI84+1));         //�������ݳ���
PrintMsg(("CWXXI86"),(CWXXI85+1));         //�޷����ӷ�����
PrintMsg(("CWXXI87"),(CWXXI86+1));         //�޷�����IP��ַ
PrintMsg(("CWXXI88"),(CWXXI87+1));         //��SIM��
PrintMsg(("CWXXI89"),(CWXXI88+1));          //GPRSδ����
PrintMsg(("CWXXI90"),(CWXXI89+1));          //�ѵ������
PrintMsg(("CWXXI91"),(CWXXI90+1));          //�޴˻�Ա

PrintMsg("CWXXI92",   (CWXXI91 +1));	    //"EJ DATA ERROR"
PrintMsg("CWXXI93",   (CWXXI92 +1));         //"NO SD CARD"
PrintMsg("CWXXI94",   (CWXXI93 +1));         //"EJ R/W ERROR"
PrintMsg("CWXXI95",   (CWXXI94 +1));         //"NO EJ RECORDS"
PrintMsg("CWXXI96",   (CWXXI95 +1));         //"EJ NEARLY FULL"
PrintMsg("CWXXI97",   (CWXXI96 +1));         //"EJ IS FULL"
PrintMsg("CWXXI98",   (CWXXI97 +1));         //"NEW EJ"
PrintMsg("CWXXI99",   (CWXXI98 +1));         //"RESET EJ FIRST"
PrintMsg("CWXXI100",   (CWXXI99 +1));         //"EJ NOT MATCHED"

//PrintMsg(("CWXXIMAX    	CWXXI89

//PrintMsg(("SHPKZCUO		CWXXI72

PrintMsg(("DKQXIANG"),(CWXXIMAX+1));		//��Ǯ��
PrintMsg(("YOUGUADAN"),(DKQXIANG+1));	//�йҵ�
PrintMsg(("SHURUQTYAMT"),(YOUGUADAN+1));	//  ������Ʒ��������Ʒ�۸�
PrintMsg("ZHUANRUDAO",(SHURUQTYAMT+1));    //ZHUANRUDAO "ת�뵽"
PrintMsg(("ERRORMSG"),(ZHUANRUDAO+1));	//Error-
PrintMsg(("CURRENCY"),(ERRORMSG+1));	//CUR
PrintMsg(("TOTALMSG"),(CURRENCY+1));	//TOT
PrintMsg(("CHANGE"),(TOTALMSG+1));	//CHG
PrintMsg(("SUBTOTAL"),(CHANGE+1));		//SUB
PrintMsg(("DISCOUNT"),(SUBTOTAL+1));	//Dis
PrintMsg(("PUTOUT"),(DISCOUNT+1));	//PO
PrintMsg(("RECIEVIN"),(PUTOUT+1));		//RA
PrintMsg(("OPENDRAW"),(RECIEVIN+1));	//DRAW
PrintMsg(("CANCEL"),(OPENDRAW+1));	//CANC
PrintMsg(("ADDMODI"),(CANCEL+1));		//ADD
PrintMsg(("TABLENUM"),(ADDMODI+1));		//TABLE
PrintMsg(("SERVICE"),(TABLENUM+1));	//SER
PrintMsg(("CHECKPAID"),(SERVICE+1));		//CPA
PrintMsg(("CHECKCPAID"),(CHECKPAID+1));	//CCP
PrintMsg(("COVERS"),(CHECKCPAID+1));	//COV
PrintMsg(("CORRECT"),(COVERS+1));		//COR
PrintMsg(("REFUND"),(CORRECT+1));		//RET
PrintMsg(("CANCEL1"),(REFUND+1));		//CANCEL 1
PrintMsg(("CANCEL2"),(CANCEL1+1));		//CANCEL 2
PrintMsg(("ZZXZZKU"),(CANCEL2+1));		//���������ֿ�
PrintMsg(("ZZXZTXING"),(ZZXZZKU+1));		//��������ͼ��
PrintMsg(("DOWNLOAD"),(ZZXZTXING+1));	//��
PrintMsg(("UPLOAD"),(DOWNLOAD+1));	//��
PrintMsg(("KAI"),(UPLOAD+1));		//��
PrintMsg(("GUAN"),(KAI+1));		    //��
PrintMsg(("MINCHENF"),(GUAN+1));		//����:
PrintMsg(("BULEIF"),(MINCHENF+1));	//����:
PrintMsg(("GUIZUF"),(BULEIF+1));		//����:
PrintMsg(("HOLD"),(GUIZUF+1));		//HOLD
PrintMsg(("DAYINF"),(HOLD+1));		//��ӡ:
PrintMsg(("XUANXIANGF"),(DAYINF+1));		//ѡ��:
PrintMsg(("LIANJIE"),(XUANXIANGF+1));	//����:
PrintMsg(("SHUILVF"),(LIANJIE+1));		//˰��:
PrintMsg(("WZHBHAOF"),(SHUILVF+1));		//λ�ñ��:
PrintMsg(("JIAGE1"),(WZHBHAOF+1));	//�۸�1:
PrintMsg(("JIAGE2"),(JIAGE1+1));		//�۸�2:
PrintMsg(("JIAGE3"),(JIAGE2+1));		//�۸�3:
PrintMsg(("JIAGE4"),(JIAGE3+1));		//�۸�4:
PrintMsg(("JINJIA"),(JIAGE4+1));		//����:
PrintMsg(("ZHKLVF"),(JINJIA+1));		//�ۿ���(%):
PrintMsg(("ZDZHIF"),(ZHKLVF+1));		//���ֵ:
PrintMsg(("FIXMSG"),(ZDZHIF+1));		//�ۿ���:
PrintMsg(("MAXMSG"),(FIXMSG+1));		//���ֵ:
PrintMsg(("HUILVF"),(MAXMSG+1));		//˰��:
PrintMsg(("MRJIAF"),(HUILVF+1));		//�����:
PrintMsg(("MCHJIAF"),(MRJIAF+1));		//������:
PrintMsg(("ZHUANGTAIF"),(MCHJIAF+1));		//״̬:
PrintMsg(("QIANXIANGF"),(ZHUANGTAIF+1));		//Ǯ��:
PrintMsg(("OTDMSG"),(QIANXIANGF+1));		//OTD
PrintMsg(("CHFDYINF"),(OTDMSG+1));		//������ӡ:

PrintMsg(("POIMSG"),(CHFDYINF+1));		//POI
PrintMsg(("PREMSG"),(POIMSG+1));		//����:
PrintMsg(("QIANZHUIFU"),(PREMSG+1));		//PER
PrintMsg(("LIANJIEF"),(QIANZHUIFU+1));		//����:
PrintMsg(("GNMA"),(LIANJIEF+1));		//���빦����
PrintMsg(("AGNJIAN"),(GNMA+1));		//�����ܼ�:
PrintMsg(("LEIXING"),(AGNJIAN+1));		//����:
PrintMsg(("KSHRQIF"),(LEIXING+1));		//��ʼ����:
PrintMsg(("JSHRQIF"),(KSHRQIF+1));		//��������:
PrintMsg(("KSHSHJIANF"),(JSHRQIF+1));		//��ʼʱ��:
PrintMsg(("JSHSHJIANF"),(KSHSHJIANF+1));		//����ʱ��:
PrintMsg(("XINGQIFF"),(JSHSHJIANF+1));		//����:
PrintMsg(("ZHEKOUF"),(XINGQIFF+1));		//�ۿ�:
PrintMsg(("DBSHLIANGF"),(ZHEKOUF+1));		//�������:
PrintMsg(("DANJIAF"),(DBSHLIANGF+1));		//����:
PrintMsg(("YHJIAF"),(DANJIAF+1));		//�Żݼ�:
PrintMsg(("TXXYIF"),(YHJIAF+1));		//ͨѶЭ��:
PrintMsg(("DHHMAF"),(TXXYIF+1));		//�绰����:
PrintMsg(("MIMAF"),(DHHMAF+1));		//����:
PrintMsg(("PINLV"),(MIMAF+1));		//Ƶ��:
PrintMsg(("ZXJERF"),(PINLV+1));		//��С���:
PrintMsg(("TXKHAOF"),(ZXJERF+1));		//ͨѶ��:
PrintMsg(("JDJER"),(TXKHAOF+1));		//�Ƶ���:
PrintMsg(("TXXHAO"),(JDJER+1));		//ͼ�����:
PrintMsg(("SHIJIANF"),(TXXHAO+1));		//ʱ��:
PrintMsg(("RIQIF"),(SHIJIANF+1));	//����:
                                        //
PrintMsg(("DYJXHAO"),(RIQIF+1));		//PER
PrintMsg(("DZCHXHAO"),(DYJXHAO+1));		//PER

PrintMsg(("EUTRONMSG"),(DZCHXHAO+1));		//���������Ŵ���ͻ�ӭʹ���Ŵ��տ��
PrintMsg(("SHKJSDING"),(EUTRONMSG+1));	//  �տ��������
PrintMsg(("AFSHSUO"),(SHKJSDING+1));	//������ʽ��������
PrintMsg(("XSHFPIAO"),(AFSHSUO+1));		//��ʽ��Ʊ
PrintMsg(("CHFDYJHAO"),(XSHFPIAO+1));	//������ӡ��#
PrintMsg(("PXZHTAI"),(CHFDYJHAO+1));	//*** ��ѵ״̬ ***
PrintMsg(("JIADIAN"),(PXZHTAI+1));		//***** �ӵ� *****
PrintMsg(("FKFZHANG"),(JIADIAN+1));		//*** �ֿ����� ***
PrintMsg(("FZHSHJU"),(FKFZHANG+1));	//*** �����վ� ***
PrintMsg(("GBPLUJGE"),(FZHSHJU+1));		//*** ��Ʒ��� ***
PrintMsg(("ZJIAKUCUN"),(GBPLUJGE+1));	//*** ���Ӽ���� ***
PrintMsg(("JSHAOKUCUN"),(ZJIAKUCUN+1));	//*** ���Ӽ���� ***
PrintMsg(("QUXIAOP"),(JSHAOKUCUN+1));		//***** ȡ�� *****
PrintMsg(("CHXCHSHHUA"),(QUXIAOP+1));		//** �����ʼ�� **
PrintMsg(("SELECT1HZ"),(CHXCHSHHUA+1));  //"��<ѡ��>��<ȷ��>"
PrintMsg(("KPTOTAL"),(SELECT1HZ+1));	//KPTOTAL
PrintMsg(("TITLE"),(KPTOTAL+1));		//Ʒ��      ����     ����     ���
PrintMsg(("TITLEQTYAMT"),(TITLE+1));	    //Ʒ��      ����        ���
PrintMsg(("TITLEAMT"),(TITLEQTYAMT+1));	    //Ʒ��      ����        ���

PrintMsg(("JANUARY"),(TITLEAMT+1));	//һ��
PrintMsg(("FEBRUARY"),(JANUARY+1));		//����
PrintMsg(("MARCH"),(FEBRUARY+1));	//����
PrintMsg(("APRIL"),(MARCH+1));		//����
PrintMsg(("MAY"),(APRIL+1));		//����
PrintMsg(("JUNE"),(MAY+1));		    //����
PrintMsg(("JULY"),(JUNE+1));		//����
PrintMsg(("AUGUST"),(JULY+1));		//����
PrintMsg(("SEPTMBER"),(AUGUST+1));		//����
PrintMsg(("OCTOBER"),(SEPTMBER+1));	//ʮ��
PrintMsg(("NOVEMBER"),(OCTOBER+1));		//ʮһ��
PrintMsg(("DECEMBER"),(NOVEMBER+1));	//ʮ����
PrintMsg(("MONDAY"),(DECEMBER+1));	//����һ
PrintMsg(("TUESDAY"),(MONDAY+1));		//���ڶ�
PrintMsg(("WEDNSDAY"),(TUESDAY+1));		//������
PrintMsg(("THURSDAY"),(WEDNSDAY+1));	//������
PrintMsg(("FRIDAY"),(THURSDAY+1));	//������
PrintMsg(("SATURDAY"),(FRIDAY+1));		//������
PrintMsg(("SUNDAY"),(SATURDAY+1));		//������
PrintMsg(("AQRJIAN"),(SUNDAY+1));		//��ȷ�ϼ�...
PrintMsg(("KPDYZE"),(AQRJIAN+1));		//��ӡ�ܶ�:
PrintMsg(("KPCXTDY"),(KPDYZE+1));		//����ͬ��ӡ
PrintMsg(("KPCBTDY"),(KPCXTDY+1));		//�˲�ͬ��ӡ
PrintMsg(("JZHLJGE"),(KPCBTDY+1));		//��ֹ��۸�
PrintMsg(("DYFGXIAN"),(JZHLJGE+1));		//��ӡ�ָ���
PrintMsg(("DXXSHOU"),(DYFGXIAN+1));		//��������:
PrintMsg(("ZHKXIANG1"),(DXXSHOU+1));		//�ۿ���1:
PrintMsg(("ZHKXIANG2"),(ZHKXIANG1+1));		//�ۿ���2:
PrintMsg(("DKQXIANGF"),(ZHKXIANG2+1));		//��Ǯ��:
PrintMsg(("SHRJE"),(DKQXIANGF+1));		//������:
PrintMsg(("JZHSHRU"),(SHRJE+1));		//��ֹ����:
PrintMsg(("SHRHMA"),(JZHSHRU+1));		//�������:
PrintMsg(("ZHLXFEI"),(SHRHMA+1));		//����ΪС��
PrintMsg(("DKQXIANGP"),(ZHLXFEI+1));		//��Ǯ��:
PrintMsg(("FKFSHJIAN"),(DKQXIANGP+1));		//���ʽ��
PrintMsg(("CRJE"),(FKFSHJIAN+1));		//������:
PrintMsg(("RJCHJIN"),(CRJE+1));		//���/����
#if defined(CASE_INDIA)
PrintMsg(("PORANUMBER"),(RJCHJIN+1));		//���/����
PrintMsg(("DYZHKE"),(PORANUMBER+1));		//��ӡ�ۿ۶�
#else
PrintMsg(("DYZHKE"),(RJCHJIN+1));		//��ӡ�ۿ۶�
#endif
PrintMsg(("SHYZHK1"),(DYZHKE+1));		//ʹ���ۿ�1:
PrintMsg(("SHYZHK2"),(SHYZHK1+1));		//ʹ���ۿ�2:
PrintMsg(("MCHJZHLIN"),(SHYZHK2+1));		//����������
PrintMsg(("WXSHDIAN"),(MCHJZHLIN+1));		//��С����:
PrintMsg(("DKQXIANGD"),(WXSHDIAN+1));		//��Ǯ��:
PrintMsg(("YYZZHI"),(DKQXIANGD+1));		//Ӫҵ/��ֵ:
PrintMsg(("DYSHLXIANG"),(YYZZHI+1));		//��ӡ˰����
PrintMsg(("DYLSHXXI"),(DYSHLXIANG+1));		//��ӡ0˰��
PrintMsg(("WGSTSHUI"),(DYLSHXXI+1));		//ΪGST��˰
PrintMsg(("DYSHE"),(WGSTSHUI+1));		//��ӡ˰��:
PrintMsg(("QXXZHI"),(DYSHE+1));		//ȡ������:
PrintMsg(("GGXZHI"),(QXXZHI+1));		//��������:
PrintMsg(("QXJYIXZHI"),(GGXZHI+1));		//ȡ������:
PrintMsg(("THXZHI"),(QXJYIXZHI+1));		//�˻�����:
PrintMsg(("BFBZHKXZHI"),(THXZHI+1));		//%�ۿ�����:
PrintMsg(("BFBJCHXZHI"),(BFBZHKXZHI+1));		//%�ӳ�����:
PrintMsg(("JJJEXZHI"),(BFBJCHXZHI+1));		//+-�������
PrintMsg(("PSHMSHI"),(JJJEXZHI+1));		//��ѵģʽ:
PrintMsg(("mPRNINDEX"),(PSHMSHI+1));         //Ccr "ȡ�˺�:",
                                            //
PrintMsg(("ECRIPADDRESS"),(mPRNINDEX+1));       //"IP Address:"
PrintMsg(("ECRNETID"),(ECRIPADDRESS+1));   //"�տ��ID��:"   //

PrintMsg(("SHRLJHAO"),(ECRNETID+1));		//<��¼��>  �¼�¼<ȷ��>  ��ǰ��¼
PrintMsg(("SHRDPDMA"),(SHRLJHAO+1));		//<����>��ɾ����Ʒ<ȷ��>  ��ǰ��Ʒ
PrintMsg(("TCHBJI"),(SHRDPDMA+1));		//<�˳�>      �˳�
PrintMsg(("BJDQJLU"),(TCHBJI    +1));		//<ȷ��>      ����
PrintMsg(("ANXZJIAN"),(BJDQJLU+1));		//ѡ���ӡ����
PrintMsg(("XFJE"),(ANXZJIAN+1));		//���ѽ��
PrintMsg(("AJGNDYI"),(XFJE    +1));		//����     //��
PrintMsg(("JLSHYONG"),(AJGNDYI+1));		//ֻ���ھ�����
PrintMsg(("YYSHYONG"),(JLSHYONG+1));		//����Ӫҵ����
PrintMsg(("DYWZI"),(YYSHYONG+1));		//��ӡ����
PrintMsg(("BAOLIU"),(DYWZI    +1));		//����
PrintMsg(("SHGNENG"),(BAOLIU    +1));		//�ļ��������
PrintMsg(("ZHZBHAO"),(SHGNENG+1));		//����
PrintMsg(("MODEMLINK"),(ZHZBHAO+1));		//MODEM ����!
PrintMsg(("DAIMA"),(MODEMLINK+1));		//����:
PrintMsg(("PZHEKOU"),(DAIMA+1));		//%�ۿ�
PrintMsg(("PJIACHEN"),(PZHEKOU+1));		//%�ӳ�
PrintMsg(("SHJHAOF"),(PJIACHEN+1));		//�վݺ�:
PrintMsg(("WENJSHU"),(SHJHAOF+1));		//�ļ���
PrintMsg(("WENJKJ"),(WENJSHU+1));		//�ļ��ռ�
PrintMsg(("TJWENJ"),(WENJKJ+1));		//ͳ���ļ�
PrintMsg(("JISHUI"),(TJWENJ+1));		//��˰
PrintMsg(("LIUSKJ"),(JISHUI+1));		//��ˮ�ռ�
PrintMsg(("RAMKB"),(LIUSKJ+1));		//RAM(KB)
PrintMsg(("CONIFOT0"),(RAMKB+1));		//�ļ���      ��¼��      �ռ��С
PrintMsg(("CONIFOT1"),(CONIFOT0+1));		//��������    ͨ�����   ͨ��Э��
PrintMsg(("DBKHSHU"),(CONIFOT1+1));		//����������:
PrintMsg(("MYEHSHU"),(DBKHSHU+1));		//ÿҳ����:
PrintMsg(("DAYXXI"),(MYEHSHU+1));		//��ӡ��Ϣ:
PrintMsg(("DEZPJU"),(DAYXXI+1));		//�ڶ���Ʊ��:
PrintMsg(("ZUOBJU"),(DEZPJU+1));		//��߾�:
PrintMsg(("PDJIXING"),(ZUOBJU+1));		//Ʊ�����:
PrintMsg(("DYJGUAN"),(PDJIXING+1));		//��ӡ����
PrintMsg(("DYJKAI"),(DYJGUAN+1));		//��ӡ����
PrintMsg(("ICSZMIMA"),(DYJKAI+1));		//����:
PrintMsg(("ICSZMIMAF"),(ICSZMIMA+1));		//����ȷ��:
PrintMsg(("POSDAIMA"),(ICSZMIMAF+1));		//POS����:
PrintMsg(("POSDIAMAF"),(POSDAIMA+1));		//����ȷ��:
PrintMsg(("BCDMA"),(POSDIAMAF+1));		//�����ѱ���
PrintMsg(("DMACUO"),(BCDMA+1));		//����� ��
PrintMsg(("ICCA"),(DMACUO+1));		//����IC��:
PrintMsg(("ZHEKOUCA"),(ICCA+1));		//�ۿۿ�:
PrintMsg(("XIANJINKA"),(ZHEKOUCA+1));		//�ֽ�:
PrintMsg(("SHEZHANGKA"),(XIANJINKA+1));		//���ʿ�:
PrintMsg(("DAYINICKA"),(SHEZHANGKA+1));		//��ӡIC��
PrintMsg(("ZDZHEKOU"),(DAYINICKA+1));		//�Զ��ۿ�:
PrintMsg(("XFJIFEN"),(ZDZHEKOU+1));		//���ѻ���:
PrintMsg(("XJJIAN"),(XFJIFEN+1));		//���ֽ��:
PrintMsg(("QYXYQI"),(XJJIAN + 1));		//������Ч��
PrintMsg(("GUASHIIC"),(QYXYQI + 1));		//��ʧ��
PrintMsg(("KAHAO"),(GUASHIIC+1));		//����:
PrintMsg(("KLXING"),(KAHAO+1));		//������:
PrintMsg(("KNJE"),(KLXING+1));		//���:
PrintMsg(("KYJIN"),(KNJE+1));		//��Ѻ��:
PrintMsg(("XFZE"),(KYJIN+1));		//����:
PrintMsg(("CHZHZE"),(XFZE+1));		//��ֵ�ܶ�:
PrintMsg(("SHYCSHU"),(CHZHZE+1));		//ʹ�ô���:
PrintMsg(("JGLBIE"),(SHYCSHU+1));		//�۸񼶱�:
PrintMsg(("PINMA"),(JGLBIE+1));		//PIN��:
PrintMsg(("BHJBIE"),(PINMA+1));		//��������:
PrintMsg(("ZDJZHANG"),(BHJBIE+1));		//�Զ�����:
PrintMsg(("ZHKRQI"),(ZDJZHANG+1));		//�ƿ�����:
PrintMsg(("KYXQI"),(ZHKRQI+1));		//����Ч��:
PrintMsg(("KHMCHEN"),(KYXQI+1));		//�ͻ�:
PrintMsg(("CHSHHICKA"),(KHMCHEN+1));		//��ʼ��IC
PrintMsg(("ICKCHZHI"),(CHSHHICKA+1));		//IC����ֵ
PrintMsg(("QCHICKA"),(ICKCHZHI+1));		//���IC��
PrintMsg(("CHZHTKUAN"),(QCHICKA+1));		//��ֵ/�˿�?
PrintMsg(("JDSDIAN"),(CHZHTKUAN+1));		//����/�͵�?
PrintMsg(("QRCHZHI"),(JDSDIAN+1));		//ȷ�ϳ�ֵ?
PrintMsg(("QRTKUAN"),(QRCHZHI+1));		//ȷ���˿�?
PrintMsg(("QRSDIAN"),(QRTKUAN+1));		//ȷ���͵�?
PrintMsg(("DJQREN"),(QRSDIAN+1));		//�ҽ�ȷ��?
PrintMsg(("XFJDDJIANG"),(DJQREN+1));		//�Ƶ�ҽ�
PrintMsg(("ICKTKUAN"),(XFJDDJIANG+1));		//IC���˿�
PrintMsg(("ICKDJDIANG"),(ICKTKUAN+1));		//IC���ҽ�����
PrintMsg(("ICKSDIAN"),(ICKDJDIANG+1));		//IC���͵���
PrintMsg(("QDDAI"),(ICKSDIAN+1));		//��ȴ�......
PrintMsg(("KNYJE"),(QDDAI+1));		//�����˿�...
PrintMsg(("TMHYHAO"),(KNYJE+1));		//��Ա��
PrintMsg(("BARREPORT"),(TMHYHAO+1));		//         �� Ա �� �� ��
PrintMsg(("CHXKJI"),(BARREPORT+1));		//Ҫ�����µ�IP,�����¿���.
PrintMsg(("ZQBBIAO"),(CHXKJI+1));		//ȷ���屨��?
PrintMsg(("WAITICARD"),(ZQBBIAO+1));		//�ȴ�IC��....
PrintMsg(("BGDYIN"),(WAITICARD+1));		//���ߴ�ӡ

//ccr2015-06-15>>>>>>>>>>>>>>>>>>>>>
PrintMsg(("CLEARIC"),(BGDYIN+1));                //"�忨",
PrintMsg(("REFUNDtoIC"),(CLEARIC+1));               //"�˿�",
PrintMsg(("PAYMENTbyIC"),(REFUNDtoIC+1));            //"����",
PrintMsg(("CHARGEtoIC"),(PAYMENTbyIC+1));           //"��ֵ",
PrintMsg(("INITIALIC"),(CHARGEtoIC+1));            //"��ʼ��",
PrintMsg(("TAKECAHSfrIC"),(INITIALIC+1));             //"ȡ��"
PrintMsg(("ADDVIPPOINTS"),((TAKECAHSfrIC+1)));//ADDVIPPOINTS "��������"
PrintMsg(("DECVIPPOINTS"),((ADDVIPPOINTS+1)));//DECVIPPOINTS "���ֶҽ�"
PrintMsg(("VIPPOINTS"),((DECVIPPOINTS+1)));//            "VIP POINTS"  //VIPPOINTS
//ccr2015-06-15<<<<<<<<<<<<<<<<<<<<<
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
PrintMsg("MsgEJ_X_STORE ",     (VIPPOINTS+1));//EJ�д洢X����
PrintMsg("MsgEJ_Z_STORE ", (MsgEJ_X_STORE+1));//EJ�д洢Z����
PrintMsg("MsgEJ_TR_STORE", (MsgEJ_Z_STORE+1));//EJ�д洢TR����
#endif

//ccr2016-02-22>>>>>>>>>>>>>>>>>>>>>
//PrintMsg(("MENUOFXMODE"),(TAKECAHSfrIC  +1));
PrintMsg(("MENUXREPORT"),(MsgEJ_TR_STORE  +1));  // ��ӡX����
#if(CASE_USBDISK)
PrintMsg(("MENUXEXPORT"),(MENUXREPORT   +1));  //������������
PrintMsg(("MENUQUICKVIEW"),(MENUXEXPORT   +1));  //Quick View
#else
PrintMsg(("MENUQUICKVIEW"),(MENUXREPORT   +1));  //Quick View
#endif
PrintMsg(("MENUXEJFUNC"),(MENUQUICKVIEW +1));  //LOG. OPERATION
#if defined(CASE_GPRS)
PrintMsg(("MENUSENDNEWLOG"),(MENUXEJFUNC +1));  //��������ˮ����
PrintMsg(("MENUXPASSWORD"),(MENUSENDNEWLOG   +1));  //����X����
#else
PrintMsg(("MENUXPASSWORD"),(MENUXEJFUNC   +1));  //����X����
#endif
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
PrintMsg(("MENUXEJOURNAL"),(MENUXPASSWORD   +1));  //��ӡEJ����
#endif
//PrintMsg(("MENUXITEMMAX"),(MENUXPASSWORD-MENUXREPORT+1));
//.................................
PrintMsg(("MENUZREPORT"),(MENUXEJOURNAL +1));  //��ӡZ����
#if (CASE_USBDISK)
PrintMsg(("MENUZEXPORT"),(MENUZREPORT   +1));  //������������
PrintMsg(("MENUCLEARLOG"),(MENUZEXPORT   +1));  //���E.J
#else
PrintMsg(("MENUCLEARLOG"),(MENUZREPORT   +1));  //���E.J
#endif
PrintMsg(("MENUZGRAND"),(MENUCLEARLOG   +1));  //�Ƿ����Grand TOTAL
PrintMsg(("MENUZPASSWORD"),(MENUZGRAND    +1));  //����Z����
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
PrintMsg(("MENUXEJOURNAL"),(MENUZPASSWORD   +1));  //��EJ����
#endif

//PrintMsg(("MENUZITEMMAX"),(MENUZPASSWORD-MENUZREPORT+1));
//...................................

//ccr2016-02-22<<<<<<<<<<<<<<<<<<<<<
//PrintMsg(("XZTITLE"),(MENUZPASSWORD  +1));
PrintMsg(("XZTITLE1"),		XZTITLE);		//�����ձ���
PrintMsg(("XZTITLE2"),(XZTITLE1+1));      //�����±���
PrintMsg(("XZTITLE3"),(XZTITLE2+1));      //��Ʒ����
PrintMsg(("XZTITLE4"),(XZTITLE3+1));      //���ʱ���
PrintMsg(("XZTITLE5"),(XZTITLE4+1));      //ʱ�α���
PrintMsg(("XZTITLE6"),(XZTITLE5+1));      //�տ�Ա�ձ���
PrintMsg(("XZTITLE7"),(XZTITLE6+1));      //�տ�Ա�±���
PrintMsg(("XZTITLE8"),(XZTITLE7+1));      //ȫ�տ�Ա�ձ���
PrintMsg(("XZTITLE9"),(XZTITLE8+1));      //ȫ�տ�Ա�±���
#if (salNumber)
PrintMsg(("XZTITLE10"),(XZTITLE9+1));      //ӪҵԱ�ձ���
PrintMsg(("XZTITLE11"),(XZTITLE10+1));      //ӪҵԱ�±���
PrintMsg(("XZTITLE12"),(XZTITLE11+1));      //ȫӪҵԱ�ձ���
PrintMsg(("XZTITLE13"),(XZTITLE12+1));      //ȫӪҵԱ�±���
#else
//PrintMsg(("XZTITLE13"),(XZTITLE9));      //ȫӪҵԱ�±���
#endif
#if (BARCUSTOMER==1)
PrintMsg(("XZTITLE14"),(XZTITLE13+1));      //�����Ա����
//PrintMsg(("XZITEMSMAX"),(XZTITLE14-XZTITLE1+1));
#else
//PrintMsg(("XZITEMSMAX"),(XZTITLE13-XZTITLE1+1));
#endif
//....................................
#if (CASE_EPOS)
PrintMsg(("ePOSTAC"),(XZTITLE1+XZNUM)  //ePOS��֤��:
PrintMsg(("WAITEPOS"),(ePOSTAC+1));        //�ȴ���ͨ��
PrintMsg(("ePOSCARNO"),(WAITEPOS+1));       //��ͨ����:
PrintMsg(("eCARREMAIN"),(ePOSCARNO+1));      //��ͨ�����:
#else
//PrintMsg(("eCARREMAIN"),(XZTITLE1+XZNUM-1)     //��������     ��������       ���
#endif


#if (CASE_USBDISK)
//ccr090715>>> USB applications >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
PrintMsg(("usbDAOCHU"),(eCARREMAIN+1));		//Ccr�����տ���ļ�//
PrintMsg(("usbDAORU"),(usbDAOCHU+1));       //Ccr�����տ���ļ� //
PrintMsg(("usbFLOW"),(usbDAORU+1));       //Ccr����������ˮ //

//PrintMsg(("usbMAINITEMS"),(usbFLOW-usbDAOCHU+1));
//;;;;;;;;;;;;;;;;;;;;

PrintMsg(("usbALL"),(usbFLOW+1));         //Ccrȫ���ļ�  //
PrintMsg(("usbBULEI"),(usbALL+1));          //Ccr"����",
PrintMsg(("usbDANPIN"),(usbBULEI+1));         //Ccr"��Ʒ",
PrintMsg(("usbSHUILV"),(usbDANPIN+1));        //Ccr"˰��",
PrintMsg(("usbPIAOTOU"),(usbSHUILV+1));         //Ccr"Ʊͷ",
PrintMsg(("usbZHEKOU"),(usbPIAOTOU+1));       //Ccr"�ۿ�",
#if (salNumber)
PrintMsg(("usbYYYUAN"),(usbZHEKOU+1));        //Ccr"ӪҵԱ",
PrintMsg(("usbSTSHZHI"),(usbYYYUAN+1));         //Ccr"ϵͳ����",
#else
PrintMsg(("usbSTSHZHI"),(usbZHEKOU+1));         //Ccr"ϵͳ����",
#endif
PrintMsg(("usbTXKOU1"),(usbSTSHZHI+1));       //Ccr"ͨѶ��1",
PrintMsg(("usbTUXIN"),(usbTXKOU1+1));       //Ccr"ͼ�δ�ӡ",
PrintMsg(("usbGUIZU"),(usbTUXIN+1));        //Ccr"����",
PrintMsg(("usbICKA"),(usbGUIZU+1));       //Ccr"IC��",
PrintMsg(("usbZHJIANG"),(usbICKA+1));           //Ccr"�н�����",
PrintMsg(("usbCANYINGN"),(usbZHJIANG+1));         //Ccr"��������",
PrintMsg(("usbSHKYUAN"),(usbCANYINGN+1));        //Ccr"�տ�Ա",
PrintMsg(("usbSHUOMIN"),(usbSHKYUAN+1));        //Ccr"˵������",
PrintMsg(("usbZHUOTAI"),(usbSHUOMIN+1));        //Ccr"��̨",
PrintMsg(("usbSHIDUANG"),(usbZHUOTAI+1));         //Ccr"ʱ��",
PrintMsg(("usbJIANPAN"),(usbSHIDUANG+1));       //Ccr"����",
PrintMsg(("usbTSHCHJIA"),(usbJIANPAN+1));         //Ccr"�������",
PrintMsg(("usbCHJRJIN"),(usbTSHCHJIA+1));       //Ccr"�������",
PrintMsg(("usbPIAOWEI"),(usbCHJRJIN+1));        //Ccr"Ʊβ",
PrintMsg(("usbPIAOJTOU"),(usbPIAOWEI+1));  //Lyq"Ʊ��Ʊͷ",
PrintMsg(("usbICCAGUASHI"),(usbPIAOJTOU+1));    //ccr"IC����ʧ",

//PrintMsg(("usbFILEITEMS"),(usbICCAGUASHI-usbALL+1));
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PrintMsg(("usbFLOWNEW"),(usbICCAGUASHI+1));   // ����������
PrintMsg(("usbFLOWALL"),(usbFLOWNEW+1));      // ����ȫ������
PrintMsg(("usbFLOWALLDEL"),(usbFLOWALL+1));      // ����ȫ�����ݺ���� //

//PrintMsg(("usbFLOWITEMS"),(usbFLOWALLDEL-usbFLOWNEW+1));
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

PrintMsg(("HDEPTREPORT"),(usbFLOWALLDEL+1));   //��������     ��������       ���
#else
PrintMsg(("HDEPTREPORT"),(eCARREMAIN+1));  //��������     ��������       ���
#endif

PrintMsg(("HPLUREPORT"),(HDEPTREPORT+1));    //��Ʒ����     ��������       ���
PrintMsg(("PRESSANYKEY"),(HPLUREPORT+1));     //������� MESS_PRESSKEY,         //

PrintMsg(("PRICEBARCODE"),(PRESSANYKEY+1));     //ccr2016-01-22 ��������

PrintMsg(("HEADCENTER"),(PRICEBARCODE+1));    //SysFlags32,  "Ʊͷ���д�ӡ"
PrintMsg(("TRAILCENTER"),(HEADCENTER  +1));    //SysFlags33, "Ʊβ���д�ӡ"
PrintMsg(("HEADDBLHIGH"),(TRAILCENTER +1));    //SysFlags34, "Ʊͷ���ߴ�ӡ"
PrintMsg(("TRAILDBLHIGH"),(HEADDBLHIGH +1));    //SysFlags35, "Ʊβ���ߴ�ӡ"

//ccr2016-02-17>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�������ܶ���...................
PrintMsg(("MsgMGADDINV"),(TRAILDBLHIGH +1));//   "���ӵ�Ʒ���"
PrintMsg(("MsgMGDECINV"),(MsgMGADDINV  +1));//   "���ٵ�Ʒ���"
PrintMsg(("MsgMGSETPRICE"),(MsgMGDECINV  +1));//   "�޸ĵ�Ʒ�۸�"
PrintMsg(("MsgMGCLEARIC"),(MsgMGSETPRICE+1));//   "��Ա�˿�"
PrintMsg(("MsgMGINITIC"),(MsgMGCLEARIC +1));//   "��ʼ����Ա��"
PrintMsg(("MsgMGCHARGE"),(MsgMGINITIC  +1));//   "��Ա����ֵ"
PrintMsg(("MsgMGADDPOINT"),(MsgMGCHARGE  +1));//   "��Ա���ͻ���"
PrintMsg(("MsgMGPRINTSTOCK"),(MsgMGADDPOINT+1));//   "��ӡ��Ʒ���"
PrintMsg(("MsgMGPASSWORD"),(MsgMGPRINTSTOCK+1));//    "���þ�������"
PrintMsg(("MsgMGCLOSEPRN"),(MsgMGPASSWORD+1));//    "�رմ�ӡ"
#if (!defined(DD_LOCK) || !defined(TR))
PrintMsg(("MsgMGTRAINING"),(MsgMGCLOSEPRN+1));//    "��ѵģʽ"
#endif
PrintMsg(("MsgMGGOTOMG"),(MsgMGTRAINING+1));//    "����"
//PrintMsg(("MsgMGMMAX"),(MsgMGGOTOMG-MsgMGADDINV+1));
//ccr2016-03-09>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
PrintMsg(("MsgALLLOG"),(MsgMGGOTOMG  +1));//MESSALLLOG       "ȫ���վ�"
PrintMsg(("MsgDATERANGE"),(MsgALLLOG  +1));//MESSDATERANGE   "���ڷ�Χ"
PrintMsg(("MsgMESSVIPLOG"),(MsgDATERANGE  +1));               //MESSVIPLOG        "��Ա���Ѽ�¼"
PrintMsg(("MsgPRNCASH"),(MsgMESSVIPLOG  +1));      //"��ӡ�����¼"
PrintMsg(("MsgPRNDEPART"),(MsgPRNCASH    +1));    //"��ӡ�����¼"
PrintMsg(("MsgPRNPLU"),(MsgPRNDEPART  +1));    //"��ӡ��Ʒ��¼"
PrintMsg(("MsgPRNDISCOUNT"),(MsgPRNPLU     +1));    //"��ӡ�ۿۼӳ�"
PrintMsg(("MsgPRNRAPO"),(MsgPRNDISCOUNT+1));    //"��ӡ�����"
PrintMsg(("MsgPRNCORRECT"),(MsgPRNRAPO    +1));    //"��ӡ��������"
PrintMsg(("MsgPRNCANCEL"),(MsgPRNCORRECT +1));  //"��ӡ����ȡ��"
PrintMsg(("MsgPRNNOSALE"),(MsgPRNCANCEL +1));    //"��ӡ������"
//PrintMsg(("MsgPRNLOGMAX"),(MsgPRNNOSALE-MsgALLLOG+1));

PrintMsg(("MsgALLCASH"),(MsgPRNNOSALE  +1));    //"ȫ�����ʽ"
PrintMsg(("MsgSELCASH"),(MsgALLCASH	+1));    //"ѡ�񸶿ʽ"
                                               //
PrintMsg(("MsgALLDEPT"),(MsgSELCASH	+1));    //"��ӡȫ������"
PrintMsg(("MsgSELDEPT"),(MsgALLDEPT	+1));    //"ѡ��һ������"
                                               //
PrintMsg(("MsgALLPLU"),(MsgSELDEPT	+1));    //"��ӡȫ����Ʒ"
PrintMsg(("MsgSELPLU"),(MsgALLPLU	    +1));    //"ѡ��һ����Ʒ"

PrintMsg(("MsgPLUNUMBER"),(MsgSELPLU	+1));       // "��¼��:"
PrintMsg(("MsgPLURANDOMSIZE"),(MsgPLUNUMBER	+1));   // "����λ��:"
PrintMsg(("MsgPLUNAMESIZE"),(MsgPLURANDOMSIZE +1)); // "���Ƴ���:"
PrintMsg(("MsgPLUPRICESIZE"),(MsgPLUNAMESIZE   +1)); // "�۸�λ��:"
PrintMsg(("MsgPLUPRICELEVEL"),(MsgPLUPRICESIZE  +1)); // "��Ա�ۼ���:"
PrintMsg(("MsgPLUCOSTSIZE"),(MsgPLUPRICELEVEL +1)); // "����λ��:"
PrintMsg(("MsgPLUINVENTSIZE"),(MsgPLUCOSTSIZE   +1)); // "���λ��:"
PrintMsg(("MsgPLUREPQTYSIZE"),(MsgPLUINVENTSIZE +1)); // "ͳ������λ��:"
PrintMsg(("MsgPLUREPAMTSIZE"),(MsgPLUREPQTYSIZE +1)); // "ͳ�ƽ��λ��:"
PrintMsg(("MsgPLUREPDISCSIZE"),(MsgPLUREPAMTSIZE +1)); // "ͳ���ۿ�λ��:"
PrintMsg(("MsgPLUREPCOSTSIZE"),(MsgPLUREPDISCSIZE+1)); // "ͳ�ƽ���λ��:"
//ccr2016-03-09<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//.......................................................
PrintMsg(("MsgDATETYPE"),(MsgPLUREPCOSTSIZE+1));  //"FORMAT "
PrintMsg(("MsgDDMMYYYY"),(MsgDATETYPE+1));    //"DDMMYYYY"
PrintMsg(("MsgMMDDYYYY"),(MsgDDMMYYYY+1));    //"MMDDYYYY"
PrintMsg(("MsgYYYYMMDD"),(MsgMMDDYYYY+1));    //"YYYYMMDD"

//ccr2016-04-05>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
PrintMsg(("MsgPOINTTYPE1"),(MsgYYYYMMDD+1));//"1.000,00"  //��λС��
PrintMsg(("MsgPOINTTYPE2"),(MsgPOINTTYPE1+1));// "1,000.00"  //��λС��
PrintMsg(("MsgPOINTTYPE3"),(MsgPOINTTYPE2+1));// "1.000"     //��С��
PrintMsg(("MsgPOINTTYPE4"),(MsgPOINTTYPE3+1));// "1,000"     //��С��
#if !defined(CASE_FORHANZI)
PrintMsg(("MsgPOINTTYPE5"),(MsgPOINTTYPE4+1));// "1.000,000"  //��λС��
PrintMsg(("MsgPOINTTYPE6"),(MsgPOINTTYPE5+1));// "1,000.000"  //��λС��
//PrintMsg(("MsgPOINTTYPE7"),(MsgPOINTTYPE6+1));// "1.000,0"  //һλС��
//PrintMsg(("MsgPOINTTYPE8"),(MsgPOINTTYPE7+1));// "1,000.0"  //һλС��
#endif
//PrintMsg(("MsgPOINTMAX"),(MsgPOINTTYPE4-MsgPOINTTYPE1+1));
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
PrintMsg("MsgEJMESSAGES", (MsgPOINTTYPE6+1)); //"EJ�洢��Ϣ"    //
PrintMsg("MsgEJALLEJ",   (MsgEJMESSAGES+1));  //"��ӡȫ��EJ"
PrintMsg("MsgEJDATERANGE",   (MsgEJALLEJ    +1));// "���ڷ�ΧEJ"
PrintMsg("MsgEJRECEIPT",   (MsgEJDATERANGE+1));// "��ӡ�վ�EJ"
PrintMsg("MsgEJXREPORT",   (MsgEJRECEIPT  +1));// "��ӡX-EJ"
PrintMsg("MsgEJZREPORT",   (MsgEJXREPORT  +1));// "��ӡZ-EJ"
PrintMsg("MsgEJCLERK",   (MsgEJZREPORT  +1));//"��ӡ�տ�ԱEJ"    
#endif

#if defined(CASE_QRCODE)
PrintMsg(("MsgQRCODE"),(MsgEJCLERK+1));//
#endif

PrintMsg(("GPRSSERVERIP"),(MsgQRCODE+1));//
PrintMsg(("GPRSSERVERPORT"),(GPRSSERVERIP+1));

#if (!defined(CASE_GPRS))		// ADD BY LQW 090827
PrintMsg(("HZMESSMAX"),(GPRSSERVERPORT+1));
#else
//ccr2014-11-11  NEWSETUP Step-4 �Ӳ˵���Ŀ��Ϣ���>>>>>>>>>>>>>>
PrintMsg(("GPRSAPNNAME"),(GPRSSERVERPORT+1));
PrintMsg(("GPRSUSERNAME"),(GPRSAPNNAME+1));
PrintMsg(("GPRSPASSWORD"),(GPRSUSERNAME+1));

PrintMsg(("gprsSETMODE"),(GPRSPASSWORD+1));
PrintMsg(("gprsSendECRLogAll"),(gprsSETMODE+1));

PrintMsg(("gprsDownloadPLU"),(gprsSendECRLogAll+1)); //"���ص�Ʒ�ļ�"
PrintMsg(("gprsDownloadDEPT"),(gprsDownloadPLU+1));     //"���ز����ļ�"
PrintMsg(("gprsDownloadCLERK"),(gprsDownloadDEPT+1)); //"�����տ�Ա"
PrintMsg(("gprsDownloadHEAD"),(gprsDownloadCLERK+1)); //"����Ʊͷ"
PrintMsg(("gprsDownloadTRAIL"),(gprsDownloadHEAD+1)); //"����Ʊβ"
PrintMsg(("gprsDownloadALL"),(gprsDownloadTRAIL+1)); //"����ȫ������"
PrintMsg(("gprsRestart"),(gprsDownloadALL+1)); //"����ȫ������"
PrintMsg(("gprsSENDMESS"),(gprsRestart+1));
//PrintMsg(("gprsMAINITEMS"),(8));                 //�Ӳ˵���Ŀ��

PrintMsg(("HZMESSMAX"),(gprsSENDMESS+1)); //<<<<<<<<
// MSg[]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#endif
}
#endif


