

#ifndef __ios_h
#define __ios_h

#include <stdint.h>

struct digitalInputs{

	uint32_t start_stop:1; 					// DI-1
	uint32_t Q1_cb_pos:1;						// DI-2
	uint32_t Q2_cb_pos:1;						// DI-3
	uint32_t Q3_cb_pos:1;						// DI-4	
	uint32_t EAF1_cb_pos:1;					// DI-5	
	uint32_t EAF3_cb_pos:1;					// DI-6
	uint32_t EAF2_cb_pos:1;					// DI-7
	uint32_t LF1_cb_pos:1;					// DI-8
	uint32_t LF2_cb_pos:1;					// DI-9
	uint32_t SVC_TRIP:1;						// DI-10
	uint32_t LF3_cb_pos:1;					// DI-11
	uint32_t Q1_open_ctb:1;					// DI-12
	uint32_t Q1_trip_ctb:1;					// DI-13
	uint32_t Q2_open_ctb:1;					// DI-14
	uint32_t Q2_trip_ctb:1;					// DI-15
	uint32_t Q3_open_ctb:1;					// DI-16
	uint32_t Q3_trip_ctb:1;					// DI-17
	uint32_t Furnace3_SWT:1;				// DI-18
	uint32_t Q10_ds_pos:1;					// DI-19-E->52
	uint32_t Q20_ds_pos:1;					// DI-20-E->53
	uint32_t Q31_ds_pos:1;					// DI-21-E->54
	uint32_t _55:1;									// DI-22-E->55
	uint32_t _56:1;									// DI-23-E->56
	uint32_t BusVoltageSelect:1;		// DI-24
	
	uint32_t Commisioning:1;				// DI-25
	uint32_t _2HF_Operation:1;			// DI-26
	uint32_t PLB_INT_DO_SPARE4:1;		// DI-27
	uint32_t CB_Operation_Qbasic:1;	// DI-28
	uint32_t PLB_INT_DO_SPARE6:1;		// DI-29
	
	
	uint32_t reset:1;		//PE10

};


extern struct digitalInputs DI;


union digitalInputsUnion  {

	struct digitalInputs DI;
	uint32_t all;


};

extern union digitalInputsUnion uDI;



struct digitalOutputs{
	
	uint32_t READY:1;							// DO-1
	uint32_t RUN:1;								// DO-2
	uint32_t IBF:1;								// DO-3
	uint32_t StartupCompleted:1;	// DO-4
	uint32_t Spare1:1;						// DO-5
	uint32_t Spare2:1;						// DO-6
	uint32_t boardSPARE:10;				// DO-7...16
	
	uint32_t LD_IBF:1;						// Board Ind. Output Upper
	uint32_t LD_READY:1;					// Board Ind. Output Mid
	uint32_t LD_RUN:1;						// Board Ind. Output Bot
	
	
	

};


extern struct digitalOutputs DO;

union digitalOutputsUnion  {

	struct digitalOutputs DO;
	uint32_t all;


};


extern union digitalOutputsUnion uDO;


#endif

