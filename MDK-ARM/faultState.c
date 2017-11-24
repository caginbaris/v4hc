
#include "states.h"
#include "nfbm.h"
#include "ios.h"


void faultState(){
	
	// led indication
	
	DO.LD_IBF=1;
	DO.LD_READY=0;
	DO.LD_RUN=0;
	
	
	
	
	if(!voltage_loss.trip){
		
		current_state=ready;
		if(extTrip.all){current_state=tripped;}
	
	}
	
	
	

}



