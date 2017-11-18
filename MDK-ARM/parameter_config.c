/*
 *
 *  Created on: Nov 17, 2017
 *      Author: baris.cengiz
 */

#include "parameter_config.h"

enum ConfigID current_config_stage=configRead;


void (*config[])(void)={

configReadStage,
configReadErrorStage,
configRunStage,
configSetStage,
configWriteStage,
configWriteErrorStage,
configRestartStage,

};


void config_chart(){

void(* config_fun)(void);

config_fun=config[current_config_stage];
config_fun();


}





