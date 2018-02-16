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
	
	sys.TCR_XL_ab=0.001f*7.92f*2*3.14159f*50.0f;
	sys.TCR_XL_bc=0.001f*7.92f*2*3.14159f*50.0f;
	sys.TCR_XL_ca=0.001f*7.92f*2*3.14159f*50.0f;

}



float Q2alpha(float x){

	float x2,x3,x4,x5;
	float alpha;

	

	if(x<0.005f){x=0.005f;}
	if(x>0.91f) {x=0.91f;}

	x2=x*x;
	x3=x2*x;
	x4=x2*x2;
	x5=x2*x3;


	if(x>=0.1f){alpha = (p1_u*x5 + p2_u*x4 + p3_u*x3 + p4_u*x2 + p5_u*x +p6_u)*r2d;}
	if(x<0.1f ){alpha = (p1_l*x5 + p2_l*x4 + p3_l*x3 + p4_l*x2 + p5_l*x +p6_l)*r2d;}

	f_limiter(&alpha,sys.Alpha_limit_down,sys.Alpha_limit_up);

	alpha=alpha-trigger_offset;

	return alpha;


}


void Q2alpha_transforms(){
	
	
	if(	current_mode==closedLoop 	|
			current_mode==openLoop 		|
			current_mode==manualVar 	|
			current_mode==inter){

		//cau scaled to 34500 with 90
				
		if(fRMS.Vab>1.0f && fRMS.Vbc>1.0f && fRMS.Vca>1.0f){
				
		sys.Bp_ab=	(ref_ab.final_Q*sys.TCR_XL_ab) /(fRMS.Vab);	
		sys.Bp_bc=	(ref_ab.final_Q*sys.TCR_XL_bc) /(fRMS.Vbc);	
		sys.Bp_ca=	(ref_ab.final_Q*sys.TCR_XL_ca) /(fRMS.Vca);	
			
		}
		
		
		ref_ab.final_alpha=Q2alpha(sys.Bp_ab);
		ref_bc.final_alpha=Q2alpha(sys.Bp_bc);
		ref_ca.final_alpha=Q2alpha(sys.Bp_ca);

			
		}
			
		
	
}





