#ifndef EJOURNAL_H
#define EJOURNAL_H

#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))

#if defined(DEBUGBYPC)
#pragma option -a1
#else
#pragma pack(1)
#endif
//-------------------------------------------------------------

#if defined(CASE_EJSD)
//EJ�洢��SD�� ��
#define GETINDEXSIZE()   ( (ApplVar.EJVar.MMCSIZEMAX<=0x2000000L)?(10*1024):(ApplVar.EJVar.MMCSIZEMAX<=0x8000000L)?(40*1024):(128*1024) )

#define MMC_LESS			0x2000          // ��EJʣ��ռ�����MMC_LESSʱ,����EJ����.
#define MMC_FULL			(1024)        // ��EJʣ��ռ�����MMC_FULLʱ,��ΪEJ����.
#define SD_BLOCKSIZE			512				// ÿ���ֽ�,����Ϊ512//

//     ͷָ�뱣���ַ IDXENDADDRESS,�˵�ַ����EJ��д��������EJHeader,���ǵ������ԣ�����ռ1024�ֽ� //
#define IDXENDADDRESS			((ApplVar.EJVar.MMCSIZEMAX-1024) & 0xfffffE00)//0x1E9FE00L

#define EJMEMORYFROM				0

#define EJHEADERADDR		EJMEMORYFROM  //EJ��ʼ����ϢEJHeader���λ��,ռ��1024�ֽ�
#define HEADSIZE			sizeof(ApplVar.EJHeader)		//ʵ��ռ��1024�ֽ�

#define EJDOCADDRFROM			(EJMEMORYFROM+1024)    //��һ��EJ��¼���ݴ��λ�ÿ��ǵ������ԣ�����ռ1024�ֽ� //

#define INDEXADDR			(IDXENDADDRESS - ApplVar.EJHeader.SizeEJIndex - SD_BLOCKSIZE)    //��¼�������λ��,��Ű�����˳�������
#define INDEXRECORDSIZE	    10   //ccr2016-10-31//������¼��С:2�ֽ�����+4�ֽڵ�ַ+���ֽ�EJ#
#define INDEXRECORDCOUNT	(ApplVar.EJHeader.SizeEJIndex / INDEXRECORDSIZE)   //������¼��

#define EJDOCADDRMAX			(INDEXADDR-SD_BLOCKSIZE)		// MMC��ʵ�ʿ�ʹ������ //

#elif defined(CASE_EJFLASH)//----------------------------------------
//EJ�洢��FLASH��
#define FLASHFOREJ       0x10000    //EJ������FLASH�д洢��ʼ��ַ
#define BLOCK1STFOREJ    4          //EJ������FLASH�д洢��ʼ��
#define BLOCKSFOREJ      31         //EJ������FLASH�д洢ռ�ÿ���

#define GETINDEXSIZE()   900    //���Դ洢90�����������

#define MMC_LESS			0x2000          // ��EJʣ��ռ�����MMC_LESSʱ,����EJ����.
#define MMC_FULL			(1024)        // ��EJʣ��ռ�����MMC_FULLʱ,��ΪEJ����.
#define SD_BLOCKSIZE			512				// ÿ���ֽ�,����Ϊ512//

#define EJMEMORYFROM		0x10000    //EJ������FLASH�д洢��ʼ��ַ

#define IDXENDADDRESS		(EJMEMORYFROM+1024)//������������ַ

//ͷָ�뱣���ַ EJHEADERADDR,�˵�ַ����EJ��д��������EJHeader,���ǵ������ԣ�����ռ1024�ֽ� //
#define EJHEADERADDR		EJMEMORYFROM  //EJ��ʼ����ϢEJHeader���λ��,ռ��1024�ֽ�
#define HEADSIZE			sizeof(TEJHEADER)		//ʵ��ռ��1024�ֽ�

#define EJDOCADDRFROM			(EJMEMORYFROM+1024)    //��һ��EJ��¼���ݴ��λ�ÿ��ǵ������ԣ�����ռ1024�ֽ� //

#define INDEXADDR			((HEADSIZE + 0x10 + EJMEMORYFROM) & 0xfffffff0)    //��¼�������λ��,��Ű�����˳�������
#define INDEXRECORDSIZE	    10   //ccr2016-10-31//������¼��С:2�ֽ�����+4�ֽڵ�ַ+���ֽ�EJ#
#if defined(DEBUGBYPC)
#if (IDXENDADDRESS>INDEXADDR+INDEXRECORDSIZE*2)
#define INDEXRECORDCOUNT	((IDXENDADDRESS-INDEXADDR) / INDEXRECORDSIZE)   //������¼��
#else
#error "Error:Size of EJ INDEX"
#endif
#else
#define INDEXRECORDCOUNT	((IDXENDADDRESS-INDEXADDR) / INDEXRECORDSIZE)   //������¼��
#endif
#define EJDOCADDRMAX			(BLOCKSFOREJ*0x10000+EJMEMORYFROM)		// MMC��ʵ�ʿ�ʹ������ //

#endif

//For ContFlag-------------------------------------------
#define EJSTOREMUST		BIT0	// Must Store into EJ
#define EJHEADMUST		BIT1	// Must Store EJ head first
#define EJDOCHEAD		BIT2	// EJ head has be store
#define EJENDMUST       BIT3    // �������EJ�ĵ�������ʾ

#define EJISNEW         BIT4    // Ϊ��EJ,������г�ʼ��
#define EJNOTEXIST      BIT5    // û��EJ,�������EJ
#define EJxECR          BIT6    // EJ���տ����ƥ��,�����³�ʼ��
#define EJISFULL        BIT7    // EJ����,�������EJ
#define EJWILLFULL      BIT8    // =1ʱ,��ʾEJ����

#define EJVIEWPRINT     BIT9    // =0,��ʾEJ;=1ʱ,��ӡEJ
//----------------------------------------------------------------
//-------------EJ��¼���Ͷ���(EJContent)-----------------------
#define EJMARK	0xC5A3	//MARKER '��' for EJ flag
//-------------EJ�ĵ���־����-----------------------------
#define CEJ_STARTDOC	0x0A	//\n = start new document
#define CEJ_STARTLN		0x0D	//\r = Ϊһ��EJ�ı�����
#define CEJ_STARTLND	0x0E	//0E = Ϊһ�б��ߵ�EJ�ı�����
#define CEJ_DOCEND		0x1A	//^Z = EJ�ĵ�������־,���һ���ֽ�ΪУ����
//CONST BYTE ZIPList[ZIPLISTMAX] ={' ','*','-','.','='};//���5��
#define CEJ_ESC			0x1B	//ESC = number of spaces to be decompressed
#define CEJ_ESC1		0x1C	//ESC = number of * to be decompressed
#define CEJ_ESC2		0x1d	//ESC = number of - to be decompressed
#define CEJ_ESC3		0x1e	//ESC = number of . to be decompressed
#define CEJ_ESC4		0x1f	//ESC = number of = to be decompressed
//---------------------------------------------------------------
typedef struct 				//EJ�ĵ�ͷ(CEJ_STARTDOC),��СΪEJDOCHEADSIZE
{
    BYTE    EJStart;          //�ĵ���ʼ��־=CEJ_STARTDOC,Ҳ����һ���ĵ�������־
    ULONG   EJDocNumber;      //�ĵ����
    BYTE    EJLocation;         //ccr2016-10-29�ŵ��
    BYTE    EJRegister;         //ccr2016-10-29�տ����
    //^^^^�������ݲ���^^^^^^^^
    BYTE    EJDocType;        //�ĵ�����('R/Z/X/M/S/O'),��Ҫ���䶨��λ��
    TDATETIME  EJDateTime;     //�ĵ�����ʱ��:0Xyymmddhhmmss,��Ҫ�������˳��
    WORD    EJClerk;           //ccr2016-10-28�տ�Ա���
} TEJDOCHEAD;

#define EJDOCHEADSIZE	sizeof(TEJDOCHEAD)  //16 ÿ��EJ�ĵ��ļ�¼ͷ���ݴ�С,=sizeof(EJDOCHEAD) //

#define EJBUFFSIZE  (PRTLEN+5)

//EJ��ʼ����Ϣ,��98�ֽ�,
//��ΪCASE_EJFLASHʱ,��󲻵ó���124�ֽ�
//��ΪCASE_EJSDʱ,��󲻵ó���1024�ֽ�
typedef struct
{
	WORD 	EJMark;              //EJ��ʼ����־
	BYTE	EJID[32];           //��ʼ����,���˰�����кŵ���Ϣ,Ҳ����������ſͻ�����
	TDATETIME InitDateTime;    //EJ��ʼ������ʱ��
	WORD	Release;            //(˫�ֽڶ���)�����汾

    //SD��������Ϣ
    ULONG   SizeOfSD;           //SD��������,=ApplVar.EJVar.MMCSIZEMAX;
    ULONG   AddrEJFirst;          //��һ��EJ��¼�ĵ�ַ,Ҳ��EJHeader�ķ���ռ�,=EJDOCADDRFROM
    ULONG   AddrEJMax;          //EJ��¼���ݿռ������ַ,=EJDOCADDRMAX
    ULONG   AddrEJIndex;        //EJ�����������λ��,=INDEXADDR
    ULONG   SizeEJIndex;        //EJ�������������ռ��С
    WORD    MaxEJIndex;         //EJ����������¼�����,=INDEXRECORDCOUNT
    ULONG   AddrEJHeader;       //���EJHeader���ݵĵ�ַ,=EJHEADERADDR
    WORD    SizeEJHeader;       //EJHeader�Ĵ�С,ʵ�ʷ���ռ�Ϊ1024�ֽ�

    //EJ�ĵ���������
    BYTE    EJLocation;         //ccr2016-10-29�ŵ��
    BYTE    EJRegister;         //ccr2016-10-29�տ����
    BYTE    EJType;             //1/2/3�ֱ��Ӧ��ͬ������,0xefʱ,Ϊʹ��flash�洢EJ
    BYTE    EJClerk;            //��ʼ���˿����տ�Ա
    //����Ϊ�̶�������Ϣ-----------------
    ULONG   AddrLastEJ;		    //���һ���ĵ���λ��,�����һ��EJ��ʼ�ĵ��Ĵ洢λ��
    ULONG   AddrLast2EJ;		//�����ڶ����ĵ���λ��,�����һ����Ч��EJ�ĵ�
    ULONG   AddrNextEJ;		    //�µ�EJ���ݽ�Ҫд��ĵ�ַ
    ULONG   AddrEJRead;         //��Ҫ���͵�EJ���ݿ�ʼ��ַ,Ϊ��Ե�ַ
    WORD    DateLastEJ;         //��ǰд��EJ�ĵ�������,����������������
    WORD    IndexCount;         //������¼��
    ULONG   EJDocNumber;		// ���һ��EJ�ĵ������
}TEJHEADER;
//ccr2016-11-01 EJ��������
typedef struct {
    WORD ContFlag;      //EJ���Ʊ�־
    BYTE EJContent; 	//content type of EJ Log
    BYTE EJcrc;         //EJ�ĵ���У����(��RefreshEJStart��Ӱ��,��У��û������)
    ULONG MMCSIZEMAX;   //SD��������(���4G)
    ULONG MMCLast;      //EJ���һ�ζ�д���ݵĵ�ַ
}TEJVAR;

//ccr2016-11-01 EJ��������
typedef struct {
    WORD  EJDate;      //EJ����
    ULONG EJAddress;   //��SD���еĵ�ַ
    ULONG EJNumber;    //EJ�ĵ����
}TEJINDEX;

#if (defined(DEBUGBYPC))
#if (INDEXRECORDSIZE!=sizeof(TEJINDEX))
#error "INDEXRECORDSIZE error!"
#endif
#endif

//ccr2014-08-07>>>>>>>>>>>>>>>>>>>>>>
/*TEJROLL�����������Ҫд���EJ LOG*/
typedef struct
{
  BYTE  Flag;       //=0x69,˵��EJ����д��ʧ��
  BYTE  FlagS;      //����Ϊ0x5a,���е����ݲ���Ч
  BYTE  EJContent;
  ULONG Address;    //EJ���ݵ�д���ַ
  BYTE  LogLen;     //EJ���ݳ���
  BYTE  EJcrc;      //EJ���ݵ�У��
  BYTE  EJData[EJBUFFSIZE];//EJ����
} TEJROLL;
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


extern void WriteEJHead(void);
extern ULONG ReadEJIndexByDate(WORD pDate);
extern ULONG ReadEJIndexByNumber(ULONG pNumber);
extern ULONG WriteEJIndex(WORD pDate,BYTE inc);
extern ULONG RecallEJHead(void);

#if (defined(CASE_EJSD))
extern BYTE MMC_CheckPresence(void);
void EJ_Exist(void);
#else//>>>for CASE_EJFLASH
#define MMC_CheckPresence() true
#define EJ_Exist()  {}
#endif

extern BYTE ReadFromMMC(char *to,ULONG pFrom,WORD bytes);
extern void StoreEJStart(void);
extern void StoreEJData(BYTE cmd, BYTE *str);
extern void StoreLogType(BYTE type, BYTE *str);
extern void PrintEJLog(BYTE prnLast);
extern BYTE Initial_EJ(void);

#define StoreEJEnd() StoreEJData(CEJ_DOCEND,0)  //�洢EJ�ĵ�������־

extern BYTE CheckEJ(void);

extern  BYTE  MMC_Buff[SD_BLOCKSIZE*2];
extern void ExploreEJournal();

BYTE WriteStream(char *from,WORD bytes,BYTE erase);
BYTE WriteEJLog(char *pFrom,WORD pSize);
BYTE ECRMode(void);

BYTE CheckEJError(BYTE disp);
void PrintEJInfo(BYTE oldEJ);
BYTE TestSaveEJ(void);
void RefreshEJStart(BYTE refresh);
void DisplayEJInfo1BY1(void);

//------------ defined for ReadEJInfo--------------
#define READEJINI_T    	    0	//��ȡ��ʼ������
#define READEJINIT_D   		(READEJINI_T    +1)	//��ȡ��ʼ������
#define READEJEND_T    		(READEJINIT_D   +1)	//��ȡ���һ��EJ�����ڱ���
#define READEJEND_D    		(READEJEND_T    +1)	//��ȡ���һ��EJ������
#define READEJSIZE_T   		(READEJEND_D    +1)	 //��ȡEJ��С����
#define READEJSIZE_D   		(READEJSIZE_T   +1)	 //��ȡEJ��С
#define READEJLEFT_T   		(READEJSIZE_D   +1)	 //��ȡEJʣ���С����
#define READEJLEFT_D   		(READEJLEFT_T   +1)	 //��ȡEJʣ���С
#define READEJRECORDS_TD     (READEJLEFT_D +1)       	//��ȡEJ��¼��
#define READEJREGISTER_TD   (READEJRECORDS_TD +1)         //��ȡEJ�տ���� /* REGISTER number */
#define READEJLOCATION_TD   (READEJREGISTER_TD+1)         //��ȡEJ�̵�� /* LOCATION number */
#define READEJCLERK_T    	(READEJLOCATION_TD+1)      //��ȡEJ�տ�Ա����/* CLERK */
#define READEJCLERK_D    	(READEJCLERK_T    +1)      //��ȡEJ�տ�Ա
void ReadEJInfo(void);

void DisplayEJInfo(BYTE prnEJLast);
void PrintEJNumber(void);
#endif
#endif


