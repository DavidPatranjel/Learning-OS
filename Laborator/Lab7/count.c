#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_RESOURCES 5
#define NR_THREADS 10
int available_resources = MAX_RESOURCES ;
pthread_mutex_t mtx;

int decrease_count(int count)
{
    	pthread_mutex_lock(&mtx);
    	if ( available_resources < count ){
    		printf("Unable to get %d resources. Only %d left\n", count, available_resources);
        	pthread_mutex_unlock(&mtx);
        	return -1;
        }
    	else{
        	available_resources -= count ;
        	printf("Got %d resources %d remaining\n", count, available_resources);
        	pthread_mutex_unlock(&mtx);
    	}
    	return 0;
}

int increase_count(int count)
{
    	pthread_mutex_lock(&mtx);
    	available_resources += count ;
    	printf("Released %d resources %d remaining\n", count, available_resources);
    	pthread_mutex_unlock(&mtx);
    	return 0;
}
void *f(void *argc){
    	int val = (int)argc;
    	if(decrease_count(val))
    		return NULL;
    	usleep(1000*100*(rand()%(10)+1));
		increase_count(val);
    	return NULL;
}

int main(){
	
		pthread_t thr[NR_THREADS];
    	if(pthread_mutex_init(&mtx, NULL)){
        	perror(NULL);
        	return errno;
    	}
    
    	for(int i = 0; i < NR_THREADS; ++i){
	    	int resources = rand()%(MAX_RESOURCES-2)+1;
        	if(pthread_create(&thr[i], NULL, f, (void*)resources)){
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
    	
    	///DISTRUGEREA MUTEXULUI
		pthread_mutex_destroy(&mtx);
    	return 0;
}
