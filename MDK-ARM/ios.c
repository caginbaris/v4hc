

#include "main.h"
#include "stm32f7xx_hal.h"
#include "ios.h"
#include "nfbm.h"

struct 	digitalInputs DI={0};
struct 	digitalOutputs DO={0};
union 	digitalInputsUnion uDI={0};
union 	digitalOutputsUnion uDO={0};


void ios(void){
	
	
	DI.start_stop					=HAL_GPIO_ReadPin(START_STOP_DI_1_GPIO_Port,START_STOP_DI_1_Pin);
	DI.Q1_cb_pos 					=HAL_GPIO_ReadPin(Q1_CB_POS_DI_2_GPIO_Port,Q1_CB_POS_DI_2_Pin);
	DI.Q2_cb_pos 					=HAL_GPIO_ReadPin(Q2_CB_POS_DI_3_GPIO_Port,Q2_CB_POS_DI_3_Pin);
	DI.Q3_cb_pos 					=HAL_GPIO_ReadPin(Q3_CB_POS_DI_4_GPIO_Port,Q3_CB_POS_DI_4_Pin);
	DI.EAF1_cb_pos 				=HAL_GPIO_ReadPin(EAF1_CB_POS_DI_5_GPIO_Port,EAF1_CB_POS_DI_5_Pin);
	DI.EAF2_cb_pos 				=HAL_GPIO_ReadPin(EAF2_CB_POS_DI_7_GPIO_Port,EAF2_CB_POS_DI_7_Pin);
	DI.EAF3_cb_pos 				=HAL_GPIO_ReadPin(EAF3_CB_POS_DI_6_GPIO_Port,EAF3_CB_POS_DI_6_Pin );
	DI.LF1_cb_pos					=HAL_GPIO_ReadPin(LF1_CB_POS_DI8_GPIO_Port,LF1_CB_POS_DI8_Pin);
	DI.LF2_cb_pos					=HAL_GPIO_ReadPin(LF2_CB_POS_DI_9_GPIO_Port,LF2_CB_POS_DI_9_Pin);
	DI.LF3_cb_pos					=HAL_GPIO_ReadPin(LF3_CB_POS_DI_11_GPIO_Port,LF3_CB_POS_DI_11_Pin);
	DI.SVC_TRIP						=HAL_GPIO_ReadPin(SVC_TRIP_DI_10_GPIO_Port,SVC_TRIP_DI_10_Pin);
	DI.Q1_open_ctb 				=HAL_GPIO_ReadPin(Q1_CB_OPEN_DI_12_GPIO_Port,Q1_CB_OPEN_DI_12_Pin);
	DI.Q2_open_ctb 				=HAL_GPIO_ReadPin(Q2_CB_OPEN_DI_14_GPIO_Port,Q2_CB_OPEN_DI_14_Pin);
	DI.Q3_open_ctb 				=HAL_GPIO_ReadPin(Q3_CB_OPEN_DI_16_GPIO_Port,Q3_CB_OPEN_DI_16_Pin);
	DI.Q1_trip_ctb				=HAL_GPIO_ReadPin(Q1_CB_TRIP_DI_13_GPIO_Port,Q1_CB_TRIP_DI_13_Pin);
	DI.Q2_trip_ctb				=HAL_GPIO_ReadPin(Q2_CB_TRIP_DI_15_GPIO_Port,Q2_CB_TRIP_DI_15_Pin);
	DI.Q3_trip_ctb				=HAL_GPIO_ReadPin(Q3_CB_TRIP_DI_17_GPIO_Port,Q3_CB_TRIP_DI_17_Pin);
	DI.Q10_ds_pos					=HAL_GPIO_ReadPin(DI_52_DI_19_GPIO_Port,DI_52_DI_19_Pin);
	DI.Q20_ds_pos					=HAL_GPIO_ReadPin(DI_53_DI_20_GPIO_Port,DI_53_DI_20_Pin);
	DI.Q31_ds_pos					=HAL_GPIO_ReadPin(DI_54_DI_21_GPIO_Port,DI_54_DI_21_Pin);
	DI._55								=HAL_GPIO_ReadPin(DI_55_DI_22_GPIO_Port,DI_55_DI_22_Pin);
	DI._56								=HAL_GPIO_ReadPin(DI_56_DI_23_GPIO_Port,DI_56_DI_23_Pin);
	DI.BusVoltageSelect 	=HAL_GPIO_ReadPin(Bus_Voltage_Selection_DI_24_GPIO_Port,Bus_Voltage_Selection_DI_24_Pin);
	DI._2HF_Operation	    =HAL_GPIO_ReadPin(_2HF_Operation_DI_26_GPIO_Port,_2HF_Operation_DI_26_Pin);
	DI.Commisioning				=HAL_GPIO_ReadPin(Commisioning_DI_25_GPIO_Port,Commisioning_DI_25_Pin);
	DI.CB_Operation_Qbasic=HAL_GPIO_ReadPin(CB_Operation_Qbasic_DI_28_GPIO_Port,CB_Operation_Qbasic_DI_28_Pin);
	DI.PLB_INT_DO_SPARE4	=HAL_GPIO_ReadPin(PLB_INT_DI_SP4_DI_27_GPIO_Port,PLB_INT_DI_SP4_DI_27_Pin);
	DI.PLB_INT_DO_SPARE6	=HAL_GPIO_ReadPin(PLB_INT_DI_SP6_DI_29_GPIO_Port,PLB_INT_DI_SP6_DI_29_Pin);
	DI.reset							=HAL_GPIO_ReadPin(DI_RESET_GPIO_Port,DI_RESET_Pin);
	
	
	DO.IBF=1;
	DO.LD_IBF=1;
	
	HAL_GPIO_WritePin(CTB1_READY_DO_1_GPIO_Port,CTB1_READY_DO_1_Pin,(GPIO_PinState)DO.READY);
	HAL_GPIO_WritePin(CTB1_RUN_DO_2_GPIO_Port  ,CTB1_RUN_DO_2_Pin,  (GPIO_PinState)DO.RUN);
	HAL_GPIO_WritePin(CTB1_IBF_DO_5_GPIO_Port,CTB1_IBF_DO_5_Pin, 		(GPIO_PinState)DO.IBF); //cau wrong  pin init
	HAL_GPIO_WritePin(CTB1_StartComp_DO_4_GPIO_Port,CTB1_StartComp_DO_4_Pin,	(GPIO_PinState)DO.StartupCompleted);
	
	HAL_GPIO_WritePin(LD_IBF_GPIO_Port,LD_IBF_Pin,(GPIO_PinState)DO.LD_IBF);
	HAL_GPIO_WritePin(LD_READY_GPIO_Port,LD_READY_Pin,	(GPIO_PinState)DO.LD_READY);
	HAL_GPIO_WritePin(LD_RUN_GPIO_Port,LD_RUN_Pin,(GPIO_PinState)DO.LD_RUN);
	
	
	

	
	cb_pos.all=0;
	
	if(DI.Furnace3_SWT){
	
	cb_pos.bit.eaf1=DI.EAF1_cb_pos; 
	cb_pos.bit.eaf2=DI.EAF2_cb_pos;
	cb_pos.bit.eaf3=DI.EAF3_cb_pos;
	
	cb_pos.bit.lf1=DI.LF1_cb_pos; 
	cb_pos.bit.lf2=DI.LF2_cb_pos;
	cb_pos.bit.lf3=DI.LF3_cb_pos;
		
	cb_pos.bit.q2=DI.Q2_cb_pos;
	cb_pos.bit.q3=DI.Q3_cb_pos;			
	
	}else{
		
	cb_pos.bit.eaf1=DI.EAF1_cb_pos; 
	cb_pos.bit.eaf3=DI.EAF3_cb_pos;
	
	cb_pos.bit.lf1=DI.LF1_cb_pos; 
	cb_pos.bit.lf2=DI.LF2_cb_pos;
		
	cb_pos.bit.q2=DI.Q2_cb_pos;
	cb_pos.bit.q3=DI.Q3_cb_pos;			

	}
	
}

