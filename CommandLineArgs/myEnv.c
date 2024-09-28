#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv, char **envp) {

	int i = 0;
	while(envp[i] != NULL){
	printf("%s\n", envp[i]);
	i++;
	
	}

	return 0;
}
