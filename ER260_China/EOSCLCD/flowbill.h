#if defined(DEBUGBYPC)
#pragma option -a1

#define FLASH_SIZE (0x200000L) /* 2048K */
#define FLASH_BLOCKS (20)

#define MX29LV160DBTI               1

#if defined(CASE_EJFLASH)//FLASH ���ڱ���EJʱ,��LOG
#define	FLASH_LOG_BLOCKFr	        4
#define	FLASH_LOG_BLOCKS            0		//640Kx16bit=1280KB	 ���ڴ洢����
#define	FLASH_LOG_ADDR	            0x010000L //BlockOffset[15]
#define	FLASH_LOG_SIZE	            (FLASH_LOG_BLOCKS*0x10000L)		//���ڴ洢����
#else
#define	FLASH_LOG_BLOCKFr	        4
#define	FLASH_LOG_BLOCKS            16		//640Kx16bit=1280KB	 ���ڴ洢����
#define	FLASH_LOG_ADDR	            0x10000L //BlockOffset[15]
#define	FLASH_LOG_SIZE	            (FLASH_LOG_BLOCKS*0x10000L)		//���ڴ洢����
#endif

#else
#pragma pack(1)
#endif

#ifndef FLOW_C
#define FLOW_C
//define the flow function No//

/*=============================================*/

//IC����������
#define IC_OP_NOVAT         0
#define IC_OP_CLEAR         1
#define IC_OP_ADD           2
#define IC_OP_SUB           3
#define IC_OP_CHARGE        4
#define IC_OP_INIT          5
#define IC_OP_DECHARGE      6   //ccr2015-05-22
#define IC_OP_ADDPOINT      7   //ccr2016-05-13//�ӵ����
#define IC_OP_DECPOINT      8   //ccr2016-05-13//�������

//---------------------------------------------------------------------------
// The ECR Journal type (FunN)
//---------------------------------------------------------------------------
#define  RESERVERLOG    1		//Reserved
#define	 DEPTLOG		2		//Journal for department
#define	 PLULOG		    3		//Journal for PLU
#define	 ENDLOG		    4		//Journal for end of the receipt
#define	 NOADDLOG		5		//Journal for open draw
#define	 OPERLOG		6       //Journal for new clerk
#define	 TENDLOG		7       //Journal for tend
#define	 LOCKLOG		8		//*Journal for ECR-Mode
#define	 DISCADDLOG	    9       //Journal for %discount
#define	 SUBDISCADDLOG	10      //Journal for %discount after subtotal
#define	 DIRECTLOG		11      //Journal for net discount
#define	 SUBDIRECTLOG	12      //Journal for net discount after subtotal
#define	 REGISLOG		13		//Journal for a new reciept
#define	 SUBTOTALLOG	14		//Journal for subtotal
//ccr2016-10-24 #define	 MESSAGELOG	    15		//*Journal for Message input
#define	 SLIPENDLOG	    16		//*Journal for the end of SLIP receipt
#define	 INSERTICLOG	17		//*Journal for insert IC card
#define	 REFRESHICLOG	18		//*Journal for update IC card
#define	 PRICELISTLOG	19		//*Journal for new price
#define  ECRNOLOG       20      //*Journal for ECR-NUMBER
#define  TVOIDLOG		21		//*Journal for cancel a receipt
#define	 PBCLOSELOG		22		//*Journal for table
#define  PBOPENLOG		23		//Journal for open a table
#define	 TRTABLELOG		24		//Journal for transfer table
#define  PORALOG		25      //Journal for Po & Ra
#define  NETIDLOG		26      //ccr2014-12-26 Net ID
#define  TAXLOG		    27      //ccr2014-12-29 TAX Log

#if defined(CASE_INDIA)//ccr2016-06-03>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define  EDITPLULOG     28        //��¼�޸�PLU������־
#define  EDITDEPTLOG    29     //��¼�޸Ĳ���������־
#define  LOGTYPEMAX  	29      //LOGTYPEMAX<=31 must
#else
#define  LOGTYPEMAX  	27      //LOGTYPEMAX<=31 must
#endif//ccr2016-06-03<<<<<<<<<<<<<<<<<<<


#define TENDLOGMAX		8		//��ˮ��¼�У�ÿһ�ʽ����������8�θ��ʽ //
#define SERNUM	    1

#define SHEETDEPT	0
#define SHEETPLU	(SHEETDEPT+1)
#define SHEETREC    (SHEETPLU+1)
#define SHEETDISC   (SHEETREC+1)
#define SHEETOPER   (SHEETDISC+1)
#define SHEETSALPER (SHEETOPER+1)
#define SHEETLOG    (SHEETSALPER+1)
#define SHEETPBLOG  (SHEETLOG+1)

#define LOGALARMON	1024     // ��ʣ��ռ����ڴ�ֵ������ //
#define RECEIPTLEN      3
//The definitions for ECR-Journal. The data type for FQty and  FAmt is BCD
//If Bit7 of FunN is set(1), the FAmt is a Negative
//If Bit6 of FunN is set(1), the FAmt is the value of canceled and then must reverse it's Bit7

struct CDC_DPT							//dept record
{
	BYTE FunN;							//DEPTLOG
	WORD DeptN;							// department number
	BYTE FQty[4];						// translate quantity.BCD
	BYTE FAmt[5];						// translate value,BCD
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_ART							//Plu record
{
	BYTE FunN;							//PLULOG
	BYTE ArtN[7];						// Plu number  (BCD)
	WORD DeptN;							// dept number
	BYTE FQty[4];						// translate quantity (BCD)
	BYTE FAmt[5];						// translate value (BCD)
	WORD OffNum;						// offset number
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_TAX							//TAX record
{
	BYTE FunN;							//TAXLOG
	BYTE TaxID;							// TAX index
	BYTE FAmt[5];						// Amount for TAX,BCD
    BYTE FRate[3];						// Rate for TAX,BCD,From 0.00% to 9999.00%
    BYTE FTax[5];						// TAXAmount,BCD,FTax=FAmt*FRate
};

struct CDC_END							//translat end record
{
	BYTE FunN;							//ENDLOG
	BYTE ReceiptNum[RECEIPTLEN];			// receipt number (BCD)
	BYTE FAmt[6];						//	Amount of receipt(BCD)
	BYTE FYear;
	BYTE FMonth;						 //
	BYTE FDay;							 // date
	BYTE FHour;
	BYTE FMinute;
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_NOADD						//no added record
{
	BYTE FunN;							//NOADDLOG
	BYTE Num[5];						// input number(BCD)
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_OPER							//operator record
{
	BYTE FunN;							//OPERLOG
	BYTE OperN;							// operator number
//	BYTE Reserve[SERNUM];				// reserve
};
struct GIVEN_DATA
{
	BYTE FTType;						// type of tend
	BYTE FAmt[5];                       // amount  (BCD)
};
struct CDC_GIVEN						//currency record
{
	BYTE FunN;							//TENDLOG
	BYTE Counter;
	struct GIVEN_DATA GivenData[TENDLOGMAX];
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_LOCK				   			//mode_lock record
{
	BYTE FunN;							//LOCKLOG
	BYTE NoModeLock;				   		// mode number
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_DISCADD						//discount and add record
{
	BYTE FunN;							//DISCADDLOG
	BYTE Percent[2];					// percent (BCD)
	BYTE FAmt[5];                       //(BCD)
	BYTE ArtN[7];						// (BCD)
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_SUBDISCADD					//subtotal discount and add record
{
	BYTE FunN;							//SUBDISCADDLOG
	BYTE Percent[2];					// percent(BCD)
	BYTE FAmt[5];                       //(BCD)
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_DIRECT						//direct sum discount record
{
	BYTE FunN;							//DIRECTLOG
	BYTE FAmt[5];                       //(BCD)
	BYTE ArtN[7];                       //(BCD)
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_SUBDIRECT					//subtotal sum discount record
{
	BYTE FunN;							//SUBDIRECTLOG
	BYTE FAmt[5];                       //(BCD)
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_REGIS						//start register record
{
	BYTE FunN;							//REGISLOG
	WORD EcrNumber;						// customer number
	BYTE OperNo;						// operator number
	BYTE SalesPer;						// SalesPerson number
	BYTE ReceiptNum[RECEIPTLEN];	        // receipt number(BCD)
	BYTE FYear;
	BYTE FMonth;						 //
	BYTE FDay;							 // date
	BYTE FHour;
	BYTE FMinute;
	BYTE FSecond;				// reserve
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_SUBTOTAL						//subtotal record
{
	BYTE FunN;							//SUBTOTALLOG
	BYTE ReceiptNum[RECEIPTLEN];	 // receipt number (BCD)
	BYTE FAmt[5];
	BYTE FYear;
	BYTE FMonth;						 //
	BYTE FDay;							 // date
	BYTE FHour;
	BYTE FMinute;
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_MESSAGE					//
{
	BYTE FunN;							//MESSAGELOG
	BYTE TypeM;							// Message type
	BYTE Message[32+1];					// Message
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_SLIPEnd						//
{
	BYTE FunN;							//SLIPENDLOG
	BYTE FileT;							// file type
	BYTE FileNo[3];
	BYTE InvoiceNo[2];					// invoice number
	BYTE FAmt[5];						// fair amount
	BYTE FYear;
	BYTE FMonth;						 //
	BYTE FDay;							 // date
	BYTE FHour;
	BYTE FMinute;
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_EnterIC						//record of enter ic
{
	BYTE FunN;							//INSERTICLOG
	ULONG Serialum;
	BYTE ICType;
	BYTE ICFlag;
	BYTE FYear;
	BYTE FMonth;						 //
	BYTE FDay;							 // date
	BYTE Custname[10];
	BYTE FTime[2];
	BYTE Discount[2];				//(BCD)
	BYTE Value[4];					//(BCD)
	BYTE Point[4];					//(BCD)
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_REFRESHIC					//record of refresh IC
{//40Bytes
	BYTE FunN;							//REFRESHICLOG
	ULONG Serialum;					//serial number of IC
	BYTE ICType;						//IC type,//ccr2016-05-22ΪECRVIPʱ,�����Ա��
	BYTE ICFlag;						//IC flag,//ccr2016-05-22ΪECRVIPʱ,Ϊ'V'
	BYTE FYear;
	BYTE FMonth;						 //
	BYTE FDay;							 // date
	BYTE Custname[10];
	BYTE FTime[2];				//(BCD)
	BYTE Discount[2];				//(BCD)
	BYTE CValue[5];						//currency value
	BYTE CPoint[4];				//(BCD)
	BYTE OpType;						//0=NO VAT TRANSLATE,1=Clear Chipcard,2=ADD,3=SUB,4=Charge value,5=Initital chipcard
                                        //ccr2016-05-22��չ�Ƶ�ͼ������
	BYTE RValue[5];						//refresh value
	BYTE RPoint[4];						// refresh point
//	BYTE Reserve[SERNUM];				// reserve
};
struct CDC_PRICELIST 					//19 relative price list
{
	BYTE FunN;							//PRICELISTLOG
	BYTE PListNo;						//value = 1,2 or 3
//	BYTE Reserve[SERNUM];				// reserve
};

struct CDC_ECRNUM
{
	BYTE FunN;							//ECRNOLOG
	WORD EcrNumber;						//value = 1,2 or 3
};

struct CDC_VOID 						 //for r_version close table
{
	BYTE FunN;							//TVOIDLOG
	BYTE FAmt[5];                       //BCD
	BYTE FYear;
	BYTE FMonth;						 //
	BYTE FDay;							 // date
	BYTE FHour;
	BYTE FMinute;
};

struct CDC_PBCLOSE						 //for r_version close table
{
	BYTE FunN;							//PBCLOSELOG
    WORD PBNo;
	BYTE FAmt[5];                       //(BCD)
	BYTE FYear;
	BYTE FMonth;						 //
	BYTE FDay;							 // date
	BYTE FHour;
	BYTE FMinute;
};

struct CDC_PBOPEN						 //for r_version close table
{
	BYTE FunN;							//PBOPENLOG
    WORD PBNo;							//Number of the table
	BYTE FYear;
	BYTE FMonth;						 //
	BYTE FDay;							 // date
	BYTE FHour;
	BYTE FMinute;
};

struct CDC_PBTT						 //for r_version close table
{
	BYTE FunN;						//TRTABLELOG
    WORD PBFNo;						 //from table
    WORD PBTNo;						 //to table
	BYTE FAmt[5];                    //(BCD)
	BYTE FYear;
	BYTE FMonth;						 //
	BYTE FDay;							 // date
	BYTE FHour;
	BYTE FMinute;
};

struct CDC_PORA							//Pora record
{
	BYTE FunN;							//PORALOG
	WORD PoRaN;							// PORA number
	BYTE FAmt[5];						// translate value
//	BYTE Reserve[SERNUM];				// reserve
};

struct CDC_NETID						 //Net ID
{
	BYTE FunN;							//NETIDLOG
	BYTE NetID[8];                       //(HEX)
};

#if defined(CASE_INDIA)//ccr2016-06-03>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
struct CDC_EDITPLU
{//��¼�޸�PLU������־
    BYTE FunN;      // LOG Type EDITPLULOG,BIT7=1,��ʾ�༭��PLU
    WORD Code;      // (Function code of the record - Also identifies the type of record)
    BYTE OperNo;	// Cashier
    BYTE FYear;     // Receipt Date Time (BCD)
    BYTE FMonth;
    BYTE FDay;
    BYTE FHour;
    BYTE FMinute;
    BYTE FSecond;
    struct PLURECORD Plu;
};
struct CDC_EDITDEPT
{//��¼�޸Ĳ���������־
    BYTE FunN;      // LOG Type EDITDEPTLOG,BIT7=1,��ʾ�༭��dept
    WORD Code;      // (Function code of the record - Also identifies the type of record)
    BYTE OperNo;	// Cashier
    BYTE FYear;     // Receipt Date Time (BCD)
    BYTE FMonth;
    BYTE FDay;
    BYTE FHour;
    BYTE FMinute;
    BYTE FSecond;
    struct DEPTRECORD Dept;
};
#endif//ccr2016-06-03<<<<<<<<<<<<<<<<<<<
union FLOWREC
{
	struct CDC_DPT			 CDC_dpt;				//dept record
	struct CDC_ART			 CDC_art;				//Plu record
	struct CDC_END			 CDC_end;				//translat end record
	struct CDC_NOADD		 CDC_noadd;				//no added record
	struct CDC_OPER			 CDC_oper;				//operator record
	struct CDC_GIVEN		 CDC_given;				//currency record
	struct CDC_LOCK			 CDC_lock;	   			//mode_lock record
	struct CDC_DISCADD		 CDC_discadd;			//discount and add record
	struct CDC_SUBDISCADD	 CDC_subdiscadd;		//subtotal discount and add record
	struct CDC_DIRECT		 CDC_direct;			//direct sum discount record
	struct CDC_SUBDIRECT	 CDC_subdirect;			//subtotal sum discount record
	struct CDC_REGIS		 CDC_regis;				//start register record
	struct CDC_SUBTOTAL		 CDC_subtotal;			//subtotal record
	struct CDC_MESSAGE	     CDC_Message;			//
	struct CDC_SLIPEnd		 CDC_slipend;
	struct CDC_EnterIC		 CDC_enteric;			//record of enter ic
	struct CDC_REFRESHIC	 CDC_refreshic;			//record of refresh IC
	struct CDC_PRICELIST 	 CDC_pricelist; 		//19 relative price list
	struct CDC_ECRNUM		 CDC_EcrNum;			//only send to manage systyem
	struct CDC_VOID 		 CDC_Void;				 //for r_version close table
	struct CDC_PBCLOSE		 CDC_PbClose;			//record the operation of close table
	struct CDC_PBOPEN		 CDC_PbOpen;			//record the operation of open table
	struct CDC_PBTT			 CDC_PbTt;				//record the operation of translate table
	struct CDC_PORA			 CDC_PoRa;				//record the operation of translate table
    struct CDC_NETID         CDC_NetID;             //ccr2014-12-26
    struct CDC_TAX           CDC_Tax;               //TAX record
#if defined(CASE_INDIA)//ccr2016-06-03>>>>
    struct CDC_EDITPLU       CDC_EditPlu;           //��¼�޸�PLU������־
    struct CDC_EDITDEPT      CDC_EditDept;          //��¼�޸�Dept������־
#endif//ccr2016-06-03<<<<<<<<<<<<<<<<<<<
};

//----��ˮ���ݲ�ѯ����-----------------------------------------------------------------
struct LOGCOND {
	UnLong RecNum;      //ָ���վݺ�,=0ʱ,��ָ���վ�; Ϊ��ѯ��Ա������ʱ,����ָ����Ա����
    UnLong RecNumTo;    //ָ���վݺ�,=0ʱ,��ָ���վ�; Ϊ��ѯ��Ա������ʱ,����ָ����Ա����
	UnLong DateFr;      //ָ����ʼ����
	UnLong DateTo;      //ָ����������
    BYTE   LogType;     //ָ����ˮ��־����,=0ʱ,��ָ������;=0xffָ���˻���
    WORD   FuncCode;    //ָ��������,��:��ѯLogTypeΪ��������ʱ,������FuncCode��ָ��ĳ������
                        //��ѯEJʱ,ָ���տ�Ա
                        //=0ʱ,�����ƴ�����
};
//---------------------------------------------------------------------------
struct ECRLOGDES {
    short    RecSize;
	void  (*Get1Record)();
};

struct FifoHeader 						//header
{
	unsigned long HeadP;                //��һ����Ч��־�Ĵ�ŵ�ַ
	unsigned long ReadP;				//��һ��Ҫ���͸���������־���ݵ�ַ,ReadP>=HeadP
	unsigned long NextNP;               //��һ����־�Ĵ�ŵ�ַ
	unsigned long FromAddr;             //��־��ſ�ʼ��ַ
	unsigned long EndAddr;              //��־��Ž�����ַ+1,��־�Ĵ洢��ַΪFromAddr<=LOG<EndAddr
	unsigned long MAXNUMB;              //��־�ռ��С,=EndAddr-FromAddr
	BYTE  	OverCount;
};

#define ADJLOGADDR(addr) {if (addr>=ApplVar.FlowHeader.EndAddr) addr=ApplVar.FlowHeader.FromAddr+addr-ApplVar.FlowHeader.EndAddr;}

UnLong Bcd2Long(BYTE *p, BYTE BcdBytes);
void Collect_Given(void);
short Read_Flow(BYTE *Area);
void	Init_Flow(void);
short Collect_Data(BYTE cmd);
void SUB_SCANFP(BYTE Size);
void WriteToLogRam(ULONG pTo,char *pFrom,short pSize);
void ReadFrLogRam(char *pTo,UnLong pFrom,short pSize);
void RecallFlowHead(void);
void  ResetECRFlow(void);
void ExploreLog(void);
void SendMultiLog(void);

extern struct LOGCOND LogDefine;

#endif



