
#include "nfbm.h"
#include "aux_functions.h"
#include "modes.h"
#include "time_constants.h"

#define up_threshold 		1.1f
#define down_threshold 	0.9f

struct levelCheckParameters levelCheck={0};

void level_check(){
	
	float It=0;

	if(!status.regulation_enable & status.start_flag & current_mode!=manualAngle){
		
		if(meanRMS.Vab>1.0f && meanRMS.Vbc>1.0f && meanRMS.Vbc>1.0f){
		
		It=(ref_ab.final_Q/meanRMS.Vab);
		
		levelCheck.TCR_ab_fault=on_delay((meanRMS.Itcr_ab>(It*up_threshold) || meanRMS.Itcr_ab<(It*down_threshold)),levelCheck.TCR_ab_fault,_1sec,&levelCheck.counter[0]);
			
		It=(ref_bc.final_Q/meanRMS.Vbc);
		
		levelCheck.TCR_bc_fault=on_delay((meanRMS.Itcr_bc>(It*up_threshold) || meanRMS.Itcr_bc<(It*down_threshold)),levelCheck.TCR_bc_fault,_1sec,&levelCheck.counter[1]);	
	
		It=(ref_ca.final_Q/meanRMS.Vca);
		
		levelCheck.TCR_ca_fault=on_delay((meanRMS.Itcr_ca>(It*up_threshold) || meanRMS.Itcr_ca<(It*down_threshold)),levelCheck.TCR_ca_fault,_1sec,&levelCheck.counter[2]);	
	
		}
	
	}else{
	
	levelCheck.TCR_ab_fault=0;
	levelCheck.TCR_bc_fault=0;
	levelCheck.TCR_ca_fault=0;
	
	}


}