#include "states.h"
#include "nfbm.h"
#include "aux_functions.h"
#include "ios.h"
#include "time_constants.h"

void trippedState(){

	static long timeOutCounter=0;
	
	// Output Set
	
	DO.READY=0;
	DO.RUN=0;
	DO.IBF=1;
	
	// led indication
	
	DO.LD_IBF=1;
	DO.LD_READY=0;
	DO.LD_RUN=0;
	
	
		if(extTrip.all==0){
			
		current_state=ready;	
			
		if(faultData.bit.voltage_loss_trip){current_state=fault;}
		
		}
	

}
