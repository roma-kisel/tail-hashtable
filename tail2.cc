// tail.cc
// Solution: IJC-DU2, example 1b), 25.04.2016
// Author: Roman Kiselevich, FIT
// Compiler: gcc 4.8.4
// // easiest implementation of the gnu-tail program written in C++

#include <iostream>
#include <fstream>
#include <cctype>
#include <limits>
#include <queue>
#include <unistd.h>

static const int NLINES_DEFAULT = 10;

using namespace std;

bool number(const char *s) {
	while (*s) {
		if (!isdigit(*s++))
			return false; 
	}
	return true;
}

void get_args(int argc, char *argv[], long long *nlines, char **filename) {
	*nlines = NLINES_DEFAULT;
	int opt;
	while ((opt = getopt(argc, argv, "n:")) != -1) {	
		switch (opt) {
			case 'n':
				if (number(optarg)) {
					try {
						*nlines = stoi(optarg, 0, 10);
					} catch (exception& ) {
						cerr << argv[0] <<
							": invalid -n parametr \n";
						exit(EXIT_FAILURE);
					}
				} else {
					cerr << argv[0] << ": invalid option -- \'" 
						 	<< optarg << "\'\n";
					exit(EXIT_FAILURE);
				}
				break;
			case '?':
				exit(EXIT_FAILURE);
				break;
		}
	}

	int count_files = argc - optind;
	if (count_files > 1) {
		cerr << argv[0] << ": cannot reading more than one file\n";
		exit(1);
	}

	*filename = argv[optind];
}

int main(int argc, char *argv[]) {
	long long nlines;
	char *filename;
	get_args(argc, argv, &nlines, &filename);
	ios::sync_with_stdio(false);

	ifstream file;
	bool read_from_file = false;
	if (filename) {
		file.open(filename, ios::in);
		if (!file) {
			cerr << argv[0] << ": cannot open file \""
						<< filename << "\"\n";
			exit(EXIT_FAILURE);
		}
		read_from_file = true;
	}

	istream &read_stream = read_from_file ? file : cin;
	queue<string> lines;
	string line;
	while (getline(read_stream,line)) {
		lines.push(line);
	}

	if (lines.size() > numeric_limits<long long>::max()) {
		cerr << argv[0] << ": input stream has too much lines\n";
		exit(EXIT_FAILURE);
	}

	while (!lines.empty()) {
		if ((long long)lines.size()-nlines <= 0) {
			cout << lines.front() << endl;
		}
		lines.pop();
	}

	return EXIT_SUCCESS;
}
