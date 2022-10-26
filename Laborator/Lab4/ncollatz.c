#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char ** args){

	if( argc >= 2){
		for(int i = 1; i < argc; ++i){
			char* number = args[i];
			pid_t pid = fork();
			if(pid < 0)
				return errno ;
			else if(pid == 0){
				/* child instructions */
				char* argv [] = {"./c", number ,NULL };
				execve(argv[0] ,argv ,NULL );
				perror(NULL);
			}else{
				/* parent instructions */
				wait(NULL);
				printf("Child %d finished\n", pid); ///in pid avem cel al copilului
			}
		}
	}else{
		char* error = "Eroare! Args insuficiente!";
		write(1, error, strlen(error));
	}
	return 0;
}
