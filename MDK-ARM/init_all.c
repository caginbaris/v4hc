#include "init_all.h"


void init_all(void){


init_conversion();
init_firing();	
init_Q2alpha();

init_Qbasic();
init_PI();
init_OpenLoopCalc();
init_firingTestMode();
init_references(); 
	
init_current_limiter();
init_voltage_limiter();


	
}

