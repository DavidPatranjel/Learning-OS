#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void *
hello(void *v){
    char *who = (char *) v;
    printf("Hello, %s\n", who);
    return NULL;
}

int main(){
    pthread_t thr;
    if(pthread_create(&thr, NULL, hello, "World!")){
        perror(NULL);
        return errno;
    }
    void *result;
    if(pthread_join(thr, &result)){
        perror(NULL);
        return errno;
    }
    return 0;
}
