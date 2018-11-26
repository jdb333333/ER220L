#ifndef MESSAGEH_EN_P
#define MESSAGEH_EN_P

// Printer
#if (PRTLEN>40)
                       //.123456789.123456789.123456789.123456789.1
#define Header1         "*       THANKS    FOR    SHOPPING        *"        //" 	 �� �� �� ��  �� �� �� ��   *"
#define Header2         "*     Eutron      Cash     Register      *"         //" 	 �� �� �� ��     �� �� �� ��   *"

#else
                       //.123456789.123456789.123456789.1
#define Header1         "*     THANKS FOR SHOPPING      *"        //" 	 �� �� �� ��  �� �� �� ��   *"
#if defined(CASE_INDONESIA)
#define Header2         "*   Posibolt Cash Register     *"         //" 	 �� �� �� ��     �� �� �� ��   *"
#else
#define Header2         "*     Eutron Cash Register     *"         //" 	 �� �� �� ��     �� �� �� ��   *"
#endif
#endif
// Printer
#define ReportType0     "  GRAND TOTAL   "        //"   ��  ��  ��   ",
#define ReportType1     "  GROUP         "        //" ��  ��  ��  �� ",//1
#define ReportType2     "  DEPARTMENT    "        //" ��  ��  ��  �� ",//2
#define ReportType3     "  PLU           "        //" ��  Ʒ  ��  �� ",/* 3 Used with ApplVar.Plu ApplVar.Report */
#define ReportType4     "  TENDER        "        //" ��  ��  ��  Ϣ ",//4
#define ReportType5     "  PORA          "        //" �� �� �� �� Ϣ ",//5
#define ReportType6     "  DRAWER        "        //" Ǯ  ��  ��  Ϣ ",//6
#define ReportType7     "  CORRECTION    "        //" ��  ��  ��  Ϣ ",//7
#define ReportType8     "  DISCOUNT      "        //" ��  ��  ��  Ϣ ",//8
#define ReportType9     "  CURRENCY      "        //" ��  ��  ��  Ϣ ",//9
#define ReportType10    "  TAX           "        //" ��  ˰  ��  Ϣ ",//10
#define ReportType11    " PB FUNCTIONS   "        //" ��  ��  ��  Ϣ ",//11
#define ReportType12    "PREVIOUS BALANCE"        //" ��  ̨  ��  Ϣ ",//12
#define ReportType13    "  TABLES        "        //" ��  ̨  ��  Ϣ ",//13
#define ReportType14    "  INVENTORY     "        //" ��  Ʒ  ��  �� ",//14
#define ReportType15    "  PB INVOICES   "   //
#define ReportType16    "  TENDER BUFFER "    //
// Printer
#define ReportType17    "  CLERK TOTAL   "  //"    �� �� Ա ͳ ��   ",
#define ReportType18    "  SALPER TOTAL  "  //"    Ӫ ҵ Ա ͳ ��   ",
// Printer
#define Trailer1        "        THANK YOU       "        //"     ~��  ~л  ~��  ~��     ",
#define Trailer2        "        GOODBYE       "        //"          ~��  ~��         ",


#define ReportList1     "CLERK DAILY"        //" �� �� Ա �� �� ",
#define ReportList2     "CLERK PERIOD"        //" �� �� Ա �� �� ",
#define ReportList3     "DAILY REPORT"        //" ��  ��  ��  �� ",
#define ReportList4     "PERIOD REPORT"        //" ��  ��  ��  �� ",
#define ReportList5     "PLU  REPORT"        //" ��  Ʒ  ��  �� ",
#define ReportList6     "TABLE REPORT"        //" ��  ��  ��  �� ",
#define ReportList7     "TIME ZONE"        //" ʱ  ��  ��  �� ",
#define ReportList8     "ALL CLERK DAILY"        //"  ȫ�տ�Ա�ձ�  ",
#define ReportList9     "ALL CLERK PERIOD"        //"  ȫ�տ�Ա�±�  ",
#define ReportList10    "SALESPER.DAILY"        //" Ӫ ҵ Ա �� �� "
#define ReportList11    "SALPR.PERIODICAL"        //" Ӫ ҵ Ա �� �� "
#define ReportList12    "ALL SALPR.DAILY"        //"  ȫӪҵԱ�ձ�  ",
#define ReportList13    "ALL SALP.PERIOD"        //"  ȫӪҵԱ�±�  ",

#define Promotion1      "  CONGRATULATIONS   "        //"  ~��  ~ϲ  ~��  ~��",

#define Correc1         "CORRECT "        //"����    "//ccr2016-07-14
#define Correc2         "VOID    "        //"ȡ��    "//ccr2016-07-14
#define Correc3         "REFUND  "        //"�˻�    "
#define Correc4         "CANCEL  "        //"ȡ������"
#define Correc5         "SUSPEND "      //"����"


#define CURRENCY1         "DOLLAR  "        //"��Ԫ    "L��ӡ/��ʾ
#define CURRENCY2         "YEN     "        //"��Ԫ    "L��ӡ/��ʾ
#define CURRENCY3         "HK $    "        //"�۱�    "L��ӡ/��ʾ
#define CURRENCY4         "CURR   1"        //"���1   "L��ӡ/��ʾ
#define CURRENCY5         "CURR   2"        //"���2   "L��ӡ/��ʾ

#define DISCOUNT1          "+%"        //"+%�ӳ�"     L��ӡ/��ʾ
#define DISCOUNT2          "-%"        //"(-%)�ۿ�"   L��ӡ/��ʾ
#define DISCOUNT3          "+NET"        //"���ӳ�"    L��ӡ/��ʾ
#define DISCOUNT4          "-NET"        //"����ۿ�"    L��ӡ/��ʾ
//#define DISCOUNT5          "+% ON PLU"   // zy //"����ӳ�"
//ccr090812 for SubDisc>>>>>>>>>>>>>>>>>>>>>>>>>
#define DISCOUNT6          "SUBTOTAL+%"   //  "+%С�Ƽӳ�"L��ӡ/��ʾ
#define DISCOUNT7          "SUBTOTAL-%"   //  "-%С���ۿ�"L��ӡ/��ʾ
#define DISCOUNT8          "SUBTOTAL+"   // "С�ƽ��ӳ�"L��ӡ/��ʾ
#define DISCOUNT9          "SUBTOTAL-"   // "С�ƽ���ۿ�"L��ӡ/��ʾ

#define DRAWER1            "CASH    "        //"�ֽ�    "L��ӡ/��ʾ
#define DRAWER2            "CHECK   "        //"֧Ʊ    "L��ӡ/��ʾ
#define DRAWER3            "CREDCARD"        //"���ÿ�  "L��ӡ/��ʾ
#define DRAWER4            "COUPON  "        //"����ȯ  "L��ӡ/��ʾ
#define DRAWER5            "CREDIT  "        //"����    "L��ӡ/��ʾ
#define DRAWER6            "CHIPCARD"        //"IC��    "L��ӡ/��ʾ
#if  defined(CASE_INDONESIA)
#define DRAWER7            "DEBIT   "        //"С��    "L��ӡ/��ʾ
#else
#define DRAWER7            "FEE     "        //"С��    "L��ӡ/��ʾ
#endif
#define DRAWER8            "DRAW-8  "//��ӡ/��ʾ

#define PBFunction0         "OPEN    "        //   "��̨����"
#define PBFunction1         "ADD     "        //   "��̨����"
#define PBFunction2         "SERVICE "        //   "�ݽ�"
#define PBFunction3         "FINALIZE"        //   "ȷ�Ͻ���"
#define PBFunction4         "PRINT PB"        //   "��ӡ��̨"
#define PBFunction5         "PRT BILL"        //   "��ӡ�ʵ�"
#define PBFunction6         "CANCEL  "        //   "ȡ��ȷ��"
#define PBFunction7         "SPLIT   "        //   "����"
#define PBFunction8         "TRANSFER"        //   "ת��"
#define PBFunction9         "MOVE TO "        //   "ת����"
#define PBFunction10        "COVER   "        //   "����"


#define PORAType1            "PO      "        //"����    "
#define PORAType2            "RA      "        //"���    "
#define PORAType3            "RETURN"        //"IC���˿�"
#define PORAType4            "CHARGE  "        //"IC����ֵ"
#define PORAType5            "DEPOSIT "        //"��ICѺ��"
#define PORAType6            "FOREGIFT"        //"��ICѺ��"

#define TendType1             "CASH       "        //"�ֽ�    "
#define TendType2             "CHECK      "        //"֧Ʊ    "
#define TendType3             "CREDIT CARD"        //"���ÿ�  "
#define TendType4             "COUPON     "        //"����ȯ  "
#define TendType5             "CREDIT     "        //"����"
#define TendType6             "CHIPCARD   "        //"ICCard"
#define TendType7             "DEBIT CARD "        //"DEBIT CARD"
#define TendType8             "CASH-8     "        //"CASH-8"


#define OperationN3             "TOTAL"  // "�ܼ�",
#define OperationN4             "CONVERT"  // "ת��",
#define OperationN5             "SUBTOTAL"  // "С��",
#define OperationN6             "PO"  // "����",
#define OperationN7             "RA"  // "���",
#define OperationN8             "REPORT"  // "����",
#define OperationN9             "ADD"  // "����",
#define OperationN10            "HOLD"  // "�ҵ�,
#define OperationN11            "VOID"  // "ȡ��",

#define OperationN14            "PRICE"  // "����:",     //
#define OperationN15            "AMOUNT"  // "���:",//

#define CaptionN2               "NET AMOUNT"  // "����",
#define CaptionN4               "TOTAL TRADE"  // "������",
#define CaptionN5               "QUANTITY"  // "����",
#define CaptionN6               "AMOUNT"  // "���",
#define CaptionN7               "COLLECT"  // "��ȡ",
#define CaptionN9               " "  // "��",
#define CaptionN10              " "  // "��",
#define CaptionN11              "-"  // "��",
#define CaptionN12              "-"  // "��",
#define CaptionN13              "STANDARD"  // "��׼",
#define CaptionN14              "CLERK"  // "�տ�Ա",
#define CaptionN15              "   HOUR"  // "ʱ",
#define CaptionN16              "  "  // "   ��",
#define CaptionN17              " --"  // "   ��",
#define CaptionN18              "REFUND"  // "�˻�",
#define CaptionN19              "COST"  // "�ɱ�",
#define CaptionN20              "TABLE# "  // "����#",
#define CaptionN21              "CHEQUE#"  // "֧Ʊ��#",
#define CaptionN22              "ITEMS"  // "����:",
#define CaptionN23              "TAXABLES"  // "��˰����",
#define CaptionN24              "TAX "  // "˰��",
#define CaptionN25              "PAGE"  //  "ҳ��",
#define CaptionN26              "NOADD#"  // "����:",
#define CaptionN27              "SERVICE"  // "����",
#define CaptionN28              "PREVIOUS BALANCE"  // "��̨",
#define CaptionN29              "Z-COUNT"  // "���ʼ���",
#define CaptionN30              "CLEAR"  // "���",
#define CaptionN31              "S-REPORT"  // "S-����",ʲô��S-REPORT? ZWQ
#if HOR_REPORT==1
#define CaptionN32              "GROSS PROFIT"  // "ë��",
#else
#define CaptionN32              "GROSS PROFIT"  // "ë��",
#endif
#define CaptionN33              "STOCK INCREASED"  // "�������",//
#define CaptionN331             "STOCK DECREASED"  // "�������",//
#define CaptionN34              "FORMER PB"  // "ԭ����:",
#define CaptionN35              "CREDIT CARD#"  // "���ÿ�#",
#define CaptionN36              "NEW TABLE"  // "������:",
#define CaptionN37              "GUESTS"  // "����",
#define CaptionN38              "EXCHANGE"  // "����",

//Dispaly
#define CaptionN41              "DISCOUNT 1"  // "�ۿ���1",
#define CaptionN42              "DISCOUNT 2"  // "�ۿ���2",
#define CaptionN43              "SALES AMOUNT"  // "���۶�",
#define CaptionN44              "MIX-MATCH"  // "����Ż�",
#define CaptionN45              "STOCK"  // "�������",
#define CaptionN46              "OFFER"  // "�ؼ��Ż�",
#define CaptionN51              "OPEN"  // "��̨�ݽ�",
#define CaptionN52              "ADD"  // "��̨����",
#define CaptionN53              "SERVICE"  // "�ݽ�",
#define CaptionN54              "FINALIZE"  // "ȷ�Ͻ���",
#define CaptionN55              "PRINT"  // "��ӡ��̨",
#define CaptionN56              "PRINT BILL"  // "��ӡ�ʵ�",
#define CaptionN57              "CANCEL"  // "ȡ��ȷ��",
#define CaptionN58              "SPLIT"  // "����",
#define CaptionN59              "TRANSFER"  // "ת��",
#define CaptionN60              "MOVE TO"  // "�����տ�Ա",��ϢΪ"MOV"
#define CaptionN61              "GUSET"  // "�˿�����",


#define CaptionE11              "CLERK"  // "�տ�Ա:",
#define CaptionE12              "SALESMAN"  // "ӪҵԱ:",
#define CaptionE13              "ECR#"  // "�տ����:",
#define CaptionE14              "SHOP#"  // "λ��:",

#define CaptionE17              "VERSION"  // "���а汾:",
#define CaptionE18              "POINTS"  // "�������ѵ�",
#define CaptionE19              "ADD PLU"  // "������Ʒ:",
#define CaptionE20              "DELETE PLU"  // "ɾ����Ʒ:",
#define CaptionE21              "TEST START"  // "��ʼ���>>",
#define CaptionE22              "TEST COMPLETED"  // "<<������",
#define CaptionE23              "INVENTORY"  // "���",
#define CaptionE24              "REPORT CLEARD!"  // "������ȫ��!",


#define CaptionE31              "MODIFIER"  // "˵������",


#define MessagesN5                "*** TRAINING MODE  ***"  // "*** ��ѵ״̬ ***",
#define MessagesN6                "***** POWER ON*****"  // "***** �ӵ� *****",
#define MessagesN7                "*** SPLIT TABLE ***"  // "*** �ֿ����� ***",
#define MessagesN8                "**DUPLICATE RECEIPT ***"  // "*** �����վ� ***",
#define MessagesN9                "**** SET PRICE PLU ****"  // "*** ��Ʒ��� ***",//
#define MessagesN10               "**INVENTORY+ **"  // "*** ���ӿ�� ***",
#define MessagesN101              "**INVENTORY- **"  // "*** ���ٿ�� ***",
#define MessagesN11               "***** CANCEL *****"  // "***** ȡ�� *****",
#define MessagesN12               "** INITIALIZING **"  // "** �����ʼ�� **",

#define EditN24                   "FILE           RECORDS      RAM"  // "�ļ���      ��¼��      �ռ��С"
#define EditN25                   "PORT           TYPE    PROTOCOL"  // "��������    ͨ�����   ͨ��Э��"

//PRINT                          /*123456789012345678901234567890123456*/
#if PRTLEN>40
#define TitleN1                   "NAME     QUANTITY       PRICE      AMOUNT"
#define TitleN3	                  "NAME            QTY.      AMOUNT"  //--Ʒ��   ����   ����   ���
#define TitleN4	                  "NAME                      AMOUNT "  //

#define DEPTREPORTTITLE           "DEPARTMENT         QUANTITY        AMOUNT"
#define PLUREPORTTITLE            "PLU                QUANTITY        AMOUNT"//

#else

#define TitleN1	                  "NAME      QTY.    PRICE   AMOUNT"  //--Ʒ��   ����   ����   ���
#define TitleN3	                  "NAME            QTY.      AMOUNT"  //--Ʒ��   ����   ����   ���
#define TitleN4	                  "NAME                      AMOUNT "  //
#define DEPTREPORTTITLE         "DEPARTMENT   QUANTITY     AMOUNT"
#define PLUREPORTTITLE          "PLU          QUANTITY     AMOUNT"//

#endif

#define OptionS37                 "CALL#"    //mPRNINDEX//Ccr "ȡ�˺�:",


#define EditN6                    "CONSUMED"  // "���ѽ��",
#define ChipCardN46               "CARD#"  // "��Ա��:",
#define ChipCardN47               "MEMBERSHIP"  // �� Ա �� ��


#define PLULIST                  "         PLU LIST"  // "         �� Ʒ �� Ϣ ��"
#define PLUTITLE1                "Name                         ID"  //
#define PLUTITLE2                "   >>Depart   STOCK       Price"//

#define DEPTLIST               "         Depart List"  // "         �� Ʒ �� Ϣ ��"
#define DEPTTITLE                "Name          Group       Price"        //



#define FisTextN18                "    ~FISCAL ~ PRINT~    "   //"    _�� _˰ _ӡ _��     "
#define FisTextN19                "    ~TRAIL ~ ENDING~    "   //"    _�� _װ _�� _��     "
#define FisTextN20                "    ~NON   ~ FISCAL~    "   //"    _��   _��   _˰     "


#define PRTStyleN1                       "Normal Printing"   //Normale
#define PRTStyleN2                       "DblHigh"   //Doppia altezza
#define PRTStyleN3                       "D~b~l~W~t~h"   //Raddoppio caratteri
#define PRTStyleN4                       "D~b~l~H~i~g~h"   //Dopia altezza + Raddoppio caratteri

#define ComTestN1                        "PORT#1 ERROR"   //"���� 1 ���Գ���"
#define ComTestN2                        "PORT#1 OK"   //"���� 1 ������ȷ"
#define ComTestN3                        "PORT#2 ERROR"    //"���� 2 ���Գ���"
#define ComTestN4                        "PORT#2 OK"   //"���� 2 ������ȷ"

#define ComTestN3ERR                      "PORT#3 ERROR"    //"���� 3 ���Գ���"
#define ComTestN3OK                      "PORT#3 OK"   //"���� 3 ������ȷ"


#define REPRN_PWON      "Re-Print When Power ON........." //
#define REPRN_PAPERON   "Re-Print When Paper OK......"  //

//ccr2016-01-12>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define GRAPHICSELF     "  SELF GRAPHIC"//
#define GRAPHICCAFFE    "  CAFFE"//
#define GRAPHICDRESS    "  DRESS"//
#define GRAPHICKNIFE    "  KNIFE"//
#define GRAPHICHIPPY    "  HIPPY"//
#define GRAPHICBREAD    "  BREAD"//
#define GRAPHICCHICKEN  "  CHICKEN"//
#define GRAPHICROSE1    "  ROSE1"//
#define GRAPHICMUM      "  CHRYSANTHEMUM"//
#define GRAPHICICE      "  ICE CREEN"//
#define GRAPHICGIFT     "  GIFT"//
#define GRAPHICROSE2    "  ROSE-BIG"//
#define GRAPHICTREE     "  CHRISTMAS TREE"   //
#define GRAPHICHBREAD   "  HOT BREAD"//
#define GRAPHICJOY      "  JOY"//
#define GRAPHICFISH     "  FISH"//
#define GRAPHICCARTOON  "  CARTOON CHICKEN" //
#define GRAPHICMONEY    "  MONEY"//
#define GRAPHICEAT      "  EATING"//
#define GRAPHICKITE     "  FLY KITE"            //
#define GRAPHICRUN      "  RUNNING"//
#define GRAPHICREST     "  REST"//

#define ECRVIPTITLE     "ACCOUNT          AMOUNT   POINTS"
                       //012345678901234567890123456789012
#define CREATEDATE      "CREATE DATE"

//ccr2016-06-06>>>>>>>>>>>INDIA>>>>>>>>>>>>>>>>
#define MsgEDITPLU      "EDIT PLU"
#define MsgEDITDEPT     "EDIT DEPART"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))//ccr2016-10-25>>>>EJ
#define Msg_RECNUMFR	"EJ# FROM"                  //��ʼ�վݺ�	//RECNUMFR
#define Msg_RECNUMTO	"EJ# TO"                    //�����վݺ�	//RECNUMTO
#define Msg_EJBBIAO		"~E~J ~R~E~P~O~R~T"		//EJ ����			//EJBBIAO
#define Msg_EJXINXI		"CURRENT MESSAGES OF EJ"            //EJ��Ϣ			//EJXINXI
#define Msg_NEWEJXINXI	"EJ AFTER INITIALIZED"            //EJ��Ϣ			//NEWEJXINXI

#define Msg_EJBHAO		"CODE"						//EJ���			//EJBHAO
#define Msg_EJLEFT    "SPACE LEFT"        //ʣ��ռ�
#define Msg_SIZEEJ		"SIZE OF EJ"				//SIZEEJ
#define Msg_EJCSHUA		"EJ INITIAL"		//EJ��ʼ��		//EJCSHUA

#define Msg_PRNEJURNAL  ">>>>PRINT ELECTRONIC JOURNAL<<<<"
#define Msg_ENTERSETUP  ">>>>>    PRINT ON SETUP    <<<<<"
#define Msg_EJDATEEND   "DATE LAST EJ"
#define Msg_EJRECORDS   "LAST EJ#"

#define Msg_EJINITIAL   "EJ INITIALIZATION"
#endif

#define Msg_MANAGEMENT "MANAGEMENT LIST "
#endif
