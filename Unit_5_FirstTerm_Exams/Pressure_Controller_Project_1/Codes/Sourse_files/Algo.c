
#include "Algo.h"

// variables
static int Pval = 0  ;
int threshold = 20 ;

//connection function
void Algo_read_Pval(int Val){
	Pval = Val ;

}

//State Pointer to function
void (*algo_state)();

//Define function 
STATE_define(High_Pressure_Detector){
	//State name
	Algo_state_id = High_Pressure_Detector ;
	//condition
	if(Pval > threshold) high_pressure();
}
