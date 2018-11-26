#define FORMAT_C
#include "king.h"
#include "exthead.h"


//------------------------------------------------------------
//��amt������ת��Ϊ�ַ���
//����˵��:toָ���ַ����洢��,ת����������ɺ���ǰ�洢
//"                         "
//                   <--to_^
//------------------------------------------------------------
void FormatAmt(char *to,BCD *amt)
{
    WORD format;

    format = BCDLEN * 2;

/*Decimal Length depend on the Format.15 and Format.11
.15   .11   Decimal Length    Need Comma List Separator.
 1     1   1                    Y
 1     0   3                    Y
 0     0   2                    Y
 0     1   0                    N
*/

    if (ApplVar.AmtDecimal == 1) /* no decimal in amount ? */
	    format |= 0x0800;   //Decimal Length=0 (bit11)
    else if (ApplVar.AmtDecimal == 2)
	    format |= 0x8000;   //Decimal Length=3 (bit15)
	else if (ApplVar.AmtDecimal == 3)
		format |= 0x8800;   //Decimal Length=1 (bit15,bit11)

    if (TESTBIT(COMMA, BIT0)) /* comma instead of point */
	    format |= 0x1000;		//bit12
    FormatBCD(to, amt, format);
}
//------------------------------------------------------------
//��qty������ת��Ϊ�ַ���
//����˵��:toָ���ַ����洢��,ת����������ɺ���ǰ�洢
//"                         "
//                   <--to_^
//------------------------------------------------------------
void FormatQty(char *to ,BCD *qty )
{
    FormatBCD(to, qty, (BCDLEN * 2) + 0x6400);
}

//��str��BCD ���ݰ�ָ����ʽ�������,����Ϻ�Ľ����SysBuf�ͳ�//
char *FormatAmtStr(CONSTCHAR *str ,BCD *amt,short width )
{
	short slen,i,sHZRight;

    MemSet(SysBuf, width, ' ');
	SysBuf[width] =  0;
    FormatAmt(SysBuf + width - 1, amt);

	sHZRight = 0;
    if (str && str[0])    /* copy string ? */
	{
		slen = strlen(str);
		if (slen > width)
			slen = width;
#if defined(CASE_FORHANZI)
		while (SysBuf[slen -1]!=' ' && slen)
			slen--;
		for (i=0;i<slen;)//for double with of HANZI
		{
			if (str[i]=='~' && str[i+1]>160 && str[i+2]>160)
			{
				sHZRight++;
				i += 3;
			}
			else
				i++;
		}
		for (i=0;i<slen && SysBuf[i+sHZRight]==' ';i++)
			SysBuf[i+sHZRight] = str[i];
#else
		for (i=0;i<slen && SysBuf[i+1]==' ';i++)
			SysBuf[i] = str[i];
#endif
	}
#if defined(CASE_FORHANZI)
	SysBuf[width + sHZRight] =  0;
	return(SysBuf + sHZRight);
#else
	return(SysBuf);
#endif
}

//��str��BCD ���ݰ�ָ����ʽ�������,����Ϻ�Ľ����SysBuf�ͳ�//
char *FormatQtyStr(CONSTCHAR *str,BCD *qty,short width)
{
	short slen,i,sHZRight;

    MemSet(SysBuf, sizeof(SysBuf), ' ');
	SysBuf[width] =  0;
    FormatQty(SysBuf + width - 1, qty);

	sHZRight = 0;
    if (str && str[0])    /* copy string ? */
	{
		slen = strlen(str);
		if (slen > width)
			slen = width;
#if defined(CASE_FORHANZI)
		while (SysBuf[slen -1]!=' ' && slen)
			slen--;
		for (i=0;i<slen;)//for double with of HANZI
		{
			if (str[i]=='~' && str[i+1]>160 && str[i+2]>160)
			{
				sHZRight++;
				i += 3;
			}
			else
				i++;
		}
		for (i=0;i<slen && SysBuf[i+sHZRight]==' ';i++)
			SysBuf[i+sHZRight] = str[i];
#else
		for (i=0;i<slen && SysBuf[i+1]==' ';i++)
			SysBuf[i] = str[i];
#endif
	}
#if defined(CASE_FORHANZI)
	SysBuf[width + sHZRight] =  0;
	return(SysBuf + sHZRight);
#else
	return(SysBuf);
#endif
}

//��str��BCD ���ݰ�ָ����ʽ�������,����Ϻ�Ľ����SysBuf�ͳ�//
char *DispQtyStr(CONSTCHAR *str ,BCD *qty,short width )
{
    short slen;

    MemSet(SysBuf, sizeof(SysBuf), ' ');

    if (str && str[0])    /* copy string ? */
	{
		slen = strlen(str);
		if (slen > width)
			slen = width;
		memcpy(SysBuf + sizeof(SysBuf) - width-1, str, slen);
	}
    FormatQty(SysBuf + sizeof(SysBuf) - 2, qty);
	SysBuf[sizeof(SysBuf)-1]=0;
	return((char*)SysBuf + sizeof(SysBuf)- width-1 );//ccr2016-10-13 "DISLEN"==>"width"
}

//��str��BCD ���ݰ�ָ����ʽ�������,����Ϻ�Ľ����SysBuf�ͳ�//
char *DispAmtStr(CONSTCHAR *str,BCD *amt,short width)
{
    short  slen;
    WORD format;

    MemSet(SysBuf, sizeof(SysBuf), ' ');
    if (str && str[0])    /* copy string ? */
	{
		slen = strlen(str);
		if (slen > width)
			slen = width;
		memcpy(SysBuf + sizeof(SysBuf) - width-1, str, slen);
	}
    format = BCDLEN * 2;

/*Decimal Length depend on the Format.15 and Format.11
.15   .11   Decimal Length    Need Comma List Separator.
 1     1   1                    Y
 1     0   3                    Y
 0     0   2                    Y
 0     1   0                    N
*/
    if (ApplVar.AmtDecimal == 1) /* no decimal in amount ? */
		format |= 0x0800;
    else if (ApplVar.AmtDecimal == 2)
		format |= 0x8000;
    else if (ApplVar.AmtDecimal == 3)
		format |= 0x8800;
    if (TESTBIT(COMMA, BIT0)) /* comma instead of point */
		format |= 0x1000;
    format |= 0x6000;       /* no prefix and not extended */
    FormatBCD(SysBuf+sizeof(SysBuf) - 2, amt, format);
    SysBuf[sizeof(SysBuf) - 1]=0;

	return(SysBuf + sizeof(SysBuf)- width-1);//ccr2016-10-13 "DISLEN"==>"width"
}

//��str��BCD ���ݰ�ָ����ʽ�������,����Ϻ�Ľ����SysBuf�ͳ�//
char *FormatStrQtyPriAmt(CONSTCHAR *str,BCD *qty,BCD *pri,BCD *amt,short width)
{
	short slen,i,sHZRight;

    MemSet(SysBuf, sizeof(SysBuf), ' ');
	SysBuf[width] =  0;
    FormatAmt(SysBuf +width - 1, amt);
    if (pri)
    {
	    FormatAmt(SysBuf + 22 + pSHIFTx, pri);
	    i = 13;
	}
	else
		i = 19;
	if(qty)
        FormatQty(SysBuf + i + (pSHIFTx>>1), qty);

	sHZRight = 0;
    if (str && str[0])    /* copy string ? */
	{
		slen = strlen(str);
		if (slen > width)
			slen = width;
#if defined(CASE_FORHANZI)
		for (i=0;i<slen;i++)
			if (SysBuf[i]!=' ') break;
		slen = i;
		for (i=0;i<slen;)//for double with of HANZI
		{
			if (str[i]=='~' && str[i+1]>160 && str[i+2]>160)
			{
				sHZRight++;
				i += 3;
			}
			else
				i++;
		}
		for (i=0;i<slen && SysBuf[i+sHZRight]==' ';i++)
			SysBuf[i+sHZRight] = str[i];
#else
		for (i=0;i<slen && SysBuf[i+1]==' ';i++)
			SysBuf[i] = str[i];
#endif
	}
#if defined(CASE_FORHANZI)
	SysBuf[width + sHZRight] =  0;
	return(SysBuf + sHZRight);
#else
	return(SysBuf);
#endif
}

