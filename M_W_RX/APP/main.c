

#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include "../HAL/LCD/LCD.h"
#include "../MCAL/UART/uart.h"
#include "../LIB/string/STRING.h"
#include "../MCAL/timer/timer.h"

#define MOTOR_STOP() 			(TCCR0=0);\
	                             PORTA&=~(1<<0)
#define MOTOR_START(x)			(pwm_timer0( (x-40)*10 ))



#define DEBUG_STOP(string)   	  LCDClearScreen();\
							  	  LCDPrint(string);\
							  	  while(1)

#define ALARM_PIN		2
#define ALARM_DIR 		DDRB
#define ALARM_PORT		PORTB

#define  ALARM_START()	 (ALARM_PORT|=(1<<ALARM_PIN))
#define  ALARM_STOP()	 (ALARM_PORT&=~(1<<ALARM_PIN))


#define ALA_PIN		0
#define ALA_DIR 		DDRA
#define ALA_PORT		PORTA

#define  ALA_START()	 (ALA_PORT|=(1<<ALA_PIN))
#define  ALA_STOP()	 (ALA_PORT&=~(1<<ALA_PIN))


char read_option();
uint16_t read_entered_time();
void counter_show(uint16_t time );
void operation_show(char option);
char wait_start_or_cancel();
static uint8_t is_stop_forced=0;



//RX
int main()
{

	//PORTD=1<<2;
	MCUCR=(1<<ISC01);
	GICR=1<<INT0;
	sei();
uint16_t time_in_second;
char option;
LCDIntiat();
iniatUart(9600);


ALARM_DIR|=1<<ALARM_PIN;
ALA_DIR|=1<<ALA_PIN;

//LCDSendChar( receiveChar() );

while(1)
{


	option=read_option();
	time_in_second=read_entered_time();
	if(wait_start_or_cancel() == '=' )

	{
		LCDClearScreen();
		operation_show(option);
		MOTOR_START(option);
		ALA_START();
		counter_show(time_in_second);
		MOTOR_STOP();
		 ALA_STOP();
		if(is_stop_forced==0)
		{
			LCDPrint("finished!!!!");
			ALARM_START();
			_delay_ms(200);
			ALARM_STOP();
			LCDClearScreen();
		}

	}
	else
	{
		//cancel
	}
	is_stop_forced=0;


}


return 0;
}


char read_option()
{

	LCDPrint("A-COOKING C-POPCB-DEFROST D-BAKE");


	return receiveChar();
}
uint16_t read_entered_time()
{
	uint16_t time=0;
	char ch;
	char counter=3;
	LCDClearScreen();
	LCDPrint("OP TIME:");
	do
	{

		ch=receiveChar();
		if(ch >='0' && ch <= '9')
		{
			LCDSendChar(ch);
			time=time*10+ (ch-48);
		}

	}while(ch!= '=');


	return time;

}
char wait_start_or_cancel()
{
	char ch;
	LCDClearScreen();
	LCDPrint("PUSH START :) ");
	do{
		ch=receiveChar();
	}
	while( ch != '=' && ch != '<' );
	return ch;
}
void counter_show(uint16_t time )
{
	char time1,time0;

	time1=time/100;
	time0=time%100;
	if(is_stop_forced==0)
	{
		LCDRowColumn(2,1);

		LCDPrint("Time:");
		while((time1!=0)||(time0!=0))
		{
			if(is_stop_forced==1)
				{
					MOTOR_STOP();
					LCDClearScreen();
					LCDPrint("OPERATION IS STOP:(");
					_delay_ms(100);
					LCDClearScreen();
					return ;
				}


			if((time0==0)&&(time1>=1))
			{
				time1--;
				time0=59;
				LCDRowColumn(2,6);
							LCDPrint("  ");

									LCDRowColumn(2,6);
									LCDPrint( intToString(time1) );
									LCDRowColumn(2,8);
									LCDPrint(":");
									LCDRowColumn(2,9);
								    LCDPrint("  ");
									LCDRowColumn(2,9);
									LCDPrint( intToString(time0) );


									timer1_delay_1s();
			}
			if(time0>1){

			LCDRowColumn(2,6);
			LCDPrint("  ");

					LCDRowColumn(2,6);
					LCDPrint( intToString(time1) );
					LCDRowColumn(2,8);
					LCDPrint(":");
					LCDRowColumn(2,9);
				    LCDPrint("  ");
					LCDRowColumn(2,9);
					LCDPrint( intToString(time0) );

					time0--;
					timer1_delay_1s();


			}
			if(time0==1){


				LCDRowColumn(2,6);
				LCDPrint("  ");

				LCDRowColumn(2,6);
				LCDPrint( intToString(time1) );
				LCDRowColumn(2,8);
			    LCDPrint(":");
			    LCDRowColumn(2,9);
			    LCDPrint("  ");


				LCDRowColumn(2,9);
				LCDPrint( intToString(time0) );


				timer1_delay_1s();

				time0--;

				LCDRowColumn(2,6);
				LCDPrint("  ");

				LCDRowColumn(2,6);
				LCDPrint( intToString(time1) );
				LCDRowColumn(2,8);
				LCDPrint(":");
				LCDRowColumn(2,9);
				LCDPrint("  ");


			  LCDRowColumn(2,9);
			LCDPrint( intToString(time0) );
			timer1_delay_1s();

			if(time1==0)
			{
				break;
			}
			else{
				time0=59;
				 time1--;
               }



			}



			}
	}
	LCDClearScreen();
}

void operation_show(char option)
{
	if(is_stop_forced==0)
	  {
		LCDClearScreen();
		LCDPrint("RUNNING:");
		switch(option)
		{
		case '/':
				LCDPrint("Cooking");
				break;
		case '*':
				LCDPrint("Defrost");
				break;
		case '-':
				LCDPrint("Popcorn");
				break;
		case '+':
				LCDPrint("Bake");
				break;

		}
	  }

}

ISR(INT0_vect)
{


	is_stop_forced=1;

}

