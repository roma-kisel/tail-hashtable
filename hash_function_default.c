// hash_function_default.c
// Solution: IJC-DU2, example 2), 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4

#include "htable.h"

unsigned hash_function_default(const char *str, unsigned htab_size) {
	unsigned int h = 0;
	const unsigned char *p;
	for (p = (const unsigned char*)str; *p != '\0'; ++p) {
		h = 65599*h + *p;
	}

	return h % htab_size;
}