// tail.c
// Solution: IJC-DU2, example 1a), 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4
// easiest implementation of the gnu-tail program written in C

#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <getopt.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>

enum { NLINES_DEFAULT = 10 };
enum { MAX_LINE_LENGTH = 210 };

static bool g_OUT_OF_LIMIT_FLAG = false;

int str_to_positive_int(const char *s) {
	intmax_t num = strtoimax(s, NULL, 10);
	if (num == INTMAX_MAX || errno == ERANGE || num > INT_MAX) {
		return -1;
	} else {
		return (int)num;
	}
}

bool number(const char *s) {
	while (*s) {
		if (!isdigit(*s++))
			return false;
	}
	return true;
}

int getline_count(FILE *fp) {
	int ch;
	int count = 0;
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == '\n') {
			if (count == INT_MAX) {
				return -1;
			}
			++count;
		}
	}

	fseek(fp, -1, SEEK_END);
	ch = fgetc(fp);
	if (ch != '\n') 
		++count;

	rewind(fp);
	return count;
}

int getline(FILE* fp, char buffer[]) {
	int ch;
	int index = 0;
	while ((ch = fgetc(fp)) != EOF && ch != '\n') {
	 	if (index == MAX_LINE_LENGTH) {
	 		buffer[MAX_LINE_LENGTH] = '\0';
			return -1;
	 	}

		buffer[index] = ch;
		++index;	
	}

	if (ch == EOF) {
		buffer[index] = '\0';
	} else {
		buffer[index] = ch;
		buffer[index+1] = '\0';
	}
	return 0;
}

void printlines(FILE *fp) {
	char buffer[MAX_LINE_LENGTH + 2];

	while (!feof(fp)) {
		if (getline(fp, buffer) < 0) {
			if (g_OUT_OF_LIMIT_FLAG == false) {
				warning_msg("tail: \"%s...\": line is out of limit\n", buffer);
				g_OUT_OF_LIMIT_FLAG = true;
			}

			printf("%s\n", buffer);

			/* to ignore other chars */
			int ch; 
			while ((ch = fgetc(fp)) != EOF && ch != '\n') 
			{}

		} else {
			printf("%s", buffer);
		}
	} // while 
}

void get_args(int argc, char *argv[], int *nlines, char **filename) {
	*nlines = NLINES_DEFAULT;
	int opt;
	while ((opt = getopt(argc, argv, "n:")) != -1) {	
		switch (opt) {
			case 'n':
				if (number(optarg)) {
					if ((*nlines = str_to_positive_int(optarg)) < 0)  {
						fprintf(stderr, "%s: invalid -n parametr \n", argv[0]);
						exit(1);
					}
				} else {
					fprintf(stderr, "%s: invalid option -- \'%s\'\n", argv[0], optarg);
					exit(1);
				}
				break;
			case '?':
				exit(1);
				break;
		}
	}

	int count_files = argc - optind;
	if (count_files > 1) {
		fprintf(stderr, "%s: cannot reading more than one file\n", argv[0]);
		exit(1);
	}

	*filename = argv[optind];
}


int main(int argc, char *argv[]) {
	int nlines = NLINES_DEFAULT;
	char *filename = NULL;
	get_args(argc, argv, &nlines, &filename);
	
	FILE *fp;
	if (filename) {
		fp = fopen(filename, "r");
		if (!fp) {
			fatal_error("%s: cannot open file \"%s\"\n", argv[0], filename);	
		}
	} else {
		fp = stdin;
	}
	
	int lines_total = getline_count(fp);
	if (lines_total < 0) {
		warning_msg("%s: I cannot read files with number", argv[0]);
		fatal_error(" of lines larger than INT_MAX :(\n");
	}

	int start_line_index = lines_total - nlines;
	if (start_line_index <= 0) {
		printlines(fp);
		if (filename) {
			if (fclose(fp) == EOF) {
				fatal_error("%s: file closing error\n");
			}
		}
		return 0;
	}

	for (int i = 0; i < lines_total; ++i) {
		if (start_line_index == i) {
			printlines(fp);
			break;
		}

		int ch;
		while ((ch = getc(fp)) != EOF) {
			if (ch == '\n')
				break;
		}
	} //for

	if (filename) {
		if (fclose(fp) == EOF) {
			fatal_error("%s: file closing error\n");
		}
	}
	return 0;
}