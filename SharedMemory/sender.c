#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "message.h"

int main ( void ) { 
	
	int r = ERR, id = ERR;
	char input[MAX];
	struct msg *send;
	
	id = shmget(KEY, MSG_SZ, 0666 | IPC_CREAT);
	if(id == ERR){
		perror("Shared memory get error\n");
		return -1;
	}
	
	send = (struct msg *) shmat(id, 0, 0);
	send->msg_new = 0;
	send->msg_txt = input;
	
	while(strcmp(send->msg_txt,"quit") != 0) {
		
		if (send->msg_new == 0){	//room for new message

			printf("Enter message>> ");
			fflush(stdout);
			
			r = read(0, send->msg_txt, MAX);
			if (r == ERR){
				perror("Read error\n"); 
				return -1;
			}
			send->msg_txt[r-1] = '\0'; 	//replaces \n
			send->msg_len = r-1; 		//acounts for \n removal
			send->msg_new = 1;
			
		} else if (send->msg_new == 1) { 
			print_msg(*send);
			sleep(2);
			//send->msg_new = 0;
		} else {
				perror("Flag error\n");
			return -1;
		}

	}
	
	return 0;
}
