
#include "timer.h"
void timer1_delay_1s()
{
 TCNT1=0;
 OCR1A=2000;
 TCCR1A=0;
 TCCR1B=(1<<CS12)|(1<<WGM12);
 while( ( TIFR & (1<<OCF1A) ) ==0 );
 TIFR=(1<<OCF1A);

}

void pwm_timer0(uint8_t duty_cycle)
{
	DDRB|=1<<3;
	OCR0=(256*duty_cycle/100)-1;
	TCCR0=0x64;

}

