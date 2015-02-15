#ifndef H_MYPTHREAD
#define H_MYPTHREAD

#define ARRAYSIZE 50
#define STACKSIZE 8200

#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Types
typedef struct {
	int state; // 0 = elligible, 1 = waiting, 2 = done
	int id;
	int wait_id;
	void *retval;
	void *(*start_routine)(void*);
	void *arg;
	ucontext_t context;
} mypthread_t;

typedef struct {
	//int stack_size;
	//char *stack;
} mypthread_attr_t;

mypthread_t main_t;
mypthread_t *thread_array[ARRAYSIZE];
int create_count;
int sched_count; //want to start at 1
int main_count; // 0 = no main yet

// Functions
int mypthread_create(mypthread_t *thread, const mypthread_attr_t *attr,
			void *(*start_routine) (void *), void *arg);

void mypthread_exit(void *retval);

int mypthread_yield(void);

int mypthread_join(mypthread_t thread, void **retval);


/* Don't touch anything after this line.
 *
 * This is included just to make the mtsort.c program compatible
 * with both your ULT implementation as well as the system pthreads
 * implementation. The key idea is that mutexes are essentially
 * useless in a cooperative implementation, but are necessary in
 * a preemptive implementation.
 */

typedef int mypthread_mutex_t;
typedef int mypthread_mutexattr_t;

static inline int mypthread_mutex_init(mypthread_mutex_t *mutex,
			const mypthread_mutexattr_t *attr) { return 0; }

static inline int mypthread_mutex_destroy(mypthread_mutex_t *mutex) { return 0; }

static inline int mypthread_mutex_lock(mypthread_mutex_t *mutex) { return 0; }

static inline int mypthread_mutex_trylock(mypthread_mutex_t *mutex) { return 0; }

static inline int mypthread_mutex_unlock(mypthread_mutex_t *mutex) { return 0; }

#endif
