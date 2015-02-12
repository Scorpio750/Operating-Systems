#ifndef H_ANALYZE_CACHE
#define H_ANALYZE_CACHE

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int array_size = 1024*1024*64;
int to_the_twenty = 1048576;
char* array;
struct cache_ {
	int interval;
	long total_time;
	long diff;
};

typedef struct cache_ Cache;

Cache* loop (int, Cache*);

#endif

