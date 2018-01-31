

#include "main_flow.h"


void main_flow(){
	
	
	PLL_all();
	lead_lag_calculation();
	RMS_all();
	
	Qbasic_calculation();
	PowerCalculations();
	faultRoutines();
	tripRoutines();
	
	mode_chart(); 
	state_chart();
	
	ref_basic();
	Q2alpha_transforms();
	firing(); 
	ios();
	

	
	

}
