#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp){

	if (argc != 2){
			printf("Usage: napierCreateNProcesses <n> \n");
			return 1;
	} 
	
	int n = atoi(argv[1]);
	int i;
		
	for (i = 1; i < n + 1; i++){
		
		int f = fork();
		
		if( f == 0){ // is child
			printf("	[c] this is child process: %d my pid is: %d\n", i, getpid());
			sleep(2);
			return i;			
		} else { //is parent 
			
			} 
		} 
for (int j = 1; j < n + 1; j++) {
	int child_pid = wait(&i);
	int creation_number = WEXITSTATUS(i);
	printf("[p] child %d pid = %d just exited\n", creation_number, child_pid);
		
	}
	
printf("I am the parent process pid %d and all my child processes exited\n", getpid());	
	
	return 0;
}
