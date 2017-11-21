


int on_delay(unsigned int input, unsigned int mem, unsigned int qual_sample, long *count)
{

	int out;

	out = mem;

	if (input == 1 && mem == 0)
	{
		*count = *count + 1;

		if ((*count) == qual_sample)
		{
			out = 1;
			*count = 0;
		}

	}

	else
	{
		*count = 0;
	}

	if (input == 0)
	{
		out = 0;
		*count = 0;
	}

	return out;

}


int off_delay(unsigned int input, unsigned int mem, unsigned int qual_sample, long *count)
{

	int out;

	out = mem;

	if (input == 0 && mem == 1)
	{
		*count = *count + 1;

		if ((*count) == qual_sample)
		{
			out = 0;
			*count = 0;
		}

	}

	else
	{
		*count = 0;
	}

	if (input == 1)
	{
		out = 1;
		*count = 0;
	}

	return out;

}






void f_limiter(float *x,float min, float max){

	if(*x<min){*x=min;}
	if(*x>max){*x=max;}

}

float minSelector_3p(float a, float b, float c){
	
	float min;
	
	min=a;
	if(b<min){min=b;}
	if(c<min){min=c;}
	
	return min;

}


