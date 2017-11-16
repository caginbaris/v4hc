/*
 *
 *  Created on: Mar 10, 2017
 *      Author: baris.cengiz
 */

#include "states.h"

enum StateID current_state=startup;


void (*state[])(void)={

startupState,
faultState,
readyState,
runState,
idleState,
stoppedState,
trippedState
	
};


void state_chart(){

void(* state_fun)(void);

state_fun=state[current_state];
state_fun();


}


