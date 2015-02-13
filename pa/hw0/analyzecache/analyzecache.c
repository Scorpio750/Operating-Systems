#include "analyzecache.h"

Cache* loop (int interval, Cache* cache_info) {
	struct timeval start, end;

	// sets start and end times for array pass in each respective timeval
	gettimeofday(&start, NULL);

	int i, passes, j;
	int a = 0;

	// does 5 passes with some arbitrary read/write operation
	for(j = 0; j  < 5; j++) {
		for(passes = 0; passes < interval; passes++) {
			for (i = 0; i < array_size; i+=interval) {
				a = a + array[i];
			}
		}
	}

	gettimeofday(&end, NULL);

	long end_time = end.tv_sec * 1000000 + end.tv_usec;
	long start_time = start.tv_sec * 1000000 + start.tv_usec;
	cache_info->total_time = end_time - start_time;
	//printf("Interval: %d\tTotal Time: %ld\n", interval, cache_info->total_time);
	cache_info->interval = interval;
	return cache_info;
}

int convert_to_MB(long interval) {
	return (2^interval/1024/1024);
}


int main(int argc, char *argv[]) {
	Cache *cache_info = malloc(sizeof(Cache));
	array = malloc(sizeof(char) * array_size);
	
	int i;
	long prevtime = -1L;
	long cachesize = -1L;
	long diff;
	int mb;

	for (i = 0; i < array_size; i++) {
		array[i] = (char)i;
	}

	printf("Testing for cache miss...\n");
	for(i = 1; i < to_the_twenty; i *= 2) {
		if (i != 1) {
			prevtime = cache_info->total_time;
		}
		cache_info = loop(i, cache_info);
		// printf("PREV TIME: %ld\nCURR TIME: %ld\n", prevtime, cache_info->total_time);
		
		/* test for cache miss */
		diff = cache_info->total_time - prevtime; 
		if (diff > prevtime * .5 && prevtime != -1L) {
			cache_info->diff = diff;	
			break;
		}
	}
	
	mb = convert_to_MB(cache_info->interval);

	/* output */
	if (cache_info->total_time == -1L) {
		printf("Your cache appears to have gone missing.\nPlease stand by as we attempt to retrieve it...\n");
	}
	else {
		printf("Cache Block/Line Size: %d\nCache Size: %dMB\nCache Miss Penalty: %ldµs\n",
				cache_info->interval, mb, cache_info->diff);
	}

	free(cache_info);
	free(array);
	return 0;
}
