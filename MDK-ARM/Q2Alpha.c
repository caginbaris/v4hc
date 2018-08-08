/*
 * Q2alpha.c
 *
 *  Created on: 21 Haz 2016
 *      Author: Baris
 */

#include "nfbm.h"
#include "Q2Alpha.h"
#include "modes.h"
#include "aux_functions.h"



void init_Q2alpha(void){
	
	sys.TCR_XL_ab=0.001f*45.236f*2*3.14159f*50.0f; //cau sys tcr-setup
	sys.TCR_XL_bc=0.001f*45.212f*2*3.14159f*50.0f;
	sys.TCR_XL_ca=0.001f*45.205f*2*3.14159f*50.0f;

	sys.Alpha_limit_down=99.0f;
	sys.Alpha_limit_up=165.0f;
	
	sys.B_limit_down=0.005f;
	sys.B_limit_up=0.85f;
	
	sys.Bp_ab=sys.B_limit_down;
	sys.Bp_bc=sys.B_limit_down;
	sys.Bp_ca=sys.B_limit_down;
	
}



float Q2alpha(float x){

	float x2,x3,x4,x5;
	float alpha;

	

	if(x<=sys.B_limit_down){x=sys.B_limit_down;}
	if(x>sys.B_limit_up) {x=sys.B_limit_up;}
	

	x2=x*x;
	x3=x2*x;
	x4=x2*x2;
	x5=x2*x3;


	if(x>=0.1f){alpha = (p1_u*x5 + p2_u*x4 + p3_u*x3 + p4_u*x2 + p5_u*x +p6_u)*r2d;}
	if(x<0.1f ){alpha = (p1_l*x5 + p2_l*x4 + p3_l*x3 + p4_l*x2 + p5_l*x +p6_l)*r2d;}

	alpha=alpha-trigger_offset;
	
	f_limiter(&alpha,sys.Alpha_limit_down,sys.Alpha_limit_up);

	return alpha;


}


void Q2alpha_transforms(){
	
	
	if(	current_mode==closedLoop 	|
			current_mode==openLoop 		|
			current_mode==manualVar 	|
			current_mode==inter){

	
		if(minSelector_3p(meanRMS.Vab,meanRMS.Vbc,meanRMS.Vca)>voltage_loss_limit){		
				
		sys.Bp_ab=	(ref_ab.final_Q*sys.TCR_XL_ab) /(fRMS.Vab);	
		sys.Bp_bc=	(ref_bc.final_Q*sys.TCR_XL_bc) /(fRMS.Vbc);	
		sys.Bp_ca=	(ref_ca.final_Q*sys.TCR_XL_ca) /(fRMS.Vca);	
			
		}
		
		
		ref_ab.final_alpha=Q2alpha(sys.Bp_ab-I_limiter.ab.B+V_limiter.ab.Bout);
		ref_bc.final_alpha=Q2alpha(sys.Bp_bc-I_limiter.bc.B+V_limiter.bc.Bout);
		ref_ca.final_alpha=Q2alpha(sys.Bp_ca-I_limiter.ca.B+V_limiter.ca.Bout);

			
		}
			
}





