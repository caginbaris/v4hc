#include "nfbm.h"
#include "aux_functions.h"

struct control_loops PI={0};


void init_PI(void){
	
	PI.CL.Ki=0.0006f;
	PI.CL.Kp=0.05f;

	
	
	PI.OL.Ki=0.00008f;
	PI.OL.Kp=0.05f;


}



void PI_CL(void){
	

	PI.CL.ab.error=PI.Qref-PI.CL.ab.Qin;
	PI.CL.bc.error=PI.Qref-PI.CL.bc.Qin;
	PI.CL.ca.error=PI.Qref-PI.CL.ca.Qin;

	PI.CL.ab.Pout=PI.CL.ab.error*PI.CL.Kp;
	PI.CL.bc.Pout=PI.CL.bc.error*PI.CL.Kp;
	PI.CL.ca.Pout=PI.CL.ca.error*PI.CL.Kp;

	PI.CL.ab.Iout=PI.CL.ab.Iout + PI.CL.ab.error*PI.CL.Ki;
	PI.CL.bc.Iout=PI.CL.bc.Iout + PI.CL.bc.error*PI.CL.Ki;
	PI.CL.ca.Iout=PI.CL.ca.Iout + PI.CL.ca.error*PI.CL.Ki;

	//****
	
	f_limiter(&PI.CL.ab.Iout,0,sys.Q_limit);                
	f_limiter(&PI.CL.bc.Iout,0,sys.Q_limit);   
	f_limiter(&PI.CL.ca.Iout,0,sys.Q_limit);   

	PI.CL.ab.PIout=PI.CL.ab.Iout + PI.CL.ab.Pout;
	PI.CL.bc.PIout=PI.CL.bc.Iout + PI.CL.bc.Pout;
	PI.CL.ca.PIout=PI.CL.ca.Iout + PI.CL.ca.Pout;

	f_limiter(&PI.CL.ab.PIout,0,sys.Q_limit);                
	f_limiter(&PI.CL.bc.PIout,0,sys.Q_limit);   
	f_limiter(&PI.CL.ca.PIout,0,sys.Q_limit); 



}





void PI_OL(void){
	

	PI.OL.error=PI.Qref*0.333333f-PI.OL.Qin;

	PI.OL.Pout=PI.OL.error*PI.OL.Kp;
	PI.OL.Iout=PI.OL.Iout+PI.OL.error*PI.OL.Ki;

	f_limiter(&PI.OL.Iout,-sys.Q_limit,sys.Q_limit); 

	PI.OL.PIout=PI.OL.Pout + PI.OL.Iout ;

	f_limiter(&PI.OL.PIout,-sys.Q_limit,sys.Q_limit); 


}
