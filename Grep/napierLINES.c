#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 1024

int main(int argc, char **argv){
	
	char buffer[BUFF_SIZE];
	char *file_name;
	int file_len, line_count = 1; //minimum of 1 line
	
	if ( argc == 2){	//checks args for format
			file_name = argv[1];
	} else {
		printf("Usage: ./napierLINES file_name\n");
		return 1;
	}

	int fd = open(file_name, O_RDONLY); //open file passed by arg
	
	if (fd < 3) { //check file opening
			printf("Error opening the file \n");
			return 1;
	}
	
	file_len = read(fd, buffer, BUFF_SIZE); //read into buffer get file length
	
	for(int i = 0; i < file_len; i++){ //gets line count
		if(buffer[i] == '\n'){
			line_count++;
		}
	}
	
	int *line_len = (int *) malloc(sizeof(int) * line_count); //int array for line length
	char **line_array = (char **) malloc(sizeof(char *) * line_count); // array for actul lines
				
	for(int i = 0; i < line_count; i++){    //gets the length of each line	
		line_len[i] = 0;
		for(int j = 0; j < file_len; j++){			
			if(buffer[j] != '\n'){
				line_len[i]++;
			} else{
				i++;
			}
		}
	}
	
	for(int i = 0; i < line_count; i++){	//allocates specific sized arrays for each line
		line_array[i] = (char *) malloc(sizeof(char) * (line_len[i] + 1));	
	}
		
	int previous_lines = 0, print_length;
	char print_buff[BUFF_SIZE];
	
	for (int i = 0; i < line_count; i++){ //fills the line array and writes to the screen
		if( i > 0){ 
			previous_lines = previous_lines + line_len[i-1] + 1 ;
		}
		for (int j = 0; j < line_len[i]; j++){
			line_array[i][j] = buffer[j + previous_lines];
		}
		
		print_length = sprintf(print_buff, "line_array[%d] = \"%s\"\n", i, line_array[i]);
		write(1, print_buff, print_length);
	}
	
	close(fd);
	free(line_array);
	free(line_len);

	return 0;
}