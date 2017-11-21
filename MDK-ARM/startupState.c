
#include "stm32f7xx_hal.h"
#include "nfbm.h"
#include "aux_functions.h"
#include "states.h"
#include "ios.h"
#include "time_constants.h"


void startupState(){
	
	static long timeOutCounter=0;
	static uint16_t blinkCounter=0;
	
	// Led Blink indication
	
	if(++blinkCounter==half_sec){
	
	blinkCounter=0;
		
	HAL_GPIO_TogglePin(LD_ALARM_GPIO_Port,LD_ALARM_Pin);
	HAL_GPIO_TogglePin(LD_TRIP_GPIO_Port,LD_TRIP_Pin);
	HAL_GPIO_TogglePin(LD_RUN_GPIO_Port,LD_RUN_Pin);			
		
	}
	
		
	if(on_delay(1,0,_3sec,&timeOutCounter)){
		
	if(extTrip.all){current_state=tripped;}
	if(voltage_loss.trip){current_state=fault;}
	if(current_state==startup){current_state=ready;}
	
	}
   		
}



