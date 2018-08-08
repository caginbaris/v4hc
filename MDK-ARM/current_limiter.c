
#include "nfbm.h"
#include "aux_functions.h"
#include "time_constants.h"

struct currentLimitParameters I_limiter={0};


void init_current_limiter(){
	
	I_limiter.level= 1765.0f; //1717A nom
	I_limiter.delay= 3.0f; //1717A nom
	I_limiter.tau=0.000005f;
	I_limiter.Bmax=0.2f;
	I_limiter.enable=1;
	

}


void current_limiter(){
	

	
	if(I_limiter.enable && I_limiter.level>1.0f){
		
	
	//----ab----	
	
	if(meanRMS.Itcr_ab>I_limiter.level && I_limiter.ab.flag ==0 ){
	
		I_limiter.ab.pick_up=1;
		
	}
	
	
	if(I_limiter.ab.pick_up){
		
		I_limiter.ab.pick_counter++;
		
		if(meanRMS.Itcr_ab<I_limiter.level*0.95f || I_limiter.ab.pick_counter>(long)(I_limiter.delay*t2s)){
		
			I_limiter.ab.release_counter_val=4*I_limiter.ab.pick_counter;
			I_limiter.ab.pick_counter=0;
			I_limiter.ab.flag=1;
			I_limiter.ab.pick_up=0;	
		}
		
	}
	

	//I_limiter.ab.flag=on_delay(I_limiter.ab.pick_up,I_limiter.ab.flag,I_limiter.delay*25000,&I_limiter.ab.pick_counter);
	
	
	
	if(I_limiter.ab.flag){
		
		
		

		
		
		I_limiter.ab.B += I_limiter.tau*(meanRMS.Itcr_ab-I_limiter.level)/I_limiter.level;
			
		f_limiter(&I_limiter.ab.B,0.0f,I_limiter.Bmax);
			
		

		
		
		if(I_limiter.ab.release_counter++>I_limiter.ab.release_counter_val){
		
			
		I_limiter.ab.B=0.0f;
		I_limiter.ab.release_counter=0.0f;
		I_limiter.ab.release_counter_val=0.0f;	
		I_limiter.ab.flag=0.0f;
				
			
			
		}
		
	}
	
	
	//----ab----end----	
	
	
	//----bc----	
	
	if(meanRMS.Itcr_bc>I_limiter.level && I_limiter.bc.flag==0 ){
	
		I_limiter.bc.pick_up=1;
		
	}
	
	
	if(I_limiter.bc.pick_up){
		
		I_limiter.bc.pick_counter++;
		
		if(meanRMS.Itcr_bc<I_limiter.level*0.95f || I_limiter.bc.pick_counter>(long)(I_limiter.delay*t2s)){
		
			I_limiter.bc.release_counter_val=4*I_limiter.bc.pick_counter;
			I_limiter.bc.pick_counter=0;
			I_limiter.bc.pick_up=0;
			I_limiter.bc.flag=1;
		}
		
	}
	

	//I_limiter.bc.flag=on_delay(I_limiter.bc.pick_up,I_limiter.bc.flag,I_limiter.delay*25000,&I_limiter.bc.pick_counter);
	
	
	
	if(I_limiter.bc.flag){
		
		
		
		
		
		
		I_limiter.bc.B += I_limiter.tau*(meanRMS.Itcr_bc-I_limiter.level)/I_limiter.level;
			
		f_limiter(&I_limiter.bc.B,0.0f,I_limiter.Bmax);
			
		
	
		
		
		if(I_limiter.bc.release_counter++>I_limiter.bc.release_counter_val){
		
			
		I_limiter.bc.B=0.0f;
		I_limiter.bc.release_counter=0.0f;
		I_limiter.bc.release_counter_val=0.0f;	
		I_limiter.bc.flag=0.0f;	
			
			
		}
		
	}
	
	
	//----bc----end----	
	
	
		//----ca----	
	
	if(meanRMS.Itcr_ca>I_limiter.level && I_limiter.ca.flag==0 ){
	
		I_limiter.ca.pick_up=1;
		
	}
	
	
	if(I_limiter.ca.pick_up){
		
		I_limiter.ca.pick_counter++;
		
		if(meanRMS.Itcr_ca<I_limiter.level*0.95f || I_limiter.ca.pick_counter>(long)(I_limiter.delay*t2s)){
		
			I_limiter.ca.release_counter_val=4*I_limiter.ca.pick_counter;
			I_limiter.ca.pick_counter=0;
			I_limiter.ca.pick_up=0;
			I_limiter.ca.flag=1;
		}
		
	}
	

	//I_limiter.ca.flag=on_delay(I_limiter.ca.pick_up,I_limiter.ca.flag,I_limiter.delay*25000,&I_limiter.ca.pick_counter);
	
	
	
	if(I_limiter.ca.flag){
		
		
		
		
		I_limiter.ca.B += I_limiter.tau*(meanRMS.Itcr_ca-I_limiter.level)/I_limiter.level;
			
		f_limiter(&I_limiter.ca.B,0.0f,I_limiter.Bmax);
			
		
		
		
		
		if(I_limiter.ca.release_counter++>I_limiter.ca.release_counter_val){
		
			
		I_limiter.ca.B=0.0f;
		I_limiter.ca.release_counter=0.0f;
		I_limiter.ca.release_counter_val=0.0f;	
		I_limiter.ca.flag=0.0f;	
			
			
		}
		
	}
	
	
	//----ca----end----	
	
	
	
	
}

}


