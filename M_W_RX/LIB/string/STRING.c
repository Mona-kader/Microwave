#include "STRING.h"





void str_copy(char *source,char *destination)
{
    uint8_t i=0;
    while( (source[i]=destination[i]) )
    {

        i++;
    }
}
uint8_t str_equal(char *str1,char *str2)
{
    uint8_t size1=0,size2=0,is_equal=1;

    while(str1[size1++] !=0);
    while(str2[size2++] !=0);
    if(size1 != size2)
    {
        is_equal=0;
    }
    else
    {
        for(--size1;size1 > 0;size1 --)
        {
            if( str1[size1-1] != str2[size1-1])
                return is_equal=0;
        }
    }
    return is_equal;
}
uint8_t str_len(char *str)
{
    uint8_t size=0;
    while(str[size++]!=0);

    return --size;
}

char * intToString(uint16_t num)
{
    static  char str[8];
    char temp;
	uint8_t size=0;

	if(num<10)
	{
		str[size++]=num+0x30;
	}

	else
	{

	    while(num)
		{
			str[size]= (num%10)+0x30;
			num/=10;
			size++;
		}

	   for (uint8_t i=0  ;i < (size/2) ;i++)
		{
			temp=str[i];
			str[i]=(str[size-i-1]);
			str[size-i-1]=temp;
		}
	}

	str[size]=0;
	return str;
}
