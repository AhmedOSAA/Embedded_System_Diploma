/*
 *  kaypad.c
 *  Author: ENG.Ahmed Osamaa
 */

#include "keypad.h"

//make array for row & array for column
int row[] = {R0,R1,R2,R3};
int column[] = {C0,C1,C2,C3};


void keybad_GPIO_init (){
	GPIO_PinConfig_t PinCfg ;
	// make Row input R0 , R1 ,R2 ,R3
	//PB0,PB1,PB3,PB4  configure as input Pull-UP in real
	PinCfg.GPIO_PinNumber = R0 ;
	//PinCfg.GPIO_MODE = GPIO_MODE_INPUT_PU ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(keyPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = R1 ;
	//PinCfg.GPIO_MODE = GPIO_MODE_INPUT_PU ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(keyPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = R2 ;
	//PinCfg.GPIO_MODE = GPIO_MODE_INPUT_PU ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(keyPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = R3 ;
	//PinCfg.GPIO_MODE = GPIO_MODE_INPUT_PU ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(keyPORT, &PinCfg);


	// make Column Output C0,C1,C2,C3
	//PB5,PB6,PB7,PB8  configure as output with speed 10MHz
	PinCfg.GPIO_PinNumber = C0 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(keyPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = C1 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(keyPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = C2 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(keyPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = C3 ;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinCfg.GPIO_output_speed = GPIO_SPEED_10M ;
	MCAL_GPIO_init(keyPORT, &PinCfg);


}

void keypad_init(){
	/*
	// make column output
	keyDDR |= ((1<<C0)|(1<<C1)|(1<<C2)|(1<<C3));
	// make row input
	keyDDR &= ~((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));
	// put high signal on all pin of keypad
	keyPORT = 0xFF ;
	 */
	keybad_GPIO_init ();
	// Put high signal on all pin of keypad
	MCAL_GPIO_WritePort(keyPORT, 0xFFFF) ;

}

char getkey(){
	int i , j ;
	for(i=0;i<4;i++){
		//keyPORT &= ~(1<<column[i]);
		MCAL_GPIO_WritePin(keyPORT, column[i], GPIO_PIN_RESET);
		for(j=0;j<4;j++){
			if(MCAL_GPIO_ReadPin(keyPORT, row[j]) == 0){         // check that any button is pressed  (keyPIN>>row[j])&1)
				while(MCAL_GPIO_ReadPin(keyPORT, row[j]) == 0);  // for single press
				switch(i){
				case 0:
					if( j == 0 )return '7' ;
					if( j == 1 )return '4' ;
					if( j == 2 )return '1' ;
					if( j == 3 )return '!' ;
					break;
				case 1:
					if( j == 0 )return '8' ;
					if( j == 1 )return '5' ;
					if( j == 2 )return '2' ;
					if( j == 3 )return '0' ;
					break;
				case 2:
					if( j == 0 )return '9' ;
					if( j == 1 )return '6' ;
					if( j == 2 )return '3' ;
					if( j == 3 )return '=' ;
					break;
				case 3:
					if( j == 0 )return '/' ;
					if( j == 1 )return 'x' ;
					if( j == 2 )return '-' ;
					if( j == 3 )return '+' ;
					break;
				}
			}
		}
		//keyPORT |= (1<<column[i]);
		MCAL_GPIO_WritePin(keyPORT, column[i], GPIO_PIN_SET);
	}
	return 'E';
}





