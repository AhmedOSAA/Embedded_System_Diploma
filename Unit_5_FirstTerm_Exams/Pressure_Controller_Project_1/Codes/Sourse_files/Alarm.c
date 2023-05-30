
#include "Alarm.h"

// variables
int time_periode = 600000 ;

//connection function
void high_pressure(){
	al_state = STATE(al_alarmON);
}

//State Pointer to function
void (*al_state)();

//Define function 

void AL_init(){
// init Alarm Driver
}

STATE_define(al_idle){
	//State name
	Al_state_id = IDLE ;
}
STATE_define(al_alarmON){
	//State name
	Al_state_id = AlarmON;
	//start alarm
	start_alarm();

	STATE(al_timer)();
}
STATE_define(al_timer){
	//State name
	Al_state_id = Timer;
	// delay
	Delay(time_periode);
	// stop alarm
	stop_alarm();

	al_state = STATE(al_idle);
}
