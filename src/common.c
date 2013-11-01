#include "common.h"

void print_error(const char *string, ...) {
	va_list argptr;
	va_start(argptr, string);
	vfprintf(stderr, string, argptr);
	va_end(argptr);
	fprintf(stderr, "\n");	
}

