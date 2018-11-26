#include "king.h"
#include "exthead.h"
#include "exth.h"


extern BYTE    InputNum;   // code number of input

struct EDITSTRUCT Editor;

//---------------------------------------------------------------------------
//display a character at screen position(x-Col,y-Row)
BYTE DispCharXY(WORD ch ,BYTE x,BYTE y)
{
    if (TESTBIT(ApplVar.ScreenStat,CURSOREN |CURSORON)==(CURSOREN |CURSORON))
        mDispCursor();//�رչ��

    if (x==0xff)
        x = ApplVar.sCursor.x;
    if (x>=SCREENWD && ch != '\n')
        return 0;

    if (y==0xff)
        y = ApplVar.sCursor.y;

    if (ch=='\n')
    {
        if (y>SCREENLN)
            return 0;
        y++;
        if (y>=(SCREENLN-TESTBIT(ApplVar.ScreenStat,STATEON)))//ccr2015-06-15
        {
            y = SCREENLN-1-TESTBIT(ApplVar.ScreenStat,STATEON);//ccr2015-06-15
            ScrollScreen(1);
        }
        ApplVar.sCursor.y = y;
        ApplVar.sCursor.x = 0;
    }
    else
    {
        if (y>SCREENLN)
            y = SCREENLN;//display it at status line

#if defined(CASE_FORHANZI)
        if (ch>0xff && x==SCREENWD-1)
            ch &= 0xff;

        if (ch>0xff)
            (*(WORD *)&ApplVar.ScreenMap[y][x]) = ch;
        else
#endif
            ApplVar.ScreenMap[y][x] = ch;

#if defined(DEBUGBYPC)
        DisplayLcd(y);
#else
        if (TESTBIT(ApplVar.ScreenStat,STATEON) && y>=SCREENLN)
            mDispCharXY(ch , x, STATELINE);
        else if (y<SCREENLN)
            mDispCharXY(ch , x, y);
#endif

    }
    return 1;
}
//---------------------------------------------------------------------------
//display a string at screen position(x,y)
void DispStrXY(CONSTBYTE *str ,BYTE x,BYTE y)
{
    short i;
    BYTE lin;
    CONSTBYTE *sStr = str;
    WORD ch;

    if (!str || !str[0])
        return;

    if (x==0xff)
        x = 0;
    else if (x>=SCREENWD)
        return;

    if (y==0xff)
        y = ApplVar.sCursor.y;
    else if (y>STATELINE)
        y = SCREENLN;//display it at status line

    switch (y)
    {
    case SCREENLN://Display message on stateline
        if (TESTBIT(ApplVar.ScreenStat,STATEON))
        {//ֻ����״̬�д򿪵������,�Ž���Ϣ��ʾ����Ļ�� //
            lin =SCREENLN-1;
            break;
        }
    case SCREENLN-1:
        if (TESTBIT(ApplVar.ScreenStat,STATEON) || y==STATELINE)
        {//������ڴ򿪵������Ҫ�ڵ�������ʾ����״̬��û�д򿪵���Ҫ��״̬����ʾʱ, //
         //ֻ����Ϣ���浽��ʾ��,��Ļ�ϲ�������ʾ���� //
            for (i=x;i<SCREENWD;i++)
            {
                if (!sStr[0])
                    break;
                ApplVar.ScreenMap[y][i] = sStr[0];
                sStr++;
            }
            return;
        }
    default:
        lin = y;
    }

    for (i=x;i<SCREENWD;)
    {
        if (!sStr[0])
            break;
        if (sStr[0] == '\n')
        {
#if defined(DEBUGBYPC)
            DisplayLcd(y);
#endif
            if (DispCharXY('\n',0,y))
            {
                y = ApplVar.sCursor.y;
                i = 0;
                if (TESTBIT(ApplVar.ScreenStat,STATEON) && y>=SCREENLN)
                    lin =SCREENLN-1;
                else
                    lin = y;
            }
        }
        else
        {
            ch = sStr[0];

            ApplVar.ScreenMap[y][i] = sStr[0];
#if defined(CASE_FORHANZI)
            if (ch>0xa0 && i<SCREENWD-1 && sStr[1]>0x80)//ccr2015-05-08 0xa0 ��
            {
                ch = *((CONSTWORD*)sStr);
                (*(WORD *)&ApplVar.ScreenMap[y][i]) = ch;
            }
            mDispCharXY(ch , i, lin);
            i++;
            if (ch>0x80a0)
            {
                sStr++;
                i++;
            }
#else
            mDispCharXY(ch , i, lin);
            i++;
#endif
        }
        sStr++;
        if (sStr[0]=='\n')
            i--;
    }
#if defined(DEBUGBYPC)
    DisplayLcd(y);
#endif

}
//-----------------------------------------------
//ccr20131120 ��ָ�����Ͽ�����ʾ�ַ���
void DispStr_Right(char *str,BYTE y)
{//�ڲ���Ա��ʾ��Ļ����ʾ����,16λ1����ʾ

    BYTE toScreen[SCREENWD+1];
    int l;

    l = strlen(str);
    if (l<SCREENWD)
    {
        memset(toScreen,' ',SCREENWD);
        memcpy(toScreen+SCREENWD-l,str,l);
    }
    else
        memcpy(toScreen,str,SCREENWD);
    toScreen[SCREENWD]=0;
    DispStrXY(toScreen,0,y);
}
//---------------------------------------------------------------------------
//set the position of cursor
//return 1 if cursor at HANZI right
BYTE GotoXY(BYTE x,BYTE y)
{
    short i;

    BYTE flg,cur=TESTBIT(ApplVar.ScreenStat,CURSOREN);

    if (cur)
        mEnCursor(DISABLE);//�رչ��

    flg = 0;
#if defined(CASE_FORHANZI)
    for (i=0;i<x;i++)
    {
        if (ApplVar.ScreenMap[y][i]>0x80)//ccr2015-05-08 0xa0 ��
            flg ^= 1;
    }
#endif
    ApplVar.sCursor.x = x;
    ApplVar.sCursor.y = y;
    if (cur)
        mEnCursor(ENABLE);
	return 	flg;
}
//---------------------------------------------------------------------------
//get the position of cursor
WORD Getxy()
{
    return(*(WORD *)&ApplVar.sCursor);
}
//---------------------------------------------------------------------------

void GetStrFr(char *str)
{
    short i;

    for (i=0;i<SCREENWD;i++)
    {
        str[i] = ApplVar.ScreenMap[ApplVar.sCursor.y][i];
        if (!str[i])
            break;
    }
    str[i] = 0;
}

//---------------------------------------------------------------------------
WORD GetChFr(BYTE x,BYTE y)
{
    WORD ch;

    if (x==0xff)
        x = ApplVar.sCursor.x;
    if (y==0xFF)
        y = ApplVar.sCursor.y;

#if defined(CASE_FORHANZI)
    ch =*((WORD *)&ApplVar.ScreenMap[y][x]);
    if (ch<0xA0 || x>=(SCREENWD-1))
        ch &= 0xff;
#else
    ch =ApplVar.ScreenMap[y][x];
#endif
    return ch;
}

//---------------------------------------------------------------------------
void OpenMess(char on)
{
    if ((on==0) ^ (TESTBIT(ApplVar.ScreenStat,STATEON)==0))
    {
        mSetState(on);
        mRefreshLine(STATELINE);
    }
}

//---------------------------------------------------------------------------
void ScrollScreen(BYTE sLines)
{
    short i;

    memcpy(&ApplVar.ScreenMap[0],&ApplVar.ScreenMap[1],SCREENWD*(SCREENLN-1));
    memset(&ApplVar.ScreenMap[SCREENLN-1],' ',SCREENWD);

    for (i=0;i<SCREENLN-TESTBIT(ApplVar.ScreenStat,STATEON);i++)
        mRefreshLine(i);
}
//---------------------------------------------------------------------------

void ClearLine(char LinNum)
{

    memset(&ApplVar.ScreenMap[LinNum],' ',SCREENWD);
    mRefreshLine(LinNum);

}

//---------------------------------------------------------------------------

void ScreenFeed(char LinNum)
{
    BYTE i;

    for (i=0;i<LinNum;i++)
        DispCharXY('\n',0xff,0xff);
}



//test if the character at pos is HANZI rightHalf or not
BYTE TestHZRight(BYTE *str,short pos)
{

#if defined(CASE_FORHANZI)
    BYTE    flag;
    short     i;

    flag = 0;
    if (str[pos]<0x80)//ccr2015-05-08 0xa0 ��
        return 0;
    for (i=pos-1;i>=0;i--)
    {
        if (str[i]>0x80)//ccr2015-05-08 0xa0 ��
            INVERTBIT(flag,BIT0);
        else
            break;
    }
    return flag;
#else
    return 0;
#endif
}


//---------------------------------------------------------------------------
//�ڵ�ǰ���λ����ʾһ��ASCII�ַ����ߺ���,��ʾ��Ϻ��Զ��������λ��
//position (ApplVar.sCursor.x,ApplVar.sCursor.y)
void DisplayChar(BYTE chNow)
{
    static BYTE chLast=0;
    WORD ch;
	BYTE x,y;

    if (chLast==0 && chNow>0x80)//ccr2015-05-08 0xa0 ��
    {//Ϊ�����ַ�
        chLast=chNow;
        return;
    }
    ch = chNow;
    if (chLast && ch>0x80)//ccr2015-05-08 0xa0 ��
    {//��ϳ�һ�������ĺ���
        ch = (ch<<8) + chLast;
    }
    chLast=0;
    x = ApplVar.sCursor.x;
    if (x>=SCREENWD && ch != '\n')
        return ;
    y = ApplVar.sCursor.y;

    if (ch=='\n')
    {
        if (y!=STATELINE)
        {//����״̬��
            y++;
            if (y>(SCREENLN-1))
            {
                y = (SCREENLN-1);
                ScrollScreen(1);
            }
            ApplVar.sCursor.y = y;
        }
        ApplVar.sCursor.x = 0;
    }
    else
    {
        if (y>SCREENLN)
            y = SCREENLN;//display it at status line

#if defined(CASE_FORHANZI)
        if (ch>0xff && x==SCREENWD-1)
            ch &= 0xff;

        if (ch>0xff)
        {
            (*(WORD *)&ApplVar.ScreenMap[y][x]) = ch;
            ApplVar.sCursor.x++;
        }
        else
#endif
            ApplVar.ScreenMap[y][x] = ch;
        ApplVar.sCursor.x++;

#if defined(DEBUGBYPC)
        DisplayLcd(y);
#else
        if (TESTBIT(ApplVar.ScreenStat,STATEON) && y>=SCREENLN)
            mDispCharXY(ch , x, SCREENLN-1);//��ʾ��״̬��
        else if (y<=SCREENLN-1-TESTBIT(ApplVar.ScreenStat,STATEON))
            mDispCharXY(ch , x, y);//�������״̬��,��ʾ�ַ�
#endif

        if (ApplVar.sCursor.x>=SCREENWD)
        {
            ApplVar.sCursor.x = 0;
            if (y!=STATELINE)
            {
                ApplVar.sCursor.y++;
            }
        }
        if (ApplVar.sCursor.y==(SCREENLN-1) && TESTBIT(ApplVar.ScreenStat,STATEON))
        {
            ApplVar.sCursor.y = SCREENLN-2;
            ScrollScreen(1);
        }
    }
    return;
}

//---------------------------------------------------------------------------
/* Clear Bytes 0->3 */
void ClsState0()
{
	char buf[PROMDISPX+1];  // 4 bytes

	memset(buf,' ',PROMDISPX);
	buf[PROMDISPX] = 0;
	DispSt0(buf);
}

/* Clear Bytes 4->14 */
void ClsState1()
{
	char buf[SCREENWD-PROMDISPX+1];	// 10 bytes

	memset(buf,' ',sizeof(buf));
	buf[SCREENWD-PROMDISPX] = 0;
	DispSt1(buf);
}

/* Clear Bytes 10->15 */
void ClsState2()
{
	char buf[INPUTWIDTH+1];		// 6 bytes

	memset(buf,' ',INPUTWIDTH);
	buf[INPUTWIDTH] = 0;
	DispSt2(buf);
}


void ClsState12()
{
	char buf[SCREENWD-PROMDISPX+1];		//10 bytes

	memset(buf,' ',SCREENWD-PROMDISPX);
	buf[SCREENWD-PROMDISPX] = 0;
	DispStrXY(buf,PROMDISPX,STATELINE);
}

//clear l width at screen pos(x,y)
void ClsArea(BYTE x,BYTE y,BYTE l)
{
	char sBuf[SCREENWD+1];

	memset(sBuf,' ',SCREENWD);
	sBuf[l] = 0;
	DispStrXY(sBuf,x,y);
}

void SuspendScreen()
{
	WORD i,k,c,l;

	for (i=0;i<SCREENWD;i++)
		for (c=0;c<SCREENLN-1;c++)
			mDispCharXY(' ',i,c);

#if defined(DD_LOCK)
        l=(SCREENWD-strlen(Msg[SHKJSDING].str))/2;
        if (l>=SCREENWD) l=0;
		for (i=0;i<strlen(Msg[SHKJSDING].str);)
		{
			c = Msg[SHKJSDING].str[i];
			if (c==0)
				break;
			if (c>0x80)//ccr2015-05-08 0xa0 ��
				c |= (((WORD)Msg[SHKJSDING].str[i+1])<<8);
			mDispCharXY(c,l++,1);
			if (c>0x80)//ccr2015-05-08 0xa0 ��
            {
				i+=2;
                l++;
            }
			else
				i++;
		}

#else
	for (k = SHKJSDING;k<=AFSHSUO;k++)
    {
        l=(SCREENWD-strlen(Msg[k].str))/2;
        if (l>=SCREENWD) l=0;
		for (i=0;i<strlen(Msg[k].str);)
        {
            if (Msg[k].str[i]==0)
                break;
            c = Msg[k].str[i];
            if (c>0x80)//ccr2015-05-08 0xa0 ��
                c |= (((WORD)Msg[k].str[i+1])<<8);
            mDispCharXY(c,l++,k-SHKJSDING+1);
            if (c>0x80)//ccr2015-05-08 0xa0 ��
            {
                l++;
                i+=2;
            }
            else
                i++;
        }
    }
#endif
}
//ccr2016-01-25>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
char    SaveScreen[SCREENLN][SCREENWD];//������Ļ����
CURSOR SaveCursor;


void RecallScreen()
{
    int i;
    if (TESTBIT(ApplVar.ScreenStat,SCREENCOPY))
    {//�ָ���Ļ����
        memcpy(ApplVar.ScreenMap,SaveScreen,(SCREENLN-TESTBIT(ApplVar.ScreenStat,STATEON))*SCREENWD);
        RESETBIT(ApplVar.ScreenStat,SCREENCOPY);
        for (i=0;i<SCREENLN-TESTBIT(ApplVar.ScreenStat,STATEON);i++)
        {
            mRefreshLine(i);
        }
        if (TESTBIT(SaveCursor.y,BIT7))
        {
            RESETBIT(SaveCursor.y,BIT7);
            ApplVar.sCursor = SaveCursor;
        }

    }
}
//Ϊ��ʾ���뺺�ֱ�����Ļ����
//savCur:�Ƿ�ͬʱ�������
void BackupScreen(BYTE savCur)
{
    int i;
    if (!TESTBIT(ApplVar.ScreenStat,SCREENCOPY))
    {//������Ļ����
        if (savCur)
        {
            SaveCursor = ApplVar.sCursor;
            SETBIT(SaveCursor.y,BIT7);
        }
        memcpy(SaveScreen,ApplVar.ScreenMap,(SCREENLN-TESTBIT(ApplVar.ScreenStat,STATEON))*SCREENWD);
        mClearScreen();
/*ccr2016-01-25
        memset(ApplVar.ScreenMap,' ',(SCREENLN-TESTBIT(ApplVar.ScreenStat,STATEON))*SCREENWD);
        for (i=0;i<SCREENLN-TESTBIT(ApplVar.ScreenStat,STATEON);i++)
        {
            mRefreshLine(i);
        }
*/
        SETBIT(ApplVar.ScreenStat,SCREENCOPY);
    }
}
/**
 * �����������Ļ�����һ��,�ȹ�����Ļ,Ȼ�������һ����ʾ�ַ���
 *
 * @author EutronSoftware (2016-01-26)
 *
 * @param str
 */
void  DispLFStr(char *str)
{
    if (CursY>SCREENLN-(1+TESTBIT(ApplVar.ScreenStat,STATEON)))
    {
        ScreenFeed(1);
        CursY=SCREENLN-(1+TESTBIT(ApplVar.ScreenStat,STATEON));
        DispStrXY(str,0,0xff);
    }
    else
        DispStrLF(str)
}
//---------------------------------------------------------------------------

/**
 * �Ա������ʽ��״̬����ʾ����
 *
 * @author EutronSoftware (2016-03-01)
 *
 * @param str :Ҫ��ʾ���ַ���
 * @param x :��ʾλ��
 */
void DispOnStatDBL(char *str,BYTE x)
{
#if (SCRSTATDBL)
    char dispBuf[SCRDBLWD+1];
//    int slen=strlen(str);

//    if (slen>SCRDBLWD)
//        slen = SCRDBLWD;

//    memset(dispBuf,' ',SCRDBLWD);
//    memcpy(dispBuf,str,slen);
    strncpy(dispBuf,str,SCRDBLWD);
    dispBuf[SCRDBLWD]=0;
    mSetDBLDisp();
    DispStrXY(dispBuf,x,STATELINE);
    mClearDBLDisp();
#endif
}
