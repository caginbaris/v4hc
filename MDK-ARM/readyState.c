
#include "states.h"
#include "nfbm.h"
#include "ios.h"


void readyState(void){
	
	// Output Set
	
	DO.READY=1;
	DO.RUN=0;
	DO.IBF=0;
	
	// led indication
	
	DO.LD_IBF=0;
	DO.LD_READY=1;
	DO.LD_RUN=0;
	
	
	status.MV_ready_flag=DI.Q10_ds_pos;
	
	if(DI.start_stop && status.MV_ready_flag){current_state=run;}
	if(extTrip.all){current_state=tripped;}
	if(voltage_loss.trip){current_state=fault;}


}


