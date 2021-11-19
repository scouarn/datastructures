#include "utils.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

#include <semaphore.h>


typedef struct {
	pthread_t tid;
	sem_t lock;
	M_uint_t index;
	void (*func) (M_uint_t);

	volatile bool running; /* flag to tell the thread to stop its loop   */

} tinfo;


struct __M_tpool_t__ {
	M_uint_t size;
	tinfo *threads;
};

#include "tpool.h"


/* one of these starts for each thread when the pool is created */
static void* job_handler_slave(void* _info) {

	tinfo *info = (tinfo*) _info;

	for (;;) {

		/* wait for start signal */
		sem_wait( &(info->lock) );

		if (info->running == false) {
			break;
		}

		info->func(info->index);

	}


	return NULL;
}


M_tpool_t* M_tpool_make(M_uint_t nb_threads) {
	M_uint_t i;

	M_tpool_t* pool = malloc( sizeof(M_tpool_t) );

	pool->size = nb_threads;
	pool->threads = malloc( nb_threads * sizeof(tinfo) );

	for (i = 0; i < nb_threads; i++) {
		tinfo* info = pool->threads + i;

		info->index = i;
		info->running = true;

		sem_init(&(info->lock), 0, 0); /* start at zero so it waits */
		pthread_create(&(info->tid), NULL, job_handler_slave, (void*)info);

	}

	return pool;

}


void M_tpool_free(M_tpool_t* pool) {

	M_uint_t i;
	for (i = 0; i < pool->size; i++) {
		tinfo* info = pool->threads + i;

		sem_destroy( &(info->lock) );
	}

	free(pool->threads);
	free(pool);
}


void M_tpool_call(M_tpool_t* pool, void (*func) (M_uint_t)) {

	M_uint_t i;

	for (i = 0; i < pool->size; i++) {
		tinfo* info = pool->threads + i;

		info->func = func;
		sem_post( &(info->lock) );
	}

}


void M_tpool_join(M_tpool_t* pool) {

	M_uint_t i;

	for (i = 0; i < pool->size; i++) {
		tinfo* info = pool->threads + i;

		info->running = false;
		sem_post( &(info->lock) );
		pthread_join( info->tid, NULL);
	}

}


void M_tpool_batch(M_tpool_t* pool, void (*func) (M_uint_t), M_uint_t nb_jobs) {

	M_uint_t jid, tid = 0;

	for (jid = 0; jid < nb_jobs; jid++) {
		tinfo* info;
		int sem; 


		/* find a thread which is currently waiting */
		do {
			info = pool->threads + tid;
			tid = (tid + 1) % pool->size;
			sem_getvalue( &(info->lock), &sem);

		} while (sem > 0); 


		/* run job on thread */
		info->func = func;
		info->index = jid;
		sem_post( &(info->lock) );
	}

	M_tpool_join(pool);

}

