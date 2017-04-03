// htab_free.c
// Solution: IJC-DU2, example 2), 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4

#include "htable.h"
#include <stdlib.h>

void htab_free(htab_t *t) {
	htab_clear(t);
	free(t);
}