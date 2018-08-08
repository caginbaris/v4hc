
#ifndef FUNDPROCESS_H
#define FUNDPROCESS_H


void fundEmAll(float x,float y,float z, float *out );

#if SR==25000


//soi part-d

#define bdf1 	 0.003134982002028f
#define bdf2 	-0.000006559052537f
#define bdf3 	-0.003128422949491f

#define adf2 	 -1.993579096088921f
#define adf3 	  0.993736512624778f

//soi part-q

#define bqf1 	0.0000131387239469265f
#define bqf2 	0.0000524720318857527f
#define bqf3 	0.0000130975120959308f

#define aqf2 	 -1.993579096088921f
#define aqf3 	  0.993736512624778f

#endif

#if  SR==2500

//stop part



//soi part-d

#define bdf1 	 0.030727862182890f
#define bdf2 	-0.000637183738059f
#define bdf3 	-0.030090678444830f

#define adf2 	 -1.923816000989245f
#define adf3 	  0.939101367424293f

//soi part-q

#define bqf1 	0.001294516286626f
#define bqf2 	0.005093696618265f
#define bqf3 	0.001254470312633f

#define aqf2 	 -1.923816000989245f
#define aqf3 	 0.939101367424293f

#endif

#endif

















