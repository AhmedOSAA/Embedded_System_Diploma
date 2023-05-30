#ifndef STATE_H_
#define STATE_H_


//Automatic state function generated

#define STATE_define(_statFUN_) void ST_##_statFUN_()
#define STATE(_statFUN_) ST_##_statFUN_

// Modules connection

void send_Pval(int Val);   //PS to PS_driver
void Algo_read_Pval(int Val);   //PS_driver to main Algo
void high_pressure();   // algo to alarm
void start_alarm(); // Alarm to actuator
void stop_alarm();  // Alarm to actuator



#endif