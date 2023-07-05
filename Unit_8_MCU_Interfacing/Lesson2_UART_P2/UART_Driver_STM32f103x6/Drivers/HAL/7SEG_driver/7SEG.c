/*  7SEG.c
 *  Author: ENG.Ahmed Osamaa
 */

#include "7SEG.h"

void SEG7_init()
{
	GPIO_PinConfig_t PinCfg ;
	//Configure pin in output mode with speed 10MHz
	//P1>>P7 is PB9 >> PB15
	PinCfg.GPIO_PinNumber = P1 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(SEG7_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = P2 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(SEG7_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = P3 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(SEG7_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = P4 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(SEG7_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = P5 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(SEG7_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = P6 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(SEG7_PORT, &PinCfg);

	PinCfg.GPIO_PinNumber = P7 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(SEG7_PORT, &PinCfg);

}


void SEG7_display_NUM(uint8_t Value){
	MCAL_GPIO_WriteINPort(SEG7_PORT, Value, GPIO_PARTIAL_PORT_2Nibble , 9);
}
