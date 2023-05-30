
#include "Ac.h"


//connection function
void start_alarm(){
	AC_state = STATE(AC_ON);
	Set_Alarm_actuator(1);
}
void stop_alarm(){
	AC_state = STATE(AC_OFF);
	Set_Alarm_actuator(0);
} 

//State Pointer to function
void (*AC_state)();

//Define function 
STATE_define(AC_waiting){
	//State name
	AC_state_id = Waiting;

}
STATE_define(AC_ON){
	//State name
	AC_state_id = ON;

}
STATE_define(AC_OFF){
	//State name
	AC_state_id = OFF;

	AC_state = STATE(AC_waiting);
}
