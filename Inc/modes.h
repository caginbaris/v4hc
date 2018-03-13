/*
*Created on : 15.11.2017
*Author : Baris
*/

#ifndef __modes_h
#define __modes_h


void closedLoopMode(void);
void openLoopMode(void);
void manualVarMode(void);
void manualAngleMode(void);
void firingTestMode(void);
void interMode(void);
void hfMode(void);


enum ModeID{	


closedLoop,
openLoop,
manualVar,
manualAngle,
firingTest,
inter,	
hf

	
};

extern enum ModeID current_mode;
extern enum ModeID new_mode;

#endif
