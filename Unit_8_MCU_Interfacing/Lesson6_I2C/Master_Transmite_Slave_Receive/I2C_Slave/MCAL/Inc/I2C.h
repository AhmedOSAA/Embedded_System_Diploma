/* I2C.h
 * Created: 7/10/2023 4:09:39 PM
 * Author : ENG.Ahmed Osamaa
 */ 

#ifndef I2C_H_
#define I2C_H_

#include "MemoryMap.h"

//=======================================
// Pins Configuration
//=======================================

#define  SCL			0
#define  SDA			1

//=======================================
// Configuration structure
//=======================================

typedef struct{
	uint8_t I2C_EN ;					// Specify SPI Enable / Disable
	// This parameter must be set based on @ref I2C_define
	
	uint8_t MODE ;						// Specify mode of SPI act as Master or slave
	// This parameter must be set based on @ref I2C_Mode_define
	
	uint8_t BR ;				// TWBR selects the division factor for the bit rate generator.
	// This parameter must be set based on this Equation : I2C frq = (CPU CLK Frq)/(16+(2*(TWBR)*(PrescalerValue)))
	
	uint8_t Prescaler ;				// TWI Prescaler 
	// This parameter must be set based on @ref I2C_Prescaler_define
	
	uint8_t AD ;				// (Slave) Address Register
	
	uint8_t Interrupt_EN ;				// Specify Interrupt Enable / Disable
	// This parameter must be set based on @ref I2C_Interrupt_define
	
}I2C_Config;


//=======================================
//Macros configuration reference
//=======================================

// @ref I2C_define
#define I2C_Enable					   (uint8_t)(1<<I2CEN)
#define I2C_Disable					   (0)

//@ref I2C_Mode_define

#define I2C_Master					   (1)
#define I2C_Slave					   (0)

//@ref I2C_Prescaler_define

#define I2C_Prescaler_1			(0)
#define I2C_Prescaler_4			(1)
#define I2C_Prescaler_16		(2)
#define I2C_Prescaler_64		(3)


//=======================================
//  Status Codes
//=======================================

#define start_transmitted		(uint8_t)(0x08)
#define Rstart_transmitted		(uint8_t)(0x10)
#define SLA_ACK_transmitted		(uint8_t)(0x18)
#define SLA_NACK_transmitted	(uint8_t)(0x20)
#define SLAR_ACK_transmitted	(uint8_t)(0x40)
#define SLAR_NACK_transmitted	(uint8_t)(0x48)
#define Data_ACK_transmitted	(uint8_t)(0x28)
#define Data_NACK_transmitted	(uint8_t)(0x30)
#define Data_ACK_slavetransmitted	(uint8_t)(0xB8)
#define LData_ACK_slavetransmitted	(uint8_t)(0xC8)
#define Data_NACK_slavetransmitted	(uint8_t)(0xC0)
#define Data_ACK_Received		(uint8_t)(0x50)
#define Data_NACK_Received		(uint8_t)(0x58)
#define Data_ACK_slaveReceived	(uint8_t)(0x80)
#define Data_NACK_slaveReceived	(uint8_t)(0x88)
#define Arbitration_lost		(uint8_t)(0x38)
#define Arbitration_lost_andAD	(uint8_t)(0x68)
#define SLA_W_slave_received	(uint8_t)(0x60)
#define SLA_R_slave_received	(uint8_t)(0xA8)

//=======================================
// Generic variable 
//=======================================

// typedef enum {
// 	I2C_Write = 0,
// 	I2C_Read = 1,
// 	I2C_Slave
// 	}I2C_Command; 

//=======================================
//  APIs
//=======================================

void I2C_init(I2C_Config * config);

void I2C_Start();
void I2C_Master_Write(uint8_t data);
uint8_t I2C_Master_Read();
void I2C_stop();

void I2C_Slave_Write(uint8_t data);
uint8_t I2C_Slave_Read();

#endif /* I2C_H_ */