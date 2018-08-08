
#include "nfbm.h"
#include <math.h>
#include "time_constants.h"
#include "plf_constants.h"
#include "aux_functions.h"

#define rms_channelNo 18
#define rms_sample 500 
#define rms_period 500.0f
#define i_rms_period 1.0f/rms_period 
#define rms_div3 0.3333333333333f
#define c_rms_time _10sec
#define c_rms_div  1.0f/c_rms_time


struct AdcData meanRMS={0};
struct fastRMS fRMS={0};
float  cRMS=0;
union  uAdc meanRMS_sum={0};
uint8_t cEN=0;
long cEN_counter=0;



void mean_RMS(union uAdc in,struct AdcData *out){
	
	static uint16_t counter=0;
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
	
	if(++counter==rms_sample){counter=0;}
	
}


float plf_rms_ab(float x){

	static float xfz1=0,xfz2=0;
	static float yf=0,yfz1=0,yfz2=0;

	static float xsz1=0,xsz2=0;
	static float ys=0,ysz1=0,ysz2=0;



	yf=(bf0*x)+(bf1*xfz1)+(bf2*xfz2)+(af1*yfz1)+(af2*yfz2);

	xfz2=xfz1;
	xfz1=x;

	yfz2=yfz1;
	yfz1=yf;


	ys=(bs0*yf)+(bs1*xsz1)+(bs2*xsz2)+(as1*ysz1)+(as2*ysz2);

	xsz2=xsz1;
	xsz1=yf;

	ysz2=ysz1;
	ysz1=ys;


	return ys*peu;

}


float plf_rms_bc(float x){

	static float xfz1=0,xfz2=0;
	static float yf=0,yfz1=0,yfz2=0;

	static float xsz1=0,xsz2=0;
	static float ys=0,ysz1=0,ysz2=0;



	yf=(bf0*x)+(bf1*xfz1)+(bf2*xfz2)+(af1*yfz1)+(af2*yfz2);

	xfz2=xfz1;
	xfz1=x;

	yfz2=yfz1;
	yfz1=yf;


	ys=(bs0*yf)+(bs1*xsz1)+(bs2*xsz2)+(as1*ysz1)+(as2*ysz2);

	xsz2=xsz1;
	xsz1=yf;

	ysz2=ysz1;
	ysz1=ys;


	return ys*peu;

}

float plf_rms_ca(float x){

	static float xfz1=0,xfz2=0;
	static float yf=0,yfz1=0,yfz2=0;

	static float xsz1=0,xsz2=0;
	static float ys=0,ysz1=0,ysz2=0;



	yf=(bf0*x)+(bf1*xfz1)+(bf2*xfz2)+(af1*yfz1)+(af2*yfz2);

	xfz2=xfz1;
	xfz1=x;

	yfz2=yfz1;
	yfz1=yf;


	ys=(bs0*yf)+(bs1*xsz1)+(bs2*xsz2)+(as1*ysz1)+(as2*ysz2);

	xsz2=xsz1;
	xsz1=yf;

	ysz2=ysz1;
	ysz1=ys;


	return ys*peu;

}


void fast_RMS(void){
	
	

	
	
fRMS.Vab_raw=(fpp_ab.Vlag*fpp_ab.Vlag + fpp_ab.Vlead*fpp_ab.Vlead)*0.5f;
fRMS.Vbc_raw=(fpp_bc.Vlag*fpp_bc.Vlag + fpp_bc.Vlead*fpp_bc.Vlead)*0.5f;
fRMS.Vca_raw=(fpp_ca.Vlag*fpp_ca.Vlag + fpp_ca.Vlead*fpp_ca.Vlead)*0.5f;

fRMS.Vab=plf_rms_ab(fRMS.Vab_raw);	
fRMS.Vbc=plf_rms_bc(fRMS.Vbc_raw);
fRMS.Vca=plf_rms_ca(fRMS.Vca_raw);
	
	
}

void correction_RMS(void){
	
	static uint32_t counter=0;
	static float average_sum=0;
	float average;
	
	
	average=(meanRMS.Ia+meanRMS.Ib+meanRMS.Ic)*0.33333333f;
	average_sum+=average;
	
	if(++counter>=250000){
		
		
	cRMS=average_sum*0.000004f;
	average_sum=0;	
	counter=0;	
	
	}
	
	
	cEN=on_off_delay((average<150.0f),cEN,2500,&cEN_counter);
	
	if(cEN){
	
	cRMS=0;
	
	}
	
	
	

}

void RMS_all(void){
	
	mean_RMS(Adc,&meanRMS);
	fast_RMS();
	correction_RMS();
	
	

}


float averager(){
	
	
	static uint32_t count=0;
	static float sum=0;
	static float x=0;
	
	sum+=Adc.bufferAdc[ch];
	
	if(++count==125000){
	
		x=sum/125000.0f;
		sum=0;
		count=0;
	}
	
	return x;

}



