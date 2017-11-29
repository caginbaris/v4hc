/**
  ******************************************************************************
  * @file    UART_MasterSlave.h
  * @author  Serbay Ozkan
  * @version V1.0.0
  * @date    06-November-2017
  * @brief   UART Master/SLave Communication Application Layer Header File
  ******************************************************************************
  */

#include "stdint.h"
#include "CommConfig.h"

#ifndef UART_MASTERSLAVE_H
#define UART_MASTERSLAVE_H

#define UART_UNIQUE_ID            1
#define UART_FUNCTION_ID          16

#define UART_UNIQUE_ID_INDEX      0
#define UART_FUNCTION_ID_INDEX    1

typedef struct
{
  	uint8_t  recComp;
  	uint8_t  tranComp;
  	uint8_t  recFlag;
  	uint8_t  pushFlag;
  	uint8_t  transmitComp;
  	uint8_t  receivedData;
  	uint16_t recTimeOut;
  	uint32_t frameSuccess;
	uint32_t rxIndex;
	uint32_t txIndex;
	uint32_t recCnt;
	uint32_t index;
	uint32_t pushDataTimerCnt;
  	uint32_t recSize;
 	uint32_t sendSize;
	unsigned char txBuffer[WRITE_TOTAL_BUFFER_SIZE + 1];
	unsigned char rxBuffer[WRITE_TOTAL_BUFFER_SIZE + 1];
	uint32_t pushDataBufferDW[WRITE_TOTAL_REGISTER_SIZE + 1];
	float    pushDataBufferF[WRITE_TOTAL_REGISTER_SIZE + 1];
	uint32_t recDataBufferDW[WRITE_TOTAL_REGISTER_SIZE + 1];
	float    recDataBufferF[WRITE_TOTAL_REGISTER_SIZE + 1];
}Typedef_comParams_uart;

typedef struct
{
  uint16_t calculated;
  uint16_t calculated_H;
  uint16_t calculated_L;
  uint16_t received;
  uint16_t received_H;
  uint16_t received_L;
}Typedef_uartCRC;

extern Typedef_comParams_uart  comParams_uart;


/* User Function Prototypes */

/* Library functions used in application layer */
void uart_runComApp(void);
void uart_initComApp(void);
void uart_sysTickCallApp(void);

/* Library Static Functions */
void uart_ReceiveTimeout(void);
void uart_RuntimeProcess(void);
void uart_frameProcess(void);
void uart_ReceiveCompCallBack(void);
void uart_pushAllData(void);
void uart_checkPushSendTime(void);
void uart_preparePushData(void);
void uart_prepareTestData(void);
void uart_crcCalculation(unsigned char *crcBuf, uint16_t crcLength);
void uart_pushAllDataCheck(void);
void uart_receiveInit(void);
void uart_prepareReceiveData(void);
void uart_checkCommunication(void);

#endif
