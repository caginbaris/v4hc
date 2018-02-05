#include "nfbm.h"

struct control_loops PI={0};


void init_PI(void){
	
	PI.CL.Ki=0.00012f;
	PI.CL.Kp=0.05f;
	PI.CL.plimit=48000.0f;
	PI.CL.nlimit=0.0f;
	
	
	PI.OL.Ki=0.0005f;
	PI.OL.Kp=0.05f;
	PI.OL.plimit=48000.0f;
	PI.OL.nlimit=-48000.0f;

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

	if(PI.CL.ab.Iout>PI.CL.plimit){PI.CL.ab.Iout=PI.CL.plimit;}
	if(PI.CL.ab.Iout<PI.CL.nlimit){PI.CL.ab.Iout=PI.CL.nlimit;}

	if(PI.CL.bc.Iout>PI.CL.plimit){PI.CL.bc.Iout=PI.CL.plimit;}
	if(PI.CL.bc.Iout<PI.CL.nlimit){PI.CL.bc.Iout=PI.CL.nlimit;}

	if(PI.CL.ca.Iout>PI.CL.plimit){PI.CL.ca.Iout=PI.CL.plimit;}
	if(PI.CL.ca.Iout<PI.CL.nlimit){PI.CL.ca.Iout=PI.CL.nlimit;}

	PI.CL.ab.PIout=PI.CL.ab.Iout + PI.CL.ab.Pout;
	PI.CL.bc.PIout=PI.CL.bc.Iout + PI.CL.bc.Pout;
	PI.CL.ca.PIout=PI.CL.ca.Iout + PI.CL.ca.Pout;

	if(PI.CL.ab.PIout>PI.CL.plimit){PI.CL.ab.PIout=PI.CL.plimit;}
	if(PI.CL.ab.PIout<PI.CL.nlimit){PI.CL.ab.PIout=PI.CL.nlimit;}

	if(PI.CL.bc.PIout>PI.CL.plimit){PI.CL.bc.PIout=PI.CL.plimit;}
	if(PI.CL.bc.PIout<PI.CL.nlimit){PI.CL.bc.PIout=PI.CL.nlimit;}

	if(PI.CL.ca.PIout>PI.CL.plimit){PI.CL.ca.PIout=PI.CL.plimit;}
	if(PI.CL.ca.PIout<PI.CL.nlimit){PI.CL.ca.PIout=PI.CL.nlimit;}



}





void PI_OL(void){

	PI.OL.error=PI.Qref*0.333333f-PI.OL.Qin;

	PI.OL.Pout=PI.OL.error*PI.OL.Kp;
	PI.OL.Iout=PI.OL.Iout+PI.OL.error*PI.OL.Ki;

	if(PI.OL.Iout>PI.OL.plimit){PI.OL.Iout=PI.OL.plimit;}
	if(PI.OL.Iout<PI.OL.nlimit){PI.OL.Iout=PI.OL.nlimit;}

	PI.OL.PIout=PI.OL.Pout + PI.OL.Iout ;

	if(PI.OL.PIout>PI.OL.plimit){PI.OL.PIout=PI.OL.plimit;}
	if(PI.OL.PIout<PI.OL.nlimit){PI.OL.PIout=PI.OL.nlimit;}




}
