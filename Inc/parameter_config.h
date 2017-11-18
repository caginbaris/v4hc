
/*
*Created on : 17.11.2017
*Author : Baris
*/

#ifndef __parameter_config_h
#define __parameter_config_h



void configReadStage(void);
void configReadErrorStage(void);
void configRunStage(void);
void configSetStage(void);
void configWriteStage(void);
void configWriteErrorStage(void);
void configRestartStage(void);

enum ConfigID{	
	

	configRead,
	configReadError,
	configRun,
	configSet,
	configWrite,
	configWriteError,
	configRestart
	
};

extern enum ConfigID current_config_stage;


#endif
