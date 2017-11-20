

#include "nfbm.h"

struct references ref_ab;
struct references ref_bc;
struct references ref_ca;

void init_references()
{

}


void Ref_CL(){
	
	ref_ab.final_Q=PI.CL.ab.PIout;
	ref_bc.final_Q=PI.CL.bc.PIout;
	ref_ca.final_Q=PI.CL.ca.PIout;


}


void Ref_OL(){
	
	ref_ab.final_Q=0.0f;
	ref_bc.final_Q=0.0f;
	ref_ca.final_Q=0.0f;


}


void Ref_manualVar(){
	
	ref_ab.final_Q=0.0f;
	ref_bc.final_Q=0.0f;
	ref_ca.final_Q=0.0f;


}


void Ref_manualAngle(){
	
	ref_ab.final_alpha=0.0f;
	ref_bc.final_alpha=0.0f;
	ref_ca.final_alpha=0.0f;


}


