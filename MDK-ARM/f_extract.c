#include "spp.h"
#include "fundProcess.h"
#include <math.h>


float sos_int_fd(float x, struct sos_structure *sos ){


	float y;

	y=(bdf1*x+bdf2*sos->xz1+bdf3*sos->xz2)-
	   (adf2*sos->yz1+adf3*sos->yz2);

	sos->xz2=sos->xz1;
	sos->xz1=x;

	sos->yz2=sos->yz1;
	sos->yz1=y;


	return y;


}


float sos_int_fq(float x, struct sos_structure *sos ){


	float y;

	y=(bqf1*x+bqf2*sos->xz1+bqf3*sos->xz2)-
	   (aqf2*sos->yz1+aqf3*sos->yz2);

	sos->xz2=sos->xz1;
	sos->xz1=x;

	sos->yz2=sos->yz1;
	sos->yz1=y;

	return y;


}


float fundProcess(float x, struct sos_structure *sos){

float y,yd,yq;


	yd=sos_int_fd(x,&sos[0]);
	yq=sos_int_fq(x,&sos[1]);
	y=sqrtf((yd*yd+yq*yq)*0.5f);

	return y; 
}


void fundEmAll(float x,float y,float z, float *out ){

static struct sos_structure sos[3][2]={0};

out[0]=fundProcess(x,  &sos[0][0]);
out[1]=fundProcess(y,  &sos[1][0]);
out[2]=fundProcess(z, &sos[2][0]);


}



