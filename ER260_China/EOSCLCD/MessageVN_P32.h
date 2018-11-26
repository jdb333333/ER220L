#ifndef MESSAGEH_VN_P
#define MESSAGEH_VN_P

// Printer
#define Header1         "CAM ON DA CHON"            //" 	 �� �� �� ��  �� �� �� ��   *"
#if defined(CASE_INDONESIA)
#define Header2         "MAY TINH TIEN TICH CUC"           //" 	 �� �� �� ��     �� �� �� ��   *"
#else
#define Header2         "MAY TINH TIEN EUTRON"      //" 	 �� �� �� ��     �� �� �� ��   *"
#endif


#define ReportType0     "DOANH THU"//"   ��  ��  ��   ",
#define ReportType1     "NHOM CHU"//" ��  ��  ��  �� ",//"/1
#define ReportType2     "NHOM"//" ��  ��  ��  �� ",//2
#define ReportType3     "MA HANG"//" ��  Ʒ  ��  �� ",      /* 3 Used with ApplVar.Plu ApplVar.Report */
#define ReportType4     "TIEN MAT"//" ��  ��  ��  Ϣ ",//4
#define ReportType5     "CHI-THU"//" �� �� �� �� Ϣ ",//5
#define ReportType6     "KET TIEN"//" Ǯ  ��  ��  Ϣ ",//6
#define ReportType7     "SUA SAI"//" ��  ��  ��  Ϣ ",//7
#define ReportType8     "CHIET KHAU"//" ��  ��  ��  Ϣ ",//8
#define ReportType9     "NGOAI TE"//" ��  ��  ��  Ϣ ",//9
#define ReportType10    "THUE"//" ��  ˰  ��  Ϣ ",//10
#define ReportType11    "CHUC NANG TRUOC"//" ��  ��  ��  Ϣ ",//11
#define ReportType12    "TAM TINH TRUOC"//" ��  ̨  ��  Ϣ ",//12
#define ReportType13    "BAN"//" ��  ̨  ��  Ϣ ",//13
#define ReportType14    "TON KHO"//" ��  Ʒ  ��  �� ",//14
#define ReportType15    "HOA DON TAM TINH"
#define ReportType16    "THANH TOAN PHU"

#define ReportType17    "TONG NHAN VIEN"//"    �� �� Ա ͳ ��   ",
#define ReportType18    "TONG PHUC VU"//"    Ӫ ҵ Ա ͳ ��   ",

#define Trailer1        "CAM ON"//"     ~��  ~л  ~��  ~��     ",
#define Trailer2        "TAM BIET"//"          ~��  ~��         ",


#define ReportList1     "N.Vien-Ngay"//" �� �� Ա �� �� ",
#define ReportList2     "N.Vien-Tich Luy"//" �� �� Ա �� �� ",
#define ReportList3     "BC NGAY"//" ��  ��  ��  �� ",
#define ReportList4     "BC TICH LUY"//" ��  ��  ��  �� ",
#define ReportList5     "BC MA HANG"//" ��  Ʒ  ��  �� ",
#define ReportList6     "BC BAN"//" ��  ��  ��  �� ",
#define ReportList7     "BC MUI GIO"//" ʱ  ��  ��  �� ",
#define ReportList8     "TC.BC NV-NGAY"//"  ȫ�տ�Ա�ձ�  ",
#define ReportList9     "TC.BC NV-T.LUY"//"  ȫ�տ�Ա�±�  ",
#define ReportList10    "PHUC VU THEO NGAY"//" Ӫ ҵ Ա �� �� "
#define ReportList11    "N.V PH.VU-T.LUY"//" Ӫ ҵ Ա �� �� "
#define ReportList12    "TC.BC NV NGAY "//"  ȫӪҵԱ�ձ�  ",
#define ReportList13    "T N.V P.V-T.LUY"//"  ȫӪҵԱ�±�  ",

#define Promotion1      "XIN CHUC MUNG"//"  ~��  ~ϲ  ~��  ~��",

#define Correc1         "SUA SAI"//"ȡ��    "//ccr2016-07-14
#define Correc2         "XOA"//"����    "//ccr2016-07-14
#define Correc3         "TRA LAI"//"�˻�    "
#define Correc4         "HUY"//"ȡ������"
#define Correc5         "TAM DUNG"//"����"


#define CURRENCY1       "USD"//"��Ԫ    "
#define CURRENCY2       "YEN"//"��Ԫ    "
#define CURRENCY3       "HK"//"�۱�    "
#define CURRENCY4       "Ngoai Te 1"//"���1   "
#define CURRENCY5       "Ngoai Te 2"//"���2   "

#define DISCOUNT1       "+% M.HANG"//"+%�ӳ�"
#define DISCOUNT2       "-% M.HANG"//"(-%)�ۿ�"
#define DISCOUNT3       "CONG TIEN"//"���ӳ�"
#define DISCOUNT4       "GIAM TIEN"//"����ۿ�"
//#define DISCOUNT5     "CONG % M.HANG"// zy //"����ӳ�"
//ccr090812 for SubDisc>>>>>>>>>>>>>>>>>>>>>>>>>
#define DISCOUNT6       "+% Bill"//  "+%С�Ƽӳ�"
#define DISCOUNT7       "-% Bill"//  "-%С���ۿ�"
#define DISCOUNT8       "PHU THU"// "С�ƽ��ӳ�"
#define DISCOUNT9       "GIAM TIEN"// "С�ƽ���ۿ�"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define DRAWER1         "TIEN MAT"//"�ֽ�    "
#define DRAWER2         "CHI PHIEU"//"֧Ʊ    "
#define DRAWER3         "THE TIN DUNG"//"���ÿ�  "
#define DRAWER4         "Voucher"//"����ȯ  "
#define DRAWER5         "TIN DUNG"//"����    "
#define DRAWER6         "THE CHIP"//"IC��    "
#if  defined(CASE_INDONESIA)
#define DRAWER7         "GHI NO"//"С��    "
#else
#define DRAWER7         "PHI"//"С��    "
#endif
#define DRAWER8         "KET-8"//��ӡ/��ʾ

#define PBFunction0     "THEM"//   "��̨����"
#define PBFunction1     "CONG THEM"//   "��̨����"
#define PBFunction2         "TAM TINH"//   "�ݽ�"
#define PBFunction3         "KTR HTAT"//   "ȷ�Ͻ���"
#define PBFunction4         "BAN"//   "��ӡ��̨"
#define PBFunction5         "IN BILL"//   "��ӡ�ʵ�"
#define PBFunction6         "HUY"//   "ȡ��ȷ��"
#define PBFunction7         "TACH MON"//   "����"
#define PBFunction8         "CHUYEN BILL"//   "ת��"
#define PBFunction9         "CHUUYEN BAN"//  "ת����'
#define PBFunction10        "SL KHACH"//   "����"

#define PORAType1            "CHI TIEN"//"����    "
#define PORAType2            "THU TIEN"//"���    "
#define PORAType3            "TRA LAI"//"IC���˿�"
#define PORAType4            "NAP"//"IC����ֵ"
#define PORAType5            "DAT COC"//"��ICѺ��"
#define PORAType6            "TCOC IC"//"��ICѺ��"

#define TendType1             "TIEN MAT"//"�ֽ�    "
#define TendType2             "PHIEU"//"֧Ʊ    "
#define TendType3             "THE TIN DUNG"//"���ÿ�  "
#define TendType4             "Voucher"//"����ȯ  "
#define TendType5             "TIN DUNG"//"����"
#define TendType6             "THE CHIP"//"ICCard"
#define TendType7             "THE NO"//"DEBIT CARD"
#define TendType8             "TIEN MAT-8"//"CASH-8"


#define OperationN3             "TONG CONG"// "�ܼ�",
#define OperationN4             "CHUYEN DOI"// "ת��",
#define OperationN5             "TONG"// "С��",
#define OperationN6             "CHI TIEN"// "����",
#define OperationN7             "THU TIEN"// "���",
#define OperationN8             "BAO CAO"// "����",
#define OperationN9             "THEM"// "����",
#define OperationN10            "GIU"// "�ҵ�,
#define OperationN11            "XOA"// "ȡ��",

#define OperationN14            "GIA"// "����:",
#define OperationN15            "SO TIEN"// "���:",

#define CaptionN2               "TONG TIEN"// "����",
#define CaptionN3               "GIA"// "�۸�",
#define CaptionN4               "TONG SO GIAO DICH"// "������",
#define CaptionN5               "SO LUONG"// "����",
#define CaptionN6               "SO TIEN"// "���",
#define CaptionN7               "TIEN MAT"// "��ȡ",
#define CaptionN8               "THOI LAI"// "����",
#define CaptionN9               "NGAY"// "��",
#define CaptionN10              "TUAN"// "��",
#define CaptionN11              "THANG"// "��",
#define CaptionN12              "NAM"// "��",
#define CaptionN13              "CHUAN"// "��׼",
#define CaptionN14              "DIEU HANH"// "�տ�Ա",
#define CaptionN15              "GIO"// "ʱ",
#define CaptionN16              "NGAY"// "   ��",
#define CaptionN17              "THANG"// "   ��",
#define CaptionN18              "TRA LAI"// "�˻�",
#define CaptionN19              "GIA"// "�ɱ�",
#define CaptionN20              "BAN SO:"// "����#",
#define CaptionN21              "SEC SO:"// "֧Ʊ��#",
#define CaptionN22              "SL"// "����:",
#define CaptionN23              "THUE BAN HANG"// "��˰����",
#define CaptionN24              "THUE"// "˰��",
#define CaptionN25              "TRANG"//  "ҳ��",
#define CaptionN26              "SO:"// "����:",
#define CaptionN27              "TAM TINH"// "����",
#define CaptionN28              "MO BAN"// "��̨",
#define CaptionN29              "LAN LAY BAO CAO"// "���ʼ���",
#define CaptionN30              "XOA"// "���",
#define CaptionN31              "S-BAO CAO"// "S-����",
#if HOR_REPORT==1
#define CaptionN32              "LAI RONG"// "ë��",
#else
#define CaptionN32              "LAI GOP"// "ë��",
#endif
#define CaptionN33              "NHAP KHO"// "�������",
#define CaptionN331             "TRU KHO"// "�������",
#define CaptionN34              "NGUYEN KHO"// "ԭ����:",
#define CaptionN35              "THE TIN DUNG"// "���ÿ�#",
#define CaptionN36              "BAN MOI:"// "������:",
#define CaptionN37              "SL KHACH"// "����",
#define CaptionN38              "TRAO DOI"// "����",

//Dispaly
#define CaptionN41              "GIAM 1"// "�ۿ���1",
#define CaptionN42              "GIAM 2"// "�ۿ���2",
#define CaptionN43              "BAN HANG"// "���۶�",
#define CaptionN44              "TRON GOI"// "����Ż�",
#define CaptionN45              "SL KHO"// "�������",
#define CaptionN46              "DE NGHI"// "�ؼ��Ż�",

#define CaptionN51              "MO"// "��̨�ݽ�",
#define CaptionN52              "THEM"// "��̨����",
#define CaptionN53              "TAM TINH"// "�ݽ�",
#define CaptionN54              "XAC NHAN THANH TOAN"// "ȷ�Ͻ���",
#define CaptionN55              "IN"// "��ӡ��̨",
#define CaptionN56              "IN BILL"// "��ӡ�ʵ�",
#define CaptionN57              "HUY"// "ȡ��ȷ��",
#define CaptionN58              "TACH"// "����",
#define CaptionN59              "CHUYEN"// "ת��",
#define CaptionN60              "CHUYEN DEN"// "�����տ�Ա",
#define CaptionN61              "SL KHACH"// "�˿�����",


#define CaptionE11              "DIEU HANH:"// "�տ�Ա:",
#define CaptionE12              "N.VIEN PHUC VU:"// "ӪҵԱ:",
#define CaptionE13              "MAY SO:"// "�տ����:",
#define CaptionE14              "CUA HANG SO:"// "λ��:",

#define CaptionE17              "PHIEN BAN:"// "���а汾:",
#define CaptionE18              "DAU CHAM"// "�������ѵ�",
#define CaptionE19              "THEM MA HANG"// "������Ʒ:",
#define CaptionE20              "XOA MA HANG"// "ɾ����Ʒ:",
#define CaptionE21              "BAT DAU KIEM TRA"// "��ʼ���>>",
#define CaptionE22              "KIEM TRA HOAN TAT"// "<<������",
#define CaptionE23              "TON KHO"// "���",
#define CaptionE24              "XOA BAO CAO"// "������ȫ��!",

#define CaptionE31              "CHU THICH"// "˵������",


#define MessagesN5                "***CHE DO THUC TAP***"// "*** ��ѵ״̬ ***",
#define MessagesN6                "***** MO NGUON*****"// "***** �ӵ� *****",
#define MessagesN7                "***TACH BAN***"// "*** �ֿ����� ***",
#define MessagesN8                "***BAN SAO PHIEU***"// "*** �����վ� ***",
#define MessagesN9                "***CAI GIA MAT HANG***"// "*** ��Ʒ��� ***",
#define MessagesN10               "**NHAP KHO +**"// "*** ���ӿ�� ***",
#define MessagesN101              "**XUAT KHO -**"// "*** ���ٿ�� ***",
#define MessagesN11               "***HUY***"// "***** ȡ�� *****",
#define MessagesN12               "**KHOI TAO CHUONG TRINH**"// "** �����ʼ�� **",


#define TitleN1	                  "TEN HANG   S.L      GIA   T.TIEN"//--Ʒ��   ����   ����   ���    //*123456789012345678901234567890123456*//

#define TitleN3	                  "TEN HANG        S.L       T.TIEN"//--Ʒ��   ����   ����   ���    //*123456789012345678901234567890123456*//
#define TitleN4	                  "TEN HANG                  T.TIEN"//

#define OptionS37                 "LAY SO"//mPRNINDEX////Ccr "ȡ�˺�:",


#define EditN6                    "TIEU THU"// "���ѽ��",
#define EditN24                   "TAP TIN       BAN GHI       RAM"// "�ļ���      ��¼��      �ռ��С"
#define EditN25                   "CONG       LOAI       GIAO THUC"// "��������    ͨ�����   ͨ��Э��"

#define ChipCardN46               "THE HOI VIEN:"// "��Ա��:",
#define ChipCardN47               "THANH VIEN"// �� Ա �� ��


#define PLULIST                  "DANH SACH MA HANG"// "         �� Ʒ �� Ϣ ��"
#define PLUTITLE1                "TEN HANG                   ID"//
#define PLUTITLE2                ">>NHOM     KHO     GIA"//

#define DEPTLIST               "DANH SACH NHOM"// "         �� Ʒ �� Ϣ ��"
#define DEPTTITLE              "TEN HANG      NHOM CHU      GIA"//

#define FisTextN18                "~ IN ~ TAI ~CHINH ~"//"    _�� _˰ _ӡ _��     "
#define FisTextN19                "~ KET ~THUC ~ THUC ~TAP ~"//"    _�� _װ _�� _��     "
#define FisTextN20                "~PHI ~THUE"//"    _��   _��   _˰     "


#define PRTStyleN1                "IN THUONG"//Normale
#define PRTStyleN2                "CAO GAP DOI"//Doppia altezza
#define PRTStyleN3                "R~O~N~G ~G~A~P ~D~O~I"//Raddoppio caratteri
#define PRTStyleN4                "C~A~O ~R~O~N~G ~G~A~P ~D~O~I"//Dopia altezza + Raddoppio caratteri

#define ComTestN1                 "LOI CONG 1"//"���� 1 ���Գ���"
#define ComTestN2                 "CONG 1 OK"//"���� 1 ������ȷ"
#define ComTestN3                        "LOI CONG 2"//"���� 2 ���Գ���"
#define ComTestN4                        "CONG 2 OK"//"���� 2 ������ȷ"

#define ComTestN3ERR                     "LOI CONG 3"//"���� 3 ���Գ���"
#define ComTestN3OK                      "CONG 3 OK"//"���� 3 ������ȷ"

#define DEPTREPORTTITLE         "NHOM       S.L        THANH TIEN"//"��������     ��������       ���"
#define PLUREPORTTITLE          "MA HANG     S.L        THANH TIEN"//

#define REPRN_PWON      "IN LAI KHI MO NGUON....."//
#define REPRN_PAPERON   "IN LAI KHI GIAY O.K...."//

//ccr2016-01-12>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define GRAPHICSELF     "  SELF GRAPHIC"
#define GRAPHICCAFFE    "  CAFFE"
#define GRAPHICDRESS    "  DRESS"
#define GRAPHICKNIFE    "  KNIFE"
#define GRAPHICHIPPY    "  HIPPY"
#define GRAPHICBREAD    "  BREAD"
#define GRAPHICCHICKEN  "  CHICKEN"
#define GRAPHICROSE1    "  ROSE1"
#define GRAPHICMUM      "  CHRYSANTHEMUM"
#define GRAPHICICE      "  ICE CREEN"
#define GRAPHICGIFT     "  GIFT"
#define GRAPHICROSE2    "  ROSE-BIG"
#define GRAPHICTREE     "  CHRISTMAS TREE"        //CHRISTMAS TREE
#define GRAPHICHBREAD   "  HOT BREAD"
#define GRAPHICJOY      "  JOY"
#define GRAPHICFISH     "  FISH"
#define GRAPHICCARTOON  "  CARTOON CHICKEN"        //CARTOON CHICKEN
#define GRAPHICMONEY    "  MONEY"
#define GRAPHICEAT      "  EATING"
#define GRAPHICKITE     "  FLY KITE"            //FLY A KITE
#define GRAPHICRUN      "  RUNNING"
#define GRAPHICREST     "  REST"

#define ECRVIPTITLE     "ACCOUNT          AMOUNT   POINTS"
                       //012345678901234567890123456789012
#define CREATEDATE      "CREATE DATE"
//ccr2016-06-06>>>>>>>>>>>INDIA>>>>>>>>>>>>>>>>
#define MsgEDITPLU      "CHINH SUA MA HANG"//
#define MsgEDITDEPT     "CHINH SUA NHOM"//
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))//ccr2016-10-25>>>>EJ
#define Msg_RECNUMFR	"EJ# FROM"                  //��ʼ�վݺ�	//RECNUMFR
#define Msg_RECNUMTO	"EJ# TO"                    //�����վݺ�	//RECNUMTO
#define Msg_EJBBIAO		"~E~J ~R~E~P~O~R~T"		//EJ ����			//EJBBIAO
#define Msg_EJXINXI		"CURRENT MESSAGES OF EJ"            //EJ��Ϣ			//EJXINXI
#define Msg_NEWEJXINXI	"EJ AFTER INITIALIZED"            //EJ��Ϣ			//NEWEJXINXI
#define Msg_EJBHAO		"CODE"						//EJ���			//EJBHAO
#define Msg_EJLEFT      "SPACE LEFT"        //ʣ��ռ�
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

