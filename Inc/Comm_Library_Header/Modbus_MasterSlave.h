/**
  ******************************************************************************
  * @file    Modbus_MasterSlave.h
  * @author  Serbay Ozkan
  * @version V1.0.0
  * @date    09-November-2017
  * @brief   Modbus Master/SLave Communication Application Layer Header File
  ******************************************************************************
  */

#ifndef MODBUS_MASTERSLAVE_H
#define MODBUS_MASTERSLAVE_H


#define FIRST_CYCLE_READ                      1
#define SECOND_CYCLE_READ                     2
#define THIRTH_CYCLE_READ                     3 
#define FOURTH_CYCLE_READ                     4
 
#define FIRST_CYCLE_STARTING_ADRESS           2
#define SECOND_CYCLE_STARTING_ADRESS          126
#define THIRTH_CYCLE_STARTING_ADRESS          252
#define FOURTH_CYCLE_STARTING_ADRESS          378

#define FIRST_CYCLE_WRITE                     1
#define SECOND_CYCLE_WRITE                    2

#define FIRST_CYCLE_WRITE_STARTING_ADRESS     512
#define SECOND_CYCLE_WRITE_STARTING_ADRESS    642

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
	unsigned char txBuffer[1024];
	unsigned char rxBuffer[1024];
	uint32_t pushDataBufferDW[512];
	float    pushDataBufferF[512];
	uint32_t recDataBufferDW[512];
	float    recDataBufferF[512];
}Typedef_comParams_modbus;

typedef struct 
{
	uint32_t usNRegs;
	uint32_t startAdress;
}Typedef_mbTestParams;

extern Typedef_mbTestParams        mbTestParams;
extern Typedef_comParams_modbus    comParams_modbus;

void modbus_preparePushData(uint8_t cycleReadNumber, unsigned char *pucRegBuffer);
void modbus_prepareReceiveData(uint8_t cycleWriteNumber, unsigned char *pucRegBuffer);

#endif
