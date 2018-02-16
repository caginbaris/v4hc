/*
*
*  Created on : 15.11.2017
*  Author : Baris
*
*/

#ifndef __firingTest_h
#define __firingTest_h

#include "stdint.h"

struct TestFiring{


	uint32_t enable_firing:1;
	uint32_t counter:31;

	float alpha;
	float firing_duration; //msec

};


extern struct TestFiring TestFire;



#endif