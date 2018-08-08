
#include "states.h"
#include "nfbm.h"
#include "ios.h"


void faultState(){
	
	// Output Set
	
	DO.READY=0;
	DO.RUN=0;

	
	
	// led indication
	

	DO.LD_READY=0;
	DO.LD_RUN=0;
	
	
	
	
	if(!faultData.bit.general_fault){
		
		current_state=ready;
		if(faultData.bit.ex_trip){current_state=tripped;}
	
	}
	
	
	

}



