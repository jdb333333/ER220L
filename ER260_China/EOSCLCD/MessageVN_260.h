#ifndef MESSAGEH_VN
#define MESSAGEH_VN


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

#define Modifier1             "GHI CHU"//"˵��    "
#define ClerkRec1             "THU NGAN"//"�տ�Ա  "
#define GroupRec1             "NHOM CHU"//"����    "
#define DeptRec1              "NHOM"//"����    "
#define PLURec1               "MA HANG"//"��Ʒ    "
#define SalesPersonRec1       "PHUC VU"//"ӪҵԱ  "
#define OffRec1               "DE NGHI"//"�������"

#define XZReportList1     "BC NGAY"//"�����ձ���",
#define XZReportList2     "BC TICH LUY"//"�����±���",
#define XZReportList3     "TICH LUY M.HANG"//"��Ʒ����",
#define XZReportList4     "TICH LUY BAN"//"���ʱ���",
#define XZReportList5     "MUI GIO"//"ʱ�α���",
#define XZReportList6     "N.VIEN-NGAY"//"�տ�Ա�ձ���",
#define XZReportList7     "N.VIEN-T.LUY"//"�տ�Ա�±���",
#define XZReportList8     "TC.BC NV-NGAY"//"ȫ�տ�Ա�ձ���",
#define XZReportList9     "TC.BC NV-T.LUY"//"ȫ�տ�Ա�±���",
#if (salNumber)
#define XZReportList10    "PHUC VU THEO NGAY"//"ӪҵԱ�ձ���"
#define XZReportList11    "N.V PH.VU-T.LUY"//"ӪҵԱ�±���"
#define XZReportList12    "TC.BC NV NGAY "//"ȫӪҵԱ�ձ���",
#define XZReportList13    "T N.V P.V-T.LUY"//"ȫӪҵԱ�±���",
#endif
#if (BARCUSTOMER==1)
#define XZReportList14    "VIP"//"�����Ա����",
#endif

#define PortType1               "MAY VI TINH"//"  ����",
#define PortType2               "DOC MA VACH"//"����ǹ",
#define PortType3               "CAN DIEN TU"//"���ӳ�",
#define PortType4               "IN BEP"//"��  ��",
#define PortType5               "IN PHIEU"//'Ʊ��'��20040322
#define PortEXTPRN              "EP-PORT"//ccr2016-12-14 ExtPrinter????
#define PortType6               "THE CHIP"//-------090421 BY ZY//"/"��Ƶ��"
#define PortType7               "THE E"//"Eͨ��"

#define KClose                  "TAT MAY"//"   �� ",

#define SysFlags0		        "CUA HANG SO:"// "���̱��"
#define SysFlags1               "MAY SO:"//"�տ����:"
#define SysFlags2               "LAM TRON"//"���뷽ʽ:"
#define SysFlags3               "GIA MO"//"��Ʒ���:"
#define SysFlags4               "TIENG Bip"//"������:"
#define SysFlags5               "BUOC VAO CA"//"ǿ���տ�Ա"
#define SysFlags6               "THAY N.VIEN"//"�ı��տ�Ա"
#define CLERKPASS               "MAT MA N.VIEN"//"�տ�Ա����"
#define SysFlags8               "IN N.VIEN PHUC VU"//"��ӡӪҵԱ"
#define SysFlags9               "IN N.VIEN"//"��ӡ�տ�Ա"
#define SysFlags10              "IN SO H.DON"//"��ӡ�վݺ�"
#define SysFlags11              "IN DAM"//"��Ũ�ȴ�ӡ"
#define SysFlags12              "BAC BUOC VAO MA PHUC VU"//"ǿ��ӪҵԱ"
#define SysFlags13              "IN MA"//"��ӡ����:"
#define SysFlags14              "BAM T.CONG"//"��С�Ƽ�:"
#define SysFlags15              "SO BAN IN"//"��ӡ��Ŀ��"
#define SysFlags16              "IN TONG CONG"//"��ӡСƱ:"
#define SysFlags17              "DAU PHIEU NHO"//"СƱƱͷ:"
#define SysFlags18              "KHOA SHIFT"//"����SHIFT:"
#define SysFlags19              "HIEN THI THOI GIAN"//"��ʾʱ��:"
#define SysFlags20              "BAN SAO"//"�����վ�:"
#define SysFlags21              "MA CAN"//"��������:"
#define SysFlags22              "NHAT KY DANG NHAP"//-----090421 BY ZY//"������־"
#define SysFlags23              "IN MO BAN"//"��̨��ӡ:"
#define SysFlags24              "IN KHO"//"��ӡ���"
#define SysFlags25              "TAT/MO H.DON"//"��ӡ����:"
#define SysFlags26              "BUOC MO BAN"//"���뿪̨:"
#define SysFlags27              "GIU SO PHIEU"//"�����վݺ�"
#define SysFlags28              "BAN SAO IN BEP"//"���Ƴ���:"
#define SysFlags29              "RESET SO PHIEU"//"�վݺŸ�λ"
#define SysFlags30              "IN GAP DOI"//-----090421 BY ZY//"���ߴ�ӡ"
#define SysFlags31              "TUONG PHAN"//-----090421 BY ZY//"�Աȶ�:"
#define SysFlags32              "TIEU DE DAU"// "Ʊͷ���д�ӡ"
#define SysFlags33              "TIEU DE CUOI"// "Ʊβ���д�ӡ"
#define SysFlags34              "GAP DOI T.DE DAU"// "Ʊͷ���ߴ�ӡ"
#define SysFlags35              "GAP DOI T.DE CUOI"// "Ʊβ���ߴ�ӡ"
//ccr2016-03-21#define SysFlags36              "To .CSV "
#define SysFlags37              "IN NGAY"
#define SysFlags38              "IN GIO"
#define SysFlags39              "IN LAY SO"//"��ӡȡ�˺�"
#define SysFlags40              "GUI TIN.H MCHU"//ccr2015-08-03"�����������Heart beat"
#define SysFlags41              "PreFix1:"      //ccr2016-08-02
#define SysFlags42              "PreFix2:"      //ccr2016-08-02

#define GrapType1               "KIEU LOGO"//"�̵�ͼ��",
#define GrapType2               "H.KH.MAI"//"�н�ͼ��:",
#define GrapType3               "LOGO CUOI"//"Ʊβͼ��:",
#define GrapType4               "VAN BAN"//"��ӡ����?",

#define GrapSet1                "STT"//"���:",
#define GrapSet2                "HINH"//"ͼ����:",
#define GrapSet3                "TU"//"��ʼ����:",
#define GrapSet4                "DEN"//"��������:",
  /////==============CHN msg===============//////

#define CurrentMode1            "BAN HANG"//"Ӫҵ",
#define CurrentMode2            "XEM BC"//"����",
#define CurrentMode3            "LAY BC"//"����",
#define CurrentMode4            "CAI DAT"//"����",
#define CurrentMode5            "CHU"//"����",

#define SetupMode1              "CAI DAT CHUNG"//---090421 BY ZY//" "�ۺϹ���",
#define SetupMode2              "NHOM/MA"// "��Ʒ����",
#define SetupKeyboard           "BAN PHIM/DEFKEYBOARD"  //
#define msgCOMMHOST             "COMM-HOST"
#define SetupMode3              "THIET BI NGOAI VI"// "ͨѶ������",
#define SetupMode4              "QUAN LY"// "���۹�������",
#define SetupMode5              "TAI KHOAN"// "��Ա������",
#define SetupMode6              "DAU/CUOI"// "Ʊ����ʽ",
#define SetupMode7              "BAO CAO"// "������",
#define msgDISCOUNT             "GIAM GIA/MENUDISC" //
#define SetupMode8              "CHUC NANG TAM"// "��������",
#define SetupMode9              "CAI MAT MA"// "����,
#define SetupMode10             "DICH VU"// "�տ��ά��",


#define SysSettings1            "TUY CHON HE THONG"// "ϵͳ��������",
#define SysSettings2            "CAI DAT NGAY"// "����",
#define SysSettings3            "CAI DAT GIO"// "ʱ��",
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define msgSETEJOURNAL          "SET EJ"      //SETEJOURNAL //EJOURNAL
#endif

#define SysSettings4            "BAN PHIM"// "����",
#define MESSKEYMACRO            "PHIM TICH HOP"// "���̺�"
#define MESSKEYTYPE             "LOAI PHIM"// "����ģʽ"

#define SysSettings5            "MO HINH NHA HANG"// "���������л�",
#define SysSettings6            "BAN LE"// "���м����л�",
#define SysSettings8          "TIN HIEU KHONG DAY"//"GPRSͨ��"  //SETGPRS //ccr2014-11-11 NEWSETUP

#define SetupCaption1           "NHOM CHU"//"����"
#define SetupCaption2           "NHOM"//"����",
#define SetupCaption3           "MA HANG"//"��Ʒ",
#define SetupCaption4           "IN DANH SACH HANG"//"��ӡ��Ʒ�嵥",
#define msgSETTEST              "KIEM TRA ECR"//"ϵͳ����"            //SETTEST
#define msgSETCLEARPLU          "XOA MA HANG"//"�����Ʒ"        //SETCLEARPLU
#define msgSETPLULIST           "IN NHOM/MA HANG"//"��ӡ��Ʒ�嵥"      //SETPLULIST
#define msgSETTSTVER	        "IN PHIEN BAN"//"��ӡ�汾"      //SETTSTVER
#define msgSETCONFIGPLU         "TU MA"//"���õ�Ʒ"          //SETCONFIGPLU
#define msgSETCONFIGDEPT        "TU NHOM"//���ò���         //SETCONFIGDEPT
#define msgSETINSTALL           "CAI DAT/SAO LUU"//"��װ/����"        //SETINSTALL
#define msgSETPRINTFAT          "IN PHAN BO"//"��ӡ�ļ������"   //SETPRINTFAT


#define SetupCaption5           "MAY TINH"// "ͨѶ��1",
#define SetupCaption6           "DOC MA VACH"// "ͨѶ��2",
#define SetupCaption7           "CAN DIEN TU"// "ͨѶ�� 3",
//#define SetupCaption8           "PORT-4"			//"CONG 4"// "ͨѶ�� 4",
#define SetupCaption9           "CONG MANG"// "��������"

#define SetupCaption10          "IN PHIEU"// "Ʊ�ݴ�ӡ",
#define SetupCaption11          "IN BEP"// "������ӡ",
#define SetupEXTPrinter         "EXTERNAL PRINT"    //SETEXTPRINTER

#define SetupCaption12          "DE NGHI"// "�Żݼ�",
#define SetupCaption13          "KHUYEN MAI"// "�н�����",
#define SetupCaption14          "GIAM GIA"// "�ۿ�",
#define SetupCaption15          "CHI.THU"// "�������",
#define SetupCaption16          "SUA SAI"// "��������",
#define SetupCaption17          "HINH THUC THANH TOAN"// "���ʽ",
#define SetupCaption18          "NGOAI TE"// "���",
#define SetupCaption19          "KET TIEN"// "Ǯ��",
#define SetupCaption20          "THUE"// "˰��",

#define SetupCaption21          "DAT TAI KHOAN"// "IC������",
#define SetAddNewECRVIP         "THEM TAI KHOAN"
#define SetPrintECRVIP          "IN TAI KHOAN"
#define SetCleanALLVIP          "XOA TAI KHOAN"

#define SetupCaption22          "MAT THE"// "IC����ʧ",
#define SetupCaption23          "IN THE"// "��ӡ����Ϣ",
#define SetupCaption24          "TIEU DE DAU"// "Ʊͷ",
#define SetupCaption25          "TIEU DE CUOI"// "Ʊβ",
#define SetupCaption26          "DAU PHIEU"// "Ʊ��Ʊͷ",
#define SetupCaption27          "LOGO HINH"// "ͼ��",
#define SetupCaption28          "IN LOGO HINH"// "��ӡͼ��",
#define SetupCaption29          "BAO CAO"// "���ñ�������",
#define SetupCaption30          "DON VI BAO CAO"// "����Ԫ",
#define SetupCaption31          "MUI GIO"// "����ʱ������",
#define SetupCaption32          "XOA TAT CA"// "���屨��",
#define SetupCaption33          "IN CUON LUU"// "��ӡ��ˮ",

#define SetupCaption34          "BAN"// "��̨",
#define SetupCaption35          "PB FUNCTION"// "��������",
#define SetupCaption36          "GHI CHU"//ZY  // "�˵�˵��",
#define SetupCaption37          "XAC NHAN"//ZY  // "ǩ��",
#define SetupCaption38         "THU NGAN"// "�տ�Ա",
#define SetupCaption39          "NHAN VIEN BAN HANG"// "ӪҵԱ",
#define SetupCaption40          "MAT MA CHUONG TRINH"//ZY  // "���õ�����",
#define SetupCaption41          "MAT MA QUAN" //LY/ZY  // "��������",
#define SetupCaption42          "MAT MA XEM BAO CAO"//ZY  // "ֻ����������",
#define SetupCaption43          "MAT MA LAY BAO CAO"//ZY  // "���ʱ�������",
#define SetupCaption44          "BO NHO"//ZY  // "��ӡ����",
#define SetupCaption45          "HIEN THI"//ZY  //"��ʾ����",
#define SetupCaption451         "KHACH HANG"// ���Բ���
#define SetupCaption46          "MAY IN"//ZY  //"��ӡ�汾",
#define SetupTestRAM           "KIEM TRA RAM"//SETTSTMEM	       //RAM����
#define SetupCaption47          "DONG HO"//ZY  //"ʱ�Ӳ���",
#define SetupCaption48          "COI BAO"//ZY  //"����������",
#define SetupCaption49          "KET TIEN"//ZY  //"Ǯ�����",
#define SetupCaption50          "BAN PHIM"//ZY  //"���̲���",
#define SetupCaption51          "CONG NOI TIEP"//ZY  //"���ڲ���",
#define SetupCaption52          "TU KIEM TRA"//ZY  //"�Զ�����",

#define msgSETPRNMENU           "IN MENU"//SETPRNMENU   //

#define OperationN1             "GHI LAI"// "��¼#",
#define OperationN2             "LUU Y?"//ZY  // "��¼?",
#define OperationN3             "TONG CONG"// "�ܼ�",
#define OperationN4             "CHUYEN DOI"// "ת��",
#define OperationN5             "TONG"// "С��",
#define OperationN6             "CHI TIEN"// "����",
#define OperationN7             "THU TIEN"// "���",
#define OperationN8             "BAO CAO"// "����",
#define OperationN9             "THEM"// "����",
#define OperationN10            "GIU"// "�ҵ�,
#define OperationN11            "XOA"// "ȡ��",

#define OperationN12            "MAT MA"// "����",
#define OperationN13            "XAC NHAN"// "����ȷ��",
#define OperationN14            "GIA"// "����:",
#define OperationN15            "SO TIEN"// "���:",
#define OperationN16            "CUA HANG"// "���а�",
#define OperationN17            "NHA HANG"// "������",
#define OperationN18            "KIEM TRA"// "����",


#define CaptionN1               "TONG CONG"// "Ӧ��",
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


#define CaptionN39              "THEM MA HANG?"// "����?",
#define CaptionN40              "XOA MA HANG?"// "ɾ��?",
#define CaptionN41              "GIAM 1"// "�ۿ���1",
#define CaptionN42              "GIAM 2"// "�ۿ���2",
#define CaptionN43              "BAN HANG"// "���۶�",
#define CaptionN44              "TRON GOI"// "����Ż�",
#define CaptionN45              "SL KHO"// "�������",
#define CaptionN46              "DE NGHI"// "�ؼ��Ż�",
#define CaptionN47              "TUY CHON:"// "ѡ��:",
#define CaptionN48              "CO DINH"// "�̶�",
#define CaptionN49              "TU DO"// "����",
#define CaptionN50              "DINH/TU DO"// "��//��",
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
#define CaptionN62              "DIEM THUONG:"// "�н��趨:",
#define CaptionN63              "DIEM THUONG"// "���ѻ���:",
#define CaptionN64              "THAY DOI GIA"// "�ı䵥Ʒ�۸�",
#define CaptionN65              "NHOM IN BEP"// "������ӡ����"��
#define CaptionN66              "CONG KHO"// "���ӿ��",
#define CaptionN67              "XUAT KHO"// "���ٿ��",
#define CaptionN68              "NHAN"// "����",
#define CaptionN69              "TRA"// "����",


#define CaptionE1               "LOI RS-232"// "RS232��",
#define CaptionE2               "RS232 OK"// "RS232��ȷ",
#define CaptionE3               "LOI RTC"// "RTC ��!",
#define CaptionE4               "LOI CTC"// "CTC ��!",
#define CaptionE5               "LOI FPROM"// "FPROM��!",
#define CaptionE6               "KHOI TAO"// "��ʼ��...",
#define CaptionE7               "KHOI TAO THANH CONG"// "��ʼ������.",
#define CaptionE8               "LOI"// "����-",////����<SCREENWD

#define CaptionE9               "SAI MAT MA"// "����� ��",
#define CaptionE10              "LUU MAT MA"// "�����ѱ���",
#define CaptionE11              "DIEU HANH:"// "�տ�Ա:",
#define CaptionE12              "N.VIEN PHUC VU:"// "ӪҵԱ:",
#define CaptionE13              "MAY SO:"// "�տ����:",
#define CaptionE14              "CUA HANG SO:"// "λ��:",
#define CaptionE15              "XAC NHAN ?"// "ȷ��?",
#define CaptionE16              "HOAN THANH"// "���",

#define CaptionE17              "PHIEN BAN:"// "���а汾:",
#define CaptionE18              "DAU CHAM"// "�������ѵ�",
#define CaptionE19              "THEM MA HANG"// "������Ʒ:",
#define CaptionE20              "XOA MA HANG"// "ɾ����Ʒ:",
#define CaptionE21              "BAT DAU KIEM TRA"// "��ʼ���>>",
#define CaptionE22              "KIEM TRA HOAN TAT"// "<<������",
#define CaptionE23              "TON KHO"// "���",
#define CaptionE24              "XOA BAO CAO"// "������ȫ��!",
#define CaptionE25              "CAP NHAT!\nKHONG THOAT!"// "���³�������ϵ�",
#define CaptionE26              "TRAN TAP TIN"// "�ļ��ռ�Խ��",
#define CaptionE27              "TRAN BO NHO"// �ڴ������
#define CaptionE28              "DAY CUON LUU"// "��ˮ�洢����",
#define CaptionE29              "HET GIAY"// "�������ӡֽ",
#define CaptionE30              "LOI BO NHO MO RONG"// "��չ�ڴ����",


#define CaptionE31              "CHU THICH"// "˵������",

#define CaptionE32              "NHAP KHONG HOP LE"// "��Ч����!",
#define CaptionE33              "NGAY KHONG HOP LE"// "��Ч����!",
#define CaptionE34              "GIO KHONG HOP LE"// "��Чʱ��!",
#define CaptionE35              "KHONG DUOC PHEP"// "��ֹ����!",
#define CaptionE36              "KHONG CO MA HANG"// "PLU����Ϊ��!",
#define CaptionE37              "DAY MA HANG"// "PLU�ļ����!",
#define CaptionE38              "BAN DA TON TAI"////" "��̨��ռ��!",
#define CaptionE39              "BAN DA MO"// "��̨�Ѵ�!",
#define CaptionE40              "SAI BAN"// "��̨�Ų���!",
#define CaptionE41              "NHAP SO BAN"// "��������̨��",
#define CaptionE42              "KHONG MO BAN"// "û�п�̨",
#define CaptionE43              "DAY BAN"// "��̨�������",
#define CaptionE44              "KHONG DUOC PHEP"// "��ֹ�޸�ʱ��",
#define CaptionE45              "DANG BAN HANG"// "����������!",
#define CaptionE46              "DAY NHO DEM"// "���ۻ�������",
#define CaptionE47              "HANG TON"// "��Ʒû���۳�",
#define CaptionE48              "DANG BAN HANG"// "���ڽ�����!",
#define CaptionE49              "SO KHONG HOP LE"// "�������ݳ���",
#define CaptionE50              "DANG THANH TOAN"// "���ڸ���!",
#define CaptionE51              "NHAP SAI KHACH"// "�������!",
#define CaptionE52              "XAC NHAN BAN"// "û��ȷ�Ͻ���",
#define CaptionE53              "KHONG DUOC PHEP"// "��ֹȡ������",
#define CaptionE54              "KHONG CO HANG"// "�޲���!",
#define CaptionE55              "KHONG CO NHAN VIEN"// "�޴��տ�Ա!",
#define CaptionE56              "KHOA NHAN VIEN"// "�տ�Ա�ı�",
#define CaptionE57              "BAO CAO-RONG"// "�޴��౨��!",
#define CaptionE58              "IN BI GIAN DOAN"// "�����ӡ�ж�",
#define CaptionE59              "BAT BUOC CHE DO QUAN LY"// "�����ھ���",
#define CaptionE60              "KHONG THE TACH"// "���ܷ���ʱ��",
#define CaptionE61              "NHAP SO#"// "�����������",
#define CaptionE62              "KEY-POS ERROR"// "ת�뵽",
#define CaptionE63              "KHONG DUOC PHEP"// "δ��Ȩ!",
#define CaptionE64              "XIN NHAP NHAN VIEN"// "��ָ���տ�Ա",
#define CaptionE65              "XIN NHAP N.VIEN PHUC VU"// "��ָ��ӪҵԱ",
#define CaptionE66              "KHONG DUOC PHEP"// "��ֹPLU��ۣ�",
#define CaptionE67              "SAI MAT MA"//  "���벻��!",
#define CaptionE68              "LOI IN BEP"// "������ӡ����",
#define CaptionE69              "LOI ERROR"// "Ʊ�ݴ�ӡ����",
#define CaptionE70              "HET GIAY"// "��ӡѹ��̧��",
#define CaptionE71              "HET GIAY"// "��ӡֽ����!",
#define CaptionE72              "NONG THANH NHIET"// "��ӡ�¶�̫��",
#define CaptionE73              "CHUA CO CHUC NANG"// "����δ����!",
#define CaptionE74              "XIN NHAP TIEN"// "����������",
#define CaptionE75              "CAM THANH TOAN HINH THUC KHAC"// "��ֹ���ָ���",
#define CaptionE76              "CHUC NANG RONG"// "�����޴˹���",
#define CaptionE77              "BAM TONG CONG"// "δ��С�Ƽ�!",
#define CaptionE78              "TON KHO"// "���ڹ�����",
#define CaptionE79              "LOI CUON LUU"// "������ˮ��",
#define CaptionE80              "LOI MODEM"// "MODEMͨѶ��!",


#define CaptionE81              "LOI CHIPCARD"// "����������!"
#define CaptionE82              "LOI MA POS"// "POS�����!"
#define CaptionE83              "LOI DU LIEU THE"// "�����ݴ�!"
#define CaptionE84              "THE HET HAN"// "Ϊ���ڿ�!"
#define CaptionE85              "MAT THE"// "Ϊ��ʧ��!"
#define CaptionE86              "SAI LOAI"// "�ͻ�����!"
#define CaptionE87              "THE MOI"// "Ϊ�¿�!"
#define CaptionE88              "KHONG THANH TOAN THE"// "���ǹ��￨!"
#define CaptionE89              "LOI GHI THE"// "д������!"
#define CaptionE90              "LOI CONG"// "���Ų���!"
#define CaptionE91              "THE GIAM GIA"// "�����ۿۿ�!"
#define CaptionE92              "THANH TOAN THE!"// "�����ֽ�!"
#define CaptionE93              "THE TIN DUNG!"// "�������ʿ�!"
#define CaptionE94              "KHONG SU DUNG"// "����IC��!"
#define CaptionE95              "LOI KHOA THE"// "�忨����!",
#define CaptionE96              "TRAN DU LIEU"// "�������!",
#define CaptionE97              "LOI CHARGE"// "IC��ֵ����!",
#define CaptionE98              "NAP THE LOI"// "IC��ʼ������",
#define CaptionE99              "CAM KHOI TAO"// "��ֹ��ʼ��!",
#define CaptionE100             "KHONG DU TIEN"// "IC����!",
#define CaptionE101             "LOI THANH TOAN"// "IC�������!",
#define CaptionE102             "LOI DIA CHI IP"// "IP��ַ��"
#define CaptionE103             "KHONG CO THE"//  ,
#define CaptionE105		"GIU"//CWXXI73////Ccr							////CWXXI73

#define CaptionERR105            "PIN YEU"// "��ص�����",
#define CaptionERR106            "KHONG DUNG KHO"//20070806"û������"
////ccr090715>>>>>>>>>>>>>>>>>>>>>>
#define CaptionERR76		"CHON DIA"//
#define CaptionERR77		"LOI MO"//
#define CaptionERR78		"LOI DOC"//
#define CaptionERR79		"LOI GHI"//
#define CaptionERR80		"LOI TAO"//
#define CaptionERR81		"LOI DONG"//
#define CaptionERR82		"GUI LOG!"//
#define CaptionERR83            "LOI WIRELESS"//
#define CaptionERR84            "LOI GUI"//
#define CaptionERR85            "LOI NHAN"//
#define CaptionERR86            "KHONG CO MAY CHU"//
#define CaptionERR87            "IP/CONG: RONG"//û�����÷�����IP�Ͷ˿�
#define CaptionERR88            "KHONG CO THE SIM"//
#define CaptionERR89            "WIRELESS KHONG OK"//
#define CaptionERR90            "VUOT GIOI HAN"//CWXXI90  ////
#define CaptionERR91            "TAI KHOANG RONG"//CWXXI91
//ccr2016-10-24 EJ >>>>>>>>>>>>>>>>>>>
#define EJ_CWXXI92  "EJ DATA ERROR"   	//CWXXI92
#define EJ_CWXXI93  "NO SD CARD"        	//CWXXI93
#define EJ_CWXXI94  "EJ R/W ERROR"   	//CWXXI94
#define EJ_CWXXI95  "NO EJ RECORDS"   	//CWXXI95
#define EJ_CWXXI96  "EJ NEARLY FULL"   	//CWXXI96
#define EJ_CWXXI97  "EJ IS FULL"   	//CWXXI97
#define EJ_CWXXI98  "NEW EJ"        	//CWXXI98
#define EJ_CWXXI99  "RESET EJ FIRST"   	//CWXXI99
#define EJ_CWXXI100 "EJ NOT MATCHED"     	//CWXXI100

////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


#define CaptionE104             "MO KET"// "��Ǯ��",
#define CaptionE106             "GIU PHIEU"//
#define CaptionE107             "NHAP SL\nVA GIA"//
#define CaptionE108             "CHUYEN DEN"    //ZHUANRUDAO

#define MsgPUTOUT               "CHI"//PUTOUT
#define MsgRECIEVIN             "THU"//RECIEVIN

#define DownLoad1               ">>TAI FONT CHU"// "���������ֿ�",
#define DownLoad2               ">>TAI LOGO HINH"// "��������ͼ��",


#define OptionN1                "DONG" ////Y// "��",
#define OptionN2               "KHONG DONG" ////Y// "��",
#define OptionN3                "TEN"// "����:",
#define OptionN4                "NHOM"// "����:",
#define OptionN5                "NHOM CHU"// "����:",
#define OptionN6                "IN"// "��ӡ:",
#define OptionN7                "TUY CHON"// "ѡ��:",
#define OptionN8                "LIEN KET"// "����:",
#define OptionN9                "THUE"// "˰��:",
#define OptionN10               "MA POS"// "λ�ñ��:",
#define OptionN11               "GIA 1"// "�۸� 1:",
#define OptionN12               "GIA 2"// "�۸� 2:",
#define OptionN13               "GIA 3"// "�۸� 3:",
#define OptionN14               "GIA 4"// "�۸� 4:",
#define OptionN15               "MUA"// "����:",
#define OptionN16               "GIAM %"// "�ۿ���(%):",
#define OptionN17               "LON NHAT"// "���ֵ:",
#define OptionN18               "GIAM GIA"// "�ۿ���:",
#define OptionN19               "LON NHAT"// "���ֵ:",
#define OptionN20               "TI LE"// "����:",
#define OptionN21               "MUA"// "�����:",
#define OptionN22               "BAN"// "������:",
#define OptionN23               "TRANG THAI"// "״̬:",
#define OptionN24               "KET TIEN"// "Ǯ��:",
#define MSGOTD                  "OTD"//OTDMSG
#define OptionN25               "IN BEP"// "������ӡ:",
#define MSGPERIOD               "THOI KHOANG"//PERMSG
#define MSGPOINTER              "CON TRO"//POIMSG

#define OptionN26               "TIEN TO"// "ǰ׺��",,6���ַ�
#define OptionN27               "LIEN KET"// "����:",
#define OptionN28               "CHUC NANG "// "���빦����:",
#define OptionN29               "CHON PHIM"// "�����ܼ�:",
#define OptionN30               "LOAI"// "����:",
#define OptionN31               "TU NGAY"// "��ʼ����:",
#define OptionN32               "DEN NGAY"// "��������:",
#define OptionN33               "THOI GIAN BAT DAU"// "��ʼʱ��:",
#define OptionN34               "THOI GIAN KET THUC"// "����ʱ��:",
#define OptionN35               "TUAN"// "����:",
#define OptionN36               "GIAM"// "�ۿ�:",
#define OptionN37               "SO LUONG"// "�������:",
#define OptionN38               "GIA"// "����:",
#define OptionN39               "DE NGHI"// "�Żݼ�:",
#define OptionN40               "GIAO THUC TRUYEN"// "ͨѶЭ��:",
#define OptionN41               "SO DIEN THOAI"// "�绰����:",
#define OptionN42               "MAT MA"// "����:",
#define OptionN43               "TAN SUAT"// "Ƶ��:",
#define OptionN44               "TOI THIEU"// "��С���:",
#define OptionN45               "CONG"// "ͨѶ��:",
#define OptionN46               "GIA TRI"// "�Ƶ���:",
#define OptionN47               "HINH ANH"// "ͼ�����:",
#define OptionN48               "GIO:"// "ʱ��:",
#define OptionN49               "NGAY:"// "����:",
#define OptionN50               "PRINTER"//
#define OptionN51               "TYPE:"      //DZCHXHAO//"���ͺ�",

#define WelcomeN1               "CAM ON DA CHON"// "�� �� �� �� �� �� �� ��\n    ��ӭʹ���Ŵ��տ��" *////"
#define WelcomeN2               "CAM ON DA CHON"// "���������Ŵ����\n�Ŵ�����ʯ�տ��" *//

#define MessagesN1              "DONG MAY"// "  �տ��������",
#define MessagesN2              "BAM<PHIM>"// "������ʽ��������",
#define MessagesN3              "HINH THUC HOA DON"// "��ʽ��Ʊ",																							////XSHFPIAO
#define MessagesN4              "IN BEP#"// "������ӡ��#",																						////CHFDYJHAO
#define MessagesN5                "***CHE DO THUC TAP***"// "*** ��ѵ״̬ ***",
#define MessagesN6                "***** MO NGUON*****"// "***** �ӵ� *****",
#define MessagesN7                "***TACH BAN***"// "*** �ֿ����� ***",
#define MessagesN8                "***BAN SAO PHIEU***"// "*** �����վ� ***",
#define MessagesN9                "***CAI GIA MAT HANG***"// "*** ��Ʒ��� ***",
#define MessagesN10               "**NHAP KHO +**"// "*** ���ӿ�� ***",
#define MessagesN101              "**XUAT KHO -**"// "*** ���ٿ�� ***",
#define MessagesN11               "***HUY***"// "***** ȡ�� *****",
#define MessagesN12               "**KHOI TAO CHUONG TRINH**"// "** �����ʼ�� **",
#define MessagesN13               "<>"
#define MessagesN14               "TONG CONG"//////KPTOTAL


#define TitleN1	                  "TEN HANG   S.L      GIA   T.TIEN"//--Ʒ��   ����   ����   ���    //*123456789012345678901234567890123456*//

#define TitleN3	                  "TEN HANG        S.L       T.TIEN"//--Ʒ��   ����   ����   ���    //*123456789012345678901234567890123456*//
#define TitleN4	                  "TEN HANG                  T.TIEN"//

#define CaptionM1                 "THANG 1"// "һ��",
#define CaptionM2                 "THANG 2"// "����",
#define CaptionM3                 "THANG 3"//  "����",
#define CaptionM4                 "THANG 4"//  "����",
#define CaptionM5                 "THANG 5"// "����",
#define CaptionM6                 "THANG 6"// "����",
#define CaptionM7                 "THANG 7"// "����",
#define CaptionM8                 "THANG 8"// "����",
#define CaptionM9                 "THANG 9"// "����",
#define CaptionM10                "THANG 10"// "ʮ��",
#define CaptionM11                "THANG 11"// "ʮһ��",
#define CaptionM12                "THANG 12"// "ʮ����",

#define CaptionW1                 "THU 2"// "����һ",
#define CaptionW2                 "THU 3"// "���ڶ�",
#define CaptionW3                 "THU 4"// "������",
#define CaptionW4                 "THU 5"// "������",
#define CaptionW5                 "THU 6"// "������",
#define CaptionW6                 "THU 7"// "������",
#define CaptionW7                 "CHU NHAT"// "������",


#define ClueN1                    "BAM ENTER"// "��ȷ�ϼ�...",

  ////"//Option for KP
#define OptionS1                  "IN TONG"// "��ӡ�ܶ�:",
#define OptionS2                  "GOP MON GIONG NHAU"// "����ͬ��ӡ",
#define OptionS3                  "KHONG GOP"// "�˲�ͬ��ӡ",
  ////"//Option for dept
#define OptionS4                  "GIA BANG 0"// "��ֹ��۸�",
#define OptionS5                  "LUOI PHAN CHIA"// "��ӡ�ָ���",
#define OptionS6                  "DOC LAP"// "��������:",
#define OptionS7                  "GIAM GIA 1"// "�ۿ��� 1:",
#define OptionS8                  "GIAM GIA 2"// "�ۿ��� 2:",
  ////Options for tend
#define OptionS9                  "MO KET"// "��Ǯ��:",
#define OptionS10                 "NHAP TIEN"// "������:",
#define OptionS11                 "CAM"// "��ֹ����:",
#define OptionS12                 "NHAP SO:"// "�������:",
#define OptionS13                 "TIEN BOA"// "����ΪС��",
  ////Options for PoRa
#define OptionS14                 "MO KET"// "��Ǯ��:",
#define OptionS15                 "THANH TOAN"// "���ʽ��",
#define OptionS16                 "DAT COC"// "������:",
#define OptionS17                 "CHI//THU"// "���//����",
  ////Option for Disc
#define OptionS18                 "IN GIAM GIA"// "��ӡ�ۿ۶�",
#define OptionS19                 "GIAM GIA 1"// "ʹ���ۿ�1:",
#define OptionS20                 "GIAM GIA 2"// "ʹ���ۿ�2:",
  ////Options for currency
#define OptionS21                 "THOI LAI"// "����������",
  ////Options for Draw
#define OptionS22                 "KHONG THAP PHAN"// "��С����:",
#define OptionS23                 "MO KET"// "��Ǯ��:",
  ////Options for Tax
#define OptionS24                 "CO THUE"// "Ӫҵ//��ֵ:",
#define OptionS25                 "IN THUE VAT"// "��ӡ˰����",
#define OptionS26                 "IN 0"// "��ӡ0˰��",
#define OptionS27                 "CAC LOP THUE"// "ΪGST��˰",
#define OptionS28                 "IN THUE"// "��ӡ˰��:",
  ////Options for clerk
#define OptionS29                 "GIOI HAN SUA SAI"// "ȡ������:",
#define OptionS30                 "GIOI HAN XOA"// "��������:",
#define OptionS31                "GIOI HAN HUY"// "ȡ������:",
#define OptionS32                 "GIOI HAN TRA LAI"// "�˻�����:",
#define OptionS33                 "GIOI HAN GIAM %"// "%�ۿ�����:",
#define OptionS34                 "GIOI HAN CONG %"// "%�ӳ�����:",
#define OptionS35                 "GIOI HAN +- TIEN"// "+-�������",
#define OptionS36                 "THUC TAP"// "��ѵģʽ:",
#define OptionS37                 "LAY SO"//mPRNINDEX////Ccr "ȡ�˺�:",

#define MESS_ECR_IP         "DIA CHI MAY"//
#define MESS_ECR_ID         "SO MAY(0-9,A-F):"//

#define EditN1                    "<GHI SO>GHI MOI \n<XAC NHAN>GHI SO GOC \n"////---ZY  ////ccr "<��¼��>  �¼�¼\n<ȷ��>  ��ǰ��¼\n",
#define EditN2                    "<GHI SO>A//D ITEM \n<XAC NHAN>GHI SO GOC \n"//---ZY  ////ccr "<��¼��>��ɾ��Ʒ\n<ȷ��>  ��ǰ��Ʒ\n",
#define EditN3                    "<THOAT>        THOAT"//---ZY  //// "<�˳�>      �˳�",
#define EditN4                    "<XAC NHAN> TIEP TUC\n"//---ZY  //// "<ȷ��>      ����\n",
#define EditN5                    "CHON BAO CAO"// "��<ѡ��>����",
#define EditN6                    "TIEU THU"// "���ѽ��",
#define EditN7                    "BAM PHIM"//---ZY  ////"����     ->��   ",
#define EditN8                    "CHI O CHUC NANG QUAN LY"// "ֻ���ھ�����",
#define EditN9                    "O CHE DO BAN HANG"// "����Ӫҵ����",
#define EditN10                   "VAN BAN"// "��ӡ����",
#define EditN11                   "(BAO LUU)"// "����",
#define EditN12                   "TAP TIN//MAT MA//KIEM TRA"// "�ļ��������",
#define EditN13                   "QUAY SO"// "����",
#define EditN14                   "DANG KET NOI"// "MODEM ����!",
#define EditN15                   "MA:"// "����:",
#define EditN16                   "GIAM %"// "%�ۿ�",
#define EditN17                   "CONG %"// "%�ӳ�",
#define EditN18                   "SO HOA DON:"// "�վݺ�:",
#define EditN19                   "NHUNG TAP TIN"// "�ļ�����"��0
#define EditN20                   "TONG"// "�ļ��ռ䣺"?
#define EditN21                   "BAO CAO"// "ͳ���ļ�"2
#define EditN22                   "THUE"// ����˰��8
#define EditN23                   "BO NHO CUON LUU"// "��ˮ�ռ�"
#define EditN24                   "TAP TIN       BAN GHI       RAM"// "�ļ���      ��¼��      �ռ��С"
#define EditN25                   "CONG       LOAI       GIAO THUC"// "��������    ͨ�����   ͨ��Э��"
#define EditN26                   "DONG TRONG"// '����������',
#define EditN27                   "SO DONG TREN TRANG"// 'ÿҳ����',
#define EditN28                   "IN NGAY"// '��ӡ��Ϣ',
#define EditN29                   "NHAN SEC"// '�ڶ���Ʊ��',
#define EditN30                   "LE TRAI"// '��߾�',
#define EditN31                   "LOAI"// 'Ʊ�����',
#define EditN32                   "TAT HOA DON"// "��ӡ����",
#define EditN33                   "MO HOA DON"// "��ӡ����",
  ////ChipCard>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define ChipCardN1                "MAT MA"//I "����:",
#define ChipCardN2                "BUOC NHAP MAT MA"// "����ȷ��:",
#define ChipCardN3                "MA POS"// "POS����:",
#define ChipCardN4                "XAC NHAN MA POS"// "����ȷ��:",
#define ChipCardN5                "LUU MA POS"// "�����ѱ���",
#define ChipCardN6                "LOI MA POS"// "����� ��",
#define ChipCardN7                "THE CHIP"// "����IC��:",
#define ChipCardN8                "GIAM GIA"// "�ۿۿ�:",
#define ChipCardN9                "TIEN MAT"// "�ֽ�:",
#define ChipCardN10               "THE TIN DUNG"// "���ʿ�:",
#define ChipCardN11               "IN"// "��ӡIC��",
#define ChipCardN12               "TU DONG GIAM GIA"// "�Զ��ۿ�:",
#define ChipCardN13               "DIEM"// "���ѻ���:",
#define ChipCardN14               "TIEN MAT=CC"// "���ֽ��:",
#define ChipCardN15               "HAN SU DUNG"// "������Ч��", ////
#define ChipCardN16               "MAT DANH SACH"// "��ʧ����",
#define ChipCardN17               "SO THE"// "����:",
#define ChipCardN18               "LOAI THE"// "������:",
#define ChipCardN19               "CAN BANG"// "���"
#define ChipCardN20               "TIEN GIU THE"// "��Ѻ��:",
#define ChipCardN21               "CHI TIEU"// "����:",
#define ChipCardN22               "PHI NAP"// "��ֵ�ܶ�:",
#define ChipCardN23               "HOA DON"// "ʹ�ô���:",
#define ChipCardN24               "MUC GIA"// "�۸񼶱�:",
#define ChipCardN25               "MA PIN"// "PIN��:",
#define ChipCardN26               "MUC BAO MAT"// "��������:",
#define ChipCardN27               "THANH TOAN TU DONG"// "�Զ�����:",
#define ChipCardN28               "NGAY LAM THE"// "�ƿ�����:",
#define ChipCardN29               "NGAY HET HAN"// "����Ч��:",
#define ChipCardN30               "KHACH HANG"// "�ͻ�:",
#define ChipCardN31               "TAO"// "��ʼ��IC",
#define ChipCardN32               "NAP THE IC"// "IC����ֵ",
#define ChipCardN33               "XOA THE IC"// "���IC��",
#define ChipCardN34               "NAP ?"// "��ֵ//�˿�?",
#define ChipCardN35               "HOAN TRA ?"// "����//�͵�?",
#define ChipCardN36               "XAC NHAN ?"// "ȷ�ϳ�ֵ?",
#define ChipCardN37               "XAC NHAN ?"// "ȷ���˿�?",
#define ChipCardN38               "XAC NHAN ?"// "ȷ���͵�?",
#define ChipCardN39               "XAC NHAN ?"// "�ҽ�ȷ��?",
#define ChipCardN40               "TONG DIEM DOI"// "�Ƶ�ҽ�",
#define ChipCardN41               "TRA THE"// "IC���˿�",
#define ChipCardN42               "DIEM DOI THE IC"// "IC���ҽ�����",
#define ChipCardN43               "SO DIEM THE IC"// "IC���͵���",
#define ChipCardN44               "XIN DOI"// "��ȴ�......",
#define ChipCardN45               "TRUOC TIEN XIN TRA LAI..."// "�����н��,�����˿�....",
#define ChipCardN46               "THE HOI VIEN:"// "��Ա��:",
#define ChipCardN47               "THANH VIEN"// �� Ա �� ��
#define ChipCardN48               "KHOI DONG LAI IP MOI"// "Ҫ�����µ�IP,�����¿���.",
#define ChipCardN49               "XAC NHAN XOA ?"//  "ȷ���屨��?",
#define ChipCardN50               "XIN DOI..."// "�ȴ�IC��....",
#define ChipCardN51               "IN CAO GAP DOI"//---zy  //// "���ߴ�ӡ",
////cr2015-06-15>>>>>>>>>>>>>>>>>>>>>
#define ChipCardN52             "XOA"//
#define ChipCardN53             "TRA LAI"//
#define ChipCardN54             "THANH TOAN"//
#define ChipCardN55             "PHU THU"//
#define ChipCardN56             "KHOI TAO"//
#define ChipCardN57             "XUAT TIEN"//
#define ChipCardN58            "THEM DIEM//ADDVIPPOINTS"
#define ChipCardN59            "GIAM DIEM//DECVIPPOINTS"
#define ChipCardN60            "TONG DIEM//VIPPOINTS"
////ccr2015-06-15<<<<<<<<<<<<<<<<<<<<<
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MESSEJ_X_STORE      "SAVE X DATA"//MsgEJ_X_STORE
#define MESSEJ_Z_STORE      "SAVE Z DATA"//MsgEJ_Z_STORE
#define MESSEJ_TR_STORE     "SAVE TRAIN"//MsgEJ_TR_STORE
#endif
////ccr2016-02-22>>>>>>>>>>>>>>>>>>>>>
#define MsgMENUXREPORT     "XEM BAO CAO"//
#define MsgMENUXEXPORT     "XUAT(X)"//
#define MsgMENUQUICKVIEW   "DOANH THU"//
#define MsgMENUXLOGFUNC     "XEM CUON LUU"//
#define MsgMENUSENDNEWLOG  "GUI DANG NHAP"      //MENUSENDNEWLOG  //��������ˮ����
#define MsgMENUXPASSWORD   "MAT MA XEM"//
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MsgMENUXEJOURNAL    "EJ"     //MENUXEJOURNAL   "E Journal"
#endif
////................................
#define MsgMENUZREPORT     "LAY BAO CAO"//
#define MsgMENUZEXPORT     "XUAT (Z)"//
#define MsgMENUCLEARLOG     "XOA CUON LUU"//
#define MsgMENUZGRAND      "CAI DAT XOA TONG"//
#define MsgMENUZPASSWORD   "MAT MA LAY BC"//
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MsgMENUZRESETEJ   "RESET EJ"     //MENUZRESETEJ   "Clear EJ"
#endif
//...................................


#define EPosN1                    "MA EPOS:"// "ePOS��֤��:",
#define EPosN2                    "XIN DOI..."// "�ȴ���ͨ��"
#define EPosN3                    "SO THE:"// "��ͨ����:",
#define EPosN4                    "CAN BANG:"// "��ͨ�����:",

#define ErrInfoN1                 "VUOT GIOI HAN"// "ͨѶ���ݹ���"
#define ErrInfoN2                 "***IN GIAN DOAN***"// " *** ��ӡ���жϡ����´�ӡ *** "
#define ErrInfoN3                 "LOI DU LIEU !"// "����У���"
////PRINT
#define PLULIST                  "DANH SACH MA HANG"// "         �� Ʒ �� Ϣ ��"
#define PLUTITLE1                "TEN HANG                   ID"//
#define PLUTITLE2                ">>NHOM     KHO     GIA"//

#define DEPTLIST               "DANH SACH NHOM"// "         �� Ʒ �� Ϣ ��"
#define DEPTTITLE              "TEN HANG      NHOM CHU      GIA"//



#define FisTextN1              "NOP THUE SO:"//"��˰�˺�:"
#define FisTextN2                 "IN PHIEU"//"����˰Ʊ        "
#define FisTextN3                 "SO UY QUYEN"//"��Ȩ����        "
#define FisTextN4                 "CONG SO:"//"д������        "
#define FisTextN5                 "XAC NHAN CONG"//"д��ȷ��        "
#define FisTextN6                 "IN DU LIEU"//"����ӡ��        "
#define FisTextN7                 "MA SO NGUOI DUNG"//"�û�����        "
#define FisTextN8                 "MIEN THUE"//"��˰״̬        "
#define FisTextN9                 "SO LAN LAY Z"//"Z-����:         "
#define FisTextN10                "TONG CHIU THUE"//"�ۼ�����        "
#define FisTextN11                "THUE TICH LUY"//"�ۼ�˰          "
#define FisTextN12                "TONG MIEN THUE"//"����˰��        "
#define FisTextN13                "TONG CHIU THUE"//"�����۶�        "
#define FisTextN14                "TONG THUE"//"��˰��          "
#define FisTextN15                "HOA DON NGAY"//"��˰Ʊ��        "
#define FisTextN16                "TONG PHIEU THUE"//"�վ�����        "
#define FisTextN17                "BAO CAO TONG"//"�౨���� :      "
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

#define CurrentTimeN1                    "GIO:"//  "��ǰʱ��"
#define InputMode1			"A:"// "A��"
#define InputMode2			"QU:"// "����"
#define InputMode3			"PING:"// "ƴ��"
#define InputMode4			"WUBI:"// "�ʣ�"

#define SpecialSymbol1			"<<"			////RUT//DOWNLOAD////Ccr "��",
#define SpecialSymbol2			">>"			////TAI//UPLOAD////Ccr "��",
#define SpecialSymbol3			"->  <-"		////TRUYEN// "��  ��",
#define DEPTREPORTTITLE         "NHOM       S.L        THANH TIEN"//"��������     ��������       ���"
#define PLUREPORTTITLE          "MA HANG     S.L        THANH TIEN"//
#define MESS_PRESSKEY          "BAM PHIM BAT KY"//

#if defined(CASE_QRCODE)
#define InputQRCode           "MA QR"//MsgQRCODE
#endif

#define GPRSServerIP			"IP MAY CHU"//"������IP"
#define GPRSServerPort		    "CONG"//"�˿ں�"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////added by lqw 090802
#if  (defined(CASE_GPRS))
#define GPRSAPNName        "APN//GPRSAPNNAME"
#define GPRSUserName       "TEN NGUOI DUNG//GPRSUSERNAME"
#define GPRSPassword       "MAT MA//GPRSPASSWORD"

#define GPRSSendMESS       "Check GPRS"//ccr2014-11-11 NEWSETUP
#define GPRSSetMode         "DAT CHE DO GUI"//gprsSETMODE ////ccr2014-11-11 NEWSETUP-step2
#define GPRSSendECRLogAll   "GUI TAT CA DANG NHAP"//gprsSendECRLogAll ////ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadPLU     "CAP NHAT MA HANG"//gprsDownloadPLU ////ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadDEPT    "CAP NHAT NHOM"//gprsDownloadDEPT ////ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadCLERK   "CAP NHAT NHAN VIEN"//gprsDownloadCLERK ////ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadHEAD    "CAP NHAT TIEU DE DAU"//gprsDownloadHEAD ////ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadTRAIL   "CAP NHAT TIEU DE CUOI"//gprsDownloadTRAIL ////ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadALL     "CAP NHAT TIEU ALL"      //gprsDownloadALL //ccr2016-08-18
#define GPRSRestart         "RESET GPRS UNIT"      //gprsRestart //ccr2016-08-26

#define GPRSstr1 "LOI DU LIEU"// "�������ʹ�"
#define GPRSstr2 "WIRELESS OK"//
#define GPRSstr3 "WIRELESS CHUA OK"//
#define GPRSstr4 "XAC NHAN"//
#define GPRSstr5 "IP//CONG BI RONG"//
#define GPRSstr6 "LOI IP//CONG"//
#define GPRSstr7 "DANG CHO WIRELESS"//
#define GPRSstr8 "DONG Y"// "��"
#define GPRSstr9 "KHONG DONG Y"// "fou "
#define GPRSstr10 "DANG TRUYEN..."// "���ݷ�����.. "
#define GPRSstr11 "HOAN TAT"// "�����ѷ���.. "
#define GPRSstr28 "THANH CONG...."// "���ͳɹ�.."
#define GPRSstr31 "LOI KET NOI"//						 "����ʧ��"
#define GPRSstr32 "DOC THAT BAI"// "����ʧ��"
#define GPRSstr33 "XAC NHAN THAT BAI"// "����ȷ��ʧ��"
#define GPRSstr34 "THAT BAI"// "����ʧ��"
#define GPRSstr58 "KET NOI...."// "���ڽ�������.."
#define GPRSstr59 "KET NOI...."// " ׼����������.."
#define GPRSstr60 "KHOI DONG WIRELESS"// "���ڸ�λģ��.."
#define GPRSstr61 "DA GUI XONG"// "�������,���˳�"
#define GPRSxACK  "WAIT ACK ERROR"
#endif ////end defined(CASE_GPRS)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define InsertUSB		"<<XIN GAN USB"//CHRUSB  ����U�� ////

////ccr090715>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define usbMAIN1		"SAO CHEP SANG USB"//usbDAOCHU	�����տ���ļ� ////
#define usbMAIN2		"SAO CHEP TU USB"//usbDAORU �����տ���ļ� ////
#define usbMAIN3		"CUON LUU SANG USB"//usbFLOW ����������ˮ ////


#define usbFLOWNEWMESS	    "XUAT DL MOI"//1-����������   ////
#define usbFLOWALLMESS	    "XUAT TOAN BO"//2-����ȫ������
#define usbFLOWDELMESS	    "XUAT VA RESET"//3-����ȫ�����ݺ����
#define usbALLFile		"TAT CA TAP TIN"//usbALL ȫ���ļ� ////


#define MESSPRNMENU     "<00> IN MENU"//
#define MESSSETMENU     " MANUALS LIST"//
#define MESSCLEANLOG    "XOA CUON LUU DIEN TU?"//
#define MESSCLEANLOGA   "TAT CA CUON LUU\nSE BI XOA!"//
#define MESSRAMOUT      "BI TRAN RAM"//
#define MESSCLEANFILES  "XOA TAP TIN?"//
#define MESSCONFIGERR   "THAY DOI CAU HINH,\nSE BI LOI NEU\nDUNG TAP TIN CU"//
#define MESSDELPLU      "BIEN THAY DOI\n   XOA MA HANG"//
#define MESSPLUPRINTEND "IN MA HANG O.K.\nBAM <ENTER>"//

#define REPRN_PWON      "IN LAI KHI MO NGUON....."//
#define REPRN_PAPERON   "IN LAI KHI GIAY O.K...."//

#define RECALLFLOW      "GOI LAI CUON LUU"//

#define USBREPNAME      "TEN"//

////////////////  CSV�����ļ�����  //////////////////////////////////////////////////////////////////////////////////////////
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

#define MESS_LOGREPET   "Re-Send All LOG!"

#define MESS_PAYALSO   "Confirm Payment?"


////ccr2016-01-12>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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
#define GRAPHICTREE     "  CHRISTMAS TREE"        ////CHRISTMAS TREE
#define GRAPHICHBREAD   "  HOT BREAD"
#define GRAPHICJOY      "  JOY"
#define GRAPHICFISH     "  FISH"
#define GRAPHICCARTOON  "  CARTOON CHICKEN"        ////CARTOON CHICKEN
#define GRAPHICMONEY    "  MONEY"
#define GRAPHICEAT      "  EATING"
#define GRAPHICKITE     "  FLY KITE"            ////FLY A KITE
#define GRAPHICRUN      "  RUNNING"
#define GRAPHICREST     "  REST"
////...............................................
#define MGADDINV        "NHAP KHO"//1+SUBTOTAL
#define MGDECINV        "TRU KHO"//2+SUBTOTAL
#define MGSETPRICE      "GIA"//3+SUBTOTAL

#define MGCLEARIC       "TRA THE IC"//
#define MGINITIC        "TAO THE IC"//
#define MGCHARGE        "NAP THE IC"//
#define MGADDPOINT      "THEM DIEM"//
#define MGPRINTSTOCK   "LIST STOCK"

#define MGPASSWORD      "CAI DAT MAT MA"//
#define MGCLOSEPRN      "TAT MAY IN"//
#define MGTRAINING      "CHE DO THUC TAP"//
#define MGGOTOMG        "CHE DO QUAN LY"//

////..............................................
#define PLUCODE     "PLU CODE"
#define INVQTYMUST  "INPUT QTY/PRICE"
#define ININVENTORY "Press <SUBT> Key\n Exit Inventory!"
////..............................................
#define DEVICENULL	"RONG"//
#define DEVICEPORT1     "CONG 1"//
#define DEVICEPORT2     "CONG 2"//
#define DEVICEPORT3     "CONG 3"//
#define DEVICEPORT4     "CONG 4"//

////................................................
#define CLOSEPRINTER    "TAT MAY IN"//
#define CLEARGRANDTOTAL "XOA TONG SAU KHI LAY BC Z"//
#define CLEANALLECRVIP  "XOA TAI KHOAN?"//"�����Ա����?"
#define ECRVIPTITLE     "ACCOUNT          AMOUNT   POINTS"
#define CREATEDATE      "CREATE DATE"
////ccr2016-06-06>>>>>>>>>>>INDIA>>>>>>>>>>>>>>>>
#define MsgEDITPLU      "CHINH SUA MA HANG"//
#define MsgEDITDEPT     "CHINH SUA NHOM"//
////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

                       ////012345678901234567890123456789012
////.......�������Ӧ������.........................................
#define MsgKEYCORR      "SUA SAI"//
#define MsgKEYCURR      "TIEN TE"//
#define MsgKEYDISC      "GIAM GIA"//
#define MsgKEYPBFUN     "CHUC NANG BAN"//
#define MsgKEYPORA      "CHI THU"//
#define MsgKEYPO_RA      "CHI/THU"
#define MsgKEYTEND      "THANH TOAN"//
#define MsgKEYCLEAR     "XOA"//
#define MsgKEYFEED      "CHAY GIAY"//
#define MsgKEYMULT      "X"//
#define MsgKEYSUBTOT    "TONG CONG"//
#define MsgKEYPRICE     "GIA"//
#define MsgKEYPRICEN    "GIA MO"//
#define MsgKEYPRICE1    "GIA 1"//
#define MsgKEYPRICE2    "GIA 2"//
#define MsgKEYPRICE3    "GIA 3"//
#define MsgKEYPRICE4    "GIA 4"//
#define MsgKEYSHIFT     "TANG"//
#define MsgKEYDATE      "NGAY"//
#define MsgKEYWEIGHT    "NANG"//
#define MsgKEYCLERKN    "CA"//
#define MsgKEYDEPT      "NHOM~"//
#define MsgKEYDEPTNo    "NHOM#"//
#define MsgKEYPLUNo     "MA HANG#"//
#define MsgKEYDRAW      "MO KET"//
#define MsgKEYMEMO      "BO NHO"//
#define MsgKEYCLERK     "CA*"//
#define MsgKEYPLUDIR    "MA HANG~"//
#define MsgKEYLOCK      "VI TRI KHOA"//
#define MsgKEYDRAWFUN   "CHUC NANG KET*"//
#define MsgKEYSALPN     "N.VIEN PHUC VU#"//
#define MsgKEYSALP      "N.VIEN PHUC VU"//
#define MsgKEYDOT       "'.'"
#define MsgKEYZERO2     "'00'"
#define MsgKEYNUMBER    "0~9"
#define MsgKEYSUSPEND   "GIU"//
#define MsgFUNCLOOK1    "CHUC NANG TIM KIEM 1"//
#define MsgFUNCLOOK2    "CHUC NANG TIM KIEM 2"//
#define MsgMODELOCK     "VI TRI KHOA"//
#define MsgVIPLOGIN     "VAO TAI KHOAN"//
#define MsgINPUTNUM     "NHAP MA VAO"//
#define MsgCUSTOMER     "CUSTOMER"
#define MsgKEYNULL      "RONG"//

#define MsgRHEADER      "Header*"
#define MsgRTRAILER     "Trail*"
#define MsgKEYBOARD     "Keyboard*"
#define MsgSYSFLAGS     "System*"
#define MsgSETDATE      "Datetime*"

////...........................................
#define MsgCONFIRM      "XAC NHAN"//
#define MsgNET          "TINH"// "����",
#define VIPLOGOUT       "XUAT TAI CHINH"//
#define VIPTOTAL        "GIA TRI"//
#define VIPTOTALA       "TONG GIA TRI"//
#define DECVIPPOINT     "GIAM"//���ȱ���Ϊ4
#define ADDVIPPOINT     "TANG"//���ȱ���Ϊ4
#define INPUTVIPNAME    "TEN"//
#define PRINTKEYBOARD   "IN BAN PHIM"//
////..........................................
#define MESSALLLOG       "CUON LUU THEO SO "//
#define MESSDATERANGE   "CUON LUU THEO NGAY"//
#define MESSVIPLOG      "VAO TAI KHOAN"//
#define MESSPRNCASH     "IN TIEN MAT"//"��ӡ�����¼"
#define MESSPRNDEPART   "IN NHOM"//"��ӡ�����¼"
#define MESSPRNPLU      "IN MA HANG"//"��ӡ��Ʒ��¼"
#define MESSPRNDISCOUNT "IN GIAM GIA"//"��ӡ�ۿۼӳ�"
#define MESSPRNRAPO     "IN CHI//THU"//"��ӡ�����"
#define MESSPRNCORRECT  "IN SUA SAI"//"��ӡ��������"
#define MESSPRNCANCEL   "IN HUY"//"��ӡ����ȡ��"
#define MESSPRNNOSALE   "IN MO KET"//"��ӡ������"

#define MESSALLCASH	"TAT CA TIEN MAT"//"ȫ�����ʽ"
#define MESSSELCASH	"CHON 1 TIEN MAT"//"ѡ�񸶿ʽ"
#define MESSALLDEPT	"TAT CA NHOM"//"��ӡȫ������"
#define MESSSELDEPT	"CHON 1 NHOM"//"ѡ��һ������"
#define MESSALLPLU	"TAT CA MA HANG"//"��ӡȫ����Ʒ"
#define MESSSELPLU	"CHON 1 MA HANG"//"ѡ��һ����Ʒ"
////........................................
////ccr2016-03-15>>>>������̺�>>>>>
#define MESSMACRO       "TICH HOP"//  "�궨��"
////....ListItems��ʾ��Ϣ....................................
#define It_MGITEMS      "CHUC NANG QUAN LY"//
#define It_SELEFUNC     "PHIM CHUC NANG"//
#define It_SELEITEM     "CHON MAT HANG"//
#define It_SELEKEYTYPE  "LOAI BAN PHIM"//
#define It_SELETEST     "CHON MAT HANG"//
#define It_SELELOG      "CHON DANG NHAP"//
#define It_SELETEND     "CHON KIEU"//
#define It_SELEDEPT     "CHON NHOM"//
#define It_SELEPLU      "CHON MA HANG"//
#define It_SELEMODI     "CHON BO NHO"//
#define It_SELEREPORT   "CHON BAO CAO"//
#define It_SELEPOINT    "CHON DIEM"// С��λ��"
#define It_SELEEJ       " EJ      "
////........................................................
#define MESSRAMVAR      "VARIABLE"
////.........................................................
#define PLUNUMBER           "SO BANG GHI"//
#define PLURANDOMSIZE     "KICH CO CUA MA"//
#define PLUNAMESIZE	"KICH CO CUA TEN"//
#define PLUPRICESIZE      "KICH CO CUA GIA"//
#define PLUPRICELEVEL     "GIA TAI KHOAN"//
#define PLUCOSTSIZE       "KICH CO GIA CA"//
#define PLUINVENTSIZE     "KICH CO CUA KHO"//
#define PLUREPQTYSIZE     "KICH CO CUA COT S.L"//
#define PLUREPAMTSIZE     "KICH CO CUA COT THANH TIEN"//
#define PLUREPDISCSIZE    "KICH CO CUA COT GIAM GIA"//
#define PLUREPCOSTSIZE    "KICH CO CUA COT GIA"//
////"//........................................................
#define POINTTYPE         "DAU CHAM"//
#define POINTTYPE1        "1.000,00"////"2 SO THAP PHAN"//��λС��
#define POINTTYPE2        "1,000.00"////"2 SO THAP PHAN"//��λС��
#define POINTTYPE3        "   1.000"
#define POINTTYPE4          "   1,000"
#define POINTTYPE5          "1.000,000"  ////"3 SO THAP PHAN"//��λС��
#define POINTTYPE6          "1,000.000"  ////"3 SO THAP PHAN"//��λС��
//#define POINTTYPE7          "1.000,0"  ////"1 SO THAP PHAN"//һλС��
//#define POINTTYPE8          "1,000.0"  ////"1 SO THAP PHAN"//һλС��
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
#define DATETYPE        "DINH DANG"//
#define DDMMYYYY        "DDMMYYYY"
#define MMDDYYYY        "MMDDYYYY"
#define YYYYMMDD        "YYYYMMDD"
////.......................................................
#define XUPDATEBIOS     "Can't Update \nfirmware by USB"
////ccr2016-06-22..........................................
#if defined(CASE_QRCODE)
#define MESSWXPAY       "OK WX-PAY"
#endif

#define SENDLOGAUTO     "SEND AUTO:"
#define DAYSFORLOG      "DAYS FOR SEND:"
#define ACKMUSTNEED     "ACK NEEDED:"

#define CSV_TITLE       "TEN HANG,SO LUONG,SO TIEN\r\n"

#define Msg_MANAGEMENT "MANAGEMENT LIST "

//ccr2017-01-10>>>>>>>>>>>>>>>>>>>>>>>>>
#define Msg_NOSTOCK     "NO STOCK FIELD"
#define Msg_DISPSTOCK   "DISPLAY/PRINT?"
//ccr2017-01-10<<<<<<<<<<<<<<<<<<<<<<<<<<

#endif

