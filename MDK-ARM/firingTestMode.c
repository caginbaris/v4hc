#include "nfbm.h"
#include "firingTest.h"
#include "time_constants.h"
#include "aux_functions.h"

struct TestFiring TestFire;


void init_firingTestMode(void){

	TestFire.alpha=sys.Alpha_limit_up;
	TestFire.enable_firing=0;
	TestFire.counter=0;
	TestFire.firing_duration=0.1f;
	
}


void firingTestMode(void){
	
	
			static long interval_pass_counter=0;
			static uint8_t reEnable=0;
	
			reEnable=off_delay(status.start_flag,reEnable,_10sec,&interval_pass_counter);
			
	
			if(TestFire.enable_firing==1){

			if(!faultData.bit.voltage_loss_trip && reEnable==0 ){status.start_flag=1;}	
			
			ref_ab.final_alpha=TestFire.alpha; // @ move to reference routine 
			ref_bc.final_alpha=TestFire.alpha; 
			ref_ca.final_alpha=TestFire.alpha; 			
				
			if(TestFire.counter++>TestFire.firing_duration*ms){

				status.start_flag=0;
				TestFire.counter=0;
				TestFire.enable_firing=0;
				
				
		}
	}
}

