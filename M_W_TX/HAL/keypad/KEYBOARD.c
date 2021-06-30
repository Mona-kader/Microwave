#include "KEYBOARD.h"

void keyboardIntiat()
{
	keyboardDDR=0xf0;  //col input  //row output
	KeyboardPORT=0xff;
}
uint8_t keyboardScan()
{
	char matrix[4][4]={		{'1','2','3','/'},
							{'4','5','6','*'},
							{'7','8','9','-'},
							{'<','0','=','+'}
					    };
	
		uint8_t colLoc, rowLoc;
	
	do
	{
		KeyboardPORT&=0x0f;
		colLoc=keyboardPIN&0x0f;
		
	} while (colLoc!=0x0f);
	
	do
	{
		do
		{
			_delay_ms(20);
			
			colLoc=keyboardPIN&0x0f;
		} while (colLoc==0x0f);
		
		_delay_ms(20);            //call delay and check again if it is not noise
		
		colLoc=keyboardPIN&0x0f;
	} while (colLoc==0x0f);
	
	while(1)
	{
		
		
		KeyboardPORT=0xEF ; // keyboardPORT=0b1110 1111
		colLoc=keyboardPIN&0x0f;
		if (colLoc!=0x0f)
		{
			rowLoc=0;
			break;
		}
		KeyboardPORT=0xDF;
		colLoc=keyboardPIN & 0x0f;
		if (colLoc !=0x0f)
		{
			rowLoc=1;
			break;
		}
		KeyboardPORT=0xBF;
		colLoc=keyboardPIN & 0x0f;
		if (colLoc !=0x0f)
		{
			rowLoc=2;
			break;
		}
		KeyboardPORT=0x7F;
		colLoc=keyboardPIN & 0x0f;
		if (colLoc !=0x0f)
		{
			rowLoc=3;
			break;
		}
	}
	
	if (colLoc==0x0E)
	colLoc=0;
	else if (colLoc==0x0D)
	colLoc=1;
	else if (colLoc==0x0B)
	colLoc=2;
	else
	colLoc=3;
	

	 return matrix[rowLoc][colLoc];
	

}
