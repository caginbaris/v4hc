
#ifndef __main_flow_h
#define __main_flow_h


void PLL_all(void);
void RMS_all(void);
void Qbasic_calculation(void);
void PowerCalculations(void);
void state_chart(void);
void mode_chart(void);

void faultRoutines(void);
void tripRoutines(void);
void protection_handling();

void ios(void);
void firing(void);
void pushDataToMaster(void);
void lead_lag_calculation(void);
void Q2alpha_transforms(void);
void ref_basic(void);

void current_limiter(void);
void voltage_limiter(void);

void level_check_startup(void);


#endif
