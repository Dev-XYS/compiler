#include "err.h"

void report(int e) {
}

void panic() {
	printf("\nerror\n\n");
	throw 0;
}

void panic(const char *s) {
	printf("\nerror: %s\n\n", s);
	throw 1;
}
