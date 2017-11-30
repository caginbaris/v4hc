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
//interModellar,
	
};


void mode_chart(void){

void(* mode_fun)(void);

mode_fun=mode[current_mode];
mode_fun();
	
	
	
if(new_mode!=current_mode){

	//entry like intermode can be entered
	//status.Qbasic_flag=1;

}	


}

