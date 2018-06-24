#ifndef __USER_STRING_H__
#define __USER_STRING_H__
#include "stdint.h"

void Srting_to_Hex(uint8 *dest, uint8 *src, uint8 length);
void Hex_To_SmallString(uint8_t *dest, uint8_t *src, uint8_t length);
uint32 strtou32(char *str);
char *strim(char *str);//去除空格和tab不可见字符

#endif	//__USER_STRING_H__
