#ifndef __commReceivedParameters_h
#define __commReceivedParameters_h

#include "stdint.h"

union mode_flags{

	struct{
		
		uint32_t closedLoopControl:1;
		uint32_t manualControl:1;
		uint32_t openLoopControl:1;
		uint32_t pointSelect:1; // PCC default 0 to HV
		uint32_t reactivePowerControl:1; //*
		uint32_t pfControl:1; //*
		uint32_t manualVarControl:1; //
		uint32_t manualAngleControl:1;
		uint32_t only2HF;
		uint32_t firingTestMode;
		uint32_t firingTestEnable;
	
	}bit;
	
	uint32_t all;

};

extern union mode_flags  receivedModeFlags;
extern union mode_flags runningModeFlags;



#endif
