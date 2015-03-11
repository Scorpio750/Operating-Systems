#include "mypthread.h"

void nullify_array() {
	int i;
	for (i = 0; i < ARRAYSIZE; i++) {
		thread_array[i] = NULL;
	}
	return;
}

void run_fnc (mypthread_t *thread) {
	//fprintf(stderr, ">>running function\n");
	thread->retval = thread->start_routine(thread->arg);
	thread->state = 2;
	free(thread->context.uc_stack.ss_sp);
	//fprintf(stderr, "entering yield from run_fnc\n");
	mypthread_yield();
}

int mypthread_create(mypthread_t *thread, const mypthread_attr_t *attr,
		void *(*start_routine) (void *), void *arg) {
	
	if (create_count == ARRAYSIZE){
		fprintf(stderr, "ERROR: Exceeded MAX number of threads\n");
		return -1;
	}

	getcontext(&(thread->context));
	thread->context.uc_stack.ss_sp = calloc (STACKSIZE, 1);
	thread->context.uc_stack.ss_size = STACKSIZE;
	thread->context.uc_link = NULL;
	makecontext(&(thread->context), (void(*)(void))run_fnc, 1, thread);

	if (main_count == 0) {
		nullify_array();
		thread_array[0] = &main_t;
		thread_array[0]->id = 0;
		thread_array[0]->state = 0;
		thread_array[0]->wait_id = -1;
		thread_array[0]->retval = NULL;
		getcontext(&(thread_array[0]->context));
		main_count = 1;
		create_count = 1;
		sched_count = 0;
	}

	thread->state = 0;
	thread->wait_id = -1;
	thread->retval = NULL;
	thread->start_routine = start_routine;
	thread->arg = arg;
	thread_array[create_count] = thread;
	thread->id = create_count;
	create_count++;

	return 0;
}

void mypthread_exit(void *retval) {
	//fprintf(stderr, "entering mypthread_exit()\n");
	if (main_count == 0 || thread_array[sched_count]->state == 2) {
		fprintf(stderr, "ERROR\n");
		return;
	}

	mypthread_t *t = thread_array[sched_count];

	t->state = 2;
	t->retval = retval;
	
	//fprintf(stderr, "entering yield from mypthread_exit\n");
	mypthread_yield();
}

int mypthread_yield(void) {
	//fprintf(stderr, "yielding...");
	if (main_count == 0) {
		fprintf(stderr, "ERROR\n");
		return -1;
	}

	mypthread_t *curr = thread_array[sched_count];

	int i;
	mypthread_t *t;

	for (i = sched_count + 1;;i++) {
		i = i % ARRAYSIZE;

		t = thread_array[i];
		int w_id;
		int swp;
		
		if (t != NULL) {
			//fprintf(stderr, "checking %i (wait on %i) (state %i)\n", t->id, t->wait_id, t->state);
			w_id = t->wait_id;
			if (t->state == 0) {
				sched_count = t->id;
				//fprintf(stderr, "t->state == 0. Exiting YIELD\n");
				swp = swapcontext(&curr->context, &t->context);
				//fprintf(stderr, "swapped contexts\n");
				return swp;
			}
			if ((t->state == 1) && (thread_array[w_id]->state == 2)) {
				sched_count = t->id;
				//fprintf(stderr, "t->state == 1. Exiting YIELD\n");
				swp = swapcontext(&curr->context, &t->context);
				//fprintf(stderr, "swapped contexts\n");
				return swp;
			}
		}
	}
}

int mypthread_join(mypthread_t thread, void **retval) {
	//printf("PTHREAD_JOIN\n");

	mypthread_t *curr_thr = thread_array[sched_count];
	mypthread_t *next_thr = thread_array[thread.id];

	curr_thr->wait_id = thread.id;
	curr_thr->state = 1;

	while (thread_array[thread.id]->state != 2) {
		//fprintf(stderr, "ENTERING YIELD\n");
		mypthread_yield();
		//fprintf(stderr, "done yielding\n");
	}

	curr_thr->state = 0;

	if (retval) {
		*retval = next_thr->retval;
	}
	//printf("EXITING PTHREAD_JOIN\n");
	return 0;
}
