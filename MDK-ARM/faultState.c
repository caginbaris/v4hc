
#include "states.h"
#include "nfbm.h"
#include "ios.h"


void faultState(){
	
	// led indication
	
	DO.READY=0;
	DO.RUN=0;
	
	
	if(!voltage_loss.trip){
		
		
		if(extTrip.all){current_state=tripped;}
		if(current_state==fault){current_state=ready;}
	
	
	}
	
	
	

}



