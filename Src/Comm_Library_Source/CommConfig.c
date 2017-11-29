/**
  ******************************************************************************
  * @file    CommConfig.c
  * @author  Serbay Ozkan
  * @version V1.0.0
  * @date    13-November-2017
  * @brief   Configuration Source File for communication layer
  ******************************************************************************
  */
#include "CommConfig.h"

//-------- <<< Use Configuration Wizard in Context Menu>>> -----------------
//
// <h> General Configuration Params
// =======================

//   <o> Master/Slave Device Selection <0-1>
//   <i> Define 1 for Master Device, 0 for Slave Device
//   <i> Default: 0
#define MASTER_DEVICE     1

//   <o> Receive TimeOut [ms] 
//   <i> Defines specific time for receive timeout operation in all comm. app. layer
//   <i> Default: 100
#define RECEIVE_TIMEOUT     100

// </h>

// <h> Read Operation
// ======================================

//   <o> Cycle number
//   <i> Defines modbus master request cycle for reading operation
//   <i> Default: 4
#define READ_CYCLE_NUMBER 4

//   <o> Cycle Total Block Size 
//   <i> Defines modbus master request block size register number for reading operation
//   <i> Default: 62
#define READ_BLOCK_SIZE 62

//   <o> First Cycle DW Block Size
//   <i> Defines modbus first DW block size 
//   <i> Default: 14
#define FIRST_DWORD_BLOCK_SIZE 14

//   <o> First Cycle Float Block Size
//   <i> Defines modbus first float block size 
//   <i> Default: 48
#define FIRST_FLOAT_BLOCK_SIZE 48

//   <o> Second Cycle DW Block Size
//   <i> Defines modbus second DW block size 
//   <i> Default: 0
#define SECOND_DWORD_BLOCK_SIZE 0

//   <o> Second Cycle Float Block Size
//   <i> Defines modbus second Float block size 
//   <i> Default: 62
#define SECOND_FLOAT_BLOCK_SIZE 62

//   <o> Thirth Cycle DW Block Size
//   <i> Defines modbus thirth DW block size 
//   <i> Default: 5
#define THIRTH_DWORD_BLOCK_SIZE 5

//   <o> Thirth Cycle Float Block Size
//   <i> Defines modbus thirth float block size 
//   <i> Default: 57
#define THIRTH_FLOAT_BLOCK_SIZE 57

//   <o> Fourth Cycle DW Block Size
//   <i> Defines modbus fourth DW block size 
//   <i> Default: 0
#define FOURTH_DWORD_BLOCK_SIZE 0

//   <o> Fourth Cycle Float Block Size
//   <i> Defines modbus fourth float block size 
//   <i> Default: 57
#define FOURTH_FLOAT_BLOCK_SIZE 62

// </h>

// <h> Write Operation
// =======================

//   <o> Cycle number
//   <i> Defines modbus master write cycle for writing operation
//   <i> Default: 2
#define WRITE_CYCLE_NUMBER 2

//   <o> Cycle Total Block Size 
//   <i> Defines modbus master write block size register number for writing operation
//   <i> Default: 61
#define WRITE_BLOCK_SIZE 61

//   <o> First Cycle DW Block Size
//   <i> Defines modbus first DW block size 
//   <i> Default: 5
#define WRITE_FIRST_DWORD_BLOCK_SIZE 5

//   <o> First Cycle Float Block Size
//   <i> Defines modbus first float block size 
//   <i> Default: 56
#define WRITE_FIRST_FLOAT_BLOCK_SIZE 56

//   <o> Second Cycle DW Block Size
//   <i> Defines modbus second DW block size 
//   <i> Default: 0
#define WRITE_SECOND_DWORD_BLOCK_SIZE 0

//   <o> Second Cycle Float Block Size
//   <i> Defines modbus second float block size 
//   <i> Default: 61
#define WRITE_SECOND_FLOAT_BLOCK_SIZE 61

// </h>

// <h> UART (Slave  -> Master)
// =======================

//   <o> UART Debug Option Selection <0-1>
//   <i> Define 1 to Open Debug Output, 0 to Close Debug Output
//   <i> Default: 0
#define UART_DEBUG     0

//   <o> UART Periodic Push Time [ms] 
//   <i> Defines specific time for pushing bulk data from Slave to Master
//   <i> This parameter is valid only when device is in Slave Mode
//   <i> Default: 800
#define UART_PUSH_ALL_DATA_TIME     800

//   <o> UART Reset TimeOut [ms] 
//   <i> Defines specific time for resetting UART interface when no data comes from slave
//   <i> This parameter is valid only when device is in Master Mode
//   <i> Default: 5000
#define UART_RESET_TIMEOUT          5000

// </h>

// <h> SPI     (Master -> Slave)
// =======================

//   <o> SPI Debug Option Selection <0-1>
//   <i> Define 1 to Open Debug Output, 0 to Close Debug Output
//   <i> Default: 0
#define SPI_DEBUG     0

//   <o> UART Periodic Push Time [ms] 
//   <i> Defines specific time for pushing bulk data from Slave to Master
//   <i> This parameter is valid only when device is in Slave Mode
//   <i> Default: 500
#define SPI_PUSH_ALL_DATA_TIME     500

//   <o> UART Reset TimeOut [ms] 
//   <i> Defines specific time for resetting UART interface when no data comes from slave
//   <i> This parameter is valid only when device is in Master Mode
//   <i> Default: 5000
#define SPI_RESET_TIMEOUT          5000

// </h>


//------------- <<< end of configuration section>>> -----------------------



