/**
  ******************************************************************************
  * @file    SPI_Master.h
  * @author  Serbay Ozkan
  * @version V1.0.0
  * @date    28-October-2017
  * @brief   SPI Master Communication Application Layer Header File
  ******************************************************************************
  */

#include "stdint.h"
#include "CommConfig.h"

#ifndef SPI_MASTERSLAVE_H
#define SPI_MASTERSLAVE_H

#define SPI_UNIQUE_ID            1
#define SPI_FUNCTION_ID          16

#define SPI_UNIQUE_ID_INDEX      0
#define SPI_FUNCTION_ID_INDEX    1

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
	unsigned char txBuffer[READ_TOTAL_BUFFER_SIZE + 1];
	unsigned char rxBuffer[READ_TOTAL_BUFFER_SIZE + 1];
	uint32_t pushDataBufferDW[READ_TOTAL_REGISTER_SIZE + 1];
	float    pushDataBufferF[READ_TOTAL_REGISTER_SIZE + 1];
	uint32_t recDataBufferDW[READ_TOTAL_REGISTER_SIZE + 1];
	float    recDataBufferF[READ_TOTAL_REGISTER_SIZE + 1];
}Typedef_comParams;

typedef struct
{
  uint16_t calculated;
  uint16_t calculated_H;
  uint16_t calculated_L;
  uint16_t received;
  uint16_t received_H;
  uint16_t received_L;
}Typedef_spiCRC;

typedef union
{
	uint32_t dwValue; 
	float    fValue; 
}Typedef_typeConversion;

/* Typedef Extern Prototypes */
extern Typedef_comParams       comParams;

/* User Function Prototypes */

/* Library functions used in application layer */
void spi_sysTickCallApp(void);
void spi_runComApp(void);
void spi_initComApp(void);

/* Library Static Functions */
void spi_ReceiveTimeout(void);
void spi_RuntimeProcess(void);
void spi_frameProcess(void);
void spi_ReceiveCompCallBack(void);
void spi_pushAllData(void);
void spi_checkPushSendTime(void);
void spi_preparePushData(void);
void spi_prepareTestData(void);
void spi_crcCalculation(unsigned char *crcBuf, uint16_t crcLength);
void spi_pushAllDataCheck(void);
void spi_receiveInit(void);
void spi_prepareReceiveData(void);
void spi_checkCommunication(void);
void spi_selectChip(void);
void spi_deselectChip(void);
#endif
