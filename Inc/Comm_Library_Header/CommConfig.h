/**
  ******************************************************************************
  * @file    CommConfig.h
  * @author  Serbay Ozkan
  * @version V1.0.0
  * @date    13-November-2017
  * @brief   Comm. header file for configuration of communication params 
  ******************************************************************************
  */

#ifndef COMMCONFIG_H
#define COMMCONFIG_H
#include "CommConfig.c"

#define FLAG_IS_ACTIVE                 1
#define FLAG_IS_INACTIVE               0

#define READ_TOTAL_REGISTER_SIZE       (READ_CYCLE_NUMBER * READ_BLOCK_SIZE)

/* (4 * CYCLE_NO * CYCLE_BLOCK_SIZE)  + ID (1 Byte) + FUNC. ID (1 Byte) + CRC (2 Bytes) */
#define READ_TOTAL_BUFFER_SIZE         ((4 * READ_TOTAL_REGISTER_SIZE) + 4)

#define WRITE_TOTAL_REGISTER_SIZE      (WRITE_CYCLE_NUMBER * WRITE_BLOCK_SIZE)

/* (4 * CYCLE_NO * CYCLE_BLOCK_SIZE)  + ID (1 Byte) + FUNC. ID (1 Byte) + CRC (2 Bytes) */
#define WRITE_TOTAL_BUFFER_SIZE        ((4 * WRITE_TOTAL_REGISTER_SIZE) + 4)

#endif


