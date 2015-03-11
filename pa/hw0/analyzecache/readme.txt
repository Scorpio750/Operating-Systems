Alison Wong
Patrick Wu

Homework 0

Analyzecache:
Creates an array of size 64MB. Runs 5 passes with some arbitrary read/write operation to cache data. 
Uses gettimeofday to obtain the start and end times. Subtracts the start time from the end time to find the duration of access.
Runs 5 passes of some interval 2^i, when there is a jump in lookup time greater than half the previous time the program assumes a cache miss.
Outputs the block/line size in bytes, cache size in megabytes, and miss penalty in µs.

ULT:
In mypthread_create() we check if the main thread has been created. If not, we
create the main thread and then we create the other threads. This is all
stored in an array of mypthread_t. We getcontext() and makecontext() for the
new threads. Each thread has a state that tells whether or not the thread is
elligible for running, if it's waiting on another thread, or if it's finished
running and has exited or returned from a function. 

In mypthread)exit() we check that the we're not exiting from the main thread.
We change the state of the thread to done and store the return value. We then
call mypthread_yield() in order to schedule the next thread.

In mypthread_yield() we check to make sure that a main thread has been created. We search through the array and fine a thread whose state is elligible and swap to that context. If not, we search for a thread that is waiting but the thread it's waiting for is now done and swap to that context. 

In mypthread_join() we set the current thread to waiting and set it's wait_id
to the id of the thread that it will be waiting on. We keep calling
mypthread_yield() until the thread that it's waiting for is done. After that
it sets it's current state back to elligible. We then store the return value.
