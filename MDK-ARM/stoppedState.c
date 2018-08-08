#include "states.h"
#include "nfbm.h"
#include "aux_functions.h"
#include "ios.h"
#include "time_constants.h"

void stoppedState(){

	static long timeOutCounter=0;
	
	// Output Set
	
	DO.READY=0;
	DO.RUN=0;

	
	// led indication
	

	DO.LD_READY=0;
	DO.LD_RUN=0;
	
	
	if(on_delay(1,0,_3sec,&timeOutCounter)){
	
		current_state=ready;
		if(faultData.bit.general_fault){current_state=fault;}
	
	}


}


