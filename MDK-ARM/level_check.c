
#include "nfbm.h"
#include "aux_functions.h"
#include "modes.h"
#include "time_constants.h"
#include "fundProcess.h"

#define up_threshold 		1.20f
#define down_threshold 	0.8f



float fTCR[3]={0};
static long counter[3]={0};
uint8_t temp[3]={0};

uint8_t check=0;



void level_check_startup(){
	
	float It=0;
	static long sDelay=0;
	
	
	
	fundEmAll(adc.Itcr_ab,adc.Itcr_ab,adc.Itcr_ab,fTCR);
	
	
	check=on_delay((!status.regulation_enable & status.start_flag & (current_mode!=manualAngle)),check,_1period,&sDelay);
	

	It=(meanRMS.Vab>voltage_loss_limit)? (ref_ab.final_Q/meanRMS.Vab): fTCR[0];	
			
	faultData.bit.level_check_ab_pick= (fTCR[0]>(It*up_threshold) || fTCR[0]<(It*down_threshold)) & check;
	temp[0]= on_delay(faultData.bit.level_check_ab_pick,temp[0],_5period,&counter[0]);
			
	It=(meanRMS.Vbc>voltage_loss_limit)? (ref_bc.final_Q/meanRMS.Vbc): fTCR[1];	
		
	faultData.bit.level_check_bc_pick= (fTCR[1]>(It*up_threshold) || fTCR[1]<(It*down_threshold))& check;
	temp[1]= on_delay(faultData.bit.level_check_bc_pick,temp[1],_5period,&counter[1]);
			
			
	It=(meanRMS.Vca>voltage_loss_limit)? (ref_ca.final_Q/meanRMS.Vca): fTCR[2];	
		
	faultData.bit.level_check_bc_pick= (fTCR[2]>(It*up_threshold) || fTCR[2]<(It*down_threshold))& check;
	temp[2]= on_delay(faultData.bit.level_check_ca_pick,temp[2],_5period,&counter[2]);
	

	
	if(temp[0]){faultData.bit.level_check_ab_trip=1;}
	if(temp[1]){faultData.bit.level_check_bc_trip=1;}
	if(temp[2]){faultData.bit.level_check_ca_trip=1;}		
		
}

