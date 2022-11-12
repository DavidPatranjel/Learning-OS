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

void afis_pids(){
    printf("Done Parent %d Me %d\n", getppid(), getpid());
}

int main(int argc, char ** args){
    printf("Starting parent %d \n", getpid());

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

    int* shm_ptr = mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(shm_ptr == MAP_FAILED){
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }    

    int size_v = shm_size/(argc-1);

    if(argc >=2){
        for(int i = 1; i < argc; ++i){
            int number = atoi(args[i]);
            pid_t pid = fork();
            if(pid < 0)
                return errno;
            else if(pid == 0){
                /*child instructions*/
                char* p = shm_ptr + (i-1) * size_v;
                int mem_util = sprintf(p, "%d ", number);
                while(number != 1){
                    mem_util = mem_util + sprintf(p + mem_util, "%d ", number);
                    if(number % 2 == 0) number /= 2;
                    else number = 3 * number + 1;
                }
                mem_util = mem_util + sprintf(p + mem_util, "%d \n", 1);
                afis_pids();
                perror(NULL);
                exit(0);
            }
            
        }
        for(int i = 1; i < argc; ++i)
            wait(NULL);
        for(int i = 1; i < argc; ++i)
            printf("%s", shm_ptr + (i-1) * size_v);

        afis_pids();

    }else{
        char *error = "Eroare! Args insuficiente\n";
        write(1, error, strlen(error));
    }
    
    shm_unlink(shm_name);
    munmap(shm_ptr, shm_size);
    return 0;
}