
#include "nfbm.h"
#include <math.h>

#define rms_channelNo 18
#define rms_period 500.0f
#define i_rms_period 1/rms_period 


struct AdcData meanRMS;
struct fastRMS fRMS;
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
	
}


void fast_RMS(void){



}
