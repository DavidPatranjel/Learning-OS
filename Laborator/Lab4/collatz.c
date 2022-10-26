#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char ** args){
	if( argc == 2){
		int number = atoi(args[1]);
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
			perror(NULL);
		}
		else{
		/* parent instructions */
			wait(NULL);
			printf("Child %d finished\n", pid); ///in pid avem cel al copilului
		}
	}else{
		char* error = "Eroare! Args insuficiente!";
		write(1, error, strlen(error));
	}
	return 0;
}
