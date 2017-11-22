
#include "nfbm.h"
#include "openLoopMode.h"
#include "constants.h"


void openLoopMode(void){

OL_handles();
OL_calculations();	
PI_OL();
Ref_OL();	
	
	

}


void OL_handles(void){
	
	PI.OL.Qin=cl.Qtotal*i3;
	
	// make relevant init of other modes
	PI.CL.ab.Iout=Qbasic.ab; PI.CL.ab.Pout=0.0f;
	PI.CL.bc.Iout=Qbasic.bc; PI.CL.bc.Pout=0.0f;
	PI.CL.ca.Iout=Qbasic.ca; PI.CL.ca.Pout=0.0f;
	
}

