#include "states.h"
#include "nfbm.h"
#include "aux_functions.h"
#include "ios.h"
#include "time_constants.h"

void trippedState(){

	static long timeOutCounter=0;
	
	// led indication
	
	DO.READY=0;
	DO.RUN=0;
	
	
		if(extTrip.all==0){
			
		current_state=ready;	
		if(voltage_loss.trip){current_state=fault;}
		
		}
	

}
