// include APPL.h after KING.h================================
#ifndef APPL_H
#define APPL_H

#if defined(DEBUGBYPC)
    #pragma option -a1
#else
    #pragma pack(1)
#endif

#if defined(CASE_PERU)
#define TEND_PREFIX     //ccr2016-08-08ֻ�ڽ���ʱ��ӡ����ǰ׺����
#endif

#define ApplVarInSRAM       0   //=1,��ApplVarֱ�ӷ��䵽SRAM��;
								//=0,��ApplVar������MCU-RAM��,����ʱ�ٽ�����ת����SRAM��

#define YEARFrDEC 2000      //RTC���꿪ʼ���
#define YEARFrHEX 0x2000    //RTC���꿪ʼ���

#define PLUCODE_X   1       //ccr2014-09-05 ��X������,��������ָ����PLU����,����ָ�������µĵ�Ʒ����
#define PLU_X_IDX   3       //ccr2014-09-05 PLU�������

#define FLOW_IN_EXTRAM		0	//=1,�洢��ˮ�Ŀռ�λ�������ļ���ĩβ;=0,ʹ��flash�洢��ˮ

#define ADDR_EXTRAM	0x64000000	//SRAM�ĵ�ַ����,RAM for application from ADDR_EXTRAM

#define		FLASH1SIZE		0x100000
#define		FLASH2SIZE		0x100000
#define		FLASHTOTAL		(FLASH1SIZE+FLASH2SIZE)


#if defined(STM32F10X_HD)    //���STM32F103MCU��MCU���޵籣����RAM��
#define     DOWN_GR_SIZE    0x1000  //����ͼƬ��С������4K�����û��Զ���ͼƬ
#define		SRAMSIZE	    (0x40000-DOWN_GR_SIZE)//����4K�����û��Զ���ͼƬ
#define     DOWN_GR_ADDR    (ADDR_EXTRAM+SRAMSIZE)//����ͼƬ���λ�ã�ʹ����չ���ⲿRAM

#define     MCU_RAM_SIZE    0x10000

#else

#define     DOWN_GR_SIZE    0x1000  //����ͼƬ��С��MCU�ڲ�4K RAM�����û��Զ���ͼƬ
#define		SRAMSIZE		0x40000
#define     DOWN_GR_ADDR    BKPSRAM_BASE//����ͼƬ���λ�ã�ʹ��MCU�ڲ�4K RAM
#define     MCU_RAM_SIZE    0x20000

#endif

#if defined(CASE_QRCODE)
#define MAX_QRCODE     50  //��ά�볤��
#endif

//#if FLASH_AppRAM
//#define ApplVar.SIZE_EXTRAM     0x100000    //size of flash
//#else
//#define ApplVar.SIZE_EXTRAM     ((EXTRAMN & 0x0f) * SRAMSIZE)     //��չRAM��С
//#endif

#if FLOW_IN_EXTRAM
#define SIZE_FLOWRAM    0           //������ˮ�ؼ�
#else
#define SIZE_FLOWRAM    0           //������ˮ�ؼ�
#endif

#define HOR_REPORT		1			//ccr100702 �����з�ʽ��ӡ����͵�Ʒ����. //

#define YN		0x17    //ʹ��YN-��ʾ:0Ϊtrue,1Ϊfalse;

#define BARCUSTOMER	0		// ccr 050307 ʹ�������Ա����  //

// command index for upload
#define UOK		0
#define UCA		1
#define UEN		2
#define UER		3

#define  PRNONOFF	205

/* if WWATCH is 1 then each plu can have 2 dept selections */
#define WWATCH	    0
#define MAXKEYB		64
#define ENTRYSIZE   80

#define ASECOND		1000
#define DELAY485	2		// delay times befor operate RTS
#define CCDBUFMAX 	254
#define PCBUFMAX	1024 //>=256 must

//////////////////////////////////////////
#define CAPWIDTH	9
#define dCAPWIDTH	9
#define mCAPWIDTH	9
#define lCAPWIDTH	4
#define tCAPWIDTH	10
#define MESSWIDTH	17
#define REPWIDTH	17
//#define SHEADWIDTH	35
#define SHEADWIDTH	PRTLEN

#define GRASETMAX	4
#define GRAFESTMAX	10
#define GRAPHMAX	22

//ccr2016-03-15>>>>������̺�>>>>>
#define MACRONAME       15  //ÿ��������Ƴ���
//#define KEYMACROMAX     20  //���Զ���20�����̺�
#define KEYS1MACRO      20  //ÿ�����̺���Զ���20���ܼ�
//ccr2016-03-15<<<<<<<<<<<<<<<<<<<



//Flags for MyFlags==========================================================
#define RGREVIEW   BIT0	/* =1,��ʾ����ģʽ��ִ���˲������۵Ĺ��� */
#define PLUPACK		BIT1	/* Set when Mix/Match mode for PLU sales */
#define PLUDISC		BIT2	/* Set when Mix/Match mode for PLU sales */
#define PLUOFF		(PLUDISC | PLUPACK)	/* Set if Mix/Match mode for PLU sales */
#define SETCONFIRM	BIT3	/* Set when must confirm setup */
#define HANZIMODE	BIT4	// ECR is in the hanzi input mode
#define PWDMODE		BIT5	// SubTotal flag
#define LOCKPLU		BIT6	// =0,lock price,=1 lock inv
#define ZREPORT		BIT7	//=1,can't change datetime;
#define CLSSCREEN	BIT8	//=1,must clean the screen befor display any message
#define PRNONPB		BIT9    //=0,open printer;=1, close printer for PBFunction
#define PRNTRAI		BIT10	//Print the trail when out of setup
#define ENPRINTER   BIT11   //=0,open printer;=1, close printer
#define ENSLIPPB    BIT12   //enable slip in pb	(open table)
#define DOTCHANGED  BIT13  //ccr2016-05-28��ʾС���������ת��
#define CONFIGECR   BIT14   //�޸����տ�������ò���

#define LOCKMODE	BIT15	//ECR Locked
#define MENUMODE    BIT16   //��ǰ��Ļ����ʾ���ǲ˵�
#define KEYFROMHOST BIT17   //�д�������������ⰴ��
#define PRNHEADMUST BIT18   //�л���RG״̬ʱ,����Ԥ��ӡƱͷ

#define NEWFIRMWARE BIT19   //ccr2017-11-30 �������°汾����
//----------------setup index definitions------------------------

#define SETUPMG		0xf000

//#define SETFIXCAP   	(SETUPMAX+1) 	//(SETZPWD+1) 		// fixed captions //
//#define SETERRMSG   	(SETFIXCAP+1)		// system & error message //
//#define SETWEEKCAP      (SETERRMSG+1)		// day of week captions //
//#define SETMONTHCAP     (SETWEEKCAP+1)	// month captions //
#define SETKEYMASK  	(SETUPMAX+1)	// keyswitch disable //

//ccr chipcard>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define MGSETUPIC		(SETKEYMASK+100)
#define SETCLEARIC		MGSETUPIC
#define SETINITIC		(SETCLEARIC+1)
#define SETCHARGIC		(SETINITIC+1)
#define SETCHIPPOINT	(SETCHARGIC+1)
//ccr chipcard<<<<<���������������<<<<<<<<<<<<<<<<<<<<<<<


//---------------- end of setup index definitions---------------------

#define MAXPWD		(6+1)	//max length of password is 6(MAXPWD-1)
#define	PWDFOR		0x0f00		//Must input password for new mode


#define SYSFLAGS    64

#define FIRMKEYS    16
//////////////////////////////////////////////
#define ENDREC	    0
#define PROGID	    1
#define SYSFLG	    2
#define START	    3
#define RCONFIG     4
#define RDAY	    5
#define RMONTH	    6
#define RZONE	    7
#define RTOTAL	    8
#define RDEBET	    9
#define LDEBET	    10		/* Debet List Record */

#define KEY0	    11
#define KEY32	    12
#define KEY64	    13
#define KEY96	    14
#define FIRM	    19
#define MNGR	    20
#define RREP1	    21
#define RREP2	    22
#define RREP3	    23
#define RREP4	    24
#define RREP5	    25

#define RCAP1	    30
#define RCAP2	    31
#define RCAP3	    32
#define RCAP4	    33
#define RCAP5	    34
#define RCAP6	    35

#define RMES1	    40
#define RMES2	    41
#define RMES3	    42
#define RMES4	    43
#define RMES5	    44
#define RMES6	    45
#define RMES7	    46
#define RMES8	    47
#define RMES9	    48
#define RMES10	    49

#define RDAYCAP     60
#define RMONTHCAP   62

#define REPCAP1     65
#define REPCAP2     66
#define REPCAP3     67

#define RHEAD1	    70
#define RHEAD2	    71
#define RHEAD3	    72

#define RTRAIL1     73
#define RTRAIL2     74
#define RTRAIL3     75

#define RSLIPH1     76
#define RSLIPH2     77
#define RSLIPH3     78

#define PROMO   	80

#define PBTRAIL     90
#define LOGO1		91		/* logo for old controller */
#if INDO == 1
    #define FISCDMP 	92		/* fiscal dump record */
#else
    #define CCHAR		92		/* Chinese Character record */
#endif
#define OPTIONS 	93		/* NEW Options record */
#define CHIPCARDSET	94		//ccr chipcard

//ccr2016-05-31>>>>>>>>>>>>>>>>>>>
#if defined(CASE_INDIA)
#define UPDATEECRNO 95     //�����տ����
#define UPDATERECNO 96      //�����վݺ�
#endif
//ccr2016-05-31<<<<<<<<<<<<<<<<<<<

#define REMOTESETTIME	98

#define REMOTE_ID   99
//.............................................

#define UPDPLU	    100
#define ADDPLU	    101
#define DELPLU	    102
#define MERGEPLU	103		/* Merge PLU file and Update File */
#define REMOVEPLU	104		/* Remove Deleted PLU from file */
#define REMMER		105		/* Merge and Remove */
#define TESTPLU 	106		/* TEST Plu file */
#define REPPLU		107		/* TEST and Repair PLU file */


//ccr2016-02-27 ������<300������ProcessKeyʶ���������(����Ϊ����)
#define CORREC	    300			//Correct

#define xLASTONE    (CORREC+1)        //"����    "//ccr2016-07-14
#define xBEFOR      (CORREC+2)        //"ȡ��    "//ccr2016-07-14
#define xREFUND     (CORREC+3)        //"�˻�    "
#define xCANCEL     (CORREC+4)        //"ȡ������"

/* ���¸��ù������Ӧ�ĸ��ù��ܱ���̶�,���ñ�� */
#define xRECEIPT    (CORREC+4)  /* �̶�Ϊȡ������(��Ҫȷ��) */
#define xSUSPEND    (CORREC+5)  /* �̶�Ϊ�������=ȡ������(����Ҫȷ��) */

#define CURR	    400			//Currency
#define DISC	    500			//Discount
/* �����ۿ۹������Ӧ���ۿ۹��ܱ���̶�,���ñ�� */
#define DISC_PERINC	(DISC+1)      //Ϊ+%�ۿ�
#define DISC_PERDEC	(DISC+2)      //Ϊ-%�ۿ�
#define DISC_NETINC	(DISC+3)      //Ϊ���ӳ�
#define DISC_NETDEC	(DISC+4)      //Ϊ����ۿ�
//ccr20130806 for SubDisc>>>>>>>>>>
#define DISC_SUB_PERINC	(DISC+5)      //ΪС��+%�ۿ�
#define DISC_SUB_PERDEC	(DISC+6)      //ΪС��-%�ۿ�
#define DISC_SUB_NETINC	(DISC+7)      //ΪС�ƽ��ӳ�
#define DISC_SUB_NETDEC	(DISC+8)      //ΪС�ƽ���ۿ�
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


#define DRAW	    600			//
#define PBF	    	700			//
#define PORA	    800			//801-CashOut  802-Cash IN   803-CashOut2   804-CashIn2
                                //
#define TEND	    900			//901-Cash  902-   903-credit
#define TEND_CASH	901
#define TEND_CHECK  902           /* TEND 2 "֧Ʊ    "*/
#define TEND_VISA	903         //���ÿ�
#define TEND_COUPON 904         /* TEND 4 "����ȯ  "*/
#define TEND_CREDIT 905         //"����"
#define TEND_CHIPC  906         //
#define TEND_WXPAY  907         //΢��֧��
#define TEND_ALPAY  908         //֧����֧��

#define MODI	    1000
//ccr2016-02-27>>>>fixed functions 2000 - 2099
#define FIXED	    2000
#define CLEAR	    2000		//
#define RPF	    	2001		//Feed
#define JPF	    	2002		//feed
#define RON	    	2003		//
#define MULT	    2004		//X
#define SUB	    	2005		//Subtotal
#define NUMBER	    2006		//
#define ODRAW	    2007		//
#define PROFORMA    2008
//#define FUNC	    2009    	/* DITRON language 'F' key */
#define NPRICE	    2010		//Price
#define LEVEL1	    2011		//plu price  level1
#define LEVEL2	    2012		//plu price  level2
#define LEVEL3	    2013		//plu price  level3
#define LEVEL4	    2014		//plu price  level3
//ccr2016-02-27��������function look������
//PO,RA,Receipt Cancel, Refund, ���ʽ�ࣨCredit Card,Coupon...),�ۿۼӳ��࣬ �����๦�ܵ�Transfer��Combine
#define FUNCLOOK_KEYS  6       //ÿ��FUNCLOOK�а����Ĺ�������Ŀ
#define FUNCLOOK1   2015
#define FUNCLOOK2   2016
#define FUNCLOOKMAX (FUNCLOOK2-FUNCLOOK1+1)
//ccr2016-02-27<<<<<<<<
//
//ccr2016-09-13>>>>>>>>>>>>
#define CUSTOMER	2019    /* ����˿���Ϣ */
//ccr2016-09-13<<<<<<<<<<<<<

#define WEIGHT		2020	//cc 20070918

/*ccr2016-01-27>>>>>>>>>>>>>>>>>>>>>>
#define ARTLEVEL1   2021
#define ARTLEVEL2   2022
#define ARTLEVEL3   2023
#define ARTLEVEL4   2024
#define ARTLEVEL5   2025
#define ARTLEVEL6   2026
#define ARTLEVEL7   2027
#define ARTLEVEL8   2028
#define ARTLEVEL9   2029
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

#define LIST	    2030
#define BEEP	    2031
#define NEWRECEIPT  2032		/* issue receipt and start new */
#define KPGROUP     2033		/* if set disable single ticket on kp */
#define NUMBER1     2034		/* number entry on RJ/slip direct */
#define TAXST1	    2035		/* invert tax 1 and 2 for transaction */
#define TAXSA1	    2036		/* invert tax 1 and 2 for one item */
#define RELCARD     2037		/* release card for DEBET only */
#define NUMBER2     2038		/* same as NUMBER1 and Open Draw when no entry */
#define SALPERS     2039		/* Sales person selection key */
#define DISCARD     2040		/* Disable card for transaction */

#define TPNUMBER    2045		/* Tax Payer Number (invoice printing) */
#define PROFORMA1   2046		/* proforma invoice also print onjournal */
#define SUB1	    2047		/* Subtotal with Print */
//ccr2016-02-27 10��������>>>>
//#define MACROFUNC   2050
#define MACROFUNC1  2051
#define MACROFUNC2  2052
#define MACROFUNC3  2053
#define MACROFUNC4  2054
#define MACROFUNC5  2055
#define MACROFUNC6  2056
#define MACROFUNC7  2057
#define MACROFUNC8  2058
#define MACROFUNC9  2059
#define MACROFUNC10 2060
#define MACROFUNC11 2061
#define MACROFUNC12 2062
#define MACROFUNC13 2063
#define MACROFUNC14 2064
#define MACROFUNC15 2065
#define MACROFUNC16 2066
#define MACROFUNC17 2067
#define MACROFUNC18 2068
#define MACROFUNC19 2069
#define MACROFUNC20 2070
#define KEYMACROMAX  (MACROFUNC20-MACROFUNC1+1)//�궨����Ŀ
//ccr2016-02-27<<<<<<<<<<<<<<

#define SUSPEND 	2080		/* Suspend / Recall key �ҵ�*/
#define NFOLIO		2081		/* New Folio Key */
#define LEVEL		2082		/* PRICE LEVEL number key */
#define ARTLEVEL	2083		/* Article Level Number key */
#define PLUINQ		2084		/* Plu Inquiry key code */

#define SHIFT1		2090         // Depart Shift 1
#define DATETIME	2091
#define MODELOCK	2092
#define LOOKPLU		2093

#define VIPLOGIN      2094        // ��Ա��¼

#define FIXED_END   2099
//ccr2016-02-27 <<<fixed functions 2000 - 2099

#define SALPER		2100
#define TAX	    	2900
#define CLERK	    3000
#define OFFER		3100
#define GROUP	    4000        //ʵ�ʹ�����Ŀ��Ӧ����255
#define DEPT	    5000		//
#define PLU1	    10000		//PLU#
#define PLU3	    50000
#define AGREE		50000
#define BLOCKIC		50500		//ccr chipcard
#define PBTOT	    60000	 	/* 60001 to 65000 pb total info */


#define POINT		46		//.
#define ZERO2	    47		//00
#define NUM0		48
#define NUM1		49
#define NUM2		50
#define NUM3		51
#define NUM4		52
#define NUM5		53
#define NUM6		54
#define NUM7		55
#define NUM8		56
#define NUM9		57

/*======================================================================================================
    {CORREC+1   ,CORREC+4 ,0,"���Ĺ���"   ,"ȡ��\0����\0�˻�\0ȡ������"},
    {CURR       ,CURR+2   ,0,"���"        ,"��Ԫ\0��Ԫ\0�۱�"},
    {DISC+1     ,DISC+4   ,0,"�ۿ۹���"   ,"+%�ӳ�\0-%�ۿ�\0���ӳ�\0����ۿ�"},
    {DRAW+1     ,DRAW+7   ,0,"Ǯ�书��"   ,"������\0֧Ʊ\0���ÿ�\0����ȯ\0��ͨ��\0IC��\0С��"},
    {PBF+1      ,PBF+12   ,0,"��������"   ,"��̨����\0̨��\0�ݽ�\0ȷ��\0��ӡ��̨\0��ӡ�ʵ�\0ȡ��ȷ��\0����\0ת��\0����ת��\0����\0�ϲ�"},
    {PORA+1     ,PORA+2   ,0,"�������"   ,"����\0���"},
    {TEND+1     ,TEND+6   ,0,"���ʽ"   ,"�ֽ�\0���ÿ�\0����\0֧Ʊ\0����ȯ\0IC��"},
    {CLEAR      ,CLEAR    ,1,"���"       ,"���"},
    {JPF        ,JPF      ,1,"��ֽ"       ,"��ֽ"},
    {MULT       ,MULT     ,1,"����"       ,"X"},
    {SUB        ,SUB      ,1,"С��"       ,"С��"},
    {NPRICE     ,NPRICE+4 ,0,"�۸�"       ,"�۸�\0�۸�1\0�۸�2\0�۸�3\0�۸�4"},
    {SHIFT1     ,SHIFT1   ,0,"SHIFT"      ,"SHIFT"},
    {DATETIME   ,DATETIME ,1,"����"       ,"����"},
    {MODELOCK   ,MODELOCK ,1,"��ʽ��"     ,"��ʽ��"},
    {SALPER     ,SALPER   ,0,"ӪҵԱ"     ,"ӪҵԱ"},
    {CLERK      ,CLERK    ,0,"�տ�Ա"     ,"�տ�Ա"},
    {DEPT+1     ,DEPT+50  ,0,"����"       ,"*"},
    {DEPT       ,DEPT     ,0,"����#"     ,"����#"},
    {PLU1       ,PLU1     ,0,"��Ʒ"           ,"PLU"},
    {PLU1+1     ,PLU1+1000,0,"ֱ�ӵ�Ʒ"   ,"*"},
    {ARTLEVEL  ,ARTLEVEL  ,0,"��Ʒ���"   ,"��Ʒ���"},  //����ֱ�ӵ�Ʒ����ʱ�ķ���
    {ARTLEVEL1  ,ARTLEVEL9,0,"��Ʒ����"   ,"*"},  //����ֱ�ӵ�Ʒ����ʱ�ķ���
    {LOOKPLU    ,LOOKPLU  ,0,"��Ʒ��ѯ"       ,"PLU��ѯ"},
    {POINT      ,POINT+11 ,1,"����",      "��\0OO\0��\0��\0��\0��\0��\0��\0��\0��\0��\0��"},
    {ODRAW      ,ODRAW    ,0,"��Ǯ��"     ,"��Ǯ��"},
    {MODI       ,MODI     ,0,   "˵��",   "˵��"},
    {INPUTVATNO ,INPUTVATNO,0,   "��˰��",   "��˰��"},
    {NUMBER     ,NUMBER     ,0,   "����",   "����"},
    {USERINFO ,USERINFO ,0,"�û���Ϣ"   ,"�û���Ϣ"},
=============================================================================================================*/


#if CASE_GIADA3000
    #define cENTER     0x23
    #define cEXIT      0x17
    #define cSELECT    0x1d
    #define cDELETE    0x00
    #define cNEXT      0x0b	//17         //right arrow
    #define cRIGHT     cNEXT
    #define cLAST      0x05	//16         //left arrow
    #define cLEFT      cLAST
    #define cSHIFT     0x0d         //
    #define cCLEAR   	0x0c
    #define cDOWN      	cNEXT  // 11
    #define cUP         cLAST	// 12
    #define cCHANGEASC 0x01

#elif (defined(CASE_ER100) || defined(CASE_ER220))//ccr2016-07-26
    #define cENTER     0x22
    #define cEXIT      0x14
    #define cSELECT    0x1b
    #define cDELETE    0x01
    #define cNEXT      0x0d	//17         //right arrow
    #define cRIGHT     cNEXT
    #define cLAST      0x06	//16         //left arrow
    #define cLEFT      cLAST
    #define cSHIFT     0x03         //
    #define cCLEAR   	0x02
    #define cDOWN      	cNEXT  // 11
    #define cUP         cLAST	// 12
    #define cCHANGEASC 0x04

#elif CASE_ER520U
    #define cENTER     0x2F
    #define cEXIT      0x1D
    #define cSELECT    0x26
    #define cDELETE    0x2d
    #define cNEXT      0x13	//17         //right arrow
    #define cRIGHT     cNEXT
    #define cLAST      0x12	//16         //left arrow
    #define cLEFT      cLAST
    #define cSHIFT     0x05
    #define cCLEAR   	0x27
    #define cDOWN      	cNEXT  // 11
    #define cUP         cLAST	// 12
    #define cCHANGEASC 0x01//

#elif CASE_ER260
    #define cENTER     0x27
    #define cEXIT      0x17
    #define cSELECT    0x1F
    #define cDELETE    0x00
    #define cNEXT      0x0f	//17         //right arrow
    #define cRIGHT     cNEXT
    #define cLAST      0x07	//16         //left arrow
    #define cLEFT      cLAST
    #define cSHIFT     0x01
    #define cCLEAR   	0x20
    #define cDOWN      	cNEXT  // 11
    #define cUP         cLAST	// 12
    #define cCHANGEASC  0x06//

#else//MACRO5150X
    #define cENTER      0x36
    #define cEXIT       0x27
    #define cSELECT     0x2e
    #define cDELETE     0x32
    #define cNEXT       0x1f         //right arrow
    #define cRIGHT      cNEXT
    #define cLAST       0x1e         //left arrow
    #define cLEFT       cLAST
    #define cSHIFT      0x13
    #define cCLEAR      0x28
    #define cDOWN       0x17
    #define cUP         0x16
    #define cCHANGEASC 0x08
#endif

#define cASCA        0x34
#define cASCB        0x35
#define cASCC        0x2C
#define cASCD        0x2D
#define cASCE        0x24
#define cASCF        0x25
#define cASCG        0x1C
#define cASCH        0x1D
#define cASCI        0x14
#define cASCJ        0x15
#define cASCK        0x0C
#define cASCL        0x0D
#define cASCM        0x04
#define cASCN        0x05
#define cASCO        0x06
#define cASCP        0x07
#define cASCQ        0x0E
#define cASCR        0x0F
#define cASCS        0x01
#define cASCT        0x02
#define cASCU        0x03
#define cASCV        0x0a
#define cASCW        0x0b
#define cASCX        0x10
#define cASCY        0x11
#define cASCZ        0x12
#define cASCFLASH	 0x18
#define cASCAT		 0x20

#define ENTER		TEND+1
#define SELECT		SUB


//===firmkey can be use for table FirmKeys==============================

#define ID_CLEAR	0 	//firmkey clear. It must be the first byte!!!!!!.
#define ID_xPRINT 1 // open or close printer ,lyq added 20040227
//#define ID_LOOKPLU	1 	//Set Time
#define ID_DATE		2 	//Display Date
#define ID_RIGHT	3
#define ID_SELECT	4 	//programming Type key,//�˵�����ʱ���¹���һҳ
#define ID_LEFT		5
#define ID_ENTER	6 	//programming Enter
#define ID_PRGOPT	7 	//Programming option invert
#define ID_SYSREP	8 	//system report trigger
#define ID_UP		8
#define ID_DOWN		9   //�˵����¹���һҳ
#define ID_DUMP		10
#define ID_xDEPT	11	// �л�����
#define ID_xINPUT	12	// �л����뷽��,��Ӣ�İ汾��,ȡ��ID_xASCII
#define ID_LOCK		13	// Mode lock
#define ID_CANCEL	14	//
#define ID_RJFEED	15	// feed paper anytime
#define ID_xASCII   ID_xDEPT   //���İ汾��,��������ASCII����Ĵ�Сд
#define ID_DELETE   ID_RJFEED   //�ڱ༭����ʱ,����ɾ������


#if (CASE_GIADA3000)

    #define fCLEAR		0x0c			//35 is the scan code.
    #define fDATE		0xff			//Set date
    #define fOCPRINTER	0x02			//open or close printer ,lyq added 20040227
    #define fLOCK		0x06			//Mode lock
    #define fREPORT		0xff			// ReportList Trigger
    #define fPRGTYPE	0x1d          // programming Type key
    #define fPRGNUM		0xff         	// Programming number
    #define fPRGENTER	0x23          // programming Enter
    #define fPRGOPT		0xff         	// Programming option invert
    #define fSYSREP		0xff         // system report trigger
    #define fHARDTEST	0xff         // Machine test key
    #define fDUMP		0xff         // Dump Program key
    #define fSHIFT1		0xff         // Alfa Shift 1 (xchange ASCII<->QuWei)
    #define fSHIFT2		0x0d         // Alfa Shift 2
    #define fSHIFT3		0xff        // Alfa Shift 3
    #define fCANCEL     0x17			//cancel,EXIT
    #define fNULL		0xff		//
    #define fDOWN		11         //  Dump Program key Left or Down
    #define fRJFEED		0x00		//feed paper anytime
    #define fBACKSPACE	fRJFEED		//�����ַ�����ʱ,������ɾ�ַ��İ���
    #define fPRGUP	    5         	//     Programming ����ѡ����Ŀ
#if defined(CASE_FORHANZI)
    #define fSHIFTDEPT	cCHANGEASC   // Alfa Shift 1 (xchange ASCII<->QuWei)
    #define fSHIFTHZ_ASC	cSHIFT
#else
    #define fSHIFTDEPT	0xff   // Alfa Shift 1 (xchange ASCII<->QuWei)
    #define fSHIFTHZ_ASC	cSHIFT  //  �л����뷨
#endif
#elif (defined(CASE_ER220)||defined(CASE_ER100))
    #define fCLEAR		cCLEAR			//    35 is the scan code.
    #define fRJFEED	    01			//    Set date
    #define fOCPRINTER	0x07			//    open or close printer ,lyq added 20040227
    #define fLOCK		0x00			//    Mode lock
    #define fREPORT	    0xff			//     ReportList Trigger
    #define fPRGTYPE	cSELECT          //     programming Type key
    #define fPRGNUM	    0xff         	//     Programming number
    #define fPRGENTER	cENTER          //     programming Enter
    #define fPRGOPT	    0xff         	//     Programming option invert
    #define fSYSREP	    0xff         //     system report trigger
    #define fHARDTEST	0xff         //     Machine test key
    #define fDUMP		0xff         //     Dump Program key

#if defined(CASE_FORHANZI)
    #define fSHIFTDEPT	04          //     Alfa Shift 1 (xchange ASCII<->QuWei)
#else
    #define fSHIFTDEPT	0xff   // Alfa Shift 1 (xchange ASCII<->QuWei)
#endif

    #define fSHIFTHZ_ASC	cSHIFT      //  �л����뷨
    #define fSHIFT3	    0xff        //     Alfa Shift 3
    #define fCANCEL    cEXIT			//    cancel,EXIT
    #define fNULL		0xff		//
    #define fDATE		0xff		//    feed paper anytime    */

#elif CASE_ER520U
    #define fCLEAR		cCLEAR			//    35 is the scan code.
    #define fRJFEED	    00			//    Set date
    #define fOCPRINTER	0x0b			//    open or close printer ,lyq added 20040227
    #define fLOCK		0xff			//    Mode lock
    #define fREPORT	    0xff			//     ReportList Trigger
    #define fPRGTYPE	cSELECT          //     programming Type key
    #define fPRGNUM	    0xff         	//     Programming number
    #define fPRGENTER	cENTER          //     programming Enter
    #define fPRGOPT	    0xff         	//     Programming option invert
    #define fSYSREP	    0xff         //     system report trigger
    #define fHARDTEST	0xff         //     Machine test key
    #define fDUMP		0xff         //     Dump Program key
    #define fSHIFTDEPT	    cCHANGEASC         //     Alfa Shift 1 (xchange ASCII<->QuWei)
    #define fSHIFTHZ_ASC	    cSHIFT
    #define fSHIFT3	    0xff        //     Alfa Shift 3
    #define fCANCEL     cEXIT			//    cancel,EXIT
    #define fNULL		0xff		//
    #define fDATE		0xff		//    feed paper anytime    */

#elif (CASE_ER260)
    #define fCLEAR		0x20			//35 is the scan code.
    #define fDATE		0xff			//Set date
    #define fOCPRINTER	0x10			//open or close printer ,lyq added 20040227
    #define fLOCK		0x08			//Mode lock
    #define fREPORT		0xff			// ReportList Trigger
    #define fPRGTYPE	0x1f          // programming Type key
    #define fPRGNUM		0xff         	// Programming number
    #define fPRGENTER	0x27          // programming Enter
    #define fPRGOPT		0xff         	// Programming option invert
    #define fSYSREP		0xff         // system report trigger
    #define fHARDTEST	0xff         // Machine test key
    #define fDUMP		0xff         // Dump Program key
#if defined(CASE_FORHANZI)
    #define fSHIFTDEPT	cCHANGEASC   // Alfa Shift 1 (xchange ASCII<->QuWei)
    #define fSHIFTHZ_ASC	cSHIFT
#else
    #define fSHIFTDEPT	0xff   // Alfa Shift 1 (xchange ASCII<->QuWei)
    #define fSHIFTHZ_ASC	cSHIFT
#endif
    #define fSHIFT3		0xff        // Alfa Shift 3
    #define fCANCEL    	0x17			//cancel,EXIT
    #define fNULL		0xff		//
    #define fRJFEED		0x00		//feed paper anytime

#else//MACRO5150X
    #define fCLEAR		0x28			//35 is the scan code.
    #define fDATE		0x02			//Set date
    #define fOCPRINTER	0x01			//open or close printer ,lyq added 20040227
    #define fLOCK		0x08			//Mode lock
    #define fREPORT		0xff			// ReportList Trigger
    #define fPRGTYPE		0x2e          // programming Type key
    #define fPRGNUM		0xff         	// Programming number
    #define fPRGENTER	0x36          // programming Enter
    #define fPRGOPT		0xff         	// Programming option invert
    #define fSYSREP		0xff         // system report trigger
    #define fHARDTEST	0xff         // Machine test key
    #define fDUMP		0xff         // Dump Program key
    #define fSHIFTDEPT		0x05         // Alfa Shift 1 (xchange ASCII<->QuWei)
    #define fSHIFTHZ_ASC		0x13
    #define fSHIFT3		0xff        // Alfa Shift 3
    #define fCANCEL     	0x27			//cancel,EXIT
    #define fNULL		0xff		//
    #define fRJFEED		0x00		//feed paper anytime

#endif

#define fTEST		fLOCK			//     �������԰��� //


/**************************************************************************/


#define KPTypeNum			(6+2)
#define SPTypeNum			(5)		//lyq added for slip 20040322

#define LogoSize			0			//logo size in bytes for download
/****************** Definitions for TAXTABLE ***********/

#if defined(CASE_INDONESIA)//ccr2015-08-20>>>>>>>
#define tQTY    0
#define tAMT    6
#define tCOST   5
#else
#define tQTY    0
#define tAMT    4
#define tCOST   3
#endif//ccr2015-08-20<<<<<<<<<<<<
#define taxNumber			3 	    /* number of tax itemizers */
#define taxCapSize			8 	    /* caption length max 12 */
#define taxTotalOffSet		(taxCapSize+4)    /* Start of totalizer in record */
#define taxRecordSize		(taxTotalOffSet+2*(tQTY+tAMT+tCOST+1))     /* size of 1 tax record *///ccr2015-08-20
//    struct  REPSIZE Size[REPDEFMAX]      /* Totalizer lay-out for function */
// �ռ�����е�*2��ʾ����������ͳ�Ƽ�¼:{0x03, (tQTY+tAMT+tCOST+1), 0, tQTY, tAMT, 0, 0, tCOST}
// 0x03��ʾͳ���պ�������(�ռ�¼���ܼ�¼)
// +1��ʾÿ��ͳ�Ƶĵ�һ���ֽ�Ϊ��־��,�˱�־����QTYͳ�ƺϲ���һ��,��ΪQty.sign,
// �μ�WrtieTotal:WriteRam(&ApplVar.Total.Qty.Sign, 1);
// Qty.Sign:BIT2:=0,��ʾͳ��������0;=1,��ʾΪ�ۼ�����
//          BIT4:=1,��ʾDiscͳ������Ϊ����
//          BIT5:=1,��ʾCostͳ������Ϊ����
//          BIT6:=1,��ʾAmtͳ������Ϊ����
//�ڴ�ӡ��Z����ִ������ʱ,ֻ��ͳ�Ƽ�¼�ĵ�һ���ֽ���0


/**************** Definitions Used for Clerk CLERKTABLE **************************/

#define clrkNumber			5   //ccr2015-08-20
#define clrkCapSize			10 	    /* caption length max 12 *///ccr2015-08-20
#define clrkRecordSize		(clrkCapSize+1+3)      /* size of 1 Clerk record */

/**************** Definitions Used for SALPERTABLE **************************/
#define salNumber			0  //ccr2015-08-20
#define salCapSize			10  /* caption length max 24 *///ccr2015-08-20
#define salRecordSize		(salCapSize+1)/* size of 1 Salesperson record *///ccr2015-08-20

/**************** Definitions Used for Time Zone ZONETABLE **************************/

#define zoneNumber			12
//    WORD    Start[24]	    /* start of zone max 24 */

/**************** Definitions Used for Day of Week DAYTABLE **************************/
#define dayNumber			7

/**************** Definitions Used for MONTHTABLE **************************/
/* When DEBET is set Months are used for SalesPerson */
#define monthNumber			12

/****************** Definitions for  PORTTABLE *************************/
#define portNumber			2	    /* number of PORT */
#define portCapSize			8	    /* caption length max 24 */
#define portRecordSize		0  /* size of 1 PORTRecord */

#if (CASE_EPOS)
#define portTypeNum			7	   //ccr2016-12-14 ExtPrinter����
#else
#define portTypeNum			6	   //ccr2016-12-14 ExtPrinter����
#endif
#define portProNum         portTypeNum	   // lyq added 20040322
/****************** Definitions for  OFFTABLE *************************/
#if defined(DEBUGBYPC)
#define offNumber			(50)//ccr081208 50	    /* number of OFF */
#else
#define offNumber			(1)//ccr081208 50	    /* number of OFF */
#endif
#define offCapSize			16	    /* caption length max 24 */
#define offPriUSize			3		/* Bytes for OFF Price u  */
#define offRecordSize		(offCapSize+1+2*4+1+1+offPriUSize+4)     /* size of 1 OFF record */


/****************** Definitions for  GROUPTABLE *************************/
#if defined(CASE_INDONESIA)//ccr2015-08-20>>>>>>>
#define gCC     2
#define gQTY    3
#define gAMT    6
#define gRET    5
#define gDISC   4
#define gCOST   0
#else
#define gCC     2
#define gQTY    3
#define gAMT    4
#define gRET    4
#define gDISC   3
#define gCOST   0
#endif//ccr2015-08-20<<<<<<<<<<<<
#define grpNumber			10	    /* number of Groups, max 250*/
#define grpCapSize			16	    /* caption length max 24 */
#define grpTotalOffSet		(grpCapSize+2)    /* Start of totalizer in record */
#define grpRecordSize		(grpTotalOffSet+2*(gCC+gQTY+gAMT+gRET+gDISC+gCOST+1))     /* size of 1 Group record */
//    struct  REPSIZE Size[REPDEFMAX]      /* Totalizer lay-out for Groups */


/**************** Definitions for   for the DEPTTABLE ******************/
#if defined(CASE_INDONESIA)//ccr2015-08-20>>>>>>>
#define dCC     2
#define dQTY    4
#define dAMT    6
#define dRET    0
#define dDISC   5
#define dCOST   0
#else
#define dCC     2
#define dQTY    3
#define dAMT    4
#define dRET    0
#define dDISC   4
#define dCOST   0
#endif//ccr2015-08-20<<<<<<<<<<<<

#define depNumber			60	    /* number of Departments */
#define depRandomSize		0      	/* max random size is 7 bytes */
#define depCapSize			16	    /* caption length max 24 */
#if defined(CASE_INDONESIA)
#define depPriceSize		5		/* max size is 4 */
#define depPriMaxSize		5		/* max size is 4 *///ccr2015-08-20
#else
#define depPriceSize		4		/* max size is 4 */
#define depPriMaxSize		4		/* max size is 4 *///ccr2015-08-20
#endif
#define depTotalOffSet		(depRandomSize+depCapSize+depPriceSize+depPriMaxSize+5+(taxNumber!=0)*1)    	/* Start of totalizer in record */
#define depRecordSize		(depTotalOffSet+2*(dCC+dQTY+dAMT+dRET+dDISC+dCOST+1))     	/* size of 1 Department record */
//    struct  REPSIZE Size[REPDEFMAX]      	/* Totalizer lay-out for dept */


/****************** Definitions for  PLUTABLE *************************/
#if defined(CASE_INDONESIA)//ccr2015-08-20>>>>>>>
#define pCC     0
#define pQTY    3
#define pAMT    6
#define pRET    0
#define pDISC   5
#define pCOST   6
#else
#define pCC     0
#define pQTY    3
#define pAMT    4
#define pRET    0
#define pDISC   4
#define pCOST   4
#endif//ccr2015-08-20<<<<<<<<<<<<
#define pluNumber			10	    	/* number of Plus */
#define pluRandomSize		7	     	/* max random size is 7 bytes */
#define pluCapSize			16		    /* caption length max 24 */
#if(defined(CASE_GPRS))
    #define pluLevel		4		    /* number of price levels, max is 4*/
#else
    #define pluLevel        1
#endif

#if defined(CASE_INDONESIA)
#define pluPriceSize	    5		    /* max is 10 digits *///ccr2015-08-20
#define pluCost			    5
#else
#define pluPriceSize	    4		    /* max is 10 digits *///ccr2015-08-20
#define pluCost			    4
#endif

#define pluInvSize			3	//zengy 20100127 ���ſ�������

#define pluTotalOffSet		(pluRandomSize+pluCapSize+(offNumber>0)*2+1+(pluLevel*pluPriceSize)+pluCost+pluInvSize)	    	/* Start of totalizer in record */
#define pluRecordSize		(pluTotalOffSet+(pCC+pQTY+pAMT+pRET+pDISC+pCOST+1))	   	/* size of 1 PLU record, 16 is the total data size */

//Link & DeptHi set by AP.Options.Plu
//  SIZE Size[REPDEFMAX]      /* Totalizer lay-out for PLU's */


/****************** Definitions for  TENDTABLE ***********/
#if defined(CASE_INDONESIA)//ccr2015-08-20>>>>>>>
#define cCC     2
#define cQTY    0
#define cAMT    6
#define cRET    0
#define cDISC   0
#define cCOST   0
#else
#define cCC     2
#define cQTY    0
#define cAMT    4
#define cRET    0
#define cDISC   0
#define cCOST   0
#endif//ccr2015-08-20<<<<<<<<<<<<

#define tendNumber			8 	    /* number of tendering functions */
#if defined(CASE_FORHANZI)
#define tendCapSize			8 	    /* caption length max 12 */
#else//ccr2015-08-14
#define tendCapSize			12 	    /* caption length max 12 */
#endif
#define tendTotalOffSet		(tendCapSize+5)    /* Start of totalizer in record */
#define tendRecordSize		(tendTotalOffSet+2*(cCC+cQTY+cAMT+cRET+cDISC+cCOST+1)+(clrkNumber+salNumber)*(cAMT+1)*2)     /* size of 1 tendering record */
                                                                       //*2,��ָӪҵԱ���տ�Ա����ͳ�ƺ���ͳ��
//    struct  REPSIZE Size[REPDEFMAX]      /* Totalizer lay-out for function */

/****************** Definitions for  PORATABLE ***********/
#if defined(CASE_INDONESIA)//ccr2015-08-20>>>>>>>
#define prCC     2
#define prQTY    0
#define prAMT    4
#define prRET    0
#define prDISC   0
#define prCOST   0
#else
#define prCC     2
#define prQTY    0
#define prAMT    4
#define prRET    0
#define prDISC   0
#define prCOST   0
#endif//ccr2015-08-20<<<<<<<<<<<<
#define poraNumber			6 	    /* number of PO & RA functions *///ccr040809
#define poraCapSize			8 	    /* caption length max 12 */
#define poraTotalOffSet		(poraCapSize+4)    /* Start of totalizer in record */
#define poraRecordSize		(poraTotalOffSet+2*(prCC+prQTY+prAMT+prRET+prDISC+prCOST+1)+(clrkNumber+salNumber)*(prAMT+1)*2)     /* size of 1 record */
                                                                       //*2,��ָӪҵԱ���տ�Ա����ͳ�ƺ���ͳ��
//    struct  REPSIZE Size[REPDEFMAX]      /* Totalizer lay-out for function */

/****************** Definitions for  CORRECTABLE ***********/
#if defined(CASE_INDONESIA)//ccr2015-08-20>>>>>>>
#define crCC     0
#define crQTY    3
#define crAMT    5
#define crRET    0
#define crDISC   0
#define crCOST   0
#else
#define crCC     0
#define crQTY    3
#define crAMT    4
#define crRET    0
#define crDISC   0
#define crCOST   0
#endif//ccr2015-08-20<<<<<<<<<<<<
#define corrNumber			5  	    /* number of correction functions,��5���̶�Ϊ���˹��� */
#define corrCapSize			12  	    /* caption length max 24 */
#define corrTotalOffSet		(corrCapSize+2)     /* Start of totalizer in record */
#define corrRecordSize		(corrTotalOffSet+2*(crCC+crQTY+crAMT+crRET+crDISC+crCOST+1)+(clrkNumber+salNumber)*(crCC+crQTY+crAMT+crRET+crDISC+crCOST+1)*2)     /* size of 1 record */
                                                                       //*2,��ָӪҵԱ���տ�Ա����ͳ�ƺ���ͳ��
//    struct  REPSIZE Size[REPDEFMAX]      /* Totalizer lay-out for function */

/****************** Definitions for  DISCTABLE ***********/
#if defined(CASE_INDONESIA)//ccr2015-08-20>>>>>>>
#define xCC     0
#define xQTY    3
#define xAMT    5
#define xRET    0
#define xDISC   0
#define xCOST   0
#else
#define xCC     0
#define xQTY    2
#define xAMT    4
#define xRET    0
#define xDISC   0
#define xCOST   0
#endif//ccr2015-08-20<<<<<<<<<<<<
#define discNumber			8 	    /*ccr090812 for SubDisc number of correction functions */
#define discCapSize			10  	    /* caption length max 12 */
#define discTotalOffSet		(discCapSize+10)     /* Start of totalizer in record */
#define discRecordSize		(discTotalOffSet+2*(xCC+xQTY+xAMT+xRET+xDISC+xCOST+1)+(clrkNumber+salNumber)*(xCC+xQTY+xAMT+xRET+xDISC+xCOST+1)*2)     /* size of 1 record */
                                                                       //*2,��ָӪҵԱ���տ�Ա����ͳ�ƺ���ͳ��
//    struct  REPSIZE Size[REPDEFMAX]      /* Totalizer lay-out for function */

/****************** Definitions for CURRTABLE ***********/
#if defined(CASE_INDONESIA)//ccr2015-08-20>>>>>>>
#define cuCC     2
#define cuQTY    0
#define cuAMT    5
#define cuRET    0
#define cuDISC   0
#define cuCOST   0
#else
#define cuCC     2
#define cuQTY    0
#define cuAMT    4
#define cuRET    0
#define cuDISC   0
#define cuCOST   0
#endif//ccr2015-08-20<<<<<<<<<<<<
#if defined(DEBUGBYPC)
#define currNumber			(5) //ccr081208 5 	    /* number of foreign currency */
#else
#define currNumber			(1) //ccr081208 5 	    /* number of foreign currency */
#endif
#define currCapSize			8 	    /* caption length max 12 */
#define currTotalOffSet		(currCapSize+12)    /* Start of totalizer in record */
#define currRecordSize		(currTotalOffSet+2*(cuCC+cuAMT+1)+(clrkNumber+salNumber)*(cuAMT+1)*2)     /* size of 1 currency record */
                                                                       //*2,��ָӪҵԱ���տ�Ա����ͳ�ƺ���ͳ��
//    struct  REPSIZE Size[REPDEFMAX]      /* Totalizer lay-out for function */


/****************** Definitions for PBTABLE ***********/
#if defined(CASE_INDONESIA)//ccr2015-08-20>>>>>>>
#define ptCC     0
#define ptQTY    2
#define ptAMT    6
#define ptRET    0
#define ptDISC   0
#define ptCOST   0

#define pfCC     0
#define pfQTY    0
#define pfAMT    6
#define pfRET    0
#define pfDISC   0
#define pfCOST   0
#else
#define ptCC     0
#define ptQTY    2
#define ptAMT    4
#define ptRET    0
#define ptDISC   0
#define ptCOST   0

#define pfCC     0
#define pfQTY    0
#define pfAMT    4
#define pfRET    0
#define pfDISC   0
#define pfCOST   0

#endif//ccr2015-08-20<<<<<<<<<<<<

#define pbNumber			11 	    /* number of PB functions */
#define pbCapSize			8 	    /* caption length max 24 */
#define pbTotalOffSet		(pbCapSize+2)    /* Start of totalizer in record */
#define pbRecordSize		(pbTotalOffSet+2*(pfCC+pfQTY+pfAMT+pfRET+pfDISC+pfCOST+1)+(clrkNumber+salNumber)*(pfCC+pfQTY+pfAMT+pfRET+pfDISC+pfCOST+1)*2)     /* size of 1 PB function record */
                                                                     //*2,��ָӪҵԱ���տ�Ա����ͳ�ƺ���ͳ��
//    struct  REPSIZE Size[REPDEFMAX]      /* Totalizer lay-out for function */

/****************Definitions for  PBTOTAL ***********************/
#define pbNumberOfPb		50     /* number of PB available */
#define pbRandom			0 	  /* random number size max 14 digits bit 0 to 3 */
#define pbText				8 	  /* text for each PB# max 24 */
#if defined(CASE_INDONESIA)
#define pbAmtSize			5 	  /* size of pb amount	*///ccr2015-08-20
#else
#define pbAmtSize			4 	  /* size of pb amount	*///ccr2015-08-20
#endif
#define pbtTotalOffset      (2+pbRandom+pbText+1+1+1+(pbAmtSize+1)+(pbAmtSize + 1) * 2)         //ccr 2003-10-31 //20040330
//WORD Block;BYTE Random[7];char Text[25];BYTE Clerk;BYTE Lines;BYTE Covers;BCD Amt;BCD Disc1;BCD Disc2;
#define pbtRecordSize       (pbtTotalOffset+(ptCC+ptQTY+ptAMT+ptRET+ptDISC+ptCOST+1)+(clrkNumber+salNumber)*(ptAMT+1))          // Record size for PBTable report ccr 2003-10-31

#if defined(CASE_INDONESIA)
#define pbArtAmt			5 	    /* max amount size for art record *///ccr2015-08-20
#define pbQty				4 	    /* max qty for artrecord *///ccr2015-08-20
#else
#define pbArtAmt			3 	    /* max amount size for art record */
#define pbQty				3 	    /* max qty for artrecord */
#endif
#define pbArtSize			(pbArtAmt+pbQty+1+2) 	    /* size of art record is ArtAmt + Qty + 1 + 2 */
#define pbNumberOfItems		10     /* number of items in 1 table record */	 //20040330
#define pbNumberOfBlocks	50	/* number table blocks */
#define pbBlockSize			(pbNumberOfItems * pbArtSize +2)//<128 must
#if (pbBlockSize>=128)  //ccr2015-08-21
#error "ERROR: pbBlockSize>=128"
#endif
//size  = (pbAmtSize + pbText + pbRandom + 6)*pbNumberOfPb
//

/****************** Definitions for DRAWERTABLE ***********/
#if defined(CASE_INDONESIA)//ccr2015-08-20>>>>>>>
#define drCC     0
#define drQTY    0
#define drAMT    6
#define drRET    0
#define drDISC   0
#define drCOST   0

#else
#define drCC     0
#define drQTY    0
#define drAMT    4
#define drRET    0
#define drDISC   0
#define drCOST   0
#endif//ccr2015-08-20<<<<<<<<<<<<
#define drawNumber			8 	    /* number of tendering functions */
#define drawCapSize			8 	    /* caption length max 24 */
#define drawTotalOffSet		(drawCapSize+2)    /* Start of totalizer in record */
#define drawRecordSize		(drawTotalOffSet+2*(drAMT+1)+(clrkNumber+salNumber)*(drAMT+1)*2)     /* size of 1 Drawer record */
                                                                       //*2,��ָӪҵԱ���տ�Ա����ͳ�ƺ���ͳ��
//    struct  REPSIZE Size[REPDEFMAX]      /* Totalizer lay-out for function */

/**************** Definitions for MODITABLE **************************/
#define modiNumber			 20
#define modiCapSize			16	    /* caption length max 24 */

/********************* Definitions for GRAND TOTALSALES**********************/
#if defined(CASE_INDONESIA)//ccr2015-08-20>>>>>>>
#define toCC     2
#define toQTY    4
#define toAMT    6
#define toRET    0
#define toDISC   5
#define toCOST   0

#else
#define toCC     2
#define toQTY    4
#define toAMT    5
#define toRET    0
#define toDISC   4
#define toCOST   0
#endif//ccr2015-08-20<<<<<<<<<<<<

#define totalRecordSize		(2*(toCC+toQTY+toAMT+toRET+toDISC+toCOST+1)+zoneNumber*(toCC+toAMT+1)+(clrkNumber+salNumber)*(toAMT+1)*2)     /*ccr090812 for SubDisc size of TOTAL SALES record */
                                                                     //*2,��ָӪҵԱ���տ�Ա����ͳ�ƺ���ͳ��
//    struct  REPSIZE Size[REPDEFMAX]      /* Totalizer lay-out */

/****************** Definitions for AGREETABLE ***********/
#define agreeNumber			0 	    /* number of foreign currency */
#define agreeCapSize		12 	    /* caption length max 25 */
#define agreeTotalOffSet	(agreeCapSize+20+18)
#define agreeRecordSize		(agreeTotalOffSet+4)     /* size of 1 currency record */

/****************** Definitions for ICBLOCKTABLE ***********/  //ccr chipcard 2004-07-01
#if	(DD_CHIPC==1)
    #define icblockNumber         100
#else
    #define icblockNumber         1
#endif
#define icblockSize        4


///////////struct	REPSIZE Size[REPDEFMAX]///////////////////////////////////////////
#define REPDEFMAX	(1+5)   /* General Total lay-out */
                            /* Clerk Total lay-out */
                            /* Time zones Total lay-out */
                            /* Day Total lay-out */
                            /* Month Total lay-out */
                            /* saler Total lay-out */
////////////////�������Ͷ���ApplVar.Report.Type//////////////////////////////
typedef enum {
    REPORT_GRANDTOTAL,//    0  //"   ��  ��  ��   "
    REPORT_GROUP     ,//    1  //"��  ��  ��  �� "//1
    REPORT_DEPARTMENT,//    2  //" ��  ��  ��  �� "//2
    REPORT_PLU       ,//    3  //"��Ʒ  ��  �� "      /* 3 Used with Plu Report */
    REPORT_TENDER    ,//    4  //"��  ��  ��  Ϣ "//4
    REPORT_PORA      ,//    5  //"�� �� �� �� Ϣ "//5
    REPORT_DRAWER    ,//    6  //"Ǯ  ��  ��  Ϣ "//6
    REPORT_CORRECTION,//    7  //" ��  ��  ��  Ϣ "//7
    REPORT_DISCOUNT  ,//    8  //" ��  ��  ��  Ϣ "//8
    REPORT_CURRENCY  ,//    9  //" ��  ��  ��  Ϣ "//9
    REPORT_TAX       ,//    10 //"��  ˰  ��  Ϣ "//10
    REPORT_PBFUNC    ,//    11 //" ��  ��  ��  Ϣ "//11
    REPORT_BALANCE   ,//    12 //" ��  ̨  ��  Ϣ "//12
    REPORT_TABLES    ,//    13 //" ��  ̨  ��  Ϣ "//13
    REPORT_INVENTORY ,//    14 //" ��  Ʒ  ��  �� "//14
    REPORTTYPE_MAX=REPORT_INVENTORY	     ,//   14
} REPORTTYPE;

//>>>>>>struct FIXEDREPORT ReportList[13] ����Ŀ¼>>>>>>>>>>>>>>>>>>
//#define XZNUM		13	 	//Number of XReport
typedef enum {
    REPID_CLERKDAILY,           //�տ�Ա�ձ�
    REPID_CLERKPERIOD,          //�տ�Ա�ܱ�
    REPID_DAILYREPORT,         //�����ձ�
    REPID_PERIODREPORT,        //�����ܱ�
    REPID_PLUREPORT,           //��Ʒ����
    REPID_TABLEREPORT,         //���ʱ���
    REPID_TIMEZONE,            //ʱ�α���
    REPID_ALLCLERKDAILY,        //ȫ�տ�Ա�ձ�
    REPID_ALLCLERKPERIOD,       //ȫ�տ�Ա�ܱ�
#if (salNumber)
    REPID_SALERDAILY,           //ӪҵԱ�ձ�
    REPID_SALERPERIOD,          //ӪҵԱ�ܱ�
    REPID_ALLSALERDAILY,       //ȫӪҵԱ�ձ�
    REPID_ALLSALERPERIOD,      //ȫӪҵԱ�ܱ�
#endif
#if (BARCUSTOMER==1)
	REPID_BARCUSTOMER,          //�����Ա����,
#endif
} REPORTLIST;


//>>>>>>>>>>ָ��XZTitle�еĶ�Ӧ������Ŀ,��REPORTLIST����Ŀһ��>>>>>>>>>>>>>>>>>
//#define XZNUM		13	 	//Number of XReport
typedef enum {
    ItemXZ_DAILYREPORT,   //"�����ձ���"},
    ItemXZ_PERIODREPORT,  //"�����±���"},
    ItemXZ_PLUDAILY,      //"��Ʒ����"},
    ItemXZ_TABLEREPORT,   //"���ʱ���"},
    ItemXZ_TIMEZONE,      //"ʱ�α���"},
    ItemXZ_CLERKDAILY,    //"�տ�Ա�ձ���"},
    ItemXZ_CLERKPERIOD,   //"�տ�Ա�±���"},
    ItemXZ_ALLCLERKDAILY, //"ȫ�տ�Ա�ձ�"},
    ItemXZ_ALLCLERKPERIOD,//"ȫ�տ�Ա�±�"},
#if (salNumber)
    ItemXZ_SALERDAILY,    //"ӪҵԱ�ձ���"},
    ItemXZ_SALERPERIOD,   //"ӪҵԱ�±���"},
    ItemXZ_ALLSALERDAILY, //"ȫӪҵԱ�ձ���"},
    ItemXZ_ALLSALERPERIOD,//"ȫӪҵԱ�±���"},
#endif
#if (BARCUSTOMER==1)
	ItemXZ_BARCUSTOMER,          //�����Ա����,
#endif
    XZNUM		          //Number of XReport
} ITEMSXZ;
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//define for the ICCard.Options=============================================

#define IC_CHIPCARD BIT0
#define IC_TYPE_0   BIT1
#define IC_TYPE_1   BIT2
#define IC_TYPE_2   BIT3
#define IC_REPORT   BIT4
#define IC_DISCOUNT BIT5
#define IC_POINTS   BIT6
#define IC_TOT_CC   BIT7
#define IC_DEAD 	 BIT8			//��Ч���Ƿ���Ч

//Index for file address table=============================================

#define AddrTotl	0
#define AddrGroup	AddrTotl+1
#define AddrDept	AddrGroup+1
#define AddrPLU		AddrDept+1
#define AddrPort	AddrPLU+1
#define AddrTend	AddrPort+1
#define AddrPoRa	AddrTend+1
#define AddrDrawer	AddrPoRa+1
#define AddrCorr	AddrDrawer+1
#define AddrDisc	AddrCorr+1
#define AddrCurr	AddrDisc+1
#define AddrTax		AddrCurr+1
#define AddrPBf		AddrTax	+1
#define AddrModi	AddrPBf	+1
#define AddrClerk	AddrModi+1
#define AddrOFF		AddrClerk+1
#define AddrICBlock	AddrOFF+1  //Edit By Ranjer.Hu 2004-06-28
#define AddrSalPer	AddrICBlock+1
#define AddrAgree	AddrSalPer+1
#define AddrRPLU	AddrAgree+1
#define AddrEndP	AddrRPLU+1
#define AddrPBt		AddrEndP+1
#define AddrTrack   AddrPBt	+1
#define AddrMAX		AddrTrack+1

/********** start arress for applications (ApplVar.AP.StartAddress)************/

#define RamOfApplVar  0 //Address for save ApplVar
#define RamOfTotal	(RamOfApplVar + (sizeof(APPLICATION_SAVE) & 0xffe0) + 0x20) //
#define RamOfGroup	(totalRecordSize + RamOfTotal)
#define RamOfDept	(grpNumber * grpRecordSize+RamOfGroup)
#define RamOfPLU	(depNumber * depRecordSize+RamOfDept)
#define RamOfPort	(pluNumber * pluRecordSize+RamOfPLU)
#define RamOfTend	(RamOfPort)
#define RamOfPoRa	(tendNumber * tendRecordSize+RamOfTend)
#define RamOfDrawer	(poraNumber * poraRecordSize+RamOfPoRa)
#define RamOfCorr	(drawNumber * drawRecordSize+RamOfDrawer)
#define RamOfDisc	(corrNumber * corrRecordSize +RamOfCorr)
#define RamOfCurr	(discNumber * discRecordSize+RamOfDisc)
#define RamOfTax	(currNumber * currRecordSize+RamOfCurr)
#define RamOfPBf	(taxNumber * taxRecordSize+RamOfTax)
#define RamOfModi	(pbNumber * pbRecordSize +RamOfPBf)
#define RamOfClerk	(modiNumber * modiCapSize +RamOfModi)
#define RamOfOFF	(clrkNumber * clrkRecordSize +RamOfClerk)
#define RamOfICBlock    (offNumber * offRecordSize +RamOfOFF)    //ccr chipcard 2004-07-01
#define RamOfRPLU	(RamOfICBlock+icblockNumber * icblockSize)
#define RamOFSalPer	(RamOfRPLU)
#define RamOFAgree	(salNumber * salRecordSize +RamOFSalPer)
#define RamOfPBt	(agreeNumber * agreeRecordSize +RamOFAgree)
#define RamOfTrack  (pbtRecordSize*pbNumberOfPb+RamOfPBt)
#define RamOfEndP	(pbBlockSize*pbNumberOfBlocks+RamOfTrack)
/*************** start arress for applications ****************/

#if (salNumber>0)  //ccr2016-09-14>>>>>
#define  SYSFORSALE     2
#else
#define  SYSFORSALE     0
#endif //ccr2016-09-14<<<<<

#if (defined(CASE_GPRS) && defined(CASE_INDONESIA)) //ccr2015-08-03
#define SYSUSED	    (33+SYSFORSALE) //�����Ƿ���Heart-Beat��Ϣ��������
#else
#define SYSUSED	    (32+SYSFORSALE)
#endif

/*********************System flags****************************************/
#define FLAG00 0x00 //NO_DECIMAL ccr2016-11-10 Ĭ��ֵ
#define NO_DECIMAL  ApplVar.AP.Flag[0]
/*
0 -> 1,00
1 ->	1
2 -> 1,000
3 -> 1,0
*/
#define FLAG01 0x01 //COMMA
#define COMMA	    ApplVar.AP.Flag[1]
/*
BIT-0	If set then Amount Point instead of Amount Comma
BIT-1	If set then print Info Line 1 () Double Height
BIT-2	If set then print Info Line 2 (Time / Date/receipt number) Double Height
BIT-3	If set then Suppress Receipt Number (R/J/Slip)
BIT-4	If set then Suppress Location/Register (R/J/Slip)
BIT-5	If set then Suppress Clerk (R/J/Slip)
BIT-6	If set then Suppress Date (R/J)
BIT-7	If set then Suppress Time (R/J)
*/
#define FLAG02 0x00//AM_PM
#define AM_PM	    ApplVar.AP.Flag[2]
/*
BIT 0 If set then AM/PM time system
BIT 1 If set then 04/10 TOTAL rounding
BIT 2 if set then Receipt Header Double Height
BIT 3 If set then Receipt Trailer Double Height
BIT 4 If set then Reset Salesperson to 1
BIT 5 If set then don't consolidate in Transaction Buffer
BIT 6 If set then Bonus on Discount Itemizer 1
*/
#define FLAG03 0x02//TIME_DATE
#define TIME_DATE   ApplVar.AP.Flag[3]
/*      0:"Mon,DD-MM-YYYY"
        1:"Mon,MM-DD-YYYY"
        2:"Mon,YYYY-MM-DD"
     ����:"Mon,DD-MM-YYYY"

*/
#define FLAG04 0x28//KEYTONE
#define KEYTONE     ApplVar.AP.Flag[4]
/* bit 0 if set then no keytone */
/* bit 1 if set then no Alfa Keyboard */
/* bit 2 if set then no Number print in reports (Plu always number */
/* bit 3 if set then don't print report end and power up on journal */
/* bit 4 if set then Item Discount not in Sales, Item, Dept, Group */
/* bit 5 if set then Item/Subtotal discount ONE key (add 1 to func) */
/* bit 6 if set then Salesperson selection compulsory */
/* bit 7 if set then no SalesPerson change in transaction */

#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define FLAG05 0x74
#else
#define FLAG05 0x04//APPLCTRL
#endif
#define APPLCTRL    ApplVar.AP.Flag[5]
/* bit 0:=1,������������CSV��ʽ����*/
/* bit 1:=1,����Ļ������ʾ������Ŀ��*/
/* bit 2:=1,GPRS�������ͨ��ʱ,��Ҫ����ACKӦ��*/
#define CSV_FORMAT      (APPLCTRL & 0x01) //���ݵ�����ʽΪCSV��ʽ
#define PRN_QTY_ITEMS   (APPLCTRL & 0x02) //��ӡ������Ŀ��Ŀ
#define GPRS_ACK_MUST   (APPLCTRL & 0x04) //GPRS�������ͨ��ʱ,��Ҫ����ACKӦ��//ccr2016-08-18
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define BIT_EJ_X_STORE     BIT4//EJ�д洢X����
#define BIT_EJ_Z_STORE     BIT5//EJ�д洢Z����
#define BIT_EJ_TR_STORE    BIT6//EJ�д洢TR����

#define EJ_X_STORE      TESTBIT(APPLCTRL, BIT_EJ_X_STORE)//BIT4:EJ�д洢X����
#define EJ_Z_STORE      TESTBIT(APPLCTRL, BIT_EJ_Z_STORE)//BIT5:EJ�д洢Z����
#define EJ_TR_STORE     TESTBIT(APPLCTRL, BIT_EJ_TR_STORE)//BIT6:EJ�д洢TR����
#endif

#define FLAG06 0x00//SLIP_TOP
#define SLIP_TOP    ApplVar.AP.Flag[6]

#define FLAG07 0x00//SLIP_MAX
#define SLIP_MAX    ApplVar.AP.Flag[7]

#define FLAG08 0x06//SLIPINFO
#define SLIPINFO    ApplVar.AP.Flag[8]

#define FLAG09 0x10//CLERKFIX
#define CLERKFIX    ApplVar.AP.Flag[9]
/*	bit 0 -> if set then clerk selection compulsory */
/*	bit 1 -> if set then clerk fixed to PB# 	*/
/*	bit 2 -> if set then no clerk change in transaction */
/*	bit 3 -> if set then autofinalising when no clerk key */
/*		 with PB # always keycode 701 and normal keycode 901 */
/*	bit 4 -> if set then print clerk descriptor when clerk changed */
/*		 during transaction */
/*	bit 5 -> if set then the first 4 locations of the clerk name are */
/*				are used as a secret 4 digit code */
/*	bit 6 -> if set then the TRAINING clerks are included in report */
/*  Bit 7 -> if set then Press SUBKey must befor Tending */
#if defined(CASE_PERU)
#define PRE1        'S'         //����ǰ׺Ϊ S/.
#define PRE2        127
#else
#define PRE1        0x00
#define PRE2        0x00
#endif
#define FLAG10 PRE1//PREFIX_1
#define PREFIX_1    ApplVar.AP.Flag[10]

#define FLAG11 PRE2//PREFIX_2
#define PREFIX_2    ApplVar.AP.Flag[11]

#define FLAG12 0x00//PRICE_LEVEL
#define PRICE_LEVEL ApplVar.AP.Flag[12]

#define FLAG13 0x00//PVAT
#define PVAT	    ApplVar.AP.Flag[13]

#define FLAG14 0x00//LOCATION
#define LOCATION    ApplVar.AP.Flag[14]	//Location number of ECR

#define FLAG15 0x00//REGISTER
#define REGISTER    ApplVar.AP.Flag[15]	//Register number of ECR
/* #define DENSITY_R   ApplVar.AP.Flag[16] */
#define FLAG16 0x03//SECOND
#define SECOND	    ApplVar.AP.Flag[16]

/* #define DENSITY_J   ApplVar.AP.Flag[17]�������Աȶ� */
#define FLAG17 0x04//DENSITY
#define DENSITY     ApplVar.AP.Flag[17]     /* combined into 1 flag */
#define CONTRAST    17
/*
Bit0..3:Contrast //BIT0 - 0:normal dencity,1:double dencity
*/
#define FLAG18 0x9A//PBINFO
#define PBINFO	    ApplVar.AP.Flag[18]
/*
BIT0 - If set Compulsory PB selection
BIT1 - If set display amount instead of PB#
BIT2 - If set then Open PB# (Check#)
BIT3 - If set then Old PB system with checkout function
BIT4 - if set then no receiptnumber increment with PB
#if PBTIME == 1
BIT5 & 6 -	00	PB time system not active
01	PB time system in minutes
10	PB time system in hours
11	PB time system in days
#endif
BIT7 - If set then store DiscItem 1&2 must not be changed by user !!!
*/
#define FLAG19 0x30//PBPRINT
#define PBPRINT     ApplVar.AP.Flag[19]
/*
BIT0 - If set then the reprint bill only in MG
BIT1 - If set then after print on slip then slip compulsory
BIT2 - If set then print new balance after close PB
BIT3 - if set then don't print Articles with ZERO amount on BILL
BIT4 - reserved harm
BIT5 - reserved harm
BIT6 - reserved harm
BIT7 - if set then Auto Check Number
*/
#define FLAG20 0x02//COMPUTER
#define COMPUTER   ApplVar.AP.Flag[20]	//RS232 port for computer
#define COMPUTER_1    (ApplVar.AP.Flag[20] -1 )	//RS232 port for computer

#define FLAG21 0x05//ACTIVE
#define ACTIVE	    ApplVar.AP.Flag[21]

#define FLAG22 0x00//CUTTER
#define CUTTER	    ApplVar.AP.Flag[22]

#define FLAG23 0x58//ART_LEVEL
#define ART_LEVEL   ApplVar.AP.Flag[23]
/*
bit 0 - if set then zero after article
bit 1 - if set to zero at end of transaction
bit 2 - is set then cost price is used for Mix/Match
bit 3 - is set then In Store Marking is active (also RANDOM PLU
MUST be set. format FFRRRRRAAAAAC fixed 13 digits
FF = 21 Identifier
RRRRR = Random Plu Number
AAAAA = Amount
C = check digit
bit 4 - If set then article level also on PLU# key
bit 5 - If set then article level also on DEPRTMENTS
bit 6 - if set then print inventory Qty in PLU sales report if active
*/
#define FLAG24 0x42//PLU_PRINT
#define PLU_PRINT   ApplVar.AP.Flag[24]
// BIT 0 Print PLU # if set
/* bit 4 print Salesperson if set  lyq added 2003\10\23 */
/* bit 5 can change PLU price(PLU FREE)*/
/* bit 6 flags for TALLONS */
/* BIT 7 if set then compulsory multiply key on fixed plu */

#define FLAG25 0x01//DOT
#define DOT	    	ApplVar.AP.Flag[25]
/* if BIT 7 set then print small chinese font */
/* if BIT 6 0 then r print else j print */
/* if BIT 5 set then print On/Off function enable*/
/* if BIT 4 set then print the tallon lyq*/
/* if BIT 2 set then save NOADDLOG,OPERLOG,LOCKLOG*/
/* if BIT 1 set then train mode ccr2016-02-16 */
#define RJPRN	    (TESTBIT(DOT,BIT6))     /* if 0 then r print else j print */

#define FLAG26 0x40//DBLHIPRN
#define DBLHIPRN	ApplVar.AP.Flag[26]
/*
BIT2 Set then print name in double high mode
BIT3 set then print header in center
BIT4 set then peint trailer in center
BIT5 Set then send heart-beat //ccr2015-08-03,CASE_INDONESIA
BIT6 Set then clear GRAND TOTAL after Z-daily //ccr2016-02-23
*/

//if set then print the data from host when update
#define FLAG27 0x03//PROMOTION
#define PROMOTION   ApplVar.AP.Flag[27]
#define PRNINDEX    (PROMOTION & 0x80)    //ccr2014-03-31
/*
Bit 0: 1-Jolly disabled,0-Jolly enabled
Bit 1: 1-Point Disabled,0-Point Enabled
bit 7 if set :��ӡȡ�˺ţ��տ���ã��վݺ�
*/
#define FLAG28 0x00//BALANCE
#define BALANCE	    ApplVar.AP.Flag[28]
//Bit2..Bit0:Ϊ���ں�,0-�޵��ӳ�
//Bit7..Bit4:Ϊ�ͺ�(1-�ϱ�,0-Ϊ����);//ccr2016-01-22
#define FLAG29 0x00//LMARGE
#define LMARGE	    ApplVar.AP.Flag[29]

#define FLAG30 0xd1//BARCODE
#define BARCODE     ApplVar.AP.Flag[30]
/* port number for barcode scanner, max is 7 */
/* when BIT 3 is set then no prefix in the code */
/* If Bit 4 is set then Magazine Decoding for France */
/* If Bit 5 set then no CTS check but Timer */
/* If Bit 6 is set then also Weigth decoding from barcode */
/* If Bit 7 is set then Extended Instore marking */
/* 02, 20, 26, 28 */
#define FLAG31 0x00//SLIP
#define SLIP	    ApplVar.AP.Flag[31]     /* 2 bytes for slip */

#define FLAG32 0x00//SLIPPORT
#define SLIPPORT  ApplVar.AP.Flag[32]    //ccr2016-01-21
#define SLIPPORT_1    (ApplVar.AP.Flag[32] - 1 )

#define FLAG33 0x00//CHARSET
#define CHARSET     ApplVar.AP.Flag[33]
/* set character set used by Controller and epson comp printers */
/* low 4 bit (o - > 15) for External printers */
/* high bit used for internal char set */
#define FLAG34 0x07//KPSTART
#define KPSTART     ApplVar.AP.Flag[34]     /*Flag[34]-Flag[57]: 8 X 3 bytes for kp's */
#define FLAG35 0x02
#define FLAG36 0x00
#define FLAG37 0x00
#define FLAG38 0x02
#define FLAG39 0x00
#define FLAG40 0x00
#define FLAG41 0x02
#define FLAG42 0x00
#define FLAG43 0x00
#define FLAG44 0x02
#define FLAG45 0x00
#define FLAG46 0x00
#define FLAG47 0x02
#define FLAG48 0x00
#define FLAG49 0x00
#define FLAG50 0x02
#define FLAG51 0x00
#define FLAG52 0x00
#define FLAG53 0x02
#define FLAG54 0x00
#define FLAG55 0x00
#define FLAG56 0x02
#define FLAG57 0x00

#define FLAG58 0x42//KPPRICE
#define KPPRICE     ApplVar.AP.Flag[58]
/*	BIT 0 if set then Print also amt on KP
BIT 1 if set then new KP print format for NORIS
BIT 2 if set then print price on KP (also BIT 1 set)
BIT 3 if set then print PLU# on KP (also BIT 1 set)
BIT 4 if set then Short Receipt Header and long when
print PB Bill
BIT 5 if set then enter modifier before article (must
be used with single ticket on department.
BIT 6 if set then print PB Text on Item Receipt and KP
if text active.
BIT 7 if set then only 2 digit receipt number on KP
*/
#define FLAG59 0x00//EXTREMAIN
#define EXTREMAIN   ApplVar.AP.Flag[59]     /* Flag[59]-SLFLAG.0-6:��չram����������������Ԥ���ռ��С(sizeof(APPLICATION_SAVE)) */

#define FLAG60 0x00//SLFLAG
#define SLFLAG	    ApplVar.AP.Flag[60]     /* DITRON Language Flag ? */
/*
Bit7: enable SHIFT if not set
*/
//#define SL_TIMEOUT  ApplVar.AP.Flag[61]     /* SL time out is TIMEOUT * 5.37 msec */
#define FLAG61 0x21//EXTRAMN
#define EXTRAMN		ApplVar.AP.Flag[61]		/* ��4λ������ʾ��չ�ڴ���Ŀ(ÿ��256K) */

#define FLAG62 0x01//COPYRECEIP
#define COPYRECEIP  ApplVar.AP.Flag[62]     /* ��4λΪ�վݸ��ƴ���,Ϊ0ʱ,��ֹ����  */
/*
bit 7 =0:�����ձ���ʱ,�վݺŲ���0; =1:�����ձ���ʱ,�վݺŹ�0    //
*/
#define FLAG63 0x00//ROUNDMASK
#define ROUNDMASK   ApplVar.AP.Flag[63]     /* type of rounding sales rounding*/
/* 2 is Swiss Rounding on Finalizing Sales amount */
/* 4 is Swiss Rounding on MULT, TAX & Percentage discount */
/* 6 Swiss Rounding on Both */
/* 8 is French Rounding on Finalizing Sales Amount */
/* 16 is French Rounding on MULT, TAX & Percentage discount */
/* 24 French Rounding on Both */
/* 1 Is Swiss Input masking (last digit must be 0 or 5) */
/* BIT 5 if set 12/25 Danish Rounding on Sales Amount */
/* BIT 6 if set 24/50 Norwegian Rounding on Sales Amount */
/* BIT 7 if set 00/10 Rounding (used in Tsjechie) on Sales Amount */
/* Other rounding in System Flag AM_PM */
/****************** General Used Structures & Unions **********************/

//===================================================================================
struct PASSWORD
{
    BYTE PwdX[MAXPWD];
    BYTE PwdZ[MAXPWD];
    BYTE PwdSET[MAXPWD];
    BYTE PwdMG[MAXPWD];
};
//===================================================================================


struct PRINTER
{
    BYTE type;      /* type of printer */
/*
BIT0 - BIT 3 used for KP type
BIT4 - IF set then Print Line after article //ccr2016-12-12
BIT5 - If set then print TALON (Total) receipt on KP
BIT6 - If set then Single Qty (1) tickets.
BIT7 - If set then Single tickets per Item.
*/
    BYTE port;      /* serial port */
    BYTE alter;     /* alternative printer */
};

struct KPINFO
{
    BYTE Number;
    BYTE Current;
    BYTE Used;
    BYTE Error;
    BYTE Next;
    struct PRINTER *Prt;
};


/* the structure SIZE is used by the tables which define the totals and
functions. The Data is stored for reporting according to the tlzr's activated.
*/

struct REPSIZE
{
    BYTE    Periods;    /* number of periods, */
                        // bit0:=1,������ͳ��
                        // bit1:=1,������ͳ��
                        // bit2:=1,������ͳ��
                        // bit3:=1,������ͳ��
    BYTE    Length;     /* length=Cc+Qty+Amt+RetQty+Disc+Cost+1 */
    BYTE    Cc;         /* Customer count size */
    BYTE    Qty;        /* Quantity size */
    BYTE    Amt;        /* Amount size */
    BYTE    RetQty;     /* return only Qty */
    BYTE    Disc;       /* Discounts only Amount */
    BYTE    Cost;       /* Cost only Amount */
};

/* the structure TOTAL is used by the routine which adds the data to the */
/* activated tlzr's in a total or function */

struct TOTAL
{
    BCD Cc;         // �˿����� */
    BCD Qty;        // ��Ʒ���� */
    BCD Amt;        // �����ܼ� */
    BCD RetQty;     // �˻��������� */
    BCD Disc;       // �ۿۻ��� */
    BCD Cost;       // ���ۻ��� */
};

/* the structure report is used by the print report routines */

struct REPORT
{
    BYTE System;    /* if non zero then system report */
    BYTE Period;    //��������:0-�ձ���,1-�ܱ���,2-�±���,3-�걨��
    BYTE Type;      /* ��������,��FIXEDREPORT�е�Link�л�ȡ */
    WORD Start;         /* Start number of PLU, DEPT etc */
    WORD End;           /* End number of PLU, DEPT etc */
    BYTE PointerType;   //��ʾ�����������͵�ͳ�����ݣ�
                        //0-����ͳ��,1-Clerk(���տ�Ա),2-Hour(��ʱ��),3-Day(����),4-Month(����),5-Saleper(��ӪҵԱ)
#if NETTEST == 1
    WORD Pointer;    /* current processed pointer number */
    WORD PointerEnd;
#else
    BYTE Pointer;    /* current processed pointer number */
    BYTE PointerEnd;
#endif
    WORD Size;      /* һ��PLU/����ȼ�¼��С */
    BYTE OffSet;    /* ����������һ��PLU/����ȼ�¼�еĿ�ʼλ�� */
};
/* FIXEDREPORT�����洢�������������ı�����,��Link���о��ӱ���,�����ж���Ա��� */
struct FIXEDREPORT
{
    BYTE Name[REPWIDTH];//��������
    BYTE PrintLayOut;   //��ӡ��ʽ
    BYTE Options;       //bit0:��Ǯ��
                        //bit1:�Ƿ��ӡȫ����������
                        //bit2:Z-counter
                        //bit3:Z-������������
    BYTE Number;        /* depending on option Group or Dept number */
    BYTE Period;        //��������:=0-�ձ���,=1-�ܱ���,=2-�±���,=3-�걨��
    BYTE PointerType;   //��ʾ�����������͵�ͳ�����ݣ�
                        //0-����ͳ��,1-Clerk(���տ�Ա),2-Hour(��ʱ��),3-Day(����),4-Month(����),5-Saleper(��ӪҵԱ)
    BYTE Link[16];      /* �������ı��� */
    // 00-���ۻ��� ,01-������� ,02-������� ,03-��Ʒ���� ,04-�տ���� ,05-���������� ,06-Ǯ����� ,
    // 07-����ͳ�� ,08-�ۿ�ͳ�� ,09-���ͳ�� ,10-��˰ͳ�� ,11-����ͳ�� ,12-��̨ͳ�� ,13-��̨ͳ��

};
/* ���浱ǰ�վݵ�������Ŀ���� */
struct TRANSRECORD
{
    union KEY Key;
    BYTE Group;/* Ϊ������������ */
    BCD Qty;    /* �������� */
    BCD Amt;    /* ������Ŀ�ĵ���,ΪPLU��Ŀʱ:Amt.Value[BCDLEN-1] = PluPriceLevel */
    BCD	DiscAmt;	/* �ۿۺ���	cc 2006-10-20 for SubDisc */
};

struct PBARTICLE
{
    struct TRANSRECORD Rec;
    BCD Total;
    BYTE Flag;
    BYTE Random[7];
};

/****************** Structures used for the AGREE *************************/
struct AGREETABLE
{
    WORD Number;
    WORD RecordSize;
    BYTE    TotalOffSet;    /* Start of totalizer in record */
    BYTE CapSize;
};
/****************** Structures used for the AGREE *************************/
struct AGREERECORD
{
    BYTE    Name[25];
    BYTE    Addr[20];
    BYTE    Tax[18];
    BYTE    Total[4];
};


/****************** Structures used for the PORT *************************/
struct PORTTABLE
{
    WORD    Number;     /* number of Groups */
    WORD    RecordSize;     /* size of 1 Group record */
    BYTE    CapSize;        /* caption length max 24 */
};

/* ccr2016-01-21............................
Type'1'- "  ����"
Type'2'- "����ǹ"
Type'3'- "���ӳ�"
Type'4'- "��  ��"
Type'5'- "Ʊ ��"
Type'6'- "��Ƶ��"
Type'7'- "Eͨ��"
...........................................*/
struct PORTRECORD
{
    BYTE    Name[portCapSize+1];
    BYTE    Type;           /* '1','2','3','4','5'.. */
    BYTE    Prot[portProNum];
};
//  �޸�PORTRECORD�еĶ��壬����ͬʱ�޸�Bios_dir.INC�е�����ֵ
//	SioName=0			;��ʾ�������ƴ��λ��
//	SioType=portCapSize+1;��ʾ�������ʹ��λ�ã�'1','2','3','4','5'.��
//	SioProt= SioType+1	;��ʾ����Э����λ��
//	SioTele��SioProt +6	;��ʾ���ڵ绰����λ��

/****************** Structure used for the TOTAL SALES Totalizer ***********/

struct TOTALSALES
{
    WORD    RecordSize;     /* size of TOTAL SALES record */
    struct  REPSIZE Size[REPDEFMAX];      /* Totalizer lay-out */
};

/****************** Structures used for the OFF *************************/
struct OFFTABLE
{
    WORD    Number;     /* number of Groups */
    WORD    RecordSize;     /* size of 1 Group record */
    BYTE    CapSize;        /* caption length max 24 */
    BYTE    PriUSize;       /* max is 4 */
};


struct OFFRECORD
{
    BYTE    Name[25];
    BYTE    Type;
    BYTE    DateFrom[2];
    BYTE    DateTo[2];
    BYTE    TimeFrom[2];
    BYTE    TimeTo[2];
    BYTE    WeekDay;
    union
    {
        BYTE    Discount[9];
        struct
        {
            BYTE    NumItems;
            BYTE    PriceU[4];
            BYTE    PriceP[4];
        }   TYPE1;
    } OFFVal;
};

/****************** Structures used for the GROUPS *************************/

struct GROUPTABLE
{
    WORD    Number;     /* number of Groups */
    WORD    RecordSize;     /* size of 1 Group record */
    BYTE    TotalOffSet;    /* Start of totalizer in record */
    BYTE    CapSize;        /* caption length max 24 */
    struct  REPSIZE Size[REPDEFMAX];      /* Totalizer lay-out for Groups can be trapped for :*/
/* Standard */
/* Clerk */
/* Hour */
/* Day of Week */
/* Month of Year */
};

struct GROUPRECORD
{
    WORD    Family;    /*   max / 10 is digit and max % 10 is number of zeroes:
                          Example: 89:��ʾ�������Ϊ8000000000*/
    BYTE    Name[25];       /* max 24 with terminator */
};


/****************** Structures used for the DEPARTMENTS *************************/

struct DEPTTABLE
{
    WORD    Number;     /* number of Departments */
    WORD    RecordSize;     /* size of 1 Department record */
    BYTE    TotalOffSet;    /* Start of totalizer in record */
    BYTE    RandomSize;     /* max random size is 7 bytes */
    BYTE    CapSize;        /* caption length max 24 */
    BYTE    PriceSize;      /* max size is 4 */
    BYTE    PriMaxSize;     /* max size is 4 */
    struct  REPSIZE Size[REPDEFMAX];      /* Totalizer lay-out for dept */
/* can be trapped for : */
/* Standard */
/* Clerk */
/* Hour */
/* Day of Week */
/* Month of Year */
};

struct DEPTRECORD
{
    BYTE    Random[7];  /* max 7 bytes is 14 digits */
    BYTE    Name[25];   /* max 24 with terminator */
    BYTE    Group;  /* group selection max 0xff also for print bill,=0 not allon to a group */
    BYTE    Print;  /* print lay-out */
    BYTE    Options;
/*
Dept.Options
BIT 0 - If set then price is negative
BIT 1 - if set then Zero Price not allowed
BIT 2 - if set Single Ticket
BIT 3 - if set then Double ticket (also Single set)
BIT 4 - Print Line after article
BIT 5 - if Set single item when start of sale on TEND#1
BIT 6 - Add to Discount Itemizer 1
BIT 7 - Add to Discount Itemizer 2
*/
    BYTE    Tax;    /* Tax selection max 8 */
    BYTE    Kp;     /* Kp aansturing max 8 */
    BYTE    Price[5];
    BYTE    PriceMax[5];
/* flags */
};

/****************** Structures used for the PLU'S *************************/

struct PLUTABLE
{
    WORD    Number;     /* number of Plus */
    WORD    RNumber;        /* Number of RandomPLU */
    WORD    RecordSize;     /* size of 1 PLU record */
    BYTE    TotalOffSet;    /* Start of totalizer in record */
    BYTE    RandomSize;     /* max random size is 7 bytes */
    BYTE    CapSize;        /* caption length max 24 */
    BYTE    Level;      /* number of price levels */
    BYTE    PriceSize;      /* max is 10 digits */
    BYTE    Cost;
    BYTE    InvSize;        /* number of bytes for inventory */
    struct  REPSIZE Size[REPDEFMAX];      /* Totalizer lay-out for PLU's */
};              /* can be trapped for : */
/* Standard */
/* Clerk */
/* Hour */
/* Day of Week */
/* Month of Year */

struct PLURECORD
{
    BYTE    Random[7];  /* max 7 bytes is 14 digits */
    BYTE    Name[25];   /* max 24 with terminator */
    WORD    OFFIndex;   // Index of OFFPrice
    BYTE    Dept;       /* department selection max 0xff */
    BYTE    DeptHi;             /* High Dept Number */
    BYTE    Price[4][5];      /* max price is 10 digits is 5 bytes */
    BYTE    Cost[5];          /* max 4 levels with 1 cost price */
    WORD    Link;               /* PLU Link */
    BCD     Inventory;  /* plu inventory */
/* scale */
/* flag */
/* inventory */
};

/****************** Structures used for the Tendering functions ***********/
/* Cash, CC, Check */

struct TENDTABLE
{
    BYTE    Number;     /* number of tendering functions */
    WORD    RecordSize;     /* size of 1 tendering record */
    BYTE    TotalOffSet;    /* Start of totalizer in record */
    BYTE    CapSize;        /* caption length max 12 */
    struct  REPSIZE Size[REPDEFMAX];      /* Totalizer lay-out for function */
};

struct TENDRECORD
{
    BYTE    Print;
                //BIT0: print stub copy
                //BIT1: print receipt
                //BIT2: only print double height on R/J
                //BIT3: print bill
                //BIT4: print bill compulsorily
    BYTE    Options;
                /*
                BIT 0 - If set then open drawer
                BIT 1 - if set then must entry on charge
                BIT 2 - if set then not entry on charge and card
                BIT 3 - if set then  must entry CardNo
                BIT 4 - if set then overtender is tipp
                BIT 5 - if set then no tax calc
                BIT 6 -
                BIT 7 -
                */
    BYTE    Drawer;
    BYTE    Over;      /* over tender, tip if bit set */
    BYTE    MaxEntry;
    BYTE    Name[13];       /* max 12 with terminator */
};

/****************** Structures used for PO/ RA functions ***********/

struct PORATABLE
{
    BYTE    Number;     /* number of PO & RA functions */
    WORD    RecordSize;     /* size of 1 record */
    BYTE    TotalOffSet;    /* Start of totalizer in record */
    BYTE    CapSize;        /* caption length max 12 */
    struct  REPSIZE Size[REPDEFMAX];      /* Totalizer lay-out for function */
};

struct PORARECORD
{
    BYTE    Print;
    BYTE    Options;
            /*
            BIT 0 - If set then open drawer
            BIT 1 - if set then ʹ�ø��ʽ��������
            BIT 2 - if set then �����´��
            BIT 3 - if set then input else output
            BIT 4 - if set then  must entry CardNo //ccr2016-05-31
            BIT 5 - if set then
            BIT 6 -
            BIT 7 -
            */
    BYTE    Drawer;
    BYTE    MaxEntry;
    BYTE    Name[13];       /* max 12 with terminator */
};

/****************** Structures used for Correction functions ***********/

struct CORRECTABLE
{
    BYTE    Number;     /* number of correction functions */
    WORD    RecordSize;     /* size of 1 record */
    BYTE    TotalOffSet;    /* Start of totalizer in record */
    BYTE    CapSize;        /* caption length max 24 */
    struct  REPSIZE Size[REPDEFMAX];      /* Totalizer lay-out for function */
};

struct CORRECRECORD
{
    BYTE    Print;
    BYTE    Options;
    BYTE    Name[13];       /* max 12 with terminator */
};

/****************** Structures used for DISCOUNT functions ***********/

struct DISCTABLE
{
    BYTE    Number;     /* number of correction functions */
    WORD    RecordSize;     /* size of 1 record */
    BYTE    TotalOffSet;    /* Start of totalizer in record */
    BYTE    CapSize;        /* caption length max 12 */
    struct  REPSIZE Size[REPDEFMAX];      /* Totalizer lay-out for function */
};

struct DISCRECORD
{
    BYTE    Print;
    BYTE    Options;
    BYTE    Fixed[3];
    BYTE    Tax;
    BYTE    Max[4];
    BYTE    Name[13];       /* max 12 with terminator */
};

/****************** Structures used for Foreign Currency functions ***********/

struct CURRTABLE
{
    BYTE    Number;     /* number of foreign currency */
    WORD    RecordSize;     /* size of 1 currency record */
    BYTE    TotalOffSet;    /* Start of totalizer in record */
    BYTE    CapSize;        /* caption length max 12 */
    struct  REPSIZE Size[REPDEFMAX];      /* Totalizer lay-out for function */
};

struct CURRRECORD
{
    BYTE    Options;
            //BIT0: if "on", it means this currency don't allow amount with decimal
            //BIT1: if "on", it means change amount will be closed accrodding to the last currency( with sell rate)
    BYTE    Drawer;
    BYTE    Prefix1;
    BYTE    Prefix2;
    BYTE    BuyRate[4];
    BYTE    SellRate[4];
    BYTE    Name[13];       /* max 12 with terminator */
};

/****************** Structures used for Previous Balance functions ***********/

struct PBTABLE
{
    BYTE    Number;     /* number of PB functions */
    WORD    RecordSize;     /* size of 1 PB function record */
    BYTE    TotalOffSet;    /* Start of totalizer in record */
    BYTE    CapSize;        /* caption length max 24 */
    WORD    NumberOfPb;     /* number of PB available */
    BYTE    Random;   /* random number size max 14 digits bit 0 to 3 */
                    /* bit 4 not used */
                    /* bit 5 if set then store random plu in trackbuffer*/
                    /* bit 6 if set then specail PB invoice Number
                    and storage of MAX 200 numbers with 7 digits amount and sign */
                    /* bit 7 if set then Extra PB Trailer of fixed 50
                    lines which is printed on the receipt with Print
                    Bill function */
    BYTE    Text;     /* text for each PB# max 24 */
    BYTE    AmtSize;      /* size of pb amount	*/
    BYTE    ArtAmt;     /* max amount size for art record */
    BYTE    Qty;        /* max qty for artrecord */
    BYTE    ArtSize;        /* size of art record is ArtAmt + Qty + 1 + 2 */
    BYTE    NumberOfItems;     /* number of items in 1 table record */
    WORD    NumberOfBlocks; /* number table blocks */
    WORD    BlockSize;
    WORD    PBTRecordSize;
    BYTE    PBTTotalOffset;
    struct  REPSIZE Size[REPDEFMAX];      /* Totalizer lay-out for function */
    struct  REPSIZE PBTSize[REPDEFMAX];      /* Totalizer lay-out for function */
};

struct PBRECORD
{
    BYTE    Print;
    BYTE    Options;
    BYTE    Name[13];       /* max 12 with terminator */
};

struct PBTOTAL    /* struct used for PB storage */
{
    WORD Block;
    BYTE Random[7];
    BYTE Text[25];
    BYTE Clerk;
    BYTE Lines;
    BYTE Covers;
    BCD Amt;
    BCD Disc1;
    BCD Disc2;
#if CUBA1 == 1
    BYTE Count[3];      /* Extra counter for CUBA */
#endif
};

/****************** Structures used for the Drawer Totalizers ***********/

struct DRAWERTABLE
{
    BYTE    Number;     /* number of tendering functions */
    WORD    RecordSize;     /* size of 1 Drawer record */
    BYTE    TotalOffSet;    /* Start of totalizer in record */
    BYTE    CapSize;        /* caption length max 24 */
    struct  REPSIZE Size[REPDEFMAX];      /* Totalizer lay-out for function */
};

struct DRAWERRECORD
{
    BYTE    Print;
    BYTE    Options;
/*
	If BIT 1 is not set then Drawer Open Total
	BIT0	BIT2	-> Decimal point position
	0		0		1,00
	1		0		1
	0		1		1,000
	1		1		1,0
*/
    BYTE    Name[13];       /* max 12 with terminator */
};



/****************** Structures used for the TAX Totalizers ***********/

struct TAXTABLE
{
    BYTE    Number;     /* number of tax itemizers */
    WORD    RecordSize;     /* size of 1 tax record */
    BYTE    TotalOffSet;    /* Start of totalizer in record */
    BYTE    CapSize;        /* caption length max 12 */
    struct  REPSIZE Size[REPDEFMAX];      /* Totalizer lay-out for function */
};

struct TAXRECORD
{
    BYTE    Name[13];       /* max 12 with terminator */
    BYTE    Rate[3];        /* rate 0.00% to 9999.00% */
    BYTE    Options;        /* if BIT4 set not print */
                             /* Bit0:=1,(VAT)Ϊ����˰(��ֵ˰),��:���ۼ۸����˰;
                                     =0,(Add on)����˰(Ӫҵ˰),��:���ۼ۸񲻰���˰ */
                             /* BIT1:��ӡ˰����(Bit0Ϊ1ʱ��Ч,����ӡ����˰��)  */
                             /* BIT2:��ӡ0˰��(Bit0Ϊ1ʱ��Ч)     */
                             /* BIT3: GST tax if set*/
                             /* BIT4:��ӡ˰��(Bit0Ϊ1ʱ��Ч)     */
};



/**************** Structure Used for Modifiers **************************/

struct MODITABLE
{
    WORD    Number;
    BYTE    CapSize;        /* caption length max 24 */
};

struct MODIRECORD
{
    BYTE Name[25];
};

/**************** Structure Used for ICBlock **************************/
//ccr chipcard 2004-07-01
struct ICBLOCKTABLE
{
    WORD    Number;
    BYTE    BlockSize;      /* caption length max 10 */
};

struct ICBLOCKRECORD
{
    UnLong ICCardNO;
};


/*********************** Structure Used for IPSet ***********************/
//hf added 20040903
struct IPSETRECORD
{
    BYTE    IPAddress[4];
    WORD    ClientPort;
    BYTE    ServerIP[4];
    WORD    ServerPort;
#if defined(CASE_GPRS)
    char    APN[16];//ccr2015-03-10
    char    UserName[16];//ccr2015-03-10
    char    Password[16];//ccr2015-03-10
#endif
    BYTE    ECR_ID[8];         //For example:unitID=0x123456789ABCDEF0, 8 bytes
};
//================= hf added end =========================

/**************** Structure Used for Clerk Info **************************/

struct CLERKTABLE
{
    WORD    Number;
    WORD    RecordSize;     /* size of 1 Clerk record */
    BYTE    CapSize;        /* caption length max 12 */
};

struct CLERKRECORD
{
    BYTE Name[13];
    BYTE Options;
                //BIT0: ȡ������
                //BIT1:  ��������
                //BIT2:  ȡ������
                //BIT3:  �˻�����
                //BIT4:  %�ۿ�����
                //BIT5:  %�ӳ�����
                //BIT6:  +-�������
                //BIT7: =0,training clerk
    BYTE Passwd[3];
};

/**************** Structure Used for Time Zone Info **************************/

struct ZONETABLE
{
    BYTE    Number;
    WORD    Start[24];      /* start of zone max 24 */
};


/**************** Structure Used for Day of Week Info **************************/

struct DAYTABLE
{
    BYTE    Number;
};

/**************** Structure Used for MONTH Info **************************/
/* When DEBET is set Months are used for SalesPerson */

struct MONTHTABLE
{
    BYTE    Number;
};


/**************** Structure Used for Salesperson Info **************************/

struct SALPERTABLE
{
    WORD    Number;
    WORD    RecordSize; /* size of 1 Salesperson record */
    BYTE    CapSize;    /* caption length max 24 */
};

struct SALPERRECORD
{
    BYTE Name[25];
    BYTE Options;
};

struct OPTIONTABLE                /* structure holding new options */
{
    BYTE    ChinaChar;
    BYTE    Plu;    /* BIT 0 - Linked Plu, BIT 1 - large Dept# */
    BYTE    InvAmt; /* PLU amount inventory size */
    BYTE    Cost;   /* BIT 0 if set then ALL Salesdata ex VAT */
/* If DANKORT set and BIT 0 not then always */
/* Subtract TAX 1 from Net Sales */
/* BIT 1 if set COSTPRICE system Active */
/* BIT 2 if set then report difference between */
/* entered price and programmed price as discount */
/* BIT 3 if set then print costcode on rececipt */
/* BIT 4 if set then don't print price in Cost */
/* Code */
/* BIT 5 Calculate Profit Ratio */
    WORD    TendBuffer;     /* Number of Entries in Tender Buffer */
    BYTE    TendAmtSize;
    BYTE    TendNumberSize;
    BYTE    Modulo;
    BYTE    WeightF[8];     /* WeightFactor for Modulo Check */
    BYTE    NotUsed;
};

#if DEBET == 1
/**************** Structure Used for Debet Card Info *****************/


struct DEBETTABLE
{
    WORD List;      /* black list entries */
    WORD NonSub;     /* Non subtract table */
    WORD Shift;     /* Shift entries */
    WORD SalPer;    /* Salesperson entries */
    BYTE Print;     /* Print Format */
/* BIT 0 -> Journal */
/* BIT 1 -> Receipt */
/* BIT 2 -> Double Heigth */
/* BIT 3 -> Slip */
/* BIT 4 -> Compulsory Slip */
/* BIT 5 -> 2 line */
    BYTE Option1;
/* BIT 0 -> Minus Allowed */
/* BIT 1 -> Add Change */
    BYTE Option2;
    BYTE PFormat;     /* Print Format */
/* BIT 0 -> print Company Code */
/* BIT 1 -> print Card# */
/* BIT 2 -> print Old Balance */
/* BIT 3 -> print New Balance */
    BYTE Max[3];    /* max amount */
    BYTE DisableShift;  /* shift used for disable card */
    BYTE DisableSalPer;  /* SalesPerson used for disable card */
    BYTE FreeVendId;    /* Shift on CARD used for FreeVend */
    BYTE FreeVendShift; /* shift used for freevend */
    BYTE StartSalPer;   /* start Salesperson on GiroVend */
    BYTE Free[12];  /* future use */
};
#endif
/*************************************************************************/

/*********** definition of the all texts used  ***********/

struct GRAPFORPRN
{
    BYTE    PictNo;//0:no picture for use
    BYTE    DateFrom[4];
    BYTE    DateTo[4];
};


struct APPTEXT
{
    BYTE    Header[8][PRTLEN+1];    /* max width printer 32 char */
    BYTE    ReportType[17][REPWIDTH];
    BYTE    SlipHeader[6][SHEADWIDTH+1];
    BYTE    Trailer[6][PRTLEN+1];
};


struct PROMRECORD
{
    WORD    Freq;
    BYTE    JollyMin[4];
    BYTE    PointVal[4];
    BYTE    PointMin[4];
    BYTE    GrapIdx;
    BYTE    Memo[PRTLEN+1];
};

struct  ICCARDSETTABLE  //ccr chipcard 2004-07-01
{
    BYTE Options;
    unsigned char Password[3];
    unsigned long PosCode;
    unsigned char Value[3];
    unsigned char MiniNum[3];

} ;

//ccr2016-03-15>>>>������̺�>>>>>
struct  MACRODEFINE
{
    char Name[MACRONAME];
    WORD FuncList[KEYS1MACRO];
} ;
//ccr2016-03-15<<<<<<<<<<<<<<<<<<<

//ccr2016-05-31>>>>>>>>>>>>>>>>>>>
#if defined(CASE_INDIA)
struct  TECRNUMBER     //UPDATEECRNO 95     //�����տ����
{
    BYTE Location;//decimal data,>>>ApplVar.AP.Flag[14]	//Location number of ECR
    BYTE Register;//decimal data,>>>ApplVar.AP.Flag[15]	//Register number of ECR
};

struct  TRECNUMBER     //UPDATERECNO 96      //�����վݺ�
{
    BYTE ReceiptNumber[RECNUM];       /* >>>>>>>>>!!!  receipt number BCD max 999999 */
};

#endif
//ccr2016-05-31<<<<<<<<<<<<<<<<<<<

//ccr2016-09-13>>>>>>>>>>>>>>>>>>>
#if defined(CASE_PERU)

#define MESS_CUSTOMER   BIT0   //�˿���Ϣ
#define MESS_SALLER     BIT1   //�̼���Ϣ

#define CUSTLINES       6       //�˿���Ϣ����
#define CUSTWIDTH       (PRTLEN+1)    //�˿���Ϣ�ַ���

struct  TRECMESSAGE
{
    BYTE CopyOfMess;          //0:û��������Ϣ;���򱣴�Messages[0][0],���ڸ����վ�
    BYTE Messages[CUSTLINES][CUSTWIDTH]; //ccr2016-10-24
};
#endif
//ccr2016-09-13<<<<<<<<<<<<<<<<<<
/*********** definition of the complete application structure ***********/
/* Please note that Flag is used in ASM files so please check when
structure AP changes
*/

struct APPLICATION
{

    BYTE                FirmKeys[FIRMKEYS];     /* firm key used when lock not in RG or MG */
    BYTE                Manager[16];        /* manager table max 128 keys */
    BYTE                Flag[SYSFLAGS];  /* system flags for general options */

    WORD                KeyTable[MAXKEYB];      /* KeyTable */

    UnLong              StartAddress[AddrMAX];

    struct PASSWORD     ModePwd;
    struct CCONFIG      Config;

    struct CLERKTABLE   Clerk;
    struct SALPERTABLE  SalPer;
    struct FIXEDREPORT  ReportList[XZNUM];

    struct TOTALSALES   Sales;
    struct CORRECTABLE  Correc;
    struct CURRTABLE    Curr;
    struct DEPTTABLE    Dept;
    struct DISCTABLE    Disc;
    struct DRAWERTABLE  Draw;
    struct GROUPTABLE   Group;
    struct MODITABLE    Modi;
    struct PBTABLE      Pb;
    struct PLUTABLE     Plu;
    struct PORATABLE    PoRa;
    struct TAXTABLE     Tax;
    struct TENDTABLE    Tend;
    struct ZONETABLE    Zone;
    struct DAYTABLE     Day;
    struct MONTHTABLE   Month; /* for DEBET month used as salesperson */
    struct OPTIONTABLE  Options;
    struct OFFTABLE     OFFPrice;
    struct PORTTABLE    Port;
    struct PROMRECORD   Promotion;
    struct AGREETABLE   Agree;
    struct ICBLOCKTABLE ICBlock;  //ccr chipcard 2004-07-01
    struct MACRODEFINE  KeyMacros[KEYMACROMAX];//ccr2016-03-15>>>>������̺�>>>>>

};

struct DEFAULT
{
    struct CORRECRECORD Correc[corrNumber];
    struct CURRRECORD   Curr[currNumber];
    struct DISCRECORD   Disc[discNumber];
    struct DRAWERRECORD Draw[drawNumber];
    struct PBRECORD     PbF[pbNumber];
    struct PORARECORD   PoRa[poraNumber];
    struct TENDRECORD   Tend[tendNumber];
    struct TAXRECORD    Tax[taxNumber];
    struct MODIRECORD   Modi;
    struct CLERKRECORD  Clerk;
    struct GROUPRECORD  Group;
    struct DEPTRECORD   Dept;
    struct PLURECORD    Plu;
    struct SALPERRECORD SalPer;
    struct OFFRECORD    OFFPrice;
    struct PORTRECORD   Port;
    struct GRAPFORPRN   Graph;
    struct AGREERECORD  Agree;
    struct ICBLOCKRECORD ICBlock;  //ccr chipcard 2004-07-01
    struct IPSETRECORD IP;      //hf added 20040907
};


typedef union
{
    //>>>>>>Record for ECR Files>>>>>>>>>>>>>>
    struct PLURECORD   BarCustomer;
    struct CLERKRECORD  Clerk;
    struct CORRECRECORD Correc;
    struct CURRRECORD   Curr;
    struct DEPTRECORD   Dept;
    struct DISCRECORD   Disc;
    struct DRAWERRECORD Draw;
    struct GROUPRECORD  Group;
    struct MODIRECORD   Modi;
    struct PBRECORD     PbF;
    struct PLURECORD    Plu;
    struct PORARECORD   PoRa;
    struct TAXRECORD    Tax;
    struct TENDRECORD   Tend;
    struct PBTOTAL     PB;
    struct OFFRECORD    OFFPrice;
    struct AGREERECORD  Agree;
    struct ICBLOCKRECORD ICBlock;  //ccr chipcard 2004-07-01
    struct SALPERRECORD  SalPer;

} ECRFILEREC;

typedef union {
    struct DEPTTABLE    Dept;
    struct PLUTABLE     Plu;
} ECRFILEDEF;

#include "flowbill.h"  //lyq2003
#include "ICCard.h"		//ccr chipcard
#include "CHNMess.h"           //cc update 2005-03-17

struct DISPLAY_RGBUF
{/* ���������Ŀ���ݿ��� */
    short FirstRGNum; /* ��ǰ��ʾ��������Ŀ��һ����Ŀ */
    short LastRGNum; /* ��ǰ��Ļ����ʾ��������Ŀ�����һ����Ŀ */
    WORD  RGCount;  /* ��������ʾ��������Ŀ���� */
};



#if defined(DEBUGBYPC)

#define xputs   puts
#define xprintf printf

#define TEXTSOFGRAPH  8             //���������ͼƬ���ı�����
#define MAX_PRNPOOL 	101         //<250 && >TEXTSOFGRAPH must

struct TPRN_POOL
{
    BYTE Length;    //Length of the text for print
    BYTE GraphicNo; //=0,print text;>0,print a graphic and ApplVar.Prn_Command is the  lines of text for graphic
    BYTE Prn_Command;   //command for print or text lines for graphic
    BYTE data[32];//text for print
};
#endif
//***************************************************************************
struct RECEPTITEMS
{/* ���������վݵ���Ŀ��Ϣ */
    int    RGNumber;                           /* pointer in Transaction Buffer */
    struct TRANSRECORD  RGBuf[TRANSITEMS];    /* Transaction Buffer:��������һ����Ŀ������������Ŀ */
};

struct RGSUSPEND
{/* �������������վݵ���Ŀ��Ϣ */
    WORD
        ClerkNumber;
    BCD
        SaleAmt,
        SaleQty,
        TaxItem[8];
    struct RECEPTITEMS SuspendItems;
};
//ccr2016-12-14 ���ô�ӡ������
typedef struct
{
    BYTE port;//��ӡ��ʹ�õĴ��ں�
    BYTE type;//��ӡ���ͺ�
} TEXTPRINTER;
//***************************************************************************
//ccr2016-12-27�����վݺ�
typedef struct
{
    BYTE ZCount[ZSIZE],              /* z-count BCD max 999999 ������ΪWorking Memory�ĵ�һ������*/
         ReceiptNumber[RECNUM+TRAINNUM];       /* >>>>>>>>>!!!  receipt number BCD max 999999 */
} TCOUNTER;

//vvvvvvvvvvvvvvvvvvvvvvvvvv For Cortex-M3 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//�ѳ�ʼ����Ϣ���浽FLASH��
//APPLICATION_SAVE
typedef struct
{
/****************Config for system*******************************************/
    WORD   InitFlags[4];//InitFlags����Ϊ��һ������,//ccr2017-11-30���Ӵ洢��������Ĵ�С

    ULONG  SIZE_EXTRAM; //size of SRAM

    struct APPTEXT TXT;         /* structure containing all texts */
    struct APPLICATION AP;      /* must start at 0x8400 for memory clear */
    struct PORTRECORD   PortList[portNumber];
    struct IPSETRECORD IP;      //hf added 20040907 // lqw add default value.
    struct GRAPFORPRN   Graph[GRAFESTMAX+2];
    //Graph[0]:Ϊ��ӡ��Ʊͷ��ͼƬ
    //Graph[1..GRAFESTMAX]:Ϊ��ָ����ʱ������ӡ��ͼƬ
    //Graph[GRAFESTMAX+1]:Ϊ��ӡ��Ʊβ��ͼƬ
    struct ICCardSetTable ICCardSet;   ////ccr2016-05-13 chipcard & ECRVIP

/************************ Working Memory lay-out ************************/

    BYTE
        ZCount[ZSIZE],              /* z-count BCD max 999999 ������ΪWorking Memory�ĵ�һ������*/
        ReceiptNumber[RECNUM+TRAINNUM];       /* >>>>>>>>>!!!  receipt number BCD max 999999 */
#if defined(CASE_QRCODE)
    BYTE
        QRCode[2][MAX_QRCODE];//ccr2016-06-29΢�ź�֧��������
#endif
    BYTE                    //��λʱ�����뽫���±�����0   //
        CopyReceipt,
        ReportNumber;

    WORD
        PromCounter,        // counter for promotion
        EmptyBlock,       /* first empty block in track buffer */
        PbInvoice;

    UnLong AutoCheck ;

/*************************************/

    BYTE
        ePosPort,               //cc epos  eͨ�������Ӵ��ں�.0-������1������0��2������1 //
        DeptKeys,
        PluKeys,
        DownLoad,               //=0x00,	not on download mode
        //=0x1B,	DownLoad BIOS,HEX format,the data will be write into EEPROM
        //=0x1C,	DownLoad CCLIB,HEX format,the data will be write into EEPROM
        //=0x2C,	DownLoad CCLIB,binary format,the data will be write into EEPROM
        //=0x1D,	DownLoad Data,HEX format,the data will be write into RAM
        //=0x2D,	DownLoad Data,binary format,the data will be write into RAM

        FuncOnEnter,

    #if GREEK == 1
        ArrowsFlag,
    #endif
        AmtDecimal,             /* used in format routines if 1 then no decimal in */
        /* amount */

        ArrowsAlfa,
        BufCC,                  /* if 1 then add CC byte instead of bit for speed */
        BufCmd,                 /* used in StoreInBuffer */
        BufKp,                  /* if 1 then print KP */
        BufRec,                  /* If 1 then second receipt */
        /* set to one before calling ProcessBuffer */
        CancelNumber,
        CancPrint,
        ClerkLock,              /* Current Clerk Lock Position */
        CorrecNumber,
        CurrNumber,
        Day,
        DecimalPoint,           /* decimal point count */
        DiscNumber,
        DrawNumber,
        ErrorNumber,            /* if not zero then error condition */
        FBalance,       //cc 2006-06-29 for Balance
        FBarcode,               /* entry is barcode or In Store Marking !!*/
        FBuffer,                /* if set then regi buffer full(���۴洢��RGBuf���� */
        FCanc,                  /* if 1 then normal cancel else non add */

        FCorr,                  /* flags is non zero set */
        FCurr,                  /* currency used */

        FInv,                   /* if 1 then ADD inventory */
        /* if 2 subtract inventory */

    #if FISCAL == 0
        FJournal,
    #endif
        FKpGroup,                 /* if set disable seperate tickets on KP */
        FNoPb,                  /* if BIT 0 set to 1 then no pb compulsion for */
        /* 1 transaction, if BIT1 to 1 then no */
        /* tender allowed after open/add PB function unless */
        /* paper is in slip */
        /* if BIT 2 set then print PB Trailer with tender */
        /* and store invoice number when used */
        FNoTax,                 /* if set then no tax calculation */
        FNoTime,                /* if set then print no time in trailer line */
        FNum,                   /* number entered */
        FPb,                    /* if set then pb open */
        FPlu,                   /* if set then plu */
        FPrice,
        FProforma,              /* if set then proforma transaction */
        FReceipt,
        FRecIssue,              /* if set then Receipt issue key used */
        FRefund,
        FRegi,
        FReport,                /* if set report in progress */
        FTrain,
        FSale,
        FSplit,                 /* split bill */
        FTend,
        FVoid,
        KeyNo,
        ModiCount,              /* number of entered modifiers */
        Month,      /* for DEBET month used as salesperson */
        MultiplyCount,          /* number of times multiply used */
        OldModiCount,
        OldMultiCount,
        OpDraw,             /* open drawer */
        PbFNumber,          /* pb function number */
        PbSplit,            /* flag use din PBBUFFER */
        PluPriceLevel,
        PointerType,         /* pointertype used in addpointertotal */
        PoRaNumber,
        PrintLayOut,            /* Print Construction */
        RepComputer,            /* if set then computer report */
        RepeatCount,            /* repeat counter used by void */
        SlipDouble,             /* if set the double wide on slip */
        SlipLines,            /* if 1 then paper in slip */
        SlipPage,               /* slip page number */
        TaxNumber,
        TaxPerm,                /* permanent tax shift */
        TaxTemp,                /* temporary tax shift */
        TaxTemp1,               /* used for void and repeat */
        TendNumber,
    #if FISCAL == 0
        Zone,
    #else
        Zone,
        FJournal,               /* is set the journal used */
    #endif                     /* Add NEW FLAG at the END because of location */
        /* Receipt Number for Fiscal versions */
        FNFolio,                        /* if set then new folio */
//        FSuspend,
        FTrvoid,
        FMixMatch,
    #if PLUENQ == 1 || BOTTLE == 1
        FPluEnq,                                /* if set process plu as enquiry */
    #endif
        SubDiscFlag,	/*cc 2006-10-11 for SubDisc
						BIT0:	SubDisc
						BIT1:	Void
						BIT2:	Corr
						BIT3:	ApplVar.DiscItem
						*/
        FSub;                   /* if set then last item was mixmatch */

    short
        PluArtLevel,        /* article shift */
        NumberEntry;    //add by lqw ..

    ULONG
        MyFlags;                /* flags for appliction */

    WORD
        AgreeNumber,
        OFFNumber,
        CentralLock,            /* Current Central Lock Position */
        ClerkNumber,
        SaveClerk,              /* used for clerk storage during report */
        DeptNumber,
        GroupNumber,
        ICBlockNumber,  //ccr chipcard 2004-07-01
        MacroNumber,   //ccr2016-03-15=0,û��ִ�к�����

    #if MA  == 0
        MenuPoint[10],
    #endif
        ModiNumber,             /* modifier number */
        ModNum[4],                /* modifiers for article */

        OldClerk,               /* old clerk used for clerk change check */
        PbNumber,
        PluNumber,
        SalPerNumber,
        SaveSalPer,
        OldSalPer,
        omax,
        nmax,
        errplu,

        PluDept;

    char *ModeHead;

    struct  ICStruct IC;                //ccr chipcard

    #if (BARCUSTOMER==1)
    struct PLURECORD   BarCustomer;
    #endif


    struct CLERKRECORD  Clerk;
    struct CORRECRECORD Correc;
    struct CURRRECORD   Curr;
    struct DEPTRECORD   Dept;
    struct DISCRECORD   Disc;
    struct DRAWERRECORD Draw;
    struct GROUPRECORD  Group;
    struct MODIRECORD   Modi;
    struct PBRECORD     PbF;
    struct PLURECORD    Plu;
    struct PORARECORD   PoRa;
    struct REPORT       Report;
    struct REPSIZE      Size;           /* used in Total Routines */
    struct TAXRECORD    Tax;
    struct TENDRECORD   Tend;
    struct TOTAL        Total;
    struct TRANSRECORD  RGRec;          /* temporary record:�������һ��������Ŀ���������� */

    struct RECEPTITEMS  RGItems;        /* Transaction Buffer:��������һ����Ŀ������������Ŀ */

    struct  PBTOTAL     PB;
#if !(SKIP & S_PB)
    struct  PBARTICLE   PBA;             /* used for temporay pbbuffer storage */
#endif
    struct  KPINFO      KP;
    struct OFFRECORD    OFFPrice;
    //0:Used for SHOP TYPE
    //1..GRAFESTMAX:used for FESTIVAL
    //GRAFESTMAX+1:Used for LOGO
    struct AGREERECORD  Agree;
    struct ICBLOCKRECORD ICBlock;  //ccr chipcard 2004-07-01
    struct SALPERRECORD  SalPer;


    union KEY
        DispKey,        //cc 2006-08-14 for Caption
        Key,
        OldKey;

    short
        NewPlu,
        OldPlu ;

    BCD
        Amt,                     /* Qty X Price */
        SUB_DiscTot,						/* cc 2006-10-11 for SubDisc */

        Cost,
        DiscAmt,                /* �ۿۺ���	cc 2006-10-20 for SubDisc */
        DiscItem[2],            /* discount selection itemizers */
        Entry,                  /* Entry in BCD format */
        MixQty,                 /* used for Mix Match */
        NumberEntered,      /* store number entered */
        Price,                  /* Item Price (Dept or Plu) */
        Qty,                    /* Total Qty */
        Qty1,                   /* Qty1, Qty2 and Qty3 used with Multiplication */
        Qty2,
        Qty3,
        RetQty,                 /* used during total update */
        SaleAmt,                /* Total Sales Amount */
        SaleQty,                /* Total Sales Qty */
        SubTotal,               /* subtotal amount used in tender and subtotal */

        TaxItem[8],
        PluInventory;               //<<<<<<<<<!!!!!

    //��ˮ���ݹ���>>>>>>>>>>>>>>>>>>>>>>>>>
    struct 	FifoHeader FlowHeader;
    struct 	GIVEN_DATA CollectGiven[TENDLOGMAX];
    BYTE 	GCouter;
    union  FLOWREC	FlowBuff;
    //��ӡ������>>>>>>>>>>>>>>>>>>>>>>>>>>>

    char GrafTexts[TEXTSOFGRAPH][(PRTLEN +1)];

#if !defined(CASE_INNERDOTPRN)
    struct TPRN_POOL PoolForPrint[MAX_PRNPOOL];//��ӡ�������
    BYTE    PoolPushIn;
    BYTE    PoolPopOut;
    BYTE    Prn_Command;
#endif
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //��ʾ���ݱ�����
    char LCD_Operator[DISLEN],LCD_Customer[DISLEN];//LCD_Operator[0]!='\0'ʱ������ʱ��ʾ���е�����

    BYTE    ScreenMap[SCREENLN+STATELN][SCREENWD];
    WORD    ScreenStat;
    CURSOR  sCursor;
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if (defined(CASE_GPRS))
    BYTE    DaysMust;        //��С������ˮ���ݼ��������=0ʱ����������������
                             //BIT7Ϊ�Ƿ��Զ�������ˮ���ݣ�=1ʱΪ���ʺ������Զ�������ˮ
    WORD    LastDaysLog;     //���һ�η�����ˮ������
#endif

//ccr2016-09-13>>>>>>>>>>>>>>>>>>>>
#if defined(CASE_PERU)
    struct  TRECMESSAGE CustomerMessage;   //��������Ϣ
#endif

//ccr2016-10-24>>>>>>>>>>>>>>>>>>>>
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
    TEJVAR   EJVar;
    TEJHEADER EJHeader;
    TEJDOCHEAD EJDocHeader;
    TEJROLL EJRoll;
#endif
//ccr2016-10-24<<<<<<<<<<<<<<<<<<<<
    TEXTPRINTER ExtPrinter;
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    WORD    ApplFlags;
//		ApplVarCRC must be the last , The new variable must insert befor ApplVarCRC
    BYTE
        ApplVarCRC;            //CRC of ApplVar

}  APPLICATION_SAVE;

#define Config_SIZE  (sizeof(ApplVar.InitFlags)\
                     +sizeof(ApplVar.SIZE_EXTRAM)\
                     +sizeof(ApplVar.TXT)\
                     +sizeof(ApplVar.AP)\
                     +sizeof(ApplVar.PortList)\
                     +sizeof(ApplVar.IP)\
                     +sizeof(ApplVar.ICCardSet)\
                     +sizeof(ApplVar.Graph))

#define AppVAR_SIZE (sizeof(APPLICATION_SAVE)-Config_SIZE)

//efine PREHEADER	3	// �վ�Ԥ��ӡ��Ʊͷ����,PANAMA�汾ʱ,��ֵ��ҪС��3  //
                        //ccr2016-11-14 ƱͷΪ���ߴ�ӡ��ʽʱ��Ҫ������ֵ
#define PREHEADER	0 //jdb2018-10-08��Ԥ��ӡƱͷ
//ccr2016-01-18>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define MGFUNCS     11

#define PORTRATENUM 8   //��������������Ŀ

#define LINKTYPENUM (portNumber+1) //�豸����������Ŀ
//GetDevicePort-pType:0-����,1-����ǹ,2-���ӳ�,3-������ӡ��,4-Ʊ�ݴ�ӡ��,5-���ô�ӡ��
#define FORHOST     0
#define FORBARCODE  1
#define FORBALANCE  2
#define FORKPRINTER 3
#define FORSLIPPRN  4
#define FOREXTPRN   5   //ccr2016-12-14 ExtPrinter����
#if (CASE_EPOS)
#define FOREPOS    6   //ccr2016-12-14 ExtPrinter����
#define DEVICENUM   7   //same as portTypeNum
#else
#define DEVICENUM   6   //same as portTypeNum
#endif


#if (DEVICENUM!=portTypeNum)
#error "DEVICENUM!=portTypeNum"
#endif
#define DOUBLELINE  0   //ccr2016-01-20�Ƿ񽫱�������������ʾ

// for ListItems
#define It_EXIT    0xfffe
#define It_PLU_MG 0xffff

#pragma pack(4)

//ccr2016-03-24...���ڹ����ļ��ռ�..................................
#define CLERKIDX    0
#define SALERIDX    (CLERKIDX+1)
#define DEPTIDX     (SALERIDX+1)
#define PLUIDX      (DEPTIDX+1)
#define OFFIDX      (PLUIDX+1)
#define REPORTIDX   (OFFIDX+1)
#define CORRIDX     (REPORTIDX+1)
#define CURRIDX     (CORRIDX+1)
#define DISCIDX     (CURRIDX+1)
#define TENDIDX     (DISCIDX+1)
#define DRAWIDX     (TENDIDX+1)
#define PORAIDX     (DRAWIDX+1)
#define GROUPIDX    (PORAIDX+1)
#define PBIDX       (GROUPIDX+1)
#define PBTIDX      (PBIDX+1)
#define TAXIDX      (PBTIDX+1)
#define ZONEIDX     (TAXIDX+1)
#define MODIIDX     (ZONEIDX+1)
#define PROMIDX     (MODIIDX+1)
#define AGREEIDX    (PROMIDX+1)
#define ECRLOGIDX   (AGREEIDX+1)
#define ICSETIDX     (ECRLOGIDX+1)
#define ICBLOCKIDX     (ICSETIDX+1)
#define ECRREPIDX   (ICBLOCKIDX+1)
#define ECRRAMIDX   (ECRREPIDX+1)
#define IDXMAX	    (ECRRAMIDX+1)
//ccr2016-12-20>>>>>>>>>>>>>>>>>>>>>>>
#define AtEntryBuffer(p) EntryBuffer[sizeof(EntryBuffer) - p - 1]

//ccr2017-03-16���ӳ��ͺ�>>>>>>
#define BALTYPEMAX  3
#define BAL_TOLEDO  0
#define BAL_DIBAL   1
#define BAL_PS1X    2
//ccr2017-03-16<<<<<<<<<<<<<<<<
#endif
