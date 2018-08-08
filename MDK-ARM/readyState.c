
#include "states.h"
#include "modes.h"
#include "nfbm.h"
#include "ios.h"


void readyState(void){
	
	// Output Set
	
	DO.READY=1;
	DO.RUN=0;

	
	// led indication
	
	DO.LD_READY=1;
	DO.LD_RUN=0;
	
	
	status.MV_ready_flag=DI.Q10_ds_pos; //cau can be omitted
	
	if(DI.start_stop & status.MV_ready_flag & current_mode!=firingTest){current_state=run;}
	if(faultData.bit.ex_trip){current_state=tripped;}
	if(faultData.bit.voltage_loss_trip){current_state=fault;}


}


