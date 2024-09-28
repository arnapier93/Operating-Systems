#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
	printf("me: %d parent: %d *\n", getpid(), getppid());
	fork(); wait(0);
	printf("me: %d parent: %d **\n", getpid(), getppid());
	fork(); wait(0);
	printf("me: %d parent: %d ***\n", getpid(), getppid());
	fork();	wait(0);
	printf("me: %d parent: %d *****\n", getpid(), getppid());
	fork(); wait(0);
	printf("me: %d parent: %d ****\n", getpid(), getppid());
	fork(); wait(0);
	printf("me: %d parent: %d ******\n", getpid(), getppid());
	
	
	
	sleep(30);
	
	return EXIT_SUCCESS;
}