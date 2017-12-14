
#include "states.h"
#include "modes.h"
#include "aux_functions.h"
#include "nfbm.h"
#include "ios.h"
#include "time_constants.h"

union cb_operations cb_pos={0};

void runState(void){
	
	static long regulationCounter=0;
	
	static uint8_t cb_op=0,cb_op_back=0,cb_op_flag=0;
	long cb_opp_counter=0;
	
	// CB timeout eklenebilir
	
	// Output Set
	
	DO.READY=0;
	DO.RUN=1;
	DO.IBF=0;
	
	// led indication
	
	DO.LD_IBF=0;
	DO.LD_READY=0;
	DO.LD_RUN=1;
	
	if((DI.Q1_cb_pos |DI.CB_Operation_Qbasic) & (!status.start_flag) & (current_mode!=hf) /*remaining entry!*/){
		
		status.start_flag=1;
	
	}
	
	
	if(status.start_flag & !status.regulation_enable){
	
		status.Qbasic_flag=1;
		
	}
	
	
	status.regulation_enable=on_delay(status.start_flag,status.regulation_enable,_10sec,&regulationCounter);
	
	
	if(status.regulation_enable){
		
		status.Qbasic_flag=0;
		
		DO.StartupCompleted=1;
		
		/**actions on CB switching**/
		
		cb_op_back=cb_op;
		cb_op=cb_pos.all;
		
		if(cb_op!=cb_op_back){cb_op_flag=1;}
		
		if(cb_op_flag){
			
		status.Qbasic_flag=1;	
		
		cb_op_flag=off_delay(0,cb_op_flag,_2sec,&cb_opp_counter);
			
		if(!cb_op_flag){status.Qbasic_flag=0;}
			
		}
	
	}
	
	
	
	//stop routine------------------------------
	
	if(DI.start_stop || extTrip.all){
	
	status.regulation_enable=0;

	DO.StartupCompleted=0;	

	current_state=idle;	
		
	
	}
	
	          
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


}


