/*
 *  kaypad.c
 *  Author: ENG.Ahmed Osamaa
 */

#include "keypad.h"

//make array for row & array for column
int row[] = {R0,R1,R2,R3};
int column[] = {C0,C1,C2,C3};
	

void keypad_init(){

	// make column output
	keyDDR |= ((1<<C0)|(1<<C1)|(1<<C2)|(1<<C3));
	// make row input
	keyDDR &= ~((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));
	// put high signal on all pin of keypad
	keyPORT = 0xFF ;
}

char getkey(){
	int i , j ;
	for(i=0;i<4;i++){
		keyPORT &= ~(1<<column[i]);
		for(j=0;j<4;j++){
			if(((keyPIN>>row[j])&1)==0){         // check that any button is pressed
				while(((keyPIN>>row[j])&1)== 0); // for single press
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
		keyPORT |= (1<<column[i]);
	}
	return 'E';
}





