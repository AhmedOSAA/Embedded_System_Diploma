/* CA.c
 * Author: ENG. Ahmed Osamaa
 */
#include "CA.h"
//prototype US_Get_distance_random
// variables
int CA_speed = 0 ;
int CA_distance = 0 ;
int CA_threshold = 50 ;

//State pointer to function
void (*CA_state)();

// State connection
void US_SET_distance (int d){
	CA_distance = d ;
	(CA_distance <= CA_threshold)? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving));
	printf("US -------- distance = %d --------> CA \n",CA_distance);
}

// define functions

STATE_define(CA_waiting){
	//State name
	CA_state_id = CA_Waiting ;
	printf("CA_Waiting State: distance = %d  Speed = %d\n",CA_distance,CA_speed);

	//State action
	CA_speed = 0 ;
	DC_SET_Motor(CA_speed);
}

STATE_define(CA_driving){
	//State name
	CA_state_id = CA_Driving ;
	printf("CA_Driving State: distance = %d  Speed = %d\n",CA_distance,CA_speed);

	//State action
	CA_speed = 30 ;
	DC_SET_Motor(CA_speed);

}
