#include "nfbm.h"
#include "aux_functions.h"
#include "time_constants.h"
#include "ios.h"

struct external_fault extTrip={0};


void tripRoutines(void){


	if(!(DI.SVC_TRIP & DI.Q1_trip_ctb)){
	
	extTrip.pick_up=1;
		
	}else{
	
	extTrip.pick_up=0;
	
	}
	
	extTrip.all=off_delay(extTrip.pick_up,extTrip.all,half_sec,&extTrip.counter);
	
}