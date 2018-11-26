/****************************************Copyright (c)**************************************************
**                               Hunan EUTRON information device Co.,LTD.
**
**                                 http://www.eutron.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:       KeyBoardDrv.c
** Descriptions:    ��������
**
**------------------------------------------------------------------------------------------------------
** Created by:      Ruby
** Created date:    2011-12-06
** Version:         1.0
** Descriptions:    The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
********************************************************************************************************/
#include "king.h"
#include "appl.h"                               /* Kingtron library and I/O routines */
#include "exthead.h"

#include "stm32f10x.h"
#include "KeyBoard.h"
#include "TypeDef.h"
#include "interface.h"
#include "fsmc_sram.h"
//#include "SysTick.h"


extern BYTE    KeyFrHost;       //ApplVar.Key code from host computer.
extern BYTE Bios_Key0_Key;			//    key number: 00 = No key


#define KB_ROW	0x303F

#define KEY_STATE_0 0
#define KEY_STATE_1 1
#define KEY_STATE_2 2
#define KEY_STATE_3 3

#define CLOSE_KEY	0x0b

uint8_t dis_buf[KEY_BUFFER_SIZE]= {0}; //��ʾ����
uint8_t key_number[COMB_KEY_TOTAL],key_total;
uint8_t key_state = 0;
uint8_t comb_index = 0,flag_press = 0;
uint8_t bitflag_key = 0; /* bit0:���¼���־ bit1:�������±�־ bit7:���������־ */
#ifdef DD_LOCK
uint8_t LockCurVal=0; //����Կ�����λ�õļ�ֵ
#endif

#if CASE_ER220
uint8_t key_value[]=					   /*  ɨ�����봫��Ӧ�ò�ļ�ֵһһ��Ӧ��: �����±����ɨ���� */
{
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x23,0x22,0x21,0x20,0x1F,0x1E,0x1D,
	 0x00,0x1C,0x1B,0x1A,0x19,0x18,0x17,0x16,
	 0x00,0x15,0x14,0x13,0x12,0x11,0x10,0x0F,
	 0x00,0x0E,0x0D,0x0C,0x0B,0x0A,0x09,0x08,
	 0x00,0x07,0x06,0x05,0x04,0x03,0x02,0x01
};

#elif CASE_ER520U
#define KB_LOCK	GPIO_Pin_3
uint8_t key_value[]=					   /*  ɨ�����봫��Ӧ�ò�ļ�ֵһһ��Ӧ��: �����±����ɨ���� */
{
/*   �ػ� ���� ���� ���� ���� ����           */
	 OFF+1,RG+1,X+1, Z+1,MG+1,SET+1,0x00,0x00,
	 0x23,0x19,0x0F,0x05,0x1A,0x2C,0x10,0x06,
	 0x22,0x18,0x0E,0x04,0x1B,0x2B,0x11,0x07,
	 0x21,0x17,0x0D,0x03,0x1C,0x2A,0x12,0x08,
	 0x20,0x16,0x0C,0x02,0x1D,0x29,0x13,0x09,
	 0x1F,0x15,0x0B,0x01,0x1E,0x28,0x14,0x0A,
	 0x00,0x00,0x00,0x00,0x2D,0x00,0x24,0x25,
	 0x00,0x00,0x00,0x00,0x2E,0x00,0x2F,0x26,
	 0x00,0x00,0x00,0x00,0x27,0x00,0x30,0x00
};
#elif CASE_ER260
uint8_t key_value[]=					   /*  ɨ�����봫��Ӧ�ò�ļ�ֵһһ��Ӧ��: �����±����ɨ���� */
{
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
	 0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,
	 0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
	 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
	 0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
#elif CASE_PCR01
uint8_t key_value[]=
{
    0x00,0x25,0x1F,0x19,0x13,0x0D,0x07,0x01,
    0x00,0x26,0x20,0x1A,0x14,0x0E,0x00,0x02,
    0x00,0x27,0x21,0x1B,0x15,0x0F,0x09,0x03,
    0x00,0x22,0x24,0x18,0x16,0x10,0x0A,0x04,
    0x00,0x28,0x00,0x1E,0x1C,0x11,0x0B,0x05,
    0x00,0x00,0x12,0x0C,0x1D,0x00,0x00,0x00,
    0x00,0x00,0x00,0x06,0x17,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
#elif CASE_ER100
uint8_t key_value[]=
{
	 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x00,
	 0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x00,
	 0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x00,
	 0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x00,
	 0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x00,
	 0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x00,
	 0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x00,
	 0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x00,
};
#elif CASE_GIADA3000
uint8_t key_value[]=
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x17,0x06,0x00,0x00,0x00,
    0x00,0x00,0x00,0x1D,0x0C,0x12,0x00,0x00,
    0x05,0x0B,0x11,0x1C,0x1E,0x00,0x28,0x00,
    0x04,0x0A,0x10,0x16,0x18,0x24,0x22,0x00,
    0x03,0x09,0x0F,0x15,0x1B,0x21,0x27,0x00,
    0x02,0x00,0x0E,0x14,0x1A,0x20,0x26,0x00,
    0x01,0x07,0x0D,0x13,0x19,0x1F,0x25,0x00,
};
#elif CASE_MCR30
uint8_t key_value[]=
{
	 0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x00,
	 0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x00,
	 0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x00,
	 0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x00,
	 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*
	 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
	 0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,
	 0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
	 0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,
	 0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
	 0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,
	 0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
	 0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,
	*/

};

#endif

uint32_t keydown_flag = 0;	                 // ÿһλ������Ӧ���İ���״̬�����3λΪ1�������ֵΪ3�ļ�������
uint8_t keydown_flag2 = 0;

uint8_t key_putin = 0;
uint8_t key_getout = 0;

volatile uint32_t Times_Of_10ms = 0;

uint8_t fBeep = true;
volatile uint16_t beep_len=0;
volatile uint8_t KeyScanEnable=0;

extern volatile BYTE DrawerOpen_time;

extern void TIM7_Init(void);

void KeyBoardDeInit(void);
void EXTILine_Init(void);
void KeyBoardInit(void)
{

#if CASE_ER520U
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KB_LOCK; //��ɨ������ź�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif

	KeyBoardDeInit();
	TIM7_Init();
	EXTILine_Init();

}


#ifdef DD_LOCK

void lockscan(void)
{
	uint8_t i,j;
	uint16_t k_col;

	uint8_t cnt=0;

	GPIOC->BRR = KB_LOCK;	//��ɨ������ź�
	*(uint16_t *)(KB_ADDR) = 0xFF;
	j = 0xF0;//0x30;
	while(j--);
	k_col = *(__IO uint16_t*) (KB_ADDR);
	if(k_col != 0xFF)
	{
		for(j=0; j<8; j++)
		{
			if(!((k_col >> j)&0x01))
				cnt++;
		}
		if (cnt == 1)	//ouhs20161205 ͬʱ���³����������еļ�,��Ӱ����λ�õ�����
		{
			for(j=0; j<8; j++)
			{
				if(!((k_col >> j)&0x01))
				{
					i = 0xF0;	//0x50;
					while(i--);
					if(!((k_col >> j)&0x01))
					{
						if(LockCurVal != key_value[j])
						{
							LockCurVal = key_value[j];
							dis_buf[key_putin++] =key_value[j];
							if(key_putin >= KEY_BUFFER_SIZE)
							 key_putin = 0;
						}
					}
				}
			}
		}
	}
	GPIOC->BSRR = KB_LOCK;
}

void keyscan(void)
{
	uint8_t i, j;
	uint16_t k_col;
	key_total = 0;

	lockscan();//��ɨ��

	j = 0xF0;//0x80;
	while(j--);

	for(i=1; i<9; i++)
	{

		*(uint16_t *)(KB_ADDR) = ~(1<<(i-1));
		j = 0xF0;//0x80;
		while(j--);
		k_col = *(__IO uint16_t*) (KB_ADDR);
		if(k_col != 0xFF)
		{
			for(j=0; j<8; j++)
			{
				if(!((k_col >> j)&0x01))
				{
					key_total++;
					if(key_total >= COMB_KEY_TOTAL)
						key_total = COMB_KEY_TOTAL;
					key_number[key_total - 1] = key_value[(i<<3 | j)];	//��ȡ���µļ���
				}
			}
		}
	}
}
#else
void keyscan(void)
{
	uint8_t i, j;
	uint16_t k_col;
	key_total = 0;
	for(i=0; i<8; i++)
	{
		*(uint16_t *)(KB_ADDR) = ~(1<<i);
		j = 0xC0;//0x80;
		while(j--);
		k_col = *(__IO uint16_t*) (KB_ADDR);
		if(k_col != 0xFF)
		{
			for(j=0; j<8; j++)
			{
				if(!((k_col >> j)&0x01))
				{
					key_total++;
					if(key_total >= COMB_KEY_TOTAL)
						key_total = COMB_KEY_TOTAL;
                    key_number[key_total - 1] = key_value[(i | j<<3)];	//��ȡ���µļ���
				}
			}
		}
	}
}
#endif



void keydown(void)
{
    uint8_t i;
    static uint8_t key_total_old;

	//ɨ�����
    keyscan();

	//����״̬����
    switch (key_state)
    {
        //������ʼ̬ �ޱպϼ�
        case KEY_STATE_0:
			flag_press = 0;
			comb_index = 0;
            key_total_old = 0;
            //�������£�ת������ȷ��̬
            if (key_total)
            {
                key_total_old = key_total;

                key_state = KEY_STATE_1;
            }
            break;

        //����ȷ��̬
        case KEY_STATE_1:
			//��������������ԭ״̬
            if (key_total_old != key_total) //��ʱ key_total >= 1
            {
	            //��ʼ̬���������ذ�����ʼ̬
            	if (flag_press == 0)
	            {
	                key_state = KEY_STATE_0;
	            }
	            //�ȴ�̬���������ذ����ȴ�̬
            	else
	            {
	                key_state = KEY_STATE_2;
	            }
            }
            //�����ȶ���������ϼ����У�ת��ȴ�̬
        	else
        	{

				//���¼�����
	            if (key_total > comb_index) //���߲�������ȣ����򰴼�Ӧ�����ȶ��ȴ�̬
				{
					//����һ��ͬʱ���µļ�����ϼ�����ͷ
		            if (0 == comb_index)
		            {
						comb_index = key_total;
						keydown_flag = 0;
						keydown_flag2 = 0;
						for (i = 0; i < key_total; i++)
		                {
							if(key_number[i]<32)
								keydown_flag |= (1UL<<key_number[i]);
							else
								keydown_flag2 |= (1UL<<(key_number[i]-32));

							if (key_number[i]>0)//ccr
								dis_buf[key_putin++] =key_number[i];
		                }
						flag_press = 1;
		            }
					//���¼��ӵ���ϼ�����β
		            else
		            {
		                for (i = 0; i < key_total; i++)
		                {
							if(key_number[i]<32)
							{
								if(!(keydown_flag&(1UL<<key_number[i])))
								{
                                    if (key_number[i]>0)//ccr
                                    {
                                        dis_buf[key_putin++] = key_number[i];
                                        comb_index++;
                                    }

								}
							}
							else
							{
								if(!(keydown_flag2&(1UL<<(key_number[i]-32))))
								{
                                    if (key_number[i]>0)//ccr
									{
										dis_buf[key_putin++] =key_number[i];
										comb_index++;
									}
								}
							}
			            }
		            }
					if(key_putin >= KEY_BUFFER_SIZE)
						 key_putin = 0;

					bitflag_key |= 0x81;	//���ڷ��ͱ��

	                key_state = KEY_STATE_2;

				}
				//�м��ͷ�
				else
				{
					//��������ֵ
					keydown_flag = 0;
					keydown_flag2 = 0;
					comb_index = key_total;
					for (i = 0; i < key_total; i++)
	                {
						if(key_number[i]<32)
							keydown_flag |= (1UL<<key_number[i]);
						else
							keydown_flag2 |= (1UL<<key_number[i]);
	                }

		            //���а����ͷţ�ת����������ʼ̬
	            	if (key_total == 0)
		            {
		            	flag_press = 0;
						comb_index = 0;
						keydown_flag = 0;
						keydown_flag2 = 0;
		                key_state = KEY_STATE_0;
						bitflag_key &= (~0x80);
		            }
		            //���а���δ�ͷţ�ת���������ȴ�̬
	            	else
		            {
		                key_state = KEY_STATE_2;
		            }
				}
			}
            break;

        //�ȴ�̬ �бպϼ����ȴ��¶���
        case KEY_STATE_2:
            if (key_total != key_total_old)
        	{
                key_total_old = key_total;

                key_state = KEY_STATE_1;
        	}
			break;
    	}

}

#ifdef DD_LOCK
uint8_t GetchLockVal(void)
{
	return (LockCurVal-1);	//����Կ�����λ�õļ�ֵ
}
#endif


/** ��ȡ��������İ���
  * @param  None
  * @retval :key pressed
  */


uint8_t Getch(void)
{  //��ȡ����,�ڶ�ȡ����֮ǰ,��ʹ��BiosCmd_CheckKeyborad�������Ƿ��а���.

    if (TESTBIT(ApplVar.MyFlags, KEYFROMHOST))
    {
        RESETBIT(ApplVar.MyFlags, KEYFROMHOST);
        return(Bios_Key0_Key-1);
    }
	else
	{
		Bios_Key0_Key=dis_buf[key_getout++]-1;
		if(key_getout >= KEY_BUFFER_SIZE)
			 key_getout = 0;

		return (Bios_Key0_Key);
	}
}
/** �������Ƿ�������
  * @param  None
  * @retval true:a key pressed
  */
uint8_t CheckKeyboard(void)
{
	if (key_putin==key_getout)
		return 0;
	else
	{
#if !defined(CASE_ASCIIDISPLAY)
//		if (!TESTBIT(ApplVar.ScreenStat,LIGHTON))
			mLightLCDOn();
        LED_On();
#endif
		return (dis_buf[key_getout]);
	}
}

/** ������ֹ���̷�����
  * @param  on_off:
  * @retval None
  */
void EnableBeep(uint8_t on_off)
{
	fBeep = on_off;
}

/** ����������̰�������
  * @brief  This function handles TIM7 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM7_IRQHandler(void)
{
//	OSIntEnter();
	//if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

		//Times_Of_10ms++;
#ifndef CASE_ER520U	//��ʹ�÷�ʽ������Ҫȡ��KB_INT�жϴ���ɨ��,�����Ƶ�������ж�
		if (KeyScanEnable < 10)		//100ms
#endif
		{
			keydown();
#ifndef CASE_ER520U	//
			KeyScanEnable++;
			KeyBoardDeInit();
#endif
		}

		if((bitflag_key & 0x01))
		{
			if(fBeep)
				Beep(1);
			//Times_Of_10ms = 0;
		}
		else
		{
			//if(!(bitflag_key & 0x80))
				//Times_Of_10ms = 0;
		}
#if (0) //testonly
		if(key_putin != key_getout)
		{
			//xputc(dis_buf[key_getout++]);     //testonly
			USART_printf("KeyValue:0x%x \r\n",dis_buf[key_getout++]);
			if(key_getout >= KEY_BUFFER_SIZE)
				key_getout = 0;
		}
#endif
		bitflag_key &= (~0x01);

		/* start beep: beep_len*10ms  */
		if(beep_len)
		{
			if (--beep_len==0)
				BEEP_OFF();
		}
		/* start DRAWER pulse output:DrawerOpen_time*10ms  */

		if(DrawerOpen_time)
		{
			if(--DrawerOpen_time == 0)
				DRAWER_OFF();
		}

		/* end DRAWER pulse output   */
	}
//	OSIntExit();
}

void KeyBoardDeInit(void)
{
	*(uint16_t *)(KB_ADDR) = 0;	// ��KB_C[7..0]����Ϊ�͵�ƽ
#ifdef CASE_ER520U
	GPIOC->BRR = KB_LOCK;	//��ɨ������ź�
#endif
}

/*********************************************************************************************************
** Function name: EXTILine_Init
** Descriptions:  �ⲿ�ж��źų�ʼ���������������������жϡ��������жϡ�
*********************************************************************************************************/
void EXTILine_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;

	/* Enable GPIOG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE);

	/* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// PE2�������ź�,PE6���̼���ź�
	/* Configure pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_6;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*  PA8 ��̫���ж��ź� */

	/* Connect EXTI Line to Selected pin */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);   //PFO

	/* Configure EXTI Line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  	  // �½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

    /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

#ifndef CASE_ER520U	//��ʹ�÷�ʽ������Ҫȡ��KB_INT�жϴ���ɨ��,�����Ƶ�������ж�

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource6); 	//KB_INT

	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  	  // ������
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //ouhs 20140814 =0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //ouhs 20140814 =3
	NVIC_Init(&NVIC_InitStructure);
#endif

}
//ccr clean keyboar data
void CleanKeyboard()
{
    key_putin = 0;
    key_getout = key_putin;

}
/*********************************************** End Of File *******************************************/
