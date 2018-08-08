/*
*Created on : 15.11.2017
*Author : Baris
*/



#include "stm32f7xx_hal.h"
#include "conversion.h"
#include "nfbm.h"
#include <string.h>

uint32_t adcBuffer[18]={0};
uint8_t conversion_completed={0};

union  uAdc Adc;


struct AdcData adc;
struct AdcData offset;
struct AdcData scale;
struct TurnRatios TR;

enum AdcChannel ch=Van;

void main_flow(void);

void init_conversion(){
	
offset.Ia=2048.912f;
offset.Ib=2046.18f;
offset.Ic=2046.07f;

offset.Itcr_ab=2048.1355f;
offset.Itcr_bc=2049.62451f;
offset.Itcr_ca=2049.42456f;

offset.Van=2047.76721;
offset.Vbn=2048.75928;
offset.Vcn=2048.46045;

offset.Vab_sync=2047.7207f;
offset.Vbc_sync=2047.88574;
offset.Vca_sync=2048.2373;
	
	
offset.Iload_a=2047.92834f;
offset.Iload_b=2048.66357f;
offset.Iload_c=2049.29785f;


	
scale.Ia=0.00553647988; 
scale.Ib=0.00553587245; 
scale.Ic=0.00552730489; 


scale.Itcr_ab=0.05621767484f;
scale.Itcr_bc=0.05609783462f;
scale.Itcr_ca=0.05623031939f;


scale.Van=0.1077999f;
scale.Vbn=0.1076202f;
scale.Vcn=0.1075999f;

scale.Vab_sync=0.114826f;
scale.Vbc_sync=0.114900f;
scale.Vca_sync=0.115300f;


scale.Iload_a=0.005535158698;
scale.Iload_b=0.005545000080;
scale.Iload_c=0.005543999840;


TR.VT_HV=345.0f;
TR.VT_MV=34.0f;
TR.CT_MV=4000.0f;
TR.CT_TCR=400.0f;
TR.CT_LOAD=600.0f;

	
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	

	
if(hadc->Instance==ADC1){
	
	HAL_GPIO_WritePin(DO_TEST_1_GPIO_Port,DO_TEST_1_Pin,GPIO_PIN_SET );
	
	
	Adc.ch.Van=			(adcBuffer[Van]-offset.Van)*scale.Van*TR.VT_MV;
	Adc.ch.Iload_a=	(adcBuffer[Iload_a]-offset.Iload_a)*scale.Iload_a*TR.CT_LOAD;
	Adc.ch.Ia=			(adcBuffer[Ia]-offset.Ia)*scale.Ia*TR.CT_MV;
	
	Adc.ch.Vbn=			(adcBuffer[Vbn]-offset.Vbn)*scale.Vbn*TR.VT_MV;
	Adc.ch.Iload_b=	(adcBuffer[Iload_b]-offset.Iload_b)*scale.Iload_b*TR.CT_LOAD;
	Adc.ch.Ib=			(adcBuffer[Ib]-offset.Ib)*scale.Ib*TR.CT_MV;
	
	Adc.ch.Vcn=			(adcBuffer[Vcn]-offset.Vcn)*scale.Vcn*TR.VT_MV;
	Adc.ch.Iload_c=	(adcBuffer[Iload_c]-offset.Iload_c)*scale.Iload_c*TR.CT_LOAD;
	Adc.ch.Itcr_bc=	(adcBuffer[Itcr_bc]-offset.Itcr_bc)*scale.Itcr_bc*TR.CT_TCR;
	
	Adc.ch.Ic=			(adcBuffer[Ic]-offset.Ic)*scale.Ic*TR.CT_MV;
	Adc.ch.Itcr_ab=	(adcBuffer[Itcr_ab]-offset.Itcr_ab)*scale.Itcr_ab*TR.CT_TCR;
	Adc.ch.Itcr_ca=	(adcBuffer[Itcr_ca]-offset.Itcr_ca)*scale.Itcr_ca*TR.CT_TCR;
	
	Adc.ch.Vab_sync=(adcBuffer[Vab_sync]-offset.Vab_sync)*scale.Vab_sync*TR.VT_HV;
	Adc.ch.Vbc_sync=(adcBuffer[Vbc_sync]-offset.Vbc_sync)*scale.Vbc_sync*TR.VT_HV;
	Adc.ch.Vca_sync=(adcBuffer[Vca_sync]-offset.Vca_sync)*scale.Vca_sync*TR.VT_HV;
	
	Adc.ch.Vab=			(Adc.ch.Van-Adc.ch.Vbn);
	Adc.ch.Vbc=			(Adc.ch.Vbn-Adc.ch.Vcn);
	Adc.ch.Vca=			(Adc.ch.Vcn-Adc.ch.Van);
	
	adc=Adc.ch;
	
	
	
	main_flow();
	
	HAL_GPIO_WritePin(DO_TEST_1_GPIO_Port,DO_TEST_1_Pin,GPIO_PIN_RESET );

	
	conversion_completed=1;
	
	}


}



