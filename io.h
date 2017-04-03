// io.h
// Solution: IJC-DU2, example 2), 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4

#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include <stdio.h>

enum { MAX_WORD = 127 };

bool g_OUT_OF_LIMIT_FLAG;

int get_word(char *s, int max, FILE *fp);

#endif /* IO_H */