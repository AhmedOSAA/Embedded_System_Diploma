

#ifndef AC_H_
#define AC_H_

#include "state.h"

//Define state
enum
{
	Waiting,
	ON,
	OFF
}AC_state_id;

//extern State Pointer to function
extern void (*AC_state)();


// Declare states functions 
STATE_define(AC_waiting);
STATE_define(AC_ON);
STATE_define(AC_OFF);

#endif