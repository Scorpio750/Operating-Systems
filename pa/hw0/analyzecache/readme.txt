Alison Wong
Patrick Wu

Homework 0

Analyzecache:
Creates an array of size 64MB. Runs 5 passes with some arbitrary read/write operation to cache data. 
Uses gettimeofday to obtain the start and end times. Subtracts the start time from the end time to find the duration of access.
Runs 5 passes of some interval 2^i, when there is a jump in lookup time greater than half the previous time the program assumes a cache miss.
Outputs the block/line size in bytes, cache size in megabytes, and miss penalty in µs.

ULT:

