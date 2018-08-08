#include "nfbm.h"
#include "aux_functions.h"
#include "time_constants.h"



union  fault_data    faultData={0};

void faultRoutines(void){
	
// voltage loss- cau sync channel must be ysed
	
float Vmin;
static uint8_t temp=0;		
static long counter=0;	
	
Vmin=minSelector_3p(meanRMS.Vab,meanRMS.Vbc,meanRMS.Vca);	
	
if(Vmin<voltage_loss_limit){

faultData.bit.voltage_loss_pick=1;
	
}

if(Vmin>voltage_loss_limit*1.1f){

faultData.bit.voltage_loss_pick=0;
	
}

temp=on_delay(faultData.bit.voltage_loss_pick,temp,_2period,&counter);

if(temp){faultData.bit.voltage_loss_trip=1;}

}


