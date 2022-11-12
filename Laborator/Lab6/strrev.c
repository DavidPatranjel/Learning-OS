#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


void *
rev(void *v){
    char *who =  (char*)v;
    int n = strlen(who), j = 0;
    char *aux = (char*)malloc(n);
    for(int i = n - 1; i >= 0; --i){
        aux[j++] = who[i];
    }
    return aux;
}

int main(int argc, char ** args){
    if(argc == 2){
        char* s = args[1];
        pthread_t thr;
        if(pthread_create(&thr, NULL, rev, s)){
            perror(NULL);
            return errno;
        }
        void *result;
        if(pthread_join(thr, &result)){
            perror(NULL);
            return errno;
        }
        printf("%s\n", result);
    }
    return 0;
}
