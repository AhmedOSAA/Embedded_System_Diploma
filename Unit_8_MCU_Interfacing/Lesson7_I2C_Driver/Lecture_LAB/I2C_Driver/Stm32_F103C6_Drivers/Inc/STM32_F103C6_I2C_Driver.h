/* STM32_F103C6_I2C_Driver.h
 * Author: ENG. Ahmed Osamaa
 */

#ifndef INC_STM32_F103C6_I2C_DRIVER_H_
#define INC_STM32_F103C6_I2C_DRIVER_H_

// includes

#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"
#include "STM32_F103C6_RCC_Driver.h"

//=======================================
// Configuration structure
//=======================================


typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_MATCHED,
	I2C_EV_DATA_REQ,
	I2C_EV_DATA_RCV
} Slave_State;

struct S_I2C_Slave_Device_Address
{
	uint16_t Duel_ADD ;						// Enable = 1   Disable = 0
	uint16_t Primary_slave_address ;
	uint16_t Secondary_slave_address ;
	uint16_t I2C_Addressing_Slave_Mode;  	//@ref I2C_Addressing_Slave_Mode_define
};

typedef struct
{
	uint32_t							ClockSpeed ;					// Specify the clock frequency
																		// This parametar must be set based on @ref I2C_SCLK_define .

	uint32_t 							StretchMode;					// Enable and disable clock stretching
																		// This parametar must be set based on @ref I2C_StretchMode_define .

	uint32_t							 Mode;							// Enable and disable clock stretching
																		// This parametar must be set based on @ref I2C_Mode_define .

	struct S_I2C_Slave_Device_Address  	 I2C_Slave_Device_Address;		// Set Slave Address
																		// This parametar must be set based on @ref I2C_Addressing_Slave_Mode_define .

	uint32_t							 ACK_Control;					// Enable and disable ACK
																		// This parametar must be set based on @ref I2C_ACK_define .

	void (* P_Slave_Event_CallBack)(Slave_State state);					// Enable and disable ACK
																		// This parametar must be set based on @ref I2C_ACK_define .

}I2C_Config;


//=======================================
//Macros configuration reference
//=======================================

// @ref I2C_SCLK_define

/*
 * Standerd speed (up to 100 KHz)
 * Fast speed (up to 400 KHz)
 * >> To configure Clock before enable the Peripheral
 * 		• I2C_CR2 FREQ[5:0]: Peripheral clock frequency
 * 			1- Configure the clock control registers
 * 				Thigh = CCR * TPCLK1
 * 				SM or FM
 *			2- Configure the rise time register
 *				>> I2C_TRISE
 *			3- Program the I2C_CR1 register to enable the peripheral
 * */


#define I2C_SCLK_SM_50K		(50000U)
#define I2C_SCLK_SM_100K	(100000U)
#define I2C_SCLK_FM_200K	(200000U)// Fast Mode Not Supported yet
#define I2C_SCLK_SM_400K	(400000U)

// @ref I2C_StretchMode_define

#define I2C_StretchMode_Enable		(0x0)
#define I2C_StretchMode_Disable		I2C_CR1_NOSTRETCH

// @ref I2C_Mode_define

#define I2C_Mode_I2C		(0)
#define I2C_Mode_SMBus		I2C_CR1_SMBUS

//@ref I2C_Addressing_Slave_Mode_define
// Bit 15 ADDMODE Addressing mode (slave mode)
// 0: 7-bit slave address (10-bit address not acknowledged)
// 1: 10-bit slave address (7-bit address not acknowledged)
#define I2C_Addressing_Slave_Mode_7BIT			0
#define I2C_Addressing_Slave_Mode_10BIT			(uint16_t)(1<<15)


// @ref I2C_ACK_define
/*I2C_CR1 >> Bit 10 ACK: Acknowledge enable
This bit is set and cleared by software and cleared by hardware when PE=0.
0: No acknowledge returned
1: Acknowledge returned after a byte is received (matched address or data)*/

#define I2C_ACK_Enable						(I2C_CR1_ACK)
#define I2C_ACK_Disable 					0

//=======================================
//		   	Generic Structure
//=======================================

typedef enum
{
	With_Stop,
	Without_Stop
}Stop_Condition;

typedef enum
{
	START,
	REPEATED_START
}Repeated_Start;

typedef enum {DISABLE = 0, ENABLE = 1}FunctionalState ;
typedef enum {RESET = 0, SET = 1}FlagStatus ;
typedef enum {I2C_Direction_Transmitter = 0, I2C_Direction_Receiver = 1} I2C_Direction ;

#define I2C_EVENT_MASTER_BYTE_TRANSMITTING				((uint32_t)0x00070080) // Checking on " TRA , BUSY , MSL , TXE flags "

typedef enum
{
	I2C_FLAG_BUSY = 0,
	EV5,      // EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address
	EV6,	  // EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	EV8,	  // EV8: TxE=1, shift register not empty, d. ata register empty, cleared by writing DR registe
	EV8_1,
	EV7,	  // EV7: RxNE=1
	MASTER_BYTE_TRANSMITTING = ((uint32_t)0x00070080)	// Checking on " TRA , BUSY , MSL , TXE flags "

}Status ;


//=======================================
//					APIs
//=======================================

void MCAL_I2C_Init(I2C_typedef* I2Cx , I2C_Config * I2C_CONFIG);

void MCAL_I2C_DeInit(I2C_typedef* I2Cx) ;

void MCAL_I2C_GPIO_Set_Pins (I2C_typedef* I2Cx) ;

// Master Polling Mechanism

void MCAL_I2C_Master_TX (I2C_typedef* I2Cx , uint16_t devAddr , uint8_t* dataOut , uint32_t dataLen , Stop_Condition Stop , Repeated_Start Start) ;
void MCAL_I2C_Master_RX (I2C_typedef* I2Cx , uint16_t devAddr , uint8_t* dataIN  , uint32_t dataLen , Stop_Condition Stop , Repeated_Start Start) ;

// Slave Interrupt Mechanism
void MCAL_I2C_Slave_TX (I2C_typedef* I2Cx , uint8_t data);
uint8_t MCAL_I2C_Slave_RX (I2C_typedef* I2Cx);


// Generic APIs

void I2C_GenerateSTART (I2C_typedef* I2Cx , FunctionalState NewState , Repeated_Start Start) ;
void I2C_GenerateStop (I2C_typedef* I2Cx , FunctionalState NewState) ;
FlagStatus I2C_GetFlagStatus (I2C_typedef* I2Cx , Status Flag) ;
void I2C_SendAddress (I2C_typedef* I2Cx , uint8_t Address , I2C_Direction Direction ) ;
void I2C_AcknowledgeConfig(I2C_typedef* I2Cx , FunctionalState NewState);


#endif /* INC_STM32_F103C6_I2C_DRIVER_H_ */
