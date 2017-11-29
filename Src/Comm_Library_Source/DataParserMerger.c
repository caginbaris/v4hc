/**
  ******************************************************************************
  * @file    DataParserMerger.c
  * @author  Serbay Ozkan
  * @version V1.0.0
  * @date    13-November-2017
  * @brief   Data Parser and Merger Source file for float and double word variables
  ******************************************************************************
  */

#include "stm32f7xx_hal.h"
#include "stdint.h"
#include "string.h"

/* User Includes */
#include "DataParserMerger.h"

Typedef_typeCnv typeCnv;

void dpm_mergeFloat(uint32_t dataIndex, uint32_t* sourceIndex, unsigned char* source, float* destination)
{
	typeCnv.dwValue  = (uint32_t)(source[(*sourceIndex)++] << 24);
	typeCnv.dwValue |= (uint32_t)(source[(*sourceIndex)++] << 16);
	typeCnv.dwValue |= (uint32_t)(source[(*sourceIndex)++] << 8);
	typeCnv.dwValue |= (uint32_t)(source[(*sourceIndex)++]);

	destination[dataIndex] = typeCnv.fValue; 
}

void dpm_mergeDWord(uint32_t dataIndex, uint32_t* sourceIndex, unsigned char* source, uint32_t* destination)
{
	destination[dataIndex]  = (uint32_t)(source[(*sourceIndex)++] << 24);
  	destination[dataIndex] |= (uint32_t)(source[(*sourceIndex)++] << 16);
  	destination[dataIndex] |= (uint32_t)(source[(*sourceIndex)++] << 8);
  	destination[dataIndex] |= (uint32_t)(source[(*sourceIndex)++]);  
}


void dpm_parseFloat(uint32_t dataIndex, uint32_t* destIndex, float* source, unsigned char* destination)
{
	typeCnv.fValue = source[dataIndex];

	destination[(*destIndex)++] = (0xFF000000 & (uint32_t)(typeCnv.dwValue)) >> 24;
	destination[(*destIndex)++] = (0x00FF0000 & (uint32_t)(typeCnv.dwValue)) >> 16;
	destination[(*destIndex)++] = (0x0000FF00 & (uint32_t)(typeCnv.dwValue)) >> 8;
	destination[(*destIndex)++] = (0x000000FF & (uint32_t)(typeCnv.dwValue));
}

void dpm_parseDWord(uint32_t dataIndex, uint32_t* destIndex, uint32_t* source, unsigned char* destination)
{
	destination[(*destIndex)++] = (0xFF000000 & (uint32_t)(source[dataIndex])) >> 24;
	destination[(*destIndex)++] = (0x00FF0000 & (uint32_t)(source[dataIndex])) >> 16;
	destination[(*destIndex)++] = (0x0000FF00 & (uint32_t)(source[dataIndex])) >> 8;
	destination[(*destIndex)++] = (0x000000FF & (uint32_t)(source[dataIndex])); 
}
