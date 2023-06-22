/*ENG. Ahmed Osamaa
 *main.c
 *Interrupt LAP 3
 */
// Clock speed 8 MHZ
#define F_CPU 8000000UL
// clock is enabled by default

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
typedef volatile unsigned char vc8_t ;

#define Base 0x20

// INTR.
#define mySREG *(vc8_t*)(Base + 0x3F)
#define myMCUCR *(vc8_t*)(Base + 0x35)
#define myGICR *(vc8_t*)(Base + 0x3B)


void INT_init ()
{
	/* NOTE you should config the EXT int firstly with (MCUCR)&(MCUSCR)
	 * then enable them by (GICR) then enable general int in (SREG)
	 * to avoid making Irq with flag register by (GIFR) because of 
	 * the default value of EXTI0 & EXTI 1 mode is The low level  generates an interrupt request   */
	//Make INT 0 (Any logic Change 01)
	myMCUCR |= 1<<0 ;
	//Make INT 1 (The rising edge 11)
	myMCUCR |= 0b11<<2 ;
	// Enable All EXTI
	myGICR |= 0b111<<5 ;
	//Global Interrupt Enable
	mySREG |= 1<<7 ;
}

// GPIO
#define myPORTA *(vc8_t*)(Base + 0x1B)
#define myDDRA *(vc8_t*)(Base + 0x1A)
#define myPORTB *(vc8_t*)(Base + 0x18)
#define myDDRB *(vc8_t*)(Base + 0x17)
#define myPORTD *(vc8_t*)(Base + 0x12)
#define myDDRD *(vc8_t*)(Base + 0x11)


void GPIO_init ()
{
	// myPORTA pin 0 1 2 output
	myDDRA |= 0b111<<0 ;
}

int main ()
{
	INT_init ();
	GPIO_init ();

	while (1){
		myPORTA = 0x0 ;
	}
	return 0 ;
}

// ISR INT0,1,2
ISR(INT0_vect)
{
	myPORTA |= (1<<0) ;
	_delay_ms(100);
}
ISR(INT1_vect)
{
	myPORTA |= (1<<1) ;
	_delay_ms(100);
}
ISR(INT2_vect)
{
	myPORTA |= (1<<2) ;
	_delay_ms(100);
}


