

#include "main.h"
#include "stm32f7xx_hal.h"
#include "ios.h"



void ios(void){
	
	
	DI.start_stop		=HAL_GPIO_ReadPin(START_STOP_DI_1_GPIO_Port,START_STOP_DI_1_Pin);
	DI.Q1_cb_pos 		=HAL_GPIO_ReadPin(Q1_CB_POS_DI_2_GPIO_Port,Q1_CB_POS_DI_2_Pin);
	DI.Q2_cb_pos 		=HAL_GPIO_ReadPin(Q2_CB_POS_DI_3_GPIO_Port,Q2_CB_POS_DI_3_Pin);
	DI.Q3_cb_pos 		=HAL_GPIO_ReadPin(Q3_CB_POS_DI_4_GPIO_Port,Q3_CB_POS_DI_4_Pin);
	DI.EAF1_cb_pos 	=HAL_GPIO_ReadPin(EAF1_CB_POS_DI_5_GPIO_Port,EAF1_CB_POS_DI_5_Pin);
	DI.EAF2_cb_pos 	=HAL_GPIO_ReadPin(EAF2_CB_POS_DI_7_GPIO_Port,EAF2_CB_POS_DI_7_Pin);
	DI.EAF3_cb_pos 	=HAL_GPIO_ReadPin(EAF3_CB_POS_DI_6_GPIO_Port,EAF3_CB_POS_DI_6_Pin );
	DI.LF1_cb_pos		=HAL_GPIO_ReadPin(LF1_CB_POS_DI8_GPIO_Port,LF1_CB_POS_DI8_Pin);
	DI.LF2_cb_pos		=HAL_GPIO_ReadPin(LF2_CB_POS_DI_9_GPIO_Port,LF2_CB_POS_DI_9_Pin);
	DI.LF3_cb_pos		=HAL_GPIO_ReadPin(LF3_CB_POS_DI_11_GPIO_Port,LF3_CB_POS_DI_11_Pin);
	DI.SVC_TRIP			=HAL_GPIO_ReadPin(SVC_TRIP_DI_10_GPIO_Port,SVC_TRIP_DI_10_Pin);
	DI.Q1_open_ctb 	=HAL_GPIO_ReadPin(Q1_CB_OPEN_DI_12_GPIO_Port,Q1_CB_OPEN_DI_12_Pin);
	DI.Q2_open_ctb 	=HAL_GPIO_ReadPin(Q2_CB_OPEN_DI_14_GPIO_Port,Q2_CB_OPEN_DI_14_Pin);
	DI.Q3_open_ctb 	=HAL_GPIO_ReadPin(Q3_CB_OPEN_DI_16_GPIO_Port,Q3_CB_OPEN_DI_16_Pin);
	DI.Q1_trip_ctb	=HAL_GPIO_ReadPin(Q1_CB_TRIP_DI_13_GPIO_Port,Q1_CB_TRIP_DI_13_Pin);
	DI.Q2_trip_ctb	=HAL_GPIO_ReadPin(Q2_CB_TRIP_DI_15_GPIO_Port,Q2_CB_TRIP_DI_15_Pin);
	DI.Q3_trip_ctb	=HAL_GPIO_ReadPin(Q3_CB_TRIP_DI_17_GPIO_Port,Q3_CB_TRIP_DI_17_Pin);
	DI._52					=HAL_GPIO_ReadPin(DI_52_DI_19_GPIO_Port,DI_52_DI_19_Pin);
	DI._53					=HAL_GPIO_ReadPin(DI_53_DI_20_GPIO_Port,DI_53_DI_20_Pin);
	DI._54					=HAL_GPIO_ReadPin(DI_54_DI_21_GPIO_Port,DI_54_DI_21_Pin);
	
	
	

	
}

