/*
 * ADC.h
 *
 * Created: 8/21/2023 6:58:00 PM
 *  Author: midom
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "MemoryMap.h"
#include <avr/interrupt.h>
#include <util/delay.h>


#define voltREF 5000
#define Res		1024


typedef enum 
{
	VREF_AREF,
	VREF_AVCC,
	VREF_265
}ADC_Vref_type;

typedef enum
{
	ADC_SCALER_2 = 0,
	ADC_SCALER_4 = 2,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
}ADC_SCALER_type;


typedef enum
{
	CH_0 = 0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7,
}ADC_Channel_type;


void ADC_init (ADC_Vref_type vref , ADC_SCALER_type Scaler);

uint16_t ADC_Read(ADC_Channel_type CH);





#endif /* ADC_H_ */