#ifndef H_ANALYZE_CACHE
#define H_ANALYZE_CACHE

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int initialize_array(char*);
double loop_through(char*, int, int);

int pow_27() {
	int i;
	int ret = 1;
	for(i = 0; i < 27; i++) {
		ret *= 2;
	} 
	return ret;
}

int ARRSIZE = 1024 * 1024 * 64;

#endif
