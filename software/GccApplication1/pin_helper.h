#ifndef _PIN_HELPER_H
#define _PIN_HELPER_H
///// Direction configure
//#define PIN_IN(bit)             {bit ## _DDR &= ~(1 << bit);}
//#define PIN_OUT(bit)            {bit ## _DDR |= (1 << bit);}
//
///// Output/Pullup
//#define PIN_SET(bit)                      {bit ## _PORT |= (1 << bit);}
//#define PIN_CLR(bit)                     {bit ## _PORT &= ~(1 << bit);}
//
///// Digital inputs for ADC
//#define DIGIN_DIS(channel)      {DIDR0 |= (1 << channel);}
//#define DIGIN_EN(channel)       {DIDR0 &= ~(1 << channel);}
//
///// Pins as interrupt sources
//#define PINT_EN(pin)    {pin ## _PCMSK |= (1 << pin ## _PCINT);}
//#define PINT_DIS(pin)   {pin ## _PCMSK &= ~(1<< pin ## _PCINT);}
//
//
///***** Manipulate Outputs *****/
//#define SET(bit)                       {bit ## _PORT |= (1 << bit);}
//#define CLR(bit)                        {bit ## _PORT &= ~(1 << bit);}
//#define TGL(bit)                         {bit ## _PIN |= (1 << bit);}
//
///***** Test Inputs *****/
//#define IS_HIGH(bit)                        (bit ## _PIN & (1 << bit))
//#define GET(bit)                        ((bit ## _PIN & (1 << bit))>>bit)

// direction
#define __PIN_IN(port,bit) 			{DDR ## port &=~(1<<bit);}
#define __PIN_OUT(port,bit)			{DDR ## port |=(1<<bit);}
#define __SET(port,bit)				{PORT ## port |=(1<<bit);}
#define __CLR(port,bit)				{PORT ## port &=~(1<<bit);}
#define __TGL(port,bit)				{PIN ## port |=(1<<bit);}
#define __IS_HIGH(port,bit)			(PIN ## port & (1<<bit))
#define __GET(port,bit)				((PIN ## port & (1<<bit))>>bit)

// direction
#define PIN_IN(...) 			__PIN_IN(__VA_ARGS__)
#define PIN_OUT(...)			__PIN_OUT(__VA_ARGS__)
// out
#define SET(...)				__SET(__VA_ARGS__)
#define CLR(...)				__CLR(__VA_ARGS__)
#define TGL(...)				__TGL(__VA_ARGS__)
// input
#define IS_HIGH(...)			__IS_HIGH(__VA_ARGS__)
#define GET(...)				__GET(__VA_ARGS__)




#endif //_PIN_HELPER_H
