
#include "states.h"
#include "nfbm.h"
#include "ios.h"


void readyState(void){
	
	// led indication
	
	DO.READY=1;
	DO.RUN=0;
	
	if(DI.start_stop && status.MV_Ready){current_state=run;}
	if(extTrip.all){current_state=tripped;}
	if(voltage_loss.trip){current_state=fault;}


}

