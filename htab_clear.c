// htab_clear.c
// Solution: IJC-DU2, example 2), 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4

#include "htable.h"
#include <stdlib.h>

static void htab_list_delete(struct htab_listitem *item) {
	if (item == NULL)
		return;

	htab_list_delete(item->next);
	free(item->key);
	free(item);
}

void htab_clear(htab_t *t) {
	for (unsigned i = 0; i < t->htab_size; ++i) {
		htab_list_delete(t->arrptr_list[i]);
	}
}