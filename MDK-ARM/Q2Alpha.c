/*
 * Q2alpha.c
 *
 *  Created on: 21 Haz 2016
 *      Author: Baris
 */

#include "nfbm.h"
#include "Q2Alpha.h"
#include "modes.h"




void init_Q2alpha(void){



}



float Q2alpha(float Qin, float RMS, float TCR_XL){

	float x,x2,x3,x4,x5;
	float alpha;

	x=TCR_XL*Qin/RMS;

	if(x<0.005f){x=0.005f;}
	if(x>0.91f) {x=0.91f;}

	x2=x*x;
	x3=x2*x;
	x4=x2*x2;
	x5=x2*x3;


	if(x>=0.1f){alpha = (p1_u*x5 + p2_u*x4 + p3_u*x3 + p4_u*x2 + p5_u*x +p6_u)*r2d;}
	if(x<0.1f ){alpha = (p1_l*x5 + p2_l*x4 + p3_l*x3 + p4_l*x2 + p5_l*x +p6_l)*r2d;}


	if(alpha>fire.alpha_limit_down){alpha=fire.alpha_limit_down;}
	if(alpha<fire.alpha_limit_up){alpha=fire.alpha_limit_up;}


	alpha=alpha-trigger_offset;

	if(Qin<=0){alpha=fire.alpha_limit_down;}

	return alpha;


}


void Q2alpha_transforms(){
	
	
	if(	current_mode==closedLoop 	|
			current_mode==openLoop 		|
			current_mode==manualVar 	|
			current_mode==inter){


		ref_ab.final_alpha=Q2alpha(ref_ab.final_Q,fRMS.Vab,sys.TCR_XL_ab);
		ref_bc.final_alpha=Q2alpha(ref_bc.final_Q,fRMS.Vbc,sys.TCR_XL_bc);
		ref_ca.final_alpha=Q2alpha(ref_ca.final_Q,fRMS.Vca,sys.TCR_XL_ca);
			
			}
	
}





