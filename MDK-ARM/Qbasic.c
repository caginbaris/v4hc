
#include "Qbasic.h"
#include "nfbm.h"
#include "ios.h"


struct QbasicData Qdata={0};
struct QbasicOut Qbasic;


void init_Qbasic(void){
	
	

	Qdata.QHF_1=0.0f; /*entered from HMI side*/
	Qdata.QHF_2=0.0f; /*entered from HMI side*/
	Qdata.QHF_3=0.0f; /*entered from HMI side*/
	Qdata.QHF_4=0.0f; /*entered from HMI side*/
	
	Qdata.BHF_1=Qdata.QHF_1/(3.0f*Vnom*Vnom);
	Qdata.BHF_2=Qdata.QHF_2/(3.0f*Vnom*Vnom);
	Qdata.BHF_3=Qdata.QHF_3/(3.0f*Vnom*Vnom);
	Qdata.BHF_4=Qdata.QHF_4/(3.0f*Vnom*Vnom);
	

}

void Qbasic_calculation(){
	
	
	//HF_1------------------------------
	
	Qdata.HF_1_CB_pos=0;//DI. from MRB
	Qdata.HF_1_DSC_pos=0;//DI. from MRB
	Qdata.HF_1_DB_pos=0;//DI. from MRB
	
	
	Qdata.HF_1_EN=Qdata.HF_1_CB_pos & 
								Qdata.HF_1_DSC_pos&
								Qdata.HF_1_DB_pos;
	
	//HF_2-----------------------------
	
	Qdata.HF_2_CB_pos=0;//DI. from MRB
	Qdata.HF_2_DSC_pos=0;//DI. from MRB
	Qdata.HF_2_DB_pos=0;//DI. from MRB
	
	
	Qdata.HF_2_EN=Qdata.HF_2_CB_pos & 
								Qdata.HF_2_DSC_pos&
								Qdata.HF_2_DB_pos;
								
								
	//HF_3----------------------------
	
	Qdata.HF_3_CB_pos=0;//DI. from MRB
	Qdata.HF_3_DSC_pos=0;//DI. from MRB
	Qdata.HF_3_DB_pos=0;//DI. from MRB
	
	
	Qdata.HF_3_EN=Qdata.HF_3_CB_pos & 
								Qdata.HF_3_DSC_pos&
								Qdata.HF_3_DB_pos;							
	
	//---------------------------------
	
	
	
	
	Qbasic.ab=Qdata.BHF_1*fRMS.Vab*Qdata.HF_1_EN+
						Qdata.BHF_2*fRMS.Vab*Qdata.HF_2_EN+
						Qdata.BHF_3*fRMS.Vab*Qdata.HF_3_EN;
						
	Qbasic.bc=Qdata.BHF_1*fRMS.Vbc*Qdata.HF_1_EN+
						Qdata.BHF_2*fRMS.Vbc*Qdata.HF_2_EN+
						Qdata.BHF_3*fRMS.Vbc*Qdata.HF_3_EN;

	Qbasic.ca=Qdata.BHF_1*fRMS.Vca*Qdata.HF_1_EN+
						Qdata.BHF_2*fRMS.Vca*Qdata.HF_2_EN+
						Qdata.BHF_3*fRMS.Vca*Qdata.HF_3_EN;
						
	
	Qbasic.mean=	(Qbasic.ab+Qbasic.bc+Qbasic.ca)*i3;				

	
}

	
	
	
	
	



