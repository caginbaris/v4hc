

#include "main_flow.h"


void main_flow(){
	
	
	PLL_all();
	
	Qbasic_calculation();
	lead_lag_calculation();
	RMS_all();
	PowerCalculations();
	
	faultRoutines();
	tripRoutines(); 
	
	protection_handling();
	//level_check_startup();
	
	mode_chart();  
	state_chart();
	
	ref_basic();
	
	//current_limiter();
	//voltage_limiter();
	
	
	Q2alpha_transforms();
	firing(); 
	ios();
	

	
	

}
