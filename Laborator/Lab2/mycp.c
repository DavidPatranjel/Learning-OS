#include <unistd.h> //write++
#include <string.h> //Strings++
#include <fcntl.h> //Readonly++
#include <errno.h> //Errno++
#include <stdio.h> //Afisare++
int main( int argc, char *argv[] )  {
	
	if( argc == 3 ) {
		char* sursa = argv[1];
		char* destinatie = argv[2];
		write(1, destinatie, strlen(destinatie));
		write(1, "\n", strlen("\n"));
		write(1, sursa, strlen(sursa));
		write(1, "\n", strlen("\n"));
		char buffer[4096];
		ssize_t date;
		int fd_source = open(sursa, O_RDONLY);
		int fd_destination = open(destinatie, O_WRONLY|O_CREAT, 0644);
		if(fd_source == -1){
			printf("Error %d\n", errno);
		}
		if(fd_destination == -1){
			printf("Error %d\n", errno);
		}
		while(date = read(fd_source, buffer, 4096)){
			write(fd_destination, buffer, date);
		}
		close(fd_source);
		close(fd_destination);
	}else {
		char* error = "Eroare! Argumente insuficiente!\n";
		write(1, error, strlen(error));
	}
}
