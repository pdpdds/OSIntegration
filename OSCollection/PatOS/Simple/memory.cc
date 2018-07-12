#include "memory.h"


extern "C" void* memset(void *dest, char val, size_t count)
{
	unsigned char *temp = (unsigned char *)dest;
	for (; count != 0; count--, temp[count] = val);
	return dest;
}

extern "C" void *memcpy(void *dest, const void *src, size_t count)
{
	const char *sp = (const char *)src;
	char *dp = (char *)dest;
	for (; count != 0; count--) *dp++ = *sp++;
	return dest;
}