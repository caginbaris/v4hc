
#ifndef RUSHPROCESS_H
#define RUSHPROCESS_H



#if SR==25000


//stop part

#define bn1 	 0.993917326456762f
#define bn2 	-1.987677448764875f
#define bn3 	 0.993917326456762f

#define an2 	 -1.987677448764164f
#define an3 	  0.987834652912813f

#define scale_factor 1.192202422608187f

//soi part-d

#define bd1 	 0.003760256358149f
#define bd2 	-0.000009438883544f
#define bd3 	-0.003750817474606f

#define ad2 	 -1.991859284538092f
#define ad3 	  0.992488530788053f

//soi part-q

#define bq1 	 0.000031522296740523f
#define bq2 	 0.000125847895264881f
#define bq3 	 0.000031403682983016f

#define aq2 	 -1.991859284538092f
#define aq3 	  0.992488530788053f


//smoothie

#define bl1 	 0.000241359049041961f
#define bl2 	 0.000482718098083923f
#define bl3 	 0.000241359049041961f

#define al2 	 -1.955578240315036f
#define al3 	  0.956543676511203f

#endif

#if  SR==2500

//stop part

#define bn1 	 0.942263075198975f
#define bn2 	-1.869623750071617f
#define bn3 	 0.942263075198975f

#define an2 	 -1.869623750071607f
#define an3 	  0.884526150397940f

#define scale_factor 1.191516333218001f

//soi part-d



#define bd1 	 0.036577061014648f
#define bd2 	-0.000909679726369f
#define bd3 	-0.035667381288279f

#define ad2 	 -1.866850747995863f
#define ad3 	  0.927374110449614f

//soi part-q

#define bq1 	 0.003089914490421f
#define bq2 	 0.012091613929521f
#define bq3 	 0.002975480316183f

#define aq2 	 -1.866850747995863f
#define aq3 	  0.927374110449614f


//smoothie

#define bl1 	 0.003621681514929f
#define bl2 	 0.007243363029857f
#define bl3 	 0.003621681514929f

#define al2 	 -1.822694925196308f
#define al3 	  0.837181651256023f

#endif

#endif




















