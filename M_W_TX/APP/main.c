#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef F_CPU
# define F_CPU 8000000UL
#endif
#include <util/delay.h>
#include "../HAL/keypad/KEYBOARD.h"
#include "../MCAL/UART/uart.h"

#define START_PIN		0
#define START_DIR 		DDRA
#define START_PORT		PORTA
#define START_READ()	(PINA & (1<<START_PIN))




void read_send_option();
void read_send_time();
void wait_start_pushed();


//TX

int main()
{


START_DIR&=~(1<<0);
START_PORT|=(1<<0);  //internal pull up
DDRD|=(1<<5);

keyboardIntiat();
iniatUart(9600);

PORTD|=1<<2;
MCUCR=(1<<ISC01);
GICR=1<<INT0;
sei();


while(1)
{
	PORTD|=(1<<5);

	read_send_option();
	read_send_time();
	wait_start_pushed();
}


return 0;
}

void read_send_option()
{
	char option;
	do{

		option=keyboardScan();
	}
	while(option !='/' && option !='*' && option !='-' && option !='+');

	sendChar(option);
}
void read_send_time()
{
 char ch;
 uint8_t size=0;
 do
 {
	 ch=keyboardScan();
	 if(ch >= '0' && ch <='9')
	 {
		 sendChar(ch);
		 ++size;
	 }
	 else
	 {
		 //invaild key
	 }
 }
 while(ch != '=' && size <=4);
 sendChar('=');
}
void wait_start_pushed()
{
	uint8_t prev_state;
	static uint8_t  state=1;
	do
	{
		do
		{
		prev_state=state;
		state=START_READ();
		}
		while(  (state==1) || (prev_state==0)   );
	_delay_ms(2);
	state=START_READ();
	PORTB=0;
	}
	while(  (state==1) || (prev_state==0) );


		sendChar('=');



}

ISR(INT0_vect)
{

	PORTD&=~(1<<5);


}
