// io.c
// Solution: IJC-DU2, example 2), 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4

#include "error.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int get_word(char *s, int max, FILE *fp) {
	int ch; 
	while (isspace( ch = fgetc(fp) ))
	{} /* to ignore <ws> sequence of chars */

	for (int i = 0; i < max; ++i) {
		if (feof(fp)) {
			s[i] = '\0';
			return EOF;
		} else if (isspace(ch)) {
			s[i] = '\0';
			return i;
		}

		s[i] = ch;
		ch = fgetc(fp);
	}

	s[max-1] = '\0';
	if (g_OUT_OF_LIMIT_FLAG == false) {
		warning_msg("get_word: \"%s...\" is too long. truncating..\n", s);
		g_OUT_OF_LIMIT_FLAG = true;
	}

	while (!isspace( ch = fgetc(fp) ) && ch != EOF)
	{} /* to ignore chars is out of limit */

	return max-1;
}