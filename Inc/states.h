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
	
	startup,
	fault,
	ready,
	run,
	idle,
	stopped,
	tripped
	
};

extern enum StateID current_state;


#endif


