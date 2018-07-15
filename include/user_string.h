#ifndef __USER_STRING_H__
#define __USER_STRING_H__
#include "stdint.h"

int srting_to_hex(uint8_t *dest, uint8_t *src, uint8_t len);

void hex_to_string(uint8_t *dest, uint8_t *src, uint8_t len);
uint32_t str_to_u32(char *str);
char *strim(char *str);

#endif	//__USER_STRING_H__
