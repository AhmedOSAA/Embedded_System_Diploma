/* CA.h
 * Author: ENG. Ahmed Osamaa
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"
//Define states
enum{
	CA_Waiting ,
	CA_Driving
}CA_state_id;

// declare states functions CA

STATE_define(CA_waiting);
STATE_define(CA_driving);

//declaration State pointer to function
extern void (*CA_state)();

#endif /* CA_H_ */
