
#include "nfbm.h"
#include <math.h>
#include "time_constants.h"

#define rms_channelNo 18
#define rms_period 500.0f
#define i_rms_period 1/rms_period 
#define rms_div3 0.3333333333333f
#define c_rms_time _10sec
#define c_rms_div  1/c_rms_time


struct AdcData meanRMS={0};
struct fastRMS fRMS;
float  cRMS=0;
union  uAdc meanRMS_sum={0};


void mean_RMS(union uAdc in,struct AdcData *out){
	
	static uint8_t counter=0;
	uint8_t i;
	
	
	for(i=0;i<rms_channelNo;i++)
  {
		
		meanRMS_sum.bufferAdc[i]+=in.bufferAdc[i]*in.bufferAdc[i];
		
  }
	
	
	switch (counter)
	{
		case 0: out->Van=sqrtf(meanRMS_sum.ch.Van*i_rms_period);meanRMS_sum.ch.Van=0.0f;break;
		case 1: out->Vbn=sqrtf(meanRMS_sum.ch.Vbn*i_rms_period);meanRMS_sum.ch.Vbn=0.0f;break;
		case 2: out->Vcn=sqrtf(meanRMS_sum.ch.Vcn*i_rms_period);meanRMS_sum.ch.Vcn=0.0f;break;
		
		case 3: out->Vab=sqrtf(meanRMS_sum.ch.Vab*i_rms_period);meanRMS_sum.ch.Vab=0.0f;break;
		case 4: out->Vbc=sqrtf(meanRMS_sum.ch.Vbc*i_rms_period);meanRMS_sum.ch.Vbc=0.0f;break;
		case 5: out->Vca=sqrtf(meanRMS_sum.ch.Vca*i_rms_period);meanRMS_sum.ch.Vca=0.0f;break;
		
		case 6: out->Ia=sqrtf(meanRMS_sum.ch.Ia*i_rms_period);meanRMS_sum.ch.Ia=0.0f;break;
		case 7: out->Ib=sqrtf(meanRMS_sum.ch.Ib*i_rms_period);meanRMS_sum.ch.Ib=0.0f;break;
		case 8: out->Ic=sqrtf(meanRMS_sum.ch.Ic*i_rms_period);meanRMS_sum.ch.Ic=0.0f;break;
		
		case 9:  out->Iload_a=sqrtf(meanRMS_sum.ch.Iload_a*i_rms_period);meanRMS_sum.ch.Iload_a=0.0f;break;
		case 10: out->Iload_b=sqrtf(meanRMS_sum.ch.Iload_b*i_rms_period);meanRMS_sum.ch.Iload_b=0.0f;break;
		case 11: out->Iload_c=sqrtf(meanRMS_sum.ch.Iload_c*i_rms_period);meanRMS_sum.ch.Iload_c=0.0f;break;
		
		case 12: out->Vab_sync=sqrtf(meanRMS_sum.ch.Vab_sync*i_rms_period);meanRMS_sum.ch.Vab_sync=0.0f;break;
		case 13: out->Vbc_sync=sqrtf(meanRMS_sum.ch.Vbc_sync*i_rms_period);meanRMS_sum.ch.Vbc_sync=0.0f;break;
		case 14: out->Vca_sync=sqrtf(meanRMS_sum.ch.Vca_sync*i_rms_period);meanRMS_sum.ch.Vca_sync=0.0f;break;
		
		case 15: out->Itcr_ab=sqrtf(meanRMS_sum.ch.Itcr_ab*i_rms_period);meanRMS_sum.ch.Itcr_ab=0.0f;break;
		case 16: out->Itcr_bc=sqrtf(meanRMS_sum.ch.Itcr_bc*i_rms_period);meanRMS_sum.ch.Itcr_bc=0.0f;break;
		case 17: out->Itcr_ca=sqrtf(meanRMS_sum.ch.Itcr_ca*i_rms_period);meanRMS_sum.ch.Itcr_ca=0.0f;break;
		

  }
	
	if(++counter==rms_channelNo){counter=0;}
	
}


void fast_RMS(void){
	
	
fRMS.Vab=(fpp_ab.Vlag*fpp_ab.Vlag + fpp_ab.Vlead*fpp_ab.Vlead)*0.5f;
fRMS.Vbc=(fpp_bc.Vlag*fpp_bc.Vlag + fpp_bc.Vlead*fpp_bc.Vlead)*0.5f;
fRMS.Vca=(fpp_ca.Vlag*fpp_ca.Vlag + fpp_ca.Vlead*fpp_ca.Vlead)*0.5f;



}

void correction_RMS(void){
	
	static uint32_t counter=0;
	static float average_sum=0;
	float average;
	
	average=(meanRMS.Ia+meanRMS.Ib+meanRMS.Ic)*rms_div3;
	average_sum+=average;
	
	if(++counter==c_rms_time){
		
		
	cRMS=average_sum*c_rms_div;
	average_sum=0;	
	counter=0;	
	
	}
	

}

void RMS_all(void){
	
	mean_RMS(Adc,&meanRMS);
	fast_RMS();
	correction_RMS();
	
	

}
