#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char ** args){
    char shm_name[] = "myshm";
    int shm_fd;

    shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
    if(shm_fd < 0){
        perror(NULL);
        return errno;
    }

    size_t shm_size = 1000;
    if(ftruncate(shm_fd, shm_size) == -1){
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }
    
    int* shm_ptr = mmap(0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);
    if(shm_ptr == MAP_FAILED){
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }       

    return 0;
}