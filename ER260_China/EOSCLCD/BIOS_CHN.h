
//---------------------------------------------------------------------------
#ifndef BIOS_CHNH
#define BIOS_CHNH
//---------------------------------------------------------------------------
#define LCDINITIAL	0
#define LCDDISPCH	1
#define LCDREFRESHL	2
#define	LCDCLEARSCR	3
#define LCDDISPCURS	4
#define LCDENCURSOR	5
//#define LCDLIGHT		6
#define LCDLIGHTON	6
#define LCDLIGHTOFF	7
//#define LCDDISPBLOCK	8
#define LCDCONTRAST		8
//---------------------------------------------------------------------------
#if defined(DEBUGBYPC)
extern void DisplayLcd(short lcdLine);
extern void mClearScreen();
extern void mBalnkScreen(void);
#define mInitialLCD() 		{memset(ApplVar.ScreenMap,' ',sizeof(ApplVar.ScreenMap));DisplayLcd(0);DisplayLcd(1);DisplayLcd(2);DisplayLcd(3);}
#define mDispCharXY(ch,x,y) {} //DispCharXY(ch , x, y)

#define mEnCursor(on)     {}

#define mDispCursor()		{}
#define mRefreshLine(LinNum) DisplayLcd(LinNum)
#define mSetState(on_off)    {(on_off==0)?RESETBIT(ApplVar.ScreenStat,STATEON):SETBIT(ApplVar.ScreenStat,STATEON);}

#define mLightLCDOn()		{}
#define mLightLCDOff()		{}

#define mSetContrast(a)		{}
#define mContrastDown()	{}

#else

void mInitialLCD(void);//��ʼ������ģ��
void mClearScreen(void);//�����Ļ����
void mDispCharXY(WORD ch,BYTE x,BYTE y) ;//�ڵ�y(0~3)��,��x(0~15)��λ����ʾ�ַ�ch,ch������ASCII���ߺ���
void mEnCursor(BYTE on)       ;//������ʾ���
void mDispCursor(void) ;//��ʾ���
void mRefreshLine(BYTE LinNum);//ˢ����Ļ��ָ������LinNum(0~3),������Ļ�ϵĵ�LinNum��������ʾһ��
void mLightLCDOn(void) ;//����ʾ����
void mLightLCDOff(void) ;//�ر���ʾ����
void mSetContrast(uint8_t contrast);//������ʾ����

#endif

#define mClearInvAttr()		RESETBIT(ApplVar.ScreenStat, INVATTR)//�����������
#define mSetInvAttr()		SETBIT(ApplVar.ScreenStat, INVATTR)//���÷�������,�˺��������ʾ���Է�����ʾ
//#define mScreenOn(char sta) {};
#endif
