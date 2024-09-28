#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>



int main(int argc, char **argv, char **envp)
{
	
	char *file_name, *child = "child\n", *parent = "parent\n";
	
	if ( argc == 2){	//checks args for format
			file_name = argv[1];
	} else {
		printf("Usage: ./napierTestInheritance1,2 file_name\n");
		return 1;
	}
	
	int fd = open(file_name, O_WRONLY);
	
	if (fd < 3) { //check file opening	
		printf("Error opening the file \n");
		return 1; }
			
	int f = fork();
	
	if( f == 0) { //is child	
		write(fd, child, 6);
		close(fd);
	} else if (f > 0) { //is parent
		write(fd, parent, 7);
		close(fd);
	} else {
		printf("Fork failed unexpectedly\n");
	}
	
	return 0;
}