#include "Psensor.h"

//Variables
static int Pval = 0;

//State Pointer to function
void (*PS_state)();

//Define function 

STATE_define(Sensor){
	//State name
	PS_state_id = Sensor ;
	// the sensor get val and store it 
	Pval = getPressureVal();
	// send it to PS_driver
	send_Pval(Pval);
}

