// error.c
// Solution: IJC-DU2, 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4
// 	Module for error handling

#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warning_msg(const char *fmt, ...) {
	va_list arguments;

	va_start(arguments, fmt);

	vfprintf(stderr, fmt, arguments);

	va_end(arguments);
}

void fatal_error(const char *fmt, ...) {
	va_list arguments;

	va_start(arguments, fmt);
	
	vfprintf(stderr, fmt, arguments);

	va_end(arguments);
	exit(1);
}