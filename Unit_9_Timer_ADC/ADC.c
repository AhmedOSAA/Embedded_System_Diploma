/*
 * ADC.c
 * Author: ENG Ahmed Osamaa
 */ 

#include "ADC.h"


void ADC_init (ADC_Vref_type vref , ADC_SCALER_type Scaler)
{
	// Vref
	switch (vref)
	{
		case VREF_AREF :
		ADMUX &= ~((1<<REFS0)|(1<<REFS1));
		break;
		
		case VREF_AVCC :
		ADMUX |= (1<<REFS0);
		ADMUX &= ~(1<<REFS1);
		break;
		
		case VREF_265 :
		ADMUX |= ((1<<REFS0)|(1<<REFS1));
		break;
	
	}
	
	//Prescaller
	
	ADCSRA &= 0xF8 ;
	ADCSRA |= Scaler ;
	
	// Enable 
	ADCSRA |= 1<<ADEN ;
	
}

uint16_t ADC_Read(ADC_Channel_type CH)
{
	//Select Channel
	ADMUX &= 0xE0 ;
	ADMUX |= CH ;
	
	// start Conversion
	ADCSRA |= 1<<ADSC ;
	
	while(ADCSRA & (1<<ADSC));
	return ADC ;
}
