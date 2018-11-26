/*****************************************************/
/********************* ePosCard.h ***********************/
/*****************************************************/
//---------------------------------------------------------------------------
#if (CASE_EPOS)

#if defined(DEBUGBYPC)
#pragma option -a1
#else
#pragma pack(1)
#endif


#ifndef EPOS_H
#define EPOS_H

#define ePOSDELAY		800

#define DLE				0x10
#define STX				0x02
#define ETX				0x03
#define ENQ				0x05
#define ACK				0x06
#define NAK				0x15
#define EOT				0x04

//Define the return type of Command
#define CMD_POSITIVE	0
#define CMD_NEGATIVE	1

#define SUCCESS			0
#define FAILURE			-1
#define RETRY			-2
#define CHECK_ERROR		-3

//error
#define	BUSY 	        73					/* POSæ */
#define TRANSAMTERR     (BUSY + 1)			/* ���ͽ��� */
#define TRANSCOMFERR    (TRANSAMTERR + 1)	/* ȷ�Ͻ��״� */
#define NOECARD          (TRANSCOMFERR + 1)	/* ������ɣ���ȡ�������Ѿ�ȡ�ߣ�*/
#define OVERTIME        (NOECARD + 1)		/* �ȴ���ʱ */
#define OUTTIME			(OVERTIME + 1)		/* ���ڿ� */
#define BLOCKCARD		(OUTTIME + 1)		/* �������� */
#define WRONGECARD		(BLOCKCARD + 1)		/* ��E��ͨ�� */
#define BROKENCARD		(WRONGECARD + 1)		/* �𻵿� */
#define SIGNONNEEDED	(BROKENCARD + 1)	/* δǩ�� */
#define LOWAMTERR		(SIGNONNEEDED + 1)	/* δǩ�� */

#define WAITTIME		2 * 1000

//pos state
#define	VACANCY		0x00	/* ϵͳ���� */
#define	WAITFORCARD	0x01	/* �ȴ����� */
#define	READFINISH	0x02	/* ������ɣ�����ȷ�Ͻ��� */
#define	LOWAMT		0x03	/* ������ */
#define	OUTDATE		0x04	/* ���Ѿ����� */
#define	BLOCKED		0x05	/* �������� */
#define NOTECARD	0x06    /* �Ƿ�������E��ͨ�� */
#define	BROKEN		0x07	/* �𻵿����޷��޸��Ŀ� */
#define	VDFINISH	0x08	/* ������ɣ��ȴ�ȡ�� */
#define	BALANCEFAILD	0x09/* ������ɣ��������ʧ�ܣ����ܲ����µ㿨 */
#define	NEEDSIGNON 	0x10	/* δǩ�� */

//error
#define	BUSY 	        73
#define TRANSAMTERR     (BUSY + 1)
#define TRANSCOMFERR    (TRANSAMTERR + 1)
#define NOCARDE          (TRANSCOMFERR + 1)
#define OVERTIMER        (NOCARDE + 1)


typedef struct
{
	unsigned char Corpld[6];		//��Ӫ��λ���� //
	unsigned char Brhld[3];			//������ //
	unsigned char Oprld[5];			//����Ա�� //
	unsigned char TxnType[1];		//�������� //
	unsigned char Posld[4];			//POS�������� //
	unsigned char PosSeq[3];		//POS ��ˮ�� //
	unsigned char CardNum[5];		//���� //
	unsigned char CardKind[1];		//������ //
	unsigned char BalBef[4];		//����ǰ��� //
	unsigned char TxnAmt[4];		//���׽�� //
	unsigned char TxnDate[4];		//�������� //
	unsigned char TxnTime[3];		//����ʱ�� //
	unsigned char TxnCounter[3];		//���׼����� //
	unsigned char TAC[4];			//������֤�� //
} TePOSRECORD; //�������ݽṹ //

extern signed char PayByePosCard(BCD *Amount);
extern void PrintePosTAC();

#endif
#endif
