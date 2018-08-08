#include "nfbm.h"
#include "aux_functions.h"
#include "time_constants.h"
#include "ios.h"




void tripRoutines(void){
	
	static long counter=0;
	static uint8_t temp=0;	

	if(!(DI.SVC_TRIP & DI.Q1_trip_ctb)){
	
	faultData.bit.ex_pick=1;
		
	}else{
	
	faultData.bit.ex_pick=0;
	
	}
	
	temp=off_delay(faultData.bit.ex_pick,temp,half_sec,&counter);
	
	if(temp){faultData.bit.ex_trip=1;}
	
}