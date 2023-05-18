/* DC.c
 * Author: ENG. Ahmed Osamaa
 */
#include "DC.h"

// variables
int DC_speed = 0 ;

//State pointer to function
void (*DC_state)();

// State connection
void DC_SET_Motor (int s){
	DC_speed = s;
	DC_state = STATE(DC_busy);
	printf("CA ------ Speed = %d------->DC \n",DC_speed);
}

// define functions

void DC_init (){
	//init PWM
	printf("DC_init \n");
}

STATE_define(DC_idle){
	//State name
	DC_state_id = DC_Idle ;
	//State action

	printf("DC_Idle State: Speed = %d\n",DC_speed);
}

STATE_define(DC_busy){
	//State name
	DC_state_id = DC_Busy ;
	//State action

	DC_state = STATE(DC_idle);


	printf("DC_Busy : Speed = %d\n",DC_speed);

}
