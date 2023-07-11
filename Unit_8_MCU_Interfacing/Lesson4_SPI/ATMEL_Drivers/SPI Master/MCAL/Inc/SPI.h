/* SPI.h
 * Created: 7/10/2023 4:09:39 PM
 * Author : ENG.Ahmed Osamaa
 */ 

#ifndef SPI_H_
#define SPI_H_

// Include

#include "MemoryMap.h"

//=======================================
// Pins Configuration
//=======================================

#define  SS				4
#define  MOSI			5
#define  MISO			6
#define  SCK			7


//=======================================
// Configuration structure
//=======================================

typedef struct{
	uint8_t SPI_EN ;					// Specify SPI Enable / Disable
										// This parameter must be set based on @ref SPI_define
										
	uint8_t MODE ;						// Specify mode of SPI act as Master or slave
										// This parameter must be set based on @ref SPI_Mode_define
										
	uint8_t DataORD ;					// Specify the LSB or MSB of the data word is transmitted first.
										// This parameter must be set based on @ref SPI_DataORD_define
										
	uint8_t Data_Mode ;					// Specify mode of data is transmitted.
										// This parameter must be set based on @ref SPI_DataMode_define
									
	uint8_t Clock_Rate ;				// Specify the LSB or MSB of the data word is transmitted first.
										// This parameter must be set based on @ref SPI_Clock_Divide_define									
	
	uint8_t Interrupt_EN ;				// Specify Interrupt Enable / Disable
										// This parameter must be set based on @ref SPI_Interrupt_define
	
}SPI_Config;


//=======================================
//Macros configuration reference
//=======================================

// @ref SPI_define
#define SPI_Enable					   (uint8_t)(1<<6)
#define SPI_Disable					   (0)

// @ref SPI_Mode_define

#define SPI_Mode_Master				   (uint8_t)(1<<4)
#define SPI_Mode_Slave				   (0)

// @ref SPI_DataORD_define

#define SPI_DataORD_LSB					(uint8_t)(1<<5)
#define SPI_DataORD_MSB					(0)

// @ref SPI_DataMode_define

// SPI Mode		  / Conditions				/Leading Edge				/Trailing Edge
//	0				CPOL=0, CPHA=0				Sample	(Rising)				Setup	(Falling)
//	1				CPOL=0, CPHA=1				Setup	(Rising)				Sample	(Falling)
//	2				CPOL=1, CPHA=0				Sample	(Falling)				Setup	(Rising)
//	3				CPOL=1, CPHA=1				Setup	(Falling)				Sample	(Rising)

#define SPI_DataMode_Leading_RisingSample						(uint8_t)(0)
#define SPI_DataMode_Leading_FallingSample						(uint8_t)(2<<2)
#define SPI_DataMode_Trailing_RisingSample						(uint8_t)(3<<2)
#define SPI_DataMode_Trailing_FallingSample						(uint8_t)(1<<2)

// @ref SPI_Clock_Divide_define

// SPI2X SPR1 SPR0		 SCK Frequency
//	 0	  0	    0			fosc/4
//	 0	  0		1			fosc/16
//	 0	  1	    0			fosc/64
//	 0	  1	    1			fosc/128
//	 1	  0	    0			fosc/2
//	 1	  0		1			fosc/8
//	 1	  1		0			fosc/32
//	 1	  1		1			fosc/64

#define SPI_Clock_Divide_4								(uint8_t)(0<<0)
#define SPI_Clock_Divide_16								(uint8_t)(1<<0)
#define SPI_Clock_Divide_64								(uint8_t)(2<<0)
#define SPI_Clock_Divide_128							(uint8_t)(3<<0)
#define SPI_Clock_Divide_DS2							(uint8_t)(4<<0)    // DS >> Double speed , instead on divide by 4 divide by 2 and so on.
#define SPI_Clock_Divide_DS8							(uint8_t)(5<<0)
#define SPI_Clock_Divide_DS32							(uint8_t)(6<<0)
#define SPI_Clock_Divide_DS64							(uint8_t)(7<<0)

// @ref SPI_Interrupt_define

#define SPI_Interrupt_Enable			(uint8_t)(1<<7)				
#define SPI_Interrupt_Disable	        (0)


//=======================================
//***************  APIs  ****************
//=======================================

void SPI_Init (SPI_typedef* SPIx , SPI_Config* CONFIG);
void SPI_DeInit (SPI_typedef* SPIx);
unsigned char SPI_SendData (SPI_typedef* SPIx , unsigned char data);
uint8_t SPI_ReveiveData (SPI_typedef* SPIx , uint8_t dataTOsend);

#endif /* SPI_H_ */