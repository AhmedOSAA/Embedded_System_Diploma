/* DC.h
 * Author: ENG. Ahmed Osamaa
 */
#ifndef DC_H_
#define DC_H_

#include "state.h"
//Define states

enum{
	DC_Idle ,
	DC_Busy
}DC_state_id;

// declare states functions DC
STATE_define(DC_idle);
STATE_define(DC_busy);

void DC_init();

//declaration State pointer to function
extern void (*DC_state)();


#endif /* DC_H_ */
