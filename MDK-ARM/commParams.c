
#include "SPI_MasterSlave.h"
#include "UART_MasterSlave.h"
#include "ios.h"
#include "nfbm.h"
#include "modes.h"
#include "states.h"
#include "commReceivedParameters.h"
#include "firingTest.h"
#include "Qbasic.h"


#define toK 0.001f
#define toK2 0.000001f
#define toM  0.000001f
#define toPercent 100.0f
#define eps  0.000001f

#define MVAR2VAR 1000000.0f
#define ind2imp  2.0f*3.14159f*50.0f*0.001f 

union mode_flags receivedModeFlags;

struct ref_parameters ref_param_received;
struct ref_parameters ref_set;
union statUnion uStatus={0}; 

void mode_selection(void);

extern float cRMS;

void pushDataToMaster(void){
	
	
	
	// cyclic read parameters
	
	uDI.DI=DI;
	uDO.DO=DO;
	uStatus.status=status;

	comParams.pushDataBufferDW[0]=1<<current_state;
	comParams.pushDataBufferDW[1]=1<<current_mode;
	comParams.pushDataBufferDW[2]=uDI.all;
	comParams.pushDataBufferDW[3]=uDO.all;
	comParams.pushDataBufferDW[4]=uStatus.all;
	//DW spare-5
	//DW spare-6
	//DW spare-7
	//DW spare-8
	//DW spare-9
	//DW spare-10
	//DW spare-11
	//DW spare-12
	//DW spare-13
	
	comParams.pushDataBufferF[0]=Qbasic.ab;
	comParams.pushDataBufferF[1]=Qbasic.bc;
	comParams.pushDataBufferF[2]=Qbasic.ca;
	
	
	comParams.pushDataBufferF[3]=cl.Qab*toM;
	comParams.pushDataBufferF[4]=cl.Qbc*toM;
	comParams.pushDataBufferF[5]=cl.Qca*toM;
	comParams.pushDataBufferF[6]=cl.Qsum*toM;
	comParams.pushDataBufferF[7]=cl.Psum*toM;
	
	comParams.pushDataBufferF[8]=Qol.a;
	comParams.pushDataBufferF[9]=Qol.b;
	comParams.pushDataBufferF[10]=Qol.c;
	
	comParams.pushDataBufferF[11]=Qol.ab;
	comParams.pushDataBufferF[12]=Qol.bc;
	comParams.pushDataBufferF[13]=Qol.ca;
	
	comParams.pushDataBufferF[14]=PI.CL.ab.PIout;
	comParams.pushDataBufferF[15]=PI.CL.bc.PIout;
	comParams.pushDataBufferF[16]=PI.CL.ca.PIout;
	
	comParams.pushDataBufferF[17]=Qol.ref_ab;
	comParams.pushDataBufferF[18]=Qol.ref_bc;
	comParams.pushDataBufferF[19]=Qol.ref_ca;
	
	comParams.pushDataBufferF[20]=ref_ab.final_Q;
	comParams.pushDataBufferF[21]=ref_bc.final_Q;
	comParams.pushDataBufferF[22]=ref_ca.final_Q;
	
	comParams.pushDataBufferF[23]=ref_ab.final_alpha;
	comParams.pushDataBufferF[24]=ref_bc.final_alpha;
	comParams.pushDataBufferF[25]=ref_ca.final_alpha;
	
	comParams.pushDataBufferF[26]=sys.Bp_ab;
	comParams.pushDataBufferF[27]=sys.Bp_bc;
	comParams.pushDataBufferF[28]=sys.Bp_ca;
	
	comParams.pushDataBufferF[29]=meanRMS.Van;
	comParams.pushDataBufferF[30]=meanRMS.Vbn;
	comParams.pushDataBufferF[31]=meanRMS.Vcn;

	comParams.pushDataBufferF[32]=meanRMS.Vab;
	comParams.pushDataBufferF[33]=meanRMS.Vbc;
	comParams.pushDataBufferF[34]=meanRMS.Vca;
	
	comParams.pushDataBufferF[35]=meanRMS.Ia;
	comParams.pushDataBufferF[36]=meanRMS.Ib;
	comParams.pushDataBufferF[37]=meanRMS.Ic;
	
	comParams.pushDataBufferF[38]=meanRMS.Iload_a;
	comParams.pushDataBufferF[39]=meanRMS.Iload_b;
	comParams.pushDataBufferF[40]=meanRMS.Iload_c;
	
	
	comParams.pushDataBufferF[41]=meanRMS.Vab_sync;
	comParams.pushDataBufferF[42]=meanRMS.Vbc_sync;
	comParams.pushDataBufferF[43]=meanRMS.Vca_sync;
	
	comParams.pushDataBufferF[44]=meanRMS.Itcr_ab;
	comParams.pushDataBufferF[45]=meanRMS.Itcr_bc;
	comParams.pushDataBufferF[46]=meanRMS.Itcr_ca;
	
	comParams.pushDataBufferF[47]=cRMS;
	
	comParams.pushDataBufferF[48]=fRMS.Vab;
	comParams.pushDataBufferF[49]=fRMS.Vbc;
	comParams.pushDataBufferF[50]=fRMS.Vca;
	
	comParams.pushDataBufferF[51]=PI.Qref;
	
	comParams.pushDataBufferF[52]=PI.CL.ab.Qin;
	comParams.pushDataBufferF[53]=PI.CL.bc.Qin;
	comParams.pushDataBufferF[54]=PI.CL.ca.Qin;
	comParams.pushDataBufferF[55]=PI.OL.Qin;
	
	
	comParams.pushDataBufferF[56]=PI.CL.ab.PIout;
	comParams.pushDataBufferF[57]=PI.CL.bc.PIout;
	comParams.pushDataBufferF[58]=PI.CL.ca.PIout;
	comParams.pushDataBufferF[59]=PI.OL.PIout*toM;
	
	
	comParams.pushDataBufferF[60]=ref_set.TR_Offset;
	comParams.pushDataBufferF[61]=ref_set.Q_PF_Set;
	
	
	// online parameters
	
	
	comParams.pushDataBufferDW[14]=receivedModeFlags.all; 
	comParams.pushDataBufferDW[15]=33; 
	comParams.pushDataBufferDW[16]=34; 
	//DW spare-4
	//DW spare-5
	
	
	comParams.pushDataBufferF[109]=ref_set.MV_Bus_Offset;
	comParams.pushDataBufferF[110]=ref_set.PF_Set;
	comParams.pushDataBufferF[111]=ref_set.ManualQ;
	comParams.pushDataBufferF[112]=ref_set.ManualAlpha;
	comParams.pushDataBufferF[113]=sys.Q_limit;
	comParams.pushDataBufferF[114]=sys.Alpha_limit_up;
	comParams.pushDataBufferF[115]=sys.Alpha_limit_down;
	comParams.pushDataBufferF[116]=sys.I_limit;
	comParams.pushDataBufferF[117]=sys.I_limit_time;
	comParams.pushDataBufferF[118]=sys.V_limit;
	comParams.pushDataBufferF[119]=sys.V_limit_time;
	comParams.pushDataBufferF[120]=sys.B_limit_up;
	comParams.pushDataBufferF[121]=sys.B_limit_down;
	comParams.pushDataBufferF[122]=TestFire.alpha ;
	comParams.pushDataBufferF[123]=TestFire.firing_duration ;
	comParams.pushDataBufferF[124]=PI.CL.Kp;
	comParams.pushDataBufferF[125]=PI.CL.Ki;
	comParams.pushDataBufferF[126]=PI.OL.Kp;
	comParams.pushDataBufferF[127]=PI.OL.Ki;
	comParams.pushDataBufferF[128]=Qdata.QHF_1;
	comParams.pushDataBufferF[129]=Qdata.QHF_2;
	comParams.pushDataBufferF[130]=Qdata.QHF_3;
	comParams.pushDataBufferF[131]=Qdata.QHF_4;
	comParams.pushDataBufferF[132]=Qdata.QTCR;
	comParams.pushDataBufferF[133]=sys.TCR_XL_ab;
	comParams.pushDataBufferF[134]=sys.TCR_XL_bc;
	comParams.pushDataBufferF[135]=sys.TCR_XL_ca;
	comParams.pushDataBufferF[136]=sys.TR_Power;
	comParams.pushDataBufferF[137]=sys.TR_Uk;
	comParams.pushDataBufferF[138]=sys.TR_Ratio;
	comParams.pushDataBufferF[139]=sys.Vnom ;
	comParams.pushDataBufferF[140]=Qdata.QHF_ext;
	
	/*spare 139-149*/
	
	comParams.pushDataBufferF[150]=TR.VT_MV_primary;
	comParams.pushDataBufferF[151]=TR.VT_MV_secondary ;
	
	comParams.pushDataBufferF[152]=TR.VT_HV_primary;
	comParams.pushDataBufferF[153]=TR.VT_HV_secondary;
	
	comParams.pushDataBufferF[154]=TR.CT_MV_primary;
	comParams.pushDataBufferF[155]=TR.CT_MV_secondary;
	
	comParams.pushDataBufferF[156]=TR.CT_TCR_primary;
	comParams.pushDataBufferF[157]=TR.CT_TCR_secondary;
	
	comParams.pushDataBufferF[158]=TR.CT_LOAD_primary;
	comParams.pushDataBufferF[159]=TR.CT_LOAD_secondary;
	
	
	

	
}


void pullDataFromMaster(void){
	
	
	receivedModeFlags.all=comParams_uart.recDataBufferDW[0];
	
	mode_selection();
	
	//DW spare 1 to 4
	ref_set.MV_Bus_Offset=comParams_uart.recDataBufferF[0]*MVAR2VAR;
	ref_set.PF_Set=comParams_uart.recDataBufferF[1];
	ref_set.ManualQ=comParams_uart.recDataBufferF[2]*MVAR2VAR;
	ref_set.ManualAlpha=comParams_uart.recDataBufferF[3];
	sys.Q_limit=comParams_uart.recDataBufferF[4]*MVAR2VAR;
	sys.Alpha_limit_up=comParams_uart.recDataBufferF[5];
	sys.Alpha_limit_down=comParams_uart.recDataBufferF[6];
	sys.I_limit=comParams_uart.recDataBufferF[7];
	sys.I_limit_time=comParams_uart.recDataBufferF[8];
	sys.V_limit=comParams_uart.recDataBufferF[9];
	sys.V_limit_time=comParams_uart.recDataBufferF[10];
	sys.B_limit_up=comParams_uart.recDataBufferF[11];
	sys.B_limit_down=comParams_uart.recDataBufferF[12];
	TestFire.alpha=comParams_uart.recDataBufferF[13];
	TestFire.firing_duration=comParams_uart.recDataBufferF[14];
	PI.CL.Kp=comParams_uart.recDataBufferF[15];
	PI.CL.Ki=comParams_uart.recDataBufferF[16];
	PI.OL.Kp=comParams_uart.recDataBufferF[17];
	PI.OL.Ki=comParams_uart.recDataBufferF[18];
	Qdata.QHF_1=comParams_uart.recDataBufferF[19]*MVAR2VAR;
	Qdata.QHF_2=comParams_uart.recDataBufferF[20]*MVAR2VAR;
	Qdata.QHF_3=comParams_uart.recDataBufferF[21]*MVAR2VAR;
	Qdata.QHF_4=comParams_uart.recDataBufferF[22]*MVAR2VAR;
	Qdata.QTCR=comParams_uart.recDataBufferF[23]*MVAR2VAR;
	sys.TCR_XL_ab=comParams_uart.recDataBufferF[24]*ind2imp;
	sys.TCR_XL_bc=comParams_uart.recDataBufferF[25]*ind2imp;
	sys.TCR_XL_ca=comParams_uart.recDataBufferF[26]*ind2imp;
	sys.TR_Power=comParams_uart.recDataBufferF[27]*MVAR2VAR;
	sys.TR_Uk=comParams_uart.recDataBufferF[28];
	sys.TR_Ratio=comParams_uart.recDataBufferF[29];
	sys.Vnom=comParams_uart.recDataBufferF[30];
	Qdata.QHF_ext=comParams_uart.recDataBufferF[31]*MVAR2VAR;
	/*31-40 spare*/
	
	TR.VT_MV_primary=comParams_uart.recDataBufferF[41];
	TR.VT_MV_secondary=comParams_uart.recDataBufferF[42];
	
	TR.VT_HV_primary=comParams_uart.recDataBufferF[43];
	TR.VT_HV_secondary=comParams_uart.recDataBufferF[44];
	
	TR.CT_MV_primary=comParams_uart.recDataBufferF[45];
	TR.CT_MV_secondary=comParams_uart.recDataBufferF[46];
	
	TR.CT_TCR_primary=comParams_uart.recDataBufferF[47];
	TR.CT_TCR_secondary=comParams_uart.recDataBufferF[48];
	
	TR.CT_LOAD_primary=comParams_uart.recDataBufferF[49];;
	TR.CT_LOAD_secondary=comParams_uart.recDataBufferF[50];
	
	
	//TR.VT_MV=		(TR.VT_MV_secondary>eps) 		?	 	(TR.VT_MV_primary/TR.VT_MV_secondary) 		: 0.0f;
	//TR.VT_HV=		(TR.VT_HV_secondary>eps) 		? 	(TR.VT_HV_primary/TR.VT_HV_secondary) 		: 0.0f;
	//TR.CT_MV=		(TR.CT_MV_secondary>eps) 		? 	(TR.CT_MV_primary/TR.CT_MV_secondary) 		: 0.0f;
	//TR.CT_TCR=	(TR.CT_TCR_secondary>eps) 	? 	(TR.CT_TCR_primary/TR.CT_TCR_secondary) 	: 0.0f;
	//TR.CT_LOAD=	(TR.CT_LOAD_secondary>eps) 	? 	(TR.CT_LOAD_primary/TR.CT_LOAD_secondary) : 0.0f;
	
	/*51-55 Spare */
	
}