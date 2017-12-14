
#include "nfbm.h"
#include "states.h"
#include "modes.h"
#include "commReceivedParameters.h"

union mode_flags runningModeFlags;

void mode_selection(){
	
	
	if(status.configData_flag){
	
	  if(current_mode==inter){
		
		runningModeFlags.all=receivedModeFlags.all;
		ref_set=ref_param_received;	
			
		/*mode selections*/	
			
		if(runningModeFlags.bit.closedLoopControl & !runningModeFlags.bit.openLoopControl 	){new_mode=closedLoop;}
		if(runningModeFlags.bit.closedLoopControl & runningModeFlags.bit.openLoopControl 		){new_mode=openLoop;}
		if(runningModeFlags.bit.manualControl     & runningModeFlags.bit.manualVarControl 	){new_mode=manualVar;}
		if(runningModeFlags.bit.manualControl     & runningModeFlags.bit.manualAngleControl	){new_mode=manualAngle;}
		
		if(runningModeFlags.bit.only2HF						 & (current_state!=run)										){
			
			new_mode=hf;
			
		}else{
			
			runningModeFlags.bit.only2HF=0;
		
		}
		
		if(runningModeFlags.bit.firingTestMode    & (current_state!=run)										){
		
			new_mode=firingTest;
			
		}else{
		
		runningModeFlags.bit.firingTestMode=0;
			
		}
		
		/*flag selections*/	
			
		}
	}
}