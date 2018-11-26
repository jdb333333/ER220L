/***************************************************************************
  ���ļ�Ϊ����ƽ̨�Ľӿ�˵���ļ�,���û�Ӧ���п�ֱ�Ӱ���ʹ�ô��ļ�
  ���ø�������APIʵ����Ҫ�Ĺ���.
  1.ϵͳ����1 API ����
  2.��ӡ API
  3.���� API ����
  4.ϵͳ����2 API ����
  5.SD�� API ����
  6.��ʾ API ����
  7.Fiscal memory API
  8.Flash memory API
  9.���̶�ȡ API
  10.USB ͨ�� API
****************************************************************************/

/**
 * �������Ͷ���
 */
#define BYTE 	unsigned char
#define WORD 	unsigned short
#define ULONG 	unsigned long
#define DWORD 	unsigned long


//---- same as stm32f10x.h ------------
#define uint8_t    unsigned char
#define uint16_t   unsigned short
#define uint32_t   unsigned long

//
#define BIT0	0x01
#define BIT1	0x02
#define BIT2	0x04
#define BIT3	0x08
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80

#define BIT8	0x0100
#define BIT9	0x0200
#define BIT10	0x0400
#define BIT11	0x0800
#define BIT12	0x1000
#define BIT13	0x2000
#define BIT14	0x4000
#define BIT15	0x8000

#define BIT16	0x010000l
#define BIT17	0x020000l
#define BIT18	0x040000l
#define BIT19	0x080000l
#define BIT20	0x100000l
#define BIT21	0x200000l
#define BIT22	0x400000l
#define BIT23	0x800000l

#define BIT24	0x01000000l
#define BIT25	0x02000000l
#define BIT26	0x04000000l
#define BIT27	0x08000000l
#define BIT28	0x10000000l
#define BIT29	0x20000000l
#define BIT30	0x40000000l
#define BIT31	0x80000000l

//type define for date (BCD, 4 bytes) :
typedef struct{
	 	BYTE dd;	//Day
	 	BYTE mm;	//Month
	 	BYTE yy;	//Year
	 	BYTE w;		//week day
} DATE_BCD;


//type define for time (BCD, 4 bytes) :
typedef struct{
	 	BYTE hh;	//Hour
	 	BYTE mm;	//minute
	 	BYTE ss;	//second
	 	BYTE w;   	//dummy : used to have even align
} TIME_BCD;

//-----------------------

extern DATE_BCD rtc_date;          //buffer for get/set date current
extern TIME_BCD rtc_time;          //buffer for get/set time current

//-------------------------------------------------------------------
// ��ӦAPI Bios��������

#define BiosCmd_ClrFip0		    15	//close LED
#define BiosCmd_AutoClickOff    23	//Disable AutoClick
#define BiosCmd_AutoClickOn	    24	//Enable AutoClick
#define BiosCmd_BuzzS		    25	//Buzzer short
#define BiosCmd_BuzzM		    26	//Buzzer medium
#define BiosCmd_BuzzL		    27	//Buzzer long
#define BiosCmd_CheckKeyborad	29	//check keyboard


#define	BiosCmd_PrintCheck	    61	//����ӡ��״̬
#define BiosCmd_ResetCutter	    63	//��λ�е�
#define BiosCmd_PrintGraph	    68	//��ӡͼƬ
#define BiosCmd_PrintX		    70	//��ӡ�ַ���


#define BiosCmd_GetDate		    80	//RTC: read date
#define BiosCmd_GetTime		    81	//RTC: read time
#define BiosCmd_SetDate		    82	//RTC: set date
#define BiosCmd_SetTime		    83	//RTC: set time

//-----------------------------------------------------------------------------------

//for SD card>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define	BiosCmd_SD_Init			92	//Initializ MMC
#define	BiosCmd_SD_ReadBlock	93	//Raead block
#define	BiosCmd_SD_ReadInfo		94	//Read CID/CSD/PROT/STATUS
#define	BiosCmd_SD_WriteBlock	95	//Write block
#define	BiosCmd_SD_Erase		97	//Erase groups
#define BiosCmd_SD_CheckPresence 101 //���SD���Ƿ����

//--------------------1.ϵͳ���� API ����------------------------------

/** STM32_Initial
 *  ��ϵͳ���г�ʼ��
 *  1.�δ�ʱ��SysTickÿ1ms�ж�һ��
 *  2.�����д��ڳ�ʼ��Ϊ115200/8/1/n
 *  3.��Ӳ���˿ڳ�ʼ��:HW_GPIOInit();
 *  4.�Դ洢�����г�ʼ��
 *  5.����ʾ���г�ʼ��
 *  6.ϵͳʱ�ӳ�ʼ��
 *  7.Timer5/Timer6��ʼ��
 *  8.˰�ش洢����ʼ��
 *  9.SD����ʼ��
 *  10.USB���ܳ�ʼ��
 */
void STM32_Initial(void);

/** Bios**************************************************************
 *
 * ʹ�ö��������ϵͳ����
 * @param cmd:����
 * @param ptr:ָ���ַ�������
 * @param par1:ָ������1
 * @param par2:ָ������2
 *
 * @return WORD:true-����ִ�гɹ�;false-����ִ��ʧ��
 ****************************************************************** */
WORD Bios(WORD cmd, void  *ptr, WORD par1, WORD par2);
/* �������Ҫ�Ĳ�������
    BiosCmd_SD_Erase:����SD������GROUP_H*65536+GROUP_L��ָ�����������, SD����Ļ�����Ҫ�μ�����ֲ�
        Example: Bios(BiosCmd_SD_Erase, (far char*)SourceBuff, (WORD)GROUP_L, (WORD)GROUP_H )
    BiosCmd_SD_ReadInfo:��ȡSD����CID��CSD,����sBuf��
        Example: Bios(BiosCmd_SD_ReadInfo, (char*)sBuf, MMC_SEND_CID,16)
    BiosCmd_SD_Init:��ʼ��SD��, SD�ĳ�ʼ��������ֲ�
        Example: Bios(BiosCmd_SD_Init, (far char*)SourceBuff, 0, 0 )
    BiosCmd_SD_ReadBlock:��SD���е�addr_H*65536+addr_L��ַ�ж�ȡһ������,����buf��,һ��Ϊ1024�ֽ�
        Example: Bios(BiosCmd_SD_ReadBlock, buf,addr_L,  addr_H)
    BiosCmd_SD_WriteBlock:��buf�е�һ������д���SD���е�addr_h*65536+addr_L��ַ��,ͨ��һ��Ϊ1024�ֽ�
        Example: Bios(BiosCmd_SD_WriteBlock, buf,addr_L,  addr_H)
    BiosCmd_SD_CheckPresence:���SD���Ƿ����
        Example: Bios(BiosCmd_SD_CheckPresence, 0, 0, 0)
    BiosCmd_PrintGraph:��ӡ��idx��ָ����ͼƬ
        Example: Bios(BiosCmd_PrintGraph, (char*)idx, option, position);
        //idx:      ͼƬ���(1-24)
        //option:   bit0  =1,��GrafTexts�е����ֵ��ӵ�ͼƬ��
        //          bit1  =1,ʹ��ͼƬ�Դ������ֵ��ӵ�ͼƬ��
        //position:ָ��ͼƬ��ӡ���ַ�λ��
    BiosCmd_PrintX:���ӡ�����ʹ�ӡ����,LineΪҪ��ӡ������;CmdΪ��ӡ����;DotLinesBlank reserved parameter
        Example: Bios(BiosCmd_PrintX, char *Line, WORD Cmd , WORD DotLinesBlank);
        //Cmd��������:*/

// ======================================================================
// ��ӡ��������������
// ======================================================================
/////////// bit Command of printrn_Command ///////////////////////////////////////

#define	B_PRI_DBLH			1	// double with print mode for text   PRN_DBLH_Mode
#define	B_PRI_RON			2	// double high print mode for text   PRN_RECEIPT_Mode
#define	B_PRI_JON			3	// print on stub printer   PRN_STUB_Mode
#define	B_PRI_GRAF			4	// print a graphic   PRN_GRAPHIC_Mode
#define	B_PRI_FCUT			5	// Cut paper full   PRN_CUTF_Mode
#define	B_PRI_PCUT			6	// Cut paper half   PRN_CUTH_Mode

// command for BiosCmd_PrintX:
#define	CMDP_RJ		((1 << B_PRI_RON) | (1 << B_PRI_JON))// ͬʱ���վݴ�ӡ���ʹ����ӡ���ϴ�ӡ(Reserved)
#define	CMDP_R		((1 << B_PRI_RON))// ֻ���վݴ�ӡ���ϴ�ӡ
#define	CMDP_J		((1 << B_PRI_JON))// ֻ�����ӡ���ϴ�ӡ(Reserved)
#define	CMDP_DRJ	((1 << B_PRI_RON) | (1 << B_PRI_JON) | (1 << B_PRI_DBLH))// ͬʱ���վݴ�ӡ���ʹ����ӡ���ϱ��ߴ�ӡ(Reserved)
#define	CMDP_DR		((1 << B_PRI_RON) | (1 << B_PRI_DBLH))// �վݴ�ӡ�����ߴ�ӡ
#define	CMDP_DJ		((1 << B_PRI_JON) | (1 << B_PRI_DBLH))// �����ӡ�����ߴ�ӡ(Reserved)
#define	CMDP_PRGRA	((1 << B_PRI_RON) | (1 << B_PRI_GRAF))// �վݴ�ӡ���ϴ�ӡͼƬ

//---------------------2. ��ӡ API ----------------------

//command definitions for RSPrint
#define PRN_DBLW_Mode        BIT0    //double with print mode for text
#define PRN_DBLH_Mode        BIT1    //double high print mode for text
#define PRN_RECEIPT_Mode     BIT2    //print on receipt printer
#define PRN_STUB_Mode        BIT3    //print on stub printer
#define PRN_GRAPHIC_Mode     BIT4    //print a graphic
#define PRN_CUTF_Mode        BIT5    //Cut paper full
#define PRN_CUTH_Mode        BIT6    //Cut paper half
#define PRN_CUTRESET_Mode    BIT7    //reset cutter

/** RSPrint******************************************************************
*
*   ��Ҫ��ӡ���ַ��������ӡ���в�������ӡ��������д�ӡ.
*   ��Ӧ���п���ֱ�ӵ���RSPrint��ȡ��Bios��BiosCmd_PrintX��BiosCmd_PrintGraphʵ�ִ�ӡ
*
*  INPUT:
*       *buf:  Text data for print,ע��:
*              ��buf[0]Ϊ�ַ�'@'ʱ,�ַ�������ӡ�ɱ���;
*              ��buf[n]Ϊ�ַ�'~'ʱ,buf[n+1]����ӡ�ɱ���;
*
*       count: Bytes in *buf must be print out
*       prnCMD: Command for TEXT ,must be one of:
*               -PRN_DBLW_Mode        //double with print mode for text
*               -PRN_DBLH_Mode        //double high print mode for text
*               -PRN_RECEIPT_Mode     //print on receipt printer
*               -PRN_STUB_Mode        //print on stub printer
*               -PRN_GRAPHIC_Mode     //print a graphic
*               -PRN_CUTF_Mode        //Cut paper full
*               -PRN_CUTH_Mode        //Cut paper half
*               -PRN_CUTRESET_Mode    //Cutter reset
*
*  return:<0;POOL is full & the data don't push in
*         >=0;data has pushed into the pool and the value is the
*         length of the data
*
* REMARK:
*     if prnCMD is the GRAPHIC command,PRN_GRAPHIC_Mode:
*         buf[0] must be the number of the graphic.(1,2,3....)
*                buf[0]=0,stop attach the text;
*         buf[1] must be '0'(don't attache text)
*               or '1' (8 lines of Text must attache for the graphic)
*               or '2' (copy text from graphic)
*        buf[2] Postion by character of the graphic on paper(0,1,2,..,32), It's not the must,
*               =0,Print at the default position defind by the graphic
*     if prnCMD is the CUT PAPER command:
*         buf[0] must be the FULL(1) cut or HALF cut(0).
*
********************************************************************************/
int RSPrint(BYTE *buf, int count, BYTE prnCMD);

/** Bios_1************************************************************
 *
 * ����cmd����ϵͳ����
 *
 * @param cmd :����
 *
 * @return WORD:���ع��ܵ��ý��,
 *              true-����ִ�гɹ�;false-����ִ��ʧ��
 ****************************************************************** */
WORD  Bios_1(WORD cmd);
/* cmd��������:
     BiosCmd_PrintCheck:��ȡ��ӡ����״̬:ȱֽ/ѹ��̧��/���ȵ�
        Example: Bios_1(BiosCmd_PrintCheck);
     BiosCmd_ResetCutter:��λ��ӡ���е�
        Example: Bios_1(BiosCmd_ResetCutter)
     BiosCmd_RestDisp0:������ʾ��ʾ��Ļ������,ͨ�����ڹػ����ٿ���ʱ��ʾ�ػ�ǰ�������Ļ����
        Example: Bios_1(BiosCmd_RestDisp0);
     BiosCmd_ClrFip0:�ر�LED��ʾ
     BiosCmd_AutoClickOff:�رհ����Զ���������
     BiosCmd_AutoClickOn:�򿪰����Զ���������
     BiosCmd_BuzzL:����������һ��
     BiosCmd_BuzzM:����������һ��
     BiosCmd_BuzzS:����������һ��
     BiosCmd_GetDate:��ȡ���ڵ�rtc_date��
     BiosCmd_GetTime:��ȡʱ�䵽rtc_time��
     BiosCmd_SetDate:����rtc_date�е�������������
     BiosCmd_SetTime:����rtc_time�е�ʱ������ʱ��
     BiosCmd_CheckKeyborad:�ж��Ƿ��а�������,���ǲ���ȡ��ֵ��1���м����£�0�� �޼�����
*/


//--------------------3.����API����------------------------------

/** SetRTS*************************************************************
 *
 * :���ô���port��RTS
 * @param port :1-����1,2-����2.....
 ****************************************************************** */
void SetRTS(BYTE port);

/** ClrRTS*************************************************************
 *
 * :������ڵ�RTS
 * @param port: 1-����1,2-����2.....
 ****************************************************************** */
void ClrRTS(BYTE port);

/** GetCTS*************************************************************
 *
 * ��ȡ����CTS״̬
 * @param port: 1-����1,2-����2.....
 * @return BYTE:0��ʾ���账������״̬
 ****************************************************************** */
BYTE GetCTS(BYTE port);

/** Bios_PortWrite******************************************************
 *
 * �򴮿�NumCom����NumBytes�ֽڵ�����(TxData)
 *
 * @param NumCom: 1-����1,2-����2.....
 * @param TxData :Ҫ���͵��ַ�����
 * @param NumBytes :Ҫ���͵��ַ���
 * @param Flags :reserved
 *
 * @return unsigned short :=true,���ͳɹ�;=false,����ʧ��
 ****************************************************************** */
unsigned short Bios_PortWrite(BYTE NumCom, void  *TxData, unsigned short NumBytes, unsigned char Flags);

/** Bios_PortRead*******************************************************
 *
 * �Ӵ��ڶ�ȡNumBytes�ֽڵ����ݲ�����Dest��;
 *
 * @param NumCom: 1-����1,2-����2.....
 * @param Dest :��ȡ���ݴ����;
 *              =0ʱ,��⴮���Ƿ�������,������ʱ���ȴ�.
 * @param NumBytes:��Ҫ��ȡ���ַ���Ŀ,
 *                =0ʱ,�ȴ��������ݿɶ�; =-1,����յ����� ��
 * @param TimeOut :�ȴ��ӳ�,�Ժ���Ϊ��ʱ��λ
 * @param Status :reserved
 *
 * @return short :����ʵ������ȡ���ֽ���
 ****************************************************************** */
short Bios_PortRead(BYTE NumCom, void *Dest, short NumBytes,ULONG TimeOut,unsigned  short *Status);


/**UARTInit***********************************************************
 *
 * @param PortNum :1-����1,2-����2.....
 * @param baudrate :1200,2400,4800,9600,19200,38400,57600,115200
 * @param Databits : 8 = 8 bit per carattere;9-9 bit per carattere
 * @param Parity : 0-NONE,1 = ODD,2- EVEN
 * @param Stopbits : 1= 1 stop bit;2-2 stop bit
 *
 * @return uint32_t :true---config success; false---	failure
 ****************************************************************** */
uint32_t UARTInit( uint32_t PortNum, uint32_t baudrate,uint8_t Databits,uint8_t Parity,uint8_t Stopbits );

//--------------------4.ϵͳ����API����------------------------------

/**Bios_TestMAC******************************************************
 *
 * ����MAC������״̬,��������Ƿ�Ҫ���տ�����мӵ��ʼ��
 *
 * @return WORD :true-MAC on; false-MAC off
 ****************************************************************** */

WORD Bios_TestMAC(void);


/** Bell,Beep*********************************************************
 *
 *  ����ָ�������򿪷�����
 *
 * @param len :����len(1/2/3)�ֱ����峤/��/��ʱ��
 * @return short :0
 ****************************************************************** */
short Bell(short len);
void Beep(BYTE len);

/** CutRPaper*********************************************************
 *
 * ��ӡ����ֽ,ֻ���������е��Ĵ�ӡ����Ч
 *
 * @param lines :��ֽǰ��ֽ����
 ****************************************************************** */
void CutRPaper(short lines);

/** DrawerOpen*********************************************************
 *
 * ��Ǯ��
 *
 ****************************************************************** */
void DrawerOpen(void);

/** msDelay************************************************************
  *
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 1 ms.
  * @retval None
  *
  ****************************************************************** */
void msDelay(ULONG nTime);

/** usDelay************************************************************
  *
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 1 us.
  * @retval None
  *
  ****************************************************************** */
void usDelay(ULONG nTime);

//--------------------5.SD��API����------------------------------

/***************************************************************
  ����SD��:SD���Ŀ��СΪ1024��ÿ�ζ�дSD��������1024�ֽ�
*****************************************************************/

/** MMC_ReadBlock********************************************************
 *
 * ��SD���϶�ȡһ������,��SD���Ŀ��СΪ1024ʱ��ÿ�ζ�дSD��������1024�ֽ�
 *
 * @param buf :���ݴ洢��,�ֽ���������ڵ���1024
 * @param addr :��ȡ��ַ
 *
 * @return BYTE :true-��ȡ�ɹ�;false-��ȡʧ��
 ****************************************************************** */
BYTE MMC_ReadBlock(char *buf,ULONG addr);

/** MMC_WriteBlock**********************************************************
 *
 * ��SD����д��һ�����ݣ���SD���Ŀ��СΪ1024ʱ��ÿ�ζ�дSD��������1024�ֽ�
 *
 * @param buf :Ҫд�������,�ֽ����������1024
 * @param addr :����д���ַ
 *
 * @return BYTE true-д��ɹ�;false-д��ʧ��
 ****************************************************************** */
BYTE MMC_WriteBlock(char *buf,ULONG addr);

//--------------------6.��ʾAPI����------------------------------

/**PutsO****************************************************************
 *
 * �ڲ���Ա�͹˿���ʾ��Ļ����ʾ�ַ���
 *
 * @param str :Ҫ��ʾ���ַ���
 ****************************************************************** */
void PutsO(const char *str);


/**mDispCharXY***********************************************************
 *
 * ��64x128������Ļ��y��,��x���ַ�λ����ʾ�ַ�ch
 *
 * @param ch: ������ASCII���ߺ���
 * @param x:��λ�� (0~15)��(0~20)
 * @param y:��λ�� (0~3)��(0~7)
 ****************************************************************** */
void mDispCharXY(WORD ch, BYTE x, BYTE y);


/**mDispStringXY***********************************************************
 *
 * ��64x128������Ļ��y��,��x���ַ�λ����ʾ�ַ���
 *
 * @param str: �ַ���
 * @param x:��λ�� (0~15)��(0~20)
 * @param y:��λ�� (0~3)��(0~7)
 ****************************************************************** */
void mDispStringXY(BYTE* str, BYTE x, BYTE y);


/**mMoveCursor**************************************************************
 *
 * �ƶ����	�ڵ�y(0~3)��,��x(0~15)��λ����ʾ��꣬��꿿�Ҷ���
 *
 * @param x
 * @param y
 ***************************************************************************/
void mMoveCursor(uint8_t x, uint8_t y);


/**mDispCursor**************************************************************
 *
 *  ��mMoveCursor�趨�Ĺ��λ����ʾ���
 *
 *  ******************************************************************** */
void mDispCursor(void);

/**mClearScreen***********************************************************
 *
 * �����Ļ����
 *
 * ******************************************************************* */
void mClearScreen(void);

//--------------------7.Fiscal memory API------------------------------

/** Bios_FM_CheckPresence,FMDetect**************************************
 *
 * ���˰�ش洢���Ƿ����
 *
 * @return BYTE :true-����;false-������
 ****************************************************************** */
BYTE Bios_FM_CheckPresence(void);
uint8_t FMDetect(void);

/**FiscalMem_ReadBuffer*************************************************
  *
  * @brief  Reads a block of data from the FM.
  * @param  pBuffer: pointer to the buffer that receives the
  *                data read from the FM.
  * @param  ReadAddr: FM's internal address to read from.
  * @param  NumByteToRead: number of bytes to read from the FM.
  * @retval None
  ****************************************************************** */
uint8_t FiscalMem_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);

/**FiscalMem_WriteBuffer*************************************************
  *
  * @brief  Writes block of data to the FM.
  * @param  pBuffer: pointer to the buffer containing the data
  *                to be written to the FM.
  * @param  WriteAddr: FM's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the FM.
  * @retval None
  ****************************************************************** */
uint8_t FiscalMem_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);


//--------------------8.Flash memory API------------------------------

//definitions for Flash--------
#define FLASH_SUCCESS (-1)
#define FLASH_WRONG_TYPE (-8)
#define FLASH_ERASE_FAIL (-14)

/** bFlashReadBuffer*****************************************************
  *
  * ���ֽڶ�ȡ�ⲿflash�е�����
  *
  * @brief  Reads a block of data from the FLASH.
  * @param  pBuffer: pointer to the buffer that receives the data read from the FLASH.
  * @param  ReadAddr: FLASH's internal address to read from.
  * @param  NumByteToRead: number of bytes to read from the FLASH.
  * @retval None
  ****************************************************************** */
uint8_t bFlashReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumBytesToRead);

/**bFlashProgram*********************************************************
 *
 * ��flash�洢����д������
 *
 * @param ulOff :����д���ַ
 * @param NumBytes :��Ҫд����ֽ���Ŀ
 * @param ucArrayPointer :��Ҫд�������
 *
 * @return int: FLASH_SUCCESS-д��ɹ�,
 *              FLASH_ERASE_FAIL������ֵ-д��ʧ��
 ****************************************************************** */
int bFlashProgram( uint32_t ulOff, uint32_t NumBytes,uint8_t *ucArrayPointer );

//
/**bFlashMBlockErase******************************************************
 *
 * ����Flash�洢��,
 *
 * @param ucBlock :��Ҫ�����Ŀ���
 * @param ucNumBlocks :��ucBlock�ſ鿪ʼ��������ucNumBlocks��
 *
 * @return int :FLASH_SUCCESS-�����ɹ�,
 *              FLASH_ERASE_FAIL������ֵ-����ʧ��
 ****************************************************************** */
int bFlashMBlockErase(int ucBlock, int ucNumBlocks);


/**bFlashChipErase*****************************************************
 *
 * The function can be used to erase the whole flash chip so long as
 *  no blocks are protected. If any blocks are protected then
 *  nothing is erased.
 *
 * @return int :On success the function returns FLASH_SUCCESS (-1)
 * If a block is protected then the function returns the number of the block and
 * no blocks are erased.
 * If the erase algorithms fails then the function returns FLASH_ERASE_FAIL (-2)
 * If the wrong type of flash is detected then FLASH_WRONG_TYPE (-8) is
 * returned.
 ****************************************************************** */
int bFlashChipErase( void );

//--------------------9.���̶�ȡ API------------------------------

/** Getch*************************************************************
  *
  * ��ȡ��������İ���
  * �ڵ���Getch֮ǰӦ���ȵ���Bios_1(BiosCmd_CheckKeyborad)�ж��Ƿ��а���
  *
  * @param  None
  * @retval :key pressed; 0,1,2,.....
  ****************************************************************** */
uint8_t Getch(void);


//--------------------10.USB ͨ�� API---------------------------------

/**USB_COMM_Ready*****************************************************
 *
 * ����USB״̬,��Ҫʹ��USB���洮�ڽ���ͨ��ʱ.���붨�ڵ���USB_COMM_Ready
 * ������USB�Ƿ�������
 *
 * @return uint8_t :true-��ʾUSB�յ���ͨ������
 **********************************************************************/
uint8_t USB_COMM_Ready(void);

/**ReadUSB***********************************************************
 *
 * ��ȡUSB��ͨ������
 *
 * @param rCH :���ڴ�Ŷ�ȡ����ͨ������
 *
 * @return BYTE :=true,��ʾ������,=false��ʾ������
 *
 ***************************************************************** */
BYTE ReadUSB(BYTE *rCH);

/**CheckUSB***********************************************************
 *
 * ����USB�Ƿ��յ�ͨ������
 *
 * @return BYTE :=true,��ʾ������,=false��ʾ������
 *
 ***************************************************************** */
BYTE CheckUSB(void);

/**EmptyUSB***********************************************************
 *
 * ���USB�յ���ͨ������
 *
 ***************************************************************** */
void EmptyUSB(void);

/**SendUSB***********************************************************
 *
 * ͨ��USB����һ���ֽ�����
 *
 * @param ch :ΪҪ���͵��ֽ�����
 *
 ***************************************************************** */
void SendUSB(BYTE ch);

/**SendUSBString******************************************************
 *
 * ͨ��USB����һ���ַ���
 *
 * @param sStr :Ҫ���͵��ַ���
 * @param len :�ַ����ĳ���
 */
void SendUSBString(BYTE *sStr,short len);
/*Example for use of USB commnunication:
     while (USB_COMM_Ready())//ccr2016-06-24
    {
	    	while (CheckUSB())
	    	{
                if (ReadUSB(&bcc))
                    SendUSB(bcc);
            }
    }
 */

//--------------------END--------------------------------------------

