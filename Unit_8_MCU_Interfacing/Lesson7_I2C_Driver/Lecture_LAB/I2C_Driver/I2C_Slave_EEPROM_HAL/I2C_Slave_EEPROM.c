/*
 * I2C_Slave_EEPROM.c
 * Author: ENG. Ahmed Osamaa
 */

#include "I2C_Slave_EEPROM.h"

void eeprom_init(void)
{
	/* **** **** *** I2C1 INIT **** **** **** */
	// PB6 : I2C_SCL
	// PB7 : I2C_SDA

	I2C_Config I2C1CFG ;

	// I2C Controller act as a Master

	I2C1CFG.ACK_Control = I2C_ACK_Enable ;
	I2C1CFG.ClockSpeed  = I2C_SCLK_SM_100K ;
	I2C1CFG.Mode = I2C_Mode_I2C ;
	I2C1CFG.StretchMode = I2C_StretchMode_Enable ;
	I2C1CFG.P_Slave_Event_CallBack = NULL ;

	MCAL_I2C_GPIO_Set_Pins(I2C1) ;
	MCAL_I2C_Init(I2C1, &I2C1CFG);

}
unsigned char eeprom_write_Nbytes(unsigned int Memory_address , uint8_t* bytes , uint8_t Data_Length)
{
	uint8_t i=0 , buffer[256];

	buffer[0] = (uint8_t)(Memory_address >> 8) ; // upper byte Memory Address
	buffer[1] = (uint8_t)(Memory_address) ; // Lower byte Memory Address

	for (i = 2 ; i < (Data_Length+2) ; i++ )
	{
		buffer[i] = bytes[i-2] ;
	}

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address , buffer , (Data_Length+2) , With_Stop , START) ;
	return 0 ;

}
unsigned char eeprom_read_Nbytes(unsigned int Memory_address , uint8_t* dataOut , uint8_t Data_Length)
{
	uint8_t buffer[2];

	buffer[0] = (uint8_t)(Memory_address >> 8) ; // upper byte Memory Address
	buffer[1] = (uint8_t)(Memory_address) ; // Lower byte Memory Address

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, 2, Without_Stop, START);
	MCAL_I2C_Master_RX(I2C1, EEPROM_Slave_Address, dataOut, Data_Length, With_Stop, REPEATED_START);



}
