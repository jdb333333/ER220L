//-----------------------------------------------
// File : BIOS_DIR.H
//       -----------
//---------------------------------------------
//CASE_ER220 = 0
//---------------------------------------------
//
#ifndef BIOS_DIR_H
#define BIOS_DIR_H

//#if defined(STM32F10X_HD)
//#define  STM32F10X_HD_USBCOMM
//#endif

//#define DD_LOCK		0		//For 520 �Ƿ����÷�ʽ�� //

//#define CASE_GPRS		0		//FOR GPRS MODEL..090815

#if defined(CASE_ETHERNET)
#define TCPIP		    1		//change to open TCP/IP FUNCTION .FROM 0->1
#endif

//------------------------------------------------------------------------
#if (defined(DEBUGBYPC))

//#define CASE_ER220		1		            // 	;���ô��д�ӡ�ֿ� //
#define CASE_ER260		    1		// 	;���ô��д�ӡ�ֿ� //
//#define CASE_ER520U		0		// 	;���ò����ֿ�,��ʾ�ֿ����ӡ�ֿ����ͬһоƬ,��portW2���� //
//#define CASE_GIADA3000    0

//#define CASE_INDONESIA    1       //ӡ�������ǰ汾

#if defined(CASE_INDONESIA)
#define CASE_GPRS		1		//FOR GPRS MODEL..090815
#else
//#define CASE_FORHANZI	1		// �Ƿ�֧�ֺ��ִ�ӡ //
#endif

#endif

//#define CASE_SPANISH    0       // �Ƿ�Ϊ��������汾

//--------------------------------------------------------------------------

// Definizioni riguardanti l'hardware

#define DD_S1245		0
#define DD_FTP628		1
#define DD_Z245		0

//-------------------------------------------------

#define	DD_CUTTER	    1	//1 = con taglierina automatica
//------------------------------------------------------------------------------
#if defined(CASE_FORHANZI)
#define EN_EXASCII      0   //���ַ�ʽ�£���ֹ��չASCII���뷽ʽ
#else
#define EN_EXASCII      1   //Ӣ�İ汾��������չASCII���뷽ʽ
#endif

//--------------------------------------------------------
#ifdef CASE_GPRS
#define DD_CHIPC		0		//IC��ģ���GPRSģ�鹫��һ���˿�
#else
#define DD_CHIPC		1		//ccr chipcard	//1 = SI gestione chip-card
#endif

#define DD_ECRVIP       1       //ccr2016-05-13 ����ECRVIP��Ա����(�ر�����)

#if defined(DEBUGBYPC)
#define CASE_MFRIC		0		//mifare RFIC,PCƽ̨�½�ֹMFRIC
#else
#define CASE_MFRIC		1		//mifare RFIC,������DD_CHIPC��,CASE_MFRIC��������Ƶ�����ǽӴ���
#endif

#if (CASE_MFRIC==1)
#define DD_4442IC		0
#else
#define DD_4442IC		1
#endif

#define B_SIOF_TX	     0	//bit 0 : 1 = In atto tasmissione di un blocco
#define B_SIOF_PWFL	     9	//bit 9  : riservato per segnalazione pwfl in RX      (NON MODIFICARE !)
#define B_SIOF_TMORX	 10	//bit 10 : riservato per segnalazione time-out in RX  (NON MODIFICARE !)
#define B_SIOF_OVFL	     11	//bit 11 : 1 = Rx buffer in overflow		     (NON MODIFICARE !)
#define B_SIOF_OVERRUN	 12	//bit 12 : Rilevati errori di overrun                 (NON MODIFICARE !)
#define B_SIOF_FRAME	 13	//bit 13 : Rilevati errori di frame                   (NON MODIFICARE !)
#define B_SIOF_PARITY	 14	//bit 14 : Rilevati errori di parita'                 (NON MODIFICARE !)
#define B_SIOF_ERRORS	 15	//bit 15 : OR dei bit di errore                       (NON MODIFICARE !)



#define CASE_EPOS			0	//=1,�������ô�ֵ�����и���

#if defined(STM32F10X_HD)
#define CASE_USBDISK		0	//=1,����U�̹���
#else
#define CASE_USBDISK		1	//=1,����U�̹���
#endif


/* Central Lock Codes as used by the MA  register */
/* now also used for KT because KT translated to MA  */

#endif
