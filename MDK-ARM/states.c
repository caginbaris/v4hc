/*
 *
 *  Created on: Mar 10, 2017
 *      Author: baris.cengiz
 */

#include "states.h"
#include "nfbm.h"

struct stat status;

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


void state_chart(void){

void(* state_fun)(void);

state_fun=state[current_state];
state_fun();


}


