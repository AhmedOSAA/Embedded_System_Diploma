/*
 * main.c
 *
 *  Created on: May 17, 2023
 *      Author: midom
 */
#include "CA.h"

void setup (){

	// init all the drivers
	// init  IRQ...
	// init HAL US_Driver & DC_Driver
	// init Block
	// Set State pointer for each block

	CA_state = STATE(CA_waiting);
}

int main(){
	setup();

	while(1){
		// Call state for each Block
		CA_state();
		for(volatile int d = 0 ;d <= 1000 ;d++);
	}
	return 0 ;
}

