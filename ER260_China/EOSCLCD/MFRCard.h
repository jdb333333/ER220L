/********************* M1Card.h ************************/

#ifndef MFRCARD_H
#define MFRCARD_H
//---------------------------------------------------------------------------
#define MFR_CTS             1   //ccr2014-08-26 ʹ�ô���CTS������Ƿ�����Ƶ��

#define MFRPORT				3			//cc 060321 MF ������

#define MFRBLOCKSIZE		16	//  ÿ�ζ�ȡ�����ݿ���ֽ���   //

#define CommandBit			0x42	//��������֮ǰ�ȷ�'B'
                                    //
#define CMD_Read_SN1		1		//�������к�
#define CMD_Read_SN2		0x59	//�������к�
                                    //
#define CMD_Read_Block		14		//������
#define CMD_Write_Block		30		//д����
                                    //
#define REC_Read_SN			5		//�������кŷ���
                                    //
#define REC_Read_Block		17		//�����ݷ���
#define REC_Write_Block1	1		//д���ݷ���
#define REC_Write_Block2	0x59	//д���ݷ���

#define CMD_Read_MFR1		1		//����״̬
#define CMD_Read_MFR2		0xC0	//����״̬


#define RW_Factory			0
#define RW_Flags			1
#define RW_Init				2
#define RW_Customer			3
#define RW_Valatt			4
#define RW_Valpre			5
#define RW_Facpre			6		//cc 20070825
#define RW_ALL				7

#define CLOGINCARD  		82641937L	// ���� //
#define MAKECARD			0
#define CHARGECARD			1
#define CLEARCARD			2

#define EMIDHEAD			0x02


BYTE SendRecordBySPI(BYTE *p,BYTE length);
BYTE ReadRecordBySPI(BYTE *p,BYTE length);
BYTE SendByteBySPI(BYTE p);
WORD ReadByteBySPI();
BYTE CC_WriteMFR(char *Source,BYTE ChipAdr);
BYTE CC_ReadMFR(char *Dest,BYTE ChipAdr);
BYTE CC_Request(void);
BYTE CC_MFRCard(void);
void GetValue(BYTE ChipAdr);

#endif