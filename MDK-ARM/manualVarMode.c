
#include "nfbm.h"
#include "manualMode.h"


void manualVarMode(void){

manual_handles();
Ref_manualVar();
	
}


void manual_handles(void){
	
	
	PI.CL.ab.Iout=Qbasic.ab; PI.CL.ab.Pout=0.0f;PI.CL.ab.PIout=Qbasic.ab;
	PI.CL.bc.Iout=Qbasic.bc; PI.CL.bc.Pout=0.0f;PI.CL.bc.PIout=Qbasic.bc;
	PI.CL.ca.Iout=Qbasic.ca; PI.CL.ca.Pout=0.0f;PI.CL.ca.PIout=Qbasic.ca;

	PI.OL.Iout=Qbasic.mean; PI.OL.Pout=0.0f;PI.OL.PIout=Qbasic.mean;
	
}
