#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
	pid_t pid = fork();
	if(pid < 0)
		return errno ;
	else if(pid == 0){
	/* child instructions */
		printf("My pid %d Child PID= %d \n " , getppid() , getpid());
		char * argv [] = {"ls" ,NULL };
		execve("/bin/ls" ,argv ,NULL );
		perror(NULL);
	}
	else{
	/* parent instructions */
		wait(NULL);
		printf("Child %d finished\n", pid); ///in pid avem cel al copilului
	}
	return 0;
}
