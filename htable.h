// htable.h
// Solution: IJC-DU2, example 2), 25.03.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4

#ifndef HTABLE_H
#define HTABLE_H

struct htab_listitem {
	char *key;
	unsigned data;
	struct htab_listitem *next;
};

typedef struct {
	unsigned htab_size;
	unsigned (*hash_fun_ptr)(const char *, unsigned);
	unsigned long n;
	struct htab_listitem *arrptr_list[];
} htab_t;

/*
 *	default hash function (sdbm algorithm)
 */
unsigned hash_function_default(const char *str, unsigned htab_size);

/*
 *	initializes the hash table with a given size and returns a pointer to it
 *	in case of error returns NULL
 */
htab_t *htab_init(unsigned size);

/*
 *	similarly like htab_init, but as the second parameter 
 *						takes a pointer to a hash function
 */
htab_t *htab_init2(unsigned size, unsigned (*hashfn)(const char *, unsigned));

/*
 *	for each element of the hash table t call the function 
 */
void htab_foreach(htab_t *t, void (*cbfunc)(const char *, unsigned));

/*
 *	adds an element with the specified key in the hash table t 
 *	If this key element already in the table, the value of data increases by one.
 *	Returns a pointer to the found or added element
 *	In case of error returns NULL
 */
struct htab_listitem *htab_lookup_add(htab_t *t, const char *key);

/*
 *	removes element with the given key from the hash table t
 */
void htab_remove(htab_t *t, const char *key);

/*
 *	deletes all items from the hash table t
 */
void htab_clear(htab_t *t);

/*
 *	Deletes the hash table t
 */
void htab_free(htab_t *t);

#endif /* HTABLE_H */
