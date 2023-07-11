/*
 *  keypad.h
 *  Author: ENG.Ahmed Osamaa
 */


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

// keypad Port D

#define keyPORT PORTD
#define keyDDR DDRD
#define keyPIN PIND

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

// DRIVE FUNCTION

void keypad_init ();
char getkey() ;



#endif /* KEYPAD_H_ */