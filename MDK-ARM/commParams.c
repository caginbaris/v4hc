
#include "SPI_MasterSlave.h"
#include "UART_MasterSlave.h"
#include "ios.h"
#include "nfbm.h"

#include "commReceivedParameters.h"


union mode_flags receivedModeFlags;

struct ref_parameters ref_param_received;
struct ref_parameters ref_set;

void pushDataToMaster(void){


	comParams.pushDataBufferDW[0]=0;
	comParams.pushDataBufferDW[1]=0;
	comParams.pushDataBufferDW[2]=uDI.all;
	comParams.pushDataBufferDW[2]=uDO.all;



}


void pullDataFromMaster(void){
	
	
	receivedModeFlags.all=comParams.pushDataBufferDW[0];
	
	



}