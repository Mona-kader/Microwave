#include "LCD.h"


static void proper_row();
static uint8_t _row=1;
static uint8_t _column=1;
void LCDIntiat()
{
	
	LCD_CDDR|=(1<<EN)|(1<<RS);
	_delay_ms(15); //wait till  lcd fully powered up
	#ifdef _4bitMode
	LCD_DDDR|=0xf0;
	//LCDSendCmd(0x33);
	LCDSendCmd(0x32);
	LCDSendCmd(0x28);


	#else
	LCD_DDDR=0xff;
	LCDSendCmd(0x38);
	#endif
	LCDSendCmd(0x0C);
	LCDSendCmd(0x01);
	//LCDSendCmd(0x0f);
	
	LCDRowColumn(1,1);
	_row=_column=1;


}

void LCDSendCmd(uint8_t cmd)
{
	LCD_CPORT&=~(1<<RS);
	#ifdef _4bitMode
	//4 bit mode
	LCD_DPORT=(LCD_DPORT&0x0f)|(cmd&0xf0);
	LCD_CPORT|=(1<<EN);
	_delay_us(0.5);
	LCD_CPORT&=~(1<<EN);
	_delay_us(70);
	LCD_DPORT=( (cmd<<4) & (0xf0) )|((LCD_DPORT&0x0f));

	#else
	//8 bit mode
	LCD_DPORT=cmd;
	#endif

	LCD_CPORT|=1<<EN;
	_delay_us(0.3);
	LCD_CPORT&=~(1<<EN);


	switch(cmd)
	{
		case 0x01:
		case 0x02:
		_delay_us(2000);
		break;
		default:
		_delay_us(200);
		break;
	}

}

void LCDSendChar(char data)
{


	LCD_CPORT|=1<<RS;
	#ifdef  _4bitMode

	LCD_DPORT=(LCD_DPORT&0x0f)|(data&0xf0);
	LCD_CPORT|=(1<<EN);
	_delay_us(0.3);
	LCD_CPORT&=~(1<<EN);
	
	_delay_us(100);
	LCD_DPORT=( (data<<4) & (0xf0) )|(LCD_DPORT&0x0f);

	#else
	LCD_DPORT=data;
	#endif

	LCD_CPORT|=1<<EN;
	_delay_us(0.3);
	LCD_CPORT&=~(1<<EN);
	_delay_us(100);
	
	
	proper_row();

	   
	
	
}

static void proper_row()
{

		++_column;
		if(_column>COLUMN_SIZE)
		{
			_row++;
			_column=1;
			LCDRowColumn(_row , 1);
	    }
}
void LCDRowColumn(uint8_t row,uint8_t column)
{
	_row=row;
	_column=column;
	uint8_t firstCharAdress[]={0x80,0xc0,0x94,0xD4};
	LCDSendCmd(firstCharAdress[_row-1]+_column-1);
}
void LCDPrint(char str[])
{
	uint8_t i=0;
	
	while(str[i]!=0)
		LCDSendChar(str[i++]);
		
}

void LCDClearScreen()
{
LCDSendCmd(0x01);
_row=_column=1;
LCDRowColumn(1,1);

}
