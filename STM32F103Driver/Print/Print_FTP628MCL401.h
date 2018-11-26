/****************************************Copyright (c)**************************************************
*        EUTRON Human Information Equipment Co.,Ltd.
*                    www.eutron.com.cn
* File name:		Print_ltp1245.c
* Descriptions:     ltp1245��ӡ����������
*------------------------------------------------------------------------------------------------------
*  Created by:			chen churong
* Created date:        2011-10-01
* Version: 1.0
********************************************************************************************************/

#include "print.h"


void   Prn_task11_ResetCutter(void);
void   Prn_task13_FeedStepCA(void); //HJ
void   Prn_task16_CutPaper(void);

extern WORD PrnTemperature(void);

BYTE emuState=0;//testonly
/****************************************************************
  Name: TESTKEYS  ��ⰴ��״̬;
 return: true-��������; false-����û�а���
*****************************************************************/
BYTE TESTKEYS(void)
{
    ULONG t1,t2;
#if 0
    do {
        t1 = (LPC_GPIO0->FIOPIN & KEY1);?????
        t2 = t1;
        t2 = (LPC_GPIO0->FIOPIN & KEY1);?????
    } while (t1!=t2);
#endif
   	if (t1)
        return false;
   	else
        return true;

}

#if ENCUTTER
/****************************************************************
  Name: TESTCUTS  ����е�HOME״̬;
 return:
 	true-�е���homeλ��;
 	false-�е�����HOMEλ��
*****************************************************************/
BYTE TESTCUTS(void)
{
    ULONG t1,t2;

    do {
        t1 = (*(uint8_t *)PRT_PH_READ_ADDR & CUTS);//?????
        t2 = t1;
        t2 = (*(uint8_t *)PRT_PH_READ_ADDR & CUTS);//?????
    } while (t1!=t2);

   	if (t1)
        return true;
   	else
        return false;

}
#endif


// move motor by step 1
void Move_Motor()
{
	Drive_Motor(TAB_PHASEJ[Prn_Jphase]);//out
	Prn_Jphase++;
	Prn_Jphase &= (PHASEMAX-1);

}
#if ENCUTTER
// move cutter motor forword by step 1
void Move_CutMotorF()
{
	Drive_CutMotor(TAB_PHASECUT[Prn_Jphase]);//out
	Prn_Jphase++;
	Prn_Jphase &= (CPHASEMAX-1);
}

// move cutter motor reverse by step 1
void Move_CutMotorR()
{
	Drive_CutMotor(TAB_PHASECUT[Prn_Jphase]);//out
	Prn_Jphase--;
	Prn_Jphase &= (CPHASEMAX-1);

}
#endif
/****************************************************************
  Name: Prn_CalcHotTime  �������ʱ��
 return: Prn_HotTime-����ʱ��
*****************************************************************/
#define PRNMAX  4096

void Prn_CalcHotTime()
{
	WORD DST_time,VTempValue;

    VTempValue = PrnTemperature();
    VTempValue /= 128;//change it into 0~32


#if 1
    if (VTempValue<6)//Too hot of the printer
#else//testonly
    if (VTempValue<16)//Too hot of the printer
#endif
    {
//testonly        Prn_Status.g_bTOOHOT = 1;
    }
	//HJ ͬCAPD245���ٶ�-���ȿ���
    if      (Prn_MotorTime<315*uSECOND) DST_time=14;    //3200 PPS
    else if (Prn_MotorTime<335*uSECOND) DST_time=13;    //3000 PPS
    else if (Prn_MotorTime<359*uSECOND) DST_time=12;    //2800 PPS
    else if (Prn_MotorTime<389*uSECOND) DST_time=11;    //2600 PPS
    else if (Prn_MotorTime<417*uSECOND) DST_time=10;    //2400 PPS
    else if (Prn_MotorTime<459*uSECOND) DST_time=9;     //2200 PPS
    else if (Prn_MotorTime<508*uSECOND) DST_time=8;     //2000 PPS
    else if (Prn_MotorTime<563*uSECOND) DST_time=7;     //1800 PPS
    else if (Prn_MotorTime<641*uSECOND) DST_time=6;     //16000 PPS
    else if (Prn_MotorTime<733*uSECOND) DST_time=5;     //1400 PPS
    else if (Prn_MotorTime<836*uSECOND) DST_time=4;     //1200 PPS
    else if (Prn_MotorTime<1074*uSECOND) DST_time=3;     //1000 PPS
    else if (Prn_MotorTime<1302*uSECOND) DST_time=2;     //800 PPS
    else if (Prn_MotorTime<1769*uSECOND) DST_time=1;     //600 PPS
    else  DST_time = 0;        //400 PPS

    Prn_HotTime = TABSTROBE24V[VTempValue][DST_time];

#if DCPOWER==0
    //Prn_HotTime+=Prn_HotTime/2;//for Battery
#endif

#if GROUPMODE==2
    VTempValue = Prn_HotTime * Prn_HotMAX * 2;//ÿ���������
#else
    VTempValue = Prn_HotTime;
#endif

#if (defined(CASE_FORHANZI))
	if(VTempValue+Prn_HZTime >= Prn_MotorTime * STEPS1LINE)//������,����һ��
    {//�������ʱ����ڲ������ʱ��,��������ʱ��
        Prn_MotorTime = (VTempValue+Prn_HZTime)/2 + 5 * uSECOND ;
#else
    if((VTempValue+PDATATIME+ASCTIMES*PRNWIDTH) >= Prn_MotorTime * STEPS1LINE)//������,����һ��
    {//�������ʱ����ڲ������ʱ��,��������ʱ��
            Prn_MotorTime = (VTempValue+PDATATIME+ASCTIMES*PRNWIDTH)/2 ;//+ 5 * uSECOND ;
#endif

        Prn_Status.g_bHotOver = 1;
        if (Prn_AccStep>=VMAXSPEED)
            Prn_AccStep = VMAXSPEED-1;
        while (Prn_AccStep)
        {
            if (Prn_MotorTime< TAB_PRTIME[Prn_AccStep])
                break;
            Prn_AccStep --;
        }
    }
    else
        Prn_Status.g_bHotOver = 0;

}
/************************************************************************************
  Tasks for print
************************************************************************************/
//Stop motor===========================================
void Prn_task00_Stop()
{
    Drive_Off();//    stop print motor
	Set_Motor_Speed( TIMESTART );
    PrnPowerOFF();

	StopTimer(TIM2);  //HJ ֹͣ��ӡ����ѭ����ʱ��
	Prn_TaskNow = 0xff;

    Prn_Jphase = 0;
    Prn_AccStep = 0;
}
//===========================================
void Prn_task01_Start()
{
	int i;
    BYTE *linep;

    GetTaskFromPool();
    if(Prn_Status.g_bPrintOver)//�������ݴ�ӡ���
    {
        Stop_Motor();//�ر�motor
    }
#if ENCUTTER
    else if (BIT(ApplVar.Prn_Command, PRN_CUTF_Mode | PRN_CUTH_Mode))
    {//cut paper
        Prn_task16_CutPaper();
    }
    else if (BIT(ApplVar.Prn_Command,PRN_CUTRESET_Mode))
    {//reset cutter
        Prn_task11_ResetCutter();
    }
    else
#endif
    {//print function
#if ENCUTTER
        CutDrive_Off();//by ouhs Drive_CutMotor(CPHSTOP);//stop cut motor
#endif
        Move_Motor();
        Set_Motor_Speed( Prn_MotorTime );

    	if(Prn_Status.g_bPrintGraph)//print a graphic without text
    	{
    		Prn_TaskNow = TASK05_FeedHalf;
            Prn_TaskNext = TASK03_PrintGraphic;
    	}
        else   if (Prn_LineChars)
        {
            Create384Dots();
            linep = DotsOfCurrent;

            //��ʼ�͵���֮ǰ,���б�Ҫ�ĳ�ʼ��
            Prn_LineDots = 0;
#if GROUPMODE==2
            memset(Prn_GroupDots,0,sizeof(Prn_GroupDots));
#endif

#if WORDorBYTE
            for(i=0;i<DOTSBUFF;i+=2)
            {
                Set_Hot_DataW( ((WORD)linep[0]<<8) + linep[1], i );
                linep+=2;
            }
#else
            for(i=0;i<DOTSBUFF;i++)
            {
                Set_Hot_Data( *linep++ , i );
            }
#endif
#if GROUPMODE==2
            //�������һ���ֽ�ʱ,�趨��������������
            Set_Hot_Group();
#endif
            Prn_LineIndex=1;

            Start_Hot();

            Prn_TaskNow = TASK05_FeedHalf;
            Prn_TaskNext = TASK02_PrintChar;

        }
        else
        {
            Prn_TaskNow = TASK04_FeedPaper;
            Prn_BlankAppend = (LINE_BLANK + TEXT_HIGH) * STEPS1LINE;
        }
    }
}
//print text============================================
void Prn_task02_PrintChar()
{
	int i;
    BYTE *linep;

	Move_Motor();
    Set_Motor_Speed( Prn_MotorTime );

	if(Prn_LineIndex<TEXT_HIGH)
	{
		Prn_TaskNow = TASK05_FeedHalf;
        Prn_TaskNext = TASK02_PrintChar;

        if (BIT(ApplVar.Prn_Command,PRN_DBLH_Mode))
		{ //double high
			if(Prn_Status.g_bDoublHight)
			{//��ͬһ�н����ٴμ���
				Prn_Status.g_bDoublHight = false;
                //20130709>>>>>>>>>
#if GROUPMODE==2
            //�������һ���ֽ�ʱ,�趨��������������
                Set_Hot_Group();
#endif
                Start_Hot();//<<<<<<<<<<
				return;//print current dots twice
			}
            else
                Prn_Status.g_bDoublHight = true;
		}
        if (Prn_LineChars)
        {
            Create384Dots();
            linep = DotsOfCurrent;

            //��ʼ�͵���֮ǰ,���б�Ҫ�ĳ�ʼ��
            Prn_LineDots = 0;
#if GROUPMODE==2
            memset(Prn_GroupDots,0,sizeof(Prn_GroupDots));
#endif
#if WORDorBYTE
            for(i=0;i<DOTSBUFF;i+=2)
            {
                Set_Hot_DataW( ((WORD)linep[0]<<8) + linep[1], i );
                linep+=2;
            }
#else
            for(i=0;i<DOTSBUFF;i++)
            {
                Set_Hot_Data( *linep++ , i );
            }
#endif

#if GROUPMODE==2
            //�������һ���ֽ�ʱ,�趨��������������
            Set_Hot_Group();
#endif

            Start_Hot();
        }
		Prn_LineIndex++;
	}
	else
	{
#if defined(CASE_FORHANZI)
        Prn_HZTime = 0;
        if (Prn_AccCopy)
        {
            Prn_AccStep = Prn_AccCopy;
            Prn_AccCopy = 0;
        }
#endif
		Prn_LineIndex = 0;// ����ʡ��
		Prn_TaskNow = TASK04_FeedPaper;
		Prn_BlankAppend = LINE_BLANK*STEPS1LINE;
		ApplVar.PoolPopOut = Prn_PoolCurrent;
	}
}
// Print graphic====================================
void Prn_task03_PrintGraphic()
{
	Move_Motor();
    Set_Motor_Speed( Prn_MotorTime );

	if(!Prn_Status.g_bGraphicOver)
	{
		if(Prn_GraphTextMax)
			CreatGraphicWithText();
		else
			CreateGraphicDots();
		Prn_TaskNow = TASK05_FeedHalf;
        Prn_TaskNext = TASK03_PrintGraphic;
	}
	else
	{
#if defined(CASE_FORHANZI)
        Prn_HZTime = 0;
        if (Prn_AccCopy)
        {
            Prn_AccStep = Prn_AccCopy;
            Prn_AccCopy = 0;
        }
#endif
		Prn_Status.g_bPrintGraph = false;
		Prn_TaskNow = TASK04_FeedPaper;
		Prn_BlankAppend = LINE_BLANK*STEPS1LINE;
		ApplVar.PoolPopOut = Prn_PoolCurrent;
	}
}
//feed paper=======================================
void Prn_task04_FeedPaper()
{
	int i;
    BYTE *linep;

    PrnHotOFF();//!!!!@@@@@@@@@!!!!!!
    Move_Motor();

	if(Prn_BlankAppend)
    {
        Set_Motor_Speed( Prn_MotorTime );
		Prn_BlankAppend--;
    }
	else
	{
        ApplVar.PoolPopOut = Prn_PoolCurrent;

        GetTaskFromPool();

		if(Prn_Status.g_bPrintOver)//�������ݴ�ӡ���
		{
			Stop_Motor();//�ر�motor
		}
#if ENCUTTER
        else  if (BIT(ApplVar.Prn_Command, PRN_CUTF_Mode | PRN_CUTH_Mode | PRN_CUTRESET_Mode))
        {//cut paper
            Prn_TaskNow = 0xff;
            Start_Motor(ApplVar.Prn_Command);
        }
#endif
        else
		{
            Set_Motor_Speed( Prn_MotorTime );
			if(Prn_Status.g_bPrintGraph)//��ӡͼƬ
			{
				Prn_TaskNow = TASK05_FeedHalf;
                Prn_TaskNext = TASK03_PrintGraphic;
			}
            else if (Prn_LineChars)
            {
                Create384Dots();
                linep = DotsOfCurrent;
                //��ʼ�͵���֮ǰ,���б�Ҫ�ĳ�ʼ��
                Prn_LineDots = 0;
#if GROUPMODE==2
                memset(Prn_GroupDots,0,sizeof(Prn_GroupDots));
#endif
#if WORDorBYTE
                for(i=0;i<DOTSBUFF;i+=2)
                {
                    Set_Hot_DataW( ((WORD)linep[0]<<8) + linep[1], i );
                    linep+=2;
                }
#else
                for(i=0;i<DOTSBUFF;i++)
                {
                    Set_Hot_Data( *linep++ , i );
                }
#endif

#if GROUPMODE==2
            //�������һ���ֽ�ʱ,�趨��������������
                Set_Hot_Group();
#endif
                Start_Hot();

    			Prn_LineIndex=1;
    			Prn_TaskNow = TASK05_FeedHalf;
                Prn_TaskNext = TASK02_PrintChar;
            }
            else
            {
                Prn_BlankAppend = (LINE_BLANK + TEXT_HIGH) * STEPS1LINE;
                ApplVar.PoolPopOut = Prn_PoolCurrent;
            }
		}
	}

}
//Drive motor half step=============================
#if (STEPS1LINE>2)
BYTE StepS=1;
#endif

void Prn_task05_FeedHalf()
{

	Move_Motor();
	Set_Motor_Speed( Prn_MotorTime );
    Prn_Status.g_bHotOver = 0;


#if (STEPS1LINE>2)
    StepS++;

#if GROUPMODE==2
/* ���ȼ�ʱ�������жϷ���ʱ���˴�����ȡ��
    if (StepS==STEPS1LINE/2 && Prn_LineDots)
    {
        Prn_HotIndex=0;
        Set_HotPIN();//����ϲ�����
        START_HOT_TIMER();
    }
    */
#endif
	//HJ ��3��ʱ���ٴ���������
    if (StepS == 3 && Prn_Status.g_bHotLatch )
    {
    	Prn_HotIndex=0;
        Set_HotPIN(); //����ϲ�����
        Set_HotTime(Prn_HotTime);
    }

    if(StepS<STEPS1LINE)
        return;
    StepS = 1;
	Prn_Status.g_bHotLatch = 0; 	//HJ ��4��ʱ����ǵڶ��μ��Ƚ���

#elif GROUPMODE==2
/* ���ȼ�ʱ�������жϷ���ʱ���˴�����ȡ��
    if (Prn_LineDots)
    {
        Prn_HotIndex=0;
        Set_HotPIN();//����ϲ�����
        START_HOT_TIMER();
    }
*/
#endif
    Prn_TaskNow = Prn_TaskNext;
}

//tasks for cutter>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#if ENCUTTER

//reset cutter===========================================
//HJ �������� TASK01_Start ��ֱ�ӵ��á�
void   Prn_task11_ResetCutter()
{
//	check_print = TESTCUTS();

	//HJ ֹͣ��ֽ���
    Drive_Off();// stop print motor

	//HJ ִ�еڶ�����ֽ�������

    Cut_Status.g_bCutOK = 0;
    Prn_FeedCount = 0;

    //HJ �е���HOMEλ��
    if( TESTCUTS() )
    {
        Move_CutMotorF();	//HJ ���򻻲�
        Set_Motor_Speed( Prn_MotorTime );  //HJ ���õ�� �´λ���ʱ����
        Prn_TaskNow = TASK13_FeedStepCA;
		//xputc('1');

        Cut_Status.g_bReverse = 0;

        {
            CutMotorMax = CUTSTEPA;
        }

        Cut_Status.g_bFirst = 0;
    }
    //HJ �е�����HOMEλ��
    else
    {
        Move_CutMotorR(); //HJ ����
        Set_Motor_Speed( Prn_MotorTime );  //HJ ���õ������ ����ʱ��
        Prn_TaskNow = TASK13_FeedStepCA;
		//xputc('2');

        Cut_Status.g_bReverse = 1;

        {
            CutMotorMax = CUTSTEPC_F;
        }
        Cut_Status.g_bFirst = 0;

    }
}


// tasks for cut paper>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//HJ �������� TASK01_Start ��ֱ�ӵ��á�
void   Prn_task16_CutPaper()
{
	//HJ ֹͣ��ֽ���
    Drive_Off();// stop print motor
	//xputc('C');

	//HJ ִ�еڶ�����ֽ�������

    Prn_FeedCount = 0;
    Prn_TaskNow = TASK13_FeedStepCA;   //Drive cutter motor half step
    Cut_Status.g_bReverse = 0;


    {
        CutMotorMax = CUTSTEPA;
    }

    Cut_Status.g_bFirst = 0;
    Prn_task13_FeedStepCA();//feed by stepA
}
/*
//feed cutter motor half phase===================================
//HJ ��(��)�򻻲� �л�����һ������
void   Prn_task12_FeedCutter()
{
    //HJ ����
    if( Cut_Status.g_bReverse )
    {
        Move_CutMotorR();
    }
    else
    {
        Move_CutMotorF();
    }
    //HJ �����´λ���ʱ��
    Set_Motor_Speed( Prn_MotorTime );  //HJ ���õ������ ����ʱ��


    Prn_TaskNow = Prn_TaskNext;

}
*/
//HJ ����============================================
void Prn_task17_FeedStepB()
{

	//HJ ��������
    Move_CutMotorF();
    Set_Motor_Speed( Prn_MotorTime );  //HJ ���õ������ ����ʱ��
	//xputc('5');


	//HJ ������������
    if( Prn_FeedCount > CutMotorMax )
    {
    	//HJ ׼����ͣ�е�
        Set_Motor_Speed( TIMESTOP );
        Prn_TaskNow = TASK10_StopCutter;//stop cut motor
        Cut_Status.g_bStop = 0; //HJ ��ͣ
        Cut_Status.g_bStepC1st = 1;
        Prn_TaskNext = TASK18_FeedStepC;
    }
}
//HJ �˵�(��ֽ)======================================================
void Prn_task18_FeedStepC()
{
//	check_print = TESTCUTS();

	//HJ �����˵�(��ֽ)
    Move_CutMotorR();
    Set_Motor_Speed( Prn_MotorTime );  //HJ ���õ������ ����ʱ��
	//xputc('7');


    if( TESTCUTS() ) 							//HJ ���Ѿ���
    {
		//HJ ���������˵�(��ֽ)��׼���л����ص�(ѹ��)
        if( Prn_FeedCount < CUTSTEPC_F )
        {
            Set_Motor_Speed( Prn_MotorTime );  //HJ ���õ������ ����ʱ��
            Prn_TaskNow = TASK14_FeedStepE;
            Prn_FeedCount = 0;
        }
        //HJ �쳣��ֹͣ
        else
        {
            //error found
            Set_Motor_Speed( TIMESTOP );
            Cut_Status.g_bStop = 1; //HJ ֹͣ,����ͣ
            Cut_Status.g_bCutOK = 0;
            Prn_TaskNow = TASK10_StopCutter;//stop cut motor
			//xputc('e');
        }
    }
    else 										//HJ ��δ��
    {
        //�쳣��δ��
        if( Prn_FeedCount > CutMotorMax )
        {
            //HJ ��ֽ��� ��ֽ
            if( Cut_Status.g_bStepC1st )
            {
                //backward the motor by 8 dots line.
                Cut_Status.g_bStepC1st = 0;
                Drive_CutMotor( CPHSTOP );  //stop cutmotor
                Drive_Motor( PHSTART );  //out
                Set_Motor_Speed( TIMESTART );
                Prn_Jphase = 0;
                Prn_AccStep = 0;
                Prn_TaskNow = TASK19_RevFeed8Line;
				//xputc('F');
            }
            //HJ ֹͣ
            else
            {
                //error found
                Set_Motor_Speed( TIMESTOP );
                Cut_Status.g_bStop = 1; //HJ ֹͣ,����ͣ
                Cut_Status.g_bCutOK = 0;
                Prn_TaskNow = TASK10_StopCutter;//stop cut motor
				//xputc('E');
            }
        }
    }
}
//Move cutter by STEPC===========================================
//HJ �˵�(����λ)������A	//
void   Prn_task13_FeedStepCA()
{
//	check_print = TESTCUTS();

    //HJ �˵�C(����λ)
    if( Cut_Status.g_bReverse )
    {
		//HJ �����˵�C(����λ)
        Move_CutMotorR();
		Set_Motor_Speed( Prn_MotorTime );  //HJ ���õ������ ����ʱ��
		//xputc('4');

		//���������˵�C(����λ)
        if( TESTCUTS() ) //HJ �Ѿ��˵�ԭ��
        {
			//xputc('c');
            Set_Motor_Speed( Prn_MotorTime );  //HJ ���õ������ ����ʱ��
            Prn_TaskNow = TASK14_FeedStepE;//drive cut motor STEPSE
            Prn_FeedCount = 0;
        }
        //HJ �쳣��ֹͣ
        else
        {
            if( Prn_FeedCount > CutMotorMax )
            {
                Set_Motor_Speed( TIMESTOP );
                Cut_Status.g_bStop = 1;  //HJ ֹͣ,����ͣ
                Prn_TaskNow = TASK10_StopCutter;//stop cut motor
				//xputc('e');
            }
        }
    }
    //HJ ����A
    else
    {
		//HJ ��������
        Move_CutMotorF();
		Set_Motor_Speed( Prn_MotorTime );
		//xputc('3');

        //HJ ������������
        if( !TESTCUTS() ) //HJ �Ѿ��뿪ԭ��
        {
			//xputc('c');

            //HJ ��ͣ(��λ����)
            if( BIT( ApplVar.Prn_Command, PRN_CUTRESET_Mode ) )
            {
                Set_Motor_Speed( TIMESTOP );  //stop motor first
                Cut_Status.g_bStop = 0; //HJ ��ͣ
                Prn_TaskNow = TASK10_StopCutter;//stop cut motor first
            }
            //HJ ׼���л�������(��ֽ����)
            else
            {
                if( BIT( ApplVar.Prn_Command, PRN_CUTF_Mode ) )
                {
                    CutMotorMax = CUTSTEPB_F;
                }
                else
                {
                    CutMotorMax = CUTSTEPB_H;
                }

                Prn_FeedCount = 0;
                Prn_TaskNow = TASK17_FeedStepB;//feed cutter by STEPB
            }
        }
        //HJ ��δ��
        else
        {
            //HJ �쳣��ֹͣ
            if( Prn_FeedCount > CutMotorMax )
            {
                Set_Motor_Speed( TIMESTOP );
                Cut_Status.g_bStop = 1; //HJ ֹͣ,����ͣ
                Prn_TaskNow = TASK10_StopCutter;//stop cut motor

				//xputc('e');
            }
        }
    }

//    //xputc('_');
}


//HJ �ص�(ѹ��)===========================================
void   Prn_task14_FeedStepE()
{
	//HJ �����ص�(ѹ��)
    Move_CutMotorR();
    Set_Motor_Speed( Prn_MotorTime );  //HJ ���õ������ ����ʱ��
	//xputc('8');

	//HJ ���������ص�(ѹ��)
    if( Prn_FeedCount > CUTSTEPE )
    {
        Set_Motor_Speed( TIMESTOP );
        Prn_TaskNow = TASK10_StopCutter;//stop cut motor
        Cut_Status.g_bCutOK = 1;
        Cut_Status.g_bStop = 1; //HJ ֹͣ,����ͣ
    }

}

//HJ �ص�(����λ)===========================================
void   Prn_task15_FeedStepAlpha()
{
//	check_print = TESTCUTS();

	//HJ �����ص�(����λ)
    Move_CutMotorR();
	Set_Motor_Speed( Prn_MotorTime );  //HJ ���õ������ ����ʱ��
	//xputc('6');

	//HJ ���������ص�(����λ)
    if( TESTCUTS() )
    {
		Set_Motor_Speed( Prn_MotorTime );  //HJ ���õ������ ����ʱ��
		Prn_TaskNow = TASK14_FeedStepE;//drive cut motor STEPSE
		Prn_FeedCount = 0;
    }
    else
    {
    	//HJ �쳣��ֹͣ
        if( Prn_FeedCount> CutMotorMax )
        {
            Set_Motor_Speed( TIMESTOP );
            Cut_Status.g_bStop = 1; //HJ ֹͣ,����ͣ
            Prn_TaskNow = TASK10_StopCutter;//stop cut motor
			//xputc('e');
        }
    }
}

//HJ ��ͣ��ֹͣ===========================================
void   Prn_task10_StopCutter()
{

    Drive_CutMotor( CPHSTOP );  //out

    //HJ ֹͣ�е���������ֽ����
    if( Cut_Status.g_bStop )
    {
        //stop cut motor
        ApplVar.PoolPopOut = Prn_PoolCurrent;// ��ǰ��ֽ���������
		//xputc('9');


        //HJ ȷ��û���µĴ�ӡ���񣬷����ٴ�������ӡ����
        if( ApplVar.PoolPushIn != ApplVar.PoolPopOut )
        {
            //A new task wait for service
            Prn_PoolCurrent = ( ApplVar.PoolPopOut + 1 );
            if( Prn_PoolCurrent >= MAX_PRNPOOL )
            {
                Prn_PoolCurrent = 0;
            }

            Prn_TaskNow = 0xff;
            Start_Motor( ApplVar.PoolForPrint[Prn_PoolCurrent].Prn_Command );
        }
        //HJ û���µĴ�ӡ���񣬹ر���ֽ���
        else
        {
            CutDrive_Off();
			PrnPowerOFF();

			StopTimer(TIM2);
            Prn_TaskNow = 0xff;
        }
    }

    //HJ ��ͣ�е�(��λ)
    else if( BIT( ApplVar.Prn_Command, PRN_CUTRESET_Mode ) )
    {
        Set_Motor_Speed( TIMESTART );
        Cut_Status.g_bReverse = 1;
        Prn_TaskNow = TASK15_FeedStepAlpha;
        Prn_TaskNext = TASK15_FeedStepAlpha;
        CutMotorMax = CUTSTEPALPHA;

		//xputc('0');
    }
    //HJ ��ͣ�е�(��ֽ)
    else //if (BIT(ApplVar.Prn_Command,PRN_CUTF_Mode | PRN_CUTH_Mode))
    {
        Set_Motor_Speed( TIMESTART );
        Cut_Status.g_bReverse = 1;
        Prn_TaskNow = TASK18_FeedStepC;
        Prn_TaskNext = TASK18_FeedStepC;

        if( BIT( ApplVar.Prn_Command, PRN_CUTF_Mode ) )
        {
            CutMotorMax = CUTSTEPC_F;
        }
        else
        {
            CutMotorMax = CUTSTEPC_H;
        }


        Cut_Status.g_bFirst = 0;

		//xputc('0');
	}


    Prn_FeedCount = 0;

    Prn_Jphase = 0;
    Prn_AccStep = 0;

}

//backward the motor by 8 dots line.===================
void Prn_task19_RevFeed8Line()
{
	//HJ �����ؾ�ֽ
    Prn_Jphase--;
    Prn_Jphase &= (PHASEMAX-1);
//    Drive_Motor(TAB_PHASEJ[Prn_Jphase]);//out
    Set_Motor_Speed( Prn_MotorTime ); //  HJ ���õ������ ����ʱ��//

	//HJ ���������ؾ�ֽ
 //   if (Prn_AccStep>8*STEPS1LINE)
    {
    	//HJ ֹͣ��ֽ���
        Drive_Off();

        //HJ ����������ֽ���
        Drive_CutMotor(CPHSTART);//out
        Set_Motor_Speed( TIMESTART );
        Prn_Jphase = 0;
        Prn_AccStep = 0;
        Prn_TaskNow = TASK18_FeedStepC;
        Prn_FeedCount=0;
    }

}

#endif
/************************************************************
����⵽��ӡ����ֽʱ,���õȴ�װֽ��־Prn_Status.g_bWaitPaper
�رմ�ӡ��,���Ƕ�ʱ������ӡ�����������,�Ա����Ƿ�װֽ
*************************************************************/
void Wait_Paper()
{
    PrnHotOFF();
    Drive_Off();//     stop print motor
    Set_Motor_Speed( TIMESTART );
    PrnPowerOFF();
    Prn_TaskNow = 0xff;

    Prn_Jphase = 0;
    Prn_AccStep = 0;

    Prn_LineIndex = 0;
	Prn_BlankAppend = LINE_BLANK*STEPS1LINE;
	Prn_Status.g_bPrintGraph = false;
    Prn_Status.g_bWaitPaper = true;//���õȴ�װֽ��־

}
/*================================ main for print===============================*/
/***************************��ӡ������ȷ�����********************************
 TIM2_IRQHandler�ڴ�ӡ���������������ֽ
1. ����Wait_Paper,�Զ��رմ�ӡ���ĵ�Դ, ��PHSTART���ڵ���TIM2_IRQHandler
2. �����¼�⵽��ֽ��,��������4,����һ�οհ׺�,�ټ�����ӡ
********************************************************************************/

void TIM2_IRQHandler(void)
{
  /* Clear TIM2 update interrupt */
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  StopTimer(TIM2);


#if ENCUTTER
    // ��ֽ����ģʽ��,�������ֽ��״̬
    if (!BIT(ApplVar.Prn_Command,PRN_CUTRESET_Mode | PRN_CUTF_Mode | PRN_CUTH_Mode))
#endif
    {
        Check_Print();
        if(Prn_Status.g_bTOOHOT)
        {//
            if(!Prn_Status.g_bSuspend)
            {//��ӡ������,��ͣ��ӡ
                Suspend_Motor();
            }
            else if (Prn_Delay==0)
            {//��ӡ����ͣ����
                Restart_Motor();
            }
            return;//��ӡ������
        }
#if CASE_HANDUP
        if(Prn_Status.g_bHANDUP)
        {
            if (!Prn_Status.g_bWaitPaper)
                Wait_Paper();
            else
                Set_Motor_Speed( TIMESTART );
            return; //��ӡ��ѹ��̧��
        }
        else
        {
            if (Prn_Status.g_bHANDDN)
            {//ѹ��̧���,����ѹ��ѹ��,�����𶯴�ӡ
                Prn_Status.g_bHANDDN = false;
                Prn_Status.g_bPaperIn = false;
                Prn_Status.g_bNOPAPER = false;
                Prn_Status.g_bWaitPaper = false;
                Prn_TaskNow = 0xff;
                Start_Motor(ApplVar.Prn_Command);
                return; //��ӡ�����������,��Ҫ����������ӡ
            }
        }
#endif
        //����Ƿ���ֽ
        if(Prn_Status.g_bNOPAPER)
        {//��ֽ
            if (!Prn_Status.g_bWaitPaper)//Ϊ��һ�μ�⵽��ֽ,�رմ�ӡ��
                Wait_Paper();
            else
                Set_Motor_Speed( TIMESTART );
            return; //û��װֽ
        }
        else
        {//��ֽ
            if (Prn_Status.g_bPaperIn)
            {//Ϊȱֽ������˴�ӡֽ,�����𶯴�ӡ
                Prn_FeedCount = Prn_Delay = 0;
                Prn_Status.g_bPaperIn = false;
                Prn_Status.g_bHANDDN = false;
                Prn_Status.g_bHANDUP = false;
                Prn_Status.g_bWaitPaper = false;
#if 1
                if ((ApplVar.ErrorNumber&0x7f)>=ERROR_ID(CWXXI39) && (ApplVar.ErrorNumber&0x7f)<=ERROR_ID(CWXXI41))
                    ApplVar.ErrorNumber = 0;//������CheckPrinter���ظ�ִ��Start_When_Ready(" ")

                Start_When_Ready(" ");
				//ֱ��������ӡ
//                Prn_TaskNow = 0xff;
//                Start_Motor(ApplVar.Prn_Command);
                return;
#else
				//����4������,����ֽ(�ᵼ���쳣)

                Prn_PoolCurrent = ApplVar.PoolPopOut;
                Prn_TaskNow = TASK04_FeedPaper;
                Prn_BlankAppend = (LINE_BLANK + TEXT_HIGH) * STEPS1LINE * 10;//��ʮ�пհ�
                PrnPowerON();
                Drive_Motor(PHSTART);//out
                Set_Motor_Speed( TIMESTART );
                Prn_Jphase = 0;
                Prn_AccStep = 0;
                //LPC_RIT->RICTRL |= RIT_CTRL_TEN;//Enable counter
                return;
#endif
            }
        }
    }


    //��ӡ�����쳣
    if(!Prn_Status.g_bPrintOver)//It's have data for print
    {

#if ENCUTTER
        if (BIT(ApplVar.Prn_Command,PRN_CUTRESET_Mode | PRN_CUTF_Mode | PRN_CUTH_Mode) && Prn_TaskNow!=TASK19_RevFeed8Line)
        {
            if(Prn_AccStep<CUTMAXSPEED)
                Prn_MotorTime = TAB_CUTTIME[Prn_AccStep];
        }
        else
#endif
        {
            if(Prn_AccStep<VMAXSPEED
               && !Prn_Status.g_bHotOver)//����ʱ�䲻��������ʱ��,(������ʱ�䳬���˲���ʱ��ʱ,�Ұ벽�Ĳ���ʱ�䲻��)
                Prn_MotorTime = TAB_PRTIME[Prn_AccStep];
            Prn_Status.g_bHotOver = 0;
        }
    }
    Prn_AccStep++;

    switch(Prn_TaskNow)
    {
        case TASK00_Stop:
            Prn_task00_Stop();
            break;
        case TASK01_Start:
            Prn_task01_Start();
            break;
        case TASK02_PrintChar:
            Prn_task02_PrintChar();
            break;
        case TASK03_PrintGraphic:
            Prn_task03_PrintGraphic();
            break;
        case TASK04_FeedPaper:
            Prn_task04_FeedPaper();
            break;
        case TASK05_FeedHalf:
            Prn_task05_FeedHalf();
            break;

        case 6://reserved
        case 7://reserved
        case 8://reserved
        case 9://reserved
            break;
#if ENCUTTER
                    //reset cutter
        case TASK10_StopCutter:
            Prn_task10_StopCutter();
            break;
        case TASK11_ResetCutter:
            Prn_task11_ResetCutter();
            break;
        case TASK12_FeedCutter:
            //Prn_task12_FeedCutter();
            break;
        case TASK13_FeedStepCA:
            Prn_task13_FeedStepCA();
            break;
        case TASK14_FeedStepE:
            Prn_task14_FeedStepE();
            break;
        case TASK15_FeedStepAlpha:
            Prn_task15_FeedStepAlpha();
            break;
                    //cut paper
        case TASK16_CutPaper:
            Prn_task16_CutPaper();
            break;
        case TASK17_FeedStepB:
            Prn_task17_FeedStepB();
            break;
        case TASK18_FeedStepC:
            Prn_task18_FeedStepC();
            break;
        case TASK19_RevFeed8Line:
            Prn_task19_RevFeed8Line();
            break;
#endif
        default:
            break;
    }
    return;
}

#if EN_PRINT
/*********************************************************************************************************
* Function Name:        TIMER3_IRQHandler
* Description:          TIMER3 �жϴ�����,���ڼ��ȿ���
* ��������ȴ�����������ʱ�������жϷ�����������Ʒ������
*********************************************************************************************************/
void TIM3_IRQHandler (void)
{
    /* Clear TIM2 update interrupt */
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    StopTimer(TIM3);

   PrnHotOFF();
   Prn_HotIndex++;
   if (Prn_HotIndex>=Prn_HotMAX)
       return;
   Prn_HotIndex %= Prn_HotMAX;

#if GROUPS>1

#if GROUPMODE==0
//�˴�ֻ�����˷� 6��������
   switch (Prn_HotIndex)
   {
       case 0:return;//���Ƚ���
       case 1:Hot_On(HOT2_PIN);  break;
       case 2:Hot_On(HOT3_PIN);  break;
       case 3:Hot_On(HOT4_PIN);  break;
       case 5:Hot_On(HOT5_PIN);  break;
       case 6:Hot_On(HOT6_PIN);  break;
   }
   StartTimer(TIM3);    // ������ʱ��

#else
	//HJ �Ĳ�һ����ʱ���������ļ��ȿ���
   if (Prn_Status.g_bHotLatch && Prn_HotIndex && Prn_GroupHot[Prn_HotIndex])
   {
       //if (Prn_HotIndex!=GROUPS*2-1)//!!!!@@@@@@@@@!!!!!!
       {
           Set_HotPIN();
           Set_HotTime(Prn_HotTime+10*uSECOND);//���LTPZ245��ӡ��:�����������£����Ӽ���ʱ�䣬�Բ����ڶ������ʱ�ĵ�ѹ����
//           START_HOT_TIMER();/* ������ʱ��      */
       }
   }
#endif
#endif

}

#endif

