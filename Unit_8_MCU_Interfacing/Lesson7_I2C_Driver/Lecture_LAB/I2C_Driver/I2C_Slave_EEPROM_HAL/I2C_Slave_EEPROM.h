/*
 * I2C_Slave_EEPROM.h
 * Author: ENG. Ahmed Osamaa
 */


#ifndef INCLUDES_I2C_SLAVE_EEPROM_H_
#define INCLUDES_I2C_SLAVE_EEPROM_H_

#include "STM32_F103C6_I2C_Driver.h"


// EEPROM is an I2C Slave
// Idle Mode : devive is in high impedance state and waits for data.
// Master Transmitter mode : the device transmits data to a slave receiver
// Master Receiver Mode : the device receive data from a slave transmitter


#define EEPROM_Slave_Address		0x2A

void eeprom_init(void);
unsigned char eeprom_write_Nbytes(unsigned int Memory_address , uint8_t* bytes , uint8_t Data_Length);
unsigned char eeprom_read_Nbytes(unsigned int Memory_address , uint8_t* dataOut , uint8_t Data_Length);







#endif /* INCLUDES_I2C_SLAVE_EEPROM_H_ */
