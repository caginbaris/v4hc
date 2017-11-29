#include "stm32f7xx_hal.h"
#include "spi.h"
#include "gpio.h"
#include "stdint.h"
#include "usart.h"

/* User Includes */
#include "UART_MasterSlave.h"
#include "DataParserMerger.h"
#include "CommConfig.h"

/* User Typedef Prototypes */
Typedef_comParams_uart  comParams_uart;
Typedef_uartCRC         uartCRC;

/* This function should be called in super loop */
void uart_runComApp(void)
{
  uart_pushAllDataCheck();
  uart_RuntimeProcess();
  uart_checkCommunication();
}

/* This function should be called in 1ms timer */
void uart_sysTickCallApp(void)
{
    uart_ReceiveTimeout();
    uart_checkPushSendTime();
}

/* This function should be called before super loop */
void uart_initComApp(void)
{
  uart_receiveInit();
}

static void uart_ReceiveCompCallBack(void)
{
    comParams_uart.rxBuffer[comParams_uart.rxIndex++] = comParams_uart.receivedData;
    comParams_uart.recTimeOut = 0;
    comParams_uart.recFlag = FLAG_IS_ACTIVE;
    comParams_uart.transmitComp = FLAG_IS_INACTIVE;
}

static void uart_ReceiveTimeout(void)
{
  comParams_uart.recTimeOut++;
  if (comParams_uart.recFlag == FLAG_IS_ACTIVE && comParams_uart.recTimeOut == RECEIVE_TIMEOUT)
  {
    comParams_uart.recComp = FLAG_IS_ACTIVE;
    comParams_uart.recTimeOut = 0;
  }

  if (comParams_uart.recTimeOut >= 0xFFFF)
  {
    comParams_uart.recTimeOut = 0;
  }
}

static void uart_RuntimeProcess(void)
{
   if(comParams_uart.recComp == 1 && comParams_uart.recFlag == FLAG_IS_ACTIVE)
   {
      uart_frameProcess();
      comParams_uart.recSize = comParams_uart.rxIndex;
      comParams_uart.rxIndex = 0;
      comParams_uart.recComp = FLAG_IS_INACTIVE;
      comParams_uart.recFlag = FLAG_IS_INACTIVE;
   }
}

static void uart_frameProcess(void)
{
  uart_prepareReceiveData();
}

static void uart_pushAllData(void)
{
  // uart_prepareTestData();
  uart_preparePushData();
  comParams_uart.sendSize = comParams_uart.txIndex;
  HAL_UART_Transmit_IT(&huart2, comParams_uart.txBuffer, comParams_uart.txIndex);
}

static void uart_pushAllDataCheck(void)
{
  #if !MASTER_DEVICE
  if (comParams_uart.pushFlag == FLAG_IS_ACTIVE)
  {
    uart_pushAllData();
    comParams_uart.pushFlag = FLAG_IS_INACTIVE;
  }
  #endif
}

static void uart_checkPushSendTime(void)
{
  comParams_uart.pushDataTimerCnt++;
  if (comParams_uart.pushDataTimerCnt >= UART_PUSH_ALL_DATA_TIME)
  {
    comParams_uart.pushFlag = FLAG_IS_ACTIVE;
    comParams_uart.pushDataTimerCnt = 0;
  }
}

static void uart_receiveInit(void)
{
  #if MASTER_DEVICE
  HAL_UART_Receive_IT(&huart2, &comParams_uart.receivedData, 1);
  #endif
}

static void uart_preparePushData(void)
{
  uint32_t bufIndexDW = 0; /* Buffer Index for DWORD Values */
  uint32_t bufIndexF  = 0; /* Buffer Index for Float Values */
    
  uint32_t bufIndexDWLast = 0; /* Buffer Last Index for DWORD Values */
  uint32_t bufIndexFLast  = 0; /* Buffer Last Index for Float Values */

  comParams_uart.txBuffer[comParams_uart.txIndex++] = UART_UNIQUE_ID;
  comParams_uart.txBuffer[comParams_uart.txIndex++] = UART_FUNCTION_ID;

  #if WRITE_FIRST_DWORD_BLOCK_SIZE
  /* First Cycle Read */
  for (bufIndexDW = 0; bufIndexDW < WRITE_FIRST_DWORD_BLOCK_SIZE; bufIndexDW++)
  {
    dpm_parseDWord(bufIndexDWLast++, &comParams_uart.txIndex, comParams_uart.pushDataBufferDW, comParams_uart.txBuffer);
  }
  #endif

  #if WRITE_FIRST_FLOAT_BLOCK_SIZE
  for (bufIndexF = 0; bufIndexF < WRITE_FIRST_FLOAT_BLOCK_SIZE; bufIndexF++)
  {
    dpm_parseFloat(bufIndexFLast++, &comParams_uart.txIndex, comParams_uart.pushDataBufferF, comParams_uart.txBuffer);
  }
  #endif

  #if WRITE_SECOND_FLOAT_BLOCK_SIZE
  /* Second Cycle Read */
  for (bufIndexF = 0; bufIndexF < WRITE_SECOND_FLOAT_BLOCK_SIZE; bufIndexF++)
  {
    dpm_parseFloat(bufIndexFLast++, &comParams_uart.txIndex, comParams_uart.pushDataBufferF, comParams_uart.txBuffer);
  }
  #endif

  uart_crcCalculation(comParams_uart.txBuffer, comParams_uart.txIndex);

  comParams_uart.txBuffer[comParams_uart.txIndex++] = uartCRC.calculated_H;
  comParams_uart.txBuffer[comParams_uart.txIndex++] = uartCRC.calculated_L;
}

static void uart_prepareReceiveData(void)
{
  uint32_t bufIndexDW = 0; /* Buffer Index for DWORD Values */
  uint32_t bufIndexF  = 0; /* Buffer Index for Float Values */
    
  uint32_t bufIndexDWLast = 0; /* Buffer Last Index for DWORD Values */
  uint32_t bufIndexFLast  = 0; /* Buffer Last Index for Float Values */

  comParams_uart.index = 2;

  uart_crcCalculation(comParams_uart.rxBuffer, (comParams_uart.recSize-2));

	uartCRC.received_H = comParams_uart.rxBuffer[comParams_uart.recSize - 2];
	uartCRC.received_L = comParams_uart.rxBuffer[comParams_uart.recSize - 1];
	
	if ((uartCRC.received_L == uartCRC.calculated_L) && (uartCRC.received_H == uartCRC.calculated_H))
  {
		#if UART_DEBUG
		printf("%s\n","UART CRC Check is OK");
		#endif
  }
	
	else
	{
		#if UART_DEBUG
		printf("%s\n","UART CRC ERROR");
		#endif
    return;
	}
	
  if (comParams_uart.rxBuffer[UART_UNIQUE_ID_INDEX] == UART_UNIQUE_ID && 
                           comParams_uart.rxBuffer[UART_FUNCTION_ID_INDEX] == UART_FUNCTION_ID)
  {
    comParams_uart.frameSuccess++;
  }

  else
  {
    #if UART_DEBUG
    printf("%s\n","Received UART frame is wrong");
    #endif
    return;
  }

  #if WRITE_FIRST_DWORD_BLOCK_SIZE
  /* First Cycle Read */
  for (bufIndexDW = 0; bufIndexDW < WRITE_FIRST_DWORD_BLOCK_SIZE; bufIndexDW++)
  {
    dpm_mergeDWord(bufIndexDWLast++, &comParams_uart.index, comParams_uart.rxBuffer, comParams_uart.recDataBufferDW);
  }
  #endif

  #if WRITE_FIRST_FLOAT_BLOCK_SIZE
  for (bufIndexF = 0; bufIndexF < WRITE_FIRST_FLOAT_BLOCK_SIZE; bufIndexF++)
  {
    dpm_mergeFloat(bufIndexFLast++, &comParams_uart.index, comParams_uart.rxBuffer, comParams_uart.recDataBufferF);
  }
  #endif

  #if WRITE_SECOND_FLOAT_BLOCK_SIZE
  /* Second Cycle Read */
  for (bufIndexF = 0; bufIndexF < WRITE_SECOND_FLOAT_BLOCK_SIZE; bufIndexF++)
  {
    dpm_mergeFloat(bufIndexFLast++, &comParams_uart.index, comParams_uart.rxBuffer, comParams_uart.recDataBufferF);
  }
  #endif

}

static void uart_prepareTestData(void)
{
  uint32_t totalDWSize = WRITE_FIRST_DWORD_BLOCK_SIZE;

  uint32_t totalFSize  = WRITE_FIRST_FLOAT_BLOCK_SIZE + WRITE_SECOND_FLOAT_BLOCK_SIZE;

  for (int i = 0; i < totalDWSize; i++)
  {
    comParams_uart.pushDataBufferDW[i] = i;
  }

  for (int i = 0; i < totalFSize; i++)
  {
    comParams_uart.pushDataBufferF[i] = 0.0f + (float)(i);
  }
                                        
}

static void uart_crcCalculation(unsigned char *crcBuf, uint16_t crcLength)
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
    uartCRC.calculated = crcRes;
    uartCRC.calculated_L = (crcRes & 0XFF00) >> 8 ;
    uartCRC.calculated_H = (crcRes & 0X00FF);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
   if (huart->Instance == USART2)
   {
    comParams_uart.txIndex  = 0;
    comParams_uart.tranComp = FLAG_IS_ACTIVE;
   }
     
} 

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
   if (huart->Instance == USART2)
   {
      uart_ReceiveCompCallBack();

      #if MASTER_DEVICE
      HAL_UART_Receive_IT(&huart2, &comParams_uart.receivedData, 1);
      #endif
      comParams_uart.recCnt++;
      if (comParams_uart.recCnt == 0xFFFF) comParams_uart.recCnt = 0;
   }
     
}

static void uart_checkCommunication(void)
{
   #if MASTER_DEVICE
   if (comParams_uart.recTimeOut >= UART_RESET_TIMEOUT)
   {
      MX_USART2_UART_Init();
      HAL_UART_Receive_IT(&huart2, &comParams_uart.receivedData, 1);
      comParams_uart.recTimeOut = 0;

   }
   #endif
}
