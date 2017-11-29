/**
  **********************************************************************************
  * @file    DataParserMerger.h
  * @author  Serbay Ozkan
  * @version V1.0.0
  * @date    13-November-2017
  * @brief   Data Parser and Merger Header file for float and double word variables
  **********************************************************************************
  */

#ifndef DATAPARSERMERGER_H
#define DATAPARSERMERGER_H

typedef union
{
	uint32_t dwValue; 
	float    fValue; 
}Typedef_typeCnv;


extern Typedef_typeCnv typeCnv;

void dpm_mergeFloat(uint32_t dataIndex, uint32_t* sourceIndex, unsigned char* source, float* destination);
void dpm_mergeDWord(uint32_t dataIndex, uint32_t* sourceIndex, unsigned char* source, uint32_t* destination);
void dpm_parseFloat(uint32_t dataIndex, uint32_t* destIndex, float* source, unsigned char* destination);
void dpm_parseDWord(uint32_t dataIndex, uint32_t* destIndex, uint32_t* source, unsigned char* destination);

#endif
