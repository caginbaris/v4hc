#ifndef __firing_H
#define __firing_H

#include <stdint.h>


#define  r2d 57.29577951f
#define  PLL_correction 0.1f;

#define firing_offset 	8.0f
#define firing_offset2 	2.0f
#define firing_offset3  2.0f
#define pos_limit 		175
#define neg_limit 		355




struct firingOutputs {

	uint8_t Ap:1;
	uint8_t Bp:1;
	uint8_t Cp:1;
	
	uint8_t An:1;
	uint8_t Bn:1;
	uint8_t Cn:1;
	
};

extern struct firingOutputs fr;


union firingOutputsUnion{
	
	struct firingOutputs fr;
	uint8_t all;



};

extern union firingOutputsUnion ufr;



#endif


void firingOutputs(void);

