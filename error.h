// error.h
// Solution: IJC-DU2, 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4
// 	header dile for error.c module 

#ifndef _ERROR_H
#define _ERROR_H

/*
 * output to stderr error message in the fmt format
 * processing format like the printf function\
 */
void warning_msg(const char *fmt, ...);

/*
 * similarly, as a warning_msg but exit 
 * the program with a return code 1
 */
void fatal_error(const char *fmt, ...);

#endif