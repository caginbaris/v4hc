/*
 * lead_lag_calculation.c
 *
 *  Created on: 25 May 2017
 *      Author: BARIS
 */

#include "nfbm.h"
#include "constants.h"
#include "plf_constants.h"
#include "aux_functions.h"




struct fastPowerParameters fpp_ab={0.0f};
struct fastPowerParameters fpp_bc={0.0f};
struct fastPowerParameters fpp_ca={0.0f};

struct OpenLoopQ Qol={0.0f};

struct system_parameters sys={0};


void init_OpenLoopCalc(){
	

	sys.OL_ratio=0.75f;


}


void lead_lag_calculation(){ //cau voltage input line changed


		static float Vlagz_ab=0.0f,Vxz_ab=0,Ilagz_ab=0.0f,Ixz_ab=0;
		static float Vlagz_bc=0.0f,Vxz_bc=0,Ilagz_bc=0.0f,Ixz_bc=0;
		static float Vlagz_ca=0.0f,Vxz_ca=0,Ilagz_ca=0.0f,Ixz_ca=0;

		//********************************************************

		fpp_ab.Vlag =Vlagz_ab*a1 + (adc.Vab  +Vxz_ab)*b1;
		Vxz_ab=adc.Vab;
		Vlagz_ab=fpp_ab.Vlag*isqrt2;


		fpp_ab.Ilag = Ilagz_ab*a1 + (adc.Iload_a +Ixz_ab)*b1;
		Ixz_ab=adc.Iload_a;
		Ilagz_ab=fpp_ab.Ilag*isqrt2;


		fpp_ab.Vlead=sqrt2*adc.Vab -fpp_ab.Vlag;
		fpp_ab.Ilead=sqrt2*adc.Iload_a-fpp_ab.Ilag;

		//********************************************************

		fpp_bc.Vlag = Vlagz_bc*a1 + (adc.Vbc +Vxz_bc)*b1;
		Vxz_bc=adc.Vbc;
		Vlagz_bc=fpp_bc.Vlag*isqrt2;


		fpp_bc.Ilag = Ilagz_bc*a1 + (adc.Iload_b +Ixz_bc)*b1;
		Ixz_bc=adc.Iload_b;
		Ilagz_bc=fpp_bc.Ilag*isqrt2;


		fpp_bc.Vlead=sqrt2*adc.Vbc -fpp_bc.Vlag;
		fpp_bc.Ilead=sqrt2*adc.Iload_b-fpp_bc.Ilag;


		//********************************************************

		fpp_ca.Vlag = Vlagz_ca*a1 + (adc.Vca +Vxz_ca)*b1;
		Vxz_ca=adc.Vca;
		Vlagz_ca=fpp_ca.Vlag*isqrt2;


		fpp_ca.Ilag = Ilagz_ca*a1 + (adc.Iload_c +Ixz_ca)*b1;
		Ixz_ca=adc.Iload_c;
		Ilagz_ca=fpp_ca.Ilag*isqrt2;


		fpp_ca.Vlead=sqrt2*adc.Vca -fpp_ca.Vlag;
		fpp_ca.Ilead=sqrt2*adc.Iload_c-fpp_ca.Ilag;

}


/*
 * plf_sos.c
 *
 *  Created on: Mar 28, 2017
 *      Author: baris.cengiz
 */

float plf_sos_ab(float x){

	static float xfz1=0,xfz2=0;
	static float yf=0,yfz1=0,yfz2=0;

	static float xsz1=0,xsz2=0;
	static float ys=0,ysz1=0,ysz2=0;



	yf=(bf0*x)+(bf1*xfz1)+(bf2*xfz2)+(af1*yfz1)+(af2*yfz2);

	xfz2=xfz1;
	xfz1=x;

	yfz2=yfz1;
	yfz1=yf;


	ys=(bs0*yf)+(bs1*xsz1)+(bs2*xsz2)+(as1*ysz1)+(as2*ysz2);

	xsz2=xsz1;
	xsz1=yf;

	ysz2=ysz1;
	ysz1=ys;


	return ys*peu;

}


float plf_sos_bc(float x){

    static float xfz1=0,xfz2=0;
    static float yf=0,yfz1=0,yfz2=0;

    static float xsz1=0,xsz2=0;
    static float ys=0,ysz1=0,ysz2=0;



    yf=(bf0*x)+(bf1*xfz1)+(bf2*xfz2)+(af1*yfz1)+(af2*yfz2);

    xfz2=xfz1;
    xfz1=x;

    yfz2=yfz1;
    yfz1=yf;


    ys=(bs0*yf)+(bs1*xsz1)+(bs2*xsz2)+(as1*ysz1)+(as2*ysz2);

    xsz2=xsz1;
    xsz1=yf;

    ysz2=ysz1;
    ysz1=ys;


    return ys*peu;

}


float plf_sos_ca(float x){

    static float xfz1=0,xfz2=0;
    static float yf=0,yfz1=0,yfz2=0;

    static float xsz1=0,xsz2=0;
    static float ys=0,ysz1=0,ysz2=0;



    yf=(bf0*x)+(bf1*xfz1)+(bf2*xfz2)+(af1*yfz1)+(af2*yfz2);

    xfz2=xfz1;
    xfz1=x;

    yfz2=yfz1;
    yfz1=yf;


    ys=(bs0*yf)+(bs1*xsz1)+(bs2*xsz2)+(as1*ysz1)+(as2*ysz2);

    xsz2=xsz1;
    xsz1=yf;

    ysz2=ysz1;
    ysz1=ys;


    return ys*peu;

}

void ref_filtering(){





	Qol.ab_f=plf_sos_ab(Qol.ab);
	Qol.bc_f=plf_sos_bc(Qol.bc);
	Qol.ca_f=plf_sos_ca(Qol.ca);




}



void OL_calculations(){


	

	Qol.a=(fpp_bc.Vlead*fpp_ab.Ilead + fpp_bc.Vlag*fpp_ab.Ilag)*i2sqrt3;
	Qol.b=(fpp_ca.Vlead*fpp_bc.Ilead + fpp_ca.Vlag*fpp_bc.Ilag)*i2sqrt3;
	Qol.c=(fpp_ab.Vlead*fpp_ca.Ilead + fpp_ab.Vlag*fpp_ca.Ilag)*i2sqrt3;

	
	Qol.ab=Qol.a+Qol.b-Qol.c;
	Qol.bc=Qol.b+Qol.c-Qol.a;
	Qol.ca=Qol.c+Qol.a-Qol.b;
	
	ref_filtering();

	Qol.ref_ab=Qbasic.ab-Qol.ab_f;
	Qol.ref_bc=Qbasic.bc-Qol.bc_f;
	Qol.ref_ca=Qbasic.ca-Qol.ca_f;


	f_limiter(&Qol.ref_ab,0,sys.Q_limit);
	f_limiter(&Qol.ref_bc,0,sys.Q_limit);
	f_limiter(&Qol.ref_ca,0,sys.Q_limit);

}

