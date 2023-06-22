/*ENG. Ahmed Osamaa
 *main.c
 *GPIO LAP
 */
// Clock speed 8 MHZ
#define F_CPU 8000000UL
// clock is enabled by default

typedef volatile unsigned char vc8_t ;

#define Base 0x20

// GPIO

#define PORTD_R *(vc8_t*)(Base + 0x12)
#define DDRD_R *(vc8_t*)(Base + 0x11)

void delay(int x)
{
	int i , j ;
	for(i=0 ; i<= x ; i++)
		for (j=0 ; j<255 ; j++);
}

void GPIO_init ()
{
	// If DDxn is written logic 'one', Pxn is configured as an output pin.
	// If DDxn is written logic 'zero', Pxn is configured as an input pin.
	// PORTD pin 4 5 6 7 output
	DDRD_R |= (0b1111<<4) ;
}

int main ()
{
	GPIO_init ();

	while (1){
		PORTD_R ^= (1<<5) ;
		delay(3000) ;
		PORTD_R ^= (1<<5) ;
		PORTD_R ^= (1<<6) ;
		delay(3000) ;
		PORTD_R ^= (1<<6) ;
		PORTD_R ^= (1<<7) ;
		delay(3000) ;
		PORTD_R ^= (1<<7) ;
		PORTD_R ^= (1<<4) ;
		delay(3000) ;
		PORTD_R ^= (1<<4) ;
	}
	
	return 0 ;
}
