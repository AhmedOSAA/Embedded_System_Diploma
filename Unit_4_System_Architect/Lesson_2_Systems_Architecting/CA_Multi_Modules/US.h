/* US.h
 * Author: ENG. Ahmed Osamaa
 */

#ifndef US_H_
#define US_H_
#include "state.h"

//Define states
enum{
	US_Busy
}US_state_id;

// declare states functions US
STATE_define(US_busy);

void US_init();

//declaration State pointer to function
extern void (*US_state)();


#endif /* US_H_ */
