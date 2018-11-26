#include "King.h"
#include "Exth.h"
#include "Exthead.h"
#include "string.h"

#if(defined(CASE_GPRS))

#define WAITFOROK   1   //ccr2017-09-29���յ����������˳���"OK"��"ERROR"�޹ص�����

#include "Gprs.h"

///////////////////////////////////////////////////////////////////////////////
#if (!defined(DEBUGBYPC) && defined(FOR_DEBUG))
#define DEBUGGPRS    //ccr2015-08-21�������ݷ�����ȷ��
#endif

#include "message.h"

#if defined(DEBUGGPRS)
#define GPRSECH_SEND(a) UARTSend(LOGIC_COM1,a)//�����͸�GPRS��ͨѶ���ݴӴ���1����
#define GPRSECH_READ(a) UARTSend(LOGIC_COM1,a)//����GPRS�յ���ͨѶ���ݴӴ���1����
#else
#define GPRSECH_SEND(a) {}//�����͸�GPRS��ͨѶ���ݴӴ���1����
#define GPRSECH_READ(a) {}//����GPRS�յ���ͨѶ���ݴӴ���1����
#endif

#define MAXLOGPACKAGE      //ccr2015-08-25����ˮ�������������ʽ����
#define GPRSWAITACK     //ccr2015-08-25����������ʱ,�ȴ����ݷ������
///////////////////////////////////////////////////////////////////////////////

unsigned long GPRS_Wait=0;//ccr2015-03-11��һ�γ���GPRSͨѶ��ʱ��

int PackageReceived=0;

BYTE GPRS_Ready=0;//������ʾGPRSģ���״̬

#if defined(ACK_MUST)
BYTE GPRS_WaitACK=0;
#endif

CONST char ATE0[]="ATE0\r";//�رջ���
CONST char GPRSReady[]="AT-Command Interpreter ready\r\n";
//GPRSReady��Ҫ����40,����40ʱ��Ҫ�޸�GPRSWaitForReady
///////////////////////////////////////////////////////////////////////////////

/**
 * ���������GPRSģ���Ƿ񷵻�GPRSReady[]�е���Ϣ�ж�GPRS�Ƿ�׼����
 *
 * @author EutronSoftware (2014-12-11)
 * @param init:true-���г�ʼ��
 */
void GPRSWaitForReady(BYTE init)
{
    static int rdyPOS=0;
    short j;

    //ccr2015-03-11>>>>>>>>>>>>>>
    if (init)
    {
        rdyPOS = 0;
        GPRS_Wait = GetSystemTimer()+SECONDS(ACTIVE*60);//�ȴ�5����
        GPRS_Ready = 0;
        GPRSReset(0);
        return;
    }//ccr2015-03-11<<<<<<<<<<<<<<<
    if (!TESTBIT(GPRS_Ready,GPRS_OK_BIT+GPRS_NO_BIT+GPRS_NO_SIM) && GetSystemTimer()>GPRS_Wait)//ccr2015-03-11
    {
        mDrawGPRS(SCREENWD-1,0,0);//�����Ͻ���˸��ʾ��ʾ
        if (rdyPOS>40)//strlen(GPRSReady))
        {
            if (!TESTBIT(GPRS_Ready,GPRS_SKIP_SIM) && (RTCTimer-rdyPOS)>SECONDS(5))
            {//û�м���SIM��
                SETBIT(GPRS_Ready,GPRS_SKIP_SIM);
                if (!GPRSSIM_Exist())
                {
                    SETBIT(GPRS_Ready,GPRS_NO_BIT+GPRS_NO_SIM);
                    ApplVar.ErrorNumber =  ERROR_ID(CWXXI88);
//ccr2016-07-27                    DispSt1(GPRSMess[G_WAITFOR].str);
//ccr2016-07-27 �����ظ����                    GPRSWaitForReady(true);//ccr2015-03-11
                    return;
                }
            }

            if ((RTCTimer-rdyPOS)>SECONDS(20))
            {//GPRSģ����Ҫ�ٵȴ�Լ20����ܹ�����TCP/IPģʽ
                Bell(1);
                SETBIT(GPRS_Ready,GPRS_OK_BIT);
                RESETBIT(GPRS_Ready,GPRS_NO_BIT);
                mSetInvAttr();
                DispSt1(GPRSMess[G_GPRSOK].str);
                mClearInvAttr();
                EmptyComm(GPRSPORT);
                rdyPOS = 0;
#if defined(CASE_INDONESIA)
                GPRSSendECR_HeartBeat(0xff);//ccr2015-08-04
#endif
            }
            return;
        }
        //�ȴ�GPRSģ��Ӧ��"AT-Command Interpreter ready\r\n"
        while (!TESTBIT(GPRS_Ready,GPRS_OK_BIT) && CheckComm(GPRSPORT))
        {
            j = ReadComm(GPRSPORT);
            if (j==-1)
                break;
            else
            {
                j &= 0xff;
                GPRSECH_READ(j);//testonly
                if (j==GPRSReady[rdyPOS])
                {
                    rdyPOS++;
                    if (rdyPOS>=strlen(GPRSReady))
                    {
    //                    Bell(1);
    //                    SETBIT(GPRS_Ready,GPRS_OK_BIT);
    //                    DispSt1(GPRSMess[G_GPRSOK].str);
                        rdyPOS = RTCTimer;
                    }
                }
            }
        }
    }
}
/**
 * ��GPRSģ�鷢��һ���ֽ�����
 *
 * @author EutronSoftware (2014-12-15)
 *
 * @param byte
 */
void GPRSSendByte(BYTE byte)
{
    Bios_PortWrite(GPRSPORT+1, &byte, 1, 1);
    GPRSECH_SEND(byte);//testonly
}

//CONST char AtIpdr[]="AT%IPDR\r\n";
//CONST char AtIpdd[]="AT%IPDD\r\n";
//CONST char AtIpdq[]="AT%IPDQ\r\n";

/**
 *
 * �����ַ�������
 * @author EutronSoftware (2014-12-15)
 *
 * @param str :��Ҫ���͵��ַ�������
 * @param len :�ַ����ĳ���.=-1ʱ,�������м��㳤��,��ʱ���ַ���������'\n'����
 */
void GPRSSendAString(CONST char *str,short len)
{
    short i;
    GPRSECH_SEND('>');
    if (len==-1)
        len=strlen(str);
    for (i=0;i<len;i++)
        GPRSSendByte(str[i]);
}
//��str�е�������HEX�ķ�ʽ����
void GPRSSendHEXString(char *str,short len)
{
    short i;
    for (i=0;i<len;i++)
        GPRSSendHEX(str[i]);
}


//---------------------------------------------------------------------------
#define WAITFORTYPE 0//�ȴ���������:'F'-Ϊ��ˮ,'U'Ϊ����
#define WAITFORSIZE 1
#define WAITFORDATA 2


/**
 *  @author EutronSoftware (2014-12-06)
 * ���յ��������н���һ��ECR�ļ�����,�����������EcrRecordָ���Ĵ洢��
 *  data��¼��ʽ:[Type]+[size]+[data],  sizeΪdata���ֽ���
 *
 * @param command:��Ҫ����������('U'...);=0ʱ,��ʼ��
 *        data:�յ�������,data[0]Ϊ����,data[1]Ϊsize,data[2..3]Ϊ��������(������)
 *        size:�����յ������ݳ���
 *
 * @return
 *         WORD:=0xffffʱ,����������;=0ʱ,���ݽ���;����ֵ:Ϊ�յ������ݶ�Ӧ�Ĺ�����
 *         EcrRecord[0]+EcrRecord[1]:��Ź�����
 *         EcrRecord+2:Ϊ��Ӧ�����������
 */
#define EcrRecord PCBuffer

WORD GPRSDecodeECRRecord(BYTE command,BYTE data,BYTE *size)
{
    //Variable for GPRSGetECRARecord
    static BYTE GPRS_Command;//�յ�����������;'F','U','D'....
    static BYTE GPRS_SizeMust;//������ȡ��������Ŀ
    static int GPRS_BytesReceived;//��¼�Ѿ��յ���������Ŀ
    static BYTE GPRS_WaitFor=WAITFORTYPE;//=0,��ʾ�ȴ���������;=1��ʾ�ȴ������ֽ�;=2��ʾ�ȴ�����

    int i;

    if (command==0)
    {//initial
        GPRS_WaitFor=WAITFORTYPE;
        GPRS_BytesReceived=0;
    }
    else
    {
        switch (GPRS_WaitFor)
        {
        case WAITFORTYPE://�ȴ���������
           if (data=='U')//Ϊ������ˮ�������ļ�����
           {
               GPRS_Command = 'U';
               GPRS_WaitFor = WAITFORSIZE;
               GPRS_BytesReceived = 0;
           }
           break;
       case WAITFORSIZE://�ȴ����ݳ���,�256�ֽ�
           //if (data<=sizeof(union ECRFILEREC))
           {//Ϊ�ļ�����
                GPRS_SizeMust = data;
                GPRS_BytesReceived = 0;
                GPRS_WaitFor = WAITFORDATA;
           }
           //else//���ļ�����
           //     GPRS_WaitFor = WAITFORTYPE;
           break;
       case WAITFORDATA://�ȴ���ȡ����
           EcrRecord[GPRS_BytesReceived++]=data;
           if (GPRS_BytesReceived==GPRS_SizeMust)
           {//��ȡ��һ�����������ݰ�
               PackageReceived++;
               GPRS_WaitFor = WAITFORTYPE;

               if (GPRS_Command=='U')
               {//������ȡ���
                   if (CWORD(EcrRecord[0])==0)
                       return 0;
                   else// if (CWORD(EcrRecord[0])>CLERK && CWORD(EcrRecord[0])<PLU3 || CWORD(EcrRecord[0])>=RHEAD1 && CWORD(EcrRecord[0])<=RTRAIL2)
                   {
                       if (size)
                           *size = GPRS_SizeMust;
                       return CWORD(EcrRecord[0]);
                   }
               }
               else
                   return 0xffff;//������һ��������
           }
           break;
       }
       return 0xffff;//������һ��������
    }
}

/*****************�жϻ������Ƿ���ָ�����ַ�������******************
����ԭ��:BYTE GPRSHand(unsigned char *a)
��������:�жϻ������Ƿ���ָ�����ַ���
�������:unsigned char *a ָ�����ַ���
�������: true---����    false---������
����ģ��:��
**********************************************************************/
BYTE GPRSHand(char *rec_buf,char *ret)
{
    int i;
    int len=strlen(ret);

    for (i=0;i<len;i++)
    {
        if (rec_buf[i]!=ret[i])
            return false;
    }
    return true;
}

BYTE ASC_2_HEX(BYTE pASC)
{
    if (pASC >= '0' && pASC <= '9')
    {
        return(pASC & 0x0f);
    }
    else if ((pASC >= 'A' && pASC <= 'F') || (pASC >= 'a' && pASC <= 'f'))  //A....F
    {
        return(pASC & 0x0f)+9;
    }
    return 0;
}

void GPRSSendHEX(BYTE byte)  //send data one byte, such as  SOH and so on..
{
    BYTE sCh;

    sCh = byte>>4;
    if (sCh>9)
        sCh += 'A'-10;
    else
        sCh += '0';
    GPRSSendByte(sCh);

    sCh = byte & 0x0f;
    if (sCh>9)
        sCh += 'A'-10;
    else
        sCh += '0';
    GPRSSendByte(sCh);
}
// ����GPRSģ�鷵�ص�����,����GPRSģ�鷢��һ������ʱ,GPRSģ��������Ѵ��������,������Դ˻��� //
// mWaitFor:�ȴ�ʱ��=mWaitFor ��
// return=0--����,  =1 ���� //
BYTE GPRSSkipReceived(ULONG mWaitFor)
{
    short j;
    BYTE sEnd=0;

    SetTimerDelay0(mWaitFor);
    while (GetTimerDelay0())
    {
        j = ReadComm(GPRSPORT);
        if (j!=-1)
        {
            GPRSECH_READ(j);//testonly

            if (j=='\r')
                sEnd = '\r';
            else if (j=='\n' &&  sEnd == '\r')
                return true;
            SetTimerDelay0(mWaitFor);
        }
    }
    return false;
}
// empty the comm..skip the string
void GPRSSkipQuick()
{
    short retry,j;
    BYTE sEnd=0;

    while (1)/*for (retry=0; retry<RETRYTIMES; )*/
    {
        j = ReadComm(GPRSPORT);
        if (j!=-1)
        {
            GPRSECH_READ(j);//testonly

            if (j=='\r')
                sEnd = '\r';
            else if (j=='\n' &&  sEnd == '\r')
                return;
        }
        else return;
    }
}
/**
 *
 *
 * @author EutronSoftware (2014-12-15)
 *
 * @param str :��ȡ���ݵĴ����
 * @param size :��Ҫ��ȡ�����ݳ���
 * @param sWaitFor :�ȴ�ʱ��(��)
 *
 * @return short:=-1,��ʱ,>=0,�յ�����
 */
short GPRSReadAString(BYTE *str,short size,ULONG sWaitFor)
{
    short i,j;
    BYTE sEnd=0;

    i =  0;
    SetTimerDelay0(sWaitFor);
    while (i<size && GetTimerDelay0()>0)
    {
        j = ReadComm(GPRSPORT);
        if (j!=-1)
        {
            GPRSECH_READ(j);//testonly

            SetTimerDelay0(sWaitFor);
            if (j=='\r')
            {
                sEnd = '\r';
                str[i]=0;
            }
            else if (j=='\n')
            {
                if (sEnd == '\r')
                    return i;
                else
                {
                    continue;
                    //return 0;
                }
            }
            else
                str[i++]=j & 0xff;
        }
    }
    return -1;
}
// connect to APN,Which is a bridge between GPRS Gateway and INTERNET Gateway..
// return !0, success, 0, failed;
/*CONST char AtSetBaudrate[]="AT+IPR=115200\r\n";
BYTE GPRSSetComm()
{
    GPRSSendAString(AtSetBaudrate,strlen(AtSetBaudrate));
    GPRSSkipReceived();
    if(GPRSReadAString(PCBuffer,sizeof(PCBuffer))>0)
    {
        return (PCBuffer[0]=='O'&&PCBuffer[1]=='K');
    }
    else
        return FALSE;
}*/

//  ����Ƿ����SIM��
// return 	!0-success,	0-failed;
CONST char AT_SIM[]="AT%TSIM\r\n";
BYTE GPRSSIM_Exist()
{
    char readGPRS[32];
    BYTE simOK=false;

    short i,j;

    if (GPRSSend_ATE0())
    {
        GPRSSendAString(AT_SIM,strlen(AT_SIM));

        for (i=0;i<6;i++)
        {
            if ((j=GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(10)))>=0)
            {
                if (CWORD(readGPRS[0])==RET_OK)
                    return simOK;
                if (GPRSHand(readGPRS,"%TSIM 0"))
                    simOK = false;
                else if (GPRSHand(readGPRS,"%TSIM 1"))
                    simOK = true;
            }
            else
                break;
        }
    }
    return simOK;
}

/**
 * �ر�GPRSģ��Ļ��Թ���
 *
 * @author EutronSoftware (2014-12-10)
 *
 * @return BYTE
 */
BYTE GPRSSend_ATE0()
{
    short i;
    char readGPRS[16];

    GPRSSendAString(ATE0,strlen(ATE0));
#if (WAITFOROK)
    return GPRSWaitForOK(SECONDS(10));
#else
    if (!GPRSSkipReceived(SECONDS(10)))//SKIP "ATE0" or '\r\n'
        return FALSE;
    if (GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(5))>0)
    {
        return(CWORD(readGPRS[0])==RET_OK);
    }
    else
        return FALSE;
#endif
}

CONST char ATCONNECTAPN[]="AT+CGDCONT=1,\"ip\",\"cmnet\"\r\n";
BYTE GPRSConnectAPN()
{
    char readGPRS[32];

    if (ApplVar.IP.APN[0])
    {//ccr2015-03-10>>>>> �����û����ƺ͵�¼����
        GPRSSendAString(ATCONNECTAPN,19);
        GPRSSendAString(ApplVar.IP.APN,strlen(ApplVar.IP.APN));
        GPRSSendAString("\"\r\n",3);
    }
    else//<<<<<����APN��
        GPRSSendAString(ATCONNECTAPN,strlen(ATCONNECTAPN));

    if (!GPRSSkipReceived(SECONDS(5)))//*/!GPRSReadAString(PCBuffer, sizeof(PCBuffer))>=0)
        return FALSE;
    if (GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(5))>0)
        return(readGPRS[0]=='O' && readGPRS[1]=='K');
    else
        return FALSE;
}


//  get a virtual ApplVar.IP from GPRS Server..
// AT%ETCPIP="username","password"
// return 	!0-success,	0-failed;
CONST char AtEtcpip[]="AT%ETCPIP=\"\",\"\"\r\n";//AT%ETCPIP="",""\r\n

BYTE GPRSRegisterTCPIP()
{
    char readGPRS[32];

    short i=strlen(AtEtcpip);

    if (ApplVar.IP.UserName[0])
    {//ccr2015-03-10>>>>> �����û����ƺ͵�¼����
        GPRSSendAString(AtEtcpip,11);
        GPRSSendAString(ApplVar.IP.UserName,strlen(ApplVar.IP.UserName));
        if (ApplVar.IP.Password[0])
        {//������
            GPRSSendAString(AtEtcpip+11,3);
            GPRSSendAString(ApplVar.IP.Password,strlen(ApplVar.IP.Password));
            GPRSSendAString(AtEtcpip+14,i-14);
        }
        else//������
            GPRSSendAString(AtEtcpip+11,i-11);
    }
    else//<<<<<�����û���������
        GPRSSendAString(AtEtcpip,i);

#if (WAITFOROK)
    return GPRSWaitForOK(SECONDS(10));
#else
    if (!GPRSSkipReceived(SECONDS(10)))//!GPRSReadAString(readGPRS, sizeof(readGPRS)))
        return false;

    if (GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(5))>0)
    {
        if (CWORD(readGPRS[0])==RET_OK)
            return TRUE;
        if (GPRSHand(PCBuffer,"ERROR"))
            return FALSE;
    }
    return FALSE;
#endif
}

CONST char ATIPOPEN[]="AT%IPOPEN=\"TCP\",\"";   //211.142.221.197\",10085\r\n";

// return =false,����ʧ��; =true���ӳɹ� /
// GPRSConnect_TCPIP("192.168.0.1","10085");
BYTE GPRSConnect_TCPIP(/*CONSTCHAR *pIP,CONSTCHAR *pPort*/)
{
    short len,retry=0;
    short i;


    strcpy(PCBuffer,ATIPOPEN);len=strlen(ATIPOPEN);//get the TCP/IP command
    NumToIP(PCBuffer+len,ApplVar.IP.ServerIP);  //get the ServerIP..
    len = strlen(PCBuffer);
    PCBuffer[len++]='"';
    PCBuffer[len++]=',';
    len += WORDtoASCL(PCBuffer+len,ApplVar.IP.ServerPort);//get the serverPort..
    PCBuffer[len++]='\r';
    PCBuffer[len++]='\n';
    GPRSSendAString(PCBuffer,len);

    if (!GPRSSkipReceived(SECONDS(60)))//!GPRSReadAString(PCBuffer, sizeof(PCBuffer))>=0)
        return false;

    memset(PCBuffer,0,sizeof(PCBuffer));
    while (retry<RETRYTIMES)
    {
        if (GPRSReadAString(PCBuffer,sizeof(PCBuffer),SECONDS(60))>=0)
        {
            if (GPRSHand(PCBuffer,"CONNECT"))
            {
                GPRSSkipReceived(SECONDS(30));
                EmptyComm(GPRSPORT);
                return TRUE;
            }
            else  if (GPRSHand(PCBuffer,"ERROR"))
                    return FALSE;
                else
                    retry++;
        }
        else
            return FALSE;
    }
    return FALSE;
}

//�ر�GPRS����
BYTE CloseGPRS()
{
    if (GPRSCloseTCPIP(2)) // AT%IPCLOSE
        return TRUE;
    else
        EmptyComm(GPRSPORT);
    return FALSE;
}

//CONST char ServerIP[]="211.142.221.197";	//should be seted;
//CONST char ServerPORT[]="10085";			// the same as above;
BYTE GPRSStartGprs()
{
   BYTE flag=0;

   if (ApplVar.CentralLock==SET)
   {//����ģʽ��,ȫ��Ļ��ʾ��Ϣ
        mClearScreen();
        {
            DispStrXY(GPRSMess[G_TOCONNECTING].str,0,0);
            EmptyComm(GPRSPORT);
            if (GPRSSend_ATE0()) //Make sure that when connect to Server the gprs are unconnect.
            {
                if ((ApplVar.IP.ServerIP[0] | ApplVar.IP.ServerIP[1] | ApplVar.IP.ServerIP[2] | ApplVar.IP.ServerIP[3])==0
                    || ApplVar.IP.ServerPort==0)
                {//û�����÷�����IP�Ͷ˿�
                    DispStrXY(GPRSMess[G_SERVERIP_NULL].str,0,1);
                    return false;
                }
                else if (GPRSConnectAPN() && GPRSRegisterTCPIP())
                {
                    if (GPRSConnect_TCPIP())
                    {//�ɹ����ӵ�������
                        EmptyComm(GPRSPORT);
                        return TRUE;
                    }
                    else
                    {//�޷����ӷ�����
                        CloseGPRS();
                        DispStrXY(GPRSMess[G_X_IPPORT].str,0,2);
                    }
                }
                GPRSReset(SET);//ccr2015-03-11 ��λһ��
                GPRS_Wait = GetSystemTimer()+SECONDS(50);//ccr2015-03-11
            }
            else
                GPRSWaitForReady(true);//ccr2015-03-11

        }
        DispStrXY(GPRSMess[G_LIANJIESERVERSHIBAI].str,0,1);

        return false;
    }
   else
   {//����ģʽ��,��״̬����ʾ��Ϣ
#if (SCRSTATDBL)
        if (ApplVar.CentralLock==RG || ApplVar.CentralLock==MG)
            DispOnStatDBL(GPRSMess[G_TOCONNECTING].str,0);
        else
#else
            DispSt1(GPRSMess[G_TOCONNECTING].str);//RG-DISPLAY
#endif
        EmptyComm(GPRSPORT);
        if (GPRSSend_ATE0()) //Make sure that when connect to Server the gprs are unconnect.
        {
            if ((ApplVar.IP.ServerIP[0] | ApplVar.IP.ServerIP[1] | ApplVar.IP.ServerIP[2] | ApplVar.IP.ServerIP[3])==0
                || ApplVar.IP.ServerPort==0)
            {//û�����÷�����IP�Ͷ˿�
                ApplVar.ErrorNumber = ERROR_ID(CWXXI87);
                return false;
            }
            else if (GPRSConnectAPN() && GPRSRegisterTCPIP())
            {//�ɹ����ӵ�������
                if (GPRSConnect_TCPIP())
                {//�ɹ����ӵ�������
                    EmptyComm(GPRSPORT);
                    return TRUE;
                }
                else
                {//�޷����ӷ�����,�ȴ�5���Ӻ�����
                    CloseGPRS();
                    ApplVar.ErrorNumber=ERROR_ID(CWXXI86);
                    GPRS_Wait = GetSystemTimer()+SECONDS(ACTIVE*60);//ccr2015-03-11
                    ClsArea(PROMDISPX,SCREENLN,SCREENWD-PROMDISPX);
                    return false;
                }
            }
            //�޷�����ͨѶ,�ȴ�5���Ӻ�����
            GPRS_Wait = GetSystemTimer()+SECONDS(ACTIVE*60);//ccr2015-03-11
#if (0)//ccr2015-03-11>>>>>
            if (!TESTBIT(GPRS_Ready,GPRS_TRY_BIT))
            {
                GPRSReset(0);
                RESETBIT(GPRS_Ready,GPRS_OK_BIT);//�ظ����һ��
                SETBIT(GPRS_Ready,GPRS_TRY_BIT);
                return false;
            }
            else
                SETBIT(GPRS_Ready,GPRS_NO_BIT);//��ʾ��GPRSģ��
#endif//ccr2015-03-11<<<<<<<
        }
        else//GPRSģ����Ӧ��,GPRSģ���쳣
        {//��λ5���Ӻ�����
            GPRSWaitForReady(true);//ccr2015-03-11
//ccr2015-03-11            RESETBIT(GPRS_Ready,GPRS_OK_BIT);
//ccr2015-03-11            SETBIT(GPRS_Ready,GPRS_NO_BIT);//��ʾ��GPRSģ��
        }
        ApplVar.ErrorNumber=ERROR_ID(CWXXI83);
        ClsArea(PROMDISPX,SCREENLN,SCREENWD-PROMDISPX);
        return FALSE;
   }
}
//------------------------------------------------------------
#define WAITFOR_IPDATA  0
#define WAITFOR_LENGTH  1
#define WAITFOR_QUOTES  2
#define WAITFOR_DATA    3
#define ENDOF_READ      4
/**
 * �Ӵ��ڶ�ȡGPRS���ص����� %IPDATA,xx,"12345678",[0d][0a]
 *
 * @author EutronSoftware (2014-12-08)
 *
 * @param pBuff :��ȡ�����ݴ����;=0ʱ,��ʼ��GPRSRead_IPDATA
 * @param size :��ͼ��ȡ���ֽ���Ŀ
 *
 * @return short :��ȡ���ֽ���Ŀ;=0ʱ,��ʱ;=-1ʱ,�������ݴ�
 */
short GPRSRead_IPDATA(char *pBuff,short size,ULONG sWaitFor)
{

    short dataLength,ch;
    char getIPDATA[16];

    short Read_MAX;//GPRSģ���յ���������Ŀ

    BYTE sByte,Read_CR;
    BYTE sBit=0;
    BYTE Read_WaitFor=0xff;// =0 ��������ͷ "%IPDATA", =1 �������ݳ���; =2,3 �������� //

    if (pBuff!=0 && size!=0)
    {
        dataLength= 0;
        SetTimerDelay0(sWaitFor);
        while (GetTimerDelay0())
        {
            ch = ReadComm(GPRSPORT);
            if (ch!=-1)
            {
                GPRSECH_READ(ch);//testonly
                switch (Read_WaitFor)
                {
                case WAITFOR_IPDATA:
                    getIPDATA[dataLength++]=ch;
                    if (ch==':')
                    {
                        getIPDATA[dataLength]=0;
                        if (strcmp(getIPDATA,"%IPDATA:")==0)//	change by lqw %IPDATA->%IPDATA:
                        {
                            sBit = 0;
                            Read_WaitFor = WAITFOR_LENGTH;
                            dataLength= Read_MAX = 0;
                        }
                        else
                            return -1;// ���ص����ݳ��� //
                    }
                    else if (dataLength>8)
                        return -1;// ���ص����ݳ��� //
                    break;
                case WAITFOR_LENGTH:
                    if (ch==',')
                        Read_WaitFor = WAITFOR_QUOTES;
                    else if (ch>='0' && ch<='9')
                        Read_MAX = Read_MAX*10 + (ch & 0x0f);// ��ȡ���ݳ��� //
                    break;
                case WAITFOR_QUOTES:
                    if (ch=='"')
                    {
                        dataLength = 0;
                        Read_WaitFor = WAITFOR_DATA;
                        sBit = 0;
                    }
                    break;
                case WAITFOR_DATA:
                    if (ch=='"')
                        Read_WaitFor = ENDOF_READ;
                    else
                    {
                        if (sBit)
                        {
                            if (dataLength<size)
                                pBuff[dataLength++] = (sByte<<4)+ASC_2_HEX(ch);
                            //if (dataLength>=Read_MAX) return dataLength;// �����д� //
                        }
                        else
                            sByte = ASC_2_HEX(ch);

                        sBit ^= 1;
                    }
                    break;
                case ENDOF_READ://ccr2016-10-25>>>>>>>>>>
                    //�ȴ��س�+����
                    if (ch=='\r')
                        Read_CR = '\r';
                    else //if (ch=='\n')
                        return dataLength;
                    break;
                default:
                    if (ch=='%')
                    {//�Ѿ���ȡ%IPDATA���ȫ������
                        Read_WaitFor=WAITFOR_IPDATA;// =0 ��������ͷ "%IPDATA", =1 �������ݳ���; =2,3 �������� //
                        dataLength= 0;
                        getIPDATA[dataLength++]=ch;
                    }
                    break;
                }
                SetTimerDelay0(sWaitFor);
            }
        }
        return dataLength;
    }
    else
        return 0;
}

CONST char ATRST[]="AT%RST\r\n";
/**
 * ��λGPRSģ��,ִ�и�λ������,����ȴ�Լ20��,��GPRS��������״̬
 *
 * @author EutronSoftware (2014-12-10)
 *
 * @return BYTE
 */
BYTE GPRSReset(WORD pSET)
{
    char readGPRS[32];

    GPRSSendAString(ATRST,strlen(ATRST));

    if (ApplVar.CentralLock==pSET)
    {
        mClearScreen();
        DispStrXY(GPRSMess[G_FUWEIMOKUAI].str,0,0);
        GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(10));//AT-Command Interpreter ready
        EmptyComm(GPRSPORT);
//ccr2015-03-11        Delay(SECONDS(20));
    }
    else
#if (SCRSTATDBL)
        if (ApplVar.CentralLock==RG || ApplVar.CentralLock==MG)
            DispOnStatDBL(GPRSMess[G_FUWEIMOKUAI].str,0);
        else
#else
            DispSt1(GPRSMess[G_FUWEIMOKUAI].str);//RG-DISPLAY
#endif

    return TRUE;
}

CONST char ATIPCLOSE[]="AT%IPCLOSE\r\n";
CONST char ATIPCLOSE1[]="AT%IPCLOSE=1\r\n";
CONST char ATIPCLOSE5[]="AT%IPCLOSE=5\r\n";
BYTE GPRSCloseTCPIP(BYTE sMode)
{

    short i,retry;
    if (sMode==1)
    {
        GPRSSendAString(ATIPCLOSE1,strlen(ATIPCLOSE1));
    }
    else  if (sMode==5)
    {
        GPRSSendAString(ATIPCLOSE5,strlen(ATIPCLOSE5));
    }
    else
    {
        GPRSSendAString(ATIPCLOSE,strlen(ATIPCLOSE));
    }

#if (WAITFOROK)
    return GPRSWaitForOK(SECONDS(10));
#else
    if (!GPRSSkipReceived(SECONDS(10)))//!GPRSReadAString(PCBuffer, sizeof(PCBuffer))>=0)
        return false;

    memset(PCBuffer,0,sizeof(PCBuffer));
    for (retry=0;retry<4;retry++)
    {
        if (GPRSReadAString(PCBuffer,sizeof(PCBuffer),SECONDS(10))>0)
        {
            if (GPRSHand(PCBuffer,"%IPCLOSE") || GPRSHand(PCBuffer,"AT%IPCLOSE"))
                continue;
            else  if (GPRSHand(PCBuffer,"ERROR"))
                return FALSE;
            else if (CWORD(PCBuffer[0])==RET_OK) // read "OK"
                return true;// �յ� "OK"
        }
    }
    return FALSE;
#endif
}


///////////ccr2014-11-10>>>>>>>>>>>>>>>>////////////////////////////////////////

BYTE SendATCommand(char *command)
{
    char readGPRS[16];

    GPRSSendAString(command,-1);
#if (WAITFOROK)
    return GPRSWaitForOK(SECONDS(10));
#else
    GPRSSkipReceived(SECONDS(15));//skip 0d 0a
    if (GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(10))>0)
    {
        if (CWORD(readGPRS[0])==RET_OK) // read "OK"
            return true;// �յ� "OK"
    }
    return FALSE;
#endif
}

/**ccr2014-11-26
 * ���Է���һ������Ϣ
 * ATE0[0d]
 * AT+CMGF=1[0d]
 * AT+CMGS=13627423241[0d]
 * Welcome to RUTRON[1a][0d]
 *
 * @author EutronSoftware (2014-11-10)
 */
void TestSendMess()
{
#if (0)//ccr2017-09-30!defined(DEBUGGPRS)

    short l;
	  //���ֻ�����һ������Ϣ,���ڼ��GPRSģ���ͨ���Ƿ�����
    EmptyComm(GPRSPORT);
    mClearScreen();
    if (TESTBIT(GPRS_Ready,GPRS_OK_BIT))
    {
        DispStrXY("Mobile #:",0,0);
        l = GetStrFrKBD('9',0,1,20,0);

        if (l>0 && GPRSSend_ATE0())
        {
            SendATCommand("AT+CMGF=1\r");
            GPRSSendAString("AT+CMGS=",-1);
            EntryBuffer[ENTRYSIZE - 1]=0;
            GPRSSendAString(&EntryBuffer[ENTRYSIZE - l - 1],-1);
            GPRSSendByte('\r');
            GPRSSkipReceived(SECONDS(5));//skip '>"

            ScrollScreen(1);
            DispStrXY("Message:",0,1);
            l = GetStrFrKBD('A',0,2,70,0);
            if (l>0)
                memcpy(PCBuffer,&EntryBuffer[ENTRYSIZE - l - 1],l);
            else
                l=0;
            PCBuffer[l]=0x1a;
            PCBuffer[l+1]=0;
            if (!SendATCommand(PCBuffer))
            {
//ccr2016-06-27                DispStrXY("Error send......",0,0);
            }
        }
    }
    else
    {
        DispStrXY(GPRSMess[G_WAITFOR].str,0,0);
    }
    PRESS_ANY_KEY(SCREENLN-2);

#else//ccr2015-08-24>>>>����GPRS�������ݷ��͹���,����Ƿ������ݶ�ʧ
    short i,size;
    ULONG sendCount=0;
    BYTE OK_Send;
    ULONG tstID=1;

    mClearScreen();

    if (TESTBIT(GPRS_Ready,GPRS_OK_BIT))//ccr2015-03-11
    {
        EmptyComm(GPRSPORT);

        if (GPRSStartGprs())
        {
            DispStrXY(GPRSMess[G_SHUJUFASONGZHONG].str,0,0);
            //ѭ������"H?<<<<<    1"�������
            do
            {
                memset(PCBuffer,0,40);
                size = 30;
                PCBuffer[0]='H';
                PCBuffer[1]=size & 0xff;
                PCBuffer[2]=NETIDLOG;
                sprintf(&PCBuffer[3],"<<<<<%15u",tstID++);

                if (!GPRSSendECRData(PCBuffer,size+2))//������ˮ����
                {
                    OK_Send = false;
                    break;
                }

                //size = GPRSRead_IPDATA(PCBuffer,10,SECONDS(5));//ccr2015-08-25>>>>>>�ȴ�Ӧ��

                sendCount++;

                memset(SysBuf,' ',SCREENWD);
                ULongtoASC(SysBuf+SCREENWD-1,sendCount);
                SysBuf[SCREENWD]=0;
                DispStrXY(SysBuf,0,1);//��ʾ�ѷ���������Ŀ

                OK_Send = true;
            } while (sendCount<20);//���Է���20��

            GPRSCheckACK(0);//�ȴ����ݷ������

            if (OK_Send)//����ʧ��
                DispStrXY(GPRSMess[G_FASONGCHENGGONG].str,0,2);
            else
                DispStrXY(GPRSMess[G_FASONGSHIBAI].str,0,2);

            CloseGPRS();
        }
    }
    else
    {
        DispStrXY(GPRSMess[G_WAITFOR].str,0,0);
    }
    PRESS_ANY_KEY(SCREENLN-2);
#endif
}

///////////////////////////////////////////////////////////////
CONST char ATTXSTATE[]="AT%TXSTATE?\r\n";
/** ccr2015-08-25
 * ��ѯ���ݷ���״̬,�ȴ��������յ����ݵĻظ�ACK
 *
 * @author EutronSoftware (2015-08-25)
 * @param ACKmust:�ȴ�����������ACK
*  @return BYTE
*  �����������������
*[0D][0A]
*[25][54][58][53][54][41][54][45][3A][20][0D][0A]
*[31][2C][35][2C][35][0D][0A]
*[32][2C][30][2C][30][0D][0A]
*[33][2C][30][2C][30][0D][0A]
*[0D][0A]
*[4F][4B][0D][0A]
 */

BYTE GPRSCheckACK(BYTE ACKmust)
{
    char readGPRS[32];
    int readInt[3];
    int i,l,reTry,mul;

#if defined(ACK_MUST)
    if (GPRS_ACK_MUST && ACKmust)
    {
        SetTimerDelay2(SECONDS(60));
        do {
            if ((GPRSRead_IPDATA(readGPRS,sizeof(readGPRS)-5,SECONDS(10))>0 && readGPRS[0]==ACKmust))
                return true;
        } while (GetTimerDelay2());
        //��ACKӦ��,��������
        DisplayPrompt(GPRSxACK);//ccr2016-08-26
        return false;
    }
    else
#endif
    {
        SetTimerDelay2(SECONDS(60));
        do {
            GPRSSendAString(ATTXSTATE,strlen(ATTXSTATE));
            while (!GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(30)))//�ȴ�%TXSTATE:
            {
            }
    //        if (GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(5))>0)
            {
                if (GPRSHand(readGPRS,"%TXSTATE:"))
                {
                    if ((i=GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(30)))>0)//1,1,0
                    {
                        memset(readInt,0,sizeof(readInt));

                        for (l=mul=0;l<i && mul<3;l++)
                        {//��ȡGPRSģ���ѷ��Ͳ��õ�������ȷ�ϵ�������Ŀ
                            if (readGPRS[l]>='0' && readGPRS[l]<='9')
                            {
                                readInt[mul] = readInt[mul]*10+ (readGPRS[l] & 0x0f);
                            }
                            else
                                if (readGPRS[l]==',')
                                    mul++;
                        }
                    }
                    //skip:'2,0,0','3,0,0','NULL'
                    for (i=0;i<4;i++)
                    {
                        if (GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(30))>0)
                        {
                            if (readGPRS[0]=='O' && readGPRS[1]=='K')
                            {
                                if (readInt[1]==readInt[2])
                                    return true;//�������յ�GPRS��ȫ������
                            }
                        }
                    }
                }
            }
        } while (GetTimerDelay2());
        return false;
    }
}

//////////////////////////////////////////////////////////////////
CONST char ATIPSEND[]="AT%IPSEND=";

/**
 * ͨ��GPRS��AT%IPSEND������TCP/IP��ʽ��buffer�е����ݷ��ͳ�ȥ
 * �ڵ���GPRSSendECRData֮ǰ,Ҫ��StartGprs����TCP/IP
 * ����GPRSSendECRData֮��,��EndGprs�ر�TCP/IP
 *
 * @author EutronSoftware (2014-11-28)
 *
 * @param buffer
 * @param len :Bytes in buffer must be send
 *
 * @return int :0=false,else return length
 */
int GPRSSendECRData(BYTE *buffer,int len)
{
#define WAITSEND    RETRYTIMES*20

    char readGPRS[32];
    int i,l,reTry,mul;

    if (len)
    {//������ʱ�ŷ���
        EmptyComm(GPRSPORT);
        GPRSSendAString(ATIPSEND,strlen(ATIPSEND));//"AT%IPSEND=",���ݷ�������
        GPRSSendByte('"');//���ݿ鿪ʼ

        for (i=0;i<len;i++)
            GPRSSendHEX(buffer[i]);//��������

        GPRSSendByte('"');//���ݿ����
        GPRSSendByte('\r');//�������

#if !defined(GPRSWAITACK)
        reTry=0;
        do {
#endif
            if (!GPRSSkipReceived(SECONDS(120))) //skip '\r\n'
                return false;

            if ((i=GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(180)))<=0) // read "%IPSEND 1,13"
                return false;
            readGPRS[7]=0;

            if (!GPRSHand(readGPRS,"%IPSEND"))
                return false;// û���յ� "%IPSEND"

            l=0;mul=1;
            i--;
            for (;i>0 && readGPRS[i]!=',';i--)
            {//��ȡGPRSģ�鷢������ʣ��ռ�����
                if (readGPRS[i]>='0' && readGPRS[i]<='9')
                {
                    l += ((readGPRS[i] & 0x0f)*mul);
                    mul *= 10;
                }
            }
#if !defined(GPRSWAITACK)
            if (reTry>0)//��ʾִ�е���"AT%IPSEND?"��ѯ
            {
                if(!GPRSSkipReceived(SECONDS(120)))	// SKIP one blank line.. add by lqw..090825
                    return FALSE;	// FOR GTM900B ,it will be opened..
            }
#endif
#if (WAITFOROK)
            if (!GPRSWaitForOK(SECONDS(10)))
                return false;//û���յ� "OK"
#else

            if (GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(180))<=0// read "OK"
                 || (CWORD(readGPRS[0])!=RET_OK))
                    return false;//û���յ� "OK"
#endif
#if defined(GPRSWAITACK)
            if (l<=1 && !GPRSCheckACK(0))//ccr2015-08-25
                return false;
#else
            if (l<=1)//��������
            {//��ѯ������
                Delay(300);
                strcpy(readGPRS,ATIPSEND);
                readGPRS[9]='?';
                readGPRS[10]='\r';
                GPRSSendAString(readGPRS,11);//"AT%IPSEND?"��ѯ
                mDrawGPRS(SCREENWD-1,0,0);//ccr2015-08-24�����Ͻ���˸��ʾ��ʾ
            }
            reTry++;
        } while (l<=1 && reTry<WAITSEND);
        if (reTry>=WAITSEND)
        {
            return false;
        }
        else
#endif
            return len;
    }
    else
    {
        return true;
    }
}

//ccr2014-11-26>>>>>>>>>>>>>>>>>>>>>>>>
/*TCP/IP>>>>>>>>>>
ATE0[0d]
AT+CGDCONT=1,"ip","cmnet"[0d];GPRSConnectAPN()
AT%ETCPIP="",""[0d][0a];GPRSRegisterTCPIP()
AT%IPOPEN="TCP","211.147.90.197",55391[0d];GPRSConnect_TCPIP()
AT%IPSEND="12121212121212121212121212"[0d][0a]
AT%IPSEND?[0d][0a]
AT%IPCLOSE[0d] */
/**
 * ͨ��AT%IPSEND �����տ������������ˮ����
 * ����SET��ʱ����������Ϣ��ʾ����Ļ��
 * ����������ʱ����������Ϣ��ʾ��״̬��
 * @author EutronSoftware (2014-12-01)
 */

void GPRSSendECR_LOG()
{
    short i,size;
    ULONG sendCount=0;//���ͼ�����
    ULONG logReadCopyNext=0;//��һ������Ҫ��ȡ����ˮ����
    ULONG logReadCopyLast=0;//��ǰ��ȡ����ˮ����
    BYTE OK_Send;
#if defined(MAXLOGPACKAGE)
    ULONG logSize;//����ָ��������͵���־���ݰ���С
    int  sendFlag;//���ͼ�����
#endif

    if (ApplVar.FlowHeader.ReadP==ApplVar.FlowHeader.NextNP)
        return;
    if (TESTBIT(GPRS_Ready,GPRS_OK_BIT) && GetSystemTimer()>GPRS_Wait)//ccr2015-03-11
    {
        //mClearScreen();
        //DispStrXY(GPRSMess[G_CONNECTING].str,0,0);
        if (GPRSStartGprs())
        {
            if (ApplVar.CentralLock==SET)
                DispStrXY(GPRSMess[G_SHUJUFASONGZHONG].str,0,1);
            else
#if (SCRSTATDBL)
                DispOnStatDBL(GPRSMess[G_SHUJUFASONGZHONG].str,0);
#else
                DispSt1(GPRSMess[G_SHUJUFASONGZHONG].str);//RG-DISPLAY
#endif
            //���ȷ����տ���������
#if defined(CASE_INDONESIA)
            GPRSSendECR_HeartBeat(0xff);//ccr2015-08-03 ECR����ʱ����heartbeat����
            size = sizeof(ApplVar.IP.ECR_ID)+1;
            PCBuffer[0]='F';
            PCBuffer[1]=size & 0xff;
            PCBuffer[2]=NETIDLOG;
            memcpy(&PCBuffer[3],ApplVar.IP.ECR_ID,sizeof(ApplVar.IP.ECR_ID));
#if defined(MAXLOGPACKAGE)
            logSize = sizeof(ApplVar.IP.ECR_ID)+3;//ccr2015-08-26
#endif
#else
            size = 3;
            PCBuffer[0]='F';
            PCBuffer[1]=size & 0xff;
            PCBuffer[2]=ECRNOLOG;
            PCBuffer[3]=REGISTER;
            PCBuffer[4]=LOCATION;
#if defined(MAXLOGPACKAGE)
            logSize = 5;//ccr2015-08-26
#endif
#endif
#if defined(MAXLOGPACKAGE)
#if (PCBUFMAX<1024)
#error "PCBUFMAX<1024"
#endif
            //����PCBuffer,һ�η��Ͳ�����1024�ֽڵ���ˮ����
            do  {//�ڴ�ѭ����,���ȫ����ˮ���ݵķ���
                sendFlag = 0;//������ʾÿ������е���ˮ����
                if (logReadCopyNext!=0)
                    ApplVar.FlowHeader.ReadP = logReadCopyNext;//ccr2015-08-24ָ����һ��Ҫ��ȡ�ͷ��͵���ˮ
                logReadCopyLast = ApplVar.FlowHeader.ReadP;//ccr2015-08-24���浱ǰ��ȡ����ˮ���ݵ�ַ
                logReadCopyNext = logReadCopyLast;//ccr2016-04-18
                do {//�ڴ�ѭ����,���һ������ͷ���
                    size = Read_Flow((BYTE *)&ApplVar.FlowBuff);//��ȡһ����ˮ
                    if (size>0 && (size+logSize)<=1020)
                    {
                        //�����ݴ���PCBuffer,��ɴ��
                        PCBuffer[logSize++]='F';
                        PCBuffer[logSize++]=size;
                        memcpy(PCBuffer+logSize,(BYTE *)&ApplVar.FlowBuff,size);
                        logSize+=size;
                        sendFlag++;
                    }
                    else if (size>=0)// || (size+logSize)>1020)
                    {
                        if (size)
                            SUB_SCANFP(size);
                        if (sendFlag)
                        {//��Ҫ���͵�����,�����ݷ��ͳ�ȥ
                            memset(SysBuf,' ',SCREENWD);
                            OK_Send = ULongtoASC(SysBuf+SCREENWD-1,sendFlag);
                            SysBuf[SCREENWD]=0;
                            if (ApplVar.CentralLock==SET)
                                DispStrXY(SysBuf,0,2);//��ʾ�ѷ���������Ŀ
                            else
                            {
                                SysBuf[0] = OK_Send;
                                DispStrXY(SysBuf+SCREENWD-SysBuf[0],SCREENWD-SysBuf[0],STATELINE);
                            }

                            logReadCopyLast = logReadCopyNext;
                            logReadCopyNext = ApplVar.FlowHeader.ReadP;
                            ApplVar.FlowHeader.ReadP = logReadCopyLast;//���ͳ���ʱ,�´δӴ����·���
                            if (
                                 !GPRSSendECRData(PCBuffer,logSize)//������ˮ����
#if defined(GPRSWAITACK)
                                 || !GPRSCheckACK(ACK)//�ȴ�������Ӧ��
#endif
                                )
                            {//����ʧ��ʱ
                                OK_Send = false;
                                size = 0;//��������.
                            }
                            else
                            {//���ͳɹ�
                                ApplVar.FlowHeader.ReadP = logReadCopyNext;//���ͳɹ�,�´δӴ˷���
                                //ccr2016-04-18 logReadCopyNext = 0;
                                if (sendCount==0) sendCount=1;//���տ��NETID����ˮ
                                sendCount+=sendFlag;
                                OK_Send = true;
                            }
                            logSize = 0;
                        }
                        break;
                    }
                } while (size>0);
            } while (size>0);

            memset(SysBuf,' ',SCREENWD);
            SysBuf[0] = ULongtoASC(SysBuf+SCREENWD-1,sendCount);
            SysBuf[SCREENWD]=0;
            if (OK_Send)
                i = G_FASONGCHENGGONG;
            else
                i = G_FASONGSHIBAI;
            if (ApplVar.CentralLock==SET)
            {
                SysBuf[0]=' ';
                DispStrXY(SysBuf,0,2);//��ʾ�ѷ���������Ŀ
                DispStrXY(GPRSMess[i].str,0,SCREENLN-2);
            }
            else
            {
#if (SCRSTATDBL)
                DispOnStatDBL(GPRSMess[i].str,0);
#else
                DispSt1(GPRSMess[i].str);//RG-DISPLAY
                DispStrXY(SysBuf+SCREENWD-SysBuf[0],SCREENWD-SysBuf[0],STATELINE);
#endif
            }
#else//����������ˮ���ݷ�ʽ>>>>>>>>>>>>
            do
            {
                //����������ˮ����
                if (!GPRSSendECRData(PCBuffer,size+2))//������ˮ����
                {
                    OK_Send = false;
                    break;
                }
                sendCount++;

                if (logReadCopyNext!=0)
                    ApplVar.FlowHeader.ReadP = logReadCopyNext;//ccr2015-08-24ָ����һ��Ҫ��ȡ�ͷ��͵���ˮ

                logReadCopyLast = ApplVar.FlowHeader.ReadP;//ccr2015-08-24���浱ǰ��ȡ����ˮ���ݵ�ַ
                size=Read_Flow(PCBuffer+2);//��ȡ��ˮ����
                logReadCopyNext = ApplVar.FlowHeader.ReadP;//ccr2015-08-24������һ����Ҫ��ȡ����ˮ����
                if (size>0)
                {
                    memset(SysBuf,' ',SCREENWD);
                    OK_Send = ULongtoASC(SysBuf+SCREENWD-1,sendCount);
                    SysBuf[SCREENWD]=0;
                    if (ApplVar.CentralLock==SET)
                        DispStrXY(SysBuf,0,2);//��ʾ�ѷ���������Ŀ
                    else
                    {
                        SysBuf[0] = OK_Send;
                        DispStrXY(SysBuf+SCREENWD-SysBuf[0],SCREENWD-SysBuf[0],STATELINE);
                    }

                    ApplVar.FlowHeader.ReadP = logReadCopyLast;//ccr2015-08-24�ָ�����ȡ����ˮ���ݵ�ַ,�Է����������ȳ���
                    PCBuffer[0]='F';
                    PCBuffer[1]=size;
                }
                OK_Send = true;

            } while (size>0);
#if defined(GPRSWAITACK)
            if (sendCount>0)//��ʾ�ڷ�������ˮ
                 GPRSCheckACK(ACK);//�ȴ�������Ӧ��
#endif
#endif//defined(MAXLOGPACKAGE)

            if (!OK_Send)//����ʧ��
            {
                if (ApplVar.CentralLock==SET || ApplVar.CentralLock==X)
                    DispStrXY(GPRSMess[G_FASONGSHIBAI].str,0,SCREENLN-2);
                else
                {
                    CheckError(ERROR_ID(CWXXI84));
                    //DispSt1(GPRSMess[G_FASONGSHIBAI].str);
                }
            }
            else if (size==0)//��ˮ���ݷ������
            {
#if defined(CASE_INDONESIA)
                ApplVar.LastDaysLog = GetDaysFrom1900(Now.year,Now.month,Now.day);
#endif
#if !defined(MAXLOGPACKAGE)
                if (ApplVar.CentralLock==SET)
                    DispStrXY(GPRSMess[G_FASONGCHENGGONG].str,0,SCREENLN-2);
                else
                {
#if (SCRSTATDBL)
                    DispOnStatDBL(GPRSMess[G_FASONGCHENGGONG].str,0);
#else
                    DispSt1(GPRSMess[G_FASONGCHENGGONG].str);//RG-DISPLAY
                    DispStrXY(SysBuf+SCREENWD-SysBuf[0],SCREENWD-SysBuf[0],STATELINE);
#endif
                }
#endif
            }
            else if (size==-1)//��ˮ���ݹ��ܺų���
            {
                ApplVar.ErrorNumber=ERROR_ID(CWXXI48);
            }
            CloseGPRS();
        }
        if (ApplVar.CentralLock==SET)
            ScrollScreen(1);
    }
    else
    {
        if (ApplVar.CentralLock==SET)
        {
            mClearScreen();
            DispStrXY(GPRSMess[G_WAITFOR].str,0,0);
        }
        else
        {
            ApplVar.ErrorNumber=ERROR_ID(CWXXI89);
#if (SCRSTATDBL)
            DispOnStatDBL(GPRSMess[G_WAITFOR].str,0);
#else
            DispSt1(GPRSMess[G_WAITFOR].str);//RG-DISPLAY
#endif
        }
    }
    if (ApplVar.CentralLock==SET || ApplVar.CentralLock==X)
        PRESS_ANY_KEY(SCREENLN-2);
}

/**
 * ����ȫ��������ˮ����
 *
 * @author EutronSoftware (2014-12-01)
 */
void GPRSSendECR_LOG_All()
{
    mClearScreen();
    DispStrXY(MESS_LOGREPET,0,0);
    if (InputYesNo(Msg[QUERENF].str,0,1,0)=='Y')
    {
        if (TESTBIT(GPRS_Ready,GPRS_OK_BIT))
            ResetECRFlow();
        GPRSSendECR_LOG();
    }
}

/**
 * ������ˮ���ͷ�ʽ
 *
 * @author EutronSoftware (2014-12-01)
 */
void GPRS_SetSendMode()
{
    BYTE y;
    short si;
    WORD saveNumber;

    // ���÷��������վݵķ��Ͳ���
    mClearScreen();
    y = InputYesNo(SENDLOGAUTO,0,0,TESTBIT(ApplVar.DaysMust,BIT7));
    if (y!=0)
    {
        if (y=='Y')
            SETBIT(ApplVar.DaysMust,BIT7);//Ϊ�Զ�������ˮ�������ʺ�����������ˮ
        else
            RESETBIT(ApplVar.DaysMust,BIT7);//���Զ�������ˮ����Ҫ�ֹ�����������ˮ����
        y = 1;
        if (!TESTBIT(ApplVar.DaysMust,BIT7))
        {//���Զ�������ˮ״̬�£���ָ���ļ�������ڣ����뷢����ˮ����
            DispStrXY(DAYSFORLOG,0,1);
    #if (SCREENWD>16)
            y=1;
    #else
            y=2;
    #endif
            DisplayDecXY(ApplVar.DaysMust,SCREENWD-2,y,2);
            si = GetStrFrKBD('9',0,y,2,0);
            if (si<0)
            {
                ClearEntry(false);
                return;
            }
            else if (si>0)
            {
                ApplVar.DaysMust = ((EntryBuffer[ENTRYSIZE-3] & 0x0f)*10 + (EntryBuffer[ENTRYSIZE-2] & 0x0f)) & 0x7f;
            }
            y++;
        }
#if defined(ACK_MUST)
        if (y>=SCREENLN-1)
        {
            ScrollScreen(1);
            y=SCREENLN-2;
        }
        y = InputYesNo(ACKMUSTNEED,0,y,GPRS_ACK_MUST);
        if (y=='Y')
            SETBIT(APPLCTRL,BIT2);      //GPRS�������ͨ��ʱ,��Ҫ����ACKӦ��
        else if (y=='N')
            RESETBIT(APPLCTRL,BIT2);    //GPRS�������ͨ��ʱ,��Ҫ����ACKӦ��
        SETBIT(ApplVar.MyFlags,CONFIGECR);
#endif
    }
    ClearEntry(false);
}

/**
 * �ӷ�����������codePLU1ָ�����տ���ļ�����
 * countPLUΪ��Ҫ���صļ�¼��
 * @author EutronSoftware (2014-12-06)
 *
 * @param typeName :������������
 * @param codePLU1 :�����������ʹ���(PLU1,DEPT,CLERK...),
 * @param countPLU :��¼��,ʵ�ʿ����ص���Ŀ����<countPLU
 *
 * ����codePLU1=0xfff,countPLU=0:����ȫ������
 *
 */
//#define ONLY1   1
#if (0)//defined(ONLY1)
//����һ��ֻ����һ�����ݵķ�ʽ�ӷ�������������,�ٶ���,�ɿ�
void GPRSDownloadEcrPLUData(const char *typeName,WORD codePLU1,WORD countPLU,ULONG sWaitFor)
{
    short sLen;
    WORD received=0;//ͳ���յ���¼��Ŀ
    WORD ECRFunc;
    BYTE decodeLen;

    short chReceived;//ͳ���Ѿ��յ����ֽ�����
    short ch;
    char getIPDATA[16];

    WORD Read_MAX;//GPRSģ���յ���������Ŀ

    if (TESTBIT(GPRS_Ready,GPRS_OK_BIT) && GetSystemTimer()>GPRS_Wait)
    {
        if (countPLU>0)
        {
            if (GPRSStartGprs())
            {
                DispStrXY(typeName,0,1);
                //���ȷ����տ���������
                for (Read_MAX=codePLU1+1;Read_MAX<=codePLU1+countPLU;Read_MAX++)
                {
                    getIPDATA[0]='D';
                    getIPDATA[1]=6;//size
                    CWORD(getIPDATA[2])=Read_MAX;
                    CWORD(getIPDATA[4])=Read_MAX;//Ĭ�������տ�������ɵĵ�Ʒ����
                    getIPDATA[6]=REGISTER;//�տ�����
                    getIPDATA[7]=LOCATION;//�տ���̵���
                    if (GPRSSendECRData(getIPDATA,6+2))//������������.
                    {

                        GPRSDecodeECRRecord(0,0,0);//initial GPRSGetECRARecord

                        if (Read_MAX==PLU1+1)
                            ApplVar.AP.Plu.RNumber = 0;

                        chReceived = GPRSRead_IPDATA(PCBuffer,sizeof(PCBuffer),sWaitFor);
                        if (chReceived)
                        {
                            for (sLen=0;sLen<chReceived;sLen++)
                            {
                                ECRFunc = GPRSDecodeECRRecord('U',PCBuffer[sLen],&decodeLen);
                                //�洢���ص�����>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                if (ECRFunc!=0xffff && ECRFunc!=0)//if (ECRFunc==0) //�վ���ȡ���
                                {
                                    if (ECRFunc>codePLU1 && ECRFunc<=codePLU1+countPLU)
                                    {
                                        ECRFunc -= codePLU1;
                                        switch (codePLU1)
                                        {
                                        case PLU1://�յ���Ϊ��Ʒ����,�����а�����Ʒ������͵�Ʒ����
                                            if (ECRFunc<=ApplVar.AP.Plu.Number && decodeLen==sizeof(ApplVar.Plu)+2)
                                            {
                                                if (ApplVar.AP.Plu.RNumber<ECRFunc)
                                                    ApplVar.AP.Plu.RNumber = ECRFunc;

                                                ApplVar.PluNumber = ECRFunc-1;
                                                memcpy(&ApplVar.Plu,EcrRecord+2,sizeof(ApplVar.Plu));
                                                WritePlu();
                                                received++;
                                            }
                                            break;
                                        case DEPT:
                                            if (ECRFunc<=ApplVar.AP.Dept.Number && decodeLen==sizeof(ApplVar.Dept)+2)
                                            {
                                                ApplVar.DeptNumber = ECRFunc-1;
                                                memcpy(&ApplVar.Dept,EcrRecord+2,sizeof(ApplVar.Dept));
                                                WriteDept();
                                                received++;
                                            }
                                            break;
                                        }
                                        //received++;
                                        memset(SysBuf,' ',SCREENWD);
                                        WORDtoASC(SysBuf+SCREENWD-1,received);
                                        SysBuf[SCREENWD]=0;
                                        DispStrXY(SysBuf,0,2);//��ʾ�ѷ���������Ŀ
                                    }//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                    else
                                    {
                                        DispStrXY(GPRSMess[G_xDATATYPE].str,0,0);//���ݴ�
                                    }
                                }

                            }
                        }
                        else
                            DispStrXY(GPRSMess[G_JIESHOUSHIBAI].str,0,2);//��ʱ��
                    }
                    else
                    {
                        DispStrXY(GPRSMess[G_FASONGSHIBAI].str,0,2);
                    }
                }
                CloseGPRS();
            }
        }
        ScrollScreen(1);
        PRESS_ANY_KEY(SCREENLN-2);//��ʾ��������˳�����
    }
}
#else

/**
 * ����һ�����ض������ݵķ�ʽ�ӷ�������������,�ٶȿ�,��������
 * �ӷ�����������codePLU1ָ�����տ���ļ�����
 * countPLUΪ��Ҫ���صļ�¼��
 * @author EutronSoftware (2014-12-06)
 *
 * @param typeName :������������
 * @param codePLU1 :�����������ʹ���(PLU1,DEPT,CLERK...),
 * @param countPLU :��¼��,ʵ�ʿ����ص���Ŀ����<countPLU
 *
 * ����codePLU1=0xffff,countPLU=0:����ȫ������
 *
 */

void GPRSDownloadEcrPLUData(const char *typeName,WORD codePLU1,WORD countPLU,ULONG sWaitFor)
{

    WORD received=0;//ͳ���յ���¼��Ŀ
    WORD ECRFunc,FuncNum;
    WORD cECRFunc0=0,cECRFunc1=0xffff;//����������ʾ
    BYTE decodeLen;

    short chReceived;//ͳ���Ѿ��յ����ֽ�����
    short ch;
    char getIPDATA[18];

    WORD Read_MAX;//GPRSģ���յ���������Ŀ
    BYTE sByte;
    BYTE sBit=0;
    BYTE Read_WaitFor=0xff;// =0 ��������ͷ "%IPDATA", =1 �������ݳ���; =2,3 �������� //


    if (TESTBIT(GPRS_Ready,GPRS_OK_BIT) && GetSystemTimer()>GPRS_Wait)
    {
        if (countPLU>0 || codePLU1==0xffff)//ccr2016-08-23
        {
            if (GPRSStartGprs())
            {
                memset(SysBuf,' ',SCREENWD);
                CopyFrStr(SysBuf,typeName);
                if (codePLU1!=0xffff)
                    WORDtoASC(SysBuf+SCREENWD-1,countPLU);
                SysBuf[SCREENWD]=0;
                DispStrXY(SysBuf,0,1);
                GotoXY(0,2);
                {
                    getIPDATA[0]='D';//������������
                    getIPDATA[1]=6;//size
                    CWORD(getIPDATA[2])=codePLU1+1;//ccr2016-08-18codePLU1=0xffffʱ,��ӽ��=0,����ȫ������
                    CWORD(getIPDATA[4])=codePLU1+countPLU;//Ĭ�������տ�������ɵĵ�Ʒ����
                    getIPDATA[6]=REGISTER;//�տ�����
                    getIPDATA[7]=LOCATION;//�տ���̵���
                    memcpy(&getIPDATA[8],ApplVar.IP.ECR_ID,sizeof(ApplVar.IP.ECR_ID));
                    if (GPRSSendECRData(getIPDATA,6+2+sizeof(ApplVar.IP.ECR_ID)))//������������.
                    {

                        GPRSDecodeECRRecord(0,0,0);//initial GPRSGetECRARecord

                        ECRFunc= 0xffff;
                        chReceived=0;
                        SetTimerDelay0(sWaitFor);
                        while (GetTimerDelay0() && ECRFunc)
                        {
                            if(KbHit() && (Getch() == ApplVar.AP.FirmKeys[ID_CANCEL]))//ccr2016-08-26
                                    break;
                            ch = ReadComm(GPRSPORT);//��ȡ�ӷ��������ص�����
                            if (ch!=-1)//������
                            {
                                GPRSECH_READ(ch);//testonly
                                switch (Read_WaitFor)
                                {
                                case WAITFOR_IPDATA:
                                    getIPDATA[chReceived++]=ch;
                                    if (ch==':')
                                    {
                                        getIPDATA[chReceived]=0;
                                        if (strcmp(getIPDATA,"%IPDATA:")==0)//	change by lqw %IPDATA->%IPDATA:
                                        {
                                            sBit = 0;
                                            Read_WaitFor = WAITFOR_LENGTH;
                                            chReceived= Read_MAX = 0;
                                        }
                                        else
                                        {
                                            DispStrXY(GPRSMess[G_xDATATYPE].str,0,0xff);//���ݴ�
                                            ECRFunc = 0;// ���ص����ݳ��� //
                                        }
                                    }
                                    else if (chReceived>8)
                                    {
                                        DispStrXY(GPRSMess[G_xDATATYPE].str,0,0xff);//���ݴ�
                                        ECRFunc = 0;// ���ص����ݳ��� //
                                    }
                                    break;
                                case WAITFOR_LENGTH:
                                    if (ch==',')
                                        Read_WaitFor = WAITFOR_QUOTES;
                                    else if (ch>='0' && ch<='9')
                                        Read_MAX = Read_MAX*10 + (ch & 0x0f);// ��ȡ���ݳ��� //
                                    break;
                                case WAITFOR_QUOTES:
                                    if (ch=='"')
                                    {//���ݿ�ʼ
                                        Read_WaitFor = WAITFOR_DATA;
                                        sBit = 0;
#if defined(ACK_MUST)
                                        GPRS_WaitACK=0;
#endif
                                    }
                                    break;
                                case WAITFOR_DATA:
                                    if (ch=='"')//���ݽ���
                                        Read_WaitFor = ENDOF_READ;
                                    else
                                    {
                                        if (sBit)
                                        {//�յ�һ���������ֽ�
                                            chReceived++;
                                            //if (chReceived>=Read_MAX)  return ;// �����д� //

                                            ECRFunc = GPRSDecodeECRRecord('U',(sByte<<4)+ASC_2_HEX(ch),&decodeLen);
                                            //�洢���ص�����>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                            if (ECRFunc!=0xffff && ECRFunc!=0)//if (ECRFunc==0) //�վ���ȡ���
                                            {//���յ�������д���տ���ļ���

                                                if (GPRS_ProcessRecord('U',EcrRecord,decodeLen))
                                                {
                                                    received++;
                                                    memset(SysBuf,' ',SCREENWD);
                                                    if (ECRFunc==ADDPLU)
                                                        SysBuf[0]='+';
                                                    else if(ECRFunc==DELPLU)
                                                        SysBuf[0]='-';
                                                    if (SysBuf[0]!=' ')
                                                    {
                                                        SysBuf[1]='P';SysBuf[2]='L';SysBuf[3]='U';
                                                        if (cECRFunc0 && cECRFunc0!=ECRFunc)
                                                        {
                                                            DispCharXY('\n',0xff,0xff);
                                                            cECRFunc0=ECRFunc;
                                                        }
                                                    }
                                                    else if (codePLU1==0xffff)
                                                    {
                                                        cECRFunc0=ECRFuncCodeToTypeName(ECRFunc,SysBuf);
                                                        if (cECRFunc0!=cECRFunc1)
                                                        {//Ϊ�µĹ�������
                                                            if (cECRFunc1!=0xffff)
                                                                DispCharXY('\n',0xff,0xff);
                                                            received=1;
                                                            cECRFunc1=cECRFunc0;
                                                        }
                                                        if (cECRFunc0)//�й�������
                                                            SysBuf[strlen(SysBuf)]=' ';
                                                        else
                                                            WORDtoASCL(SysBuf,ECRFunc);
                                                    }
                                                    WORDtoASC(SysBuf+SCREENWD-1,received);
                                                    SysBuf[SCREENWD]=0;
                                                    DispStrXY(SysBuf,0,0xff);//��ʾ���յ���������Ŀ
                                                }
                                                else
                                                {
                                                    ScreenFeed(1);
                                                    DispStrXY(GPRSMess[G_xDATATYPE].str,0,0xff);//���ݴ�
                                                }
                                            }//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                        }
                                        else
                                            sByte = ASC_2_HEX(ch);

                                        sBit ^= 1;
                                    }
                                    break;
                                case ENDOF_READ://ccr2016-10-25>>>>>>>>>>
                                    //�ȴ��س�+����
                                    //DispStrXY("END.",0,5);//testonly
#if defined(ACK_MUST)
                                    if (GPRS_ACK_MUST && GPRS_WaitACK)
                                    {
                                        //����ACKӦ��
                                        sByte=ACK;
                                        if ( (!GPRSSendECRData(&sByte,1)//��Ҫ�����ؽ���Ӧ��
#if defined(GPRSWAITACK)
                            //ccr2016-08-11    || !GPRSCheckACK(0)//�ȴ�������Ӧ��
#endif
                                            ))
                                        {//����ʧ��ʱ
                                            //DispStrXY("Send ACK error",0,0xff);//testonly
                                        }
                                        GPRS_WaitACK=false;
                                    }
#endif
                                    if (ch=='\r')
                                        break;
                                    else// if (ch=='\n')
                                    {//�Ѿ���ȡ%IPDATA���ȫ������
                                        Read_WaitFor=0xff;
                                    }
                                    //ccr2016-10-25<<<<<<<<
                                default:
                                    if (ch=='%')//ccr2016-10-25 || ch=='\r' || ch=='\n')
                                    {//�Ѿ���ȡ%IPDATA���ȫ������
                                        Read_WaitFor=WAITFOR_IPDATA;// =0 ��������ͷ "%IPDATA", =1 �������ݳ���; =2,3 �������� //
                                        chReceived= Read_MAX = 0;
                                        //ccr2016-10-25if (ch=='%')
                                            getIPDATA[chReceived++]=ch;
                                    }
                                    break;
                                }
                                SetTimerDelay0(sWaitFor);

                            }
                        }//While
                        if (!GetTimerDelay0())
                        {
                            ScreenFeed(1);
                            DispStrXY(GPRSMess[G_JIESHOUSHIBAI].str,0,0xff);//��ʱ��
                        }
                    }
                    else
                    {
                        ScreenFeed(1);
                        DispStrXY(GPRSMess[G_FASONGSHIBAI].str,0,0xff);
                    }
                }
                CloseGPRS();
            }
            ScrollScreen(1);
        }
	}
	else
	{
		mClearScreen();
#if (SCRSTATDBL)
        DispOnStatDBL(GPRSMess[G_WAITFOR].str,0);
#else
        DispSt1(GPRSMess[G_WAITFOR].str);//RG-DISPLAY
#endif
	}
	PRESS_ANY_KEY(SCREENLN-2);

}
#endif
/**
 * //"���ص�Ʒ�ļ�"
 *
 * @author EutronSoftware (2014-12-06)
 */
void GPRS_DownloadPLU()
{
    GPRSDownloadEcrPLUData(Msg[gprsDownloadPLU].str,PLU1,ApplVar.AP.Plu.Number,SECONDS(30));
}
/**
 * //"���ز����ļ�"
 *
 * @author EutronSoftware (2014-12-06)
 */
void GPRS_DownloadDEPT()
{
    GPRSDownloadEcrPLUData(Msg[gprsDownloadDEPT].str,DEPT,ApplVar.AP.Dept.Number,SECONDS(30));
}
/**
 * //"�����տ�Ա"
 *
 * @author EutronSoftware (2014-12-06)
 */
void GPRS_DownloadCLERK()
{
    GPRSDownloadEcrPLUData(Msg[gprsDownloadCLERK].str,CLERK,ApplVar.AP.Clerk.Number,SECONDS(30));
}
/**
 * //"����Ʊͷ"
 *
 * @author EutronSoftware (2014-12-06)
 */
void GPRS_DownloadHEAD()
{
    //Ϊӭ��GPRSDownloadEcrPLUData�е�CWORD(getIPDATA[2])=codePLU1+1
    //����ʹ��RHEAD1-1��Ϊ����Ʊͷ����
    GPRSDownloadEcrPLUData(Msg[gprsDownloadHEAD].str,RHEAD1-1,2,SECONDS(30));
}
/**
 * //"����Ʊβ"
 *
 * @author EutronSoftware (2014-12-06)
 */
void GPRS_DownloadPTRAIL()
{
    //Ϊӭ��GPRSDownloadEcrPLUData�е�CWORD(getIPDATA[2])=codePLU1+1
    //����ʹ��RTRAIL1-1��Ϊ����Ʊβ����
    GPRSDownloadEcrPLUData(Msg[gprsDownloadTRAIL].str,RTRAIL1-1,2,SECONDS(30));
}

/**
 * //"���ز�����"
 *
 * @author EutronSoftware (2014-12-06)
 */
void GPRS_DownloadALL()
{
    //Ϊӭ��GPRSDownloadEcrPLUData�е�CWORD(getIPDATA[2])=codePLU1+1
    //����ʹ��RTRAIL1-1��Ϊ����Ʊβ����
    //����0xfff,0:����ȫ������
    GPRSDownloadEcrPLUData(Msg[gprsDownloadALL].str,0xffff,0,SECONDS(30));
}

/** ccr2015-08-03>>>>>>>>>>>>>>>>>>>>>
 * ͨ��AT%IPSEND �����տ��heartbeat��Ϣ
 * @author EutronSoftware (2015-08-02)
 *  @param force: =0x00���տ������ʱ����Heart-Beat;
 *                =0x01��������Heart-Beat;
 *                =0xff���÷���Heart-Beat���ӳ�ʱ��
 */
void GPRSSendECR_HeartBeat(BYTE force)
{
    BYTE HeartBuffer[15];
    static ULONG IDLE_HB;//=GetSystemTimer()+SECONDS(ACTIVE*60);//�ȴ�5����;

    if (force==0xff)
    {//=0xff���÷���Heart-Beat���ӳ�ʱ��
        IDLE_HB=GetSystemTimer()+SECONDS(ACTIVE*60);//�ȴ�5����;
    }
    else if (TESTBIT(GPRS_Ready,GPRS_OK_BIT) //GPRSģ����������
             && TESTBIT(DBLHIPRN,BIT5) //������Heart-Beat
             && (force || (ACTIVE && GetSystemTimer()>IDLE_HB)))
    {
        if (GPRSStartGprs())
        {
            //�����տ�����������ΪHeartBeat��Ϣ
            HeartBuffer[0]='H';
            HeartBuffer[1]=sizeof(ApplVar.IP.ECR_ID)+1;
            HeartBuffer[2]=NETIDLOG;
            memcpy(&HeartBuffer[3],ApplVar.IP.ECR_ID,sizeof(ApplVar.IP.ECR_ID));

            GPRSSendECRData(HeartBuffer,sizeof(ApplVar.IP.ECR_ID)+3);//����HeartBeat����
            CloseGPRS();

            IDLE_HB = GetSystemTimer()+SECONDS(ACTIVE*60);//��һ�η���Heart-Beat��ʱ����;
        }
    }
}//<<<<<<<<<<<<<<<<<<<<<<

/**
 * GPRS_ProcessRecord ccr2016-08-19
 * �����յ���¼����,
 *
 * @author EutronSoftware (2015-01-27)
 *
 * @param cmd :'U','D','F'
 * @param data :[func]+[data]
 *     data[0]+data[1]:��Ź�����
 *     data+2:Ϊ��Ӧ�����������
 * @param psize :size of data(=data[0]+1)
 *
 * @return BYTE :=true,�յ�һ������;=false,�յ�һ�����������.
 */

BYTE GPRS_ProcessRecord(char cmd,BYTE *srvData,BYTE psize)
{
//ccr2016-08-19    static UnLong logFirst=0;

//ccr2016-08-19    char sBuffer[sizeof(union FLOWREC)+5];

    WORD start, end, sMax, id, save, type;
    short size;
    UnLong sAddr;
    char *record;
    BYTE sPC,sBAR,sBAL,sEcrNo,sLocate,sEXTMem;
    BYTE err_state=true;
    char cmdReturn=0;//����ֵ��Ϊ0ʱ,��Ҫ����������Ӧ��.


#if !defined(CASE_ASCIIDISPLAY)
      mDrawGPRS(SCREENWD-1,SCREENLN-1,1);//ccr2015-01-29 testonly
#endif

    type = *((WORD *)(srvData));   // type: get the DataType..

    id = 0;
    if (type > CLERK)
        save = ApplVar.ClerkNumber;
    else if (type > SALPER)
        save = ApplVar.SalPerNumber;
    switch (cmd)       /* determine record type */
    {
    case cmdUPDATE://Update the ECR file
//ccr2016-08-19    case cmdDOWNLOAD: //Send ECR file to host
        {
            size = 0;
            record = 0;
            switch (type)
            {
            case PROMO:
                size = sizeof(ApplVar.AP.Promotion);
                record = (char *)&ApplVar.AP.Promotion;
                break;
            case SALPER:
                size = sizeof(ApplVar.AP.SalPer);
                record = (char *)&ApplVar.AP.SalPer;
                break;
            case OPTIONS:
                size = sizeof(ApplVar.AP.Options);
                record = (char *)&ApplVar.AP.Options;
                break;
            case PROGID :  /* program ID data */
                size = sizeof(Release);
                record = (char *)Release;
                break;
            case SYSFLG :  /* system Flags */
                size = sizeof(ApplVar.AP.Flag);
                record = (char *)ApplVar.AP.Flag;
                break;
            case START :  /* start addresses */
                size = sizeof(ApplVar.AP.StartAddress) ;
                record = (char *)ApplVar.AP.StartAddress;
                break;
            case RCONFIG : /* config */
                size = sizeof(ApplVar.AP.Config);
                record = (char *)&ApplVar.AP.Config;
                break;
            case RDAY : /* DAY table */
                size = sizeof(ApplVar.AP.Day);
                record = (char *)&ApplVar.AP.Day;
                break;
            case RMONTH : /* ApplVar.Month table */
                size = sizeof(ApplVar.AP.Month);
                record = (char *)&ApplVar.AP.Month;
                break;
            case RZONE : /* zone table */
                size = sizeof(ApplVar.AP.Zone);
                record = (char *)&ApplVar.AP.Zone;
                break;
            case RTOTAL : /* ApplVar.Total sales */
                size = sizeof(ApplVar.AP.Sales);
                record = (char *)&ApplVar.AP.Sales;
                break;
            case KEY0 :
                size = 64;     /* 64 bytes is 32 keys */
                record = (char *)ApplVar.AP.KeyTable;
                break;
            case KEY32 :
                size = 64;     /* 64 bytes is 32 keys */
                record = (char *)&ApplVar.AP.KeyTable[32];
                break;
    //		case KEY64 :
    //		    size = 64;     /* 64 bytes is 32 keys */
    //			record = (char *)&ApplVar.AP.KeyTable[64];
    //		    break;
    //		case KEY96 :
    //		    size = 64;     /* 64 bytes is 32 keys */
    //			record = (char *)&ApplVar.AP.KeyTable[96];
    //		    break;
            case RREP1 :        /* user report 1,2 & 3 */
                size =  3 * sizeof(struct FIXEDREPORT);
                record = (char *)&ApplVar.AP.ReportList[0];
                break;
            case RREP2 :        /* user report 4,5 & 6 */
                size =  3 * sizeof(struct FIXEDREPORT);
                record = (char *)&ApplVar.AP.ReportList[3];
                break;
            case RREP3 :        /* user report 7,8 & 9 */
                size = 3 * sizeof(struct FIXEDREPORT);
                record = (char *)&ApplVar.AP.ReportList[6];
                break;
#if (salNumber)
			case RREP4 :        /* user report 7,8 & 9 */
				size = 3 * sizeof(struct FIXEDREPORT);
				record = (char *)&ApplVar.AP.ReportList[9];
				break;
			case RREP5 :        /* user report 7,8 & 9 */
				size = 1 * sizeof(struct FIXEDREPORT);
				record = (char *)&ApplVar.AP.ReportList[12];
				break;
#else
            case RREP4 :        /* user report 7,8 & 9 */
                size = 1 * sizeof(struct FIXEDREPORT);
                record = (char *)&ApplVar.AP.ReportList[9];
                break;
#endif

            case REPCAP1 :        /* report types 0 - 6 */
                size = 7 * REPWIDTH;
                record = (char *)ApplVar.TXT.ReportType;
                break;
            case REPCAP2 :        /* report types 7 - 13 */
                size = 7 * REPWIDTH;
                record = (char *)ApplVar.TXT.ReportType[7];
                break;
            case REPCAP3 :        /* messages 14 - 15 */
                size = 2 * REPWIDTH;
                record = (char *)ApplVar.TXT.ReportType[14];
                break;
            case RHEAD1 :       /* receipt header 0 - 4 */
                size = 5 * (PRTLEN+1);
                record = (char *)ApplVar.TXT.Header;
                break;
            case RHEAD2 :       /* receipt header 5 - 7 */
                size = 3 * (PRTLEN+1);
                record = (char *)ApplVar.TXT.Header[5];
                break;
            case RTRAIL1 :       /* receipt trailer 0 - 4 */
                size = 5 * (PRTLEN+1);
                record = (char *)ApplVar.TXT.Trailer;
                break;
            case RTRAIL2 :       /* receipt trailer 5 - 5 */
                size = 1 * (PRTLEN+1);
                record = (char *)ApplVar.TXT.Trailer[5];
                break;
            case RSLIPH1 :       /* slip header 0 - 2 */
                size = 3 * SHEADWIDTH;
                record = (char *)ApplVar.TXT.SlipHeader;
                break;
            case RSLIPH2 :       /* receipt header 3 - 5 */
                size = 3 * SHEADWIDTH;
                record = (char *)ApplVar.TXT.SlipHeader[3];
                break;

            case FIRM :
                size = sizeof(ApplVar.AP.FirmKeys);
                record = (char *)ApplVar.AP.FirmKeys;
                break;
            case MNGR :
                size = sizeof(ApplVar.AP.Manager);
                record = (char *)ApplVar.AP.Manager;
                break;
            case CORREC :
                size = sizeof(ApplVar.AP.Correc);
                record = (char *)&ApplVar.AP.Correc;
                break;
            case CURR :
                size = sizeof(ApplVar.AP.Curr);
                record = (char *)&ApplVar.AP.Curr;
                break;
            case DISC :
                size = sizeof(ApplVar.AP.Disc);
                record = (char *)&ApplVar.AP.Disc;
                break;
            case DRAW :
                size = sizeof(ApplVar.AP.Draw);
                record = (char *)&ApplVar.AP.Draw;
                break;
            case PBF :
                size = sizeof(ApplVar.AP.Pb);
                record = (char *)&ApplVar.AP.Pb;
                break;
            case PORA :
                size = sizeof(ApplVar.AP.PoRa);
                record = (char *)&ApplVar.AP.PoRa;
                break;
            case TEND :
                size = sizeof(ApplVar.AP.Tend);
                record = (char *)&ApplVar.AP.Tend;
                break;
            case MODI :
                size = sizeof(ApplVar.AP.Modi);
                record = (char *)&ApplVar.AP.Modi;
                break;
            case TAX :
                size = sizeof(ApplVar.AP.Tax);
                record = (char *)&ApplVar.AP.Tax;
                break;
            case CLERK :
                size = sizeof(ApplVar.AP.Clerk);
                record = (char *)&ApplVar.AP.Clerk;
                break;
            case GROUP :
                size = sizeof(ApplVar.AP.Group);
                record = (char *)&ApplVar.AP.Group;
                break;
            case DEPT :
                size = sizeof(ApplVar.AP.Dept);
                record = (char *)&ApplVar.AP.Dept;
                break;
            case PLU1 :
                size = sizeof(ApplVar.AP.Plu);
                record = (char *)&ApplVar.AP.Plu;
                break;
            case OFFER:
                size = sizeof(ApplVar.AP.OFFPrice);
                record = (char *)&ApplVar.AP.OFFPrice;
                break;
            case AGREE :
                size = sizeof(ApplVar.AP.Agree);
                record = (char *)&ApplVar.AP.Agree;
                break;
            case BLOCKIC:       //ccr chipcard
                size = sizeof(ApplVar.AP.ICBlock);
                record = (char *)&ApplVar.AP.ICBlock;
                break;
            case CHIPCARDSET:   //ccr chipcard
                size = sizeof(ApplVar.ICCardSet);
                record = (char *)&ApplVar.ICCardSet;
                break;
            case REMOTESETTIME :
                if (TESTBIT(ApplVar.MyFlags,ZREPORT))   /* z report taken ? */
                {
                    CheckError(ERROR_ID(CWXXI13));
                    type = 0xffff;
                } else
                {
                    ApplVar.ErrorNumber=0;
                    memcpy(&EntryBuffer[ENTRYSIZE - 9],&srvData[-1+3],8);
                    Appl_EntryCounter = 8;
                    NewTimeDate(1);
                    memcpy(&EntryBuffer[ENTRYSIZE - 7],&srvData[-1+11],6);
                    Appl_EntryCounter = 6;
                    NewTimeDate(2);
                    if (ApplVar.ErrorNumber)
                    {
                        CheckError(0);
                        type = 0xffff;
                    }
                    ClearEntry(true);
                    InActive |= ACTIVE+1;     /* Inactive longer then allowed */
                    CheckTime(false);
                }
                cmdReturn = cmdANSWER;//ccr2016-08-19return tcp_AnswerToHost(tpcb,cmdANSWER,type);
#if defined(ACK_MUST)
                GPRS_WaitACK = true;
#endif
                return (cmdReturn);//ccr2016-10-27
            default :
                break;
            }//switch(type)
            if (size)
            {//�����տ������������,��Ʊͷ/Ʊβ/����/ϵͳ������
#if defined(ACK_MUST)
                GPRS_WaitACK = true;
#endif
                if (cmd == cmdUPDATE)   /* update */
                {
                    sEcrNo = REGISTER;
                    sLocate = LOCATION;
                    sPC = COMPUTER;
                    sBAR = BARCODE;
                    sBAL = BALANCE;
                    sEXTMem = EXTRAMN;
                    if (type == CHIPCARDSET)
                        sAddr = ApplVar.ICCardSet.PosCode;
                    memcpy(record, &srvData[-1+3], size);//�����ݴ����տ�������ļ���
                    if (type == CHIPCARDSET)
                        ApplVar.ICCardSet.PosCode = sAddr;
                    if (type == SYSFLG)
                    {
                        InitSysFlag();
                        COMPUTER = sPC;
                        BARCODE = sBAR;
                        BALANCE = sBAL;
                        REGISTER = sEcrNo;
                        LOCATION = sLocate;
                        EXTRAMN =  sEXTMem;
                    } else if (type == START)
                    {//���µ�ַ����,�յ��ĵ�ַ����Ϊ��Ե�ַ!!!!
                        ClsXRam();
                        if (ResetStartAddress(true)==false)
                        {
                            Bell(2);
                            DispSt1C(Msg[WJKJYJIE].str);
                            RJPrint(0,Msg[WJKJYJIE].str);


                            //���¼����ڴ��п����ɵĵ�Ʒ��Ŀ
                            sAddr = ApplVar.AP.StartAddress[AddrEndP] - ApplVar.SIZE_EXTRAM;

                            sAddr /= pluRecordSize;
                            sAddr++;//Ϊ��Ҫ���ٵĵ�Ʒ��Ŀ
                            sMax = sAddr;
                            sAddr *= pluRecordSize;//�����ٵĵ�Ʒ��ռ�õĿռ�
                            if (sMax<ApplVar.AP.Plu.Number)
                            {
                                ApplVar.AP.Plu.Number -= sMax;
                                if (ApplVar.AP.Plu.RNumber>ApplVar.AP.Plu.Number)
                                    ApplVar.AP.Plu.RNumber = ApplVar.AP.Plu.Number;
                            } else
                            {
                                RJPrint(0,(char*)cMessageE18);//"!!!! FAT(PLU) ERROR !!!!"
                                ApplVar.AP.Plu.Number = ApplVar.AP.Plu.RNumber = 0;
                            }

                            for (sMax = AddrPLU+1;sMax<AddrMAX;sMax++)
                                ApplVar.AP.StartAddress[sMax] -= sAddr;


                        }
                        ApplVar.MyFlags = 0;
                        //Save_ApplRam();
                    } else if (type == KEY0 || type == KEY32)
                    {
                        DeptPluKeysCount();

                        ApplVar.AP.FirmKeys[ID_xDEPT] = 0xff;
                        ApplVar.AP.FirmKeys[ID_DATE] = 0xff;
                        ApplVar.AP.FirmKeys[ID_RJFEED] = 0xff;
                        ApplVar.AP.FirmKeys[ID_CLEAR] = 0xff;
                        ApplVar.AP.FirmKeys[ID_LOCK] = 0xff;

                        for (id=0;id<MAXKEYB;id++)
                        {
                            switch (ApplVar.AP.KeyTable[id])
                            {
                            case SHIFT1:
                                ApplVar.AP.FirmKeys[ID_xDEPT] = id;
                                break;
                            case DATETIME:
                                ApplVar.AP.FirmKeys[ID_DATE] = id;
                                break;
                            case JPF:
                            case RPF:
                                ApplVar.AP.FirmKeys[ID_RJFEED] = id;
                                break;
                            case CLEAR:
                                ApplVar.AP.FirmKeys[ID_CLEAR] = id;
                                break;
                            case MODELOCK:
                                ApplVar.AP.FirmKeys[ID_LOCK] = id;
                                break;
                            }
                        }
                    }
                    cmdReturn = cmdANSWER;//ccr2016-08-19return tcp_AnswerToHost(tpcb,cmdANSWER,type);//Ӧ��host,�������
                }
                //Ϊ'D'����,���������ݷ��͸�����
                if (type == START)//ת��Ϊ��Ե�ַ���͸�����
                    ResetStartAddress(false);
                cmdReturn = cmdANSWER;//ccr2016-08-19err_state = tcp_RecordToHost(tpcb,cmdUPDATE,type,record,size);/* send record */
                if (type == START)//�ָ�Ϊ���Ե�ַ
                {
                    ResetStartAddress(true);
                    Init_Flow();
                }
                Save_Config(true);//ccr2014-10-30
            } else
            {
                if (type == ADDPLU || type == DELPLU || type == UPDPLU)
                {
                    if (cmd != cmdUPDATE)
                    {
//ccr2016-08-23                        cmdReturn = cmdANSWER;
                        break;
                    }
                    if (ApplVar.AP.Plu.RandomSize && ApplVar.AP.Plu.Number)
                    {
                        ApplVar.Key.Code = 0;   /* suppress repeat */
                        memcpy(&ApplVar.Plu, &srvData[-1+3], sizeof(ApplVar.Plu));
                        ApplVar.PluNumber = GetPluNumber(1, ApplVar.Plu.Random);        /* fill ApplVar.PluNumber with number */
                        switch (type)
                        {
                        case DELPLU:
                            if (ApplVar.PluNumber)
                            {
                                CheckRandomPlu(1, 1);       /* delete plu */
                                SETBIT(ApplVar.MyFlags,CONFIGECR);
                            }
                            break;
                        case ADDPLU:
                            if (!ApplVar.PluNumber)  /* Not Found then move and Add */
                            {
                                CheckRandomPlu(0, 1);//ccr2014-12-10
                                //ccr2014-12-10if (CheckRandomPlu(0, 1))
                                //ccr2014-12-10	ApplVar.PluNumber = GetPluNumber(0, ApplVar.Plu.Random);        /* fill ApplVar.PluNumber with number */
                                SETBIT(ApplVar.MyFlags,CONFIGECR);
                                break;//ccr2014-12-10
                            }
                        case UPDPLU:
                            if (ApplVar.PluNumber)
                            {
                                ApplVar.PluNumber--;
                                WritePlu();
                                SETBIT(ApplVar.MyFlags,CONFIGECR);
                            }
                        default:
                            break;
                        }
                        cmdReturn = cmdDOWNLOAD;//ccr2016-08-19err_state = tcp_AnswerToHost(tpcb,cmdANSWER,type);//Ӧ������,�������ݴ������,����������һ��
                    }
                    break;
                } else if (type > PBTOT)
                {
                    if (cmd == cmdUPDATE)   /* update */
                    {
                        PbTotal(type - PBTOT, 0);
                        if (!(PBINFO & 0x04) && !(PBPRINT & 0x80))       /* open numbers ? */
                            memcpy(ApplVar.PB.Random, &srvData[-1+3], 7);
                        memcpy(ApplVar.PB.Text, &srvData[-1+10], sizeof(ApplVar.PB.Text));
                        PbTotal(type - PBTOT, 3);
                        cmdReturn = cmdDOWNLOAD;//ccr2016-08-19err_state = tcp_AnswerToHost(tpcb,cmdDOWNLOAD,type+1);//Ӧ������,�������ݴ������,����������һ��
                        break;
                    }
                    id = PBTOT + 1;
                    if ((ApplVar.AP.Pb.Random & 0x0f) || ApplVar.AP.Pb.Text)
                        sMax = ApplVar.AP.Pb.NumberOfPb;
                    else
                        sMax = 0;                /* Not active */
                    size = sizeof(ApplVar.PB.Random) + sizeof(ApplVar.PB.Text);
                    record = (char *)ApplVar.PB.Random;
                } else if (type > BLOCKIC)    /* Chipcard for block ? ccr chipcard */
                {
                    if (cmd == cmdUPDATE)   /* update */
                    {
                        ApplVar.ICBlockNumber = type - BLOCKIC - 1;
                        if (ApplVar.ICBlockNumber < ApplVar.AP.ICBlock.Number)
                        {
                            memcpy(&ApplVar.ICBlock, &srvData[-1+3], sizeof(ApplVar.ICBlock));
                            WriteICBlock();
                            cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                        } else
                            cmdReturn = cmdANSWER;
                        break;
                    }
                    id = BLOCKIC + 1;
                    sMax = ApplVar.AP.ICBlock.Number;
                    size = sizeof(ApplVar.ICBlock);
                    record = (char *)&ApplVar.ICBlock;

                } else if (type > PLU1)   /* plu */
                {
                    if (cmd == cmdUPDATE)   /* update */
                    {
                        ApplVar.PluNumber = type - PLU1 - 1;
                        if (ApplVar.PluNumber < ApplVar.AP.Plu.Number)
                        {
                            memcpy(&ApplVar.Plu, &srvData[-1+3], sizeof(ApplVar.Plu));
                            WritePlu();
                            if (ApplVar.PluNumber==0)//ccr2015-02-26
                                ApplVar.AP.Plu.RNumber=0;//ccr2015-02-26
                            if (ApplVar.AP.Plu.RandomSize &&    /* set PLU's used */
                                (ApplVar.PluNumber >= ApplVar.AP.Plu.RNumber))
                            {
                                ApplVar.AP.Plu.RNumber = (ApplVar.PluNumber + 1);
                            }
                            cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                        } else
                            cmdReturn = cmdANSWER;
                        break;
                    }
                    id = PLU1 + 1;
                    if (ApplVar.AP.Plu.RandomSize)    /* set PLU's used */
                        sMax = ApplVar.AP.Plu.RNumber;
                    else
                        sMax = ApplVar.AP.Plu.Number;
                    size = sizeof(ApplVar.Plu);
                    record = (char *)&ApplVar.Plu;
                } else if (type > DEPT)   /* dept */
                {
                    if (cmd == cmdUPDATE)   /* update */
                    {
                        ApplVar.DeptNumber = type - DEPT - 1;
                        if (ApplVar.DeptNumber<ApplVar.AP.Dept.Number)
                        {
                            memcpy(&ApplVar.Dept, &srvData[-1+3], sizeof(ApplVar.Dept));
                            WriteDept();
                            cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                        } else
                            cmdReturn = cmdANSWER;
                        break;
                    }
                    id = DEPT + 1;
                    sMax = ApplVar.AP.Dept.Number;
                    size = sizeof(ApplVar.Dept);
                    record = (char *)&ApplVar.Dept;
                } else if (type > GROUP)   /* group */
                {
                    if (cmd == cmdUPDATE)   /* update */
                    {
                        ApplVar.GroupNumber = type - GROUP - 1;
                        if (ApplVar.GroupNumber<ApplVar.AP.Group.Number)
                        {
                            memcpy(&ApplVar.Group, &srvData[-1+3], sizeof(ApplVar.Group));
                            WriteGroup();
                            cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                        } else
                            cmdReturn = cmdANSWER;
                        break;
                    }
                    id = GROUP + 1;
                    sMax = ApplVar.AP.Group.Number;
                    size = sizeof(ApplVar.Group);
                    record = (char *)&ApplVar.Group;
                } else if (type > OFFER)   /* OFFER */
                {
                    if (cmd == cmdUPDATE)   /* update */
                    {
                        ApplVar.OFFNumber = type - OFFER -1;
                        if (ApplVar.OFFNumber<ApplVar.AP.OFFPrice.Number)
                        {
                            memcpy(&ApplVar.OFFPrice, &srvData[-1+3], sizeof(ApplVar.OFFPrice));
                            WriteOFFPrice();
                            cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                        } else
                            cmdReturn = cmdANSWER;
                        break;
                    }
                    id = OFFER+1;
                    sMax = ApplVar.AP.OFFPrice.Number;
                    size = sizeof(ApplVar.OFFPrice);
                    record = (char *)&ApplVar.OFFPrice;
                } else if (type > CLERK)   /* clerk */
                {
                    if (cmd == cmdUPDATE)   /* update */
                    {
                        if (ApplVar.ClerkNumber<=ApplVar.AP.Clerk.Number)
                        {
                            ApplVar.ClerkNumber = type - CLERK;
                            memcpy(&ApplVar.Clerk, &srvData[-1+3], sizeof(ApplVar.Clerk));
                            WriteClerk();
                            cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                        } else
                            cmdReturn = cmdANSWER;
                        break;
                    }
                    id = CLERK;
                    sMax = ApplVar.AP.Clerk.Number + 1;
                    size = sizeof(ApplVar.Clerk);
                    record = (char *)&ApplVar.Clerk;
                } else if (type > TAX)    /* modifier */
                {
                    if (cmd == cmdUPDATE)   /* update */
                    {
                        ApplVar.TaxNumber = type - TAX - 1;
                        if (ApplVar.TaxNumber<ApplVar.AP.Tax.Number)
                        {
                            memcpy(&ApplVar.Tax, &srvData[-1+3], sizeof(ApplVar.Tax));
                            WriteTax();
                            cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                        } else
                            cmdReturn = cmdANSWER;
                        break;
                    }
                    id = TAX + 1;
                    sMax = ApplVar.AP.Tax.Number;
                    size = sizeof(ApplVar.Tax);
                    record = (char *)&ApplVar.Tax;
                } else if (type > SALPER)    /* sales person */
                {
                    if (cmd == cmdUPDATE)   /* update */
                    {
                        ApplVar.SalPerNumber = type - SALPER;
                        if (ApplVar.SalPerNumber<=ApplVar.AP.SalPer.Number)
                        {
                            memcpy(&ApplVar.SalPer, &srvData[-1+3], sizeof(ApplVar.SalPer));
                            WriteSalPer();
                            cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                        } else
                            cmdReturn = cmdANSWER;
                        break;
                    }
                    id = SALPER;
                    sMax = ApplVar.AP.SalPer.Number+1;
                    size = sizeof(ApplVar.SalPer);
                    record = (char *)&ApplVar.SalPer;
                } else if (type > MODI)    /* modifier */
                {
                    if (cmd == cmdUPDATE)   /* update */
                    {
                        ApplVar.ModiNumber = type - MODI - 1;
                        if (ApplVar.ModiNumber<ApplVar.AP.Modi.Number)
                        {
                            memcpy(&ApplVar.Modi, &srvData[-1+3], sizeof(ApplVar.Modi));
                            WriteModi();
                            cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                        } else
                            cmdReturn = cmdANSWER;
                        break;
                    }
                    id = MODI + 1;
                    sMax = ApplVar.AP.Modi.Number;
                    size = sizeof(ApplVar.Modi);
                    record = (char *)&ApplVar.Modi;
                } else
                {
                    id = (type / 100) * 100 + 1;
                    if (type > TEND)
                    {
                        if (cmd == cmdUPDATE)   /* update */
                        {
                            ApplVar.TendNumber = type - TEND - 1;
                            if (ApplVar.TendNumber<ApplVar.AP.Tend.Number)
                            {
                                memcpy(&ApplVar.Tend, &srvData[-1+3], sizeof(ApplVar.Tend));
                                WriteTender();
                                cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                            } else
                                cmdReturn = cmdANSWER;
                            break;
                        }
                        sMax = ApplVar.AP.Tend.Number;
                        size = sizeof(ApplVar.Tend);
                        record = (char *)&ApplVar.Tend;
                    } else if (type > PORA)
                    {
                        if (cmd == cmdUPDATE)   /* update */
                        {
                            ApplVar.PoRaNumber = type - PORA - 1;
                            if (ApplVar.PoRaNumber<ApplVar.AP.PoRa.Number)
                            {
                                memcpy(&ApplVar.PoRa, &srvData[-1+3], sizeof(ApplVar.PoRa));
                                WritePoRa();
                                cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                            } else
                                cmdReturn = cmdANSWER;
                            break;
                        }
                        sMax = ApplVar.AP.PoRa.Number;
                        size = sizeof(ApplVar.PoRa);
                        record = (char *)&ApplVar.PoRa;
                    } else if (type > PBF)
                    {
                        if (cmd == cmdUPDATE)   /* update */
                        {
                            ApplVar.PbFNumber = type - PBF - 1;
                            if (ApplVar.PbFNumber<ApplVar.AP.Pb.Number)
                            {
                                memcpy(&ApplVar.PbF, &srvData[-1+3], sizeof(ApplVar.PbF));
                                WritePbF();
                                cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                            } else
                                cmdReturn = cmdANSWER;
                            break;
                        }
                        sMax = ApplVar.AP.Pb.Number;
                        size = sizeof(ApplVar.PbF);
                        record = (char *)&ApplVar.PbF;
                    } else if (type > DRAW)
                    {
                        if (cmd == cmdUPDATE)   /* update */
                        {
                            ApplVar.DrawNumber = type - DRAW - 1;
                            if (ApplVar.DrawNumber<ApplVar.AP.Draw.Number)
                            {
                                memcpy(&ApplVar.Draw, &srvData[-1+3], sizeof(ApplVar.Draw));
                                WriteDrawer();
                                cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                            } else
                                cmdReturn = cmdANSWER;
                            break;
                        }
                        sMax = ApplVar.AP.Draw.Number;
                        size = sizeof(ApplVar.Draw);
                        record = (char *)&ApplVar.Draw;
                    } else if (type > DISC)
                    {
                        if (cmd == cmdUPDATE)   /* update */
                        {
                            ApplVar.DiscNumber = type - DISC - 1;
                            if (ApplVar.DiscNumber<ApplVar.AP.Disc.Number)
                            {
                                memcpy(&ApplVar.Disc, &srvData[-1+3], sizeof(ApplVar.Disc));
                                WriteDisc();
                                cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                            } else
                                cmdReturn = cmdANSWER;
                            break;
                        }
                        sMax = ApplVar.AP.Disc.Number;
                        size = sizeof(ApplVar.Disc);
                        record = (char *)&ApplVar.Disc;
                    } else if (type > CURR)
                    {
                        if (cmd == cmdUPDATE)   /* update */
                        {
                            ApplVar.CurrNumber = type - CURR - 1;
                            if (ApplVar.CurrNumber<ApplVar.AP.Curr.Number)
                            {
                                memcpy(&ApplVar.Curr, &srvData[-1+3], sizeof(ApplVar.Curr));
                                WriteCurr();
                                cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                            } else
                                cmdReturn = cmdANSWER;
                            break;
                        }
                        sMax = ApplVar.AP.Curr.Number;
                        size = sizeof(ApplVar.Curr);
                        record = (char *)&ApplVar.Curr;
                    } else if (type > CORREC)
                    {
                        if (cmd == cmdUPDATE)   /* update */
                        {
                            ApplVar.CorrecNumber = type - CORREC - 1;
                            if (ApplVar.CorrecNumber<ApplVar.AP.Correc.Number)
                            {
                                memcpy(&ApplVar.Correc, &srvData[-1+3], sizeof(ApplVar.Correc));
                                WriteCorrec();
                                cmdReturn = cmdDOWNLOAD; //Ӧ������,�������ݴ������,����������һ��
                            } else
                                cmdReturn = cmdANSWER;
                            break;
                        }
                        sMax = ApplVar.AP.Correc.Number;
                        size = sizeof(ApplVar.Correc);
                        record = (char *)&ApplVar.Correc;
                    } else
                    {
                        cmdReturn = cmdANSWER;
                        break;
                    }
                }
#if (0)//ccr2016-08-19 ���ṩ�ϴ��ļ����ݵĹ���
                start = type - id;
                if (start < sMax)
                {//��ָ���ļ���һ����¼���ݷ��͸�����
                    MemSet(record, size, 0);    /* clear memory */
                    memset(sBuffer,' ',INPUTWIDTH);
                    if (type > PBTOT)
                    {
                        CopyFrStr(sBuffer,Msg[SETPBINF].str);
                        PbTotal(start + 1, 0);  /* read */
                    } else if (type > BLOCKIC)//ccr chipcard
                    {
                        CopyFrStr(sBuffer,Msg[GUASHIIC].str);
                        ApplVar.ICBlockNumber = start;
                        ReadICBlock();
                    } else if (type > PLU1)
                    {
                        CopyFrStr(sBuffer,Msg[SETPLU].str);
                        ApplVar.PluNumber= start;
                        ReadPlu();
                    } else if (type > DEPT)
                    {
                        CopyFrStr(sBuffer,Msg[SETDEPT].str);
                        ApplVar.DeptNumber = start;
                        ReadDept();
                    } else if (type > GROUP)
                    {
                        CopyFrStr(sBuffer,Msg[SETGROUP].str);
                        ApplVar.GroupNumber = start;
                        ReadGroup();
                    } else if (type > OFFER)
                    {
                        CopyFrStr(sBuffer,Msg[SETOFF].str);
                        ApplVar.OFFNumber = start;
                        ReadOFFPrice();
                    } else if (type > CLERK)
                    {
                        CopyFrStr(sBuffer,Msg[SETCLERK].str);
                        ApplVar.ClerkNumber = start;
                        ReadClerk();
                    } else if (type > TAX)    /* tax */
                    {
                        CopyFrStr(sBuffer,Msg[SETTAX].str);
                        ApplVar.TaxNumber = start;
                        ReadTax();
                    } else if (type > SALPER)    /* salesperson */
                    {
                        CopyFrStr(sBuffer,Msg[SETSALER].str);
                        ApplVar.SalPerNumber = start;
                        ReadSalPer();
                    } else if (type > MODI)    /* modifier */
                    {
                        CopyFrStr(sBuffer,Msg[SETMODIF].str);
                        ApplVar.ModiNumber = start;
                        ReadModi();
                    } else if (type > TEND)    /* tender */
                    {
                        CopyFrStr(sBuffer,Msg[SETTEND].str);
                        ApplVar.TendNumber = start;
                        ReadTender();
                    } else if (type > PORA)    /* pora */
                    {
                        CopyFrStr(sBuffer,Msg[SETPORA].str);
                        ApplVar.PoRaNumber = start;
                        ReadPoRa();
                    } else if (type > PBF)    /* pb */
                    {
                        CopyFrStr(sBuffer,Msg[SETPBF].str);
                        ApplVar.PbFNumber = start;
                        ReadPbF();
                    } else if (type > DRAW)    /* drawer */
                    {
                        CopyFrStr(sBuffer,Msg[SETDRAWER].str);
                        ApplVar.DrawNumber = start;
                        ReadDrawer();
                    } else if (type > DISC)    /* discount */
                    {
                        CopyFrStr(sBuffer,Msg[SETDISC].str);
                        ApplVar.DiscNumber = start;
                        ReadDisc();
                    } else if (type > CURR)    /* currency */
                    {
                        CopyFrStr(sBuffer,Msg[SETCURR].str);
                        ApplVar.CurrNumber = start;
                        ReadCurr();
                    } else                  /* correction */
                    {
                        CopyFrStr(sBuffer,Msg[SETCORR].str);
                        ApplVar.CorrecNumber = start;
                        ReadCorrec();
                    }
                    WORDtoASC(sBuffer+INPUTWIDTH-1,start);
                    DispSt2(sBuffer);

                    err_state = tcp_RecordToHost(tpcb,cmdUPDATE,type,record, size);//���ͼ�¼����
                } else
                    cmdReturn = cmdANSWER;//������Ҫ������
#endif
            }
        }
        break;
    case cmdCLEAR:           /* clear memory ? */
        if (type == 0x524c) /* command "C  LR" */
        {
            id = ApplVar.CentralLock;
            start = ApplVar.ClerkNumber;
            end = ApplVar.ClerkLock;
            sMax = ApplVar.SalPerNumber;
//				ClearApplMemory();
            ClearAllReport();
            ApplVar.CentralLock = id;
            ApplVar.ClerkNumber = start;
            ApplVar.ClerkLock = end;
            ApplVar.SalPerNumber = sMax;
        }
        cmdReturn = cmdANSWER;
        ARROWS = 0x01;
        break;
#if (0)//ccr2016-08-19 ���ṩ��ȡ��ˮ�Ĺ���
        case cmdINIT:           /* init */
            if (type == 0x544e) /* command "INT" */
            {
                InitApplication(true);//ǿ�ƽ��г�ʼ��
            }
            cmdReturn = cmdANSWER;//Ӧ������,���ݴ������
            ARROWS = 0x01;
            break;
    case cmdFLOWDATA:
        if(ApplVar.FRegi || ApplVar.FlowHeader.ReadP==ApplVar.FlowHeader.NextNP)
        {//������״̬��,��ֹ��ȡ��ˮ����
            cmdReturn = cmdANSWER;
        }
        else
        {//�����տ��������ˮ,���ݷ��͸�ʽ:'F'+[size]+[type1]+[type2]+[data]; [type1]+[type2]Ϊ��ˮ˳���
            if (logFirst!=0)
                ApplVar.FlowHeader.ReadP = logFirst;

            if (type==0)
            {
                logFirst = ApplVar.FlowHeader.ReadP;
                sBuffer[0] = ECRNOLOG;
                sBuffer[1] = REGISTER;
                sBuffer[2] = LOCATION;
                return tcp_RecordToHost(tpcb,cmdFLOWDATA,type,sBuffer, 3);//���ͼ�¼����
            }
            sAddr = ApplVar.FlowHeader.ReadP;
            size = Read_Flow(sBuffer);
            logFirst = ApplVar.FlowHeader.ReadP;
            if (size <= 0)
            {
                if (size==-1)
                {
                    ApplVar.ErrorNumber = (ERROR_ID(CWXXI48));
                }

                cmdReturn = cmdANSWER;
            } else
            {
                ApplVar.FlowHeader.ReadP = sAddr;//�������յ�host��Ӧ���,ȷ��host�յ�������,������FlowHeader.ReadP
                err_state = tcp_RecordToHost(tpcb,cmdFLOWDATA,type,sBuffer, size);//���ͼ�¼����
                if (err_state!=ERR_OK)
                {//����ʧ��,�ָ���ˮָ��
                    ApplVar.ErrorNumber = (ERROR_ID(CWXXI84));
                    cmdReturn = cmdANSWER;
                } else
                    return err_state;
            }
        }
        break;
    case cmdPASSWORD://ccr2015-02-04 Catesir for PWD>>>>>>>>>>>>>>>>
        switch (type)
        {
        case 0:
            memcpy(&ApplVar.AP.ModePwd.PwdX,&srvData[-1+3],MAXPWD);//MAXPWD-1
            break;
        case 1:
            memcpy(&ApplVar.AP.ModePwd.PwdZ,&srvData[-1+3],MAXPWD);
            break;
        case 2:
            memcpy(&ApplVar.AP.ModePwd.PwdSET,&srvData[-1+3],MAXPWD);
            break;
        case 3:
            memcpy(&ApplVar.AP.ModePwd.PwdMG,&srvData[-1+3],MAXPWD);
            break;
        }
        cmdReturn = cmdANSWER;
        break;
#endif
    default :
//ccr2016-08-23        cmdReturn = cmdANSWER;
        break;
    }

    if (cmdReturn)
    {//�����host����Ӧ��

#if (0)//ccr2016-10-25>>>>>
#if defined(ACK_MUST)
        if (GPRS_ACK_MUST)
        {
            //����ACKӦ��
            sEcrNo=ACK;
            if ( cmdReturn==cmdDOWNLOAD && //��Ҫ�����ؽ���Ӧ��
                 (!GPRSSendECRData(&sEcrNo,1)
#if defined(GPRSWAITACK)
//ccr2016-08-11    || !GPRSCheckACK(0)//�ȴ�������Ӧ��
#endif
                ))
            {//����ʧ��ʱ
            }
        }
#endif
#else
#if defined(ACK_MUST)
            GPRS_WaitACK = GPRS_ACK_MUST;
#endif
#endif//ccr2016-10-25<<<<<

    }

    if (type > CLERK && type<OFFER)
    {
        ApplVar.ClerkNumber = save;

        if (save)
        {
            ReadClerk();
        }

    } else if (type > SALPER  && type<TAX)
    {
        ApplVar.SalPerNumber = save;
        ReadSalPer();
    }
    if (TRAINING)
    {
        ApplVar.FTrain = 1 ;
    } else
    {
        ApplVar.FTrain = 0 ;
    }
    return (cmdReturn);
}

//ccr2016-08-26
void GPRS_Restart()
{
    //DispSt1(GPRSMess[G_WAITFOR].str);
    GPRSWaitForReady(true);
    GPRS_Wait = 0;
    KeyFrHost = ApplVar.AP.FirmKeys[ID_CANCEL];//
}

/********************************************************
 * �ȴ�GPRSģ�鷵��Ӧ��"OK"
 *
 * @author EutronSoftware (2017-09-29)
 *
 * @param sWaitFor :�ȴ�ʱ��
 *
 * @return BYTE :=true,�յ�Ӧ��"OK",����û���յ�
 *******************************************************/
BYTE GPRSWaitForOK(ULONG sWaitFor)
{
    char strOK[32];
    short i,j;
    BYTE sEnd=0;

    i =  0;
    strOK[0]=0;
    SetTimerDelay0(sWaitFor);
    while (GetTimerDelay0()>0)
    {
        j = ReadComm(GPRSPORT);
        if (j!=-1)
        {
            GPRSECH_READ(j);//testonly

            SetTimerDelay0(sWaitFor);
            switch (j)
            {
            case '\r':
                if (sEnd!='\r')
                {
                    strOK[i]=0;
                    break;
                }
            case '\n':
                //if (sEnd == '\r')
                {
                    if (i>=2 && CWORD(strOK[0]==RET_OK))
                        return true;
                    else if (i>=5 && CLONG(strOK[0])==RET_ERROR)
                        return false;
                }
                i=0;
                break;
            default:
                if (i<sizeof(strOK)-1)
                    strOK[i++]=j & 0xff;
            }
            sEnd = j & 0xff;
        }
    }
    return (CWORD(strOK[0]==RET_OK));//false;
}

/************************************************
 * ���ź�ǿ��
 *
 * @author EutronSoftware (2017-10-11)
 ************************************************/
CONST char AT_CSQ[]="AT+CSQ\r\n";
void GPRS_DrawSignal()
{
#if !defined(CASE_ASCIIDISPLAY)
    char readGPRS[32];

    short i,j;
    BYTE  s;
#if defined(FOR_DEBUG)
    if (KbHit())
#endif
    if (TESTBIT(GPRS_Ready,GPRS_OK_BIT))
    {
        GPRSSendAString(AT_CSQ,strlen(AT_SIM));

        for (i=0;i<3;i++)
        {
            if ((j=GPRSReadAString(readGPRS,sizeof(readGPRS),SECONDS(10)))>=0)
            {
                if (CWORD(readGPRS[0])==RET_OK)
                    return;
                if (GPRSHand(readGPRS,"+CSQ:"))
                {
                    s=0;
                    for (j=5;j<10 && readGPRS[j]!=',';j++)
                        s=s*10+(readGPRS[j] & 0x0f);
                    if (s>31) s=0;
                    mDrawGPRSSignal(s,SIGNAL_X,SCREENLN-1);
                }
            }
            else
                break;
        }
    }
    //else
    //    mDrawGPRSSignal(0,SIGNAL_X,SCREENLN-1);
#endif
}

#endif
