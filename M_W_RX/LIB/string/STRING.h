#ifndef _STRING_H_
#define _STRING_H_

#include <stdint.h>


void str_copy(char *source,char *destination);
uint8_t str_equal(char *str1,char *str2);
uint8_t str_len(char *str);
char * intToString(uint16_t num);

#endif
