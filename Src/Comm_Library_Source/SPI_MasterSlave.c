/**
  ******************************************************************************
  * @file    SPI_Master.c
  * @author  Serbay Ozkan
  * @version V1.0.0
  * @date    28-October-2017
  * @brief   SPI Master Communication Application Layer Source File
  ******************************************************************************
  */

#include "stm32f7xx_hal.h"
#include "spi.h"
#include "gpio.h"
#include "stdint.h"
#include "string.h"

/* User Includes */
#include "SPI_MasterSlave.h"
#include "DataParserMerger.h"
#include "CommConfig.h"

/* User Typedef Prototypes */
Typedef_comParams       comParams;
Typedef_spiCRC          spiCRC;


/* This function should be called in super loop */
void spi_runComApp(void)
{
	spi_pushAllDataCheck();
    spi_RuntimeProcess();
    spi_checkCommunication();
}

/* This function should be called in 1ms timer */
void spi_sysTickCallApp(void)
{
	spi_ReceiveTimeout();
  	spi_checkPushSendTime();
}

/* This function should be called before super loop */
void spi_initComApp(void)
{
	spi_deselectChip();
	spi_receiveInit();
}

static void spi_selectChip(void)
{
	 // HAL_GPIO_WritePin(SPI_COM_GPIO_Port, SPI_COM_Pin, GPIO_PIN_RESET);
}

static void spi_deselectChip(void)
{
	 // HAL_GPIO_WritePin(SPI_COM_GPIO_Port, SPI_COM_Pin, GPIO_PIN_SET);
}

static void spi_ReceiveCompCallBack(void)
{
    comParams.recTimeOut = 0;
    comParams.recFlag = FLAG_IS_ACTIVE;
    comParams.transmitComp = 0;
}

static void spi_ReceiveTimeout(void)
{
	comParams.recTimeOut++;
	if (comParams.recFlag == FLAG_IS_ACTIVE && comParams.recTimeOut == RECEIVE_TIMEOUT)
	{
		comParams.recComp = FLAG_IS_ACTIVE;
		comParams.recTimeOut = 0;
	}

	if (comParams.recTimeOut == 0xFFFF)
	{
		comParams.recTimeOut = 0;
	}
}

static void spi_RuntimeProcess(void)
{
   if(comParams.recComp == 1 && comParams.recFlag == FLAG_IS_ACTIVE)
   {
	    spi_frameProcess();
	    comParams.rxIndex = 0;
	    comParams.recComp = FLAG_IS_INACTIVE;
	    comParams.recFlag = FLAG_IS_INACTIVE;
   }
}

static void spi_frameProcess(void)
{
	spi_prepareReceiveData();
}

static void spi_pushAllData(void)
{
	spi_prepareTestData();
	spi_preparePushData();
	spi_selectChip();
	HAL_SPI_Transmit_IT(&hspi2, comParams.txBuffer, comParams.txIndex);
}

static void spi_pushAllDataCheck(void)
{
	#if MASTER_DEVICE
	if (comParams.pushFlag == FLAG_IS_ACTIVE)
	{
		spi_pushAllData();
		comParams.pushFlag = FLAG_IS_INACTIVE;
	}
	#endif
}

static void spi_checkPushSendTime(void)
{
	comParams.pushDataTimerCnt++;
	if (comParams.pushDataTimerCnt >= SPI_PUSH_ALL_DATA_TIME)
	{
		comParams.pushFlag = FLAG_IS_ACTIVE;
		comParams.pushDataTimerCnt = 0;
	}
}

static void spi_receiveInit(void)
{
	#if !MASTER_DEVICE
	HAL_SPI_Receive_IT(&hspi2, comParams.rxBuffer, READ_TOTAL_BUFFER_SIZE);
	#endif
}

static void spi_preparePushData(void)
{
	uint32_t bufIndexDW = 0; 	 /* Buffer Index for DWORD Values */
	uint32_t bufIndexF  = 0; 	 /* Buffer Index for Float Values */
    
    uint32_t bufIndexDWLast = 0; /* Buffer Last Index for DWORD Values */
	uint32_t bufIndexFLast  = 0; /* Buffer Last Index for Float Values */

    comParams.txBuffer[comParams.txIndex++] = SPI_UNIQUE_ID;
	comParams.txBuffer[comParams.txIndex++] = SPI_FUNCTION_ID;

    #if FIRST_DWORD_BLOCK_SIZE
    /* First Cycle Read */
	for (bufIndexDW = 0; bufIndexDW < FIRST_DWORD_BLOCK_SIZE; bufIndexDW++)
	{
		dpm_parseDWord(bufIndexDWLast++, &comParams.txIndex, comParams.pushDataBufferDW, comParams.txBuffer);
	}
	#endif

    #if FIRST_FLOAT_BLOCK_SIZE
	for (bufIndexF = 0; bufIndexF < FIRST_FLOAT_BLOCK_SIZE; bufIndexF++)
	{
		dpm_parseFloat(bufIndexFLast++, &comParams.txIndex, comParams.pushDataBufferF, comParams.txBuffer);
	}
    #endif

    #if SECOND_FLOAT_BLOCK_SIZE
	/* Second Cycle Read */
	for (bufIndexF = 0; bufIndexF < SECOND_FLOAT_BLOCK_SIZE; bufIndexF++)
	{
		dpm_parseFloat(bufIndexFLast++, &comParams.txIndex, comParams.pushDataBufferF, comParams.txBuffer);
	}
	#endif

	#if SECOND_DWORD_BLOCK_SIZE
 	for (bufIndexDW = 0; bufIndexDW < SECOND_DWORD_BLOCK_SIZE; bufIndexDW++)
	{
		dpm_parseDWord(bufIndexDWLast++, &comParams.txIndex, comParams.pushDataBufferDW, comParams.txBuffer);
	}
    #endif

    #if THIRTH_DWORD_BLOCK_SIZE
    /* Third  Cycle Read */
	for (bufIndexDW = 0; bufIndexDW < THIRTH_DWORD_BLOCK_SIZE; bufIndexDW++)
	{
		dpm_parseDWord(bufIndexDWLast++, &comParams.txIndex, comParams.pushDataBufferDW, comParams.txBuffer);
	}
    #endif

    #if THIRTH_FLOAT_BLOCK_SIZE
	for (bufIndexF = 0; bufIndexF < THIRTH_FLOAT_BLOCK_SIZE; bufIndexF++)
	{
		dpm_parseFloat(bufIndexFLast++, &comParams.txIndex, comParams.pushDataBufferF, comParams.txBuffer);
	}
    #endif

    #if FOURTH_DWORD_BLOCK_SIZE
    /* Fourth  Cycle Read */
	for (bufIndexDW = 0; bufIndexDW < FOURTH_DWORD_BLOCK_SIZE; bufIndexDW++)
	{
		dpm_parseDWord(bufIndexDWLast++, &comParams.txIndex, comParams.pushDataBufferDW, comParams.txBuffer);
	}
    #endif

    #if FOURTH_FLOAT_BLOCK_SIZE
	for (bufIndexF = 0; bufIndexF < FOURTH_FLOAT_BLOCK_SIZE; bufIndexF++)
	{
		dpm_parseFloat(bufIndexFLast++, &comParams.txIndex, comParams.pushDataBufferF, comParams.txBuffer);
	}
	#endif

	spi_crcCalculation(comParams.txBuffer, (READ_TOTAL_BUFFER_SIZE - 2));

    comParams.txBuffer[comParams.txIndex++] = spiCRC.calculated_H;
    comParams.txBuffer[comParams.txIndex++] = spiCRC.calculated_L;
}

static void spi_prepareReceiveData(void)
{
	uint32_t bufIndexDW = 0; 	 /* Buffer Index for DWORD Values */
	uint32_t bufIndexF  = 0; 	 /* Buffer Index for Float Values */
    
    uint32_t bufIndexDWLast = 0; /* Buffer Last Index for DWORD Values */
	uint32_t bufIndexFLast  = 0; /* Buffer Last Index for Float Values */

    comParams.index = 2;         /* index[0] -> ID, index[1] -> Transc. ID  */

    spi_crcCalculation(comParams.rxBuffer, (READ_TOTAL_BUFFER_SIZE - 2));

    spiCRC.received_H = comParams.rxBuffer[READ_TOTAL_BUFFER_SIZE - 2];
	spiCRC.received_L = comParams.rxBuffer[READ_TOTAL_BUFFER_SIZE - 1];

    if ((spiCRC.received_L == spiCRC.calculated_L) && (spiCRC.received_H == spiCRC.calculated_H))
	{
		#if SPI_DEBUG
		printf("%s\n","SPI CRC Check is OK");
		#endif
		comParams.frameSuccess++;
		if (comParams.frameSuccess == 0XFFFF) comParams.frameSuccess = 0;
	}
	
	else
	{
		#if SPI_DEBUG
		printf("%s\n","SPI CRC ERROR");
		#endif
    	return;
	}

    if (comParams.rxBuffer[SPI_UNIQUE_ID_INDEX] == SPI_UNIQUE_ID && 
    	                       comParams.rxBuffer[SPI_FUNCTION_ID_INDEX] == SPI_FUNCTION_ID)
    {
    	#if SPI_DEBUG
        printf("%s\n","Received SPI frame is OK");
    	#endif
    }

    else
    {
    	#if SPI_DEBUG
        printf("%s\n","Received SPI frame is wrong");
    	#endif
    	return;
    }

    #if FIRST_DWORD_BLOCK_SIZE
    /* First Cycle Read */
	for (bufIndexDW = 0; bufIndexDW < FIRST_DWORD_BLOCK_SIZE; bufIndexDW++)
	{
		dpm_mergeDWord(bufIndexDWLast++, &comParams.index, comParams.rxBuffer, comParams.recDataBufferDW);
	}
    #endif

    #if FIRST_FLOAT_BLOCK_SIZE
	for (bufIndexF = 0; bufIndexF < FIRST_FLOAT_BLOCK_SIZE; bufIndexF++)
	{
		dpm_mergeFloat(bufIndexFLast++, &comParams.index, comParams.rxBuffer, comParams.recDataBufferF);
	}
    #endif

    #if SECOND_FLOAT_BLOCK_SIZE
	/* Second Cycle Read */
	for (bufIndexF = 0; bufIndexF < SECOND_FLOAT_BLOCK_SIZE; bufIndexF++)
	{
		dpm_mergeFloat(bufIndexFLast++, &comParams.index, comParams.rxBuffer, comParams.recDataBufferF);
	}
    #endif

    #if SECOND_DWORD_BLOCK_SIZE
	for (bufIndexDW = 0; bufIndexDW < SECOND_DWORD_BLOCK_SIZE; bufIndexDW++)
	{
		dpm_mergeDWord(bufIndexDWLast++, &comParams.index, comParams.rxBuffer, comParams.recDataBufferDW);
	}
    #endif

    #if THIRTH_DWORD_BLOCK_SIZE
    /* Third  Cycle Read */
	for (bufIndexDW = 0; bufIndexDW < THIRTH_DWORD_BLOCK_SIZE; bufIndexDW++)
	{
		dpm_mergeDWord(bufIndexDWLast++, &comParams.index, comParams.rxBuffer, comParams.recDataBufferDW);
	}
	#endif

    #if THIRTH_FLOAT_BLOCK_SIZE
	for (bufIndexF = 0; bufIndexF < THIRTH_FLOAT_BLOCK_SIZE; bufIndexF++)
	{
		dpm_mergeFloat(bufIndexFLast++, &comParams.index, comParams.rxBuffer, comParams.recDataBufferF);
	}
    #endif

    #if FOURTH_DWORD_BLOCK_SIZE
    /* Fourth  Cycle Read */
	for (bufIndexDW = 0; bufIndexDW < FOURTH_DWORD_BLOCK_SIZE; bufIndexDW++)
	{
		dpm_mergeDWord(bufIndexDWLast++, &comParams.index, comParams.rxBuffer, comParams.recDataBufferDW);
	}
	#endif

    #if FOURTH_FLOAT_BLOCK_SIZE
	for (bufIndexF = 0; bufIndexF < FOURTH_FLOAT_BLOCK_SIZE; bufIndexF++)
	{
		dpm_mergeFloat(bufIndexFLast++, &comParams.index, comParams.rxBuffer, comParams.recDataBufferF);
	}
	#endif

}

static void spi_prepareTestData(void)
{
	uint32_t totalDWSize = FIRST_DWORD_BLOCK_SIZE + SECOND_DWORD_BLOCK_SIZE 
	                       + THIRTH_DWORD_BLOCK_SIZE + FOURTH_DWORD_BLOCK_SIZE;

	uint32_t totalFSize  = FIRST_FLOAT_BLOCK_SIZE + SECOND_FLOAT_BLOCK_SIZE
	                       + THIRTH_FLOAT_BLOCK_SIZE + FOURTH_FLOAT_BLOCK_SIZE;

	for (int i = 0; i < totalDWSize; i++)
	{
		comParams.pushDataBufferDW[i] = i;
	}

	for (int i = 0; i < totalFSize; i++)
	{
		comParams.pushDataBufferF[i] = 0.0f + (float)(i);
	}
	                                      
}

static void spi_crcCalculation(unsigned char *crcBuf, uint16_t crcLength)
{
   uint16_t crcTemp, crcRes;
   uint16_t i, j;
   crcRes = 0xFFFF;

    for (i = 0; i < crcLength; i++)
    {
      crcRes = crcRes ^ crcBuf[i];
      for ( j = 0; j < 8; j++)
      {
        crcTemp = crcRes & 0x0001;
        crcRes = crcRes >> 1;
        if (crcTemp)
        {
            crcRes = crcRes ^ 0xa001;
        }
      }
    }
    spiCRC.calculated = crcRes;
    spiCRC.calculated_L = (crcRes & 0XFF00) >> 8 ;
    spiCRC.calculated_H = (crcRes & 0X00FF);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	 if (hspi->Instance == hspi2.Instance)
	 {
	 	spi_deselectChip();
        comParams.txIndex  = 0;
		comParams.tranComp = FLAG_IS_ACTIVE;
	 }
		 
}	

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == hspi2.Instance)
	{
		spi_ReceiveCompCallBack();

		#if !MASTER_DEVICE
		HAL_SPI_Receive_IT(&hspi2, comParams.rxBuffer, READ_TOTAL_BUFFER_SIZE);
		#endif

		comParams.recCnt++;
	}
		 
}

static void spi_checkCommunication(void)
{
   #if !MASTER_DEVICE
   if (comParams.recTimeOut >= SPI_RESET_TIMEOUT)
   {
      NVIC_SystemReset();
   }
   #endif
}
