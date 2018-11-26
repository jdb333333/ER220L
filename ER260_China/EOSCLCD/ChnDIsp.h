//---------------------------------------------------------------------------
#if defined(DEBUGBYPC)
#pragma option -a1
#endif

#ifndef CHNDispH
#define CHNDispH

//#define CHAR_6X8  0 //ccr2016-01-18 ʹ��8x16����ASCII�ַ�

#if (!defined(CHAR_6X8) || defined(CASE_FORHANZI))
#define SCREENLN	4	//Screen lines
#define SCREENWD	16	//20050105 24	//Screen width
#else
#define SCREENLN	8	//Screen lines
#define SCREENWD	21	//20050105 24	//Screen width
#define SCRDBLWD    11  //ccr2016-03-01����ʱ����Ļ���
//#define SCRSTATDBL   1   //ccr2016-03-01״̬�б�����ʾ
#endif

#define STATELN		1	//Statues lines

#define STATELINE	SCREENLN


//ApplVar.ScreenStat:

//��ʾ״̬,��λ��Ӧ����:
#define STATEON		BIT0    //STATEON����Ϊ��һλ(���ֵ���ڼ���)
#define CURSOREN	BIT1    //���ʹ�ܱ�־(�Ƿ�����Ļ����ʾ���)
#define CURSORON	BIT2    //��Ļ����ʾ�й���־
#define SCREENON	BIT3    //��ĻΪ��ʾ״̬��־
#define LIGHTON		BIT4    //����򿪱�־
#define HZINPUTMODE BIT5    //Ϊ��������ģʽ
#define HZSELECT    BIT6    //������һ������
#define INVATTR		BIT7    //����
#define CRITICAL	BIT8	//�������
#define SCREENCOPY  BIT9    //��Ļ���ݱ����븲��
#define DOUBLEWIDTH  BIT10    //˫����ȣ���5x8�ַ���ʾΪ10x8

//ccr2016-03-01 ��������
#define mClearDBLDisp() RESETBIT(ApplVar.ScreenStat, DOUBLEWIDTH)
#define mSetDBLDisp()   SETBIT(ApplVar.ScreenStat, DOUBLEWIDTH)

typedef struct {
    char y;
    char x;
    } CURSOR;
//---------------------------------------------------------------------------
#if defined(DEBUGBYPC)
#define CONST

#define mDrawPower( ctrl,  ColNum, LinNum) {}
#define  mDrawGPRSSignal(Signal,ColNum,LinNum) {}

#pragma option -a1

#else

#define CONST const

void mDrawPower(BYTE ctrl, BYTE ColNum,BYTE LinNum);
void mDrawGPRSSignal(BYTE Signal,uint8_t ColNum,uint8_t LinNum);

#endif

#if defined(CASE_FORHANZI)
#define SIGNAL_X     4  //GPRS�ź���ʾλ��
#else
#define SIGNAL_X     3
#endif

#if defined(CASE_GPRS)
#define POWER_X    (SIGNAL_X+1)  //��Դǿ����ʾλ��
#else
#define POWER_X    (SIGNAL_X)  //��Դǿ����ʾλ��
#endif


struct EDITSTRUCT {
    short   DispFrom;//��ǰ��ʾ��ʼλ��,����EditBuff+DispFrom��ʾ����
    BYTE    DispX;//�༭��������Ļ�ϵ���ʾλ��
    BYTE    DispY;//�༭������ʾλ��
    BYTE    DispW;//���ݱ༭����ʾ���
    BYTE    EditOffs;//��ǰ�༭λ��
    BYTE    EditCount;//�Ѿ�������ַ���Ŀ
    BYTE    BuffSize;//=sizeof(EditBuff)-1
    BYTE    *EditBuff;//must terminated by NULL(\0)
    char    *Source; //ccr2015-03-11����������ݽ�Ҫ����Ĵ洢��
};
//---------------------------------------------------------------------------

extern void SetEditPosition(BYTE x,BYTE y,BYTE len,char *source);
extern void InitLineEditor(short x,short y);
extern BYTE DispCharXY(WORD ch ,BYTE x,BYTE y);
extern void DispStrXY(CONST BYTE *str ,BYTE x,BYTE y);
extern BYTE GotoXY(BYTE x,BYTE y);
extern WORD Getxy(void);
extern void GetStrFr(char *str);
extern WORD GetChFr(BYTE x,BYTE y);
extern void OpenMess(char on);
extern void ClearScreen(void);
extern void ScrollScreen(BYTE sLines);
extern void ClearLine(char LinNum);

extern void ScreenFeed(char LinNum);
extern BYTE LineEditor(union KEY ch);
extern BYTE TestHZRight(BYTE *str,short pos);
extern void DisplayChar(BYTE ch);
extern void	mDispStringXY(BYTE *dbuf,BYTE DISPX,BYTE LN);

extern void DispStr_Right(char *str,BYTE y);

extern void BackupScreen(BYTE savCur);
extern void RecallScreen();
extern void  DispLFStr(char *str);
//---------------------------------------------------------------------------

extern struct EDITSTRUCT Editor;

extern WORD    HANZI;

void DispOnStatDBL(char *str,BYTE x);//�Ա������ʽ��״̬����ʾ����


//---------------------------------------------------------------------------
#define DispSt0(a)	DispStrXY(a,0,STATELINE)			/* Display from 0 */
#define DispSt1(a)  DispStrXY(a,PROMDISPX,STATELINE)	/* Display from 4 */
#define DispSt2(a)  DispStrXY(a,INPUTDISPX,STATELINE)	/* Display from 10 */

#define DispSt0C(a)	{ClsState0();DispStrXY(a,0,STATELINE);}	/* Display from 0 */
#define DispSt1C(a) {ClsState1();DispStrXY(a,PROMDISPX,STATELINE);}	/* Display from 4 */
#define DispSt2C(a) {ClsState2();DispStrXY(a,INPUTDISPX,STATELINE);}	/* Display from 10 */

#define DispStrLF(a) {DispStrXY(a,0,0xff);ScreenFeed(1);}

extern void ClsState0(void);	/* Clear first 4 Bytes 0->3 */
extern void ClsState1(void);  /* Clear first 10 Bytes 4->14 */
extern void ClsState2(void);  /* Clear first 6 Bytes 10->15*/
extern void ClsState12(void);
extern void ClsArea(BYTE x,BYTE y,BYTE l);
extern void SuspendScreen(void);

#endif

