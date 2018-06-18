

#ifndef __Qbasic_h
#define __Qbasic_h

#include <stdint.h>


#define i3   0.333333333333333f


struct QbasicData{

	float QHF_1;
	float QHF_2;
	float QHF_3;
	float QHF_4;
	float QHF_ext;
	
	float BHF_1;
	float BHF_2;
	float BHF_3;
	float BHF_4;
	float BHF_ext;
	
	float QTCR;

	
	uint32_t HF_1_CB_pos:1;
	uint32_t HF_2_CB_pos:1;
	uint32_t HF_3_CB_pos:1;
	uint32_t HF_4_CB_pos:1;
	
	
	uint32_t HF_1_DSC_pos:1;
	uint32_t HF_2_DSC_pos:1;
	uint32_t HF_3_DSC_pos:1;
	uint32_t HF_4_DSC_pos:1;
	
	
	uint32_t HF_1_EN:1;
	uint32_t HF_2_EN:1;
	uint32_t HF_3_EN:1;
	uint32_t HF_4_EN:1;
	
	uint32_t HF_ext_EN:1;

};


struct QbasicStartup{
	
	uint32_t  step1:1;
	uint32_t  step2:1;
	uint32_t  step3:1;
	
	uint32_t  step1_passed:1;
	uint32_t  step2_passed:1;
	uint32_t  step3_passed:1;
	
	long step1_counter;
	long step2_counter;
	long step3_counter;


};

extern struct QbasicData Qdata;

#endif

