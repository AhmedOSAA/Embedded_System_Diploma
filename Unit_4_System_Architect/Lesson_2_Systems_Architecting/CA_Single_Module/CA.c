/*
 * CA.c
 *
 *  Created on: May 17, 2023
 *      Author: midom
 */
#include "CA.h"
//prototype US_Get_distance_random
int US_Get_distance_random (int l, int r, int count);
// variables
int CA_speed = 0 ;
int CA_distance = 0 ;
int CA_threshold = 50 ;

//State pointer to function
void (*CA_state)();

// define functions

STATE_define(CA_waiting){
	//State name
	CA_state_id = CA_Waiting ;
	//State action
	CA_speed = 0 ;
	//Event check
	//US_Get_distance_random
	CA_distance = US_Get_distance_random(45,55,1);
	(CA_distance <= CA_threshold)? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving));

	printf("CA_Waiting State: distance = %d  Speed = %d\n",CA_distance,CA_speed);
}

STATE_define(CA_driving){
	//State name
	CA_state_id = CA_Driving ;
	//State action
	CA_speed = 30 ;
	//Event check
	//US_Get_distance_random
	CA_distance = US_Get_distance_random(45,55,1);
	(CA_distance <= CA_threshold)? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving));

	printf("CA_Driving State: distance = %d  Speed = %d\n",CA_distance,CA_speed);

}

int US_Get_distance_random (int l, int r, int count){

	//this Will generate random number in range l and r
	int i ;
	for(i=0;i<count;i++){
		int rand_num = (rand()%(r - l + 1)) + l;
		return rand_num ;
	}
	return 0 ;
}
