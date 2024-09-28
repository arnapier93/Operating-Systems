#define ERR -1
#define MAX 1024

struct msg {
	long type;
	char *txt;
	int len;	
		//0 = sent / space available / ready for new message
		//1 = stored / space occupied / ready to be sent
};

int print_msg(struct msg m) {
	int w = write(1, m.txt, m.len);  
	printf("\n");
	return w; //write returns -1 for errors
};
