/**
  ******************************************************************************
  * @file    stm322xg_eval_fsmc_sram.c
  * @author  MCD Application Team
  * @version V5.0.3
  * @date    09-March-2012
  * @brief   This file provides a set of functions needed to drive the
  *          IS61WV102416BLL SRAM memory mounted on STM322xG-EVAL evaluation
  *          board(MB786) RevB.
  *
  *          Note: This memory is not available on the RevA of the board.
  *
  ******************************************************************************/
/**-----------Includes --------------------------------------------------------*/
#include "fsmc_sram.h"

#include <string.h>  //ouhs 20140815


//ʹ��1Ƭ512KB SRAM EM643FV16F
//ʹ��1Ƭ256KB SRAM EM621FV16B
uint32_t SRAM_Detect(void)
{//���SRAM�������ڻ����״ο���ִ��һ��
	uint8_t tmp;

	*(uint8_t *) (SRAM_ADDR + 0x1FFFFF) = 0xA5; //2MBĩ��ַ --ER-520��4Ƭ512KBоƬ
	__NOP();__NOP();__NOP();
	tmp = *(uint8_t *) (SRAM_ADDR + 0x1FFFFF);
	if (tmp == 0xA5)
		return (0x200000L);

	*(uint8_t *) (SRAM_ADDR + 0x17FFFF) = 0x5A; //1MB+512KBĩ��ַ --ER-520��3Ƭ512KBоƬ
	__NOP();__NOP();__NOP();
	tmp = *(uint8_t *) (SRAM_ADDR + 0x17FFFF);
	if (tmp == 0x5A)
		return (0x180000L);

	*(uint8_t *) (SRAM_ADDR + 0xFFFFF) = 0xA5; //1MBĩ��ַ --ER-520��2Ƭ512KBоƬ
	__NOP();__NOP();__NOP();
	tmp = *(uint8_t *) (SRAM_ADDR + 0xFFFFF);
	if (tmp == 0xA5)
		return (0x100000l);

	*(uint8_t *) (SRAM_ADDR + 0x7FFFF) = 0x5A; //512KBĩ��ַ --ER-520��1Ƭ512KBоƬ��ER-260��2Ƭ256KBоƬ
	__NOP();__NOP();__NOP();
	tmp = *(uint8_t *) (SRAM_ADDR + 0x7FFFF);
	if (tmp == 0x5A)
		return (0x80000L);

	*(uint8_t *) (SRAM_ADDR + 0x3FFFF) = 0xA5; //256KBĩ��ַ --ER-260��1Ƭ256KBоƬ��ER-220����
	__NOP();__NOP();__NOP();
	tmp = *(uint8_t *) (SRAM_ADDR + 0x3FFFF);
	if (tmp == 0xA5)
		return (0x40000L);
	return (0L);
}


void FSMC_IOInit(void);

/************ FSMC IO���� ************/
void FSMC_IOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable GPIOs clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOE |
										 RCC_APB2Periph_GPIOF, ENABLE);

/*-- GPIOs Configuration -----------------------------------------------------*/
/*
 +-------------------+--------------------+------------------+------------------+
 | PD0  <-> FSMC_D2  | PE0  <-> FSMC_NBL0 | PF0 <-> FSMC_A0  | PG0 <-> FSMC_A10 |
 | PD1  <-> FSMC_D3  | PE1  <-> FSMC_NBL1 | PF1 <-> FSMC_A1  | PG1 <-> FSMC_A11 |
 | PD4  <-> FSMC_NOE | PE2  <-> --------- | PF2 <-> FSMC_A2  | PG2 <-> FSMC_A12 |
 | PD5  <-> FSMC_NWE | PE3  <-> FSMC_A19  | PF3 <-> FSMC_A3  | PG3 <-> FSMC_A13 |
 | PD8  <-> FSMC_D13 | PE4  <-> FSMC_A20  | PF4 <-> FSMC_A4  | PG4 <-> FSMC_A14 |
 | PD9  <-> FSMC_D14 | PE5  <-> FSMC_A21  | PF5 <-> FSMC_A5  | PG5 <-> FSMC_A15 |
 | PD10 <-> FSMC_D15 | PE6  <-> --------- | PF12 <-> FSMC_A6 | PG9 <-> FSMC_NE2 |
 | PD11 <-> FSMC_A16 | PE7  <-> FSMC_D4   | PF13 <-> FSMC_A7 | PG10 <-> FSMC_NE3 |
 | PD12 <-> FSMC_A17 | PE8  <-> FSMC_D5   | PF14 <-> FSMC_A8 |
 | PD13 <-> FSMC_A18 | PE9  <-> FSMC_D6   | PF15 <-> FSMC_A9 |
 | PD14 <-> FSMC_D0  | PE10 <-> FSMC_D7   |------------------+
 | PD15 <-> FSMC_D1  | PE11 <-> FSMC_D8   |
 +-------------------| PE12 <-> FSMC_D9   |
   PD7  <-> FSMC_NE1 | PE13 <-> FSMC_D10  |
                     | PE14 <-> FSMC_D11  |
                     | PE15 <-> FSMC_D12  |
                     +--------------------+
*/

    /* GPIOD configuration */
    // GPIOD����������ó�FSMC���ܡ����졢��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_7 |
                                  GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 |
                                  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* GPIOE configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_3 |
                                  GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_7 |
                                  GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11|
                                  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

    GPIO_Init(GPIOE, &GPIO_InitStructure);

    /* GPIOF configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_2 | GPIO_Pin_3 |
                                  GPIO_Pin_4  | GPIO_Pin_5  |
                                  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

    GPIO_Init(GPIOF, &GPIO_InitStructure);

    /* GPIOG configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_2 | GPIO_Pin_3 |
                                  GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_9 | GPIO_Pin_10;

    GPIO_Init(GPIOG, &GPIO_InitStructure);
}

/**
  * @brief  Configures the FSMC and GPIOs to interface with the SRAM memory.
  *         This function must be called before any write/read operation
  *         on the SRAM.
  * @param  None
  * @retval None
  */
void FSMC_Init(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  p;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

    FSMC_IOInit();
/*-- FSMC Configuration ------------------------------------------------------*/
    //------------FSMC_Bank1_NORSRAM1 ����NOR Flash: MX29LV160DBT1---//
    p.FSMC_AddressSetupTime = 5;      //��ַ����ʱ�� 0 5
    p.FSMC_AddressHoldTime = 0;       //��ַ����ʱ�� 0 3
    p.FSMC_DataSetupTime = 8;         //���ݽ���ʱ�� 5 6
    p.FSMC_BusTurnAroundDuration = 0; //1
    p.FSMC_CLKDivision = 0;
    p.FSMC_DataLatency = 0;
    p.FSMC_AccessMode = FSMC_AccessMode_B;

    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;                    // SRAMʹ��FSMC_NE2Ƭѡ
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;  // ��ʹ��������/��ַ�߸���ģʽ
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;            // �洢������:PSRAM
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;    // �洢�����16bit
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;      // ��չģʽ(����дʹ�ò�ͬ��ʱ��)
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

	//------------FSMC_Bank1_NORSRAM2 ����SRAM:EM643FV16F------------//
	p.FSMC_AddressSetupTime = 2;      //��ַ����ʱ�� 0 5
    p.FSMC_AddressHoldTime = 0;       //��ַ����ʱ�� 0 3
    p.FSMC_DataSetupTime = 6;         //���ݽ���ʱ�� 5 6
	p.FSMC_AccessMode = FSMC_AccessMode_A;

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM2;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

	//------------FSMC_Bank1_NORSRAM3 ��������------------//
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    //------------ʹ��FSMC_Bank1_NORSRAM1��2��3��4 ------------------//
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM2, ENABLE);
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);

}



/**
  * @brief  Writes a Half-word buffer to the FSMC SRAM memory.
  * @param  pBuffer : pointer to buffer.
  * @param  WriteAddr : SRAM memory internal address from which the data will be
  *         written.
  * @param  NumHalfwordToWrite : number of half-words to write.
  * @retval None
  */

void SRAM_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumHalfwordToWrite)
{
#if (!SRAMSIZE_SHIFT)
#if 1
	uint8_t *pWrite = (uint8_t *)(WriteAddr+SRAM_ADDR);

    if (NumHalfwordToWrite>1)
        memcpy(pWrite,pBuffer,NumHalfwordToWrite);
    else
        *pWrite = *pBuffer;

#elif 0
	uint8_t *pWrite = (uint8_t *)(WriteAddr+SRAM_ADDR);
	for (;NumHalfwordToWrite;NumHalfwordToWrite--)
		*pWrite++ = *pBuffer++;
#else
	WriteAddr += SRAM_ADDR;
    if (NumHalfwordToWrite)
    {
        if (WriteAddr & 1)//�����ַ�Ͽ�ʼд����
        {
            //�������ַ��д��һ���ֽ�,
            *(uint8_t *) (WriteAddr) = *pBuffer++;
            WriteAddr ++;
            NumHalfwordToWrite--;
        }
        for (; NumHalfwordToWrite >=2; NumHalfwordToWrite-=2) /* while there is data to write */
        {
            //��ż��ַ��,��WORD��ʽд������,�������д���ٶ�
            /* Transfer data to the memory */
            *(uint16_t *) (WriteAddr) = *(uint16_t *) pBuffer;
            WriteAddr+=2;
            pBuffer+=2;
        }
        if (NumHalfwordToWrite)
        {//д�����һ���ֽ�
            *(uint8_t *) (WriteAddr) = *pBuffer;
        }
    }
#endif
#else  // SRAMSIZE_SHIFT
	uint32_t count;
	uint8_t NumOfPage;
    if (NumHalfwordToWrite)
    {
		count = SRAM_8KB - (WriteAddr % SRAM_8KB);
		NumOfPage =  NumHalfwordToWrite / SRAM_8KB; //��������Page, SIZE:8KB

		WriteAddr += SRAM_ADDR;
		//�������ַ��д��һ���ֽ�
		SRAM_A12_SHIFT(WriteAddr);
		if (WriteAddr & 1)
		{
			*(uint8_t *) (WriteAddr) = *pBuffer++;
			WriteAddr ++;
			NumHalfwordToWrite--;
			count--;
		}

		//д��ǰpage��д��count�ֽڻ�NumHalfwordToWrite�ֽ�
		SRAM_A12_SHIFT(WriteAddr);
		if(NumHalfwordToWrite <= count)
			count = NumHalfwordToWrite;

		if(count & 0x01)//����forѭ��ʱ��
			NumHalfwordToWrite -= (count-1);
		else
			NumHalfwordToWrite -= (count);

		for (; count >=2; count-=2) /* while there is data to write */
		{
			//��ż��ַ��,��WORD��ʽд������,�������д���ٶ�
			/* Transfer data to the memory */
			*(uint16_t *) (WriteAddr) = *(uint16_t *) pBuffer;
			WriteAddr+=2;
			pBuffer+=2;
			//NumHalfwordToWrite-=2;
		}


		//����1����NumOfPage+1��page��д��ʣ��ż�����ֽ�
		if(NumHalfwordToWrite > count)
		{
			NumOfPage += 1;
			for (; NumOfPage>0; NumOfPage--)
			{
				if(NumHalfwordToWrite > SRAM_8KB)
					count = SRAM_8KB;
				else
					count = NumHalfwordToWrite;
				SRAM_A12_SHIFT(WriteAddr);

				if(count & 0x01) //����forѭ��ʱ��
					NumHalfwordToWrite -= (count-1);
				else
					NumHalfwordToWrite -= (count);

				for (; count >=2; count-=2) /* while there is data to write */
				{
					//��ż��ַ��,��WORD��ʽд������,�������д���ٶ�
					/* Transfer data to the memory */
					*(uint16_t *) (WriteAddr) = *(uint16_t *) pBuffer;
					WriteAddr+=2;
					//NumHalfwordToWrite-=2;
					pBuffer+=2;
				}
			}
		}

		if (NumHalfwordToWrite)
		{//д�����һ���ֽ�
			SRAM_A12_SHIFT(WriteAddr);
			*(uint8_t *) (WriteAddr) = *pBuffer;
		}
	}
#endif
}


/**
  * @brief  Reads a block of data from the FSMC SRAM memory.
  * @param  pBuffer : pointer to the buffer that receives the data read from the
  *         SRAM memory.
  * @param  ReadAddr : SRAM memory internal address to read from.
  * @param  NumHalfwordToRead : number of half-words to read.
  * @retval None
  */
void SRAM_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumHalfwordToRead)
{

#if (!SRAMSIZE_SHIFT)
#if 1
	uint8_t *pRead = (uint8_t *)(ReadAddr+SRAM_ADDR);

    if (NumHalfwordToRead>1)
        memcpy(pBuffer,pRead,NumHalfwordToRead);
    else
       *pBuffer =   *pRead;

#elif 0
	uint8_t *pRead = (uint8_t *)(ReadAddr+SRAM_ADDR);

	for(;NumHalfwordToRead;NumHalfwordToRead--)
		*pBuffer =   *pRead;

#else
	ReadAddr += SRAM_ADDR;
    if (NumHalfwordToRead)
    {
        if (ReadAddr & 1)
        {
            *pBuffer++ = *(__IO uint8_t*) (ReadAddr);
            NumHalfwordToRead--;
            ReadAddr++;
        }
        for (; NumHalfwordToRead >=2; NumHalfwordToRead-=2) /* while there is data to read */
        {
            /* Read a half-word from the memory */
            *(uint16_t*)pBuffer = *(__IO uint16_t*) (ReadAddr);

            /* Increment the address*/
            ReadAddr +=2;
            pBuffer+=2;
        }
        if (NumHalfwordToRead)
        {
            *pBuffer = *(__IO uint8_t*) (ReadAddr);
        }
    }
#endif
#else  // SRAMSIZE_SHIFT
	uint32_t count=0;
	uint8_t NumOfPage=0;
    if (NumHalfwordToRead)
    {
		count = SRAM_8KB - (ReadAddr % SRAM_8KB);
		NumOfPage =  NumHalfwordToRead / SRAM_8KB; //��������Page, SIZE:8KB

		ReadAddr += SRAM_ADDR;
		SRAM_A12_SHIFT(ReadAddr);
		if (ReadAddr & 1)
		{
			*pBuffer++ = *(uint8_t *) (ReadAddr);
			ReadAddr ++;
			NumHalfwordToRead--;
			count--;
		}

		SRAM_A12_SHIFT(ReadAddr);
		if(NumHalfwordToRead <= count)
			count = NumHalfwordToRead;
		if(count & 0x01)
			NumHalfwordToRead -= (count-1);
		else
			NumHalfwordToRead -= (count);
		for (; count >=2; count-=2) /* while there is data to write */
		{
			/* Transfer data to the memory */
			*(uint16_t *) pBuffer = *(uint16_t *) (ReadAddr);
			ReadAddr+=2;
			pBuffer+=2;
			//NumHalfwordToRead-=2;
		}

		if(NumHalfwordToRead > count)
		{
			NumOfPage += 1;
			for (; NumOfPage>0; NumOfPage--)
			{
				if(NumHalfwordToRead > SRAM_8KB)
					count = SRAM_8KB;
				else
					count = NumHalfwordToRead;
				if(count & 0x01)
					NumHalfwordToRead -= (count-1);
				else
					NumHalfwordToRead -= (count);
				SRAM_A12_SHIFT(ReadAddr);
				for (; count >=2; count-=2) /* while there is data to write */
				{
					/* Transfer data to the memory */
					*(uint16_t *) pBuffer = *(uint16_t *) (ReadAddr);
					ReadAddr+=2;
					//NumHalfwordToRead-=2;
					pBuffer+=2;
				}
			}
		}

		if (NumHalfwordToRead)
		{
			SRAM_A12_SHIFT(ReadAddr);
			*pBuffer = *(uint8_t *) (ReadAddr);
		}
	}
#endif
}



/**
  * @brief  Move a block of data from the FSMC SRAM memory.
  * @param  toAddr : SRAM memory internal address for data to Move to
  * @param  fromAddr : SRAM memory internal address for data to move from.
  * @param  BytesToMove : number of half-words to copy.
  * @retval None
  */
void SRAM_Move(uint32_t toAddr, uint32_t fromAddr, int32_t BytesToMove)
{
	//SRAM_A12_SHIFT(toAddr);
	//SRAM_A12_SHIFT(fromAddr);
    if (toAddr<fromAddr)
    {//Ϊ�ɸߵ�ַ����ص�ַ���ƶ�����
        if (BytesToMove>0)
        {
            //      fromAddr->*************
            //toAddr->*************
        }
        else//BytesToMove<0
        {
            //      *************<-fromAddr
            //*************<-toAddr
            fromAddr+=BytesToMove;
            toAddr+=BytesToMove;
            fromAddr++;
            toAddr++;
            BytesToMove=-BytesToMove;
        }

		//SRAM_A12_SHIFT(toAddr);
		//SRAM_A12_SHIFT(fromAddr);

		toAddr += SRAM_ADDR;
		fromAddr += SRAM_ADDR;
#if 0
        memcpy((uint8_t*)(toAddr),(uint8_t*)(fromAddr),BytesToMove);
#else
        for (; BytesToMove != 0; BytesToMove--) /* while there is data to read */
        {
            /* Read a half-word from the memory */
            *(__IO uint8_t*) (toAddr) = *(__IO uint8_t*) (fromAddr);

            /* Increment the address*/
            fromAddr ++;
            toAddr++;
			//SRAM_A12_SHIFT(toAddr);
			//SRAM_A12_SHIFT(fromAddr);
        }
#endif
    }
    else if (toAddr>fromAddr)
    {//Ϊ�ɵ͵�ַ����ߵ�ַ���ƶ�����
        if (BytesToMove>0)
        {
            //fromAddr->*************
            //      toAddr->*************
            fromAddr+=BytesToMove;
            toAddr+=BytesToMove;
            fromAddr--;
            toAddr--;
        }
        else
        {
            // *************<-fromAddr
            //      *************<-toAddr
            BytesToMove=-BytesToMove;
        }

		//SRAM_A12_SHIFT(toAddr);
		//SRAM_A12_SHIFT(fromAddr);

		toAddr += SRAM_ADDR;
		fromAddr += SRAM_ADDR;

        for (; BytesToMove != 0; BytesToMove--) /* while there is data to read */
        {
            /* Read a half-word from the memory */
            *(__IO uint8_t*) (toAddr) = *(__IO uint8_t*) (fromAddr);

            /* Increment the address*/
            fromAddr--;
            toAddr--;
			//SRAM_A12_SHIFT(toAddr);
			//SRAM_A12_SHIFT(fromAddr);
        }
    }

}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
