#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "message.h"
#include "usage.h"

int main (int argc, char *argv[]){

	char flag;
	char input[MAX];
	int msg_sz = MAX + sizeof(int);
	key_t key;
	struct msg msg;
	int q_id = -1, p = -1;

	//The program expects inputs from the user through the argument list passed through the command prompt
	if(argc >= 3){
		flag = argv[1][1];
		key = atoi(argv[2]);
		if (key == 0){
			printf(USAGE);
			printf("Error! Key value must be integer\n");
			return 1;
		}
	} 
	else {
		printf(USAGE);
		return 1;
	}
	
	//The application can do one of the following functions:
	
	/*msqQTest -c/C <key>*/
	//Create a message queue using the –c/C flag and the key entered by the user to identify the msg queue
	if (flag == 'c' || flag == 'C'){
		if (argc != 3){
			printf(USAGE_C);
			return 1;
		}
		q_id = msgget(key, 0);
		if(q_id != -1){
			printf("Message queue already exists and has ID: %d\n", q_id);
			return 0;
		}
		q_id = msgget(key, IPC_CREAT|0777);
		if (q_id == ERR){
			perror("Error creating message queue\n");
			return 1;
		}
		printf("Message queue successfuly created with id: %d\n", q_id);
		return 0;
	}
	
	/*msqQTest -s/S <key> <type> <text>*/
	//Send a message of specific type to the intended message queue using the –s/S flag and the key used to create the msg queue.
	//This option will print the message that was sent to the queue
	else if (flag == 's' || flag == 'S') {
		if (argc < 5){
			printf(USAGE_S);
			return 1;
		}
		
		msg.type = atoi(argv[3]);
		if (msg.type == 0){
			printf("Error! Message type must be integer\n");
			printf(USAGE);
			return 1;
		}
		
		q_id = msgget(key, 0);
		if (q_id == ERR){
			perror("Error accessing message queue\n");
			return 1;
		}
		
		//argv[4] is the first possible location for message text
		//we have to make all argv[>4] be stored in one char[]
		int j = 0, k = 0; //initialized outside loop to maintain value
		for (int i = 4; i < argc; i++ ){ //loops through argv[] starting at [4]
			for ( j = 0; argv[i][j] != '\0'; j++){ //resets j but not k
				input[k + j] = argv[i][j];
			}
			k += j; //adds in last word len
			input[k] = ' ';	//adds spaces inbetween words
			k++;
		}
		input[k] = '\0'; //pads with null char
		k++;
		
		msg.txt = input;
		msg.len = k;
		
		int sent = -1;
		sent = msgsnd(q_id, &msg, msg_sz, 0);
		if (sent == ERR){
			printf("Message failed to send\nMSG Queue ID: %d\nMessage Size: %d\n",q_id,k);
			perror("");
			return 1;
		}
		
		printf("Message successfuly added to queue %d\n", q_id);
		return 0;
	}
	
	//msqQTest -r/R <key> <type>
	//Receive a message of specific type from the intended message queue using the key used to create the msg queue:
	else if (flag == 'r' || flag == 'R') {
		if (argc != 4){
			printf(USAGE_R);
			return 1;
		}
		
		msg.type = atoi(argv[3]);
		if (msg.type == 0){
			printf("Error! Message type must be integer\n");
			printf(USAGE);
			return 1;
		}
	
		q_id = msgget(key, 0);
		if(q_id == ERR){
			perror("Error accessing message queue\n");
			return 1;
		}
		
		int rcvd = -1;
		rcvd = msgrcv(q_id, &msg, msg_sz, msg.type, IPC_NOWAIT);
		if(rcvd == ERR){
			perror("Failed to receive message\n");
			return 1;
		}
		
		printf("%li\n", msg.type);
		printf("%d\n", msg.len);
		printf("%s\n", msg.txt);
		
		int p = print_msg(msg);
		if (p == ERR){
			perror("Error: printing message\n");
			return 1;
		}
		printf("Message received successfuly!\n");
		return 0;
	}
	
	//msqQTest -d/D <key>
	//Delete a msg queue using the key used to create the msg queue: 
	else if (flag == 'd' || flag == 'D') {
	
		if (argc != 3){
			printf(USAGE_D);
			return 1;
		}
		
		q_id = msgget(key, 0);
		if (q_id == ERR){
			perror("Error accessing message queue\nCheck that queue exists and has permissions\n");
			return 1;
		}

		struct msqid_ds qbuf;
		
		msgctl(q_id, IPC_STAT, qbuf)

		printf("Message queue %d successfuly deleted\n", q_id);
		return 0;
	}	
	
	else {
		printf(USAGE);
	}
	
	return 0;
}