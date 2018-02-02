/*
 *
 *  Created on: Mar 10, 2017
 *      Author: baris.cengiz
 */

#include "modes.h"
#include "nfbm.h"

enum ModeID current_mode=manualAngle;
enum ModeID new_mode=manualAngle;

void (*mode[])(void)={

closedLoopMode,
openLoopMode,
manualVarMode,
manualAngleMode,
firingTestMode,
interMode,	
hfMode

};


void mode_chart(void){

void(* mode_fun)(void);

mode_fun=mode[current_mode];
mode_fun();
	

}

