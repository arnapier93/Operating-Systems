#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "message.h"

int main (int argc, char **argv){
	
		struct msg *rcvd;
		int id;
		
		id = shmget(KEY, MSG_SZ, 0);
		if(id == -1){
			perror("Shared memory error\n");
			return -1;
		}
		
		rcvd = (struct msg *) shmat(id, 0, 0);
		
		printf("%d\n", id);
		print_msg(*rcvd);
		
		while(strcmp(rcvd->msg_txt,"quit") != 0){
			
			if(rcvd->msg_new == 1){				
				rcvd = (struct msg *) shmat(id, NULL, 0);
				if (rcvd == (void *) -1) {
					perror("Shared memory attach error");
					return -1;
				}
				print_msg(*rcvd);
				printf("message received!\n");
				rcvd->msg_new = 0;
			} else if (rcvd->msg_new == 0) {
				//do nothing
			} else {
				perror("Flag error\n");
				return -1;
			}
		}	
		printf("Successful Exit!\n");
		return 0;
}
