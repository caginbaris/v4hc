
#include "Qbasic.h"
#include "nfbm.h"
#include "ios.h"
#include "states.h"
#

#include "aux_functions.h"
#include "time_constants.h"


struct QbasicData Qdata={0};
struct QbasicOut Qbasic;
struct QbasicStartup Qstartup={0};


void init_Qbasic(void){
	
	

	Qdata.QHF_1=90.0; 	  /* 3HF entered from HMI side*/ 
	Qdata.QHF_2=80.0;		/* 2HF entered from HMI side*/ 
	Qdata.QHF_3=100.0; 	/* 4HF entered from HMI side*/

	
	sys.Vnom=34.5;
	
	Qdata.BHF_1=Qdata.QHF_1/(3.0f*sys.Vnom*sys.Vnom);
	Qdata.BHF_2=Qdata.QHF_2/(3.0f*sys.Vnom*sys.Vnom);
	Qdata.BHF_3=Qdata.QHF_3/(3.0f*sys.Vnom*sys.Vnom);

	

}

void Qbasic_calculation(void){
	
	
	
	//in normal operation
	


	
	//HF_1-2------------------------------
	
	Qdata.HF_1_CB_pos		=	DI.Q1_cb_pos;				//DI. from MRB
	Qdata.HF_1_DSC_pos	=	DI.Q10_ds_pos;			//DI. from MRB
	Qdata.HF_2_CB_pos=DI.Q3_cb_pos;
	
	
	Qdata.HF_1_EN				=	Qdata.HF_1_CB_pos & Qdata.HF_1_DSC_pos;
	Qdata.HF_2_EN				= Qdata.HF_1_EN 		& Qdata.HF_2_CB_pos;
								
	//HF_3----------------------------
	
	Qdata.HF_3_CB_pos = DI.Q2_cb_pos;//DI. from MRB
	Qdata.HF_3_DSC_pos=DI.Q20_ds_pos;//DI. from MRB
	
	Qdata.HF_3_EN= Qdata.HF_3_CB_pos & Qdata.HF_3_DSC_pos;
		
	
	//--------------------------------
	
	
	if(current_state==run){
	
	
	if((Qdata.HF_1_DSC_pos & (!Qdata.HF_1_CB_pos)	& DI.CB_Operation_Qbasic & !Qstartup.step1_passed )){
	
		Qstartup.step1=1;Qdata.HF_1_EN=1;
	
	}
	
	
	Qstartup.step1_passed=on_delay(Qstartup.step1,Qstartup.step1_passed,_2sec,&Qstartup.step1_counter);
	
	
	
	
	if((Qstartup.step1_passed & !Qdata.HF_2_CB_pos		& DI.CB_Operation_Qbasic & !Qstartup.step2_passed )){
		
		Qstartup.step2=1;Qdata.HF_2_EN=1;	
	
	}
	
		Qstartup.step2_passed=on_delay(Qstartup.step2,Qstartup.step2_passed,_2sec,&Qstartup.step2_counter);
	
		if(Qstartup.step2 & !DI.CB_Operation_Qbasic & !Qdata.HF_2_CB_pos){Qstartup.step2=0;}
	
	
	if( (Qstartup.step2_passed  & Qdata.HF_3_DSC_pos & (!Qdata.HF_3_CB_pos) & DI.CB_Operation_Qbasic & !Qstartup.step3_passed)){
		
		Qstartup.step3=1;Qdata.HF_3_EN =1;	
	
	}
	
	//Qstartup.step3_passed=on_delay(Qstartup.step3,Qstartup.step3_passed,_2sec,&Qstartup.step3_counter);
	
	if(Qstartup.step3 & !DI.CB_Operation_Qbasic & !Qdata.HF_3_CB_pos){Qstartup.step3=0;}
		
}else{
	
	Qstartup.step1=0;
	Qstartup.step2=0;
	Qstartup.step3=0;
	
	Qstartup.step1_passed=0;
	Qstartup.step2_passed=0; 

	Qstartup.step1_counter=0;
	Qstartup.step2_counter=0;

}




	/*CB closing in manual after startup*/

	
	
	
	
	Qbasic.ab=Qdata.BHF_1*fRMS.Vab*Qdata.HF_1_EN+
						Qdata.BHF_2*fRMS.Vab*Qdata.HF_2_EN+
						Qdata.BHF_3*fRMS.Vab*Qdata.HF_3_EN;
						
	Qbasic.bc=Qdata.BHF_1*fRMS.Vbc*Qdata.HF_1_EN*+
						Qdata.BHF_2*fRMS.Vbc*Qdata.HF_2_EN+
						Qdata.BHF_3*fRMS.Vbc*Qdata.HF_3_EN;

	Qbasic.ca=Qdata.BHF_1*fRMS.Vca*Qdata.HF_1_EN+
						Qdata.BHF_2*fRMS.Vca*Qdata.HF_2_EN+
						Qdata.BHF_3*fRMS.Vca*Qdata.HF_3_EN;
						
	
	Qbasic.mean=	(Qbasic.ab+Qbasic.bc+Qbasic.ca)*i3;				

	
}

	
	
	
	
	



