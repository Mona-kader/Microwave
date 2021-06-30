#ifndef LCD_h_
#define LCD_h_
#ifndef F_CPU
# define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#define _4bitMode
//data ports
#define LCD_DDDR DDRA
#define LCD_DPORT PORTA
#define LCD_DPIN PINA
//command ports
#define LCD_CDDR DDRA
#define LCD_CPORT PORTA
#define LCD_CPIN PINA
#define EN 3
#define RS 2
#define COLUMN_SIZE 16
#define ROW_SIZE	2









void LCDIntiat();
void LCDSendCmd(uint8_t cmd);
void LCDSendChar(char data);
void LCDRowColumn(uint8_t row,uint8_t column);
void LCDPrint(char str[]);
void LCDClearScreen();


#endif
