/* US.c
 * Author: ENG. Ahmed Osamaa
 */
#include "US.h"
//prototype US_Get_distance_random
int US_Get_distance_random (int l, int r, int count);
// variables
int US_distance = 0 ;

//State pointer to function
void (*US_state)();

// define functions

void US_init (){
	//init US Driver
	printf("US_init \n");
}

STATE_define(US_busy){
	//State name
	US_state_id = US_Busy ;
	//State action
	US_distance = US_Get_distance_random(45,55,1);

	printf("US_busy State: distance = %d\n",US_distance);

	// State connection
	US_SET_distance (US_distance);

	US_state = STATE(US_busy);
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
