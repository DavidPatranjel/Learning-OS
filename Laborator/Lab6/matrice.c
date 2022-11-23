#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>

int a[20][20], b[20][20], c[20][20], m, p, n;

struct poz{
    int i,j;
};

void 
*mul(void *v){
    struct poz *pp = v;
    int *result = (int*) malloc(sizeof(int));
    for(int k = 1; k <= p; ++k){
        int i,j;
        i = pp->i; j = pp->j;
        (*result) = (*result) + a[i][k] * b[k][j];
    }
    return result;
}

int main(){
    printf("m= "); 
    scanf("%d", &m);
    printf("p= "); 
    scanf("%d", &p);
    printf("n= "); 
    scanf("%d", &n);
    printf("Matricea A mxp: ");
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= p; j++){
            scanf("%d", &a[i][j]);
        }
    } 
    printf("Matricea B pxn: ");
    for(int i = 1; i <= p; i++){
        for(int j = 1; j <= n; j++){
            scanf("%d", &b[i][j]);
        }
    } 

    int aux = 1;
    pthread_t thr[(m+1)*(p+1)];
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= p; ++j){
            struct poz *pp = (struct poz*) malloc(sizeof(struct poz));
            pp->i = i; pp->j = j;
            if(pthread_create(&thr[aux++], NULL, mul, pp)){
                perror(NULL);
                return errno;
            }
        }
    }
    aux = 1;
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= p; ++j){
            int *result;
            if(pthread_join(thr[aux++], &result)){
                perror(NULL);
                return errno;
            }
            c[i][j] = *result;
        }
    }
        
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= n; ++j){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}
