#include "nfbm.h"
#include "ios.h"





void protection_handling(){
	
		
	if((faultData.all&0x1E0)!=0x0){
	
	faultData.bit.general_fault=1;DO.IBF=0;DO.LD_IBF=0;//cau
	
	}else{
	
	faultData.bit.general_fault=0;DO.IBF=1;DO.LD_IBF=1; 
		
	}
	
	if(!faultData.bit.voltage_loss_pick 		& DI.reset){faultData.bit.voltage_loss_trip=0;}
	
	if(!faultData.bit.level_check_ab_pick		& DI.reset){faultData.bit.level_check_ab_trip=0;}
	if(!faultData.bit.level_check_bc_pick		& DI.reset){faultData.bit.level_check_bc_trip=0;}
	if(!faultData.bit.level_check_ca_pick		& DI.reset){faultData.bit.level_check_ca_trip=0;}
	
	if(DI.reset){faultData.bit.ex_trip=0;}
	

}