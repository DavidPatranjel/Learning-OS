#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char ** args){

    if( argc >= 2){
		printf("Starting parent %d\n", getpid());
		for(int i = 1; i < argc; ++i){
			int number = atoi(args[i]);
			pid_t pid = fork();
			if(pid < 0)
				return errno ;
			else if(pid == 0){
				/* child instructions */
				printf("%d : ", number);
				while(number != 1){
					printf("%d ", number);
					if(number % 2 == 0) number /= 2;
					else number = 3 * number + 1;
				}
				printf("%d \n", 1);
				printf("Done Parent %d Me %d\n", getppid(), getpid());
				perror(NULL);
				exit(0);
			}
		}
		for(int i = 1; i < argc; ++i){
			wait(NULL);  
		}
		printf("Done Parent %d Me %d\n", getppid(), getpid());
	}else{
		char* error = "Eroare! Args insuficiente!";
		write(1, error, strlen(error));
	}
	return 0;
}