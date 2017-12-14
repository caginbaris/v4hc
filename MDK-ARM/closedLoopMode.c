

#include "nfbm.h"
#include "closedLoopMode.h"



void closedLoopMode(void){
	
	CL_handles();
	PI_CL();
	Ref_CL();
	Ref_flag_handles();
	
	
}

void CL_handles(void){
	
	PI.CL.ab.Qin=cl.Qab;
	PI.CL.bc.Qin=cl.Qbc;
	PI.CL.ca.Qin=cl.Qca;
	
	// make relevant init of other modes
	PI.OL.Iout=Qbasic.mean;
	PI.OL.PIout=Qbasic.mean;
	
}

