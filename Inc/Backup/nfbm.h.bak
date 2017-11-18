/*
*Created on : 15.11.2017
*Author : Baris
*/

#ifndef __nfbm_h
#define __nfbm_h

#include "stdint.h"


struct AdcData{
	
	float Van; 				//AN-1
	float Iload_a;		//AN-13
	float Ia;					//AN-2
	
	float Vbn;				//AN-3
	float Iload_b;		//AN-14
	float Ib;					//AN-4
	
	float Vcn;				//AN-5
	float Iload_c;		//AN-15
	float Itcr_bc;		//AN-11
	
	float Ic;					//AN-6
	float Itcr_ab;		//AN-10
	float Itcr_ca;		//A-N12
	
	float Vab_sync;		//AN-7
	float Vbc_sync;		//AN-8
	float Vca_sync;		//AN-9
	
	float Vab;		//AN-7
	float Vbc;		//AN-8
	float Vca;		//AN-9
	
	

}; 


extern struct AdcData adc;


union unionAdc
{
  struct AdcData ch;
	float  bufferAdc[18];
		
};

extern union unionAdc Adc;


enum AdcChannel{

	Van=0, 				//AN-1
	Iload_a=1,		//AN-13
	Ia=2,					//AN-2
	
	Vbn=3,				//AN-3
	Iload_b=4,		//AN-14
	Ib=5,					//AN-4
	
	Vcn=6,				//AN-5
	Iload_c=7,		//AN-15
	Itcr_bc=8,		//AN-11
	
	Ic=9,					//AN-6
	Itcr_ab=10,		//AN-10
	Itcr_ca=11,		//A-N12
	
	Vab_sync=12,	//AN-7
	Vbc_sync=13,	//AN-8
	Vca_sync=15,	//AN-9
	


};


struct PhaseLockedLoop{

	float ab_rad;
	float bc_rad;
	float ca_rad;
	
	float ab_deg;
	float bc_deg;
	float ca_deg;

};

extern struct PhaseLockedLoop PLL;

struct control_loops{

	float Qref;


	struct{

		float Kp;
		float Ki;
		float plimit;
		float nlimit;

		struct{float Qin;float error;float Pout;float Iout;float PIout;}ab;
		struct{float Qin;float error;float Pout;float Iout;float PIout;}bc;
		struct{float Qin;float error;float Pout;float Iout;float PIout;}ca;

	}CL;

	struct{

		float Kp;
		float Ki;
		float plimit;
		float nlimit;
		float error;
		float Pout;
		float Iout;
		float PIout;
		float Qin;

	}OL;


};


extern struct control_loops PI;

struct firing_parameters{




	float alpha_limit_up;
	float alpha_limit_down;

	float overload_alpha;
	float nominal_alpha;




	struct{

		float alpha;
		float alpha_neg;
		float pre_alpha_p;
		float pre_alpha_n;

		uint8_t  p_fired:1;
		uint8_t n_fired:1;
		uint8_t p_flag:1;
		uint8_t n_flag:1;

	}ab;



	struct{

		float alpha;
		float alpha_neg;
		float pre_alpha_p;
		float pre_alpha_n;

		uint8_t p_fired:1;
		uint8_t n_fired:1;
		uint8_t p_flag:1;
		uint8_t n_flag:1;

	}bc;



	struct{

		float alpha;
		float alpha_neg;
		float pre_alpha_p;
		float pre_alpha_n;

		uint8_t p_fired:1;
		uint8_t n_fired:1;
		uint8_t p_flag:1;
		uint8_t n_flag:1;

	}ca;



};

extern struct firing_parameters fire;










#endif
