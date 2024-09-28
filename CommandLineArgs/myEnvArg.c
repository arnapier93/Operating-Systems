#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv, char **envp) {


	if(argc < 2) {
		printf("Must provide mode\n");
		return 1;
	}
	int i = 0;
	if (strcmp(argv[1], "-u") == 0){
		while(envp[i] != NULL){
			if (strstr (envp[i], "USER")){
			printf("%s\n", envp[i]);
			}
		i++;
		}
	} else if (strcmp(argv[1], "-p") == 0){
		while(envp[i] != NULL){
			if (strstr (envp[i], "PWD")){
			printf("%s\n", envp[i]);
			}
		i++;
		}
	} else { 
		printf("You must use either -u or -p\n");
	}
	return 0;
}
