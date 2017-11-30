#include "nfbm.h"
#include "aux_functions.h"
#include "time_constants.h"
#include "ios.h"

struct internal_fault voltage_loss;

void faultRoutines(void){
	
// voltage loss
	
if(minSelector_3p(fRMS.Vab,fRMS.Vbc,fRMS.Vca<voltage_loss.limit)){

voltage_loss.pick_up=1;
	
}


if(minSelector_3p(fRMS.Vab,fRMS.Vbc,fRMS.Vca<voltage_loss.limit)>voltage_loss.limit*1.1f){

voltage_loss.pick_up=0;
	
}



voltage_loss.trip=on_delay(voltage_loss.pick_up,voltage_loss.trip,_3period,&voltage_loss.counter);


if(voltage_loss.trip){

if(DI.reset==1 && voltage_loss.pick_up==0){

	voltage_loss.trip=0;

	}
}


}


