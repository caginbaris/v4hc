#include "nfbm.h"
#include "aux_functions.h"
#include "time_constants.h"
#include "ios.h"


static long counter=0;

void tripRoutines(void){


	if(!(DI.SVC_TRIP & DI.Q1_trip_ctb)){
	
	faultData.bit.ex_pick=1;
		
	}else{
	
	faultData.bit.ex_pick=0;
	
	}
	
	faultData.bit.ex_trip=off_delay(faultData.bit.ex_pick,faultData.bit.ex_trip,half_sec,&counter);
	
}