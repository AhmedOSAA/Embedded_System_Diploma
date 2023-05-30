

#ifndef ALARM_H_
#define ALARM_H_

#include "state.h"

//Define state
enum
{
	IDLE,
	AlarmON,
	Timer
}Al_state_id;

//extern State Pointer to function
extern void (*al_state)();


// Declare states functions 
void AL_init();
STATE_define(al_idle);
STATE_define(al_alarmON);
STATE_define(al_timer);

#endif