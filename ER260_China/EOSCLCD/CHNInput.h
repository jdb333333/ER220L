//---------------------------------------------------------------------------
#if defined(DEBUGBYPC)
#pragma option -a1
#endif

#ifndef CHNInputH
#define CHNInputH

#define INPUTPOS    3 //���뷨�µı�����ʾλ��
#define DISPPOSY    1 //���뺺����ʾ��
#define DISPPOSX	0 //���뷨�µ����뺺����ʾλ��
#define DISPMAX	    10 //���뺺����ʾ����

#define CHECKINPUT	0
#define GETINPUT	1
#define OPENINPUT	2
#define CLOSEINPUT	3


//.................................................................

#define ASC_MODE    0   //��ǰΪASCII����
#define QUWEI_MODE  1   //��ǰΪ��λ����
#define PYBH_MODE   2   //��ǰΪƴ����ڻ�����

//defined for ASCIIMode>>>>>>>>>>>>>>>
#define LOASCII     0   //СдASCII
#define UPASCII     1   //��дASCII
#define SPASCII     2   //�����ַ����뷽ʽ(!@#$%...)

#if EN_EXASCII
#define EXASCII     3   //��չASCII�ַ�
#define MAXASCII    3   //ASCII��ʽ�����Ŀ
#else
#define MAXASCII    2   //ASCII��ʽ�����Ŀ
#define EXASCII     (MAXASCII+1)   //��չASCII�ַ�
#endif
//<<<<<<<<<<<<<<<<<<<<<<<<<

typedef struct {
    const char *Name;
    BYTE MaxInput;
} MODEREC;

extern BYTE CHNMode;
extern WORD ChnInput(BYTE func);
//---------------------------------------------------------------------------
#endif
