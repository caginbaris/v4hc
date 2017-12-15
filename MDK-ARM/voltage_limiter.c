
#include "nfbm.h"
#include "aux_functions.h"
#include "time_constants.h"


struct voltageLimitParameters V_limiter;

void init_voltage_limiter(){


}


void voltage_limiter(){
	
	
	
	if(fRMS.Vab>V_limiter.level){V_limiter.ab.pick=1;}
	
	if(fRMS.Vab<V_limiter.level*0.9f){V_limiter.ab.pick=0;}
	
	V_limiter.ab.start=on_delay(V_limiter.ab.pick,V_limiter.ab.start,V_limiter.delay*t2s,&V_limiter.ab.counter);
	
	if(V_limiter.ab.start){
	
	V_limiter.ab.Bout+=V_limiter.tau*(fRMS.Vab-V_limiter.level);	
		
	f_limiter(&V_limiter.ab.Bout,0.0f,0.5f);	
		
	status.voltage_limiting=1;	
	
	}else{
	
	V_limiter.ab.Bout=0;
	
	status.voltage_limiting=1;		
	
	}
	
	


}

