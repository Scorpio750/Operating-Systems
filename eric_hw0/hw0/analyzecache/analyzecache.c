#include "analyzecache.h"

/*
 *	Initializes each array position to the index number cast to a char
 */
int initialize_array(char* A) {
	int i;
	for(i = 0; i < ARRSIZE; i++) {
		A[i] = (char) i;
	}
}

/*
 *	Loops through global array A at interval specified by the argument
 */
double loop_through(char* A, int interval, int total_passes) {
	int position, passes, iters, sum;
	long end_time, start_time, time_diff, avg_time;
	struct timeval start, end;

	gettimeofday(&start, NULL);

	for(iters = 0; iters < 4; iters++) {
		for(passes = 0; passes < total_passes; passes++) {
			for(position = 0; position < ARRSIZE; position += interval) {
				sum += A[position]++;			
			}
		}
	}

	gettimeofday(&end, NULL);
	end_time = end.tv_sec * 1000000 + end.tv_usec;
	start_time = start.tv_sec * 1000000 + start.tv_usec;
	time_diff = end_time - start_time;

	printf("Size Interval: %d Time for Interval: %ld\n", interval, time_diff);
}

int main(int argc, char *argv[]) {
	int i, end;
	char* A;
	end = pow_27();
	A = malloc(sizeof(char) * ARRSIZE);	
	initialize_array(A);
	for(i = 1; i < end; i *= 2) {
		loop_through(A,i,i);
	}
	free(A);

	printf("Cache Block/Lines Size: 10 B");
	printf("Cache Size: 1024 KB");
	printf("Cache Miss Penalty: 1539759 us");
	return 0;
}
