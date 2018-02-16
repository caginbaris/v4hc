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


closedLoop=0x1,
openLoop=0x2,
manualVar=0x4,
manualAngle=0x8,
firingTest=0x10,
inter=0x20,	
hf=0x40

	
};

extern enum ModeID current_mode;
extern enum ModeID new_mode;

#endif
