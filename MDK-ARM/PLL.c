/*
 * PLL_calculation.c
 *
 *  Created on: 10 May 2015
 *      Author: Baris
 */

#include <math.h>
#include "nfbm.h"

#include "stm32f7xx_hal.h"
#include "main.h"


#define PI_limit 3.1415926535f
#define wi_pll   314.15926535f
#define _2pi 			6.2831853071f
#define Kp_pll 		0.0015f
#define Ki_pll 		0.05f;



struct PhaseLockedLoop PLL={0.0f};

float dq_filter_buffer[12]={0.0f};
float integral_buffer[6]={0.0f};




float PLL_theta (float Valpha_pll, float wt_pll,int index){

	float Vbeta_pll=0.0f;
	float Vd_pll=0.0f,Vq_pll=0.0f;
	float Vd_pll_filt=0.0f, Vq_pll_filt=0.0f;
	float P_pll=0.0f, I_pll=0.0f, PI_pll=0.0f;
	int integral_index=0.0f;
	float theta_pll=0.0f;




	integral_index=2*index-1;
	index=4*index-3;


	Vd_pll= Valpha_pll*cosf(wt_pll) + Vbeta_pll*sinf(wt_pll);
	Vq_pll=-Valpha_pll*sinf(wt_pll) + Vbeta_pll*cosf(wt_pll);

	Vd_pll_filt=dq_filter_buffer[index-1]*(0.9950f)+(Vd_pll + dq_filter_buffer[index])*0.0025f;
	dq_filter_buffer[index-1]=Vd_pll_filt;
	dq_filter_buffer[index]=Vd_pll;

	Vq_pll_filt=dq_filter_buffer[index+1]*(0.9950f)+(Vq_pll + dq_filter_buffer[index+2])*0.0025f;
	dq_filter_buffer[index+1]=Vq_pll_filt;
	dq_filter_buffer[index+2]=Vq_pll;

	Vbeta_pll=Vd_pll_filt*sinf(wt_pll)+Vq_pll_filt*cosf(wt_pll);


	P_pll = Vd_pll_filt * Kp_pll;

	I_pll=integral_buffer[integral_index-1];
	I_pll = I_pll + Vd_pll_filt * (0.00004f) * Ki_pll;

	if(I_pll> wi_pll){I_pll = I_pll-wi_pll;}
	if(I_pll<-wi_pll){I_pll = I_pll+wi_pll;}

	integral_buffer[integral_index-1]=I_pll;

	PI_pll = P_pll + I_pll;



	theta_pll=integral_buffer[integral_index];
	theta_pll=theta_pll+0.00004f*(PI_pll+wi_pll);

	if(theta_pll>_2pi){theta_pll  = theta_pll-_2pi;}
	if(theta_pll<0.0f)	 {theta_pll = theta_pll+_2pi;}

	integral_buffer[integral_index]=theta_pll;




	return theta_pll;

}


void PLL_all(void){

		//cau scale to 400V rms with 90.0f
    PLL.ab_rad=PLL_theta(adc.Vab_sync ,PLL.ab_rad,1);
    PLL.bc_rad=PLL_theta(adc.Vbc_sync,PLL.bc_rad,2);
    PLL.ca_rad=PLL_theta(adc.Vca_sync,PLL.ca_rad,3);
	
		if(PLL.ab_rad>0.0f &&PLL.ab_rad<0.5f*3.14159f){
		
			HAL_GPIO_WritePin(DO_TEST_2_GPIO_Port,DO_TEST_2_Pin,GPIO_PIN_SET);
			
		}else{
			
			HAL_GPIO_WritePin(DO_TEST_2_GPIO_Port,DO_TEST_2_Pin,GPIO_PIN_RESET);
		
		}
	
	

}
