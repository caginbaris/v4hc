
#include "states.h"
#include "aux_functions.h"
#include "nfbm.h"
#include "ios.h"

void runState(void){
	
	// led indication
	
	DO.READY=0;
	DO.RUN=1;
	
	if(DI.Q1_cb_pos && status.start_flag==0 /*remaining entry!*/){
		
		status.start_flag=1;
	
	}
	
	
	if(status.start_flag==1 && status.regulation_enable==0){
	
		status.Qbasic_mode=1;
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


}


