//---------------------------------------------------------------------------
#ifndef CHNMESS_H
#define CHNMESS_H

#if (defined(CHAR_6X8) && defined(CASE_FORHANZI))
#error "Not allowed same time:CHAR_6X8 & CASE_FORHANZI "
#endif
#if (defined(DEBUGBYPC)&& defined(STM32F10X_HD))
#error "Not allowed same time:DEBUGBYPC & STM32F10X_HD "
#endif

#if (!defined(CHAR_6X8) || defined(CASE_FORHANZI))
#define SETDATEDISPX	6
#define PROMDISPX	    4       //State1��ʾλ��
#define INPUTWIDTH	    12		//RGģʽ��,���������,
#define SETUPDISPX 	    10      //SETģʽ��,����������ʾλ��
#else
#define SETDATEDISPX	8
#define PROMDISPX	    4       //State1��ʾλ��
#define INPUTWIDTH	    12		//RGģʽ��,���������,
#define SETUPDISPX 	    13      //SETģʽ��,����������ʾλ��
#endif

#define INPUTDISPX	(SCREENWD-INPUTWIDTH)	// State2��ʾλ��
#define PROMPTWD	(SCREENWD-PROMDISPX)	//12 hf 20060105

#define SETINPUTWD		(SCREENWD-SETUPDISPX)	//SETģʽ��,����������ʾ���


//----------------------------------------------
#define CursX		ApplVar.sCursor.x
#define CursY		ApplVar.sCursor.y
// MSg[]>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LING			0				//WAIT
#define WAITING          LING
#define SHOUKUAN		(LING+1)		//Ӫҵ
#define XBBIAO			(SHOUKUAN+1)	//����
#define ZBBIAO			(XBBIAO+1)		//����
#define SHEZHI			(ZBBIAO+1)		//����
#define JINLI			(SHEZHI+1)		//����

//vvvvvvvvvvvvvvvv���õ��˵���ص���Ϣ����vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//���õ������˵�����Ŀ���洢��SubMenuItems��

/* ���õ�һ���˵�(���˵�) */
#define MENUFILES		(JINLI+1)		//���Ϲ���
#define ZHGNSZ			(MENUFILES+1)	//ϵͳ����
#define DEFKEYBOARD 	(ZHGNSZ+1)	    //���̶���
#define PJYSSZ			(DEFKEYBOARD+1)	//ƱͷƱβ
#define COMMHOST        (PJYSSZ+1)      //ͨѶ
#define TXKYWS			(COMMHOST+1)    //����豸
#define CYGNSZ			(TXKYWS+1)		//��������
#define BBGNSZ			(CYGNSZ+1)		//�������
#define MENUDISC        (BBGNSZ+1)      //�ۿ۴���
#define JYGLSZ			(MENUDISC+1)	//���۹�������
#define ICKGLI			(JYGLSZ+1)		//IC������
#if !defined(DD_LOCK)
#define QXSZHI			(ICKGLI+1)		//����Ȩ��
#else
#define QXSZHI			(ICKGLI)		//����Ȩ��
#endif
#define MENUSERVICE		(QXSZHI+1)		//ά��(SERVICE)
//���ڲ˵�����,Msg[]������Ϣ>>>>>>>>>>>>>>>.........
#define MENUID_FILES	(1)		//���Ϲ���
#define MENUID_SYS		(MENUID_FILES+1)	//ϵͳ����
#define MENUID_DEFKB 	(MENUID_SYS+1)	    //���̶���
#define MENUID_HEAD		(MENUID_DEFKB+1)	//ƱͷƱβ
#define MENUID_COMM     (MENUID_HEAD+1)      //ͨѶ
#define MENUID_DEV		(MENUID_COMM+1)    //����豸
#define MENUID_RES		(MENUID_DEV+1)		//��������
#define MENUID_REP		(MENUID_RES+1)		//�������
#define MENUID_DISC     (MENUID_REP+1)      //�ۿ۴���
#define MENUID_OP		(MENUID_DISC+1)	//���۹�������
#define MENUID_VIP		(MENUID_OP+1)		//IC������
#if !defined(DD_LOCK)
#define MENUID_PWD		(MENUID_VIP+1)		//����Ȩ��
#else
#define MENUID_PWD		(MENUID_VIP)		//����Ȩ��
#endif
#define MENUID_SERVICE	(MENUID_PWD+1)		//ά��(SERVICE)
#define SUBMENTMAX      (MENUSERVICE-MENUFILES+1)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<........

//���õ������˵�>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    #define SETIDXFROM      (MENUSERVICE+1)           //������Ŀ�Ŀ�ʼ���

    /* ZHGNSZ�µ��ۺϹ������ò˵� */
    #define SETSYSFLAG      SETIDXFROM        //ϵͳ��������
    #define SETPOINTTYPE    (SETSYSFLAG+1)    //����С������
    #define SETDATE		    (SETPOINTTYPE+1)	  //��������
    #define SETTIME 	    (SETDATE+1)  	  //����ʱ��
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
    #define SETEJOURNAL     (SETTIME+1)         //����EJ
#else
    #define SETEJOURNAL     (SETTIME)         //����EJ
#endif
    #define	MENUSYSMAX	    (SETEJOURNAL-SETSYSFLAG+1)		/* ccr2014-11-11 NEWSETUP Step-3 total items of sys menu */

    /* DEFKEYBOARD�µ��ۺϹ������ò˵� */
    #define SETKEYB   	    (SETEJOURNAL+1) 	  //���ü���
    #define SETKEYMACRO     (SETKEYB+1)         //  MESSKEYMACRO            "���̺�"
    #define SETKEYTYPE      (SETKEYMACRO+1)     //  MESSKEYTYPE             "����ģʽ"
    #define SETPRINTKEYB    (SETKEYTYPE+1)      //��ӡ���̲���
    #define	MENUKEYBMAX	    (SETPRINTKEYB-SETKEYB+1)		/* ccr2014-11-11 NEWSETUP Step-3 total items of sys menu */

    /* ����ģʽѡ��*/
    #define SETREST   	    (SETPRINTKEYB+1)		    //���ò�������
    #define SETMARKET       (SETREST+1)		        //���ó��м���
    #define KEYTYPEMAX      (SETMARKET-SETREST+1)   //����ģʽѡ��

    #define SETGROUP   	    (SETMARKET+1)	  //���� //ccr2014-11-11 NEWSETUP Step-3<<<<<<
    #define SETSALER   	    (SETGROUP+1)	    //ӪҵԱ

    /* SPGLSZ�µ���Ʒ����˵� */
    #define SETPLU   	    (SETSALER+1)		 //��Ʒ
    #define SETDEPT   	    (SETPLU+1) 	 //����
#if !defined(CASE_FORHANZI)
    #define SETTAX   	    (SETDEPT+1) 	    //˰��
    #define SETCLERK   	    (SETTAX+1)	    //�տ�Ա
#else
    #define SETCLERK   	    (SETDEPT+1)	    //�տ�Ա
#endif
    #define	MENUPLUMAX	    (SETCLERK-SETPLU+1)	/* total items of plu manages */

    /* COMMHOST�µ�ͨѶ�˵� */
    #define SETCOMPUTER   	(MENUPLUMAX+SETPLU)	    //"�����"
    #define SETIP		    (SETCOMPUTER+1)        //IP��ַ
    //ccr2014-11-11 NEWSETUP Step-3>>>>>>
    #if defined(CASE_GPRS)
    #define SETGPRS         (SETIP+1)
    #else
    #define SETGPRS         (SETIP)
    #endif

    #define	MENUHOSTMAX	    (SETGPRS-SETCOMPUTER+1)		/* total items of comm.port setup */

    /* TXKYWS�µ�����˵� */
    #define SETBARCODE   	    (SETGPRS+1)        //"����ǹ"
    #define SETBALANCE   	    (SETBARCODE+1)        //"���ӳ�"
    //ccr2016-01-22#define SETPORT4   	    (SETBALANCE+1)        //ͨѶ��4
    #define SETSP           (SETBALANCE+1)		    //Ʊ�ݴ�ӡ
    #define SETKP           (SETSP+1)           //������ӡ
    #define SETEXTPRINTER         (SETKP+1)          //"EXTERNAL PRINT"
    #define	MENUCOMMAX	    (SETEXTPRINTER-SETBARCODE+1)		/* total items of comm.port setup */

    #define SETPROM         (SETEXTPRINTER+1)          //�н�����

    /* MENUDISC�µ��ۿ۴�����������*/
    #define SETOFF		    (SETPROM+1)           //�Żݼ�
    #define SETDISC   	    (SETOFF+1)		    //�ۿ�
    #define MENUDISCMAX     (SETDISC-SETOFF+1)

    /* JYGLSZ�µ����۹�������*/
    #define SETTEND   	    (SETDISC+1)		    //���ʽ
    #define SETCORR   	    (SETTEND+1)		    //��������
    #define SETDRAWER       (SETCORR+1)		    //Ǯ��
    #define SETPORA   	    (SETDRAWER+1)		    //�������
    #define SETCURR   	    (SETPORA+1)		    //���
    #define	MENUMANMAX	    (SETCURR-SETTEND+1)		/* total items of comsume manages */

    /* ICKGLI�µ�IC������*/
    #define SETVIPIC           (SETCURR+1)          //IC����VIP����
    #define SETADDNEWVIP       (SETVIPIC+1)  //SetAddNewECRVIP //"ADD NEW VIP"
    #define SETPRINTVIP       (SETADDNEWVIP+1)  //SetPrintECRVIP //"PRINT VIP"
    #define SETCLEANVIP       (SETPRINTVIP+1)   //"CLEAN VIP"
    #define SETBLOCKIC      (SETCLEANVIP+1)           //IC����ʧ
    #define SETPRINTIC	    (SETBLOCKIC+1)	    //��ӡ����Ϣ
    #define	MENUICCMAX	    (SETPRINTIC-SETVIPIC+1)		/* total items of Chip Card */

    /* PJYSSZ�µ�ƱͷƱβ*/
    #define SETHEAD   	    (SETPRINTIC+1)	    //�վ�Ʊͷ
    #define SETTRAIL   	    (SETHEAD+1)         //�վ�Ʊβ
    #define SETSHEAD   	    (SETTRAIL+1) 	    //Ʊ��Ʊͷ
    #define SETGRAP         (SETSHEAD+1)	    //ƱβͼƬ
    #define SETPRTGRAP      (SETGRAP+1)		    //��ӡͼƬ
    #define	MENUTICMAX	    (SETPRTGRAP-SETHEAD+1)		/* total items of tictes */

    /* BBGNSZ�µı�����*/
    #define SETREPORT       (SETPRTGRAP+1)	    //���ñ�������
    #define SETREPTYPE      (SETREPORT+1)	    //����Ԫ
    #define SETZONES   	    (SETREPTYPE+1)	    //����ʱ������
    #define SETCLRREP       (SETZONES+1)	    //���屨��
    #define SETPRTJOUR 	    (SETCLRREP+1)	    //��ӡ��ˮ
    #define	MENUREPMAX	    (SETPRTJOUR-SETREPORT+1)		/* total items of report */

    /* CYGNSZ�µĲ�������*/
    #define SETPBINF   	    (SETPRTJOUR+1)	    //��̨
    #define SETPBF   	    (SETPBINF+1)	    //��������
    #define SETMODIF   	    (SETPBF+1) 	 	    //�˵�˵��
#if (agreeNumber)
xxx    #define SETAGREE        (SETMODIF+1)        //ǩ��
#endif
    #define	MENUTBLMAX	    (SETMODIF-SETPBINF+1)		/* total items of table function */

    /* QXSZHI�µ�����Ȩ������*/
    #if !defined(DD_LOCK)
    #define SETSETPWD       (SETMODIF+1)	    //���õ�����
    #define SETXPWD   	    (SETSETPWD+1)	    //ֻ����������
    #define SETZPWD   	    (SETXPWD+1)		    //���ʱ�������
    #define SETMGPWD   	    (SETZPWD+1)	    //��������
    #define	MENUPWDMAX	    (SETMGPWD-SETSETPWD+1)		/* total items of password setup */
    #else
    #define SETMGPWD   	    (SETMODIF+1)	    //��������
    #endif

    /* MENUSERVICE�µ�ϵͳ���Թ��� */
    #define SETTEST        (SETMGPWD+1)      //ϵͳ����
    #define SETCLEARPLU     (SETTEST+1)      //�����Ʒ
    #define SETPLULIST      (SETCLEARPLU+1)		 //��ӡ��Ʒ�嵥
    #define SETTSTVER	    (SETPLULIST+1)         //��ӡ�汾
    #define SETCONFIGPLU    (SETTSTVER+1)      //���õ�Ʒ
    #define SETCONFIGDEPT   (SETCONFIGPLU+1)              //���ò���
#if CASE_USBDISK
    #define SETINSTALL      (SETCONFIGDEPT+1)    //��װ/����
    #define SETPRINTFAT     (SETINSTALL+1)      //��ӡ�ļ������
#else
    #define SETPRINTFAT     (SETCONFIGDEPT+1)      //��ӡ�ļ������
#endif
    #define SETPRNMENU	    (SETPRINTFAT+1)      //��ӡ���ò˵�
    #define MENUSERVICEMAX  (SETPRNMENU-SETTEST+1)

    /* SKJCSHI�µ�ϵͳ���Թ��� */
    #define SETTSTDISP	    (SETPRNMENU+1)       //��ʾ����
    #define SETTSTCUST	    (SETTSTDISP+1)       //���Բ���
    #define SETTSTPRT	    (SETTSTCUST+1)      //��ӡ����
    #define SETTSTCLK	    (SETTSTPRT+1)       //ʱ�Ӳ���
    #define SETTSTMEM	    (SETTSTCLK+1)       //RAM����
    #define SETTSTBELL	    (SETTSTMEM+1)       //����������
    #define SETTSTDRAW	    (SETTSTBELL+1)      //Ǯ�����
    #define SETTSTKBD	    (SETTSTDRAW+1)      //���̲���
    #define SETTSTCOMM	    (SETTSTKBD+1)       //���ڲ���
    #define SETTSTAUTO	    (SETTSTCOMM+1)      //�Զ�����

    #define	MENUTSTMAX	    (SETTSTAUTO-SETTSTDISP+1)		/* total items of test function */
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    #define SETUPMAX	    SETTSTAUTO	//hf 20060105
    #if (SETUPMAX>254)
    #error "Error on setup IDX" //���ù��ܺŲ���>255
    #endif
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//ccr2016-02-04>>>>ר����ListMenu,Msg[]����Ϣ>>>>>>>>>>>>>>>>>>>>>>>
#define LISTMGFUNC        (SETUPMAX+1)      //ccr2016-01-15 ������ѡ��С�ƹ���ListItem���
#define LISTKEYDES    (LISTMGFUNC+1)      //ccr2016-02-04 ����������ListItem���
#define LISTKEYSID      (LISTKEYDES+1)  //ccr2016-02-04 ��������ϸ����ListItem���
#define LISTNUMRIC      (LISTKEYSID+1)  //ccr2016-02-25 �������б�
//ccr2016-02-04<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define JLHAO			(SETUPMAX+1)	//��¼#
#define SHRDMA			(JLHAO+1)		//��¼?
#define ZONGJI			(SHRDMA+1)		//�ܼ�
#define ZHHUAN			(ZONGJI+1)		//ת��
#define XIAOJI			(ZHHUAN+1)		//С��
#define CHUJIN			(XIAOJI+1)		//����
#define RUJIN			(CHUJIN+1)		//���
#define BAOBIAO			(RUJIN+1)		//����
#define ZENJIA			(BAOBIAO+1)		//����
#define GUAQI			(ZENJIA+1)		//�ҵ�
#define QUXIAO			(GUAQI+1)		//ȡ��
#define MIMA			(QUXIAO+1)		//����
#define MMQREN			(MIMA+1)		//����ȷ��
#define DANJIA			(MMQREN+1)		//����:
#define JINEF			(DANJIA+1)		//���:
#define CHAOSHI			(JINEF+1)		//���а�
#define CANYIN			(CHAOSHI+1)		//������
#define CEISHI			(CANYIN+1)		//����
#define RAM				(CEISHI+1)		//  RAM:
#define YINGFU			(RAM+1)		//Ӧ��
#define JINGE			(YINGFU+1)		//����
#define JIAGE			(JINGE+1)		//�۸�
#define JIAOYISHU		(JIAGE+1)		//������
#define SHULIANG		(JIAOYISHU+1)		//����
#define JINE			(SHULIANG+1)		//���
#define SHOUQU			(JINE+1)		//��ȡ
#define ZHAOLING		(SHOUQU+1)		//����
#define RI				(ZHAOLING+1)		//��
#define ZHOU			(RI+1)		//��
#define YUE				(ZHOU+1)		//��
#define NIAN			(YUE+1)		//��
#define BIAOZHUN		(NIAN+1)		//��׼
#define SHKYUANS		(BIAOZHUN+1)		//�տ�Ա
#define SHI				(SHKYUANS+1)		//   ʱ
#define RIS				(SHI+1)		//   ��
#define YUES			(RIS+1)		//   ��
#define TUIHUO			(YUES+1)		//�˻�
#define CHENBEN			(TUIHUO+1)		//�ɱ�
#define ZUOHAO			(CHENBEN+1)		//����#
#define ZHPHAO			(ZUOHAO+1)		//֧Ʊ��#
#define XIANGSHU		(ZHPHAO+1)		//����:
#define HSHXSHOU		(XIANGSHU+1)		//��˰����
#define SHUIE			(HSHXSHOU+1)		//˰��
#define YEHAO			(SHUIE+1)		//ҳ��
#define HAOMA			(YEHAO+1)		//����:
#define GUAZHE			(HAOMA+1)		//����
#define KAITAI			(GUAZHE+1)		//��̨
#define QZHJSHU			(KAITAI+1)		//���ʼ���
#define QINGCHU			(QZHJSHU+1)		//���
#define SBAOBIAO		(QINGCHU+1)		//S-����
#define MAOLI			(SBAOBIAO+1)		//ë��
#define KCZJIA			(MAOLI+1)		//�������
#define KCJIANSHAO	    (KCZJIA+1)		//�������
#define YZHZHANG		(KCJIANSHAO+1)		//ԭ����:
#define XYKHAO			(YZHZHANG+1)		//���ÿ�#
#define XZHZHANG		(XYKHAO+1)		//������:
#define RENSHU			(XZHZHANG+1)		//����
#define HUANHUO			(RENSHU+1)		//����
#define ZENJIAA			(HUANHUO+1)		//����?
#define SHANCHU			(ZENJIAA+1)		//ɾ��?ZENJIAA��SHANCHU���ܼ��
#define ZHKOU1			(SHANCHU+1)		//�ۿ��� 1
#define ZHKOU2			(ZHKOU1+1)		//�ۿ��� 2
#define XSHOUE			(ZHKOU2+1)		//���۶�
#define DBYHUI			(XSHOUE+1)		//����Ż�
#define KCSHLIANG		(DBYHUI+1)		//�������
#define TJYHUI			(KCSHLIANG+1)		//�ؼ��Ż�
#define XUANXIANG		(TJYHUI+1)		//ѡ��:
#define GDZHKOU			(XUANXIANG+1)		//�̶�
#define FDZHKOU1		(GDZHKOU+1)		//����
#define GFZHKOU1		(FDZHKOU1+1)		//��/��
#define KTZHJIE			(GFZHKOU1+1)		//��̨�ݽ�
#define KTZJIA			(KTZHJIE+1)		//��ӡ��̨
#define ZHANJIE			(KTZJIA+1)		//�ݽ�
#define QRJZHANG		(ZHANJIE+1)		//ȷ�Ͻ���
#define DYKTAI			(QRJZHANG+1)		//��ӡ��̨
#define DYZHDAN			(DYKTAI+1)		//��ӡ�ʵ�
#define QXQREN			(DYZHDAN+1)		//ȡ��ȷ��
#define FENZHANG		(QXQREN+1)		//����
#define ZHUANZHANG		(FENZHANG+1)		//ת��
#define GHSHKYUAN		(ZHUANZHANG+1)		//������̨
#define GKRSHU			(GHSHKYUAN+1)		//�˿�����
#define ZHJSHDING		(GKRSHU+1)		//�н��趨:
#define JIFEN			(ZHJSHDING+1)		//���ѻ���:
#define GBDPJGE			(JIFEN+1)		//�ı䵥Ʒ�۸�
#define CHFDYJZU		(GBDPJGE+1)		//������ӡ����
#define ZJKCUN			(CHFDYJZU+1)		//���ӿ��
#define JSHKCUN			(ZJKCUN+1)		//���ٿ��
#define SHURU			(JSHKCUN+1)		//����
#define DAIFU			(SHURU+1)		//����
#define RS232ERR		(DAIFU+1)		//RS232��
#define RS232OK			(RS232ERR+1)		//RS232��ȷ
#define RTCERR			(RS232OK+1)		//RTC ��!
#define CTCERR			(RTCERR+1)		//CTC ��!
#define FPROMERR		(CTCERR+1)		//FPROM��!
#define CHSHHUA			(FPROMERR+1)		//��ʼ��...
#define SHSHHJSHU		(CHSHHUA+1)		//��ʼ������.
#define CHUCUO			(SHSHHJSHU+1)		//����-
#define MMACUO			(CHUCUO+1)		//����� ��
#define BCMMA			(MMACUO+1)		//�����ѱ���
#define SHKYUANF		(BCMMA+1)		//�տ�Ա:
#define YYYUANF			(SHKYUANF+1)		//ӪҵԱ:
#define SHKJHAO			(YYYUANF+1)		//�տ����:
#define WEIZHI			(SHKJHAO+1)		//λ��:
#define QUERENF			(WEIZHI+1)		//ȷ��?
#define WANCHENG		(QUERENF+1)		//���
#define FXBBEN			(WANCHENG+1)		//���а汾:
#define BCXFEI			(FXBBEN+1)		//�������ѵ�
#define ZJDPIN			(BCXFEI+1)		//������Ʒ:
#define SHCHDP			(ZJDPIN+1)		//ɾ����Ʒ:
#define KSHJCE			(SHCHDP+1)		//��ʼ���>>
#define JCJSHU			(KSHJCE+1)		//<<������
#define KUCUN			(JCJSHU+1)		//���
#define BBQQING			(KUCUN+1)		//������ȫ��!
#define GXBIOS			(BBQQING+1)		//���³�������ϵ�
#define WJKJYJIE		(GXBIOS+1)		//�ļ��ռ�Խ��
#define JSHDPSHL		(WJKJYJIE+1)		//�ڴ������
#define RZQMAN			(JSHDPSHL+1)		//��ˮ�洢����
#define GHDYZHI			(RZQMAN+1)		//�������ӡֽ
#define KZNCCUO			(GHDYZHI+1)		//��չ�ڴ����
#define SHUOMINF		(KZNCCUO+1)		//˵������:

#define CWXXI01			(SHUOMINF+1)		//��Ч����!
#define CWXXI02			(CWXXI01+1)		//��Ч����!
#define CWXXI03			(CWXXI02+1)		//��Чʱ��!
#define CWXXI04			(CWXXI03+1)		//��ֹ����!
#define CWXXI05			(CWXXI04+1)		//PLU����Ϊ��!
#define CWXXI06			(CWXXI05+1)		//PLU�ļ����!
#define CWXXI07			(CWXXI06+1)		//��̨��ռ��!
#define CWXXI08			(CWXXI07+1)		//��̨�Ѵ�!
#define CWXXI09			(CWXXI08+1)		//��̨�Ų���!
#define CWXXI10			(CWXXI09+1)		//��������̨��
#define CWXXI11			(CWXXI10+1)		//��̨û�п�̨
#define CWXXI12			(CWXXI11+1)		//��̨�������
#define CWXXI13			(CWXXI12+1)		//��ֹ�޸�ʱ��
#define CWXXI14			(CWXXI13+1)		//����������!
#define CWXXI15			(CWXXI14+1)		//���ۻ�������
#define CWXXI16			(CWXXI15+1)		//��Ʒû���۳�
#define CWXXI17			(CWXXI16+1)		//���ڽ�����!
#define CWXXI18			(CWXXI17+1)		//�������ݳ���
#define CWXXI19			(CWXXI18+1)		//���ڸ���!
#define CWXXI20			(CWXXI19+1)		//�������!
#define CWXXI21			(CWXXI20+1)		//û��ȷ�Ͻ���
#define CWXXI22			(CWXXI21+1)		//��ֹȡ������
#define CWXXI23			(CWXXI22+1)		//�޲���!
#define CWXXI24			(CWXXI23+1)		//�޴��տ�Ա!
#define CWXXI25			(CWXXI24+1)		//�տ�Ա�ı�
#define CWXXI26			(CWXXI25+1)		//�޴��౨��!
#define CWXXI27			(CWXXI26+1)		//�����ӡ�ж�
#define CWXXI28			(CWXXI27+1)		//�����ھ���
#define CWXXI29			(CWXXI28+1)		//���ܷ���ʱ��
#define CWXXI30			(CWXXI29+1)		//�����������!
#define CWXXI31			(CWXXI30+1)		//ת�뵽
#define CWXXI32			(CWXXI31+1)		//δ��Ȩ!
#define CWXXI33			(CWXXI32+1)		//��ָ���տ�Ա
#define CWXXI34			(CWXXI33+1)		//��ָ��ӪҵԱ
#define CWXXI35			(CWXXI34+1)		//��ֹPLU��ۣ�
#define CWXXI36			(CWXXI35+1)		//���벻��!
#define CWXXI37			(CWXXI36+1)		//������ӡ����
#define CWXXI38			(CWXXI37+1)		//Ʊ�ݴ�ӡ����
#define CWXXI39			(CWXXI38+1)		//��ӡѹ��̧��
#define CWXXI40			(CWXXI39+1)		//��ӡֽ����!
#define CWXXI41			(CWXXI40+1)		//��ӡ�¶�̫��
#define CWXXI42			(CWXXI41+1)		//����δ����!
#define CWXXI43			(CWXXI42+1)		//����������/* zero price not allowed enter amount */
#define CWXXI44			(CWXXI43+1)		//��ֹ���ָ���
#define CWXXI45			(CWXXI44+1)		//�����޴˹���
#define CWXXI46			(CWXXI45+1)		//δ��С�Ƽ�!
#define CWXXI47			(CWXXI46+1)		//���ڹ�����
#define CWXXI48			(CWXXI47+1)		//������ˮ��
#define CWXXI49			(CWXXI48+1)		//MODEMͨѶ��
#define CWXXI50			(CWXXI49+1)		//����������!
#define CWXXI51			(CWXXI50+1)		//POS�����!
#define CWXXI52			(CWXXI51+1)		//�����ݴ�!
#define CWXXI53			(CWXXI52+1)		//Ϊ���ڿ�!
#define CWXXI54			(CWXXI53+1)		//Ϊ��ʧ��!
#define CWXXI55			(CWXXI54+1)		//�ͻ�����!
#define CWXXI56			(CWXXI55+1)		//Ϊ�¿�!
#define CWXXI57			(CWXXI56+1)		//���ǹ��￨!
#define CWXXI58			(CWXXI57+1)		//д������!
#define CWXXI59			(CWXXI58+1)		//���Ų���!
#define CWXXI60			(CWXXI59+1)		//�����ۿۿ�!
#define CWXXI61			(CWXXI60+1)		//�����ֽ�!
#define CWXXI62			(CWXXI61+1)		//�������ʿ�!
#define CWXXI63			(CWXXI62+1)		//�� IC ��!
#define CWXXI64			(CWXXI63+1)		//�忨����!
#define CWXXI65			(CWXXI64+1)		//�������!
#define CWXXI66			(CWXXI65+1)		//IC��ֵ����!
#define CWXXI67			(CWXXI66+1)		//IC��ʼ������
#define CWXXI68			(CWXXI67+1)		//��ֹ��ʼ��!
#define CWXXI69			(CWXXI68+1)		//IC����!
#define CWXXI70			(CWXXI69+1)		//IC�������!
#define CWXXI71			(CWXXI70+1)		//IP��ַ��!
#define CWXXI72			(CWXXI71+1)		//��IC��!
#define CWXXI73			(CWXXI72+1)		//���йҵ�

#define CWXXI74         (CWXXI73+1)         //  ��ص�����"
#define CWXXI75         (CWXXI74+1)         //  û������"
#define CWXXI76         (CWXXI75+1)         // ��U��!     //
#define CWXXI77         (CWXXI76+1)         // ���ļ�����     //
#define CWXXI78         (CWXXI77+1)         // ���ļ�����!     //
#define CWXXI79         (CWXXI78+1)         // д�ļ�����!     //
#define CWXXI80         (CWXXI79+1)         //�����ļ�����     //
#define CWXXI81         (CWXXI80+1)         // �ر��ļ�����     //
                                            //GPRS>>>>>
#define CWXXI82    	    (CWXXI81+1)         //���뷢����ˮ����
#define CWXXI83         (CWXXI82+1)         //GPRS����
#define CWXXI84         (CWXXI83+1)         //�������ݳ���
#define CWXXI85         (CWXXI84+1)         //�������ݳ���
#define CWXXI86         (CWXXI85+1)         //�޷����ӷ�����
#define CWXXI87         (CWXXI86+1)         //�޷�����IP��ַ
#define CWXXI88         (CWXXI87+1)         //��SIM��
#define CWXXI89         (CWXXI88+1)          //GPRSδ����
#define CWXXI90         (CWXXI89+1)          //�ѵ������
#define CWXXI91         (CWXXI90+1)          //�޴˻�Ա

//ccr2016-10-24 EJ >>>>>>>>>>>>>>>>>>>
#define CWXXI92 		(CWXXI91 +1)	    //"EJ DATA ERROR"
#define CWXXI93 		(CWXXI92 +1)         //"NO SD CARD"
#define CWXXI94 		(CWXXI93 +1)         //"EJ R/W ERROR"
#define CWXXI95 		(CWXXI94 +1)         //"NO EJ RECORDS"
#define CWXXI96 		(CWXXI95 +1)         //"EJ NEARLY FULL"
#define CWXXI97 		(CWXXI96 +1)         //"EJ IS FULL"
#define CWXXI98 		(CWXXI97 +1)         //"NEW EJ"
#define CWXXI99 		(CWXXI98 +1)         //"RESET EJ FIRST"
#define CWXXI100		(CWXXI99 +1)         //"EJ NOT MATCHED"

#define CWXXIMAX    	CWXXI100            //������Ϣ��Ŀ<127
//...........................................................

#define DKQXIANG		(CWXXIMAX+1)		//��Ǯ��
#define YOUGUADAN		(DKQXIANG+1)	//�йҵ�
#define SHURUQTYAMT		(YOUGUADAN+1)	//  ������Ʒ��������Ʒ�۸�
#define ZHUANRUDAO      (SHURUQTYAMT+1)    //ZHUANRUDAO "ת�뵽"
#define ERRORMSG		(ZHUANRUDAO+1)	//Error-
#define CURRENCY		(ERRORMSG+1)	//CUR
#define TOTALMSG		(CURRENCY+1)	//TOT
#define CHANGE			(TOTALMSG+1)	//CHG
#define SUBTOTAL		(CHANGE+1)		//SUB
#define DISCOUNT		(SUBTOTAL+1)	//Dis
#define PUTOUT			(DISCOUNT+1)	//PO
#define RECIEVIN		(PUTOUT+1)		//RA
#define OPENDRAW		(RECIEVIN+1)	//DRAW
#define CANCEL			(OPENDRAW+1)	//CANC
#define ADDMODI			(CANCEL+1)		//ADD
#define TABLENUM		(ADDMODI+1)		//TABLE
#define SERVICE			(TABLENUM+1)	//SER
#define CHECKPAID		(SERVICE+1)		//CPA
#define CHECKCPAID		(CHECKPAID+1)	//CCP
#define COVERS			(CHECKCPAID+1)	//COV
#define CORRECT			(COVERS+1)		//COR
#define REFUND			(CORRECT+1)		//RET
#define CANCEL1			(REFUND+1)		//CANCEL 1
#define CANCEL2			(CANCEL1+1)		//CANCEL 2
#define ZZXZZKU			(CANCEL2+1)		//���������ֿ�
#define ZZXZTXING		(ZZXZZKU+1)		//��������ͼ��
#define DOWNLOAD		(ZZXZTXING+1)	//��
#define UPLOAD			(DOWNLOAD+1)	//��
#define KAI				(UPLOAD+1)		//��
#define GUAN			(KAI+1)		    //��
#define MINCHENF		(GUAN+1)		//����:
#define BULEIF			(MINCHENF+1)	//����:
#define GUIZUF			(BULEIF+1)		//����:
#define HOLD			(GUIZUF+1)		//HOLD
#define DAYINF			(HOLD+1)		//��ӡ:
#define XUANXIANGF		(DAYINF+1)		//ѡ��:
#define LIANJIE			(XUANXIANGF+1)	//����:
#define SHUILVF			(LIANJIE+1)		//˰��:
#define WZHBHAOF		(SHUILVF+1)		//λ�ñ��:
#define JIAGE1			(WZHBHAOF+1)	//�۸�1:
#define JIAGE2			(JIAGE1+1)		//�۸�2:
#define JIAGE3			(JIAGE2+1)		//�۸�3:
#define JIAGE4			(JIAGE3+1)		//�۸�4:
#define JINJIA			(JIAGE4+1)		//����:
#define ZHKLVF			(JINJIA+1)		//�ۿ���(%):
#define ZDZHIF			(ZHKLVF+1)		//���ֵ:
#define FIXMSG			(ZDZHIF+1)		//�ۿ���:
#define MAXMSG			(FIXMSG+1)		//���ֵ:
#define HUILVF			(MAXMSG+1)		//˰��:
#define MRJIAF			(HUILVF+1)		//�����:
#define MCHJIAF			(MRJIAF+1)		//������:
#define ZHUANGTAIF		(MCHJIAF+1)		//״̬:
#define QIANXIANGF		(ZHUANGTAIF+1)		//Ǯ��:
#define OTDMSG			(QIANXIANGF+1)		//OTD
#define CHFDYINF		(OTDMSG+1)		//������ӡ:

#define POIMSG			(CHFDYINF+1)		//POI
#define PREMSG			(POIMSG+1)		//����:
#define QIANZHUIFU		(PREMSG+1)		//PER
#define LIANJIEF		(QIANZHUIFU+1)		//����:
#define GNMA			(LIANJIEF+1)		//���빦����
#define AGNJIAN			(GNMA+1)		//�����ܼ�:
#define LEIXING			(AGNJIAN+1)		//����:
#define KSHRQIF			(LEIXING+1)		//��ʼ����:
#define JSHRQIF			(KSHRQIF+1)		//��������:
#define KSHSHJIANF		(JSHRQIF+1)		//��ʼʱ��:
#define JSHSHJIANF		(KSHSHJIANF+1)		//����ʱ��:
#define XINGQIFF		(JSHSHJIANF+1)		//����:
#define ZHEKOUF			(XINGQIFF+1)		//�ۿ�:
#define DBSHLIANGF		(ZHEKOUF+1)		//�������:
#define DANJIAF			(DBSHLIANGF+1)		//����:
#define YHJIAF			(DANJIAF+1)		//�Żݼ�:
#define TXXYIF			(YHJIAF+1)		//ͨѶЭ��:
#define DHHMAF			(TXXYIF+1)		//�绰����:
#define MIMAF			(DHHMAF+1)		//����:
#define PINLV			(MIMAF+1)		//Ƶ��:
#define ZXJERF			(PINLV+1)		//��С���:
#define TXKHAOF			(ZXJERF+1)		//ͨѶ��:
#define JDJER			(TXKHAOF+1)		//�Ƶ���:
#define TXXHAO			(JDJER+1)		//ͼ�����:
#define SHIJIANF		(TXXHAO+1)		//ʱ��:
#define RIQIF			(SHIJIANF+1)	//����:
                                        //
#define DYJXHAO			(RIQIF+1)		//��ӡ���ͺ�
#define DZCHXHAO        (DYJXHAO+1)     //ccr2017-03-16"���ͺ�:",

#define EUTRONMSG		(DZCHXHAO+1)		//���������Ŵ���ͻ�ӭʹ���Ŵ��տ��
#define SHKJSDING		(EUTRONMSG+1)	//  �տ��������
#define AFSHSUO			(SHKJSDING+1)	//������ʽ��������
#define XSHFPIAO		(AFSHSUO+1)		//��ʽ��Ʊ
#define CHFDYJHAO		(XSHFPIAO+1)	//������ӡ��#
#define PXZHTAI			(CHFDYJHAO+1)	//*** ��ѵ״̬ ***
#define JIADIAN			(PXZHTAI+1)		//***** �ӵ� *****
#define FKFZHANG		(JIADIAN+1)		//*** �ֿ����� ***
#define FZHSHJU			(FKFZHANG+1)	//*** �����վ� ***
#define GBPLUJGE		(FZHSHJU+1)		//*** ��Ʒ��� ***
#define ZJIAKUCUN		(GBPLUJGE+1)	//*** ���Ӽ���� ***
#define JSHAOKUCUN		(ZJIAKUCUN+1)	//*** ���Ӽ���� ***
#define QUXIAOP			(JSHAOKUCUN+1)		//***** ȡ�� *****
#define CHXCHSHHUA		(QUXIAOP+1)		//** �����ʼ�� **
#define SELECT1HZ       (CHXCHSHHUA+1)  //"��<ѡ��>��<ȷ��>"
#define KPTOTAL			(SELECT1HZ+1)	//KPTOTAL
#define TITLE			(KPTOTAL+1)		//Ʒ��      ����     ����     ���
#define TITLEQTYAMT		(TITLE+1)	    //Ʒ��      ����        ���
#define TITLEAMT		(TITLEQTYAMT+1)	    //Ʒ��      ����        ���

#define JANUARY			(TITLEAMT+1)	//һ��
#define FEBRUARY		(JANUARY+1)		//����
#define MARCH			(FEBRUARY+1)	//����
#define APRIL			(MARCH+1)		//����
#define MAY			    (APRIL+1)		//����
#define JUNE			(MAY+1)		    //����
#define JULY			(JUNE+1)		//����
#define AUGUST			(JULY+1)		//����
#define SEPTMBER		(AUGUST+1)		//����
#define OCTOBER			(SEPTMBER+1)	//ʮ��
#define NOVEMBER		(OCTOBER+1)		//ʮһ��
#define DECEMBER		(NOVEMBER+1)	//ʮ����
#define MONDAY			(DECEMBER+1)	//����һ
#define TUESDAY			(MONDAY+1)		//���ڶ�
#define WEDNSDAY		(TUESDAY+1)		//������
#define THURSDAY		(WEDNSDAY+1)	//������
#define FRIDAY			(THURSDAY+1)	//������
#define SATURDAY		(FRIDAY+1)		//������
#define SUNDAY			(SATURDAY+1)		//������
#define AQRJIAN			(SUNDAY+1)		//��ȷ�ϼ�...
#define KPDYZE			(AQRJIAN+1)		//��ӡ�ܶ�:
#define KPCXTDY			(KPDYZE+1)		//����ͬ��ӡ
#define KPCBTDY			(KPCXTDY+1)		//�˲�ͬ��ӡ
#define JZHLJGE			(KPCBTDY+1)		//��ֹ��۸�
#define DYFGXIAN		(JZHLJGE+1)		//��ӡ�ָ���
#define DXXSHOU			(DYFGXIAN+1)		//��������:
#define ZHKXIANG1		(DXXSHOU+1)		//�ۿ���1:
#define ZHKXIANG2		(ZHKXIANG1+1)		//�ۿ���2:
#define DKQXIANGF		(ZHKXIANG2+1)		//��Ǯ��:
#define SHRJE			(DKQXIANGF+1)		//������:
#define JZHSHRU			(SHRJE+1)		//��ֹ����:
#define SHRHMA			(JZHSHRU+1)		//�������:
#define ZHLXFEI			(SHRHMA+1)		//����ΪС��
#define DKQXIANGP		(ZHLXFEI+1)		//��Ǯ��:
#define FKFSHJIAN		(DKQXIANGP+1)		//���ʽ��
#define CRJE			(FKFSHJIAN+1)		//������:
#define RJCHJIN			(CRJE+1)		//���/����
#if defined(CASE_INDIA)
#define PORANUMBER      (RJCHJIN+1)     //ccr2016-05-31  ���뿨��
#define DYZHKE			(PORANUMBER+1)		//��ӡ�ۿ۶�
#else
#define DYZHKE			(RJCHJIN+1)		//��ӡ�ۿ۶�
#endif
#define SHYZHK1			(DYZHKE+1)		//ʹ���ۿ�1:
#define SHYZHK2			(SHYZHK1+1)		//ʹ���ۿ�2:
#define MCHJZHLIN		(SHYZHK2+1)		//����������
#define WXSHDIAN		(MCHJZHLIN+1)		//��С����:
#define DKQXIANGD		(WXSHDIAN+1)		//��Ǯ��:
#define YYZZHI			(DKQXIANGD+1)		//Ӫҵ/��ֵ:
#define DYSHLXIANG		(YYZZHI+1)		//��ӡ˰����
#define DYLSHXXI		(DYSHLXIANG+1)		//��ӡ0˰��
#define WGSTSHUI		(DYLSHXXI+1)		//ΪGST��˰
#define DYSHE			(WGSTSHUI+1)		//��ӡ˰��:
#define QXXZHI			(DYSHE+1)		//ȡ������:
#define GGXZHI			(QXXZHI+1)		//��������:
#define QXJYIXZHI		(GGXZHI+1)		//ȡ������:
#define THXZHI			(QXJYIXZHI+1)		//�˻�����:
#define BFBZHKXZHI		(THXZHI+1)		//%�ۿ�����:
#define BFBJCHXZHI		(BFBZHKXZHI+1)		//%�ӳ�����:
#define JJJEXZHI		(BFBJCHXZHI+1)		//+-�������
#define PSHMSHI			(JJJEXZHI+1)		//��ѵģʽ:
#define mPRNINDEX       (PSHMSHI+1)         //Ccr "ȡ�˺�:",
                                            //
#define ECRIPADDRESS    (mPRNINDEX+1)       //"IP Address:"
#define ECRNETID        (ECRIPADDRESS+1)   //"�տ��ID��:"   //

#define SHRLJHAO		(ECRNETID+1)		//<��¼��>  �¼�¼<ȷ��>  ��ǰ��¼
#define SHRDPDMA		(SHRLJHAO+1)		//<����>��ɾ����Ʒ<ȷ��>  ��ǰ��Ʒ
#define TCHBJI			(SHRDPDMA+1)		//<�˳�>      �˳�
#define BJDQJLU			(TCHBJI    +1)		//<ȷ��>      ����
#define ANXZJIAN		(BJDQJLU+1)		//ѡ���ӡ����
#define XFJE			(ANXZJIAN+1)		//���ѽ��
#define AJGNDYI			(XFJE    +1)		//����     //��
#define JLSHYONG		(AJGNDYI+1)		//ֻ���ھ�����
#define YYSHYONG		(JLSHYONG+1)		//����Ӫҵ����
#define DYWZI			(YYSHYONG+1)		//��ӡ����
#define BAOLIU			(DYWZI    +1)		//����
#define SHGNENG			(BAOLIU    +1)		//�ļ��������
#define ZHZBHAO			(SHGNENG+1)		//����
#define MODEMLINK		(ZHZBHAO+1)		//MODEM ����!
#define DAIMA			(MODEMLINK+1)		//����:
#define PZHEKOU			(DAIMA+1)		//%�ۿ�
#define PJIACHEN		(PZHEKOU+1)		//%�ӳ�
#define SHJHAOF			(PJIACHEN+1)		//�վݺ�:
#define	WENJSHU			(SHJHAOF+1)		//�ļ���
#define	WENJKJ			(WENJSHU+1)		//�ļ��ռ�
#define	TJWENJ			(WENJKJ+1)		//ͳ���ļ�
#define	JISHUI			(TJWENJ+1)		//��˰
#define	LIUSKJ			(JISHUI+1)		//��ˮ�ռ�
#define	RAMKB			(LIUSKJ+1)		//RAM(KB)
#define	CONIFOT0		(RAMKB+1)		//�ļ���      ��¼��      �ռ��С
#define	CONIFOT1		(CONIFOT0+1)		//��������    ͨ�����   ͨ��Э��
#define	DBKHSHU			(CONIFOT1+1)		//����������:
#define	MYEHSHU			(DBKHSHU+1)		//ÿҳ����:
#define	DAYXXI			(MYEHSHU+1)		//��ӡ��Ϣ:
#define	DEZPJU			(DAYXXI+1)		//�ڶ���Ʊ��:
#define	ZUOBJU			(DEZPJU+1)		//��߾�:
#define	PDJIXING		(ZUOBJU+1)		//Ʊ�����:
#define DYJGUAN			(PDJIXING+1)		//��ӡ����
#define DYJKAI			(DYJGUAN+1)		//��ӡ����
#define ICSZMIMA		(DYJKAI+1)		//����:
#define ICSZMIMAF		(ICSZMIMA+1)		//����ȷ��:
#define POSDAIMA		(ICSZMIMAF+1)		//POS����:
#define POSDIAMAF		(POSDAIMA+1)		//����ȷ��:
#define BCDMA			(POSDIAMAF+1)		//�����ѱ���
#define DMACUO			(BCDMA+1)		//����� ��
#define ICCA			(DMACUO+1)		//����IC��:
#define ZHEKOUCA		(ICCA+1)		//�ۿۿ�:
#define XIANJINKA		(ZHEKOUCA+1)		//�ֽ�:
#define SHEZHANGKA		(XIANJINKA+1)		//���ʿ�:
#define DAYINICKA		(SHEZHANGKA+1)		//��ӡIC��
#define ZDZHEKOU		(DAYINICKA+1)		//�Զ��ۿ�:
#define XFJIFEN		(ZDZHEKOU+1)		//���ѻ���:
#define XJJIAN			(XFJIFEN+1)		//���ֽ��:
#define QYXYQI			(XJJIAN + 1)		//������Ч��
#define GUASHIIC		(QYXYQI + 1)		//��ʧ��
#define KAHAO			(GUASHIIC+1)		//����:
#define KLXING			(KAHAO+1)		//������:
#define KNJE			(KLXING+1)		//���:
#define KYJIN			(KNJE+1)		//��Ѻ��:
#define XFZE			(KYJIN+1)		//����:
#define CHZHZE			(XFZE+1)		//��ֵ�ܶ�:
#define SHYCSHU			(CHZHZE+1)		//ʹ�ô���:
#define JGLBIE			(SHYCSHU+1)		//�۸񼶱�:
#define PINMA			(JGLBIE+1)		//PIN��:
#define BHJBIE			(PINMA+1)		//��������:
#define ZDJZHANG		(BHJBIE+1)		//�Զ�����:
#define ZHKRQI			(ZDJZHANG+1)		//�ƿ�����:
#define KYXQI			(ZHKRQI+1)		//����Ч��:
#define KHMCHEN			(KYXQI+1)		//�ͻ�:
#define CHSHHICKA		(KHMCHEN+1)		//��ʼ��IC
#define ICKCHZHI		(CHSHHICKA+1)		//IC����ֵ
#define QCHICKA			(ICKCHZHI+1)		//���IC��
#define CHZHTKUAN		(QCHICKA+1)		//��ֵ/�˿�?
#define JDSDIAN			(CHZHTKUAN+1)		//����/�͵�?
#define QRCHZHI			(JDSDIAN+1)		//ȷ�ϳ�ֵ?
#define QRTKUAN			(QRCHZHI+1)		//ȷ���˿�?
#define QRSDIAN			(QRTKUAN+1)		//ȷ���͵�?
#define DJQREN			(QRSDIAN+1)		//�ҽ�ȷ��?
#define XFJDDJIANG		(DJQREN+1)		//�Ƶ�ҽ�
#define ICKTKUAN		(XFJDDJIANG+1)		//IC���˿�
#define ICKDJDIANG		(ICKTKUAN+1)		//IC���ҽ�����
#define ICKSDIAN		(ICKDJDIANG+1)		//IC���͵���
#define QDDAI			(ICKSDIAN+1)		//��ȴ�......
#define KNYJE			(QDDAI+1)		//�����˿�...
#define TMHYHAO			(KNYJE+1)		//��Ա��
#define BARREPORT		(TMHYHAO+1)		//         �� Ա �� �� ��
#define CHXKJI			(BARREPORT+1)		//Ҫ�����µ�IP,�����¿���.
#define ZQBBIAO			(CHXKJI+1)		//ȷ���屨��?
#define WAITICARD		(ZQBBIAO+1)		//�ȴ�IC��....
#define BGDYIN			(WAITICARD+1)		//���ߴ�ӡ

//ccr2015-06-15>>>>>>>>>>>>>>>>>>>>>
#define CLEARIC         (BGDYIN+1)                //"�忨",
#define REFUNDtoIC      (CLEARIC+1)               //"�˿�",
#define PAYMENTbyIC     (REFUNDtoIC+1)            //"����",
#define CHARGEtoIC      (PAYMENTbyIC+1)           //"��ֵ",
#define INITIALIC       (CHARGEtoIC+1)            //"��ʼ��",
#define TAKECAHSfrIC    (INITIALIC+1)             //"ȡ��"
#define ADDVIPPOINTS    (TAKECAHSfrIC+1)             //"���ӻ���"
#define DECVIPPOINTS    (ADDVIPPOINTS+1)             //"���ֶҽ�"
#define VIPPOINTS       (DECVIPPOINTS+1)             //"�ۼƻ���"
//ccr2015-06-15<<<<<<<<<<<<<<<<<<<<<
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MsgEJ_X_STORE      (VIPPOINTS+1)//EJ�д洢X����
#define MsgEJ_Z_STORE      (MsgEJ_X_STORE+1)//EJ�д洢Z����
#define MsgEJ_TR_STORE     (MsgEJ_Z_STORE+1)//EJ�д洢TR����
#else
#define MsgEJ_TR_STORE     (VIPPOINTS)//EJ�д洢TR����
#endif
//ccr2016-02-22>>>>>>>>>>>>>>>>>>>>>
#define MENUXREPORT     (MsgEJ_TR_STORE  +1)  // ��ӡX����
#if (CASE_USBDISK)
#define MENUXEXPORT     (MENUXREPORT   +1)  //������������
#define MENUQUICKVIEW   (MENUXEXPORT   +1)  //Quick View
#else
#define MENUQUICKVIEW   (MENUXREPORT   +1)  //Quick View
#endif
#define MENUXEJFUNC     (MENUQUICKVIEW +1)  //LOG. OPERATION

#if defined(CASE_GPRS)
#define MENUSENDNEWLOG  (MENUXEJFUNC   +1)  //��������ˮ����
#define MENUXPASSWORD   (MENUSENDNEWLOG+1)  //����X����
#else
#define MENUXPASSWORD   (MENUXEJFUNC   +1)  //����X����
#endif

#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MENUXEJOURNAL  (MENUXPASSWORD+1)//MsgMENUXEJOURNAL     //   "E Journal"
#else
#define MENUXEJOURNAL   MENUXPASSWORD   //MsgMENUXEJOURNAL    //   "E Journal"
#endif

#define MENUXITEMMAX    (MENUXEJOURNAL-MENUXREPORT+1)
//.................................
#define MENUZREPORT     (MENUXEJOURNAL +1)  //��ӡZ����
#if (CASE_USBDISK)
#define MENUZEXPORT     (MENUZREPORT   +1)  //������������
#define MENUCLEARLOG     (MENUZEXPORT   +1)  //���LOG
#else
#define MENUCLEARLOG     (MENUZREPORT   +1)  //���LOG
#endif
#define MENUZGRAND      (MENUCLEARLOG   +1)  //�Ƿ����Grand TOTAL
#define MENUZPASSWORD   (MENUZGRAND    +1)  //����Z����

#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MENUZRESETEJ   (MENUZPASSWORD+1)//MsgMENUZRESETEJ  ,     //   "RESET EJ"
#else
#define MENUZRESETEJ    MENUZPASSWORD
#endif

#define MENUZITEMMAX    (MENUZRESETEJ-MENUZREPORT+1)
//...................................

//ccr2016-02-22<<<<<<<<<<<<<<<<<<<<<
#define XZTITLE			(MENUZRESETEJ  +1)
#define XZTITLE1		XZTITLE		//�����ձ���
#define XZTITLE2		(XZTITLE1+1)      //�����±���
#define XZTITLE3		(XZTITLE2+1)      //��Ʒ����
#define XZTITLE4		(XZTITLE3+1)      //���ʱ���
#define XZTITLE5		(XZTITLE4+1)      //ʱ�α���
#define XZTITLE6		(XZTITLE5+1)      //�տ�Ա�ձ���
#define XZTITLE7		(XZTITLE6+1)      //�տ�Ա�±���
#define XZTITLE8		(XZTITLE7+1)      //ȫ�տ�Ա�ձ���
#define XZTITLE9		(XZTITLE8+1)      //ȫ�տ�Ա�±���
#if (salNumber)
#define XZTITLE10		(XZTITLE9+1)      //ӪҵԱ�ձ���
#define XZTITLE11		(XZTITLE10+1)      //ӪҵԱ�±���
#define XZTITLE12		(XZTITLE11+1)      //ȫӪҵԱ�ձ���
#define XZTITLE13		(XZTITLE12+1)      //ȫӪҵԱ�±���
#else
#define XZTITLE13		(XZTITLE9)      //ȫӪҵԱ�±���
#endif
#if (BARCUSTOMER==1)
#define XZTITLE14		(XZTITLE13+1)      //�����Ա����
#define XZITEMSMAX      (XZTITLE14-XZTITLE1+1)
#else
#define XZITEMSMAX      (XZTITLE13-XZTITLE1+1)
#endif
//....................................
#if (CASE_EPOS)
#define ePOSTAC			(XZTITLE1+XZNUM)  //ePOS��֤��:
#define WAITEPOS		(ePOSTAC+1)        //�ȴ���ͨ��
#define ePOSCARNO		(WAITEPOS+1)       //��ͨ����:
#define eCARREMAIN		(ePOSCARNO+1)      //��ͨ�����:
#else
#define eCARREMAIN		(XZTITLE1+XZNUM-1)     //��������     ��������       ���
#endif


#if (CASE_USBDISK)
//ccr090715>>> USB applications >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define usbDAOCHU     (eCARREMAIN+1)		//Ccr�����տ���ļ�//
#define usbDAORU      (usbDAOCHU+1)       //Ccr�����տ���ļ� //
#define usbFLOW       (usbDAORU+1)       //Ccr����������ˮ //

#define usbMAINITEMS  (usbFLOW-usbDAOCHU+1)
//;;;;;;;;;;;;;;;;;;;;

#define usbALL			(usbFLOW+1)         //Ccrȫ���ļ�  //
#define usbBULEI      (usbALL+1)          //Ccr"����",
#define usbDANPIN     (usbBULEI+1)         //Ccr"��Ʒ",
#define usbSHUILV     (usbDANPIN+1)        //Ccr"˰��",
#define usbPIAOTOU    (usbSHUILV+1)         //Ccr"Ʊͷ",
#define usbZHEKOU     (usbPIAOTOU+1)       //Ccr"�ۿ�",
#if (salNumber)
#define usbYYYUAN     (usbZHEKOU+1)        //Ccr"ӪҵԱ",
#define usbSTSHZHI    (usbYYYUAN+1)         //Ccr"ϵͳ����",
#else
#define usbSTSHZHI    (usbZHEKOU+1)         //Ccr"ϵͳ����",
#endif
#define usbTXKOU1     (usbSTSHZHI+1)       //Ccr"ͨѶ��1",
#define usbTUXIN      (usbTXKOU1+1)       //Ccr"ͼ�δ�ӡ",
#define usbGUIZU      (usbTUXIN+1)        //Ccr"����",
#define usbICKA       (usbGUIZU+1)       //Ccr"IC��",
#define usbZHJIANG    (usbICKA+1)           //Ccr"�н�����",
#define usbCANYINGN   (usbZHJIANG+1)         //Ccr"��������",
#define usbSHKYUAN    (usbCANYINGN+1)        //Ccr"�տ�Ա",
#define usbSHUOMIN    (usbSHKYUAN+1)        //Ccr"˵������",
#define usbZHUOTAI    (usbSHUOMIN+1)        //Ccr"��̨",
#define usbSHIDUANG   (usbZHUOTAI+1)         //Ccr"ʱ��",
#define usbJIANPAN    (usbSHIDUANG+1)       //Ccr"����",
#define usbTSHCHJIA   (usbJIANPAN+1)         //Ccr"�������",
#define usbCHJRJIN    (usbTSHCHJIA+1)       //Ccr"�������",
#define usbPIAOWEI    (usbCHJRJIN+1)        //Ccr"Ʊβ",
#define usbPIAOJTOU   (usbPIAOWEI+1)  //Lyq"Ʊ��Ʊͷ",
#define usbICCAGUASHI (usbPIAOJTOU+1)    //ccr"IC����ʧ",

#define usbFILEITEMS	(usbICCAGUASHI-usbALL+1)
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#define usbFLOWNEW      (usbICCAGUASHI+1)   // ����������
#define usbFLOWALL      (usbFLOWNEW+1)      // ����ȫ������
#define usbFLOWALLDEL   (usbFLOWALL+1)      // ����ȫ�����ݺ���� //

#define usbFLOWITEMS	(usbFLOWALLDEL-usbFLOWNEW+1)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define HDEPTREPORT		(usbFLOWALLDEL+1)   //��������     ��������       ���
#else
#define HDEPTREPORT		(eCARREMAIN+1)  //��������     ��������       ���
#endif

#define HPLUREPORT		(HDEPTREPORT+1)    //��Ʒ����     ��������       ���
#define PRESSANYKEY     (HPLUREPORT+1)     //������� MESS_PRESSKEY,         //

#define PRICEBARCODE    (PRESSANYKEY+1)     //ccr2016-01-22 ��������

#define HEADCENTER       (PRICEBARCODE+1)    //SysFlags32,  "Ʊͷ���д�ӡ"
#define TRAILCENTER      (HEADCENTER  +1)    //SysFlags33, "Ʊβ���д�ӡ"
#define HEADDBLHIGH      (TRAILCENTER +1)    //SysFlags34, "Ʊͷ���ߴ�ӡ"
#define TRAILDBLHIGH     (HEADDBLHIGH +1)    //SysFlags35, "Ʊβ���ߴ�ӡ"

//ccr2016-02-17>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�������ܶ���...................
#define MsgMGADDINV    (TRAILDBLHIGH +1)//   "���ӵ�Ʒ���"<(1+С�ƹ���)
#define MsgMGDECINV    (MsgMGADDINV  +1)//   "���ٵ�Ʒ���"<(2+С�ƹ���)
#define MsgMGSETPRICE  (MsgMGDECINV  +1)//   "�޸ĵ�Ʒ�۸�"<(3+С�ƹ���)
#define MsgMGCLEARIC   (MsgMGSETPRICE+1)//   "��Ա�˿�"<(4+С�ƹ���)
#define MsgMGINITIC    (MsgMGCLEARIC +1)//   "��ʼ����Ա��"<(5+С�ƹ���)
#define MsgMGCHARGE    (MsgMGINITIC  +1)//   "��Ա����ֵ"<(6+С�ƹ���)
#define MsgMGADDPOINT  (MsgMGCHARGE  +1)//   "��Ա���ͻ���"<(7+С�ƹ���)
#define MsgMGPRINTSTOCK  (MsgMGADDPOINT+1)//   "��ӡ��Ʒ���"//ccr2017-01-10
#define MsgMGPASSWORD  (MsgMGPRINTSTOCK+1)//    "���þ�������"
#define MsgMGCLOSEPRN  (MsgMGPASSWORD+1)//    "�رմ�ӡ"
#if (!defined(DD_LOCK) || !defined(TR))
#define MsgMGTRAINING  (MsgMGCLOSEPRN+1)//    "��ѵģʽ"
#else
#define MsgMGTRAINING  (MsgMGCLOSEPRN)//    ��"��ѵģʽ"
#endif
#define MsgMGGOTOMG    (MsgMGTRAINING+1)//    "����"
#define MsgMGMMAX      (MsgMGGOTOMG-MsgMGADDINV+1)
//ccr2016-03-09>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define MsgALLLOG         (MsgMGGOTOMG  +1)//MESSALLLOG       "ȫ���վ�"
#define MsgDATERANGE     (MsgALLLOG  +1)//MESSDATERANGE   "���ڷ�Χ"
#define MsgMESSVIPLOG    (MsgDATERANGE  +1)               //MESSVIPLOG        "��Ա���Ѽ�¼"
#define MsgPRNCASH       (MsgMESSVIPLOG  +1)      //"��ӡ�����¼"
#define MsgPRNDEPART     (MsgPRNCASH    +1)    //"��ӡ�����¼"
#define MsgPRNPLU        (MsgPRNDEPART  +1)    //"��ӡ��Ʒ��¼"
#define MsgPRNDISCOUNT   (MsgPRNPLU     +1)    //"��ӡ�ۿۼӳ�"
#define MsgPRNRAPO       (MsgPRNDISCOUNT+1)    //"��ӡ�����"
#define MsgPRNCORRECT    (MsgPRNRAPO    +1)    //"��ӡ��������"
#define MsgPRNCANCEL     (MsgPRNCORRECT +1)  //"��ӡ����ȡ��"
#define MsgPRNNOSALE     (MsgPRNCANCEL +1)    //"��ӡ������"
#define MsgPRNLOGMAX      (MsgPRNNOSALE-MsgALLLOG+1)

#define MsgALLCASH	     (MsgPRNNOSALE  +1)    //"ȫ�����ʽ"
#define MsgSELCASH		 (MsgALLCASH	+1)    //"ѡ�񸶿ʽ"
                                               //
#define MsgALLDEPT		 (MsgSELCASH	+1)    //"��ӡȫ������"
#define MsgSELDEPT		 (MsgALLDEPT	+1)    //"ѡ��һ������"
                                               //
#define MsgALLPLU		 (MsgSELDEPT	+1)    //"��ӡȫ����Ʒ"
#define MsgSELPLU		 (MsgALLPLU	    +1)    //"ѡ��һ����Ʒ"

#define MsgPLUNUMBER        (MsgSELPLU	+1)       // "��¼��:"
#define MsgPLURANDOMSIZE    (MsgPLUNUMBER	+1)   // "����λ��:"
#define MsgPLUNAMESIZE		(MsgPLURANDOMSIZE +1) // "���Ƴ���:"
#define MsgPLUPRICESIZE     (MsgPLUNAMESIZE   +1) // "�۸�λ��:"
#define MsgPLUPRICELEVEL    (MsgPLUPRICESIZE  +1) // "��Ա�ۼ���:"
#define MsgPLUCOSTSIZE      (MsgPLUPRICELEVEL +1) // "����λ��:"
#define MsgPLUINVENTSIZE    (MsgPLUCOSTSIZE   +1) // "���λ��:"
#define MsgPLUREPQTYSIZE    (MsgPLUINVENTSIZE +1) // "ͳ������λ��:"
#define MsgPLUREPAMTSIZE    (MsgPLUREPQTYSIZE +1) // "ͳ�ƽ��λ��:"
#define MsgPLUREPDISCSIZE   (MsgPLUREPAMTSIZE +1) // "ͳ���ۿ�λ��:"
#define MsgPLUREPCOSTSIZE   (MsgPLUREPDISCSIZE+1) // "ͳ�ƽ���λ��:"
//ccr2016-03-09<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//.......................................................
#define MsgDATETYPE     (MsgPLUREPCOSTSIZE+1)  //"FORMAT "
#define MsgDDMMYYYY     (MsgDATETYPE+1)    //"DDMMYYYY"
#define MsgMMDDYYYY     (MsgDDMMYYYY+1)    //"MMDDYYYY"
#define MsgYYYYMMDD     (MsgMMDDYYYY+1)    //"YYYYMMDD"

//ccr2016-04-05>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define MsgPOINTTYPE1       (MsgYYYYMMDD+1)//"1.000,00"  //��λС��
#define MsgPOINTTYPE2       (MsgPOINTTYPE1+1)// "1,000.00"  //��λС��
#define MsgPOINTTYPE3       (MsgPOINTTYPE2+1)// "1.000"     //��С��
#define MsgPOINTTYPE4       (MsgPOINTTYPE3+1)// "1,000"     //��С��
#if !defined(CASE_FORHANZI)
#define MsgPOINTTYPE5       (MsgPOINTTYPE4+1)// "1.000,000"  //��λС��
#define MsgPOINTTYPE6       (MsgPOINTTYPE5+1)// "1,000.000"  //��λС��
#else
#define MsgPOINTTYPE6       (MsgPOINTTYPE4)
#endif
//#define MsgPOINTTYPE7       (MsgPOINTTYPE6+1)// "1.000,0"  //һλС��
//#define MsgPOINTTYPE8       (MsgPOINTTYPE7+1)// "1,000.0"  //һλС��
#define MsgPOINTMAX         (MsgPOINTTYPE6-MsgPOINTTYPE1+1)
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//ccr2016-10-31>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))
#define MsgEJMESSAGES     (MsgPOINTTYPE6+1) //"EJ�洢��Ϣ"
#define MsgEJALLEJ        (MsgEJMESSAGES+1)//"��ӡȫ��EJ"
#define MsgEJDATERANGE    (MsgEJALLEJ    +1)// "���ڷ�ΧEJ"
#define MsgEJRECEIPT      (MsgEJDATERANGE+1)// "��ӡ�վ�EJ"
#define MsgEJXREPORT      (MsgEJRECEIPT  +1)// "��ӡX-EJ"
#define MsgEJZREPORT      (MsgEJXREPORT  +1)// "��ӡZ-EJ"
#define MsgEJCLERK        (MsgEJZREPORT  +1)//"��ӡ�տ�ԱEJ"    

#define MsgPRNEJMAX      (MsgEJCLERK-MsgEJMESSAGES+1)
#else
#define MsgEJCLERK         MsgPOINTTYPE6
#endif
//ccr2016-10-31<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#if defined(CASE_QRCODE)
#define MsgQRCODE           (MsgEJCLERK+1)//"��ά��"
#else
#define MsgQRCODE           MsgEJCLERK
#endif

#define GPRSSERVERIP	(MsgQRCODE+1)//
#define GPRSSERVERPORT  (GPRSSERVERIP+1)

#if (!defined(CASE_GPRS))		// ADD BY LQW 090827
#define HZMESSMAX (GPRSSERVERPORT+1)
#else
//ccr2014-11-11 NEWSETUP Step-4 �Ӳ˵���Ŀ��Ϣ���>>>>>>>>>>>>>>
#define GPRSAPNNAME     (GPRSSERVERPORT+1)
#define GPRSUSERNAME    (GPRSAPNNAME+1)
#define GPRSPASSWORD    (GPRSUSERNAME+1)

#define gprsSETMODE  (GPRSPASSWORD+1)
#define gprsSendECRLogAll (gprsSETMODE+1)
#define gprsDownloadPLU     (gprsSendECRLogAll+1) //"���ص�Ʒ�ļ�"
#define gprsDownloadDEPT    (gprsDownloadPLU+1)     //"���ز����ļ�"
#define gprsDownloadCLERK   (gprsDownloadDEPT+1) //"�����տ�Ա"
#define gprsDownloadHEAD    (gprsDownloadCLERK+1) //"����Ʊͷ"
#define gprsDownloadTRAIL   (gprsDownloadHEAD+1) //"����Ʊβ"
#define gprsDownloadALL   (gprsDownloadTRAIL+1) //"����ȫ������"
#define gprsRestart         (gprsDownloadALL+1)//  "��λGPRS"    //gprsRestart //ccr2016-08-26
#define gprsSENDMESS    (gprsRestart+1)

#define gprsMAINITEMS   (10)        //�Ӳ˵���Ŀ��,��Ҫ�޸�MENUGPRSFUNSMAX

#define HZMESSMAX	    (gprsSENDMESS+1) //<<<<<<<<
// MSg[]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>added by lqw 09-08-02
#define G_xDATATYPE 0                                            //ccr"�������ʹ�"
#define G_GPRSOK                  (G_xDATATYPE+1)                //ccr"GPRS READY"
#define G_GPRSNOTOK               (G_GPRSOK+1)                   //ccr"GPRS ERROR"
#define G_CONFIRM                 (G_GPRSNOTOK+1)                //ccr"��ȷ��"
#define G_SERVERIP_NULL           (G_CONFIRM+1)                 //ccr"������IP��˿ڲ���:"
#define G_X_IPPORT                (G_SERVERIP_NULL+1)           //ccr"������IP��˿ڲ���:"
#define G_WAITFOR                 (G_X_IPPORT+1)                 //ccr�ȴ�GPRS
#define G_SHUJUFASONGZHONG        (G_WAITFOR+1)                      //"���ݷ�����.."
#define G_SHUJUYIFACHU            (G_SHUJUFASONGZHONG+1)         //"�����ѷ���.."
#define G_FASONGCHENGGONG         (G_SHUJUYIFACHU+1)      //"���ͳɹ�.."
#define G_LIANJIESERVERSHIBAI     (G_FASONGCHENGGONG+1)   //"���ӷ�����ʧ��"
#define G_JIESHOUSHIBAI           (G_LIANJIESERVERSHIBAI+1)      //"����ʧ��"
#define G_FASONGSHIBAI            (G_JIESHOUSHIBAI+1)       //"����ʧ��"
#define G_SERVERIP	              (G_FASONGSHIBAI+1)               //
#define G_SERVERPORT              (G_SERVERIP+1)                 //
#define G_CONNECTING              (G_SERVERPORT+1)          // "���ڽ�������.."
#define G_TOCONNECTING            (G_CONNECTING+1)               // "׼����������.."
#define G_FUWEIMOKUAI             (G_TOCONNECTING+1)            // "���ڸ�λģ��.."
#define G_CHENGGONGTUICHU         (G_FUWEIMOKUAI+1)              // "�������,���˳�.."
#define G_GPRSMessMax             (G_CHENGGONGTUICHU+1)

extern CONST GPRSSTR GPRSMess[G_GPRSMessMax]; //ADD BY LQW. 090802
#endif
//<<<<<<<<<<<<<<<<<<<

//---------------------------------------------------------------------------
extern CONST FSTRING Msg[];

//---------------------------------------------------------------------------
#define ERROR_ID(err) (err-CWXXI01+1)

extern CONST char SPACE[2];

extern const char
    cMsg_NOSTOCK[],  //�޿������
    cMsg_DISPSTOCK[],//��ʾ/��ӡ?
#if (defined(CASE_EJSD) || defined(CASE_EJFLASH))//ccr2016-10-25>>>>EJ
    cMsg_RECNUMFR[], //"Rec_FROM"                  //RECNUMFR p
    cMsg_RECNUMTO[], //"Rec_TO"                    //RECNUMTO  p
    cMsg_EJBBIAO[],  //	"~E~J ~R~E~P~O~R~T"		//EJBBIAO $
    cMsg_EJXINXI[],  //	"EJ INFORMATIONS"            //EJXINXI  
    cMsg_EJBHAO[],   //"CODE"						//EJBHAO
    cMsg_SIZEEJ[],   //"Size of EJ"				//SIZEEJ
    cMsg_EJCSHUA[],  //	"EJ INITIALIZED"	   //EJCSHUA O 
    cMsg_EJLEFT[],   //Msg_EJLEFT,
    cMsg_FORMAT[],
    cMsg_EJDATEEND[],// "DATE LAST EJ"
    cMsg_EJRECORDS[],// "LAST EJ#"

#endif//ccr2016-10-25<<<<<<<<
    cMESS_PAYALSO[],
    cDEPTLIST[],
    DEPTTITLE[],
    cPLULIST[],
    cPLUTITLE1[],
    cPLUTITLE2[],
    cMESSPLUPRINTEND[],
    cMESS_TABLEHOLD[],
    cMESSPRNMENU[],
    cPRTStyleN1[],
    cPRTStyleN2[],
    cPRTStyleN3[],
    cPRTStyleN4[],
    cComTestN1[],
    cComTestN2[],
    cComTestN3[],
    cComTestN4[],
    cCurrentTimeN1[],
    cMESSCONFIGERR[],
    cMESSCLEANFILES[],
    cMESSRAMOUT[],
    cMESSDELPLU[],
    cMESSCLEANLOG[],
    cMESSCLEANLOGA[],
    cSpecialSymbol3[],
    cRECALLFLOW[],
    cErrInfoN1[],
    cErrInfoN3[],
    cMessageE18[],
    cEXPORTCSV[],
    cDEPTCAP[],
    cPLUCAP[],
    cTAXCAP[],
    cHEADERCAP[],
    cDISCCAP[],
    cSALPERCAP[],
    cSYSTEMCAP[],
    cCOMMCAP[],
    cGRAPPRNCAP[],
    cGROUPCAP[],
    cICCARDCAP[],
    cPROMCAP[],
    cPBFUNCCAP[],
    cCLERKCAP[],
    cMODICAP[],
    cPBTOTALCAP[],
    cZONECAP[],
    cKEYBOARDCAP[],
    cOFFCAP[],
    cPORACAP[],
    cTRAILERCAP[],
    cSLIPHEADCAP[],
    cICBLOCKCAP[],
    cUSBREPNAME[],
    cSetupCaption38[],
    cSetupCaption39[],
    cReportType0[],
    cReportType1[],
    cReportType2[],
    cReportType3[],
    cReportType7[],
    cReportType8[],
    cReportType13[],
    cReportType17[],
    cReportType18[],
    cCSVREPTITL[],
    cDEPTTITLE[],
#if defined(CASE_FORHANZI)
    cInputMode1[],
    cInputMode2[],
    cInputMode3[],
    cInputMode4[],
#endif
    cBUTTONBATLOW[],
    cCHARGEBATNOW[],
    cREPRN_PWON[],
    cComTestN3ERR[],
    cComTestN3OK[],
    cSRAMNOTFOUND[],
    cCLERKPASS[],
    cMESSSETMENU[],
    cCLEARGRANDTOTAL[],
    cMsgNET[],
    cCLOSEPRINTER[],
    cCLEANALLECRVIP[],
    cECRVIPTITLE[],//ECRVIPTITLE;//"��Ա��      ���ѽ��     �Ƶ�";
    cCREATEDATE[],//CREATEDATE;//��������:
    cVIPLOGOUT[],//VIPLOGOUT ��Ա�˳�
    cVIPTOTAL[],//VIPTOTAL �ܶ�
    cVIPTOTALA[],//VIPTOTALA �����ܶ�
    cDECVIPPOINT[],//�ҽ�
    cADDVIPPOINT[],//�ͷ�
    cINPUTVIPNAME[],//�����Ա����:
#if defined(CASE_PERU)
    cMsgCUSTOMER[],//     "CUSTOMER"
#endif
    cPRINTKEYBOARD[];//��ӡ���̲���
#endif
