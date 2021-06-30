#ifndef  _UART_H_
#define  _UART_h_

#include <avr/interrupt.h>
#include <stdint.h>


#define  osc   8000000



void iniatUart(uint16_t baudrate );
char receiveChar();
void sendChar(char ch);



#endif
