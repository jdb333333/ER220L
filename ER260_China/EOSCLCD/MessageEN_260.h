#ifndef MESSAGEH_EN
#define MESSAGEH_EN


#define Modifier1             "MODIFIER"        //"˵��    "
#define ClerkRec1             "CLERK"        //"�տ�Ա  "
#define GroupRec1             "GROUP"        //"����    "
#define DeptRec1              "DEPT"        //"����    "
#define PLURec1               "PLU"        //"��Ʒ    "
#define SalesPersonRec1       "SALPER"        //"ӪҵԱ  "
#define OffRec1               "OFFER"        //"�������"

#define XZReportList1     "DAILY REPORT"        //"�����ձ���",
#define XZReportList2     "PERIOD REPORT"        //"�����±���",
#define XZReportList3     "PERIOD PLU"        //"��Ʒ����",
#define XZReportList4     "PERIOD TABLES"        //"���ʱ���",
#define XZReportList5     "TIME ZONE"        //"ʱ�α���",
#define XZReportList6     "CLERK DAILY"        //"�տ�Ա�ձ���",
#define XZReportList7     "CLERK PERIOD"        //"�տ�Ա�±���",
#define XZReportList8     "CLERK DAILY-*"        //"ȫ�տ�Ա�ձ���",
#define XZReportList9     "CLER.PERIOD-*"        //"ȫ�տ�Ա�±���",
#if (salNumber)
#define XZReportList10    "SALPR.DAILY"        //"ӪҵԱ�ձ���"
#define XZReportList11    "SALPR. PERIOD"        //"ӪҵԱ�±���"
#define XZReportList12    "SALPR.DAILY-*"        //"ȫӪҵԱ�ձ���",
#define XZReportList13    "SALP.PERIOD-*"        //"ȫӪҵԱ�±���",
#endif
#if (BARCUSTOMER==1)
#define XZReportList14    "MEMBERSHIP"        //"�����Ա����",
#endif

#define PortType1               "COMPUTER"        //"  ����",
#define PortType2               "SCANNER"        //"����ǹ",
#define PortType3               "SCALE"        //"���ӳ�",
#define PortType4               "KP-PORT"        //"��  ��",
#define PortType5               "SP-PORT"        //'Ʊ��'��20040322
#define PortEXTPRN      "EP-PORT"//ccr2016-12-14 ExtPrinter����
#define PortType6               "CHIP CARD"        //-------090421 BY ZY//"��Ƶ��"
#define PortType7               "E-CARD"        //"Eͨ��"

#define KClose                  "   OFF"        //"   �� ",

#define SysFlags0		        "SHOP#"	// "���̱��"
#define SysFlags1               "ECR#"        //"�տ����:"
#define SysFlags2               "ROUNDING"        //"���뷽ʽ:"
#define SysFlags3               "FREE PRICE"        //"��Ʒ���:"
#define SysFlags4               "BUZZER"        //"������:"
#define SysFlags5               "OPER.COMP"        //"ǿ���տ�Ա"
#define SysFlags6               "OPER.SHFT"        //"�ı��տ�Ա"
#define CLERKPASS               "OPER.PWD"        //"�տ�Ա����"
#define SysFlags8               "PRT SALP."        //"��ӡӪҵԱ"
#define SysFlags9               "PRT OPER."        //"��ӡ�տ�Ա"
#define SysFlags10              "PRT R-NO"        //"��ӡ�վݺ�"
#define SysFlags11              "HEAVY PRN"        //"��Ũ�ȴ�ӡ"
#define SysFlags12              "SALP.COMP"        //"ǿ��ӪҵԱ"
#define SysFlags13              "PRT PLU#"        //"��ӡ����:"
#define SysFlags14              "SUB.MUST"        //"��С�Ƽ�:"
#define SysFlags15              "PRN.ITEMS"        //"��ӡ��Ŀ��"
#define SysFlags16              "STUB"        //"��ӡСƱ:"
#define SysFlags17              "STUB HEAD"        //"СƱƱͷ:"
#define SysFlags18              "SHIFT LOCK"        //"����SHIFT:"
#define SysFlags19              "IDLE TIME"        //"��ʾʱ��:"
#define SysFlags20              "RECE. COPY"        //"�����վ�:"
#define SysFlags21              "SCALE CODE"        //"��������:"
#define SysFlags22              "OPR. LOG" //-----090421 BY ZY//"������־"
#define SysFlags23              "PRINT PB"        //"��̨��ӡ:"
#define SysFlags24              "PRN STOCK"        //"��ӡ���"
#define SysFlags25              "PRN ON/OFF"        //"��ӡ����:"
#define SysFlags26              "CHECK REQUIRED"        //"���뿪̨:"
#define SysFlags27              "KEEP R-NO#"        //"�����վݺ�"
#define SysFlags28              "KP COPY"        //"���Ƴ���:"
#define SysFlags29              "RESET R-NO"        //"�վݺŸ�λ"
#define SysFlags30              "DOUBLE PRT"    //-----090421 BY ZY//"���ߴ�ӡ"
#define SysFlags31              "CONTRAST"   //-----090421 BY ZY//"�Աȶ�:"
#define SysFlags32              "->HEAD<-"  // "Ʊͷ���д�ӡ"
#define SysFlags33              "->TRAIL<-"  // "Ʊβ���д�ӡ"
#define SysFlags34              "DBLH HEAD"  // "Ʊͷ���ߴ�ӡ"
#define SysFlags35              "DBLH TRAL"  // "Ʊβ���ߴ�ӡ"
//ccr2016-03-21#define SysFlags36              "To .CSV "
#define SysFlags37              "PRINT DATE"
#define SysFlags38              "PRINT TIME"
#define SysFlags39              "PRINT CALL#"    //"��ӡȡ�˺�"
#define SysFlags40              "HEART BEAT"    //ccr2015-08-03"�����������Heart beat"
#define SysFlags41              "PreFix1:"      //ccr2016-08-02
#define SysFlags42              "PreFix2:"      //ccr2016-08-02


#define GrapType1               "LOGO TYPE"        //"�̵�ͼ��",
#define GrapType2               "PRIZE"        //"�н�ͼ��:",
#define GrapType3               "TRAIL LOGO"        //"Ʊβͼ��:",
#define GrapType4               "TEXT"        //"��ӡ����?",

#define GrapSet1                "SEQUENCE#"        //"���:",
#define GrapSet2                "PICTURE#"        //"ͼ����:",
#define GrapSet3                "FROM "        //"��ʼ����:",
#define GrapSet4                "TO "        //"��������:",
  /////==============CHN msg===============//////

#define CurrentMode1            "RG  "  //"Ӫҵ",
#define CurrentMode2            "X   "  //"����",
#define CurrentMode3            "Z   "  //"����",
#define CurrentMode4            "SET "  //"����",
#define CurrentMode5            "MG  "  //"����",

#define SetupMode1              "GENERAL SET"  //---090421 BY ZY// "�ۺϹ���",
#define SetupMode2              "DEPT/PLU..."  // "��Ʒ����",
#define SetupKeyboard           "KEYBOARD"      //DEFKEYBOARD  //
#define msgCOMMHOST             "NETWORK"
#define SetupMode3              "PERIPHERALS"    // "ͨѶ������",
#define SetupMode4              "MANAGEMENT"    // "���۹�������",
#define SetupMode5              "ACCOUNT"   // "��Ա������",
#define SetupMode6              "HEADER/TRAILER"  // "Ʊ����ʽ",
#define SetupMode7              "REPORT    "    // "������",
#define msgDISCOUNT             "DISCOUNT"      //MENUDISC //
#define SetupMode8              "PB FUNCTION"   // "��������",
#define SetupMode9              "SET PASSWORD"    // "����,
#define SetupMode10             "SERVICE"       // "�տ��ά��",


#define SysSettings1            "SYSTEM OPTIONS"     // "ϵͳ��������",
#define SysSettings2            "SET DATE"     // "����",
#define SysSettings3            "SET TIME"     // "ʱ��",
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define msgSETEJOURNAL          "SET EJ"      //SETEJOURNAL //EJOURNAL
#endif

#define SysSettings4            "DEF KEYBOARD"     // "����",
#define MESSKEYMACRO            "KEYB. MACRO" // "���̺�"
#define MESSKEYTYPE             "KEYBOARD TYPE"             // "����ģʽ"

#define SysSettings5            "HOSPITALITY"      // "���������л�",
#define SysSettings6            "RETAIL"    // "���м����л�",
#define SysSettings8            "WIRELESS"          //"GPRSͨ��"  //SETGPRS //ccr2014-11-11 NEWSETUP

#define SetupCaption1           "GROUP"			//"����"
#define SetupCaption2           "DEPARTMENT"	//"����",
#define SetupCaption3           "PLU"			//"��Ʒ",
#define SetupCaption4           "PRINT PLUS"			//"��ӡ��Ʒ�嵥",
#define msgSETTEST              "TEST ECR"//"ϵͳ����"            //SETTEST
#define msgSETCLEARPLU          "CLEAR PLU"//"�����Ʒ"        //SETCLEARPLU
#define msgSETPLULIST           "PRN DEPT/PLU"//"��ӡ��Ʒ�嵥"      //SETPLULIST
#define msgSETTSTVER	        "PRINT VERSION"//"��ӡ�汾"      //SETTSTVER
#define msgSETCONFIGPLU         "FORM PLU"//"���õ�Ʒ"          //SETCONFIGPLU
#define msgSETCONFIGDEPT        "FORM DEPT" //���ò���         //SETCONFIGDEPT
#define msgSETINSTALL           "INSTAL/BACKUP"//"��װ/����"        //SETINSTALL
#define msgSETPRINTFAT          "PRINT MAT"//"��ӡ�ļ������"   //SETPRINTFAT


#define SetupCaption5           "COMPUTER"			// "ͨѶ��1",
#define SetupCaption6           "SCANNER"			// "ͨѶ��2",
#define SetupCaption7           "SCALE"			// "ͨѶ�� 3",
//#define SetupCaption8           "PORT-4"			// "ͨѶ�� 4",
#define SetupCaption9           "ETHERNET"			// "��������",

#define SetupCaption10          "SLIP PRINTER"			// "Ʊ�ݴ�ӡ",
#define SetupCaption11          "KITCHEN PRINT"			// "������ӡ",
#define SetupEXTPrinter         "EXTERNAL PRINT"    //SETEXTPRINTER

#define SetupCaption12          "OFFER"				// "�Żݼ�",
#define SetupCaption13          "PROMOTION"			// "�н�����",
#define SetupCaption14          "DISCOUNT"				// "�ۿ�",
#define SetupCaption15          "PO.RA"				// "�������",
#define SetupCaption16          "CORRECT"			// "��������",
#define SetupCaption17          "TENDER"			// "���ʽ",
#define SetupCaption18          "CURRENCY"        // "���",
#define SetupCaption19          "DRAWER"        // "Ǯ��",
#define SetupCaption20          "TAX"        // "˰��",

#define SetupCaption21          "SET ACCOUNT"  // "IC������",
#define SetAddNewECRVIP         "ADD ACCOUNT"
#define SetPrintECRVIP          "PRINT ACCOUNT"
#define SetCleanALLVIP          "CLEAN ACCOUNT"

#define SetupCaption22          "LOST CARD"        // "IC����ʧ",
#define SetupCaption23          "PRINT CARD"        // "��ӡ����Ϣ",
#define SetupCaption24          "HEADER"        // "Ʊͷ",
#define SetupCaption25          "TRAILER"        // "Ʊβ",
#define SetupCaption26          "SLIP HEADER"        // "Ʊ��Ʊͷ",
#define SetupCaption27          "GRAPHIC"        // "ͼ��",
#define SetupCaption28          "PRINT GRAPHICS"  // "��ӡͼ��",
#define SetupCaption29          "REPORT"        // "���ñ�������",
#define SetupCaption30          "REPORT UNIT"  // "����Ԫ",
#define SetupCaption31          "TIME ZONE"        // "����ʱ������",
#define SetupCaption32          "CLEAR ALL"     // "���屨��",
#define SetupCaption33          "PRINT LOG"         // "��ӡ��ˮ",

#define SetupCaption34          "TABLE"  // "��̨",
#define SetupCaption35          "PB FUNCTION"  // "��������",
#define SetupCaption36          "MODIFIER"      //ZY  // "�˵�˵��",
#define SetupCaption37          "AGREEMENT"          //ZY  // "ǩ��",
#define SetupCaption38          "CLERK"  // "�տ�Ա",
#define SetupCaption39          "SALESMAN"  // "ӪҵԱ",
#define SetupCaption40          "PG-PASSWORD"          //ZY  // "���õ�����",
#define SetupCaption41          "MG-PASSWORD"          //ZY  // "��������",
#define SetupCaption42          "X-PASSWORD"     //ZY  // "ֻ����������",
#define SetupCaption43          "Z-PASSWORD"     //ZY  // "���ʱ�������",
#define SetupCaption44          "MEMORY"        //ZY  // "��ӡ����",
#define SetupCaption45          "DISPLAY"       //ZY  //"��ʾ����",
#define SetupCaption451         "CUSTOMER"      // ���Բ���
#define SetupCaption46          "PRINTER"      //ZY  //"��ӡ�汾",
#define SetupTestRAM           "CHECK RAM"        //SETTSTMEM	       //RAM����
#define SetupCaption47          "CLOCK"      //ZY  //"ʱ�Ӳ���",
#define SetupCaption48          "BUZZER"     //ZY  //"����������",
#define SetupCaption49          "DRAWER"     //ZY  //"Ǯ�����",
#define SetupCaption50          "KEYBOARD"       //ZY  //"���̲���",
#define SetupCaption51          "SERIAL PORTS"        //ZY  //"���ڲ���",
#define SetupCaption52          "SELF-TEST"       //ZY  //"�Զ�����",

#define msgSETPRNMENU           "PRINT MENU"      //SETPRNMENU   //

#define OperationN1             "RECORD#"  // "��¼#",
#define OperationN2             "NOTE?"           //ZY  // "��¼?",

#define OperationN12            " PASSWD:"  // "����",
#define OperationN13            "CONFIRM:"  // "����ȷ��",
#define OperationN16            "STORE"  // "���а�",
#define OperationN17            "RESTAURANT"  // "������",
#define OperationN18            "TEST"  // "����",


#define CaptionN1               "TOTAL"  // "Ӧ��",
#define CaptionN3               "PRICE"  // "�۸�",
#define CaptionN8               "CHANGE"  // "����",

#define CaptionN39              "ADD PLU?"  // "����?",
#define CaptionN40              "DEL PLU?"  // "ɾ��?",
#define CaptionN47              "OPTIONS:"  // "ѡ��:",
#define CaptionN48              "FIXED"  // "�̶�",��Ҫ����SETINPUTWD�Ŀ��
#define CaptionN49              "FREE"  // "����",��Ҫ����SETINPUTWD�Ŀ��
#define CaptionN50              "FIX/FREE"  // "��/��",��Ҫ����SETINPUTWD�Ŀ��
#define CaptionN62              "JOLLY:"  // "�н��趨:",
#define CaptionN63              "ACCOUNT POINT"  // "���ѻ���:",
#define CaptionN64              "ALTER PRICE"  // "�ı䵥Ʒ�۸�",
#define CaptionN65              "KP GROUP"  // "������ӡ����"��
#define CaptionN66              "INC. INVEN"  // "���ӿ��",
#define CaptionN67              "DEC. INVEN"  // "���ٿ��",
#define CaptionN68              "GET "  // "����",
#define CaptionN69              "PAY "  // "����",


#define CaptionE1               "RS232 ERR"  // "RS232��",
#define CaptionE2               "RS232 OK"  // "RS232��ȷ",
#define CaptionE3               "RTC ERR!"  // "RTC ��!",
#define CaptionE4               "CTC ERR!"  // "CTC ��!",
#define CaptionE5               "FPROM ERR!"  // "FPROM��!",
#define CaptionE6               "INITIALIZING."  // "��ʼ��...",
#define CaptionE7               "INIT.COMPLETE"  // "��ʼ������.",
#define CaptionE8               "ERROR"  // "����-",//����<SCREENWD

#define CaptionE9               "PWD ERR!"  // "����� ��",
#define CaptionE10              "PWD SAVED"  // "�����ѱ���",
#define CaptionE15              "CONFIRM ?"  // "ȷ��?",
#define CaptionE16              "COMPLETE"  // "���",

#define CaptionE25              "@UPDATING!\nDON'T SHUTDOWN!"  // "���³�������ϵ�",
#define CaptionE26              "FILE OVERFLOW!"  // "�ļ��ռ�Խ��",
#define CaptionE27              "MEM OVERFLOW,\nDEC PLU!"  // �ڴ������
#define CaptionE28              "LOG-MEMORY FULL"  // "��ˮ�洢����",
#define CaptionE29              "PAPER END"  // "�������ӡֽ",
#define CaptionE30              "EXTD MEM ERR"  // "��չ�ڴ����",



#define CaptionE32              "INVALIDINPUT"  // "��Ч����!",
#define CaptionE33              "INVALID DATE"  // "��Ч����!",
#define CaptionE34              "INVALID TIME"  // "��Чʱ��!",
#define CaptionE35              "NOT ALLOWED!"  // "��ֹ����!",
#define CaptionE36              "NULL PLU!"  // "PLU����Ϊ��!",
#define CaptionE37              "PLU FULL"  // "PLU�ļ����!",
#define CaptionE38              "TABLE EXIST!"  // "��̨��ռ��!",
#define CaptionE39              "TABLE OPENED"  // "��̨�Ѵ�!",
#define CaptionE40              "WRONG TABLE#"  // "��̨�Ų���!",
#define CaptionE41              "INPUT TABLE#"  // "��������̨��",
#define CaptionE42              "NULL TABLE"  // "û�п�̨",
#define CaptionE43              "TABLE FULL"  // "��̨�������",
#define CaptionE44              "NOT ALLOWED!"  // "��ֹ�޸�ʱ��",
#define CaptionE45              "IN TRADING!"  // "����������!",
#define CaptionE46              "BUFFER FULL"  // "���ۻ�������",
#define CaptionE47              "ITEM NOT SOLD"  // "��Ʒû���۳�",
#define CaptionE48              "IN TRADING!"  // "���ڽ�����!",
#define CaptionE49              "INVALID NUM."  // "�������ݳ���",
#define CaptionE50              "TENDERING!"  // "���ڸ���!",
#define CaptionE51              "WRONG COVER"  // "�������!",
#define CaptionE52              "CONFIRM TABLE"  // "û��ȷ�Ͻ���",
#define CaptionE53              "NOT ALLOWED!"  // "��ֹȡ������",
#define CaptionE54              "NULL ITEM!"  // "�޲���!",
#define CaptionE55              "NULL CLERK"  // "�޴��տ�Ա!",
#define CaptionE56              "CLERK LOCK"  // "�տ�Ա�ı�",
#define CaptionE57              "NULL REPORT!"  // "�޴��౨��!",
#define CaptionE58              "PRT INTERRUPT"  // "�����ӡ�ж�",
#define CaptionE59              "MG-MODE MUST"  // "�����ھ���",
#define CaptionE60              "CAN'T SPLIT"  // "���ܷ���ʱ��",
#define CaptionE61              "INPUT NOADD#!"  // "�����������",
#define CaptionE62              "KEY-POS ERROR"  // "Կ�׵�λ��",
#define CaptionE63              "UNAUTHORIZED"  // "δ��Ȩ!",
#define CaptionE64              "OPER.REQUIRED"  // "��ָ���տ�Ա",
#define CaptionE65              "SALP.REQUIRED"  // "��ָ��ӪҵԱ",
#define CaptionE66              "NOT ALLOWED!"  // "��ֹPLU��ۣ�",
#define CaptionE67              "PASSWORD ERR!"  //  "���벻��!",
#define CaptionE68              "K-PRINT ERR"  // "������ӡ����",
#define CaptionE69              "PRINT ERROR"  // "Ʊ�ݴ�ӡ����", //ccr2017-08-31
#if defined(CASE_INNERDOTPRN)
#define CaptionE70              "PRINTER BUSY!"  // "��ӡѹ��̧��",
#else
#define CaptionE70              "PAPER END!"  // "��ӡѹ��̧��",
#endif
#define CaptionE71              "PAPER END!"  // "��ӡֽ����!",
#define CaptionE72              "OVERHEATING!"  // "��ӡ�¶�̫��",
#define CaptionE73              "FUNC UNDEFINE"  // "����δ����!",
#define CaptionE74              "VALUE REQUIRED"  // "����������",
#define CaptionE75              "POST TENDER!"  // "��ֹ���ָ���",
#define CaptionE76              "NULL FUNC."  // "�����޴˹���",
#define CaptionE77              "SUBT REQUIRED"  // "δ��С�Ƽ�!",
#define CaptionE78              "IN INVENTORY"  // "���ڹ�����",
#define CaptionE79              "LOG ERROR"  // "������ˮ��",
#define CaptionE80              "MODEM ERROR"  // "MODEMͨѶ��!",


#define CaptionE81              "CHIPCARD EROR"  // "����������!"
#define CaptionE82              "POS CODE ERR!"  // "POS�����!"
#define CaptionE83              "DATA ERROR!"  // "�����ݴ�!"
#define CaptionE84              "EXPIRED CARD!"  // "Ϊ���ڿ�!"
#define CaptionE85              "LOST CARD"  // "Ϊ��ʧ��!"
#define CaptionE86              "WRONG TYPE!"  // "�ͻ�����!"
#define CaptionE87              "NEW CARD!"  // "Ϊ�¿�!"
#define CaptionE88              "NO CASH CARD!"  // "���ǹ��￨!"
#define CaptionE89              "WRITING ERROR!"  // "д������!"
#define CaptionE90              "WRONG SERIAL#!"  // "���Ų���!"
#define CaptionE91              "DISC. CARD!"  // "�����ۿۿ�!"
#define CaptionE92              "CASH CARD!"  // "�����ֽ�!"
#define CaptionE93              "CREDIT CARD!"  // "�������ʿ�!"
#define CaptionE94              "DISABLE!"  // "����IC��!"
#define CaptionE95              "DISCHARGEERR"  // "�忨����!",
#define CaptionE96              "OVERFLOW!"  // "�������!",
#define CaptionE97              "CHARGE ERR!"  // "IC��ֵ����!",
#define CaptionE98              "INIT ERR"  // "IC��ʼ������",
#define CaptionE99              "DISABLED"  // "��ֹ��ʼ��!",
#define CaptionE100             "LOW VALUE!"  // "IC����!",
#define CaptionE101             "PAY ERR!"  // "IC�������!",
#define CaptionE102             "IP-ERR!"  // "IP��ַ��"
#define CaptionE103             "NO CHIP CARD!"  //  ,
#define CaptionE105		        "ON HOLD"    //CWXXI73//Ccr							//CWXXI73

#define CaptionERR105             "BATTERY LOW!"  // "��ص�����",
#define CaptionERR106             "STOCK DISABL"	//20070806"û������"
//ccr090715>>>>>>>>>>>>>>>>>>>>>>
#define CaptionERR76			  "INSERT DISK"	//
#define CaptionERR77			  "OPEN ERROR!"		//
#define CaptionERR78			  "READ ERROR!"		//
#define CaptionERR79			  "WRITE ERROR!"		//
#define CaptionERR80			  "CREATE ERROR"		//
#define CaptionERR81			  "CLOSE ERROR!"		//
#define CaptionERR82			  "SEND LOG!"		//
#define CaptionERR83              "GPRS ERROR!"
#define CaptionERR84              "SEND ERROR!"
#define CaptionERR85              "ERR-RECEIVE"
#define CaptionERR86              "No SERVER!"
#define CaptionERR87              "IP/PORT:NULL"    //û�����÷�����IP�Ͷ˿�
#define CaptionERR88              "NO SIM CARD"
#define CaptionERR89              "GPRS NOT OK"
#define CaptionERR90              "OUT OF RANGE" //CWXXI90  //
#define CaptionERR91              "NULL ACCOUNT"  //CWXXI91


//ccr2016-10-24 EJ >>>>>>>>>>>>>>>>>>>
#define EJ_CWXXI92  "EJ data ERROR"   	//CWXXI92
#define EJ_CWXXI93  "NO SD CARD"        	//CWXXI93
#define EJ_CWXXI94  "R-W EJ ERROR."   	//CWXXI94
#define EJ_CWXXI95  "NO EJ RECORDS"   	//CWXXI95
#define EJ_CWXXI96  "EJ NEARLY FULL"   	//CWXXI96
#define EJ_CWXXI97  "EJ IS FULL"   	//CWXXI97
#define EJ_CWXXI98  "NEW EJ"        	//CWXXI98
#define EJ_CWXXI99  "Initial EJ 1ST"   	//CWXXI99
#define EJ_CWXXI100 "EJ NOT MATCHED"     	//CWXXI100


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


#define CaptionE104             "OPEN DRAWER"  // "��Ǯ��",
#define CaptionE106             "RECEIPT ON HOLD"    //YOUGUADAN
#define CaptionE107             "  ENTER QUANTITY\n AND IT'S PRICE"    //SHURUQTYAMT
#define CaptionE108             "TRANFER TO"    //ZHUANRUDAO

#define MsgPUTOUT               "PO"   	                //PUTOUT
#define MsgRECIEVIN             "RA" 		            //RECIEVIN

#define DownLoad1               ">> FONT"  // "���������ֿ�",
#define DownLoad2               ">> GRAP"  // "��������ͼ��",


#define OptionN1                "YES"  // "��",
#define OptionN2                " NO"  // "��",
#define OptionN3                "NAME "  // "����:",
#define OptionN4                "DEPART"  // "����:",
#define OptionN5                "GROUP"  // "����:",
#define OptionN6                "PRINT"  // "��ӡ:",
#define OptionN7                "OPTION"  // "ѡ��:",
#define OptionN8                "LINKED"  // "����:",
#define OptionN9                "TAX"  // "˰��:",
#define OptionN10               "POS CODE"  // "λ�ñ��:",
#define OptionN11               "PRICE1"  // "�۸� 1:",
#define OptionN12               "PRICE2"  // "�۸� 2:",
#define OptionN13               "PRICE3"  // "�۸� 3:",
#define OptionN14               "PRICE4"  // "�۸� 4:",

#define OptionN15               "BUY"  // "����:",
#define OptionN16               "DISC(%)"  // "�ۿ���(%):",
#define OptionN17               "MAX"  // "���ֵ:",
#define OptionN18               "DISC"  // "�ۿ���:",
#define OptionN19               "MAX"  // "���ֵ:",
#define OptionN20               "RATE"  // "����:",
#define OptionN21               "BUYING"  // "�����:",
#define OptionN22               "SELLING"  // "������:",
#define OptionN23               "STATUS"  // "״̬:",
#define OptionN24               "DRAWER"  // "Ǯ��:",
#define MSGOTD                  "OTD"                    //OTDMSG
#define OptionN25               "K-PRINTER"  // "������ӡ:",
#define MSGPERIOD               "PERIOD"                      //PERMSG
#define MSGPOINTER              "POINTER"                     //POIMSG

#define OptionN26               "PREFIX"  // "ǰ׺��",,6���ַ�
#define OptionN27               "LINK"  // "����:",
#define OptionN28               "FUNC-CODE "  // "���빦����:",
#define OptionN29               "ASSIGN TO"  // "�����ܼ�:",
#define OptionN30               "TYPE"  // "����:",
#define OptionN31               "DATE FROM"  // "��ʼ����:",
#define OptionN32               "DATE TO"  // "��������:",
#define OptionN33               "STA. TIME"  // "��ʼʱ��:",
#define OptionN34               "END TIME"  // "����ʱ��:",
#define OptionN35               "WEEK"  // "����:",
#define OptionN36               "DISC."  // "�ۿ�:",
#define OptionN37               "QUANTITY"  // "�������:",
#define OptionN38               "PRICE"  // "����:",
#define OptionN39               "OFFER"  // "�Żݼ�:",
#define OptionN40               "PROTOCOL"  // "ͨѶЭ��:",
#define OptionN41               "PHONE#"  // "�绰����:",
#define OptionN42               "PWD."  // "����:",
#define OptionN43               "FREQUENT"  // "Ƶ��:",
#define OptionN44               "THRESHOLD"  // "��С���:",
#define OptionN45               "PORT"  // "ͨѶ��:",
#define OptionN46               "VALUE"  // "�Ƶ���:",
#define OptionN47               "PICTURE#"  // "ͼ�����:",
#define OptionN48               "TIME"  // "ʱ��:",
#define OptionN49               "DATE"  // "����:",
#define OptionN50               "PRINTER"
#define OptionN51               "TYPE:"      //DZCHXHAO//"���ͺ�:",

#define WelcomeN1                "THANKS CHOOSING\nEUTRON ECR"  // "�� �� �� �� �� �� �� ��\n    ��ӭʹ���Ŵ��տ��" */
#define WelcomeN2                "THANKS CHOOSING \nEUTRON ECR"  // "���������Ŵ����\n�Ŵ�����ʯ�տ��" */

#define MessagesN1                "ECR CLOSED!"  // "  �տ��������",
#define MessagesN2                "PRESS <KEY>"  // "������ʽ��������",
#define MessagesN3                "FORMAL INVOICE"  // "��ʽ��Ʊ",																							//XSHFPIAO
#define MessagesN4                "KITCHEN #"  // "������ӡ��#",																						//CHFDYJHAO
#define MessagesN13               "<>"
#define MessagesN14               "TOTAL"  ////KPTOTAL


#define CaptionM1                 "JANUARY"  // "һ��",
#define CaptionM2                 "FEBRUARY"  // "����",
#define CaptionM3                 "MARCH"  //  "����",
#define CaptionM4                 "APRIL"  //  "����",
#define CaptionM5                 "MAY"  // "����",
#define CaptionM6                 "JUNE"  // "����",
#define CaptionM7                 "JULY"  // "����",
#define CaptionM8                 "AUGUST"  // "����",
#define CaptionM9                 "SEPTEMBER"  // "����",
#define CaptionM10                "OCTOBER"  // "ʮ��",
#define CaptionM11                "NOVEMBER"  // "ʮһ��",
#define CaptionM12                "DECEMBER"  // "ʮ����",

#define CaptionW1                 "MONDAY"  // "����һ",
#define CaptionW2                 "TUESDAY"  // "���ڶ�",
#define CaptionW3                 "WEDNSDAY"  // "������",
#define CaptionW4                 "THURSDAY"  // "������",
#define CaptionW5                 "FRIDAY"  // "������",
#define CaptionW6                 "SATURDAY"  // "������",
#define CaptionW7                 "SUNDAY"  // "������",


#define ClueN1                    "PRESS ENTER..."  // "��ȷ�ϼ�...",

  //Option for KP
#define OptionS1                  "PRT.TOTAL"  // "��ӡ�ܶ�:",
#define OptionS2                  "COMBINED"  // "����ͬ��ӡ",
#define OptionS3                  "CLASSIFIED"  // "�˲�ͬ��ӡ",
  //Option for dept
#define OptionS4                  "ZERO PRICE"  // "��ֹ��۸�",
#define OptionS5                  "SEPARATRIX"  // "��ӡ�ָ���",
#define OptionS6                  "SINGLE"  // "��������:",
#define OptionS7                  "DISC. 1"  // "�ۿ��� 1:",
#define OptionS8                  "DISC. 2"  // "�ۿ��� 2:",
  //Options for tend
#define OptionS9                  "OPENDRAWER"  // "��Ǯ��:",
#define OptionS10                 "AMT. COMP."  // "������:",
#define OptionS11                 "FORBIDDEN"  // "��ֹ����:",
#define OptionS12                 "NOADD#:"  // "�������:",
#define OptionS13                 "TIP"  // "����ΪС��",
  //Options for PoRa
#define OptionS14                 "OPEN DRAWER"  // "��Ǯ��:",
#define OptionS15                 "<TENDER>"  // "���ʽ��",
#define OptionS16                 "DEPOSIT"  // "������:",
#define OptionS17                 "PO/RA"  // "���/����",
  //Option for Disc
#define OptionS18                 "PRINT DISC."  // "��ӡ�ۿ۶�",
#define OptionS19                 "DISCOUNT 1"  // "ʹ���ۿ�1:",
#define OptionS20                 "DISCOUNT 2"  // "ʹ���ۿ�2:",
  //Options for currency
#define OptionS21                 "CHANGE"  // "����������",
  //Options for Draw
#define OptionS22                 "NO DECIMAL"  // "��С����:",
#define OptionS23                 "OPEN DRAWER"  // "��Ǯ��:",
  //Options for Tax
#define OptionS24                 "TAX ADDON"  // "Ӫҵ/��ֵ:",
#define OptionS25                 "PRINT VAT"  // "��ӡ˰����",
#define OptionS26                 "PRINT ZERO"  // "��ӡ0˰��",
#define OptionS27                 "GST"  // "ΪGST��˰",
#define OptionS28                 "PRINT TAX"  // "��ӡ˰��:",
  //Options for clerk
#define OptionS29                 "CORRECT"  // "ȡ������:",
#define OptionS30                 "VOID"  // "��������:",
#define OptionS31                 "CANCEL"  // "ȡ������:",
#define OptionS32                 "REFUND"  // "�˻�����:",
#define OptionS33                 "%DISCOUNT"  // "%�ۿ�����:",
#define OptionS34                 "%SURCHARGE"  // "%�ӳ�����:",
#define OptionS35                 "+-AMOUNT."  // "+-�������",
#define OptionS36                 "TRAINING"  // "��ѵģʽ:",

#define MESS_ECR_IP         "ECR IP ADDRESS:"
#define MESS_ECR_ID         "ECR ID(0-9,A-F):"

#define EditN1                    "<REC.SQ>NEW REC.\n<ENTER> CUR.REC \n"  //---ZY  //ccr "<��¼��>  �¼�¼\n<ȷ��>  ��ǰ��¼\n",
#define EditN2                    "<REC.SQ>A/D ITEM\n<ENTER> CUR.REC \n"   //---ZY  //ccr "<��¼��>��ɾ��Ʒ\n<ȷ��>  ��ǰ��Ʒ\n",
#define EditN3                    "<EXIT>      EXIT"                       //---ZY  // "<�˳�>      �˳�",
#define EditN4                    "<ENTER> CONTINUE\n"                 //---ZY  // "<ȷ��>      ����\n",
#define EditN5                    "SELECT A REPORT"  // "��<ѡ��>����",
#define EditN7                    "ASSIGN TO"                    //---ZY  //"����     ->��   ",
#define EditN8                    "MG REQUIRED"  // "ֻ���ھ�����",
#define EditN9                    "RG REQUIRED"  // "����Ӫҵ����",
#define EditN10                   "TEXT"  // "��ӡ����",
#define EditN11                   "(RESERVED)"  // "����",
#define EditN12                   "FILE/PASSWORD/TEST"  // "�ļ��������",
#define EditN13                   "DIALING"  // "����",
#define EditN14                   "CONNECTING!"  // "MODEM ����!",
#define EditN15                   "CODE:"  // "����:",
#define EditN16                   "%DISCOUNT"  // "%�ۿ�",
#define EditN17                   "%SURCHARGE"  // "%�ӳ�",
#define EditN18                   "RECEIPT#:"  // "�վݺ�:",
#define EditN19                   "FIELS"  // "�ļ�����"��0
#define EditN20                   "TOTAL"  // "�ļ��ռ䣺"?
#define EditN21                   "REPORT"  // "ͳ���ļ�"2
#define EditN22                   "TAX"  // ����˰��8
#define EditN23                   "LOG MEMORY"  // "��ˮ�ռ�"
#define EditN24                   "FILE           RECORDS      RAM"  // "�ļ���      ��¼��      �ռ��С"
#define EditN25                   "PORT         TYPE      PROTOCOL"  // "��������    ͨ�����   ͨ��Э��"
#define EditN26                   "BLANKLINE"  // '����������',
#define EditN27                   "LINAGE"  // 'ÿҳ����',
#define EditN28                   "PRINT DATE"  // '��ӡ��Ϣ',
#define EditN29                   "SEC RECEIPT"  // '�ڶ���Ʊ��',
#define EditN30                   "LEFT MARGIN"  // '��߾�',
#define EditN31                   "TYPE"  // 'Ʊ�����',
#define EditN32                   "PRINTER OFF"  // "��ӡ����",
#define EditN33                   "PRINTER ON"  // "��ӡ����",
  //ChipCard>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define ChipCardN1                "PWD"  //I "����:",
#define ChipCardN2                "PWD CONF."  // "����ȷ��:",
#define ChipCardN3                "POS CODE"  // "POS����:",
#define ChipCardN4                "POS CONF."  // "����ȷ��:",
#define ChipCardN5                "POS SAVED"  // "�����ѱ���",
#define ChipCardN6                "POS ERR."  // "����� ��",
#define ChipCardN7                "CHIP CARD"  // "����IC��:",
#define ChipCardN8                "DISCOUNT"  // "�ۿۿ�:",
#define ChipCardN9                "CASH"  // "�ֽ�:",
#define ChipCardN10               "CREDIT"  // "���ʿ�:",
#define ChipCardN11               "PRINT"  // "��ӡIC��",
#define ChipCardN12               "AUTO DISC"  // "�Զ��ۿ�:",
#define ChipCardN13               "POINTS"  // "���ѻ���:",
#define ChipCardN14               "CASH=CC"  // "���ֽ��:",
#define ChipCardN15               "DEAD DATE"  // "������Ч��", //
#define ChipCardN16               "LOST LIST"  // "��ʧ����",
#define ChipCardN17               "SERIAL#"  // "����:",
#define ChipCardN18               "TYPE"  // "������:",
#define ChipCardN19               "BALANCE"  // "���"
#define ChipCardN20               "FOREGIFT"  // "��Ѻ��:",
#define ChipCardN21               "SPENDING"  // "����:",
#define ChipCardN22               "CHARGE"  // "��ֵ�ܶ�:",
#define ChipCardN23               "RECEIPTS"  // "ʹ�ô���:",
#define ChipCardN24               "PRICE LVL"  // "�۸񼶱�:",
#define ChipCardN25               "PIN"  // "PIN��:",
#define ChipCardN26               "PROTECT LVL"  // "��������:",
#define ChipCardN27               "AUTO CHECK"  // "�Զ�����:",
#define ChipCardN28               "INIT DATE"  // "�ƿ�����:",
#define ChipCardN29               "DEAD DATE"  // "����Ч��:",
#define ChipCardN30               "HOLDER"  // "�ͻ�:",
#define ChipCardN31               "CREATE"  // "��ʼ��IC",
#define ChipCardN32               "CHARGE"  // "IC����ֵ",
#define ChipCardN33               "CLEAR CARD"  // "���IC��",
#define ChipCardN34               "CHARGE?"  // "��ֵ/�˿�?",
#define ChipCardN35               "REDEMPTION?"  // "����/�͵�?",
#define ChipCardN36               "CONFIRM?"  // "ȷ�ϳ�ֵ?",
#define ChipCardN37               "CONFIRM?"  // "ȷ���˿�?",
#define ChipCardN38               "CONFIRM?"  // "ȷ���͵�?",
#define ChipCardN39               "CONFIRM?"  // "�ҽ�ȷ��?",
#define ChipCardN40               "ENCASH"  // "�Ƶ�ҽ�",
#define ChipCardN41               "WITHDRAWAL"  // "IC���˿�",
#define ChipCardN42               "ENCASH"  // "IC���ҽ�����",
#define ChipCardN43               "PONITS"  // "IC���͵���",
#define ChipCardN44               "PLEASE WAIT......"  // "��ȴ�......",
#define ChipCardN45               "PLEASE REFUND FIRST...."  // "�����н��,�����˿�....",
#define ChipCardN48               "RESTART NEW IP"  // "Ҫ�����µ�IP,�����¿���.",
#define ChipCardN49               "CONFIRM CLEAR?"  //  "ȷ���屨��?",
#define ChipCardN50               "WAITTING..."  // "�ȴ�IC��....",
#define ChipCardN51               "DOUBLE PRT." //---zy  // "���ߴ�ӡ",

//ccr2015-06-15>>>>>>>>>>>>>>>>>>>>>
#define ChipCardN52             "CLEAR"
#define ChipCardN53             "REFUND"
#define ChipCardN54             "PAYMENT"
#define ChipCardN55             "CHARGE"
#define ChipCardN56             "INITIALIZATION"
#define ChipCardN57             "CASH OUT"
#define ChipCardN58            "ADD POINTS"   //ADDVIPPOINTS
#define ChipCardN59            "DEC POINTS"   //DECVIPPOINTS
#define ChipCardN60            "SUM POINTS"  //VIPPOINTS
//ccr2015-06-15<<<<<<<<<<<<<<<<<<<<<
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MESSEJ_X_STORE      "SAVE X DATA"//MsgEJ_X_STORE
#define MESSEJ_Z_STORE      "SAVE Z DATA"//MsgEJ_Z_STORE
#define MESSEJ_TR_STORE     "SAVE TRAIN"//MsgEJ_TR_STORE
#endif
//ccr2016-02-22>>>>>>>>>>>>>>>>>>>>>
#define MsgMENUXREPORT     "X REPORT"
#define MsgMENUXEXPORT     "EXPORT(X)"
#define MsgMENUQUICKVIEW   "GRAND TOTAL"
#define MsgMENUXLOGFUNC     "VIEW LOG"
#define MsgMENUSENDNEWLOG  "SEND NEW LOG"      //MENUSENDNEWLOG  //��������ˮ����
#define MsgMENUXPASSWORD   "X-PASSWORD"
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MsgMENUXEJOURNAL    "EJ"     //MENUXEJOURNAL   "E Journal"
#endif
//.................................
#define MsgMENUZREPORT     "Z REPORT"
#define MsgMENUZEXPORT     "EXPORT(Z)"
#define MsgMENUCLEARLOG     "CLEAR LOG"
#define MsgMENUZGRAND      "SET CLEAR TOTAL"
#define MsgMENUZPASSWORD   "Z-PASSWORD"
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MsgMENUZRESETEJ   "RESET EJ"     //MENUZRESETEJ   "Clear EJ"
#endif
//...................................


#define EPosN1                    "EPOS CODE:"  // "ePOS��֤��:",
#define EPosN2                    "WAITING..."  // "�ȴ���ͨ��"
#define EPosN3                    "CARD NUM:"  // "��ͨ����:",
#define EPosN4                    "BALANCE:"  // "��ͨ�����:",


#define ErrInfoN1                 "DATA OVERSIZE"  // "ͨѶ���ݹ���"
#define ErrInfoN2                 "**** PRINT INTERRUPTED *****"  // " *** ��ӡ���жϡ����´�ӡ *** "
#define ErrInfoN3                 "CRC ERROR!"  // "����У���"
//PRINT



#define FisTextN1                 "TAXPAYER ID"   //"��˰�˺�:"
#define FisTextN2                 "PRINT INVOICE"   //"����˰Ʊ        "
#define FisTextN3                 "AUTHORIZED NUMBER "   //"��Ȩ����        "
#define FisTextN4                 "SERIAL NUMBER"   //"д������        "
#define FisTextN5                 "SERIAL# CONFIRM "   //"д��ȷ��        "
#define FisTextN6                 "DATA      PRINT "   //"����ӡ��        "
#define FisTextN7                 "USER        ID  "   //"�û�����        "
#define FisTextN8                 "TAX-EXEMPT      "   //"��˰״̬        "
#define FisTextN9                 "Z-COUNT         "   //"Z-����:         "
#define FisTextN10                "TAXABLE    SUM  "   //"�ۼ�����        "
#define FisTextN11                "TAX        SUM  "   //"�ۼ�˰          "
#define FisTextN12                "TOTAL TAX-EXEMPT"   //"����˰��        "
#define FisTextN13                "TOTAL   TAXABLE "   //"�����۶�        "
#define FisTextN14                "TOTAL    TAX    "   //"��˰��          "
#define FisTextN15                "DAILY RECEIPTS"   //"��˰Ʊ��        "
#define FisTextN16                "TAX RECPT. SUM  "   //"�վ�����        "
#define FisTextN17                "REPORT   SUM    "   //"�౨���� :      "

#define CurrentTimeN1                    "TIME:"      //  "��ǰʱ��"
#define InputMode1				"A:" // "A��"
#define InputMode2				"QU:" // "����"
#define InputMode3				"PING:" // "ƴ��"
#define InputMode4				"WUBI:" // "�ʣ�"

#define SpecialSymbol1			"<<"			//DOWNLOAD//Ccr "��",
#define SpecialSymbol2			">>"			//UPLOAD//Ccr "��",
#define SpecialSymbol3			"->  <-"		// "��  ��",

#define MESS_PRESSKEY   "PRESS ANY KEY..."

#if defined(CASE_QRCODE)
#define InputQRCode           "QRCODE"  //MsgQRCODE
#endif

#define GPRSServerIP			"SERVER IP"//"������IP"
#define GPRSServerPort		    "PORT"//"�˿ں�"

/////////////////////////////////////////////////////////
//added by lqw 090802
#if  (defined(CASE_GPRS))
#define GPRSAPNName        "APN"           //GPRSAPNNAME
#define GPRSUserName        "User Name"           //GPRSUSERNAME
#define GPRSPassword        "Password"           //GPRSPASSWORD

#define GPRSSendMESS        "Check GPRS" //ccr2014-11-11 NEWSETUP
#define GPRSSetMode         "Set Sent Mode"    //gprsSETMODE //ccr2014-11-11 NEWSETUP-step2
#define GPRSSendECRLogAll   "Send All LOG"    //gprsSendECRLogAll //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadPLU     "Update PLU"    //gprsDownloadPLU //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadDEPT    "Update DEPT"    //gprsDownloadDEPT //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadCLERK   "Update CLERK"    //gprsDownloadCLERK //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadHEAD    "Update HEAD"       //gprsDownloadHEAD //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadTRAIL   "Update TRAIL"      //gprsDownloadTRAIL //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadALL     "Update ALL"      //gprsDownloadALL //ccr2016-08-18
#define GPRSRestart         "RESET GPRS"      //gprsRestart //ccr2016-08-26

#define GPRSstr1 "DATA ERROR!"  // "�������ʹ�"
#define GPRSstr2 "GPRS OK"
#define GPRSstr3 "GPRS NOT OK"
#define GPRSstr4 "CONFIRM?"
#define GPRSstr5 "IP/PORT:NULL"
#define GPRSstr6 "ERROR:IP/PORT"
#define GPRSstr7 "WAITING GPRS"
#define GPRSstr8 "YES"   // "��"
#define GPRSstr9 " NO"    // "fou "
#define GPRSstr10 "TRANSMITTING..."  // "���ݷ�����.. "
#define GPRSstr11 "FINISHED"  // "�����ѷ���.. "
#define GPRSstr28 "SUCCESS........"						// "���ͳɹ�.."
#define GPRSstr31 "FAILURE ON CONNECT"	//						// "����ʧ��"
#define GPRSstr32 "FAILURE ON READ"                                           // "����ʧ��"
#define GPRSstr33 "CONFIRMA ERR"			// "����ȷ��ʧ��"
#define GPRSstr34 "FAILURE........"							// "����ʧ��"
#define GPRSstr58 "CONNECT........."		// "���ڽ�������.."
#define GPRSstr59 "CONNECT........."		// " ׼����������.."
#define GPRSstr60 "RESTART GPRS"	// "���ڸ�λģ��.."
#define GPRSstr61 "END OF SEND." // "�������,���˳�"

#define GPRSxACK  "Wait ACK Error"

#endif //end defined(CASE_GPRS)
///////////////////////////////////////////////////////////////////
#define InsertUSB		"<<Insert USB"//CHRUSB  ����U�� //

//ccr090715>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define usbMAIN1		"COPY TO USB"			//usbDAOCHU	�����տ���ļ� //
#define usbMAIN2		"COPY FROM USB"			//usbDAORU �����տ���ļ� //
#define usbMAIN3		"LOG TO USB"		//usbFLOW ����������ˮ //


#define usbFLOWNEWMESS	    "EXPORT UPDATE"      //1-����������   //
#define usbFLOWALLMESS	    "EXPORT ALL"      //2-����ȫ������
#define usbFLOWDELMESS	    "EXPORT/RESET"    //3-����ȫ�����ݺ����

#define usbALLFile		"ALL FILES"		//usbALL ȫ���ļ� //


#define MESSPRNMENU     "<00>Print IT"
#define MESSSETMENU     " MANUALS LIST"
#define MESSCLEANLOG    "CLEAR LOG?  "
#define MESSCLEANLOGA   "All of LOG\nwill be cleared!"
#define MESSRAMOUT      "RAM Overflow!HLT"
#define MESSCLEANFILES  "CLEAR FILES?"
#define MESSCONFIGERR   "Config changed,\nError will be if\nuse the old file"
#define MESSDELPLU      "Variable Changed\n     PLU deleted"
#define MESSPLUPRINTEND "PLU Printed O.K.\nPress <ENTER>!"


#define RECALLFLOW      "Recall LOG"

#define USBREPNAME      "Name"

////////  CSV�����ļ�����  /////////////////////////////////////////////
#define DEPTCAP       "Random,Name,Group,Print,Options\r\n"
#define PLUCAP        "Random,Name,OFFIndex,Dept,DeptHi,Price1,Price2,Price3,Price4,,Cost,Link,Inventory\r\n"

#define TAXCAP        "Name,Rate,Options\r\n"
#define HEADERCAP     "Captions on the receipt head\r\n"
#define DISCCAP       "Name,Print,Options,Fixed[3],Tax,Max\r\n"

#define SALPERCAP     "Name,Options\r\n"
#define SYSTEMCAP     "System Flags\r\n"
#define COMMCAP       "Name,Type,Prot,Telephone\r\n"
#define GRAPPRNCAP    "PictNo,DateFrom,DateTo\r\n"
#define GROUPCAP      "Name,Max\r\n"
#define ICCARDCAP     "Sets for Chip Card\r\n"
#define PROMCAP       "Freq,JollyMin,PointVal,PointMin,GrapIdx,Memo\r\n"
#define PBFUNCCAP     "Name,Print,Options\r\n"
#define CLERKCAP      "Name,Options,Passwd\r\n"
#define MODICAP       "Captions for modify\r\n"
#define PBTOTALCAP    "Random,Name\r\n"
#define ZONECAP       "Zone1,Zone2,Zone3,Zone4,Zone5,Zone6,Zone7,Zone8,Zone9,Zone10,Zone11,Zone12\r\n"
#define KEYBOARDCAP   "Defitions for keyboard"
#define OFFCAP        "Name,Type,DateFrom,DateTo,TimeFrom,TimeToWeekDay,Discount,NumItems,PriceU,PriceP\r\n"
#define PORACAP       "Name,,Print,Options,Drawer,Max\r\n"

#define TRAILERCAP    "Captions on the receipt trail\r\n"
#define SLIPHEADCAP   "Captions on the receipt Slip\r\n"
#define ICBLOCKCAP    "Chip card blocked\r\n"


#define EXPORTCSV    "1-CSV,2-BIN:"

#define CSVFLOETITL "Name,Quantity,Amount,Receipt,Clerk,SalesMan,DateTime,Register,ShopNo,Type\r\n"
#define CSVREPTITL  "DateTime,Register,ShopNo\r\n"

#define BUTTONBATLOW "S.Battery Low!"
#define CHARGEBATNOW "O.Battery Low!\nCharge Now..."

#define SRAMNOTFOUND "SRAM not found!\nSystem HALT!"

#define INPUTPLUCODE "PLU CODE:"

#define MessageE18      "!!!! FAT(PLU) ERROR !!!!"

#define MESS_TABLEHOLD  "Table    Suspend"

#define MESS_LOGREPET   "Re-Send LOG!"

#define MESS_PAYALSO   "Confirm Payment?"


#define MGADDINV        "INVENTORY+"  //1+SUBTOTAL
#define MGDECINV        "INVENTORY-"  //2+SUBTOTAL
#define MGSETPRICE      "PRICE PLU"  //3+SUBTOTAL

#define MGCLEARIC       "REFUND IC"
#define MGINITIC        "INIT IC"
#define MGCHARGE        "CHARGE IC"
#define MGADDPOINT      "ADD POINT"
#define MGPRINTSTOCK   "LIST STOCK"

#define MGPASSWORD      "SET PASSWORD"
#define MGCLOSEPRN      "CLOSE PRINT"
#define MGTRAINING      "TRAINING MODE"
#define MGGOTOMG        "MANAGEMENT"

//..............................................
#define PLUCODE     "PLU CODE"
#define INVQTYMUST  "INPUT QTY/PRICE"
#define ININVENTORY "Press <SUBT> Key\n Exit Inventory!"
//..............................................
#define DEVICENULL		" NULL"
#define DEVICEPORT1     "PORT#1"
#define DEVICEPORT2     "PORT#2"
#define DEVICEPORT3     "PORT#3"
#define DEVICEPORT4     "PORT#4"

//................................................
#define CLOSEPRINTER    "CLOSE PRINTER"
#define CLEARGRANDTOTAL "CLS G.T AFTER Z"
#define CLEANALLECRVIP  "CLEAN ACCOUNT?"//"�����Ա����?"

                       //012345678901234567890123456789012
//.......�������Ӧ������.........................................
#define MsgKEYCORR      "CORRECT"
#define MsgKEYCURR      "CURRENCY"
#define MsgKEYDISC      "DISCOUNT"
#define MsgKEYPBFUN     "PB-FUNC"
#define MsgKEYPORA      "PORA"
#define MsgKEYPO_RA      "PO/RA"
#define MsgKEYTEND      "TENDER"
#define MsgKEYCLEAR     "CLEAR"
#define MsgKEYFEED      "FEED"
#define MsgKEYMULT      "X"
#define MsgKEYSUBTOT    "SUBTOTAL"
#define MsgKEYPRICE     "PRICE"
#define MsgKEYPRICEN    "PRICE#"
#define MsgKEYPRICE1    "PRICE1"
#define MsgKEYPRICE2    "PRICE2"
#define MsgKEYPRICE3    "PRICE3"
#define MsgKEYPRICE4    "PRICE4"
#define MsgKEYSHIFT     "SHIFT"
#define MsgKEYDATE      "DATE"
#define MsgKEYWEIGHT    "WEIGHT"
#define MsgKEYCLERKN    "CLERK#"
#define MsgKEYDEPT      "DEPT~"
#define MsgKEYDEPTNo    "DEPT#"
#define MsgKEYPLUNo     "PLU#"
#define MsgKEYDRAW      "OPEN-DRAW"
#define MsgKEYMEMO      "MODIFIER"
#define MsgKEYCLERK     "CLERK*"
#define MsgKEYPLUDIR    "PLU~"
#define MsgKEYLOCK      "MODE KEY"
#define MsgKEYDRAWFUN   "DRAW FUNC*"
#define MsgKEYSALPN     "SALPER#"
#define MsgKEYSALP      "SALPER"
#define MsgKEYDOT       "'.'"
#define MsgKEYZERO2     "'00'"
#define MsgKEYNUMBER    "0~9"
#define MsgKEYSUSPEND   "HOLD"
#define MsgFUNCLOOK1    "FUNC LOOK1"
#define MsgFUNCLOOK2    "FUNC LOOK2"
#define MsgMODELOCK     "MODE KEY"
#define MsgVIPLOGIN     "ACCOUNT LOGIN"
#define MsgINPUTNUM     "INPUT CODE"
#define MsgCUSTOMER    "CUSTOMER"
#define MsgKEYNULL      "(OTHERS)"

#define MsgRHEADER      "Header*"
#define MsgRTRAILER     "Trail*"
#define MsgKEYBOARD     "Keyboard*"
#define MsgSYSFLAGS     "System*"
#define MsgSETDATE      "Datetime*"

//...........................................
#define MsgCONFIRM      "CONFIRM"
#define MsgNET          "NET-AMT"  // "����",
#define VIPLOGOUT       "ACCOUNT LOGOUT"
#define VIPTOTAL        "AMOUNT"
#define VIPTOTALA       "SUM-AMOUNT"
#define DECVIPPOINT     "DEC."//���ȱ���Ϊ4
#define ADDVIPPOINT     "ADD."//���ȱ���Ϊ4
#define INPUTVIPNAME    "NAME:"
#define PRINTKEYBOARD   "PRINT KEYBOARD"
//...........................................
#define MESSALLLOG         "LOG BY REC.NO"
#define MESSDATERANGE     "LOG BY DATE"
#define MESSVIPLOG        "ACCOUNT LOG"
#define MESSPRNCASH       "PRINT CASH"		//"��ӡ�����¼"
#define MESSPRNDEPART     "PRINT DEPART"	//"��ӡ�����¼"
#define MESSPRNPLU        "PRINT PLU"		//"��ӡ��Ʒ��¼"
#define MESSPRNDISCOUNT   "PRINT DISCOUNT"	//"��ӡ�ۿۼӳ�"
#define MESSPRNRAPO       "PRINT RA/PO"		//"��ӡ�����"
#define MESSPRNCORRECT    "PRINT CORRECT"	//"��ӡ��������"
#define MESSPRNCANCEL     "PRINT CANCEL"   //"��ӡ����ȡ��"
#define MESSPRNNOSALE     "PRINT NOSALE"	//"��ӡ������"

#define MESSALLCASH		  "ALL OF CASH"		//"ȫ�����ʽ"
#define MESSSELCASH		  "ONE OF CASH"		//"ѡ�񸶿ʽ"
#define MESSALLDEPT		  "ALL OF DEPT"		//"��ӡȫ������"
#define MESSSELDEPT		  "ONE OF DEPT"		//"ѡ��һ������"
#define MESSALLPLU		  "ALL OF PLU"		//"��ӡȫ����Ʒ"
#define MESSSELPLU		  "ONE OF PLU"		//"ѡ��һ����Ʒ"
//........................................
//ccr2016-03-15>>>>������̺�>>>>>
#define MESSMACRO         "MACRO"//  "�궨��"
//....ListItems��ʾ��Ϣ....................................
#define It_MGITEMS      "MG FUNCTION"
#define It_SELEFUNC     "KEY FUNCTION"
#define It_SELEITEM     "SELECT ITEM"
#define It_SELEKEYTYPE  "K.BOARD TYPE"
#define It_SELETEST     "SELECT ITEM"
#define It_SELELOG      "SELECT LOG"
#define It_SELETEND     "SELECT TYPE"
#define It_SELEDEPT     "SELECT DEPT"
#define It_SELEPLU      "SELECT PLU"
#define It_SELEMODI     "SELECT MODI."
#define It_SELEREPORT   "PRINT REPORT"
#define It_SELEPOINT    "SELECT POINT"// С��λ��"
#define It_SELEEJ       " EJ      "
//.........................................................
#define MESSRAMVAR      "VARIABLE"
//.........................................................
#define PLUNUMBER           "RECORDE COUNT:"
#define PLURANDOMSIZE     	"SIZE OF CODE:"
#define PLUNAMESIZE			"SIZE OF NAME:"
#define PLUPRICESIZE        "SIZE OF PRICE:"
#define PLUPRICELEVEL       "ACCOUNT PRICE:"
#define PLUCOSTSIZE         "SIZE OF COST:"
#define PLUINVENTSIZE       "SIZE OF STOCK:"
#define PLUREPQTYSIZE       "SIZE OF REP-QTY:"
#define PLUREPAMTSIZE       "SIZE OF REP-AMT:"
#define PLUREPDISCSIZE      "SIZE OF REP-DISC:"
#define PLUREPCOSTSIZE      "SIZE OF REP-COST:"
//.........................................................
#define POINTTYPE           "POINTS"
#define POINTTYPE1          "1.000,00"  //��λС��
#define POINTTYPE2          "1,000.00"  //��λС��
#define POINTTYPE3          "   1.000"
#define POINTTYPE4          "   1,000"
#define POINTTYPE5          "1.000,000"  //��λС��
#define POINTTYPE6          "1,000.000"  //��λС��
//#define POINTTYPE7          "1.000,0"  //һλС��
//#define POINTTYPE8          "1,000.0"  //һλС��
//.......................................................
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))//ccr2016-10-25>>>>EJ
#define MESSEJMESSAGES      "ABOUT EJ"    //MsgEJMESSAGES
#define MESSEJALLEJ         "ALL OF EJ"
#define MESSEJDATERANGE     "EJ BY DATE"
#define MESSEJRECEIPT       "EJ OF RECEIPT"
#define MESSEJXREPORT       "EJ OF X-REPORT"
#define MESSEJZREPORT       "EJ OF Z-REPORT"
#define MESSEJCLERK         "EJ OF CLERK"
#endif
//.......................................................
#define DATETYPE        "FORMAT "
#define DDMMYYYY        "DDMMYYYY"
#define MMDDYYYY        "MMDDYYYY"
#define YYYYMMDD        "YYYYMMDD"
//.......................................................
#define XUPDATEBIOS     "Can't Update \nfirmware by USB"
//ccr2016-06-22..........................................
#if defined(CASE_QRCODE)
#define MESSWXPAY       "OK WX-PAY"
#endif

#define SENDLOGAUTO     "SEND AUTO:"
#define DAYSFORLOG      "DAYS FOR SEND:"
#define ACKMUSTNEED     "ACK NEEDED:"

#define CSV_TITLE       "CAPTION,QUANTITY,AMOUNT\r\n"

//ccr2017-01-10>>>>>>>>>>>>>>>>>>>>>>>>>
#define Msg_NOSTOCK     "NO STOCK FIELD"
#define Msg_DISPSTOCK   "DISPLAY/PRINT?"
//ccr2017-01-10<<<<<<<<<<<<<<<<<<<<<<<<<<

#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))//ccr2016-10-25>>>>EJ
#define Msg_FORMAT      "ERASE EJ"
#define Msg_FORMATED    "ERASED"
#define Msg_RECALLEJ    "RECALL EJ"
#define Msg_EJNOTEMPTY  "EJ NOT EMPTY"

#define Msg_ECRDATEltEJ "ECR DATE < EJ"


//#define MESSEJMESSAGES      "ABOUT EJ"    //MsgEJMESSAGES
//#define MESSEJALLEJ         "ALL OF EJ"
//#define MESSEJDATERANGE     "EJ BY DATE"
//#define MESSEJRECEIPT       "EJ OF RECEIPT"
//#define MESSEJXREPORT       "EJ OF X-REPORT"
//#define MESSEJZREPORT       "EJ OF Z-REPORT"
//#define MESSEJCLERK         "EJ OF CLERK"

#endif
#define Msg_MANAGEMENT "MANAGEMENT LIST "

#endif
