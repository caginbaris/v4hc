
#include "SPI_MasterSlave.h"
#include "UART_MasterSlave.h"
#include "ios.h"

void pushDataToMaster(void){


	comParams.pushDataBufferDW[0]=0;
	comParams.pushDataBufferDW[1]=0;
	comParams.pushDataBufferDW[2]=uDI.all;
	comParams.pushDataBufferDW[2]=uDO.all;



}