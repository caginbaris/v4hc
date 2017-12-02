
#include "nfbm.h"
#include "aux_functions.h"
#include "time_constants.h"

struct currentLimitParameters I_limiter;


void init_current_limiter(){


}


void current_limiter(){
	
	if(I_limiter.enable){
		
		
	//----ab----	
	
	if(meanRMS.Itcr_ab>I_limiter.level && I_limiter.ab.pick_up==0 ){
	
		I_limiter.ab.pick_up=1;
		
	}
	
	
	if(I_limiter.ab.pick_up){
		
		I_limiter.ab.pick_counter++;
		
		if(meanRMS.Itcr_ab<I_limiter.level*0.95f || I_limiter.ab.pick_counter>(long)(I_limiter.delay*t2s)){
		
			I_limiter.ab.release_counter_val=4*I_limiter.ab.pick_counter;
			I_limiter.ab.pick_counter=0;
			I_limiter.ab.pick_up=0;
			I_limiter.ab.flag=1;
		}
		
	}
	

	//I_limiter.ab.flag=on_delay(I_limiter.ab.pick_up,I_limiter.ab.flag,I_limiter.delay*25000,&I_limiter.ab.pick_counter);
	
	
	
	if(I_limiter.ab.flag){
		
		
		
		if(meanRMS.Itcr_ab>I_limiter.level){
		
		
		I_limiter.ab.B += I_limiter.tau*(meanRMS.Itcr_ab-I_limiter.level);
			
		f_limiter(&I_limiter.ab.B,0.0f,I_limiter.Bmax);
			
		
		}
		
		
		if(I_limiter.ab.release_counter++>I_limiter.ab.release_counter_val){
		
			
		I_limiter.ab.B=0.0f;
		I_limiter.ab.release_counter=0.0f;
		I_limiter.ab.release_counter_val=0.0f;	
		I_limiter.ab.flag=0.0f;	
			
			
		}
		
	}
	
	
	//----ab----end----	
	
}
	
	
}


