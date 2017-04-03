// htab_remove.c
// Solution: IJC-DU2, example 2), 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4

#include "htable.h"
#include <string.h>
#include <stdlib.h>

void htab_remove(htab_t *t, const char *key) {
	for (unsigned i = 0; i < t->htab_size; ++i) {
		struct htab_listitem **pre_item_adr = &t->arrptr_list[i];

		for (struct htab_listitem *tmp = t->arrptr_list[i]; 
			tmp != NULL; tmp = tmp->next) 
		{
			if (!strcmp(tmp->key, key)) {
				*pre_item_adr = tmp->next;
				--t->n;
				free(tmp->key);
				free(tmp);
				return;
			}
			pre_item_adr = &tmp->next;
		}
	}
}