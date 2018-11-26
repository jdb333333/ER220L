#include "king.h"
#include "exthead.h"
#include "exth.h"

#if (CASE_EPOS)

#include "ePosCard.h"

TePOSRECORD ePosLastRec;


/* ��ePos��ȡһ���ֽڣ�����д����԰������ǿ�ƽ���  */
BYTE ReadePos(BYTE *frePos)
{
  	short fr,lp;

	for (lp=0;lp<5;lp++)
	{

		if(KbHit() && Getch() == ApplVar.AP.FirmKeys[ID_CLEAR])
				return false;

		fr = ReadComm(ApplVar.ePosPort-1);
		if (fr != -1)
		{
			*frePos = fr & 0xff;
			return true;
		}
	}
	return false;
}

void StringToBytes( BYTE *strSource, BYTE *ucTarget )
{
	WORD i;
	BYTE sByte,sByte1;

	for( i = 0; i < sizeof(TePOSRECORD); i++ )
	{
		sByte = *strSource ;
		switch( sByte & 0xF0)
		{
		case 0x30:
			sByte1 = (sByte & 0x0F);
			break;
		case 0x40:
		case 0x60:
			sByte1 = (( sByte & 0x07 ) + 0x09);
			break;
		default:
			sByte1 = 0x00;
		}
		sByte1 <<= 4;
		strSource++;
		sByte = *strSource;
		switch( sByte  & 0xF0)
		{
		case 0x30:
			sByte1 |=  ( sByte & 0x0F );
			break;
		case 0x40:
		case 0x60:
			sByte1 |=  ( ( sByte & 0x07 ) + 0x09 );
			break;
		}
		strSource++;
		*ucTarget = sByte1;
		ucTarget++;
	}
}

//---------------------------------------------------
signed char RecvACK()
{
	BYTE Resp[2],lp=0;

	Resp[1] = 0x00;
	do
	{
		Resp[0] = Resp[1];
		if(!ReadePos(Resp+1) || (lp++)>10)
			return FAILURE;
	}while( ( Resp[0] != DLE ) || ( Resp[1] != ACK ) );

	return SUCCESS;
}
//---------------------------------------------------------------
void SendENQ()
{
	BYTE ucENQ[2];

	ucENQ[0] = DLE;
	ucENQ[1] = ENQ;

	Bios_PortWrite(ApplVar.ePosPort, ucENQ, 2, 1);
}
//---------------------------------------------------------------
signed char RecvEOT()
{
	BYTE Resp[2],lp=0;

	Resp[1] = 0x00;
	do
	{
		Resp[0] = Resp[1];
        if(!ReadePos(Resp+1) || (lp++)>10)
        	return FAILURE;
	}while( ( Resp[0] != DLE ) || ( Resp[1] != EOT ) );

	return SUCCESS;
}
//---------------------------------------------------------------
void SendEOT()
{
	BYTE ucEOT[2];

	ucEOT[0] = DLE;
	ucEOT[1] = EOT;

	Bios_PortWrite(ApplVar.ePosPort, ucEOT, 2, 1);
}
//---------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  ���ս�ȡ���ݰ��е���Ϣ                                                   //
//                                                                           //
//  BYTE OMLRecvData( BYTE *RealMessage, WORD RLen )                         //
//                                                                           //
//  RealMessage	���ݰ��е���Ч����                                           //
//	RLen		���ݰ����������ȣ�����ΪRealMessage�Ĵ�С��0��ʾ��ETX����    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
signed char RecvData(BYTE *RealMessage, WORD *RLen )
{
	short i, PLen;
	BYTE VByte, PByte;

	PLen = 0;
	VByte = 0x00;
	for(i=0;i<10;i++)
	{
        if (!ReadePos(&PByte))
			return FAILURE;

		if (VByte==DLE && PByte==STX)
			break;
		else if (VByte==DLE && PByte==NAK)
			return RETRY;
		else
			VByte = PByte;
	}
	if (i>=10)
		return FAILURE;

	PLen = 0;
	while( 1 )
	{
		if (PLen>*RLen || !ReadePos(RealMessage+PLen))
			return FAILURE;

		if( RealMessage[PLen] == DLE )
		{
            if (!ReadePos(RealMessage+PLen + 1))
				return FAILURE;

			if( RealMessage[PLen + 1] == ETX )
				break;
			else if( RealMessage[PLen + 1] == DLE )
				{ PLen++; continue; }
			else PLen += 2;
		}
		else PLen++;
	}

    if(!ReadePos(&PByte))
		return FAILURE;

	VByte = 0x00;		/* Check Bit */
	for ( i = 0; i < PLen; i++ )
		VByte ^= RealMessage[i];
	VByte ^= ETX;

	if ( VByte != PByte )
		return CHECK_ERROR;

	*RLen = PLen;

	return SUCCESS;
}
//---------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  �����������                                                             //
//                                                                           //
//  void OMLSendData( BYTE *RealMessage, short RLen )                          //
//                                                                           //
//  ��ڲ�����RealMessage	���͵�����                                       //
//  	      RLen			���͵����ݳ���                                   //
//  ���ڲ�����DataPacket	����������                                     //
//  �� �� ֵ��PLen			���ݰ�����                                       //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
void SendDataePos(BYTE *RealMessage, short RLen )
{
	short i, PLen;
	BYTE VByte;
	BYTE DataPacket[24];

	DataPacket[0] = DLE;
	DataPacket[1] = STX;

	PLen = 2;
	VByte = 0x00;		/* Check Bit */
	for( i = 0; i < RLen; i++ )
	{
		if( RealMessage[i] == 0x10 )
		{
			DataPacket[PLen++] = RealMessage[i];
			DataPacket[PLen++] = RealMessage[i];
		}
		else
		{
			DataPacket[PLen++] = RealMessage[i];
		}
		VByte ^= RealMessage[i];
	}
	VByte ^= ETX;

	DataPacket[PLen++] = DLE;
	DataPacket[PLen++] = ETX;
	DataPacket[PLen++] = VByte;

	Bios_PortWrite(ApplVar.ePosPort, DataPacket, PLen, 1);
}
//---------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  Command Format( HOST -> C/R )                                            //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
signed char SendCMD(char *CMD, BYTE *Parameter, WORD Len, BYTE *Response, WORD *RespLen )
{
	BYTE ucSendBuffer[30];//, ucRecvBuffer[120];
	WORD i, lResult, lSendLength, lRecvLength,maxLen=*RespLen;


	ucSendBuffer[0] = 0x43;		// 'C'
	ucSendBuffer[1] = CMD[0];
	ucSendBuffer[2] = CMD[1];

	if( Len != 0 )
		memcpy(	ucSendBuffer + 3, Parameter, Len );

	lSendLength = Len + 3;

	EmptyComm(ApplVar.ePosPort-1);

	for( i = 0; i < 3; i++ )
	{
		SendENQ();

		if( RecvACK() == SUCCESS )
				break;
	}
	if (i>=3)
		return FAILURE;

	EmptyComm(ApplVar.ePosPort-1);

	while( 1 )
	{
		SendDataePos(ucSendBuffer,lSendLength);
        lRecvLength = maxLen;
		if( ( lResult = RecvData(SysBuf, &lRecvLength ) ) == SUCCESS )
			break;
		else if( lResult == RETRY )
			continue;
		else
			return FAILURE;
	}

	switch( SysBuf[0] )
	{
	case 'N':
		*RespLen = 0;
		return CMD_NEGATIVE;
	case 'P':
		memcpy( Response, SysBuf + 5, lRecvLength - 5 );	//Return Response data
		*RespLen = lRecvLength - 5;
		return CMD_POSITIVE;
	default:
		*RespLen = 0;
		return FAILURE;
	}
}
//------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  ȡPOS����״̬                                                            //
//                                                                           //
//  BYTE GetPosStatus( HANDLE PortHandle, WORD *Status )                     //
//                                                                           //
//  ��ڲ�����                                                               //
//		PortHandle;  �˿ھ��                                                //
//  ���ڲ�����                                                               //
//		Status:	ϵͳ���ص�POS״̬                                            //
//			0	ϵͳ����                                                     //
//			1	�ȴ�����                                                     //
//			2	������ɣ�����ȷ�Ͻ���                                       //
//			3	������                                                   //
//			4 	���Ѿ�����                                                   //
//			5	��������                                                     //
//			6	�Ƿ���                                                       //
//			7	�𻵿�                                                       //
//			8	������ɣ��ȴ�ȡ��                                           //
//  �� �� ֵ��                                                               //
//		0	����                                                             //
//  	<>0	ʧ��                                                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
signed char GetPosStatus(BYTE *Status )
{
	WORD ulRespLen;
	BYTE ucRespData[20];

	ulRespLen = 15;
	switch( SendCMD("00", NULL, 0, ucRespData, &ulRespLen ) )
	{
	case CMD_POSITIVE:
		break;
	case CMD_NEGATIVE:
	default:
		return FAILURE;
	}

	*Status = ( ucRespData[0] - 0x30 ) * 10 + ( ucRespData[1] - 0x30 );

	return SUCCESS;
}
//------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  ȡ���׵Ŀ���                                                             //
//                                                                           //
//  BYTE GetTransCardNo( HANDLE PortHandle, BYTE *CardNo )                   //
//                                                                           //
//  ��ڲ�����                                                               //
//		PortHandle;  �˿ھ��                                                //
//  ���ڲ�����                                                               //
//		CardNo; 10 λΪ�����                                                //
//  �� �� ֵ��                                                               //
//		0	����                                                             //
//		-1	ϵͳ��ʱ                                                         //
//		1	ϵͳæ                                                           //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
/*
BYTE GetTransCardNo(BYTE *CardNo )
{
	WORD ulRespLen;
	BYTE ucRespData[20];

	ulRespLen = 18;
	switch( SendCMD("01", NULL, 0, ucRespData, &ulRespLen ) )
	{
	case CMD_POSITIVE: break;
	case CMD_NEGATIVE:
	default: return FAILURE;
	}

	memset( CardNo, 0x00, 11 );
	memcpy( CardNo, ucRespData, ulRespLen );

	return SUCCESS;
}
*/
//------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  POS����������ȡ��Ȼ��ȴ��û�ˢ��                                    //
//                                                                           //
//  BYTE UpdateTransAmount( HANDLE PortHandle, WORD *Amount )                //
//                                                                           //
//  ��ڲ�����                                                               //
//		PortHandle;  �˿ھ��                                                //
//  ���ڲ�����                                                               //
//		Amount;	��������ȡ���                                               //
//  �� �� ֵ��                                                               //
//		0	����                                                             //
//		-1	ʧ��                                                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
signed char UpdateTransAmount(BCD *Amount )
{
	WORD ulRespLen;
	BYTE sSing = Amount->Sign;
	BYTE ucParamData[40], ucRespData[40];

	memset(ucParamData,'0',sizeof(ucParamData));
	Amount->Value[7] = Amount->Value[6] = Amount->Value[5] = Amount->Value[4] = 0;
	Amount->Sign &= 0x7f;
	FormatQty(ucParamData+7, Amount);
	Amount->Sign &= sSing;

	ulRespLen = 15;
	switch( SendCMD("02", ucParamData, 8, ucRespData, &ulRespLen ) )
	{
	case CMD_POSITIVE:
		break;
	case CMD_NEGATIVE:
	default:
		return FAILURE;
	}

	return SUCCESS;
}
//------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  ͨ����ȡPOS״̬������Ѿ���������������ȷ�ϴ˽���                        //
//                                                                           //
//  BYTE UpdateTransComfirm( HANDLE PortHandle )                             //
//                                                                           //
//  ��ڲ�����                                                               //
//		PortHandle;  �˿ھ��                                                //
//  ���ڲ�������                                                             //
//  �� �� ֵ��                                                               //
//		0	����                                                             //
//		-1	ʧ��                                                             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
signed char UpdateTransComfirm()
{
	WORD ulRespLen;
	BYTE ucRespData[20];

	ulRespLen = 15;
	switch( SendCMD("04", NULL, 0, ucRespData, &ulRespLen ) )
	{
	case CMD_POSITIVE:
		break;
	case CMD_NEGATIVE:
	default:
		return FAILURE;
	}

	return SUCCESS;
}
//------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  ������δȷ��ʱ,����ʹ�ô˽���ȡ������                                    //
//                                                                           //
//  BYTE CancelTrans( HANDLE PortHandle )                                    //
//                                                                           //
//  ��ڲ�����                                                               //
//		PortHandle;  �˿ھ��                                                //
//  ���ڲ�������                                                             //
//  �� �� ֵ��                                                               //
//		0	�����ɹ�                                                         //
//		-1	����ʧ��                                                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
signed char CancelTrans()
{
	WORD ulRespLen;
	BYTE ucRespData[20];

	ulRespLen = 15;
	switch( SendCMD("05", NULL, 0, ucRespData, &ulRespLen ) )
	{
	case CMD_POSITIVE:
		break;
	case CMD_NEGATIVE:
	default:
		return FAILURE;
	}

	return SUCCESS;
}
//------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  ȡ���һ�ʽ��׼�¼                                                       //
//                                                                           //
//  BYTE GetLastTrans( HANDLE PortHandle, TRECORD *Rec )                     //
//                                                                           //
//  ��ڲ�����                                                               //
//		PortHandle;  �˿ھ��                                                //
//  ���ڲ�����                                                               //
//		Rec;	�������ݽṹ                                                 //
//  �� �� ֵ��                                                               //
//		0	�ɹ�                                                             //
//		-1	ʧ��                                                             //
//		1	�޽��׼�¼                                                       //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
signed char GetLastTrans()
{
	WORD ulRespLen;
	BYTE ucRespData[150];

	memset(ucRespData,0,sizeof(ucRespData));

	ulRespLen = sizeof(ePosLastRec)*2 + 15;
	switch( SendCMD("03", NULL, 0, ucRespData, &ulRespLen ) )
	{
	case CMD_POSITIVE:
		break;
	case CMD_NEGATIVE:
	default:
		return FAILURE;
	}

	StringToBytes( ( char * )ucRespData,(char *)&ePosLastRec);
	return SUCCESS;
}
//--------------------------------------------------
/**************************************************************************/
/* �ӿں��� BYTE PayByECard(BCD *Amount) */
/* ִ��һ������������                                                     */
/* Amount :BCD   ������                                                 */
/* �ɹ����� SUCCESS,�� ePosLastRec�ͳ����������                        */
/* ʧ�ܷ���                                                               */
/* BUSY          POSæ                                                    */
/* TRANSAMTERR   ���ͽ���                                               */
/* TRANSCOMFERR  ȷ�Ͻ��״�                                               */
/* NOCARD        �������,��ȡ�������Ѿ�ȡ�ߣ�                        */
/* OVERTIME      �ȴ���ʱ                                                 */
/* OUTTIME		 ���ڿ�													  */
/* BLOCKCARD	 ��������                                                 */
/* WRONGCARD	 ��E��ͨ��                                                */
/* BROKENCARD	 �𻵿�                                                   */
/* SIGNONNEEDED	 δǩ��                                                   */
/**************************************************************************/
signed char PayByePosCard(BCD *Amount)
{
    	BYTE retry,Status;

//ccr2016-03-02		PutsO(Msg[WAITEPOS].str);//C-DISPLAY

        if(GetPosStatus(&Status) == FAILURE || Status != VACANCY)//free?
        	switch(Status)
        	{
        		case NEEDSIGNON:
        			return SIGNONNEEDED;
        		default:
        			return BUSY;
        	}

        if(UpdateTransAmount(Amount) == FAILURE)
            return TRANSAMTERR;

        Delay(ePOSDELAY);
		for (retry=0;;)
		{
	        if (GetPosStatus(&Status) == FAILURE || Status != READFINISH)
	        {
				if (Status==LOWAMT || ++retry>50 || KbHit() && (Getch() == ApplVar.AP.FirmKeys[ID_CLEAR]))
				{
					Bell(2);//���У�����   //
					CancelTrans();
					return FAILURE;
				}
	        }
			else
				break;
		}

        if(UpdateTransComfirm() == FAILURE)
       	{
			CancelTrans();
            return TRANSCOMFERR;
       	}

        if(GetPosStatus(&Status) == SUCCESS && (Status == VDFINISH || Status == BALANCEFAILD))//complete
        {
	        Delay(ePOSDELAY);
//			memset(&ePosLastRec,0,sizeof(ePosLastRec));
            if (GetLastTrans()!=SUCCESS)
				memset(&ePosLastRec,0,sizeof(ePosLastRec));
			else
				Bell(0);
		    return SUCCESS;
        }
        else
		    return FAILURE;
}
/**************************************************************************/
/* ��ӡePos������֤�� 													  */
/**************************************************************************/
void PrintePosTAC()
{
	BYTE i;
	BCD	theLast,theCurr;


	memset(SysBuf,' ',sizeof(SysBuf));
//	CopyFrStr(SysBuf, Msg[ePOSTAC].str);
	HEXtoASC(SysBuf+6,ePosLastRec.TAC,4);
	RJPrint(0,SysBuf);


	memset(SysBuf,' ',sizeof(SysBuf));
	CopyFrStr(SysBuf, Msg[ePOSCARNO].str);

	i = ePosLastRec.CardNum[0];	ePosLastRec.CardNum[0] = ePosLastRec.CardNum[4];ePosLastRec.CardNum[4] = i;
	i = ePosLastRec.CardNum[1];	ePosLastRec.CardNum[1] = ePosLastRec.CardNum[3];ePosLastRec.CardNum[3] = i;

	HEXtoASC(SysBuf+10,ePosLastRec.CardNum,5);
	i = SysBuf[10];	SysBuf[10] = SysBuf[14];SysBuf[14] = i;
	i = SysBuf[11];	SysBuf[11] = SysBuf[13];SysBuf[13] = i;
	i = SysBuf[12];	SysBuf[12] = SysBuf[17];SysBuf[17] = i;
	i = SysBuf[15];	SysBuf[15] = SysBuf[19];SysBuf[19] = i;
	i = SysBuf[16];	SysBuf[16] = SysBuf[18];SysBuf[18] = i;
	for (i=10;i<10+10;i++)
	{
		if (SysBuf[i]=='9')
			SysBuf[i] = '0';
		else if (SysBuf[i]=='0')
			SysBuf[i] = '9';
		else if (SysBuf[i] & 1)
			SysBuf[i]++;
		else
			SysBuf[i]--;
	}
	RJPrint(0,SysBuf);

    theLast = theCurr = ZERO;

	theCurr.Value[0] = ePosLastRec.BalBef[3];//����ǰ��� //
	theCurr.Value[1] = ePosLastRec.BalBef[2];//����ǰ��� //
	theCurr.Value[2] = ePosLastRec.BalBef[1];//����ǰ��� //
	theCurr.Value[3] = ePosLastRec.BalBef[0];//����ǰ��� //

	theLast.Value[0] = ePosLastRec.TxnAmt[3];//���׽�� //
	theLast.Value[1] = ePosLastRec.TxnAmt[2];//���׽�� //
	theLast.Value[2] = ePosLastRec.TxnAmt[1];//���׽�� //
	theLast.Value[3] = ePosLastRec.TxnAmt[0];//���׽�� //

	Subtract(&theCurr, &theLast);
	RJPrint(0,FormatAmtStr(Msg[eCARREMAIN].str, &theCurr, PRTLEN));

}
#endif
