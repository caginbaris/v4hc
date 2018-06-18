#include "nfbm.h"
#include "aux_functions.h"
#include "time_constants.h"
#include "ios.h"

#define voltage_loss_limit 0

static long counter=0;

void faultRoutines(void){
	
// voltage loss- cau sync channel must be ysed
	
if(minSelector_3p(fRMS.Vab,fRMS.Vbc,fRMS.Vca<voltage_loss_limit)){

faultData.bit.voltage_loss_pick=1;
	
}

if(minSelector_3p(fRMS.Vab,fRMS.Vbc,fRMS.Vca)>voltage_loss.limit*1.1f){

faultData.bit.voltage_loss_pick=0;
	
}

faultData.bit.voltage_loss_trip=on_delay(voltage_loss.pick_up,faultData.bit.voltage_loss_trip,_3period,&counter);

if(faultData.bit.voltage_loss_trip){DO.IBF=0;}

if(DI.reset==1 && faultData.bit.voltage_loss_pick==0){

	faultData.bit.voltage_loss_trip=0;
	DO.IBF=1;}



}


