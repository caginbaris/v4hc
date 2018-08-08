#include "spp.h"
#include "rushProcess.h"
#include <math.h>


float sos_removal(float x, struct sos_structure *sos ){


	float y;

	y=(bn1*x+bn2*sos->xz1+bn3*sos->xz2)-
	   (an2*sos->yz1+an3*sos->yz2);

	sos->xz2=sos->xz1;
	sos->xz1=x;

	sos->yz2=sos->yz1;
	sos->yz1=y;

	return y*scale_factor;


}


float sos_int_d(float x, struct sos_structure *sos ){


	float y;

	y=(bd1*x+bd2*sos->xz1+bd3*sos->xz2)-
	   (ad2*sos->yz1+ad3*sos->yz2);

	sos->xz2=sos->xz1;
	sos->xz1=x;

	sos->yz2=sos->yz1;
	sos->yz1=y;


	return y;


}


float sos_int_q(float x, struct sos_structure *sos ){


	float y;

	y=(bq1*x+bq2*sos->xz1+bq3*sos->xz2)-
	   (aq2*sos->yz1+aq3*sos->yz2);

	sos->xz2=sos->xz1;
	sos->xz1=x;

	sos->yz2=sos->yz1;
	sos->yz1=y;

	return y;


}


float sos_sm(float x, struct sos_structure *sos ){


	float y;

	y=(bl1*x+bl2*sos->xz1+bl3*sos->xz2)-
	   (al2*sos->yz1+al3*sos->yz2);

	sos->xz2=sos->xz1;
	sos->xz1=x;

	sos->yz2=sos->yz1;
	sos->yz1=y;


	return y;


}


float rushProcess(float x, struct sos_structure *sos){

	

	float y,yd,yq,ymag,ymag_s;

	y=sos_removal(x,&sos[0]);
	yd=sos_int_d(y,&sos[1]);
	yq=sos_int_q(y,&sos[2]);

	ymag=sqrtf((yd*yd+yq*yq)*0.5f);

	ymag_s=sos_sm(ymag,&sos[3]);

	return ymag_s;


}


void rushEmAll(float x,float y,float z, float *out ){


static struct sos_structure sos[3][4]={0};

out[0]=rushProcess(x, &sos[0][0]);
out[1]=rushProcess(y, &sos[1][0]);
out[2]=rushProcess(z, &sos[2][0]);

}


