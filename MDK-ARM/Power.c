

#include "conversion.h"
#include "nfbm.h"
#include "constants.h"

#define 	power_period 	500.0f
#define  ipower_period 	1.0f/power_period

#define n1 0.0000391302053991682f
#define n2 2.0f*0.0000391302053991682f
#define n3 0.0000391302053991682f

#define d2 -1.982228929792529f
#define d3 0.982385450614126f


float quadrature(float x){

static float xz1=0.0f,xz2=0.0f,ytemp=0.0f,yz1=0.0f,yz2=0.0f;

	
ytemp = n1*x+n2*xz1+n3*xz2-d2*yz1-d3*yz2;

yz2 = yz1;
yz1 = ytemp;

xz2 = xz1;
xz1 = x;
	
return ytemp*sqrt2;
	
}


struct ClosedLoopPQ cl={0};

void PowerCalculations(void){
	
float Vq=0;

Vq=quadrature(adc.Vab);	
	
cl.Psum			=cl.Psum 		+	adc.Vab  * adc.Ia;//+	adc.Van * adc.Ia
												//+	adc.Vbn * adc.Ib
												//+	adc.Vcn * adc.Ic;
	
	
cl.Qsum			=cl.Qsum 		//+	adc.Vab * adc.Ic
												+	Vq * adc.Ia;
												//+	adc.Vca * adc.Ib;	
	
cl.Qab_sum 	=cl.Qab_sum	+	adc.Ia*Vq;//adc.Ia*adc.Vbc;
													//+ adc.Ib*adc.Vca
													//-	adc.Ic*adc.Vab;
	
cl.Qbc_sum 	=cl.Qbc_sum	-	adc.Ia*adc.Vbc
												+ adc.Ib*adc.Vca
												+	adc.Ic*adc.Vab;
	
cl.Qca_sum 	=cl.Qca_sum	+	adc.Ia*adc.Vbc
												- adc.Ib*adc.Vca
												+	adc.Ic*adc.Vab;
												
												
	if(++cl.counter==power_period){
	
	cl.Ptotal=cl.Psum*ipower_period;

	cl.Qtotal=cl.Qsum*ipower_period;//*isqrt3;

	cl.Qab=cl.Qab_sum*ipower_period;//*isqrt3;
	cl.Qbc=cl.Qbc_sum*ipower_period*isqrt3;
	cl.Qca=cl.Qca_sum*ipower_period*isqrt3;

	cl.counter=0;

	cl.Psum=0;
	cl.Qsum=0;
	cl.Qab_sum=0;
	cl.Qbc_sum=0;
	cl.Qca_sum=0;


	}												
												
												
}
