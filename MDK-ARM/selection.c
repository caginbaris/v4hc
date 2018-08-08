
#include "nfbm.h"
#include "states.h"
#include "modes.h"
#include "commReceivedParameters.h"
#include "firingTest.h"

union mode_flags runningModeFlags;

void mode_selection(){
	
		runningModeFlags.all=receivedModeFlags.all;
		
		/*mode selections*/	
	
		if(runningModeFlags.bit.only_2HF					& (current_state!=run)){	new_mode=hf;}
		if(runningModeFlags.bit.firingTest    		& (current_state!=run)){	new_mode=firingTest; TestFire.enable_firing=1;}
			
		if(runningModeFlags.bit.closedLoopControl & !runningModeFlags.bit.openLoopControl 	){new_mode=closedLoop;}
		if(runningModeFlags.bit.closedLoopControl &  runningModeFlags.bit.openLoopControl 	){new_mode=openLoop;}
		if(runningModeFlags.bit.manualControl     & !runningModeFlags.bit.manual_modeSelect ){new_mode=manualVar;}
		if(runningModeFlags.bit.manualControl     &  runningModeFlags.bit.manual_modeSelect	){new_mode=manualAngle;}
		
		if(current_mode!=new_mode){current_mode=inter;}
		
		/*flag selections*/	

}