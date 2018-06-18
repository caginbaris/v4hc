
#include "stm32f7xx_hal.h"
#include "nfbm.h"
#include "aux_functions.h"
#include "states.h"
#include "ios.h"
#include "time_constants.h"


void startupState(){
	
	static long timeOutCounter=0;
	static uint16_t blinkCounter=0;
	
	// Output Set
	
	DO.READY=0;
	DO.RUN=0;
	DO.IBF=1;
	DO.StartupCompleted=0;
	
	// Led Blink indication
	
	if(++blinkCounter==half_sec){
	
	blinkCounter=0;
		
	DO.LD_IBF^=1;
	DO.LD_READY^=1;
	DO.LD_RUN^=1;
		
	}
	
		
	if(on_delay(1,0,_5sec,&timeOutCounter)){
	
	current_state=ready;		
	if(faultData.bit.ex_trip){current_state=tripped;}
	if(faultData.bit.voltage_loss_trip){current_state=fault;}
	
	DO.LD_IBF=1;
	DO.LD_READY=0;
	DO.LD_RUN=0;
	
	
	
	}
   		
}



