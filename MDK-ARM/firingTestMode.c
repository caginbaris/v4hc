#include "nfbm.h"
#include "firingTest.h"
#include "time_constants.h"


struct TestFiring TestFire;


void firingTestMode(void){
	
	
			if(TestFire.enable_firing==1){

			if(!voltage_loss.trip){status.start_flag=1;}	
				
			if(TestFire.counter++>TestFire.firing_duration*ms){


				status.start_flag=0;
				TestFire.counter=0;
				TestFire.enable_firing=0;


		}
	}
}

