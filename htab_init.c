// htab_init.c
// Solution: IJC-DU2, example 2), 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4

#include "htable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

htab_t *htab_init(unsigned size) {
	if (size == 0) {
		fprintf(stderr, "htab_init: hash table with size 0 cannot be created\n");
		return NULL;
	}
	size_t size_arrptr_list = size*sizeof(struct htab_listitem*);
	htab_t *new_htab = malloc( sizeof(htab_t) + size_arrptr_list );
	if (new_htab == NULL)
		return NULL;

	memset(new_htab->arrptr_list, 0, size_arrptr_list);
	new_htab->htab_size = size;
	new_htab->hash_fun_ptr = &hash_function_default;
	new_htab->n = 0;
	return new_htab;	
}