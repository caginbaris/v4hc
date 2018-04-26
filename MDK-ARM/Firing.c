/*
*
*  Created on : 15.11.2017
*  Author : Baris
*
*/



#include "nfbm.h"
#include "firing.h"
#include "main.h"
#include "aux_functions.h"

struct firing_parameters fire;
struct firingOutputs fr={0};
union firingOutputsUnion ufr={0};

uint8_t firing_disable=1;


void init_firing(void){
	
sys.Alpha_limit_up=170.0f;
sys.Alpha_limit_down=95;	

}



void firing(){


	PLL.ab_deg=PLL.ab_rad*r2d+PLL_correction;
	PLL.bc_deg=PLL.bc_rad*r2d+PLL_correction;
	PLL.ca_deg=PLL.ca_rad*r2d+PLL_correction;

	if(PLL.ab_deg>360.0f){PLL.ab_deg=PLL.ab_deg-360.0f;}
	if(PLL.bc_deg>360.0f){PLL.bc_deg=PLL.bc_deg-360.0f;}
	if(PLL.ca_deg>360.0f){PLL.ca_deg=PLL.ca_deg-360.0f;}

	if(PLL.ab_deg<0){PLL.ab_deg=PLL.ab_deg+360;}
	if(PLL.bc_deg<0){PLL.bc_deg=PLL.bc_deg+360;}
	if(PLL.ca_deg<0){PLL.ca_deg=PLL.ca_deg+360;}



	fire.ab.alpha=ref_ab.final_alpha;
	fire.bc.alpha=ref_bc.final_alpha;
	fire.ca.alpha=ref_ca.final_alpha;

	f_limiter(&fire.ab.alpha,sys.Alpha_limit_down,sys.Alpha_limit_up);
	f_limiter(&fire.bc.alpha,sys.Alpha_limit_down,sys.Alpha_limit_up);
	f_limiter(&fire.ca.alpha,sys.Alpha_limit_down,sys.Alpha_limit_up);
	
	fire.ab.alpha_neg=ref_ab.final_alpha+180.0f;
	fire.bc.alpha_neg=ref_bc.final_alpha+180.0f;
	fire.ca.alpha_neg=ref_ca.final_alpha+180.0f;


	if(((fire.ab.p_fired==0) &&  PLL.ab_deg>(fire.ab.alpha+firing_offset3) && PLL.ab_deg<pos_limit)  || fire.ab.p_flag==1) 	{fire.ab.alpha= fire.ab.pre_alpha_p; fire.ab.p_flag=1;}
	if(((fire.bc.p_fired==0) &&  PLL.bc_deg>(fire.bc.alpha+firing_offset3) && PLL.bc_deg<pos_limit)  || fire.bc.p_flag==1) 	{fire.bc.alpha= fire.bc.pre_alpha_p; fire.bc.p_flag=1;}
	if(((fire.ca.p_fired==0) &&  PLL.ca_deg>(fire.ca.alpha+firing_offset3) && PLL.ca_deg<pos_limit)  || fire.ca.p_flag==1) 	{fire.ca.alpha= fire.ca.pre_alpha_p; fire.ca.p_flag=1;}


	if(((fire.ab.n_fired==0) && PLL.ab_deg>(fire.ab.alpha_neg+firing_offset3) && PLL.ab_deg<neg_limit) || fire.ab.n_flag==1)	{fire.ab.alpha_neg= fire.ab.pre_alpha_n;fire.ab.n_flag=1;}
	if(((fire.bc.n_fired==0) && PLL.bc_deg>(fire.bc.alpha_neg+firing_offset3) && PLL.bc_deg<neg_limit) || fire.bc.n_flag==1)	{fire.bc.alpha_neg= fire.bc.pre_alpha_n;fire.bc.n_flag=1;}
	if(((fire.ca.n_fired==0) && PLL.ca_deg>(fire.ca.alpha_neg+firing_offset3) && PLL.ca_deg<neg_limit) || fire.ca.n_flag==1)	{fire.ca.alpha_neg= fire.ca.pre_alpha_n;fire.ca.n_flag=1;}

	fire.ab.pre_alpha_p=fire.ab.alpha;
	fire.ab.pre_alpha_n=fire.ab.alpha_neg;

	fire.bc.pre_alpha_p=fire.bc.alpha;
	fire.bc.pre_alpha_n=fire.bc.alpha_neg;

	fire.ca.pre_alpha_p=fire.ca.alpha;
	fire.ca.pre_alpha_n=fire.ca.alpha_neg;
	

	if(status.start_flag==1){


		if((PLL.ab_deg>=fire.ab.alpha) && (PLL.ab_deg<=(fire.ab.alpha+firing_offset))) 		  									{fr.Ap=1;	fire.ab.p_fired=1;}
		if((PLL.ab_deg<(fire.ab.alpha-firing_offset2)) || (PLL.ab_deg>(fire.ab.alpha+firing_offset))) 				{fr.Ap=0;	fire.ab.p_fired=0;fire.ab.p_flag=0;}

		if((PLL.bc_deg>=fire.bc.alpha) && (PLL.bc_deg<=(fire.bc.alpha+firing_offset)))        								{fr.Bp=1;;	fire.bc.p_fired=1;}
		if((PLL.bc_deg<(fire.bc.alpha-firing_offset2)) || (PLL.bc_deg>(fire.bc.alpha+firing_offset))) 				{fr.Bp=0;  fire.bc.p_fired=0;fire.bc.p_flag=0;}

		if((PLL.ca_deg>=fire.ca.alpha) && (PLL.ca_deg<=(fire.ca.alpha+firing_offset))) 		  									{fr.Cp=1; fire.ca.p_fired=1;}
		if((PLL.ca_deg<(fire.ca.alpha-firing_offset2)) || (PLL.ca_deg>(fire.ca.alpha+firing_offset))) 				{fr.Cp=0;   fire.ca.p_fired=0;fire.ca.p_flag=0;}


		if((PLL.ab_deg>=fire.ab.alpha_neg) && (PLL.ab_deg<=(fire.ab.alpha_neg+firing_offset)))				  			{fr.An=1;   fire.ab.n_fired=1;}
		if((PLL.ab_deg<(fire.ab.alpha_neg-firing_offset2)) || (PLL.ab_deg>(fire.ab.alpha_neg+firing_offset))) {fr.An=0;   fire.ab.n_fired=0;fire.ab.n_flag=0;}

		if((PLL.bc_deg>=fire.bc.alpha_neg) && (PLL.bc_deg<=(fire.bc.alpha_neg+firing_offset)))								{fr.Bn=1;   fire.bc.n_fired=1;}
		if((PLL.bc_deg<(fire.bc.alpha_neg-firing_offset2)) || (PLL.bc_deg>(fire.bc.alpha_neg+firing_offset))) {fr.Bn=0;   fire.bc.n_fired=0;fire.bc.n_flag=0;}

		if((PLL.ca_deg>=fire.ca.alpha_neg) && (PLL.ca_deg<=(fire.ca.alpha_neg+firing_offset)))								{fr.Cn=1;   fire.ca.n_fired=1;}
		if((PLL.ca_deg<(fire.ca.alpha_neg-firing_offset2)) || (PLL.ca_deg>(fire.ca.alpha_neg+firing_offset))) {fr.Cn=0;   fire.ca.n_fired=0;fire.ca.n_flag=0;}


	}else{
		
		
		ufr.all=0;
		fr=ufr.fr;
				  
	}
	
	firingOutputs();

}


void firingOutputs(){
	
	HAL_GPIO_WritePin(FR_1_GPIO_Port,FR_1_Pin,fr.Ap);
	HAL_GPIO_WritePin(FR_4_GPIO_Port,FR_4_Pin,fr.An);
	
	HAL_GPIO_WritePin(FR_2_GPIO_Port,FR_2_Pin,fr.Bp);
	HAL_GPIO_WritePin(FR_5_GPIO_Port,FR_5_Pin,fr.Bn);
	
	HAL_GPIO_WritePin(FR_3_GPIO_Port,FR_3_Pin,fr.Cp);
	HAL_GPIO_WritePin(FR_6_GPIO_Port,FR_6_Pin,fr.Cn);

}












