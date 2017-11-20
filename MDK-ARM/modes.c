/*
 *
 *  Created on: Mar 10, 2017
 *      Author: baris.cengiz
 */

#include "modes.h"

enum ModeID current_mode=closedLoop;


void (*mode[])(void)={

closedLoopMode,
openLoopMode,
manualVarMode,
manualAngleMode,
firingTestMode
	
};


void mode_chart(void){

void(* mode_fun)(void);

mode_fun=mode[current_mode];
mode_fun();


}

