

#include "main_flow.h"


void main_flow(){
	
	PLL_all();
	RMS_all();
	
	Qbasic_calculation();
	PowerCalculations();
	
	faultRoutines();
	tripRoutines();
	
	state_chart();
	mode_chart();
	
	ios();

}
