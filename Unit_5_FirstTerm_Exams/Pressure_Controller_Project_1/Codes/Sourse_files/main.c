#include <stdint.h>
#include <stdio.h>

#include "driver.h"

#include "Psensor.h"
#include "PS_driver.h"
#include "Algo.h"
#include "Alarm.h"
#include "Ac.h"

void setup (){

	// init all the drivers
	// init  IRQ...
	// init HAL US_Driver & DC_Driver
	// init Block
	PS_D_init ();
	AL_init();
	// Set State pointer for each block

	PS_state = STATE(Sensor);
	PSdriver_state = STATE(Reading);
	algo_state = STATE(High_Pressure_Detector);
	al_state = STATE(al_idle);
	AC_state = STATE(AC_waiting);
}


int main (){
	GPIO_INITIALIZATION();
	setup();
	while (1)
	{
		//Implement your Design 
		PS_state ();
		PSdriver_state (); 
		algo_state ();
		al_state (); 
		AC_state (); 
	}

}
