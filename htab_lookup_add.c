// htab_lookup_add.c
// Solution: IJC-DU2, example 2), 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4

#include "htable.h"
#include <stdlib.h>
#include <string.h>

struct htab_listitem *htab_lookup_add(htab_t *t, const char *key) {
	unsigned index = t->hash_fun_ptr(key, t->htab_size);
	
	struct htab_listitem **last_item_addr = &t->arrptr_list[index];
	for (struct htab_listitem *tmp = t->arrptr_list[index];
		tmp != NULL; tmp = tmp->next)
	{
		last_item_addr = &tmp->next;
		if (!strcmp(tmp->key, key)) {
			++tmp->data;
			return tmp;
		}
	} 

	*last_item_addr = malloc( sizeof(struct htab_listitem) );
	struct htab_listitem *new_item = *last_item_addr;
	if (new_item == NULL)
		return NULL;

	new_item->key = malloc( strlen(key)+1 );
	if (new_item->key == NULL) {
		free(new_item);
		return NULL;
	}

	++t->n;
	strcpy(new_item->key, key);
	new_item->data = 1;
	new_item->next = NULL;

	return new_item;
}