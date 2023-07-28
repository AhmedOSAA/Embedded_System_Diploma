/* I2C.h
 * Created: 7/10/2023 4:09:39 PM
 * Author : ENG.Ahmed Osamaa
 */ 


#include "I2C.h"

//=======================================
//	Generic Macros
//=======================================

// Control Transition function Macro , Setting TWINT bit flag.
#define transition()	I2CCR |= (1<<I2CINT)
// Checking TWINT flag is 1 or 0
#define CKINT()			while(!(I2CCR & (1<<I2CINT)))
// Checking value of statues register
#define StatueR			(I2CSR & 0xf8)



/*  =================================================  */


//=======================================
//	Generic Function
//=======================================



/*  =================================================  */

//=======================================
//		APIs
//=======================================

void I2C_init(I2C_Config * config)
{
	if (config->MODE == I2C_Master){
		I2CBR = config->BR ;
		I2CSR = config->Prescaler ;
	}else if(config->MODE == I2C_Slave){
		//TWAR and TWCR have been initialized as a slave
		I2CAR  = config->AD ;
	} 
	I2CCR |= config->I2C_EN ;
}


void I2C_Start()
{
	I2CCR |= (1<<I2CINT) | (1<<I2CSTA) ;
	CKINT();
	while (StatueR != start_transmitted);
}
void I2C_Master_Write(uint8_t data)
{
	I2CDR = data ;
	I2CCR = (1<<I2CINT) | (1<<I2CEN) ;
	CKINT();
	while (StatueR != SLA_ACK_transmitted && StatueR != Data_ACK_transmitted && StatueR != SLAR_ACK_transmitted);
}
uint8_t I2C_Master_Read()
{
	I2CCR = (1<<I2CINT)| (1<<I2CEA) | (1<<I2CEN) ;
	CKINT();	
	while (StatueR != Data_ACK_Received);
	return I2CDR ;
}
void I2C_stop()
{
	I2CCR |= (1<<I2CINT) | (1<<I2CSTO);
}




void I2C_Slave_Write(uint8_t data)
{
	I2CDR = data ; 
	I2CCR = (1<<I2CINT) | (1<<I2CEN );
	CKINT();
	while (StatueR != Data_NACK_slavetransmitted);
}
uint8_t I2C_Slave_Read()
{
	// Receive SLA
	I2CCR = (1<<I2CINT) |  (1<<I2CEA) | (1<<I2CEN );
	CKINT();
	while (StatueR != SLA_W_slave_received);
	if ((I2CDR & 1) == 0 ){
		//Receiving Data
		transition();
		CKINT();
		return I2CDR ;
	}
}
