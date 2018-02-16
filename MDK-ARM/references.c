

#include "nfbm.h"
#include "commReceivedParameters.h"
#include <math.h>
#include "aux_functions.h"

#define VnomSquare 34500.0f*34500.0f
#define div3 0.333333333333333333333f

struct references ref_ab;
struct references ref_bc;
struct references ref_ca;

void init_references()
{
	
	ref_set.ManualAlpha=120.0f;
	
	

}


void Ref_CL(){
	
	ref_ab.final_Q=PI.CL.ab.PIout;
	ref_bc.final_Q=PI.CL.bc.PIout;
	ref_ca.final_Q=PI.CL.ca.PIout;
	
	


}


void Ref_OL(){
	
	ref_ab.final_Q=Qol.ref_ab*sys.OL_ratio + PI.OL.PIout*(1.0f-sys.OL_ratio);
	ref_bc.final_Q=Qol.ref_bc*sys.OL_ratio + PI.OL.PIout*(1.0f-sys.OL_ratio);
	ref_ca.final_Q=Qol.ref_ca*sys.OL_ratio + PI.OL.PIout*(1.0f-sys.OL_ratio);
	
	
	


}


void Ref_manualVar(){
	
	
	
	f_limiter(&ref_set.ManualQ,0,sys.Q_limit);
	
	ref_ab.final_Q=ref_set.ManualQ;
	ref_bc.final_Q=ref_set.ManualQ;
	ref_ca.final_Q=ref_set.ManualQ;
	

	
	
	


}


void Ref_manualAngle(){
	
	f_limiter(&(ref_set.ManualAlpha),sys.Alpha_limit_down,sys.Alpha_limit_up);
	
	ref_ab.final_alpha=ref_set.ManualAlpha;
	ref_bc.final_alpha=ref_set.ManualAlpha;
	ref_ca.final_alpha=ref_set.ManualAlpha;
	



}


void Ref_hf(){

	ref_ab.final_alpha=sys.Alpha_limit_up;
	ref_bc.final_alpha=sys.Alpha_limit_up;
	ref_ca.final_alpha=sys.Alpha_limit_up;

		
}


void Ref_inter(){
	
	ref_ab.final_alpha=Qbasic.ab;
	ref_bc.final_alpha=Qbasic.bc;
	ref_ca.final_alpha=Qbasic.ca;


}

void ref_basic(){
	
	if(status.Qbasic_flag ){

	ref_ab.final_Q=Qbasic.ab;
	ref_bc.final_Q=Qbasic.bc;
	ref_ca.final_Q=Qbasic.ca;
	
	}
		
	
}

void Ref_flag_handles(){


		if(runningModeFlags.bit.reactivePowerControl ){
			
			if(runningModeFlags.bit.pointSelect){
				
			PI.Qref=(ref_set.MV_Bus_Offset);
			
			}else{
				
			ref_set.TR_Offset = sys.TR_Ratio*sys.TR_Uk*(VnomSquare)/sys.TR_Power;
				
				
			PI.Qref=(ref_set.MV_Bus_Offset - ref_set.TR_Offset);
			
			}
		
		}
		
		
		
		if(runningModeFlags.bit.pfControl ){
			
			ref_set.Q_PF_Set=cl.Ptotal*tanf(acosf(ref_set.PF_Set))*div3;
			
			if(runningModeFlags.bit.pointSelect){
				
			PI.Qref=ref_set.Q_PF_Set;
			
			}else{
				
			ref_set.TR_Offset = sys.TR_Ratio*sys.TR_Uk*(VnomSquare)/sys.TR_Power;	
			
			PI.Qref=(ref_set.Q_PF_Set - ref_set.TR_Offset);
			
			}
		
		}

}






