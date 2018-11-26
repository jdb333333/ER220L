#ifndef MESSAGE_SP
#define MESSAGE_SP


//----------Length<=32------------------
#define Header1         "*       LO MEJOR PARA USTED   *" // "*   �� �� �� ��  �� �� �� ��  *"
#define Header2         "*       LO MEJOR PARA USTED  *" // "*   �� �� �� ��  �� �� �� ��  *"

#define ReportType0     "TOTAL VENTA  "// " ��  ��  ��  �� "
#define ReportType1     "INFO-GRUPO     "//" ��  ��  ͳ  �� "
#define ReportType2     "INFO-DEPT      "//" ��  ��  ͳ  �� "
#define ReportType3     "INFO-ARTICULO "//" ��  Ʒ  ͳ  �� "
#define ReportType4     "INFO-PAGO   "// " ��  ��  ͳ  �� "
#define ReportType5     "INFO-CAJA +/-  " //" �� �� �� ͳ �� "
#define ReportType6     "INFO-CAJA     " //" Ǯ  ��  ͳ  �� "
#define ReportType7     "INFO-ALTERACION " // " ��  ��  ͳ  �� "
#define ReportType8     "INFO-DESCUENTO  " // " ��  ��  ͳ  �� "
#define ReportType9     "INFO-DIVISA    " //" ��  ��  ͳ  �� "
#define ReportType10    "INFO-IMPUESTO   " //" ��  ˰  ͳ  �� "
#define ReportType11    "INFO-CUENTA-MESA" // " ��  ��  ͳ  �� "
#define ReportType12    "INFO-ALIMENTACION" // " ��  ��  ͳ  �� "
#define ReportType13    "  INFO-MESA     "//" ��  ̨  ͳ  �� "
#define ReportType14    "  ALMACEN       "//" ��  Ʒ  ��  �� "
#define ReportType15    " FACTURA        "
#define ReportType16    "BUFFER VENDEDOR "

#define ReportType17    "INFO-CAJERO   "//" �� �� Ա ͳ �� "
#define ReportType18    "INFO-VENDEDOR  "// " Ӫ ҵ Ա ͳ �� "

#define Trailer1        "     GRACIAS POR LA VISITA  "//"     ~��  ~л  ~��  ~��   "
#define Trailer2        "     HASTA LA PROXIMA VISITA"//"           ~��  ~��"
//----------Length<=16------------------
#define ReportList1     "DIA CAJERO"//" �� �� Ա �� �� "
#define ReportList2     "SEMANA CAJERO"//" �� �� Ա �� �� "
#define ReportList3     "DOC/DIA -VENTA"//" ��  ��  ��  �� "
#define ReportList4     "DOC/SEMANA-VENTA"//" ��  ��  ��  �� "
#define ReportList5     "DOC-ARTICULO"//" ��  Ʒ  ��  �� "
#define ReportList6     "DOC-CUENTA-MESA "//  " ��  ��  ��  �� "
#define ReportList7     "DOC-TIEMPO"//" ʱ  ��  ��  �� "
#define ReportList8     "D-TODOCAJERO"// "  ȫ�տ�Ա�ձ�  "
#define ReportList9     "S-TODOCAJERO"//"  ȫ�տ�Ա�±�  "
#define ReportList10    "DOC/DIA-VENDEDOR"//" Ӫ ҵ Ա �� �� "
#define ReportList11    "SEMANA VEND."//" Ӫ ҵ Ա �� �� "
#define ReportList12    "DIA-TODOVEND."// "  ȫӪҵԱ�ձ�  "
#define ReportList13    "SEMANATODOVEN"// "  ȫӪҵԱ�±�  "

#define Promotion1      " USTED TOCA PREMIO  "// "  ~��  ~ϲ  ~��  ~��"

//----------Length<=12------------------
#define Correc1         "CANCELAR"//"~ȡ~��  "
#define Correc2         "ALTERAR "//  "~��~��  "
#define Correc3         "DEVOLUCION"// "~��~��  "
#define Correc4         "CANCEL PEDID"//"~ȡ~��~��~��"
#define Correc5         "APARCA �"//   "~��~��"

#define CURRENCY1         "DOLAR   "//"��Ԫ    "
#define CURRENCY2         "YEN     "//"��Ԫ    "
#define CURRENCY3         "HK $    "//"�۱�    "
#define CURRENCY4         "DIVISA 1"// "��� 1  "
#define CURRENCY5         "DIVISA 2"//"��� 2  "


#define DISCOUNT1          "COMIS.%"//"%�ӳ�"
#define DISCOUNT2          "DTO-%"//  "%�ۿ�"
#define DISCOUNT3          "COMIS.�"// "���ӳ�"
#define DISCOUNT4          "DTO-�"//  "����ۿ�"
#define DISCOUNT5          "COMISION-#"//"����ӳ�"

#define DISCOUNT6          "S.TOTAL %+"//"С��%�ӳ�"
#define DISCOUNT7          "S.TOTAL %-"// "С��%�ۿ�"
#define DISCOUNT8          "+ S.TOTAL"//"С��ֱ��"
#define DISCOUNT9          "- S.TOTAL"//"С��ֱ��"


#define DRAWER1            "CASH"// "�ֽ�    "
#define DRAWER2            "CHEQUE  "// "֧Ʊ    "
#define DRAWER3            "T.CREDITO "//"���ÿ�  "
#define DRAWER4            "CUPON   "//"����ȯ  "
#define DRAWER5            "CREDIT  "//"��ͨ��  "
#define DRAWER6            "IC "// "IC��    "
#define DRAWER7            "PROPINA "// "С��    "
#define DRAWER8            "DRAW-8  "//��ӡ/��ʾ

#define PBFunction0         "ABRRMESA"// "��̨����"
#define PBFunction1         " + MESA  "//"��̨����"
#define PBFunction2         "PAGO TEMPORA"// "�ݽ�    "
#define PBFunction3         "CONFIRMAPAGO"// "ȷ�Ͻ���"
#define PBFunction4         "PRINT MESA"//"��ӡ��̨"
#define PBFunction5         "PRINT CUENTA"//"��ӡ�ʵ�"
#define PBFunction6         "CANCELAR"//"ȡ��ȷ��"
#define PBFunction7         "DIVIDECUENTA"// "����    "
#define PBFunction8         "TRANS-CUENTA"// "ת��    "
#define PBFunction9         "TRANSFCUENTA"//"ת����  "
#define PBFunction10        "GENTE NO  "// "����    "

#define PORAType1            "P.O"//ccr2016-08-09"CAJA + �"//"����    "
#define PORAType2            "R.A"//ccr2016-08-09"CAJA - �"//"���    "
#define PORAType3            "DEVOLVE�IC"//"IC���˿�"
#define PORAType4            "RECARGA"//  "IC����ֵ"
#define PORAType5            "-FINANZA"//"��ICѺ��"
#define PORAType6            "+FINANZA"//"��ICѺ��"

#define TendType1             "CASH"//"�ֽ�    "
#define TendType2             "CHEQUE  "//"֧Ʊ    "
#define TendType3             "T.CREDITO"//   "���ÿ�  "
#define TendType4             "CUPON   "//"����ȯ  "
#define TendType5             "CREDIT  "//"��ͨ��  "
#define TendType6             "IC "//  "IC��    "
#define TendType7             "DEBIT CARD"        //"DEBIT CARD"
#define TendType8             "CASH-8    "        //"CASH-8"


#define Modifier1             "INSTRUCCION"// "˵��    "
#define ClerkRec1             "CAJERO  "//"�տ�Ա  "
#define GroupRec1             "GRUPO   "//"����    "
#define DeptRec1              "DEPT"//"����    "
#define PLURec1               "ARTICULO "//"��Ʒ    "
#define SalesPersonRec1       "VENDEDOR"//"ӪҵԱ  "
#define OffRec1               "OFERTA  "//  "�������  "
//----------Length<=14------------------
#define XZReportList1         "CIERRE DIARIO"// "�����ձ���"
#define XZReportList2         "SEMANA-VENTA"//  "�����±���"
#define XZReportList3         "DOC-ARTICULO  "//"��Ʒ����"
#define XZReportList4         "MESA CUENTA"// "���ʱ���"
#define XZReportList5         "DOC-TIEMPO"//  "ʱ�α���"
#define XZReportList6         "DIA CAJERO"// "�տ�Ա�ձ���"
#define XZReportList7         "SEMANA CAJERO"//"�տ�Ա�±���"
#define XZReportList8         "D-TODOCAJERO"// "ȫ�տ�Ա�ձ���"
#define XZReportList9         "S-TODOCAJERO"//  "ȫ�տ�Ա�±���"
#if (salNumber)
#define XZReportList10        "DIA-VENDEDOR"//"ӪҵԱ�ձ���"
#define XZReportList11        "SEMANA VEND."// "ӪҵԱ�±���"
#define XZReportList12        "DIA-TODOVEND."// "ȫӪҵԱ�ձ���"
#define XZReportList13        "SEM-TODOVENDEDO" //"ȫӪҵԱ�±���"
#endif
#if (BARCUSTOMER==1)
#define XZReportList14        "SOCIO/BARCODE"//  "�����Ա����"
#endif
#define XZReportList15        "GRABA EN U" //ccr090715 "�����U��"

//----------Length<=6------------------
#define PortType1               "  PC"//"  ����"
#define PortType2               "SCANER"//"����ǹ"
#define PortType3               "BALANZ"// "���ӳ�"
#define PortType4               "COCINA"//"��  ��"
#define PortType5               "TICKET"//"Ʊ ��"
#define PortEXTPRN              "EP-PORT"//ccr2016-12-14 ExtPrinter????
#define PortType6               "MR IC"//"��Ƶ��"
#define PortType7               "E CARD"//"Eͨ��"

#define KClose                  "CERRAR"//  "   �� "

//----------Length<=10------------------
#define SysFlags0		        "LOCAL NO:    "//"���̱��:"
#define SysFlags1               "CAJA NO:     "// "�տ����:"
#define SysFlags2               "ROUNDING::"//"���뷽ʽ:"
#define SysFlags3               "CAMBIA PVP:"//"��Ʒ���:"
#define SysFlags4               "SILBATO:"//  "������:"
#define SysFlags5               "DESIGNA C"//"ǿ���տ�Ա"
#define SysFlags6               "CAMBIAR C"// "�ı��տ�Ա"
#define CLERKPASS               "CLAVE C."//"�տ�Ա����"
#define SysFlags8               "PRINT.VEND."// "��ӡӪҵԱ"
#define SysFlags9               "PRINT C."//  "��ӡ�տ�Ա"
#define SysFlags10              "PRINT DOC#"// "��ӡ�վݺ�"
#define SysFlags11              "OSCURO PRINT"// "��Ũ�ȴ�ӡ"
#define SysFlags12              "DESIGNA V."//"ǿ��ӪҵԱ"
#define SysFlags13              "IMPRIME#"// "��ӡ����:"
#define SysFlags14              "PULSES.TOTAL:"// "��С�Ƽ�:"
#define SysFlags15              "IMPR.VENTA"// "��ӡ������"
#define SysFlags16              "IMPRIME DOC:"// "��ӡСƱ:"
#define SysFlags17              "CABEZA-TIC:"//"СƱƱͷ:"
#define SysFlags18              "BLOQ SHIFT:"//"����SHIFT:"
#define SysFlags19              "MUESTRAHORA:"//"��ʾʱ��:"
#define SysFlags20              "COPIA DOC:"// "�����վ�:"
#define SysFlags21              "ESPECIAL #:"// "��������:"
#define SysFlags22              "MONTA DIA:"//"������־:"
#define SysFlags23              "PRINT.MESA:"//"��̨��ӡ:"
#define SysFlags24              "PRINT.STCOK:"//"��ӡ���:"
#define SysFlags25              "INTERRUPTOR:"// "��ӡ����:"
#define SysFlags26              "OBL.MESA:"// "���뿪̨:"
#define SysFlags27              "CONSERVA#"// "�����վݺ�"
#define SysFlags28              "COPYCOCINA:"// "���Ƴ���:"
#define SysFlags29              "RECUPERA#"// "�վݺŸ�λ"
#define SysFlags30              "ALTA IMPRIME:"//"���ߴ�ӡ:"
#define SysFlags31              "PARIDAD:"//  "�Աȶ�:"
#define SysFlags32              "CBZ.CENTRO:"//"Ʊͷ����:"
#define SysFlags33              "PIE CENTRO:"//  "Ʊβ����:"
#define SysFlags34              "ALTA CABEZA:"//Ʊͷ����:
#define SysFlags35              "ALTA PIE:"//Ʊβ����
//ccr2016-03-21#define SysFlags36              "EXPORTAR CSV"//".CSV����"
#define SysFlags37              "PRINT FECHA"// "��ӡ����"
#define SysFlags38              "PRINT HORA"// "��ӡʱ��"
#define SysFlags39              "PRINT INDEX"    //"��ӡȡ�˺�"
#define SysFlags40              "HEART BEAT"    //ccr2015-08-03"�����������Heart beat"
#define SysFlags41              "PreFix1:"      //ccr2016-08-02
#define SysFlags42              "PreFix2:"      //ccr2016-08-02

//----------Length<=9------------------
#define GrapType1               "MARCA"// " �̵�ͼ��"
#define GrapType2               "PREMIO"//" �н�ͼ��"
#define GrapType3               "LOGO-PIE"//" Ʊβͼ��"
#define GrapType4               "IMPRIME ?"// "��ӡ����?"

#define GrapSet1                "NO#:"//"���:"
#define GrapSet2                "FOTO REF."//"ͼ����:"
#define GrapSet3                "INICIO"//"��ʼ����:"
#define GrapSet4                "FECHA-FIN:"//"��������:"

  /////======================CHN msg========================//////

#define CurrentMode1            "ABIERTO"//"Ӫҵ"
#define CurrentMode2            "LEE CUENTA"//"����"
#define CurrentMode3            "QUITA CUENTA"//"����"
#define CurrentMode4            "CONFIG."//"����"
#define CurrentMode5            "GERENTE"//"����"

//----------Length<=14------------------
#define SetupMode1              "FUNCION GRAL."//"�ۺϹ���"
#define SetupMode2              "GESTION-ART."//"��Ʒ����"
#define SetupKeyboard           "KEYBOARD"      //DEFKEYBOARD  //
#define msgCOMMHOST             "COMM-HOST"      // �����Ҫ???ZWQ
#define SetupMode3              "DEVICE SET"// "ͨѶ������"
#define SetupMode4              "CONFIG.VENTA"//"���۹�������"
#define SetupMode5              "ACCOUNT"//"IC������"
#define SetupMode6              "CABEZA-PIE"//"ƱͷƱβ"
#define SetupMode7              "GESTION-DOC"//"�������"
#define msgDISCOUNT             "DISCOUNT"      //MENUDISC //
#define SetupMode8              "CONFIGURA"//"��������"
#define SetupMode9              "CAJERO-CLAVE"//"����Ա������"
#define SetupMode10             "PROBAR CAJA"//"�տ������"

#define SysSettings1            "CONFIG.SISTEMA"//"ϵͳ��������"
#define SysSettings2            "CONFIG.FECHA"// "��������"
#define SysSettings3            "CONFIG.HORA"//"����ʱ��"
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define msgSETEJOURNAL          "CONFIG.EJ"      //SETEJOURNAL //EJOURNAL
#endif

#define SysSettings4            "CONFIG.TECLADO"//  "���ü���"
#define MESSKEYMACRO            "KEYB. MACRO" // "���̺�"
#define MESSKEYTYPE             "KEYBOARD TYPE"             // "����ģʽ"
#define SysSettings5            "TECLADOCOMIDA"// "���ò�������"
#define SysSettings6            "TECLADOSUPERM"//"���ó��м���"
#define SysSettings7            "EXP/IMP DATOS"  //SETEXPORT//  "���ݵ���/����"
#define SysSettings8            "GPRS FUNCTION"          //"GPRSͨ��"  //SETGPRS //ccr2014-11-11 NEWSETUP

#define SetupCaption1           "GRUPO"//"����"
#define SetupCaption2           "DEPT"//"����"
#define SetupCaption3           "ARTICULO"//"��Ʒ"
#define SetupCaption4           "IMPRIME ART.#"//"��ӡ��Ʒ�嵥"
#define msgSETTEST              "TEST ECR"//"ϵͳ����"            //SETTEST
#define msgSETCLEARPLU          "CLEAR PLU"//"�����Ʒ"        //SETCLEARPLU
#define msgSETPLULIST           "PRINT PLU"//"��ӡ��Ʒ�嵥"      //SETPLULIST
#define msgSETTSTVER	        "PRINT VERSION"//"��ӡ�汾"      //SETTSTVER
#define msgSETCONFIGPLU         "FORM PLU"//"���õ�Ʒ"          //SETCONFIGPLU
#define msgSETCONFIGDEPT        "FORM DEPT" //���ò���         //SETCONFIGDEPT
#define msgSETINSTALL           "INSTAL/BACKUP"//"��װ/����"        //SETINSTALL
#define msgSETPRINTFAT          "PRINT MAT"//"��ӡ�ļ������"   //SETPRINTFAT

#define SetupCaption5           "COMPUTER"//"ͨѶ��1"
#define SetupCaption6           "BARCODE"//"ͨѶ��2"
#define SetupCaption7           "E-BALANCE"//"ͨѶ��3"
//#define SetupCaption8           "INTERFAZ 4"//"ͨѶ��4"
#define SetupCaption9           "NETWORK"// "��������"

#if defined(CASE_QRCODE)
#define InputQRCode           "QRCODE"  //MsgQRCODE
#endif

#define GPRSServerIP			"SERVIDOR IP"//"������IP"
#define GPRSServerPort		    "INTERFAZ"//"�˿ں�"

#if (defined(CASE_GPRS))
#define GPRSAPNName        "APN"           //GPRSAPNNAME
#define GPRSUserName        "User Name"           //GPRSUSERNAME
#define GPRSPassword        "Password"           //GPRSPASSWORD

#define GPRSSendMESS            "Check GPRS" //ccr2014-11-11
#define GPRSSetMode        "Set Sent Mode"    //gprsSETMODE //ccr2014-11-11 NEWSETUP-step2
#define GPRSSendECRLogAll   "Send All LOG"    //gprsSendECRLogAll //ccr2014-11-11 NEWSETUP-step2

#define GPRSDownloadPLU     "Update PLU"    //gprsDownloadPLU //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadDEPT    "Update DEPT"    //gprsDownloadDEPT //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadCLERK   "Update CLERK"    //gprsDownloadCLERK //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadHEAD    "Update HEAD"       //gprsDownloadHEAD //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadTRAIL   "Update TRAIL"      //gprsDownloadTRAIL //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadALL     "Update ALL"      //gprsDownloadALL //ccr2016-08-18
#define GPRSRestart         "RESET GPRS UNIT"      //gprsRestart //ccr2016-08-26
#endif

#define SetupCaption10          "PRINT DOC"//"Ʊ�ݴ�ӡ"
#define SetupCaption11          "PRINT.COCINA"//"������ӡ"
#define SetupEXTPrinter         "EXTERNAL PRINT"    //SETEXTPRINTER

#define SetupCaption12          "OFERTA"//"�Żݼ�"
#define SetupCaption13          "CONFIG.PREMIO"//"�н�����"
#define SetupCaption14          "DESCUENTO"//"�ۿ�"
#define SetupCaption15          "CAJA +/- �"//"�������"
#define SetupCaption16          "REVISAR"//"��������"
#define SetupCaption17          "PAGO FORMA "//"���ʽ"
#define SetupCaption18          "DIVISA"//"���"
#define SetupCaption19          "CAJA"// "Ǯ��"
#define SetupCaption20          "IMPUESTO%"//"˰��"

#define SetupCaption21          "SET.ACCOUNT"//"IC������"
#define SetAddNewECRVIP         "ADD ACCOUNT"
#define SetPrintECRVIP          "PRINT ACCOUNT"
#define SetCleanALLVIP          "CLEAN ACCOUNT"

#define SetupCaption22          "PERDER.IC"//"IC����ʧ"
#define SetupCaption23          "PRINT IC"//"��ӡ����Ϣ"

#define SetupCaption24          "CABEZA-TIC"//"�վ�Ʊͷ"
#define SetupCaption25          "PIE-TIC"//"�վ�Ʊβ"
#define SetupCaption26          "CABEZA-DOC"// "Ʊ��Ʊͷ"
#define SetupCaption27          "PIE FOTO  "//"ƱβͼƬ"
#define SetupCaption28          "IMPRIME FOTO"//"��ӡͼƬ"

#define SetupCaption29          "CONFIG.DOC"// "���ñ�������"
#define SetupCaption30          "DOC MODULO"//"����Ԫ"
#define SetupCaption31          "CONFIG.HORA"// "����ʱ������"
#define SetupCaption32          "QUITA TODODOC"//"���屨��"
#define SetupCaption33          "IMPRIME C/C"//"��ӡ��ˮ��"

#define SetupCaption34          " MESA"//"��̨"
#define SetupCaption35          "ALIMENTACION"//"��������"
#define SetupCaption36          "MENU"//"�˵�˵��"
#define SetupCaption37          "FIRMAR CUENTA"//"ǩ��"
#define SetupCaption38          "CAJERO"//"�տ�Ա"
#define SetupCaption39          "VENDEDOR"//"ӪҵԱ"
#define SetupCaption40          "CONFIG.CLAVE"//"���õ�����"
#define SetupCaption41          "CLAVE-GERENTE"//"��������"
#define SetupCaption42          "CLAVE-LEER"//"ֻ����������"
#define SetupCaption43          "CLAVE-QUITA"//"���ʱ�������"

#define SetupCaption44          "MEMORIA TEST"//"�ڴ����"
#define SetupCaption45          "DISPLAY TEST"//"��ʾ����"
#define SetupCaption451         "CUSTOMER"      // ���Բ���
#define SetupCaption46          "IMPRESORATEST"//"��ӡ����"
#define SetupTestRAM           "CHECK RAM"        //SETTSTMEM	       //RAM����
#define SetupCaption47          "TIEMPO TEST"//"ʱ�Ӳ���"
#define SetupCaption48          "SILBATO TEST"//"����������"
#define SetupCaption49          "CAJA TEST"// "Ǯ�����"
#define SetupCaption50          "TECLADO TEST"//"���̲���"
#define SetupCaption51          "SERIE TEST"// "���ڲ���"
#define SetupCaption52          "AUTO-TEST"// "�Զ�����"
#define SetupCaption53          "REPARTIR DOC"//"�ļ������"

//----------Length<=8------------------
#define msgSETPRNMENU           "PRINT MENU"      //SETPRNMENU   //
#define OperationN1             "GRABAR#"//"��¼#"
#define OperationN2             "GRABAR?"//"��¼?"
#define OperationN3             "TOTAL"// "�ܼ�"
#define OperationN4             "VUELTO"//ccr2016-08-08"EN CAMBIO"//"ת��"
#define OperationN5             "SUBTOTAL"//"С��"
#define OperationN6             "CAJA + �"// "����"
#define OperationN7             "CAJA - �"//"���"
#define OperationN8             "RESUMEN"//  "����"
#define OperationN9             "ANADIR"// "����"
#define OperationN10            "PEDI.ABIERTO"// "�ҵ�"  too long for display
#define OperationN11            "CANCELAR"// "ȡ��"

#define OperationN12            "CONTRASENA"//"����"
#define OperationN13            "CONFIR.CLA"// "����ȷ��"
#define OperationN14            "PVP:"// "����:"
#define OperationN15            "IMPORTE:"//"���:"
#define OperationN16            "SUPERMERCADO"//"���а�"
#define OperationN17            "RESTRAURANTE"//"������"
#define OperationN18            "TEST"//  "����"


#define CaptionN1               "TOTAL"//ccr2016-08-08"DEBIDO"// "Ӧ��"
#define CaptionN2               "IMPORTE BRUTO"//"����"
#define CaptionN3               "PVP"//"�۸�"
#define CaptionN4               "CANT-PEDIDO"//"������"
#define CaptionN5               "CANTIDAD"//"����"
#define CaptionN6               "IMPORTE"//"���"
#define CaptionN7               "ENTREGADO"//ccr2016-08-08"COBRAR"// "��ȡ"
#define CaptionN8               "VUELTO"//ccr2016-08-08"EN CAMBIO"//"����"
#define CaptionN9               "DIA"//"��"
#define CaptionN10              "SEMANA"// "��"
#define CaptionN11              "MES"// "��"
#define CaptionN12              "ANO"// "��"
#define CaptionN13              "STANDARD"//"��׼"
#define CaptionN14              "VENDEDOR"//"�տ�Ա"
#define CaptionN15              " HORA "//"   ʱ"
#define CaptionN16              " DIA "// "   ��"
#define CaptionN17              " MES "//"   ��"
#define CaptionN18              "DEVOLUCION"// "�˻�"
#define CaptionN19              "COSTE"// "�ɱ�"
#define CaptionN20              "MESA NO"//"����#"
#define CaptionN21              "CHEQUE NO"//"֧Ʊ��#"
#define CaptionN22              "    #:    "//   "����:"
#define CaptionN23              "VENTA+I.G.V"// "��˰����"
#define CaptionN24              "I.G.V"//"˰��"
#define CaptionN25              "PAGINA"// "ҳ��"
#define CaptionN26              "NO#:"//"����:"
#define CaptionN27              "APARCA �"//"����"
#define CaptionN28              "ABRIR MESA"//"��̨"
#define CaptionN29              "Z"//ccr2016-08-09"CANT-QUITACUENTA"//"���ʼ���"
#define CaptionN30              "BORRAR"// "���"
#define CaptionN31              "S-RESUMEN"//"S-����"
#if HOR_REPORT==1
#define CaptionN32              "BRUTO"//"BENEFICIO BRUTO"// "ë��"
#else
#define CaptionN32              "BENEFICIO BRUTO"// "ë��"
#endif
#define CaptionN33              "ALMACON +/-"//"�������"
#define CaptionN331             "STOCK DECREASED"  // "�������",
#define CaptionN34              "CUENTA-MESA ANTERIOR"// "ԭ����:"
#define CaptionN35              "T.CREDITO"// "���ÿ�#"
#define CaptionN36              "CUENTA-MESA NUEVA:"// "������:"
#define CaptionN37              "CLIENTE NO"// "����"
#define CaptionN38              "CAMBIA ARTICULO"// "����"


#define CaptionN39              "ANADIR?"//"����?"
#define CaptionN40              "BORRAR?"// "ɾ��?"
#define CaptionN41              "DESCUENT1"//"�ۿ��� 1"
#define CaptionN42              "DESCUENT2"//"�ۿ��� 2"
#define CaptionN43              "VENTA �"//  "���۶�"
#define CaptionN44              "DTO MASIVO"//  "����Ż�"
#define CaptionN45              "STOCK CANT"//"�������"
#define CaptionN46              "OFERTA"//"�ؼ��Ż�"
#define CaptionN47              "OPCION:"//    "ѡ��:"
#define CaptionN48              "FIJO"// "�̶�"
#define CaptionN49              "FLEXI."//"����"
#define CaptionN50              "FIJO/FLEX."// "��/��"

#define CaptionN51              "MESA TEMPORALFIN "//"��̨�ݽ�"
#define CaptionN52              " +MESA"//"��̨����"
#define CaptionN53              "CERRA TEMPORAL"// "�ݽ�"
#define CaptionN54              "CONFIRMAPAGO"//"ȷ�Ͻ���"
#define CaptionN55              "IMPRIME MESA"//"��ӡ��̨"
#define CaptionN56              "IMPRIMCUENTA"// "��ӡ�ʵ�"
#define CaptionN57              "CANCELA CONFIRMA"//"ȡ��ȷ��"
#define CaptionN58              "DIVIDECUENTA"//"����"
#define CaptionN59              "TRANS-CUENTA"// "ת��"
#define CaptionN60              "ALTERAR OPER"//"������̨"
#define CaptionN61              "CLIENTE NO"// "�˿�����"

#define CaptionN62              "CONFIG.PREMIO:"// "�н��趨:"
#define CaptionN63              "PUNTOS:"//"���ѼƵ�:"

#define CaptionN64              "ALTERA PVP"// "�ı䵥Ʒ�۸�"
#define CaptionN65              "COCINA#"//"������ӡ����"
#define CaptionN66              " +STOCK"//  "���ӿ��"
#define CaptionN67              "-STOCK"//  "���ٿ��"
#define CaptionN68              "TECLAR"// "����"
#define CaptionN69              "TOTAL"//ccr2016-08-08"DEBIDO"// "����"


#define CaptionE1               "ERROR RS232"//  "RS232��"
#define CaptionE2               "CORRECTO RS232"//"RS232��ȷ"
#define CaptionE3               "RTC ERROR!"//"RTC ��!"
#define CaptionE4               "CTC ERROR!"//  "CTC ��!"
#define CaptionE5               "FPROM ERROR!"//"FPROM��!"
#define CaptionE6               "INICIAR..."// "��ʼ��..."
#define CaptionE7               "YA INICIADO."// "��ʼ������."
#define CaptionE8               "ERROR-"//"����-"

#define CaptionE9               "CLAVE ERROR!"// "����� ��"
#define CaptionE10              "GRABADO CLAVE"//"�����ѱ���"
#define CaptionE11              "CAJERO:"//"�տ�Ա:"
#define CaptionE12              "VENDEDOR:"// "ӪҵԱ:"
#define CaptionE13              "CAJA NO:"//"�տ����:"
#define CaptionE14              "LOCAL:"// "����:"
#define CaptionE15              "CONFIRMAR?"//"ȷ��?"
#define CaptionE16              "TERMINADO"//"���"

#define CaptionE17              "VERSION ACTUAL:"//"���а汾:"
#define CaptionE18              "PUNTOS ACTUAL"//"�������ѵ�"
#define CaptionE19              "ARTICULO NUEVO:"//"������Ʒ:"
#define CaptionE20              "BORRA ARTICULO:"// "ɾ����Ʒ:"
#define CaptionE21              "COMENZAR TEST>>" //"��ʼ���>>"
#define CaptionE22              "<<YA TEST"//  "<<������"
#define CaptionE23              "STOCK"//"���"
#define CaptionE24              "ARREGLADO RESUMEN!"// "������ȫ��!"
#define CaptionE25              "NO APAQUE EN ACTUALIZAR"//"���³�������ϵ�"
#define CaptionE26              "FILE OVERFLOW!"// "�ļ��ռ�Խ��"
#define CaptionE27              "DESBORDADO MEMORIA��"// "�ڴ������"
#define CaptionE28              "MEMORIA LLENA"//  "��ˮ�ʴ洢��"
#define CaptionE29              "CAMBIA ROLLO"//"�������ӡֽ"
#define CaptionE30              "MEMORIA EXTERNAL ERR��"// "��չ�ڴ����"

#define CaptionE31              "NOTA:"//"˵������:"

//----------Length<=10------------------
#define CaptionE32              "INVALIDO!"//"��Ч����!"
#define CaptionE33              "FECHA INVALIDO!"//"��Ч����!"
#define CaptionE34              "HORA INVALIDO"//"��Чʱ��!"
#define CaptionE35              "NO TECLAR!"//"��ֹ����!"
#define CaptionE36              "PLU ES VACIO!"// "PLU����Ϊ��!"
#define CaptionE37              "PLU DOC LLENO!"//   "PLU�ļ����!"
#define CaptionE38              "MESA OCUPADA!"// "��̨��ռ��!"
#define CaptionE39              "MESA ABIERTA!"// "��̨�Ѵ�!"
#define CaptionE40              "MESA NO ERROR!"//"��̨�Ų���!"
#define CaptionE41              "TELCA MESA# "// "��������̨��"
#define CaptionE42              "MESA LIBRE"// "û�п�̨"
#define CaptionE43              "CUENTA-MESA LLENA"//"��̨�������"
#define CaptionE44              "NO MODIF.HORA"// "��ֹ�޸�ʱ��"
#define CaptionE45              "EN VENTA!"//"����������!"
#define CaptionE46              "RAM-VENTA LLENA"//"���ۻ�������"
#define CaptionE47              "STOCK ARTICULO"//"��Ʒû���۳�"
#define CaptionE48              "DURANTE COBRO!"// "���ڽ�����!"
#define CaptionE49              "DATOS LARGO"//"�������ݳ���"
#define CaptionE50              "DURANTE PAGO!"//"���ڸ���!"
#define CaptionE51              "CLIENTE LLENO!"//  "�������!"
#define CaptionE52              "FALTA PAGO"//  "û��ȷ�Ͻ���"
#define CaptionE53              "NO CANCELE PAGO"// "��ֹȡ������"
#define CaptionE54              "SIN ESTE COMIDA!"// "�޲���!"
#define CaptionE55              "SIN ESTE C!"//"�޴��տ�Ա!"
#define CaptionE56              "CAMBIADO C"// "�տ�Ա�ı�"
#define CaptionE57              "SIN ESTE DOC!"//"�޴��౨��!"
#define CaptionE58              "FALLO PRINT DOC"// "�����ӡ�ж�"
#define CaptionE59              "OBL.GERENTE"//"�����ھ���"
#define CaptionE60              "NO REPARTICION-CUENTA"//  "���ܷ���ʱ��"
#define CaptionE61              "OBL.NO#!"// "�����������!"
#define CaptionE62              "KEY POS ERROR"//"Կ�׵�λ��"
#define CaptionE63              "SIN AUTORIZACION!"// "δ��Ȩ!"
#define CaptionE64              "RESIGNA C"//"��ָ���տ�Ա"
#define CaptionE65              "RESIGNA VEND"//"��ָ��ӪҵԱ"
#define CaptionE66              "NOCAMIBE PLU-PVP��"//"��ֹPLU��ۣ�"
#define CaptionE67              "CLAVE ERROR!"// "���벻��!"
#define CaptionE68              "COCINA ERR"//"������ӡ����"
#define CaptionE69              "PRINT ERROR"//"Ʊ�ݴ�ӡ����" //ccr2017-08-31
#define CaptionE70              "LEVANTA EJE"// "��ӡѹ��̧��"
#define CaptionE71              "SIN ROLLO!"//"��ӡֽ����!"
#define CaptionE72              "TEMPERATURA ALTA"//"��ӡ�¶�̫��"
#define CaptionE73              "SIN DEFINIR BOTON!"//"����δ����!"
#define CaptionE74              "OBLIGATORIO�"// "����������"
#define CaptionE75              "NO-FORMA-PAGO"//"��ֹ���ָ���"
#define CaptionE76              "SIN ESTE FUNCION"//"�����޴˹���"
#define CaptionE77              "FALTA PULSES.TOTAL!"//"δ��С�Ƽ�!"
#define CaptionE78              "EN GESTION-STOCK"//"���ڹ�����"
#define CaptionE79              "GRABA C/C ERR"//"������ˮ�ʴ�"
#define CaptionE80              "COM-MODEM ERR"//"MODEMͨѶ��"


#define CaptionE81              "MONTA-T ERR!"//"����������!"
#define CaptionE82              "POS BARCODE ERR!"// "POS�����!"
#define CaptionE83              "T.DATOS ERR!"//"�����ݴ�!"
#define CaptionE84              "T.CADUCADA!"//"Ϊ���ڿ�!"
#define CaptionE85              "T.PERDIDA!"// "Ϊ��ʧ��!"
#define CaptionE86              "CLIENTE TIPO ERR!"//"�ͻ�����!"
#define CaptionE87              "T.NUEVA!"//   "Ϊ�¿�!"
#define CaptionE88              "T.INVALIDA!"//"���ǹ��￨!"
#define CaptionE89              "LEE T.ERR!"//"д������!"
#define CaptionE90              "T.NO ERR!"// "���Ų���!"
#define CaptionE91              "NO T.DTO!"//"�����ۿۿ�!"
#define CaptionE92              "NO T.CASH!"//"�����ֽ�!"
#define CaptionE93              "NO T.CREDITO!"//"�������ʿ�!"
#define CaptionE94              "NO USE IC!"//"����IC��!"
#define CaptionE95              "QUITA T.ERR!"// "�忨����!"
#define CaptionE96              "DATOS LLENOS!"//"�������!"
#define CaptionE97              "RECARGA IC ERR!"//"IC��ֵ����!"
#define CaptionE98              "INICIA IC ERR"//"IC��ʼ������"
#define CaptionE99              "NO INICIE IC!"//  "��ֹ��ʼ��!"
#define CaptionE100             "FALTA SALDO!"//"IC����!"
#define CaptionE101             "PAGO ERR CONIC!"//"IC�������!"
#define CaptionE102             "IP DIRECCION ERR!"// "IP��ַ��!"
#define CaptionE103             "NO CHIP CARD!"
#define CaptionE105		        "HAY PEDIDO ABIERTO"//"���йҵ�"

#define CaptionERR105             "BATERIA BAJA!"  // "��ص�����",
#define CaptionERR106             "NO ABRIR STOCK!"	//20070806"û������"//δ�������!
//ccr090715>>>>>>>>>>>>>>>>>>>>>>
#define CaptionERR76			  "INSERTA PEN DRIVE!"	//  "�����U��!"
#define CaptionERR77			  "ABRE DOC ERR!"		//  "���ļ���!"
#define CaptionERR78			  "LEE PENDRIVE ERR!"		//"��U�̳���!"
#define CaptionERR79			  "ESCRIBE DRIVE ERR!"		// "дU�̳���!"
#define CaptionERR80			  "CREA DOC ERR!"		//  "�����ļ���!"
#define CaptionERR81			  "CERRA DOC ERR!"		//  "�ر��ļ���!"
#define CaptionERR82			  "Send LOG 1st"		//
#define CaptionERR83              "GPRS ERROR!"
#define CaptionERR84              "ERROR-SEND!"
#define CaptionERR85              "ERR-RECEIVE"
#define CaptionERR86              "No SERVER!"
#define CaptionERR87              "IP/PORT:NULL"
#define CaptionERR88              "NO SIM CARD"
#define CaptionERR89              "GPRS NOT OK"
#define CaptionERR90              "OUT OF RANGE" //CWXXI90  //
#define CaptionERR91              "NULL ACCOUNT"  //CWXXI91
//ccr2016-10-24 EJ >>>>>>>>>>>>>>>>>>>
#define EJ_CWXXI92  "ERROR DATOS EJ"   	//CWXXI92
#define EJ_CWXXI93  "NO SD TARJETA"        	//CWXXI93
#define EJ_CWXXI94  "ERROR EJ E/W"   	//CWXXI94
#define EJ_CWXXI95  "SIN REGISTR EJ"   	//CWXXI95
#define EJ_CWXXI96  "EJ CASI LLENO"   	//CWXXI96
#define EJ_CWXXI97  "EJ est? lleno"   	//CWXXI97
#define EJ_CWXXI98  "NUEVO EJ"        	//CWXXI98
#define EJ_CWXXI99  "REINICIAR EJ"   	//CWXXI99
#define EJ_CWXXI100 "EJ NO COINCIDE"     	//CWXXI100

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


#define CaptionE104             "ABRE CAJA"//   "��Ǯ��"
#define CaptionE106             "HAY PEDIDO ABIERTO"//"�йҵ�"
#define CaptionE107             "CANT.ARTI.PVP"//   "  ������Ʒ����\n  ����Ʒ�۸�"
#define CaptionE108             "PASA A"    //ZHUANRUDAO

#define MsgPUTOUT               "PO"   	                //PUTOUT
#define MsgRECIEVIN             "RA" 		            //RECIEVIN
#define DownLoad1               ">> LETRA"//  "���������ֿ�"
#define DownLoad2               ">> FOTO"//   "��������ͼ��"

#define OptionN1                " SI"// "��"
#define OptionN2                " NO"//"��"
#define OptionN3                "NOMBRE:"//"����:"
#define OptionN4                "DEPT:"//   "����:"
#define OptionN5                "GRUPO:"//  "����:"
#define OptionN6                "IMPRIMIR:"// "��ӡ:"
#define OptionN7                "OPCION:"// "ѡ��:"
#define OptionN8                "CONEXION:"//"����:"
#define OptionN9                "IMPUESTO%:"// "˰��:"
#define OptionN10               "LOCACION NO:"//  "λ�ñ��:"

#define OptionN11               "PRECIO 1:"//"�۸�1:"
#define OptionN12               "PRECIO 2:"// "�۸�2:"
#define OptionN13               "PRECIO 3:"// "�۸�3:"
#define OptionN14               "PRECIO 4:"//  "�۸�4:"

#define OptionN15               "COSTE:"// "����:"
#define OptionN16               "DESCUENTO(%):"// "�ۿ���(%):"
#define OptionN17               "MAXIMO:"// "���ֵ:"
#define OptionN18               "DESCUENTO:"//"�ۿ���:"
#define OptionN19               "MAXIMO:"//"���ֵ:"
#define OptionN20               "IMPUESTO%:"// "˰��:"
#define OptionN21               "COSTE:"//"�����:"
#define OptionN22               "PRECIO:"//"������:"
#define OptionN23               "ESTADO:"//"״̬:"
#define OptionN24               "CAJA:"// "Ǯ��:"
#define MSGOTD                  "OTD"                    //OTDMSG
#define OptionN25               "IMPRIME COCINA:"// "������ӡ:"
#define MSGPERIOD               "PERIOD"                      //PERMSG
#define MSGPOINTER              "POINTER"                     //POIMSG

#define OptionN26               "PERIODO:"  // "����:",
#define OptionN27               "CONEXION:"  // "����:",
#define OptionN28               "FUNCION "  // "���빦����:",
#define OptionN29               "PULSE TO:"  // "�����ܼ�:",
#define OptionN30               "TIPO:"  // "����:",
#define OptionN31               "INICIO:"  // "��ʼ����:",
#define OptionN32               "FECHA-FIN:"  // "��������:",
#define OptionN33               "HORA-INICIO:"  // "��ʼʱ��:",
#define OptionN34               "HORA-FIN:"  // "����ʱ��:",
#define OptionN35               "SEMANA:"  // "����:",
#define OptionN36               "DESCUENTO :"  // "�ۿ�:",
#define OptionN37               "MASIVA:"  // "�������:",
#define OptionN38               "PVP:"  // "����:",
#define OptionN39               "OFERTA:"  // "�Żݼ�:",
#define OptionN40               "PROTOCOL:"  // "ͨѶЭ��:",
#define OptionN41               "TELIFONO NO#:"  // "�绰����:",
#define OptionN42               "CONTRASENA:"  // "����:",
#define OptionN43               "FRECUENCIA:"  // "Ƶ��:",
#define OptionN44               "MIN.�:"  // "��С���:",
#define OptionN45               "INTERFAZ :"  // "ͨѶ��:",
#define OptionN46               "PUNTOS �:"  // "�Ƶ���:",
#define OptionN47               "FOTO NO:"  // "ͼ�����:",
#define OptionN48               "HORA"  // "ʱ��:",
#define OptionN49               "FECHA"  // "����:",
#define OptionN50               "PRINTER"
#define OptionN51               "TYPE:"      //DZCHXHAO//"���ͺ�",

//#define WelcomeN1                "���������Ŵ����\n�Ŵ�MACRO�տ��!"
#define WelcomeN1                "CAJA REGISTRADORA!"//"�Ŵ�MACRO�տ��!"
#define WelcomeN2                " DO THE BEST! \nMade by EUTRON"

#define MessagesN1                "CAJA BLOQUEADA"  // "  �տ��������",
#define MessagesN2                "ENCIENDE MODO"  // "������ʽ��������",
#define MessagesN3                "FACUTRA             "  // "��ʽ��Ʊ",	//XSHFPIAO
#define MessagesN4                "COCINA#"  // "������ӡ��#",	//CHFDYJHAO
#define MessagesN5                "*** IMPRESORA DE COCINA ***"  // "*** ��ѵ״̬ ***",
#define MessagesN6                "***** CARGAR BATERIA *****"  // "***** �ӵ� *****",
#define MessagesN7                "***PAGAR EN PARTE ***"  // "*** �ֿ����� ***",
#define MessagesN8                "*** COPIAR DOCUMENTO ***"  // "*** �����վ� ***",
#define MessagesN9                "*** ALTERAR PRECIO***"  // "*** ��Ʒ��� ***",
#define MessagesN10               "*** MOVIMIENTO DE STOCK ***"  // "*** ������� ***",
#define MessagesN101              "**INVENTORY- **"  // "*** ���ٿ�� ***",
#define MessagesN11               "***** CANCELAR*****"  // "***** ȡ�� *****",
#define MessagesN12               "**  INICIAR PROGRAMA **"  // "** �����ʼ�� **",
#define MessagesN13               "<>"
#define MessagesN14               "TOTAL"  ////KPTOTAL
//                                 01234567890123456789012345678901
#define TitleN1	                  "NOMBRE  CANTIDAD.   PVP. IMPORTE"  //--Ʒ��   ����   ����   ���
//                                 01234567890123456789012345678901345
#define TitleN3	                  "NOMBRE      CANTIDAD.  IMPORTE"  //--Ʒ��   ����   ����   ���
#define TitleN4	                  "NAME                      AMOUNT "  //

#define CaptionM1                 "ENERO"  // "һ��",
#define CaptionM2                 "FEBRERO"  // "����",
#define CaptionM3                 "MARZO"  //  "����",
#define CaptionM4                 "ABRIL"  //  "����",
#define CaptionM5                 "MAYO"  // "����",
#define CaptionM6                 "JUNIO"  // "����",
#define CaptionM7                 "JULIO"  // "����",
#define CaptionM8                 "AGOSTO"  // "����",
#define CaptionM9                 "SEPTIEMBRE"  // "����",
#define CaptionM10                "OCTUBRE"  // "ʮ��",
#define CaptionM11                "NOVIEMBRE"  // "ʮһ��",
#define CaptionM12                "DICIEMBRE"  // "ʮ����",

#define CaptionW1                 "LUNES "  // "����һ",			//LUNES
#define CaptionW2                 "MARTES"  // "���ڶ�",			//MARTES
#define CaptionW3                 "MI."  // "������",			//MIERCOLES
#define CaptionW4                 "JUEVES"  // "������",			//JUEVES
#define CaptionW5                 "VIERNES"  // "������",			//VIERNES
#define CaptionW6                 "SABADO"  // "������",			//SABADO
#define CaptionW7                 "DOMINGO"  // "������",			//DOMINGO

#define ClueN1                    "TECLAR CONFIRMA"  // "��ȷ�ϼ�...",

  //Option for KP
#define OptionS1                  "PRINT SUM:"  // "��ӡ�ܶ�:",
#define OptionS2                  "I.M.PLATO "  // "����ͬ��ӡ",
#define OptionS3                  "I.D.PLATO "  // "�˲�ͬ��ӡ",
  //Option for dept
#define OptionS4                  "PVP 0"  // "��ֹ��۸�",
#define OptionS5                  "PRINT.SEP."  // "��ӡ�ָ���",
#define OptionS6                  "ITEM VENTA:"  // "��������:",
#define OptionS7                  "DTO ITEM 1:"  // "�ۿ��� 1:",
#define OptionS8                  "DTO ITEM 2:"  // "�ۿ��� 2:",
  //Options for tend
#define OptionS9                  "ABRE CAJA:"  // "��Ǯ��:",
#define OptionS10                 "TECLA VAL:"  // "������:",
#define OptionS11                 "NO PULSE:"  // "��ֹ����:",
#define OptionS12                 "TECLA NO#:"  // "�������:",
#define OptionS13                 "NO CAMBIO"  // "����ΪС��",
  //Options for PoRa
#define OptionS14                 "ABRE CAJA:"  // "��Ǯ��:",
#define OptionS15                 "PAGO FORMA"  // "���ʽ��",
#define OptionS16                 "INGRESO:"  // "������:",
#define OptionS17                 "ENTRADA/SALIDA"  // "���/����",
  //Option for Disc
#define OptionS18                 "PRINT.DTO."  // "��ӡ�ۿ۶�",
#define OptionS19                 "APLICA DTO1:"  // "ʹ���ۿ�1:",
#define OptionS20                 "APLICA DTO2:"  // "ʹ���ۿ�2:",
  //Options for currency
#define OptionS21                 "CAMBIO"  // "����������",
  //Options for Draw
#define OptionS22                 "SIN CENTIMO:"  // "��С����:",
#define OptionS23                 "ABRE CAJA:"  // "��Ǯ��:",
  //Options for Tax
#define OptionS24                 "+ VENTA:"  // "Ӫҵ/��ֵ:",
#define OptionS25                 "PRINT.TASA"  // "��ӡ˰����",
#define OptionS26                 "ES GST "  // "��ӡ0˰��",
#define OptionS27                 "IMPUESTO-GST"  // "ΪGST��˰",
#define OptionS28                 "PRINT.IGV:"  // "��ӡ˰��:",
  //Options for clerk
#define OptionS29                 "NO LIMITE:"  // "ȡ������:",
#define OptionS30                 "ALTERA LMT:"  // "��������:",
#define OptionS31                 "NO PEDIDO:"  // "ȡ������:",
#define OptionS32                 "LIMITE DEV.:"  // "�˻�����:",
#define OptionS33                 "LIMITE-DTO:"  // "%�ۿ�����:",
#define OptionS34                 "LMT.COMIS.:"  // "%�ӳ�����:",
#define OptionS35                 "LIMITE-�"  // "+-�������",
#define OptionS36                 "FORMACION:"  // "��ѵģʽ:",
#define OptionS37                 "INDEX:"    //mPRNINDEX//Ccr "ȡ�˺�:",

#define MESS_ECR_IP         "ECR IP ADDRESS:"
#define MESS_ECR_ID         "ECR ID(0-9,A-F):"

#define EditN1                    "<BARCODE>TECLAR GRABAR\n<CONFIRMA>  ACTUAL GRABAR\n"  //ccr "<��¼��>  �¼�¼\n<ȷ��>  ��ǰ��¼",
#define EditN2                    "<BARCODE> +/- ARTICULO.\n<CONFIRMA> ARTI.\n"  //ccr "<��¼��>��ɾ��Ʒ\n<ȷ��>  ��ǰ��Ʒ\n",
#define EditN3                    "<SALIR>   SALIR"  // "<�˳�>      �˳�",
#define EditN4                    "<CONFIRMA>  CONTINUAR\n"  // "<ȷ��>      ����\n",
#define EditN5                    "ELIGE DOC"  // "��<ѡ��>����",
#define EditN6                    "� COSUMO"  // "���ѽ��",
#define EditN7                    "TECLADO  ->TECLADO    "  //"����     ->��   ",
#define EditN8                    "SOLO GTE."  // "ֻ���ھ�����",
#define EditN9                    "PARA VENTA"  // "����Ӫҵ����",
#define EditN10                   "IMPRIME LETRAS"  // "��ӡ����",
#define EditN11                   "(RESERVAR)"  // "����",
#define EditN12                   "TEST DOC CLAVE"  // "�ļ��������",
#define EditN13                   "DISCAR NUMERO"  // "����",
#define EditN14                   "CONEXON MODEM!"  // "MODEM ����!",
#define EditN15                   "CODE:"  // "����:",
#define EditN16                   "DESCENTO%"  // "%�ۿ�",
#define EditN17                   "COMIS.%"  // "%�ӳ�",
#define EditN18                   "DOC NO#.:"  // "�վݺ�:",
#define EditN19                   "DOC CANTIDAD "  // "�ļ�����"��0
#define EditN20                   "DOC ESPACIO  "  // "�ļ��ռ䣺"?
#define EditN21                   "CALCULA DOC"  // "ͳ���ļ�"2
#define EditN22                   "CALCULAR IMPUESTO"  // ����˰��8
#define EditN23                   "MOVIMIENTO CUENTAE SPACIO"  // "��ˮ�ռ�"
#define EditN24                   "DOC NOMBRE CANTIDAD ESPACIO"  // "�ļ���      ��¼��      �ռ��С"
#define EditN25                   "NOMBRE SERIE TIPO COMUNICACION"  // "��������    ͨ�����   ͨ��Э��"
#define EditN26                   "SUPERIOR L.:"  // '����������',
#define EditN27                   "LIN/PAG:"  // 'ÿҳ����',
#define EditN28                   "PRINT INFO"  // '��ӡ��Ϣ',
#define EditN29                   "EL SEGUINDA DOC:"  // '�ڶ���Ʊ��',
#define EditN30                   "ZONA IZQA:"  // '��߾�',
#define EditN31                   "TICKET TIPO   :"  // 'Ʊ�����',
#define EditN32                   "IMPRESORA OFF"  // "��ӡ����",
#define EditN33                   "IMPRESORA ON"  // "��ӡ����",

  //ChipCard>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define ChipCardN1                "CONTRASENA:"  //I "����:",
#define ChipCardN2                "CONFIRMA CLAVE:"  // "����ȷ��:",
#define ChipCardN3                "POS CODE:"  // "POS����:",
#define ChipCardN4                "CONFIRMA CODE:"  // "����ȷ��:",
#define ChipCardN5                "GRABADO CODE"  // "�����ѱ���",
#define ChipCardN6                "CODE ERROR ��"  // "����� ��",
#define ChipCardN7                "USE IC:"  // "����IC��:",
#define ChipCardN8                "T.DTO:"  // "�ۿۿ�:",
#define ChipCardN9                "T.CASH:"  // "�ֽ�:",
#define ChipCardN10               "T.CREDITO:"  // "���ʿ�:",
#define ChipCardN11               "PRINT IC"  // "��ӡIC��",
#define ChipCardN12               "AUTO-DTO :"  // "�Զ��ۿ�:",
#define ChipCardN13               "PUNTOS:"  // "���ѼƵ�:",
#define ChipCardN14               "USA � :"  // "���ֽ��:",
#define ChipCardN15               "USA PLAZO"  // "������Ч��", //
#define ChipCardN16               "PERDIDA TARJETA"  // "��ʧ����",
#define ChipCardN17               "T.NO:"  // "����:",
#define ChipCardN18               "T.TIPO:"  // "������:",
#define ChipCardN19               "SALDO:"  // "���"
#define ChipCardN20               "T.FIANZA:"  // "��Ѻ��:",
#define ChipCardN21               "CONSUMO:"  // "����:",
#define ChipCardN22               "TOTAL RECARGA:"  // "��ֵ�ܶ�:",
#define ChipCardN23               "CANT DE UTILIZA:"  // "ʹ�ô���:",
#define ChipCardN24               "PVP CATEGORIA:"  // "�۸񼶱�:",
#define ChipCardN25               "PIN CODE:"  // "PIN��:",
#define ChipCardN26               "PROTECCION NIVEL:"  // "��������:",
#define ChipCardN27               "AUTO-PAGO:"  // "�Զ�����:",
#define ChipCardN28               "HORA/CREA.T:"  // "�ƿ�����:",
#define ChipCardN29               "T.PLAZO:"  // "����Ч��:",
#define ChipCardN30               "CLIENTE:"  // "�ͻ�:",
#define ChipCardN31               "INICIAR IC"  // "��ʼ��IC",
#define ChipCardN32               "RECARGA"  // "IC����ֵ",
#define ChipCardN33               "BORRAR IC "  // "���IC��",
#define ChipCardN34               "+/- �?"  // "��ֵ/�˿�?",
#define ChipCardN35               " -/+ PUNTOS?"  // "����/�͵�?",
#define ChipCardN36               "CONFIRMA+ �?"  // "ȷ�ϳ�ֵ?",
#define ChipCardN37               "CONFIRMA- �?"  // "ȷ���˿�?",
#define ChipCardN38               "CONFIRMA + PUNTOS?"  // "ȷ���͵�?",
#define ChipCardN39               "PAGA PREMIO?"  // "�ҽ�ȷ��?",
#define ChipCardN40               "PREMIO POR PUNTO"  // "�Ƶ�ҽ�",
#define ChipCardN41               "DEVOLVE�IC"  // "IC���˿�",
#define ChipCardN42               "PUNTOS-PREMIO IC"  // "IC���ҽ�����",
#define ChipCardN43               "PUNTO-REGALO IC"  // "IC���͵���",
#define ChipCardN44               "ESPERA POR FAVOR......"  // "��ȴ�......",
#define ChipCardN45               "HAY SALDO, DEVULVE � PRIMERO...."  // "�����н��,�����˿�....",
#define ChipCardN46               "SOCIO NO"  // "��Ա��:",
#define ChipCardN47               "SOCIO CONSUMO"  // "�� Ա �� ��"
#define ChipCardN48               "PARA  NUEVO IP, ENCIENDE"  // "Ҫ�����µ�IP,�����¿���.",
#define ChipCardN49               "QUITA DOC?"  //  "ȷ���屨��?",
#define ChipCardN50               "ESPERA IC...."  // "�ȴ�IC��....",
#define ChipCardN51               "DBLHIGH PRINT"  // "���ߴ�ӡ",
//ccr2015-06-15>>>>>>>>>>>>>>>>>>>>>
#define ChipCardN52             "CLEAR"
#define ChipCardN53             "REFUND"
#define ChipCardN54             "PAYMEND"
#define ChipCardN55             "CHARGE"
#define ChipCardN56             "INITIAL"
#define ChipCardN57             "TAKE CASH"
#define ChipCardN58            "ADD POINTS"   //ADDVIPPOINTS
#define ChipCardN59            "DEC POINTS"   //DECVIPPOINTS
#define ChipCardN60            "SUM POINTS"  //VIPPOINTS
//ccr2015-06-15<<<<<<<<<<<<<<<<<<<<<
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MESSEJ_X_STORE      "SALVAR EJ X"//MsgEJ_X_STORE
#define MESSEJ_Z_STORE      "SALVAR EJ Z"//MsgEJ_Z_STORE
#define MESSEJ_TR_STORE     "SALVAR EJ TR"//MsgEJ_TR_STORE
#endif
//ccr2016-02-22>>>>>>>>>>>>>>>>>>>>>
#define MsgMENUXREPORT     "X-REPORT"
#define MsgMENUXEXPORT     "EXPORT(X)"
#define MsgMENUQUICKVIEW   "GRAND TOTAL"
#define MsgMENUXLOGFUNC    "RECEIPT LOG"
#define MsgMENUSENDNEWLOG  "SEND NEW LOG"      //MENUSENDNEWLOG  //��������ˮ����
#define MsgMENUXPASSWORD   "X-PASSWORD"
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MsgMENUXEJOURNAL    "EJ"     //MENUXEJOURNAL   "E Journal"
#endif
//.................................
#define MsgMENUZREPORT     "Z-REPORT"
#define MsgMENUZEXPORT     "EXPORT(Z)"
#define MsgMENUCLEARLOG    "CLEAR LOG"
#define MsgMENUZGRAND      "CLEAR TOTAL"
#define MsgMENUZPASSWORD   "Z-PASSWORD"
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MsgMENUZRESETEJ   "REINICIAR EJ"     //MENUZRESETEJ   "Clear EJ"
#endif
//...................................


#define EPosN1                    "EPOS CLAVE:"  // "ePOS��֤��:",
#define EPosN2                    "WAIT ACCOUNTS"  // "�ȴ���ͨ��"
#define EPosN3                    "ACCOUNTS::"  // "��ͨ����:",
#define EPosN4                    "EPOS BALANCE:"  // "��ͨ�����:",


#define ErrInfoN1                 "DATOS LARGO"  // "ͨѶ���ݹ���"
#define ErrInfoN2                 " ***   FALLO PRINT, OTRAVEZ *** "  // " *** ��ӡ���жϡ����´�ӡ *** "
#define ErrInfoN3                 "Check error!"  // "����У���"

#define PLULIST                  " INFO- ARTICULO"  // "         �� Ʒ �� Ϣ ��"
                                 //1234567890123456789012345678901234567890
#define PLUTITLE1                "NOBRE-ARTICULO          REF"// "��Ʒ����                    ����"
#define PLUTITLE2                "DEPT EN STOCK PVP "

#define DEPTLIST                  "INFO-DEPT  "  // "         �� �� �� Ϣ ��"

//                                "INFO- ARTICULO"  // "         �� Ʒ �� Ϣ ��"
#define DEPTTITLE                 "NO-DEPT  GRUPO  PVP"// �������� ��������  �۸�

#define FisTextN1                  "CONTRIBUYENTE NO#:"  //"��˰�˺�:"
#define FisTextN2                  "CREA IMPUESTODOC "  //"����˰Ʊ      "
#define FisTextN3                  "LICENCIA NO#"  //"��Ȩ����        "
#define FisTextN4                  "ESCRIBIR MAQUINA NO#"  //"д������        "
#define FisTextN5                  "CONFIRMA ESCRITO"  //"д��ȷ��        "
#define FisTextN6                  "IMPRIMIR DATOS  "  //"����ӡ��        "
#define FisTextN7                  "USUARIO NO#"  //"�û�����        "
#define FisTextN8                  "SIN IMPUESTO"  //"��˰״̬        "
#define FisTextN9                  "Z-NUMERAR:        "  //"Z-����:         "
#define FisTextN10                 "CANT VENTA "  //"�ۼ�����        "
#define FisTextN11                 "TOTAL IMPUESTO"  //"�ۼ�˰          "
#define FisTextN12                 "SUM SIN-I.G.V"  //"����˰��        "
#define FisTextN13                 "VENTA TOTAL  "  //"�����۶�        "
#define FisTextN14                 "TOTAL I.G.V"  //"��˰��          "
#define FisTextN15                 "CANT IMPUESTO/DIA"  //"��˰Ʊ��        "
#define FisTextN16                 "CANT DOC"  //"�վ�����        "
#define FisTextN17                 "NUMERO EXPORT:      "  //"�౨���� :      "
#define FisTextN18                 "IMPRIME IMPUESTO NO"  //"    _�� _˰ _ӡ _��     "
#define FisTextN19                 "TERMINADO PROBAR MUESTRA     "  //"    _�� _װ _�� _��     "
#define FisTextN20                 "   _NOT   _FISCAL     "  //"    _��   _��   _˰     "


#define PRTStyleN1                 "NORMAL IMPRIME"  //Normale
#define PRTStyleN2                 " DblHigh"  //Doppia altezza//      "���� DblHigh"
#define PRTStyleN3                 "~D~b~l~W~t~h"  //Raddoppio caratteri//"~��~��~D~b~l~W~t~h"
#define PRTStyleN4                 "D~b~l~H~i~g~h"  //Dopia altezza + Raddoppio caratteri//  "~��~��~D~b~l~H~i~g~h"


#define ComTestN1                  "SERIE 1 X"  //"���� 1 ���Գ���"
#define ComTestN2                  "SERIE 1 v"  //"���� 1 ������ȷ"
#define ComTestN3                  "SERIE 2 X"  //"���� 2 ���Գ���"
#define ComTestN4                  "SERIE 2 v"  //"���� 2 ������ȷ"

#define ComTestN3ERR                "SERIE 3 X"  //"���� 3 ���Գ���"
#define ComTestN3OK                "SERIE 4 v"  //"���� 3 ������ȷ"

#define CurrentTimeN1              "HORA ACTUAL:"  // "��ǰʱ��"


#define InputMode1				"A:" // "A��"
#define InputMode2				"ZONA:" // "����"
#define InputMode3				"ESCRIBIR:" // "ƴ��"
#define InputMode4				"WUBI:" // "�ʣ�"

#define SpecialSymbol1			"->"			//DOWNLOAD//Ccr "��",
#define SpecialSymbol2			"<-"			//UPLOAD//Ccr "��",
#define SpecialSymbol3			"^   v"		// "��  ��",
#define DEPTREPORTTITLE         "DEPT      CANTIDAD      IMPORTE"
                            //  "��������     ��������     ���"
#define PLUREPORTTITLE          "NOMBRE      CANTIDAD   IMPORTE"// "��Ʒ����     ��������       ���"
#define MESS_PRESSKEY   "PRESS ANY KEY..."

#if defined(CASE_QRCODE)
#define InputQRCode           "QRCODE"  //MsgQRCODE
#endif

#define GPRSServerIP			"SERVER IP"//"������IP"
#define GPRSServerPort		    "PORT"//"�˿ں�"

//added by lqw 090802
#if  (defined(CASE_GPRS))
#define GPRSAPNName        "APN"           //GPRSAPNNAME
#define GPRSUserName        "User Name"           //GPRSUSERNAME
#define GPRSPassword        "Password"           //GPRSPASSWORD

#define GPRSSendMESS        "Check GPRS" //ccr2014-11-11 NEWSETUP
#define GPRSSetMode        "Set Sent Mode"    //gprsSETMODE //ccr2014-11-11 NEWSETUP-step2
#define GPRSSendECRLogAll   "Send All LOG"    //gprsSendECRLogAll //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadPLU     "Update PLU"    //gprsDownloadPLU //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadDEPT    "Update DEPT"    //gprsDownloadDEPT //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadCLERK   "Update CLERK"    //gprsDownloadCLERK //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadHEAD    "Update HEAD"       //gprsDownloadHEAD //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadTRAIL   "Update TRAIL"      //gprsDownloadTRAIL //ccr2014-11-11 NEWSETUP-step2
#define GPRSDownloadALL     "Update ALL"      //gprsDownloadALL //ccr2016-08-18
#define GPRSRestart         "RESET GPRS UNIT"      //gprsRestart //ccr2016-08-26

#define GPRSstr1 "Data error!"
#define GPRSstr2 "GPRS OK"
#define GPRSstr3 "GPRS NOT OK"
#define GPRSstr4 "CONFIRM?"
#define GPRSstr5 "IP/PORT:NULL"
#define GPRSstr6 "ERROR:IP/PORT"
#define GPRSstr7 "Waiting GPRS" // "�ջ�"
#define GPRSstr8 "SI"   // "��"
#define GPRSstr9 "NO"    // "fou "
#define GPRSstr10 "ENVIANDO DATOS.."  // "���ݷ�����.. "
#define GPRSstr11 "ENVIADO DATOS.."  // "�����ѷ���.. "
#define GPRSstr28 "ENVIAR CON EXITO.."						// "���ͳɹ�.."
#define GPRSstr31 "CONECTAR ERR"	//						// "����ʧ��"
#define GPRSstr32 "ACCEPTA FALLO"                                           // "����ʧ��"
#define GPRSstr33 "CONFIRMA ERR"			// "����ȷ��ʧ��"
#define GPRSstr34 "ENVIA ERR"							// "����ʧ��"
#define GPRSstr58 "ESTABLECIENDO CONEXION.."		// "���ڽ�������.."
#define GPRSstr59 "PREPARA A CONEXION.."		// " ׼����������.."
#define GPRSstr60 "RESTAURA MODULO.."	// "���ڸ�λģ��.."
#define GPRSstr61 "YA,SALE PORFAVOR.." // "�������,���˳�"
#define GPRSxACK  "WAIT ACK ERROR"
#endif //end defined(CASE_GPRS)
///////////////////////////////////////////////////////////////////
#define InsertUSB		"<<Insert USB"//CHRUSB  ����U�� //

//������Ϣ������Msg[]��
#define usbMAIN1		"COPY TO USB"			//usbDAOCHU	�����տ���ļ� //
#define usbMAIN2		"COPY FROM USB"			//usbDAORU �����տ���ļ� //
#define usbMAIN3		"LOG TO USB"		//usbFLOW ����������ˮ //


#define usbFLOWNEWMESS	    "EXPORT UPDATE"      //1-����������   //
#define usbFLOWALLMESS	    "EXPORT ALL"      //2-����ȫ������
#define usbFLOWDELMESS	    "EXPORT/RESET"    //3-����ȫ�����ݺ����

#define usbALLFile		"ALL FILES"		//usbALL ȫ���ļ� //
#define MESSPRNMENU     "<00>PRINT MENU"//"<00>��ӡ�˵�"
#define MESSSETMENU     " MANUALS LIST"//"         ���ù��ܲ˵���"
#define MESSCLEANLOG    "QUITA MEMORIA?  "//"  �����ˮ��?"
#define MESSCLEANLOGA   "All of LOG\nwill be cleared!"
#define MESSRAMOUT      "NO MAS ESPACIO"//"  �洢�ռ䲻��!"
#define MESSCLEANFILES  "QUITA DOC DATOS?"// "  ����ļ�����?"
#define MESSCONFIGERR   "CAMBIADO DATOS CONFIGURADO\nDATOS CAUSAN ERR!"//"���������Ѹı�,\n�����ļ����ݿ���\n�������۴���!"
#define MESSDELPLU      "SISTEMA CAMBIADO \n      BORRADO ARTICULO!"// "ϵͳ�����б仯,\n     ��Ʒ��ɾ��!"
#define MESSPLUPRINTEND "PLU Printed O.K.\nPress <ENTER>!"

#define REPRN_PWON      "IMPRIME SIN LUZ"//"���������ӡ........."
#define REPRN_PAPERON   "IMPRIME SIN ROLLO"//"ȱֽ������ӡ........."
#define RECALLFLOW      "RESTAURA MEMORIA"//"�ָ�������ˮ��"

/////////////////////////////////////////////////////////////

#define InsertUSB		"<<INSERTA PEN DRIVE>>" //"<<����U��>>"
//ccr090715>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define usbMAIN1		"EXPORTA DOC" //"�����ļ�"
#define usbMAIN2		"IMPORTA DOC" //"�����ļ�"
#define usbMAIN3		"EXP ORIGINAL DOC" //"�������Ӵ��"

#define usbFLOWNEWMESS	"EXP DATOS NUEVOS"//"����������"
#define usbFLOWALLMESS	"EXP TODOS DATOS"//"����ȫ������"
#define usbFLOWDELMESS	"EXP TODO+QUITA"//"����ȫ��+���"

#define usbALLFile		"TODO DOC" //"ȫ���ļ�"
#define RECALLFLOW      "Recall LOG"

#define USBREPNAME      "PROYECTO NOBRE"// "��Ŀ����"

////////  CSV�����ļ�����  /////////////////////////////////////////////
#define DEPTCAP       "REFERENCIA,NOMBRE,GRUPO,OPCION,VENTA\r\n"//  "����,����,��������,��Ӧѡ��,����ѡ��\r\n"
#define PLUCAP        "REFERENCIA,NOMBRE,GRUPO,PRECIO 1,PRECIO 2,PRECIO 3,PRECIO 4, COSTE,COMBINADA VENTA,STOCK\r\n"// "����,����,�����Ż�,��������,�۸�1,�۸�2,�۸�3,�۸�4,����,��������,���\r\n"

#define TAXCAP        "NOMBRE,TASA IMPUESTO,OPCION\r\n"//"����,˰��,ѡ��\r\n"
#define HEADERCAP     "LETRA-CABEZA-DOC"//  "Ʊͷ����\r\n"
#define DISCCAP       "NOMBRE,PRINT OPCION ,OPCION,FIJO DESCUENTO,TASA IMPUESTO,MAXIMO VALOR\r\n"//  "����,��ӡѡ��,ѡ��,�̶��ۿ�,˰��,���ֵ\r\n"

#define SALPERCAP     "NOMBRE, OPCION\r\n"//"����,ѡ��\r\n"
#define SYSTEMCAP     "SISTEMA CONTROL SENAL\r\n"// "ϵͳ���Ʊ�־\r\n"
#define COMMCAP       "NOMBRE,TIPO,COMPANERO CONVENIO,TELEFONO NO#\r\n"//"����,����,ͬѧЭ��,�绰����\r\n"
#define GRAPPRNCAP    "FOTO REF.,INICIO,FECHA  FIN\r\n"// "ͼ����,��ʼ����,��������\r\n"
#define GROUPCAP      "NOMBRE, MAXIMO VALOR\r\n"// "����,������۽��\r\n"
#define ICCARDCAP     "CONFIG.IC SOCIO TARJETA\r\n"//"IC��Ա������\r\n"
#define PROMCAP       "CANT PREMIO,MIN.�,PUNTOS,MIN PUNTO,FOTO NO,NOTA\r\n"// "�н�Ƶ��,��С���,�Ƶ�,��С����,ͼ�����,˵������\r\n"
#define PBFUNCCAP     "NOMBRE,PRINT CONTROL,,OPCION\r\n"// "����,��ӡ����,ѡ��\r\n"
#define CLERKCAP      "NOMBRE,OPCION, CONTRASENA\r\n"//"����,ѡ��,����\r\n"
#define MODICAP       "SABOR INSTRUCCION \r\n"//   "��ζ˵��\r\n"
#define PBTOTALCAP    "REFERENCIA,NOMBRE"//  "����,����\r\n"
#define ZONECAP       "TIEMPO 1,TIEMPO 2,TIEMPO 3,TIEMPO 4,TIEMPO 5,TIEMPO 6,TIEMPO 7,TIEMPO 8,TIEMPO 9,TIEMPO 10,TIEMPO 11,TIEMPO 12\r\n"// "ʱ��1,ʱ��2,ʱ��3,ʱ��4,ʱ��5,ʱ��6,ʱ��7,ʱ��8,ʱ��9,ʱ��10,ʱ��11,ʱ��12\r\n"
#define KEYBOARDCAP   "DEFINE TECLADO\r\n"// "���̶���\r\n"
#define OFFCAP        "NOMBRE,TIPO,INICIO,FECHA FIN,FROM,TO ,DISCOUNT,NUMITES,PVP,PRICEP\r\n"//  "����,����,��ʼ����,��������,��ʼʱ��,����ʱ��,�ۿ�,������,����,�����۸�\r\n"
#define PORACAP       "NOMBRE,PRINT CONTROL,OPCION, CAJA, MAXIMO VALOR\r\n"//"����,��ӡ����,ѡ��,Ǯ��,�����\r\n"

#define TRAILERCAP    "LETRA-PIE-DOC\r\n"//"Ʊβ����\r\n"
#define SLIPHEADCAP   "CABEZA-TIC\r\n"// "�վݴ�ӡ��Ʊͷ\r\n"
#define ICBLOCKCAP    "IC TARJETA  LISTA NEGRA  PARA SOCIO\r\n"// "IC��Ա��������\r\n"

#define EXPORTCSV    "1-CSV,2-BIN:"//"1-CSV,2-BIN:"

#define CSVFLOETITL "PROYECTO NOMBRE, CANTIDAD, IMPORTE,ALBARIN NO,CAJERO,VENDEDOR, FECHA, CAJA, LOCAL,DOC TIP .\r\n"//"��Ŀ����,����,���,�վݺ�,�տ�Ա,ӪҵԱ,����,�տ��,����,��������\r\n"
#define CSVREPTITL  "FECHA,CAJA,LOCAL\r\n"//",����,�տ��,����\r\n"

//new messages>>>>>>>>>>>>>>>>>
#define BUTTONBATLOW "BAJA BATERIA!"
#define CHARGEBATNOW "CARGA BATERIA!"

#define SRAMNOTFOUND "SRAM not found!\nSystem HALT!"

#define INPUTPLUCODE "PLU CODE:"

#define MessageE18   "!!!! FAT(PLU) ERROR !!!!"

#define MESS_TABLEHOLD  "Table    Suspend"

#define MESS_LOGREPET   "Re-Send all LOG!"

#define MESS_PAYALSO   "Confirm Payment?"
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
//...............................................
#define MGADDINV        "INVENTORY+"  //1+SUBTOTAL
#define MGDECINV        "INVENTORY-"  //2+SUBTOTAL
#define MGSETPRICE      "PRICE PLU"  //3+SUBTOTAL

#define MGCLEARIC       "Refund IC"
#define MGINITIC        "Init IC"
#define MGCHARGE        "Charge IC"
#define MGADDPOINT      "Add Point"
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
#define DEVICEPORT1     "Port#1"
#define DEVICEPORT2     "Port#2"
#define DEVICEPORT3     "Port#3"
#define DEVICEPORT4     "Port#4"

//................................................
#define CLOSEPRINTER    "Close PRINTER"
#define CLEARGRANDTOTAL "Cls G.T After Z"
#define CLEANALLECRVIP  "CLEAN ACCOUNT?"//"�����Ա����?"
#define ECRVIPTITLE     "ACCOUNT          AMOUNT   POINTS"
#define CREATEDATE      "CREATE DATE"
//ccr2016-06-06>>>>>>>>>>>INDIA>>>>>>>>>>>>>>>>
#define MsgEDITPLU      "EDIT PLU"
#define MsgEDITDEPT     "EDIT DEPART"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
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
#define MsgKEYDRAW      "OPEN DRAWER"
#define MsgKEYMEMO      "MODIFIER"
#define MsgKEYCLERK     "CLERK*"
#define MsgKEYPLUDIR    "PLU~"
#define MsgKEYLOCK      "MODE KEY"
#define MsgKEYDRAWFUN   "DRAW FUNC*"
#define MsgKEYSALPN     "SALESMAN#"
#define MsgKEYSALP      "SALESMAN"
#define MsgKEYDOT       "'.'"
#define MsgKEYZERO2     "'00'"
#define MsgKEYNUMBER    "0~9"
#define MsgKEYSUSPEND   "HOLD"
#define MsgFUNCLOOK1    "FUNC LOOK1"
#define MsgFUNCLOOK2    "FUNC LOOK2"
#define MsgMODELOCK     "MODE KEY"
#define MsgVIPLOGIN     "ACCOUNT LOGIN"
#define MsgINPUTNUM     "INPUT CODE"
#define MsgCUSTOMER     "CUSTOMER"
#define MsgKEYNULL      "(OTHERS)"

#define MsgRHEADER      "Header*"
#define MsgRTRAILER     "Trail*"
#define MsgKEYBOARD     "Keyboard*"
#define MsgSYSFLAGS     "System*"
#define MsgSETDATE      "Datetime*"

//......................................
#define MsgCONFIRM      "CONFIRM"
#define MsgNET          "NET AMOUNT"  // "����",
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
#define MESSEJMESSAGES      "ACERCA DE EJ"    //MsgEJMESSAGES
#define MESSEJALLEJ         "TODO"
#define MESSEJDATERANGE     "EJ POR FECHA"
#define MESSEJRECEIPT       "EJ DE RECIBO"
#define MESSEJXREPORT       "EJ DE X INFORM"
#define MESSEJZREPORT       "EJ DE Z INFORM"
#define MESSEJCLERK         "EJ DE CAJERO"
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

#define CSV_TITLE       "NOMBRE,CANTIDAD,IMPORTE\r\n"

//ccr2017-01-10>>>>>>>>>>>>>>>>>>>>>>>>>
#define Msg_NOSTOCK     "NO STOCK FIELD"
#define Msg_DISPSTOCK   "DISPLAY/PRINT?"
//ccr2017-01-10<<<<<<<<<<<<<<<<<<<<<<<<<<

#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))//ccr2016-10-25>>>>EJ
#define Msg_RECNUMFR	"#EJ DE"                  //��ʼ�վݺ�	//RECNUMFR
#define Msg_RECNUMTO	"#EJ PARA"                    //�����վݺ�	//RECNUMTO
#define Msg_EJBBIAO		"~E~J ~I~N~F~O~R~M~E"		//EJ ����			//EJBBIAO
#define Msg_EJXINXI		"MENSAJES ACTUALES DE EJ"            //EJ��Ϣ			//EJXINXI
#define Msg_NEWEJXINXI	"EJ DESPU?S INICIALIZADO"            //EJ��Ϣ			//NEWEJXINXI
#define Msg_EJBHAO		"EJ ID"						//EJ���			//EJBHAO
#define Msg_EJLEFT      "EJ IZQUIERDO"        //ʣ��ռ�
#define Msg_SIZEEJ		"EJ TAMA?O"				//SIZEEJ
#define Msg_EJCSHUA		"EJ INICIO"		//EJ��ʼ��		//EJCSHUA
#define Msg_FORMAT      "BORRAR EJ"
#define Msg_FORMATED    "BORRADO"
#define Msg_RECALLEJ    "RECUERDA EJ"
#define Msg_EJNOTEMPTY  "EJ NO VACIO"

#define Msg_PRNEJURNAL  ">>>IMPRESION DE TESTIGO DIARIO<<"
#define Msg_ENTERSETUP  ">>>>IMPRIMIR EN CONFIGURACION<<<"
#define Msg_EJDATEEND   "FECHA ULTIMA EJ"
#define Msg_EJRECORDS   "ULTIMO #EJ"
#define Msg_EJINITIAL   "INICIALIZACION EJ"

#define Msg_ECRDATEltEJ "FECHA EJ ECR"
#endif
#define Msg_MANAGEMENT "MANAGEMENT LIST "
#endif


