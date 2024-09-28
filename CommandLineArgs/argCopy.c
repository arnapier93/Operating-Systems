#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv, char **envp) {

	//defines an arrazy of character arrays 5 arrays 256 chars long
	#define MAX_NUM_OF_ARGS 5
	#define MAX_ARG_SIZE 256
	char argumentArray[MAX_NUM_OF_ARGS][MAX_ARG_SIZE];
	
	//initializes loop counters and "string" for defaultArg
	int i = 0;
	int j = 0;
	char darg[10] = "defaultArg";
	
	//check for proper # of args
	if(argc < 2){
		printf("Please provide arguments and %s will copy and display them \n", argv[0]);
		return 1;
	}  
	if (argc > 5){
		printf("Too many arguments. Max arguments is: %d \n", (MAX_NUM_OF_ARGS-1));
		return 1;
	}
	
	//fill argumentArray with default args
	while( i <= 5 ){		
	/*and*/ while ( j <= 10 ) {
				argumentArray[i][j] = darg[j];
				j++;
			}
		j=0;	
		i++;
	} j = 0; i = 0; //reset counters
	
	//fill argumentArray with args provided from user
	while( i < argc ){
		int arglen = strlen(argumentArray[i]);
	/*and*/ while ( j < arglen ) {
				argumentArray[i][j] = argv[i][j];
				j++;
			}
		j = 0;
		i++;
	} j = 0; i = 0; //reset counters
	
	//print argumentArray 
	while( i < MAX_NUM_OF_ARGS ){
		printf("Arg%d: ", i );
		printf("%s \n", argumentArray[i]);
		i++;
	} printf("\n"); j = 0; i = 0; //print new line and reset counters

	return 0;
}


