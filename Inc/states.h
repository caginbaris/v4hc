/*
*Created on : 15.11.2017
*Author : Baris
*/

#ifndef __states_h
#define __states_h


void startupState(void);
void faultState(void);
void readyState(void);
void runState(void);
void idleState(void);
void stoppedState(void);
void trippedState(void);

enum StateID{	
	
	startup=0x01,
	fault=0x02,
	ready=0x04,
	run=0x08,
	idle=0x10,
	stopped=0x20,
	tripped=0x40
	
};

extern enum StateID current_state;


#endif


