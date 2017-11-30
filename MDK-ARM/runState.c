
#include "states.h"
#include "aux_functions.h"
#include "nfbm.h"
#include "ios.h"
#include "time_constants.h"

void runState(void){
	
	static long regulationCounter=0;
	// CB timeout eklenebilir
	
	// led indication
	
	DO.LD_IBF=0;
	DO.LD_READY=0;
	DO.LD_RUN=1;
	
	if(DI.Q1_cb_pos && status.start_flag==0 /*remaining entry!*/){
		
		status.start_flag=1;
	
	}
	
	
	if(status.start_flag==1 && status.regulation_enable==0){
	
		status.Qbasic_flag=1;
		
	}
	
	
	status.regulation_enable=on_delay(status.start_flag,status.regulation_enable,_10sec,&regulationCounter);
	
	
	if(status.regulation_enable){
		
		status.Qbasic_flag=0;
		
		/**actions on CB switching**/
	
	
	}
	
	
	
	//stop routine------------------------------
	
	if(DI.start_stop || extTrip.all){
	
	status.regulation_enable=0;
	status.Qbasic_flag=1;	
		
		
	current_state=idle;	
		
	
	}
	
	          
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


}


