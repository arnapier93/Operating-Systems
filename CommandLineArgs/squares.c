#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv, char **envp) {
	
	//check for args
	if(argc < 2){
		printf("Provide arguments");
		return 1;
	}
	
	//establishes two arrays and two loop counters
	int *numbers = (int *) malloc(sizeof(int) * (argc - 1) );
	int *squares = (int *) malloc( sizeof(int) * (argc - 1) );
	int i = 1;
	int j = 0;
	
	//converts strings entered to integers for mathing
	while ( i < argc ){
		numbers[i-1] = atoi(argv[i]);
		i++;
	}

	//sets values of squares to the squares of numbers and prints them to the screen
	while ( j < (argc-1) ) {
		squares[j] = numbers [j] * numbers[j];
		printf("%d ", squares[j]);
		j++;
	}
	printf("\n");	
	
	free(numbers);
	return 0;
}


