// wordcount.c
// Solution: IJC-DU2, example 2), 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4
//  To choose the size of the hash table, 
//  I was inspired by the following excerpt from the book "Introduction to Algorithms" by 
// 			Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein
// 
// 	"A prime not too close to an exact power of 2 is often a good choice for m. For example,
// suppose we wish to allocate a hash table, with collisions resolved by chaining, to hold roughly
// n = 2000 character strings, where a character has 8 bits. We don't mind examining an average 
// of 3 elements in an unsuccessful search, so we allocate a hash table of size m = 701. The
// number 701 is chosen because it is a prime near 2000/3 but not near any power of 2. Treating
// each key k as an integer, our hash function would be
// h(k) = k mod 701." 
// 
// In this case, I decided to use the number 1572869 because it is good for the hash function and the 
// size of the table structure will eventually be about 12 MiB that I think of sufficient size to 
// store information about the words of the average file size
// 2^20 < 1572869 < 2^21

#include "error.h"
#include "htable.h"
#include "io.h"
#include <stdio.h>

void print_word_info(const char *key, unsigned data) {
	printf("%s\t%u\n", key, data);
}

int main() {
	char word[MAX_WORD+1];
	htab_t *map = htab_init(1572869);
	while (get_word(word, MAX_WORD+1, stdin) != EOF) {
		if (!htab_lookup_add(map, word)) {
			warning_msg("warning: out of memory\n");
			break;
		}
	}
	if (word[0]) {
		/* processing case: ...<word><EOF> */
		htab_lookup_add(map, word);
	}

	htab_foreach(map, &print_word_info);
	htab_free(map);
	return 0;
}