#include "PS_driver.h"
//Variables
static int Pval = 0;

//connection function
void send_Pval(int Val){
	Pval = Val ;
	PSdriver_state = STATE(Sending);
}

//State Pointer to function
void (*PSdriver_state)();

//Define function 

void PS_D_init (){
//init pressure sensor driver
}

STATE_define(Reading){
	//State name
	PSdriver_state_id = Reading ;
	//Read is done//
}
STATE_define(Sending){
	//State name
	PSdriver_state_id = Sending ;
	//send to algo
	Algo_read_Pval(Pval);
	
	PSdriver_state = STATE(Reading);
}
