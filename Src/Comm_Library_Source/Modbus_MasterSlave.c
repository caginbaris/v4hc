/**
  ******************************************************************************
  * @file    Modbus_MasterSlave.c
  * @author  Serbay Ozkan
  * @version V1.0.0
  * @date    09-November-2017
  * @brief   Modbus Master/SLave Communication Application Layer Source File
  ******************************************************************************
  */

#include "stm32f7xx_hal.h"
#include "spi.h"
#include "gpio.h"
#include "stdint.h"
#include "string.h"

/* User Includes */
#include "Modbus_MasterSlave.h"
#include "UART_MasterSlave.h"
#include "SPI_MasterSlave.h"
#include "DataParserMerger.h"
#include "CommConfig.h"

/* User Typedef Prototypes */
Typedef_comParams_modbus    comParams_modbus;
Typedef_mbTestParams        mbTestParams;

void modbus_preparePushData(uint8_t cycleReadNumber, unsigned char *pucRegBuffer)
{
	uint32_t bufIndexDW = 0;     /* Buffer Index for DWORD Values */
	uint32_t bufIndexF  = 0;     /* Buffer Index for Float Values */

    uint32_t bufIndexDWLast;     /* Buffer Last Index for DWORD Values */
	uint32_t bufIndexFLast;      /* Buffer Last Index for Float Values */

    if (cycleReadNumber == FIRST_CYCLE_READ)
    {
    	bufIndexDWLast = 0;
		bufIndexFLast  = 0;
        
        #if FIRST_DWORD_BLOCK_SIZE
    	/* First Cycle Read */
		for (bufIndexDW = 0; bufIndexDW < FIRST_DWORD_BLOCK_SIZE; bufIndexDW++)
		{
			dpm_parseDWord(bufIndexDWLast++, &comParams_modbus.txIndex, comParams.recDataBufferDW, pucRegBuffer);
		}
        #endif

        #if FIRST_FLOAT_BLOCK_SIZE
		for (bufIndexF = 0; bufIndexF < FIRST_FLOAT_BLOCK_SIZE; bufIndexF++)
		{
			dpm_parseFloat(bufIndexFLast++, &comParams_modbus.txIndex, comParams.recDataBufferF, pucRegBuffer);
		}
		#endif
    }
    
    if (cycleReadNumber == SECOND_CYCLE_READ)
    {
    	bufIndexDWLast = 0;
		bufIndexFLast  = FIRST_FLOAT_BLOCK_SIZE - 1;

        #if SECOND_FLOAT_BLOCK_SIZE
    	/* Second Cycle Read */
		for (bufIndexF = 0; bufIndexF < SECOND_FLOAT_BLOCK_SIZE; bufIndexF++)
		{
			dpm_parseFloat(bufIndexFLast++, &comParams_modbus.txIndex, comParams.recDataBufferF, pucRegBuffer);
		}
		#endif

        #if SECOND_DWORD_BLOCK_SIZE
		for (bufIndexDW = 0; bufIndexDW < SECOND_DWORD_BLOCK_SIZE; bufIndexDW++)
		{
			dpm_parseDWord(bufIndexDWLast++, &comParams_modbus.txIndex, comParams.recDataBufferDW, pucRegBuffer);
		}
		#endif
	    
    }

    if (cycleReadNumber == THIRTH_CYCLE_READ)
    {
    	bufIndexDWLast = FIRST_DWORD_BLOCK_SIZE;
		bufIndexFLast  = FIRST_FLOAT_BLOCK_SIZE + SECOND_FLOAT_BLOCK_SIZE - 1;

        #if THIRTH_DWORD_BLOCK_SIZE
    	/* Third  Cycle Read */
		for (bufIndexDW = 0; bufIndexDW < THIRTH_DWORD_BLOCK_SIZE; bufIndexDW++)
		{
			dpm_parseDWord(bufIndexDWLast++, &comParams_modbus.txIndex, comParams.recDataBufferDW, pucRegBuffer);
		}
        #endif

        #if THIRTH_FLOAT_BLOCK_SIZE
 		for (bufIndexF = 0; bufIndexF < THIRTH_FLOAT_BLOCK_SIZE; bufIndexF++)
		{
			dpm_parseFloat(bufIndexFLast++, &comParams_modbus.txIndex, comParams.recDataBufferF, pucRegBuffer);
		}
		#endif
	    
    } 
	
    if (cycleReadNumber == FOURTH_CYCLE_READ)
    {
    	bufIndexDWLast = FIRST_DWORD_BLOCK_SIZE + SECOND_DWORD_BLOCK_SIZE;
		bufIndexFLast  = FIRST_FLOAT_BLOCK_SIZE + SECOND_FLOAT_BLOCK_SIZE + THIRTH_FLOAT_BLOCK_SIZE - 1;
   
        #if FOURTH_DWORD_BLOCK_SIZE
    	/* Fourth  Cycle Read */
		for (bufIndexDW = 0; bufIndexDW < FOURTH_DWORD_BLOCK_SIZE; bufIndexDW++)
		{
			dpm_parseDWord(bufIndexDWLast++, &comParams_modbus.txIndex, comParams.recDataBufferDW, pucRegBuffer);
		}
        #endif

        #if FOURTH_FLOAT_BLOCK_SIZE
    	for (bufIndexF = 0; bufIndexF < FOURTH_FLOAT_BLOCK_SIZE; bufIndexF++)
		{
			dpm_parseFloat(bufIndexFLast++, &comParams_modbus.txIndex, comParams.recDataBufferF, pucRegBuffer);
		}
		#endif
    }
}

void modbus_prepareReceiveData(uint8_t cycleWriteNumber, unsigned char *pucRegBuffer)
{
	uint32_t bufIndexDW = 0;     /* Buffer Index for DWORD Values */
	uint32_t bufIndexF  = 0;     /* Buffer Index for Float Values */

    uint32_t bufIndexDWLast;     /* Buffer Last Index for DWORD Values */
	uint32_t bufIndexFLast;      /* Buffer Last Index for Float Values */

    if (cycleWriteNumber == FIRST_CYCLE_WRITE)
    {
    	bufIndexDWLast = 0;
		bufIndexFLast  = 0;

        #if WRITE_FIRST_DWORD_BLOCK_SIZE
    	/* First Cycle Write */
		for (bufIndexDW = 0; bufIndexDW < WRITE_FIRST_DWORD_BLOCK_SIZE; bufIndexDW++)
		{
			dpm_mergeDWord(bufIndexDWLast++, &comParams_modbus.index, pucRegBuffer, comParams_uart.pushDataBufferDW);
		}
		#endif

        #if WRITE_FIRST_FLOAT_BLOCK_SIZE
		for (bufIndexF = 0; bufIndexF < WRITE_FIRST_FLOAT_BLOCK_SIZE; bufIndexF++)
		{
			dpm_mergeFloat(bufIndexFLast++, &comParams_modbus.index, pucRegBuffer, comParams_uart.pushDataBufferF);
		}
		#endif
    }
    
    if (cycleWriteNumber == SECOND_CYCLE_WRITE)
    {
    	bufIndexDWLast = 0;
		bufIndexFLast  = WRITE_FIRST_FLOAT_BLOCK_SIZE;

    	/* Second Cycle Write */
        #if WRITE_SECOND_DWORD_BLOCK_SIZE
    	for (bufIndexDW = 0; bufIndexDW < WRITE_SECOND_DWORD_BLOCK_SIZE; bufIndexDW++)
		{
			dpm_mergeDWord(bufIndexDWLast++, &comParams_modbus.index, pucRegBuffer, comParams_uart.pushDataBufferDW);
		}
        #endif

        #if WRITE_SECOND_FLOAT_BLOCK_SIZE
		for (bufIndexF = 0; bufIndexF < WRITE_SECOND_FLOAT_BLOCK_SIZE; bufIndexF++)
		{
			dpm_mergeFloat(bufIndexFLast++, &comParams_modbus.index, pucRegBuffer, comParams_uart.pushDataBufferF);
		}
		#endif
    }
}
