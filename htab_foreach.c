// htab_foreach.c
// Solution: IJC-DU2, example 2), 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4

#include "htable.h"
#include <stdio.h>

void htab_foreach(htab_t *t, void (*cbfunc)(const char *, unsigned)) {
	for (unsigned i = 0; i < t->htab_size; ++i) {
		for (struct htab_listitem *tmp = t->arrptr_list[i];
			tmp != NULL; tmp = tmp->next) 
		{
			cbfunc(tmp->key, tmp->data);
		}
	}
}