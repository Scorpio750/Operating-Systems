#include "mypthread.h"

int mypthread_create(mypthread_t* thread, const mypthread_attr_t* attr, void* (*start_routine)(void*), void* arg) {
	char* stack;

	if(main_set_up == 0) {
		printf("Setting up main context\n");
		current_thread_index = 0;
		create_thread_index = 0;
		if(getcontext(&main_program) != 0) {
			printf("ERROR: main function context could not be created!\n");
			return -1;
		}
		main_set_up = 1;
		inThread = 0;
		toRun = -1;
		total = 0;
	}

	printf("Creating new thread...\n");

	thread->id = malloc(sizeof(int));
	*(thread->id) = get_id();

	if(*(thread->id) < 0) {
		printf("ERROR: Max number of threads exceeded.\n");
		return -1;
	}

	thread->state = malloc(sizeof(int));
	*(thread->state) = 2;
	stack = malloc(sizeof(char) * STACKSIZE);
	
	//printf("Creating context...\n");
	thread->this_context = malloc(sizeof(ucontext_t));
	getcontext(thread->this_context);
	
	//printf("Creating the stack...\n");
	thread->this_context->uc_stack.ss_sp = stack;
	thread->this_context->uc_stack.ss_size = STACKSIZE;
	
	//printf("Copying start routine...\n");
	thread->start_routine = start_routine;
	//printf("Copying args...\n");
	thread->args = arg;

	makecontext(thread->this_context, (void*)thread->start_routine, 1, thread->args);
	
	//printf("Adding thread to the list...\n");
	thread_list[*(thread->id)] = thread;
	toRun++;
	total++;

	printf("Thread %d created with state %d\n", *(thread->id), *(thread->state));

	return 0;
}

void mypthread_exit(void* retval) {
	int current_id;
	current_id = *(thread_list[current_thread_index]->id);

	printf("Exiting from %d\n", current_id);

	*(thread_list[current_thread_index]->state) = 0;
	if(*(thread_list[current_id])->state != 0) {
		toRun--;
	}

	//printf("%d threads are left to run\n", toRun);
	if(toRun < 1) {
		swapcontext(thread_list[current_thread_index]->this_context, &main_program);
	} else {
		mypthread_yield();
	}
}

int mypthread_yield() {
	int next_id, prev_id;
	mypthread_t* current_thread, * next_thread;
	
	printf("Yielding thread %d...\n", *(thread_list[current_thread_index]->id));

	if(inThread) {
		*(thread_list[current_thread_index]->state) = 2;
		//printf("Swapping from %d to main\n", current_thread_index);
		inThread = 0;	
		swapcontext(thread_list[current_thread_index]->this_context, &main_program);
		return 0;
		
	} else {

		while(toRun > 0) {
			//printf("Retrieving next thread ID...\n");
			next_id = get_next_thread();

			//printf("NEXT ID %d\n", next_id);

			if(next_id < 0 || next_id >= THREADCEILING) {
				printf("ERROR: The next thread cannot be retrieved.\n");
				return -1;
			}

			//printf("Retrieving next thread...\n");
			next_thread = thread_list[next_id];
	
			//printf("Changing running boolean...\n");
			*(next_thread->state) = 1;

			inThread = 1;
			swapcontext(&main_program, thread_list[next_id]->this_context);
	
			thread_list[current_thread_index]->start_routine(thread_list[current_thread_index]->args);
			return next_id;
		}
	}
	return 0;
}

int mypthread_join(mypthread_t thread, void** retval) {
	printf("Joining thread %d to %d\n", *(thread_list[current_thread_index]->id), *(thread.id));
	while(*(thread_list[*(thread.id)]->state) != 0) {
		mypthread_yield();
	}	
	return 0;
}

int get_id() {
	//printf("Generating new ID...\n"); 
	int i, j;
	for(i = create_thread_index, j = 0; j < THREADCEILING; i++, j++) {
		if(i >= THREADCEILING) {
			current_thread_index = 0;
		}
		if(thread_list[i] == NULL || *(thread_list[i]->state) == 0) {
			//printf("Generation successful! %d\n", i);
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
	for(i = current_thread_index + 1, j = 0; j < total; i++, j++) {
		if(i >= THREADCEILING) {
			i = 0;
		}
		if(i > total) {
			i = 0;
		}
		if(thread_list[i] != NULL) {
			//printf("Status of thread %d is %d\n", i, *(thread_list[i]->state));
		}
		if(thread_list[i] != NULL && *(thread_list[i]->state) == 2 && i != current_thread_index) {
			//printf("Generation successful! Retrieved thread %d\n", i);
			current_thread_index = i;
			return current_thread_index;
		}
	}
	//printf("Could not find next thread!\n");
	return -1;
}

