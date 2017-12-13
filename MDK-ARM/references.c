

#include "nfbm.h"
#include "commReceivedParameters.h"
#include <math.h>

#define div3 0.333333333333333333333f

struct references ref_ab;
struct references ref_bc;
struct references ref_ca;

void init_references()
{

}


void Ref_CL(){
	
	ref_ab.final_Q=PI.CL.ab.PIout;
	ref_bc.final_Q=PI.CL.bc.PIout;
	ref_ca.final_Q=PI.CL.ca.PIout;


}


void Ref_OL(){
	
	ref_ab.final_Q=Qol.ab_f*sys.OL_ratio + PI.OL.PIout*(1-sys.OL_ratio);
	ref_bc.final_Q=Qol.bc_f*sys.OL_ratio + PI.OL.PIout*(1-sys.OL_ratio);
	ref_ca.final_Q=Qol.ca_f*sys.OL_ratio + PI.OL.PIout*(1-sys.OL_ratio);


}


void Ref_manualVar(){
	
	ref_ab.final_Q=0.0f;
	ref_bc.final_Q=0.0f;
	ref_ca.final_Q=0.0f;


}


void Ref_manualAngle(){
	
	ref_ab.final_alpha=120.0f;
	ref_bc.final_alpha=120.0f;
	ref_ca.final_alpha=120.0f;


}


void Ref_inter(){
	
	ref_ab.final_alpha=Qbasic.ab;
	ref_bc.final_alpha=Qbasic.bc;
	ref_ca.final_alpha=Qbasic.ca;


}

void Ref_flag_handles(){


		if(runningModeFlags.bit.reactivePowerControl ){
			
			if(runningModeFlags.bit.pointSelect){
				
			PI.Qref=(ref_set.MV_Bus_Offset);
			
			}else{
			
			PI.Qref=(ref_set.MV_Bus_Offset - ref_param_received.TR_Offset);
			
			}
		
		}
		
		
		
		if(runningModeFlags.bit.pfControl ){
			
			ref_set.Q_PF_Set=cl.Ptotal*tan(acos(ref_param_received.PF_Set))*div3;
			
			if(runningModeFlags.bit.pointSelect){
				
			PI.Qref=ref_set.Q_PF_Set;
			
			}else{
			
			PI.Qref=(ref_set.Q_PF_Set - ref_param_received.TR_Offset);
			
			}
		
		}
		

		

		
		
	
	


}






