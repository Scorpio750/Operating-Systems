#include "analyzecache.h"

long loop (int interval) {
	struct timeval start, end;
	gettimeofday(&start, NULL);

	int i, passes, j;
	int a = 0;

	for(j = 0; j  < 5; j++) {
		for(passes = 0; passes < interval; passes++) {
			for (i = 0; i < array_size; i+=interval) {
				a = a + array[i];
			}
		}
	}

	gettimeofday(&end, NULL);

	long end_t = end.tv_sec * 1000000 + end.tv_usec;
	//printf("END --> SEX: %ld, MILISEX: %ld, TOTAL: %ld\n", end.tv_sec, end.tv_usec, end_t);
	long start_t = start.tv_sec * 1000000 + start.tv_usec;
	//printf("START --> SEX: %ld, MILISEX: %ld, TOTAL: %ld\n", start.tv_sec, start.start_t);
	long total_t = end_t - start_t;
	printf("%d, %ld\n", interval, total_t);
	return total_t;
}

int main(int argc, char *argv[]) {
	array = malloc(sizeof(char) * array_size);

	int i;
	for (i = 0; i < array_size; i++) {
		array[i] = (char)i;
	}

	for(i = 1; i < to_the_twenty; i *= 2) {
		loop(i);
	}

	return 0;
}
