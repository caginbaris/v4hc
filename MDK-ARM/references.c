

#include "nfbm.h"
#include "commReceivedParameters.h"
#include <math.h>
#include "aux_functions.h"

#define VnomSquare 34500.0f*34500.0f
#define div3 0.333333333333333333333f

struct references ref_ab={160.0f,0.0f};
struct references ref_bc={160.0f,0.0f};;
struct references ref_ca={160.0f,0.0f};;

void init_references()
{
	
	ref_set.ManualAlpha=120.0f;
	ref_set.ManualQ=0.0f;
	ref_set.MV_Bus_Offset=0;
	ref_set.TR_Offset=0;
	ref_set.MV_Bus_Offset=0;
	ref_set.PF_Set=1.0f;
	ref_set.Q_PF_Set=0;	
	
	sys.TR_Uk=0.144;
	sys.TR_Power=150000000;
	sys.TR_Ratio=0.5;
	
	

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
		
	PI.OL.Iout=Qbasic.mean;
	PI.OL.PIout=Qbasic.mean;	
		
	PI.CL.ab.Iout=Qbasic.ab; PI.CL.ab.Pout=0.0f;
	PI.CL.bc.Iout=Qbasic.bc; PI.CL.bc.Pout=0.0f;
	PI.CL.ca.Iout=Qbasic.ca; PI.CL.ca.Pout=0.0f;	
	
	}
		
}

void Ref_flag_handles(){
	
			if(!runningModeFlags.bit.Qcontrol_compSelect ){
			
			if(runningModeFlags.bit.PCC_pointSelect){
				
			PI.Qref=(ref_set.MV_Bus_Offset);
			
			}else{
				
			if(	sys.TR_Power>1.0f){
				
			ref_set.TR_Offset = cRMS*cRMS*sys.TR_Ratio*sys.TR_Uk*(VnomSquare)/sys.TR_Power;

			}else{ref_set.TR_Offset=0;}
				
			PI.Qref=(ref_set.MV_Bus_Offset - ref_set.TR_Offset);
			
			}
		
		}
		
		
		
		
		if(runningModeFlags.bit.Qcontrol_compSelect ){
			
			ref_set.Q_PF_Set=cl.Ptotal*tanf(acosf(ref_set.PF_Set))*div3;
			
			if(runningModeFlags.bit.PCC_pointSelect){
				
			PI.Qref=ref_set.Q_PF_Set;
			
			}else{
				
			if(	sys.TR_Power>1.0f){	
				
			ref_set.TR_Offset = cRMS*cRMS*sys.TR_Ratio*sys.TR_Uk*(VnomSquare)/sys.TR_Power;	}else{ref_set.TR_Offset=0;}
			
			PI.Qref=(ref_set.Q_PF_Set - ref_set.TR_Offset);
			
			}
		
		}


}






