
#ifndef ALGO_H_
#define ALGO_H_

#include "state.h"

//Define state
enum
{
	High_Pressure_Detector
}Algo_state_id;

//extern State Pointer to function
extern void (*algo_state)();


// Declare states functions 
STATE_define(High_Pressure_Detector);
	

#endif