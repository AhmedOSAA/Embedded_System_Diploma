/* main.c
 * Author: ENG. Ahmed Osamaa
 */
#include "US.h"
#include "CA.h"
#include "DC.h"

void setup (){

	// init all the drivers
	// init  IRQ...
	// init HAL US_Driver & DC_Driver
	// init Block
	US_init();
	DC_init();
	// Set State pointer for each block

	US_state = STATE(US_busy);
	CA_state = STATE(CA_waiting);
	DC_state = STATE(DC_idle);
}

int main(){
	setup();

	while(1){
		// Call state for each Block
		US_state();
		CA_state();
		DC_state();
		for(volatile int d = 0 ;d <= 1000 ;d++);
	}
	return 0 ;
}

