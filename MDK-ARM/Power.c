

#include "conversion.h"
#include "nfbm.h"
#include "constants.h"

#define 	power_period 	500.0f
#define  ipower_period 	1.0f/power_period




struct ClosedLoopPQ cl={0};

void PowerCalculations(void){
	

	
cl.Psum			=cl.Psum 		+	adc.Van * adc.Ia
												+ adc.Vbn * adc.Ib
												+ adc.Vcn * adc.Ic;
	
	
cl.Qsum			=cl.Qsum 		+ adc.Vbc * adc.Ia
												+	adc.Vab * adc.Ic
												+	adc.Vca * adc.Ib;	
	
cl.Qab_sum 	=cl.Qab_sum	+	adc.Ia*adc.Vbc
												+ adc.Ib*adc.Vca
												-	adc.Ic*adc.Vab;
	
cl.Qbc_sum 	=cl.Qbc_sum	-	adc.Ia*adc.Vbc
												+ adc.Ib*adc.Vca
												+	adc.Ic*adc.Vab;
	
cl.Qca_sum 	=cl.Qca_sum	+	adc.Ia*adc.Vbc
												- adc.Ib*adc.Vca
												+	adc.Ic*adc.Vab;
												
												
	if(++cl.counter==power_period){
	
	cl.Ptotal=cl.Psum*ipower_period;

	cl.Qtotal=cl.Qsum*ipower_period*isqrt3;

	cl.Qab=cl.Qab_sum*ipower_period*isqrt3;
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
