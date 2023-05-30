
#ifndef Psensor_H_
#define Psensor_H_

#include "state.h"

//Define state
enum
{
	Sensor
}PS_state_id;


//extern State Pointer to function
extern void (*PS_state)();

// Declare states functions 
STATE_define(Sensor);

#endif