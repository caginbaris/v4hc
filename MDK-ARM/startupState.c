

#include "aux_functions.h"
#include "states.h"
#include "ios.h"
#include "time_constants.h"


void startupState(){
	
	static long timeOutCounter=0;
	static uint16_t blinkCounter=0;
	
	// Led Blink indication
	
	++blinkCounter;
	
	if(++blinkCounter==half_sec){
	
	blinkCounter=0;
			
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	




}



