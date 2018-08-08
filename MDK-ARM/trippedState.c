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

	
		// led indication
	
		DO.LD_READY=0;
		DO.LD_RUN=0;
	
	
		if(!faultData.bit.ex_trip){
			
		current_state=ready;
			
		if(faultData.bit.general_fault){current_state=fault;}
		
		}
	

}
