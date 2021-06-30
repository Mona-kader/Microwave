#ifndef KEYBOARD_h_
#define KEYBOARD_h_

#include <avr/io.h>
#ifndef F_CPU
# define F_CPU 8000000UL
#endif
#include <util/delay.h>

#define keyboardDDR 	DDRB
#define KeyboardPORT 	PORTB
#define keyboardPIN 	PINB

void keyboardIntiat();
uint8_t keyboardScan();




#endif
