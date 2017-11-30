/*
*
*  Created on : 15.11.2017
*  Author : Baris
*
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
	
	float Vab;		
	float Vbc;		
	float Vca;		
	
	

}; 


extern struct AdcData adc;


union uAdc
{
  struct AdcData ch;
	float  bufferAdc[18];
		
};

extern union uAdc Adc;


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



struct references{

float final_Q;
float final_alpha;

};


extern struct references ref_ab;
extern struct references ref_bc;
extern struct references ref_ca;


struct stat{

	uint32_t MV_ready_flag:1;
	uint32_t start_flag:1;
	uint32_t Qbasic_flag:1;
	uint32_t regulation_enable:1;
	uint32_t current_limiting_pick_up:1;
	uint32_t current_limiting:1;
	uint32_t voltage_limiting_pick_up:1;
	uint32_t voltage_limiting:1;
	uint32_t cb_operation_flag:1;
	
};

extern struct stat status;

union statUnion{
	
	struct stat status;
	uint8_t all;
	
	
}; 

extern union statUnion uStatus;


struct fastRMS {

	float Vab;
	float Vbc;
	float Vca;

};

extern struct fastRMS fRMS;


struct QbasicOut{

float ab;
float bc;
float ca;
float mean;	
	


};

extern struct QbasicOut Qbasic ;

struct ClosedLoopPQ{

	float Psum;
	float Ptotal;

	float Qab_sum;
	float Qbc_sum;
	float Qca_sum;
	float Qsum;

	float Qab;
	float Qbc;
	float Qca;
	float Qtotal;

	uint16_t counter;

};

extern struct ClosedLoopPQ cl;



struct internal_fault{


 float 	limit;
 long 	 counter;
 uint16_t 	 pick_up:1;
 uint16_t 	 trip:1;		

};

extern struct internal_fault voltage_loss;


struct external_fault{
	
	long 	 counter;
	uint32_t 	 pick_up:1;
  uint32_t 	 all:1;		

};

extern struct external_fault extTrip;


struct fastPowerParameters{

	float Vlag;
	float Vlead;

	float Ilag;
	float Ilead;

};



extern struct fastPowerParameters fpp_ab;
extern struct fastPowerParameters fpp_bc;
extern struct fastPowerParameters fpp_ca;


struct OpenLoopQ{

	float a;
	float b;
	float c;

	float ab;
	float bc;
	float ca;

	float ab_f;
	float bc_f;
	float ca_f;

	float ref_ab;
	float ref_bc;
	float ref_ca;


};

extern struct OpenLoopQ Qol;


struct system_parameters{


	float TCR_XL_ab;
	float TCR_XL_bc;
	float TCR_XL_ca;


	float TR_Power;
	float TR_Ratio;
	float TR_Uk;

	float OL_ratio;
	float OL_ref_limit;



};

extern struct system_parameters sys;



#endif
