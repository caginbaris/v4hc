#include "nfbm.h"

void hfMode(void){

	PI.CL.ab.Iout=Qbasic.ab; PI.CL.ab.Pout=0;PI.CL.ab.PIout=Qbasic.ab;
	PI.CL.bc.Iout=Qbasic.bc; PI.CL.bc.Pout=0;PI.CL.bc.PIout=Qbasic.bc;
	PI.CL.ca.Iout=Qbasic.ca; PI.CL.ca.Pout=0;PI.CL.ca.PIout=Qbasic.ca;

	PI.OL.Iout=Qbasic.mean; PI.OL.Pout=0;PI.OL.PIout=Qbasic.mean;
	
	
}

