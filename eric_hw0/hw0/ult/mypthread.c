#include "mypthread.h"

int mypthread_create(mypthread_t* thread, const mypthread_attr_t* attr, void* (*start_routine)(void*), void* arg) {
	char* stack;

	if(main_set_up == 0) {
		if(getcontext(&main_program) != 0) {
			printf("ERROR: main function context could not be created!\n");
			return -1;
		}
		main_set_up = 1;
	}

	printf("Creating new thread...\n");

	thread->id = get_id();

	if(thread->id < 0) {
		printf("ERROR: Max number of threads exceeded.\n");
		return -1;
	}

	thread->running = 0;
	stack = malloc(sizeof(char) * STACKSIZE);
	
	//printf("Creating context...\n");
	getcontext(&(thread->this_context));
	
	//printf("Creating the stack...\n");
	thread->this_context.uc_stack.ss_sp = stack;
	thread->this_context.uc_stack.ss_size = STACKSIZE;
	
	//printf("Copying start routine...\n");
	thread->start_routine = start_routine;
	//printf("Copying args...\n");
	thread->args = arg;

	//printf("Adding thread to the list...\n");
	thread_list[thread->id] = thread;

	printf("Thread %d created\n", thread->id);
	return 0;
}

void mypthread_exit(void* retval) {
	int current_id;
	current_id = thread_list[current_thread_index]->id;

	thread_list[current_thread_index]->running = 0;
	thread_list[current_thread_index]->finished = 1;

	swapcontext(&(thread_list[current_thread_index]->this_context), &main_program);
}

int mypthread_yield() {
	int next_id, prev_id;
	mypthread_t* current_thread, * next_thread;
	
	printf("Yielding thread %d...\n", thread_list[current_thread_index]->id);

	current_thread = thread_list[current_thread_index];
	prev_id = thread_list[current_thread_index]->id;

	printf("Retrieving next thread ID...\n");
	next_id = get_next_thread();
	if(next_id < 0 || next_id >= THREADCEILING) {
		printf("ERROR: The next thread cannot be retrieved.\n");
		return -1;
	}

	printf("Retrieving next thread...\n");
	next_thread = thread_list[current_thread_index + 1];

	printf("Changing running boolean...\n");
	current_thread->running = 0;
	next_thread->running = 1;

	swapcontext(&(thread_list[prev_id]->this_context), &(thread_list[next_id]->this_context));

	
	return 0;
}

int mypthread_join(mypthread_t thread, void** retval) {
	
	return 0;
}

int get_id() {
	//printf("Generating new ID...\n"); 
	int i, j;
	for(i = create_thread_index, j = 0; j < THREADCEILING; i++, j++) {
		if(i >= THREADCEILING) {
			current_thread_index = 0;
		}
		if(thread_list[i] == NULL || thread_list[i]->finished == 1) {
			//printf("Generation successful!\n");
			create_thread_index = i;
			return create_thread_index;
		}
	}
	//printf("Generating failed!\n");
	return -1;
}

int get_next_thread() {
	//printf("Getting next thread...\n");
	int i,j;
	for(i = current_thread_index, j = 0; j < THREADCEILING; i++, j++) {
		if(i >= THREADCEILING) {
			current_thread_index = 0;
		}
		if(thread_list[i] != NULL && thread_list[i]->finished != 1) {
			//printf("Generation successful!\n");
			current_thread_index = i;
			return current_thread_index;
		}
	}
	//printf("Could not find next thread!\n");
	return -1;
}
