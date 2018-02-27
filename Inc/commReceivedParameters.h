#ifndef __commReceivedParameters_h
#define __commReceivedParameters_h

#include "stdint.h"

union mode_flags{

	struct{
		
		uint32_t closedLoopControl:1;
		uint32_t manualControl:1;
		uint32_t openLoopControl:1;
		uint32_t only_2HF:1; 
		uint32_t firingTest:1;
		uint32_t spare1:3; 
		uint32_t PCC_pointSelect:1; //0=>154, 1=>34.5
		uint32_t Qcontrol_compSelect:1; //0=>Reactive, 1=>PF
		uint32_t manual_modeSelect:1;//0=>Var, 1=>Angle;
		uint32_t firingTestEnable:1;
	
	}bit;
	
	uint32_t all;

};

extern union mode_flags  receivedModeFlags;
extern union mode_flags runningModeFlags;



#endif
