
#include "nfbm.h"
#include "aux_functions.h"
#include "time_constants.h"
#include <math.h>

#define drop_out_ratio 0.98f

static long pick_count=0;
static uint8_t voltage_limit_flag=0;

struct voltageLimitParameters V_limiter={0};

void init_voltage_limiter(){
	
	V_limiter.level=34650.0f;
	V_limiter.delay=0.15f;
	V_limiter.tau=0.0025f;
	
	
	// +tau*(Vm-Vlevel)/Vlevel
	//tau=Bmax/((Vm-Vlevel)/Vlevel)-->15, for 1500 sample (60ms) =>tau 0.01
	
}


void voltage_limiter(){
	
	if(V_limiter.level>1.0f){
	
	//ab
	
	if(meanRMS.Vab>=V_limiter.level)    {V_limiter.ab.pick=1;}
	
	if(meanRMS.Vab<V_limiter.level*drop_out_ratio){V_limiter.ab.pick=0;}
	
	
	V_limiter.ab.start=on_off_delay(V_limiter.ab.pick,V_limiter.ab.start,V_limiter.delay*t2s,&V_limiter.ab.counter);
	
	
	if(V_limiter.ab.start){
	
	V_limiter.ab.Bout+=V_limiter.tau*(meanRMS.Vab-V_limiter.level*drop_out_ratio)/V_limiter.level;	
		
	f_limiter(&V_limiter.ab.Bout,0.0f,0.25f);	
		
	voltage_limit_flag=1;	
	
	}else{
	
	V_limiter.ab.Bout=0;
	
	voltage_limit_flag=0;		
	
	}
	
	
	//bc
	
	
	if(meanRMS.Vbc>=V_limiter.level)    {V_limiter.bc.pick=1;}
	
	if(meanRMS.Vbc<V_limiter.level*drop_out_ratio)  {V_limiter.bc.pick=0;}
	
	
	V_limiter.bc.start=on_delay(V_limiter.bc.pick,V_limiter.bc.start,V_limiter.delay*t2s,&V_limiter.bc.counter);
	
	
	if(V_limiter.bc.start){
	
	V_limiter.bc.Bout+=V_limiter.tau*(meanRMS.Vbc-V_limiter.level*drop_out_ratio)/V_limiter.level;	
		
	f_limiter(&V_limiter.bc.Bout,0.0f,0.25f);	
		
	voltage_limit_flag=1;	
	
	}else{
	
	V_limiter.bc.Bout=0;
	
	voltage_limit_flag=0;		
	
	}
	
	
	//ca
	
	
	if(meanRMS.Vca>=V_limiter.level)    {V_limiter.ca.pick=1;}
	
	if(meanRMS.Vca<V_limiter.level*drop_out_ratio){V_limiter.ca.pick=0;}
	
	
	V_limiter.ca.start=on_delay(V_limiter.ca.pick,V_limiter.ca.start,V_limiter.delay*t2s,&V_limiter.ca.counter);
	
	
	if(V_limiter.ca.start){
	
	V_limiter.ca.Bout+=V_limiter.tau*(meanRMS.Vca-V_limiter.level*drop_out_ratio)/V_limiter.level;	
		
	f_limiter(&V_limiter.ca.Bout,0.0f,0.25f);	
		
	voltage_limit_flag=1;	
	
	}else{
	
	V_limiter.ca.Bout=0;
	
	voltage_limit_flag=0;		
	
	}
	
	

}
	
	
	status.voltage_limiting=off_delay(voltage_limit_flag,status.voltage_limiting,25000,&pick_count);

	
}

