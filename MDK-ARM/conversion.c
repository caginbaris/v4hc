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


void init_conversion(){
union  uAdc init;		
uint8_t i=0;
	


for(i=0;i<18;i++){init.bufferAdc[i]=2048.0f;}	
offset=init.ch;	
for(i=0;i<18;i++){init.bufferAdc[i]=1.0f;}	
scale=init.ch;		
	
	
	
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	

	
if(hadc->Instance==ADC1){
	
	HAL_GPIO_WritePin(DO_TEST_1_GPIO_Port,DO_TEST_1_Pin,GPIO_PIN_SET );
	
	
	Adc.ch.Van=			(adcBuffer[Van]-offset.Van)*scale.Van;
	Adc.ch.Iload_a=	(adcBuffer[Iload_a]-offset.Iload_a)*scale.Iload_a;
	Adc.ch.Ia=			(adcBuffer[Ia]-offset.Ia)*scale.Ia;
	
	Adc.ch.Vbn=			(adcBuffer[Vbn]-offset.Vbn)*scale.Vbn;
	Adc.ch.Iload_b=	(adcBuffer[Iload_b]-offset.Iload_b)*scale.Iload_b;
	Adc.ch.Ib=			(adcBuffer[Ib]-offset.Ib)*scale.Ib;
	
	Adc.ch.Vcn=			(adcBuffer[Vcn]-offset.Vcn)*scale.Vcn;
	Adc.ch.Iload_c=	(adcBuffer[Iload_c]-offset.Iload_c)*scale.Iload_c;
	Adc.ch.Itcr_bc=	(adcBuffer[Itcr_bc]-offset.Itcr_bc)*scale.Itcr_bc;
	
	Adc.ch.Ic=			(adcBuffer[Ic]-offset.Ic)*scale.Ic;
	Adc.ch.Itcr_ab=	(adcBuffer[Itcr_ab]-offset.Itcr_ab)*scale.Itcr_ab;
	Adc.ch.Itcr_ca=	(adcBuffer[Itcr_ca]-offset.Itcr_ca)*scale.Itcr_ca;
	
	Adc.ch.Vab_sync=(adcBuffer[Vab_sync]-offset.Vab_sync)*scale.Vab_sync;
	Adc.ch.Vbc_sync=(adcBuffer[Vbc_sync]-offset.Vbc_sync)*scale.Vbc_sync;
	Adc.ch.Vca_sync=(adcBuffer[Vca_sync]-offset.Vca_sync)*scale.Vca_sync;
	
	Adc.ch.Vab=			(Adc.ch.Van-Adc.ch.Vbn);
	Adc.ch.Vbc=			(Adc.ch.Vbn-Adc.ch.Vcn);
	Adc.ch.Vca=			(Adc.ch.Vcn-Adc.ch.Van);
	
	adc=Adc.ch;
	
	conversion_completed=1;
	
	}


}
