
#include "nfbm.h"
#include "aux_functions.h"

struct currentLimitParameters I_limiter;


void init_current_limiter(){


}


void current_limiter(){
	
	
	
	if(meanRMS.Itcr_ab>I_limiter.level){
	
		I_limiter.ab.pick_up=1;
		I_limiter.ab.pre_pick_up=1;
		
	}
	
	
	if(I_limiter.ab.pick_up){
		
		if(meanRMS.Itcr_ab<I_limiter.level*0.95f || I_limiter.ab.flag){
		
			I_limiter.ab.release_counter_val=4*I_limiter.ab.pick_counter;
		
		}
		
	}
	

	I_limiter.ab.flag=on_delay(I_limiter.ab.pick_up,I_limiter.ab.flag,I_limiter.delay*25000,&I_limiter.ab.pick_counter);
	
	
	
	if(I_limiter.ab.flag){
		
		
		I_limiter.ab.B += I_limiter.tau*(meanRMS.Itcr_ab-I_limiter.Inom);
		f_limiter(&I_limiter.ab.B,0.0f,I_limiter.Bmax);
		
	}
	
	
	
	
	
}


