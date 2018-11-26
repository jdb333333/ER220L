#define AUTOBUFMAX  2048
#define SENDTOHOST	1
#define FASTMODE	0   //���ٲ��Է�ʽ
#define DEPT_TEST   1   //���Բ�������
#define PLU_TEST    1   //���Ե�Ʒ����
//---------------------------------------
#define TEST_END        0
#define TEST_NEXTDAY    1
#define TEST_REPEAT1    2
#define TEST_REPEAT2    (TEST_REPEAT1+1)
#define TEST_REPEAT3    (TEST_REPEAT1+2)
#define TEST_REPEAT4    (TEST_REPEAT1+3)
#define TEST_REPEAT5    (TEST_REPEAT1+4)
#define TEST_REPEAT6    (TEST_REPEAT1+5)
#define TEST_REPEAT7    (TEST_REPEAT1+6)
#define TEST_REPEAT8    (TEST_REPEAT1+7)
#define TEST_REPEAT9    (TEST_REPEAT1+8)
#define TEST_REPEAT10   (TEST_REPEAT1+9)
#define TEST_ZREPORT    TEST_REPEAT10+1
//---------------------------------------

struct ECRTESTATTR {
	BYTE	Going;			// �Ƿ���в���,=0ʱ,�����в��� //
	BYTE	LastDay;
	BYTE	Repeat;		// ѭ������һ��
	BYTE	PrnOFF;			//
	int     KeyEmuNum;		// ʹ��ROM�е����ݽ��в���
    int    TestCount;    //��¼���Դ���
#if FASTMODE
    int AutoKeyCurrent ;
    int AutoReceiptTag ;

    BYTE AutoKeyBuf[AUTOBUFMAX];
#endif

};


extern struct  ECRTESTATTR  FisTestTask;

void SendABCD(BCD *pBcd);

extern void FisTestProc();
extern void chkAutoReceiptKey();

void SendALong(long pLInt);
void SendAWord(WORD pLInt);


