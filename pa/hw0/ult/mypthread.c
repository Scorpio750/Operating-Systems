#include "mypthread.h"

int get_id(mypthread_t *thread){
	if (count == ARRAYSIZE){
		return -1;
	}
	int i;
	for (i = 0; i < ARRAYSIZE; i++) {
		if (thread->exists == 0) {
			return i;
		}
	}
}

int mypthread_create(mypthread_t *thread, const mypthread_attr_t *attr,
		void *(*start_routine) (void *), void *arg) {
	
	int id = get_id(thread);
	if (id == -1){
		return -1;
	}
	thread->id = id;

	getcontext(&(thread->context));

	char *stack = malloc (sizeof(STACKSIZE));
	thread->context.uc_stack.ss_sp = stack;
	thread->context.uc_stack.ss_size = STACKSIZE;
	
	memcpy(thread->start_routine, start_routine, sizeof(start_routine));
	memcpy(thread->arg, arg, sizeof(arg));
	
	thread->run_state = 0;
	thread->exists = 1;
	thread_array[id] = thread;
	count++;

	//if first thread, create 2 threads - one for main & new thread
	//setcontext
}

void mypthread_exit(void *retval, mypthread_t *thread) {
	//make state zero 
	//schedule the next thread
	thread->run_state = 0;
	//swapcontext();
	count--;
}

int mypthread_yield(void) {
	return 0;
	//swapcontext
}

int mypthread_join(mypthread_t thread, void **retval) {
	return 0;
	//do not reselct thisthread until another is done
}
