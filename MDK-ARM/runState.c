
#include "states.h"
#include "modes.h"
#include "aux_functions.h"
#include "nfbm.h"
#include "ios.h"
#include "time_constants.h"

union cb_operations cb_pos={0};

void runState(void){
	
	static long regulationCounter=0;
	static long start_count=0;
	static uint8_t start_stop=0;
	
	static uint8_t cb_op=0,cb_op_back=0,cb_op_flag=0;
	static long cb_opp_counter=0;
	
	// CB timeout eklenebilir
	
	// Output Set
	
	DO.READY=0;
	DO.RUN=1;

	
	// led indication
	
	DO.LD_READY=0;
	DO.LD_RUN=1;
	
	if(	(DI.Q1_cb_pos) & 
			(!status.start_flag) /*remaining entry!*/){
		
		status.start_flag=1;
	
	}
	
	
	if(status.start_flag & 
		(current_mode==openLoop | current_mode==closedLoop)&
		(!status.Qbasic_flag) &
		(!status.regulation_enable)
	){
	
		status.Qbasic_flag=1;
		
	}
	
	
	status.regulation_enable=on_delay(status.start_flag,status.regulation_enable,_12sec,&regulationCounter);
	

	
	if(status.regulation_enable){
		
		status.Qbasic_flag=0;
		
		/*sebeke güç kontrolü sonrasinda DO.startup set, +-5 MVAR, for 2sec*/
		
		DO.StartupCompleted=1;
		
		/**actions on CB switching**/
		
		cb_op_back=cb_op;
		cb_op=cb_pos.all;
		
		if(cb_op!=cb_op_back){cb_op_flag=1;}
		
		if(cb_op_flag){
			
		
		status.Qbasic_flag=1;	
		
		cb_op_flag=off_delay(0,cb_op_flag,_3sec,&cb_opp_counter);
			
		if(!cb_op_flag){status.Qbasic_flag=0;}
			
		}
	
	}
	
	
	
	//stop routine------------------------------
	
	start_stop=off_delay(DI.start_stop,start_stop,_1period,&start_count);
	
	if(start_stop==0 || faultData.bit.ex_trip==1  ||  DI.Q1_open_ctb==0){
		
	status.regulation_enable=0;
	DO.StartupCompleted=0;
	cb_op_flag=0;		

	current_state=idle;	
		
	
	}
	
}


