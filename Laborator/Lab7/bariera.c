#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#define NR_THREADS 5

int max_threads;
int nr_threads;
pthread_mutex_t mtx;
sem_t sem;

void barrier_point(){
	pthread_mutex_lock(&mtx);
	nr_threads++;
	if(nr_threads == max_threads){
		for(int i = 1; i <= max_threads - 1; ++i){
			if(sem_post(&sem)){
				perror(NULL);
				pthread_mutex_unlock(&mtx);
				return;
			}
		}
		nr_threads = 0;
		pthread_mutex_unlock(&mtx);
	}
	else{
		pthread_mutex_unlock(&mtx);
		if(sem_wait(&sem)){
			perror(NULL);
			return;
		}
	}
}

void *tfun(void *v)
{
    	int tid = ( int) v ;
    	printf ("%d reached the barrier \n " , tid );
    	barrier_point();
    	printf ("%d passed the barrier \n " , tid );

    	return NULL ;
}

void init(int k)
{
	max_threads = k;
	nr_threads = 0;
	if(pthread_mutex_init(&mtx, NULL)){
        	perror(NULL);
        	return;
    	}
    	
	if(sem_init(&sem, 0, 0))
	{
		perror(NULL);
		return;
	}
}

int main(){
	init(5);
	pthread_t thr[NR_THREADS];
	
	for(int i = 0; i < NR_THREADS; ++i){
        	if(pthread_create(&thr[i], NULL, tfun, (void*)i)){
		    	perror(NULL);
		    	return errno;
        	}
    	}
    	
    	for(int i = 0; i < NR_THREADS; ++i){
        	if(pthread_join(thr[i], NULL)){
			perror(NULL);
		    	return errno;
        	}
        

    	}
	pthread_mutex_destroy(&mtx);
	sem_destroy(&sem);
    	return 0;
}
