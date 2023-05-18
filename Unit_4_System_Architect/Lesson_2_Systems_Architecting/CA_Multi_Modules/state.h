/* state.h
 * Author: ENG. Ahmed Osamaa
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <stdlib.h>

// Automatic state function generated

#define STATE_define(_statFUN_) void ST_##_statFUN_()
#define STATE(_statFUN_) ST_##_statFUN_


// State connection
void US_SET_distance (int d);
void DC_SET_Motor (int s);


#endif /* STATE_H_ */
