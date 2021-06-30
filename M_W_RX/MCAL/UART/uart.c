#include "uart.h"


void iniatUart(uint16_t baudrate )
{
	uint16_t ubrr= (osc/16/baudrate) - 1;
	UCSRC= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
	UCSRB= (1<<RXEN)| (1<<TXEN);
	UBRRH=ubrr>>8;
	UBRRL=(uint8_t)ubrr;
	
}
void sendChar(char ch)
{
	while( ( UCSRA & (1<<UDRE) ) == 0 );
	UDR=ch;
}
char receiveChar()
{
	
	while (  (UCSRA & (1<<RXC)  ) ==0 );
	return UDR;
}

