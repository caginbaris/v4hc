#include "states.h"
#include "aux_functions.h"
#include "nfbm.h"
#include "ios.h"
#include "time_constants.h"

void idleState(){
	
	static long counter=0;
	static uint8_t idleFlag=0;
	
	// Output Set
	
	DO.READY=0;
	DO.RUN=1;
	DO.IBF=0;

	// led indication
	
	DO.LD_IBF=0;
	DO.LD_READY=0;
	DO.LD_RUN=1;
	
	status.Qbasic_flag=1;
	
	idleFlag=off_delay(DI.Q1_cb_pos,idleFlag,_1sec,&counter);
	
	if(!idleFlag){
		
		status.start_flag=0;
		status.Qbasic_flag=0;
		
		current_state=tripped;
		if(DI.start_stop){current_state=stopped;}
	
	}

}


