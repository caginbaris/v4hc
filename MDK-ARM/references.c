

#include "nfbm.h"
#include "commReceivedParameters.h"
#include <math.h>

#define VnomSquare 34500.0f*34500.0f
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
	
	ref_ab.final_Q=ref_set.ManualQ;
	ref_bc.final_Q=ref_set.ManualQ;
	ref_ca.final_Q=ref_set.ManualQ;


}


void Ref_manualAngle(){
	
	ref_ab.final_alpha=ref_set.ManualAlpha;
	ref_bc.final_alpha=ref_set.ManualAlpha;
	ref_ca.final_alpha=ref_set.ManualAlpha;


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
				
			ref_set.TR_Offset = sys.TR_Ratio*sys.TR_Uk*(VnomSquare)/sys.TR_Power;
				
				
			PI.Qref=(ref_set.MV_Bus_Offset - ref_set.TR_Offset);
			
			}
		
		}
		
		
		
		if(runningModeFlags.bit.pfControl ){
			
			ref_set.Q_PF_Set=cl.Ptotal*tan(acos(ref_set.PF_Set))*div3;
			
			if(runningModeFlags.bit.pointSelect){
				
			PI.Qref=ref_set.Q_PF_Set;
			
			}else{
				
			ref_set.TR_Offset = sys.TR_Ratio*sys.TR_Uk*(VnomSquare)/sys.TR_Power;	
			
			PI.Qref=(ref_set.Q_PF_Set - ref_set.TR_Offset);
			
			}
		
		}

}






