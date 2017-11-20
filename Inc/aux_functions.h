
#ifndef __aux_functions_h
#define __aux_functions_h

int on_delay(unsigned int input, unsigned int mem, unsigned int qual_sample, long *);
int off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample, long *count);
void f_limiter(float *x,float min, float max);


#endif

