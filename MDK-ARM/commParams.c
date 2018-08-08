
#include "SPI_MasterSlave.h"
#include "UART_MasterSlave.h"
#include "ios.h"
#include "nfbm.h"
#include "modes.h"
#include "states.h"
#include "commReceivedParameters.h"
#include "firingTest.h"
#include "Qbasic.h"
#include "aux_functions.h"

#define toM 	1000000.0f
#define toK 	1000.0f
#define div3 	0.3333333f
#define fac3 	3.0f

union mode_flags receivedModeFlags;

struct ref_parameters ref_param_received;
struct ref_parameters ref_set;
union statUnion uStatus={0}; 

extern float cRMS;


#define MV_Bus_Offset_limit 3300000.0f
#define PF_Set_limit 1.0f
#define Qsys_limit 70000000.0f
#define Alpha_up_limit 175.0f
#define Alpha_down_limit 97.0f
#define Isys_limit 1800.0f
#define Isys_limit_time 5.0f
#define Vsys_limit 35000.0f
#define Vsys_limit_time 0.3f
#define Bsys_limit 0.95f



void mode_selection(void);

void pushDataToMaster(void){
	
	
	
	// cyclic read parameters
	
	uDI.DI=DI;
	uDO.DO=DO;
	uStatus.status=status;

	comParams.pushDataBufferDW[0]=(uint8_t)1<<current_state;
	comParams.pushDataBufferDW[1]=(uint8_t)1<<current_mode;
	comParams.pushDataBufferDW[2]=uDI.all;
	comParams.pushDataBufferDW[3]=uDO.all;
	comParams.pushDataBufferDW[4]=uStatus.all;
	comParams.pushDataBufferDW[5]=faultData.all;
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
	
	
	comParams.pushDataBufferF[3]=cl.Qab;
	comParams.pushDataBufferF[4]=cl.Qbc;
	comParams.pushDataBufferF[5]=cl.Qca;
	comParams.pushDataBufferF[6]=cl.Qtotal;
	comParams.pushDataBufferF[7]=cl.Ptotal;
	
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
	
	comParams.pushDataBufferF[51]=PI.Qref*fac3;
	
	comParams.pushDataBufferF[52]=PI.CL.ab.Qin;
	comParams.pushDataBufferF[53]=PI.CL.bc.Qin;
	comParams.pushDataBufferF[54]=PI.CL.ca.Qin;
	comParams.pushDataBufferF[55]=PI.OL.Qin;
	
	
	comParams.pushDataBufferF[56]=PI.CL.ab.PIout;
	comParams.pushDataBufferF[57]=PI.CL.bc.PIout;
	comParams.pushDataBufferF[58]=PI.CL.ca.PIout;
	comParams.pushDataBufferF[59]=PI.OL.PIout;
	
	
	comParams.pushDataBufferF[60]=ref_set.TR_Offset;
	comParams.pushDataBufferF[61]=ref_set.Q_PF_Set;
	
	comParams.pushDataBufferF[62]=I_limiter.ab.B;//cau
	comParams.pushDataBufferF[63]=I_limiter.bc.B;
	comParams.pushDataBufferF[64]=I_limiter.ca.B;
	comParams.pushDataBufferF[65]=V_limiter.ab.Bout;
	comParams.pushDataBufferF[66]=V_limiter.bc.Bout;
	comParams.pushDataBufferF[67]=V_limiter.ca.Bout;
	
	

	
	
	// online parameters
	
	
	comParams.pushDataBufferDW[14]=receivedModeFlags.all; 
	comParams.pushDataBufferDW[15]=33; 
	comParams.pushDataBufferDW[16]=34; 
	//DW spare-4
	//DW spare-5
	
	
	comParams.pushDataBufferF[109]=ref_set.MV_Bus_Offset*fac3;
	comParams.pushDataBufferF[110]=ref_set.PF_Set;
	comParams.pushDataBufferF[111]=ref_set.ManualQ*fac3;
	comParams.pushDataBufferF[112]=ref_set.ManualAlpha;
	comParams.pushDataBufferF[113]=sys.Q_limit*fac3;
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
	

	
	comParams.pushDataBufferF[160]=TR.VT_MV;
	comParams.pushDataBufferF[161]=TR.VT_HV;
	comParams.pushDataBufferF[162]=TR.CT_MV;
	comParams.pushDataBufferF[163]=TR.CT_TCR;
	comParams.pushDataBufferF[164]=TR.CT_LOAD;

	
	
}


void pullDataFromMaster(void){
	
	
	
	receivedModeFlags.all=comParams_uart.recDataBufferDW[0];
	
	mode_selection();
	
	//DW spare 1 to 4
	ref_set.MV_Bus_Offset=comParams_uart.recDataBufferF[0]*toM*div3 ; f_limiter(&ref_set.MV_Bus_Offset,-MV_Bus_Offset_limit,MV_Bus_Offset_limit);
	ref_set.PF_Set=comParams_uart.recDataBufferF[1];									f_limiter(&ref_set.PF_Set,-PF_Set_limit,PF_Set_limit);	
	ref_set.ManualQ=comParams_uart.recDataBufferF[2]*toM*div3;				f_limiter(&ref_set.ManualQ,0.0f,Qsys_limit);	
	ref_set.ManualAlpha=comParams_uart.recDataBufferF[3];							f_limiter(&ref_set.ManualAlpha,Alpha_down_limit,Alpha_up_limit);	
	sys.Q_limit=comParams_uart.recDataBufferF[4]*toM*div3;						f_limiter(&sys.Q_limit,Qsys_limit*0.25,Qsys_limit);
	sys.Alpha_limit_up=comParams_uart.recDataBufferF[5];							f_limiter(&sys.Alpha_limit_up,Alpha_down_limit,Alpha_up_limit);
	sys.Alpha_limit_down=comParams_uart.recDataBufferF[6];						f_limiter(&sys.Alpha_limit_down,Alpha_down_limit,Alpha_up_limit);
	sys.I_limit=comParams_uart.recDataBufferF[7];											f_limiter(&sys.I_limit,Isys_limit*0.25f,Isys_limit);
	sys.I_limit_time=comParams_uart.recDataBufferF[8];								f_limiter(&sys.I_limit_time,Isys_limit_time*0.1f,Isys_limit_time);
	sys.V_limit=comParams_uart.recDataBufferF[9];											f_limiter(&sys.V_limit,Vsys_limit*0.97f,Vsys_limit);
	sys.V_limit_time=comParams_uart.recDataBufferF[10];								f_limiter(&sys.V_limit_time,Vsys_limit_time*0.1f,Vsys_limit_time);	
	sys.B_limit_up=comParams_uart.recDataBufferF[11];									f_limiter(&sys.B_limit_up,Bsys_limit*0.25f,Bsys_limit);
	sys.B_limit_down=comParams_uart.recDataBufferF[12];								f_limiter(&sys.B_limit_down,0,Bsys_limit);
	TestFire.alpha=comParams_uart.recDataBufferF[13];									f_limiter(&TestFire.alpha,Alpha_down_limit,Alpha_up_limit);
	TestFire.firing_duration=comParams_uart.recDataBufferF[14];				f_limiter(&TestFire.firing_duration,0.02,0.2);
	//PI.CL.Kp=comParams_uart.recDataBufferF[15];
	//PI.CL.Ki=comParams_uart.recDataBufferF[16];
	//PI.OL.Kp=comParams_uart.recDataBufferF[17];
	//PI.OL.Ki=comParams_uart.recDataBufferF[18];
	Qdata.QHF_1=comParams_uart.recDataBufferF[19];
	Qdata.QHF_2=comParams_uart.recDataBufferF[20];
	Qdata.QHF_3=comParams_uart.recDataBufferF[21];
	Qdata.QHF_4=comParams_uart.recDataBufferF[22];
	Qdata.QTCR=comParams_uart.recDataBufferF[23];
	//sys.TCR_XL_ab=comParams_uart.recDataBufferF[24];;
	//sys.TCR_XL_bc=comParams_uart.recDataBufferF[25];
	//sys.TCR_XL_ca=comParams_uart.recDataBufferF[26];
	//sys.TR_Power=comParams_uart.recDataBufferF[27]*toM;
	//sys.TR_Uk=comParams_uart.recDataBufferF[28];
	sys.TR_Ratio=comParams_uart.recDataBufferF[29];	f_limiter(&sys.TR_Ratio,0.0f,1.0f);
	//sys.Vnom=comParams_uart.recDataBufferF[30]*toK;
	/*29-40 spare*/
	
	I_limiter.level=sys.I_limit;
	I_limiter.delay =sys.I_limit_time;

	V_limiter.level=sys.V_limit;
	V_limiter.delay=sys.V_limit_time;
	
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
	
	
	TR.VT_MV=	(TR.VT_MV_secondary>1.0f) 	? 			(TR.VT_MV_primary/	TR.VT_MV_secondary) : TR.VT_MV;
	TR.VT_HV=	(TR.VT_HV_secondary>1.0f) 	? 			(TR.VT_HV_primary/	TR.VT_HV_secondary) : TR.VT_HV;
	TR.CT_MV=	(TR.CT_MV_secondary>1.0f) 	? 			(TR.CT_MV_primary/	TR.CT_MV_secondary) : TR.CT_MV;
	TR.CT_TCR=	(TR.CT_TCR_secondary>1.0f) 	? 		(TR.CT_TCR_primary/	TR.CT_TCR_secondary) :TR.CT_TCR;
	TR.CT_LOAD=	(TR.CT_LOAD_secondary>1.0f) 	? 	(TR.CT_LOAD_primary/TR.CT_LOAD_secondary):TR.CT_LOAD;
	
	
	/*51-55 Spare */
	
}