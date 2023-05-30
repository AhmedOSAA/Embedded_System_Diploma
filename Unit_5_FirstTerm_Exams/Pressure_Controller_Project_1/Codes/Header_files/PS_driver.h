#ifndef PS_D_H_
#define PS_D_H_

#include "state.h"

//Define state
enum
{
	Reading,
	Sending
}PSdriver_state_id;

//extern State Pointer to function
extern void (*PSdriver_state)();


// Declare states functions 
void PS_D_init ();
STATE_define(Reading);
STATE_define(Sending);

#endif