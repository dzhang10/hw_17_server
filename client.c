#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>


int main() {


	//client creates pipe
    	mkfifo("stc", 0644);
    	printf("[Client] Pipe Created\n");

    	int cts = open("cts", O_WRONLY);
	printf("[Client Handshake] connected to server\n");


	//client sends to server
    	write(cts,"stc",10);
    	printf("[Client Handshake] Sent stc pipe\n");
	printf("[Client Handshake] Waiting for Connection...\n");
	int stc = open("stc", O_RDONLY);
	printf("[Client Handshake] server connected\n");

	remove("stc");
	printf("[Client Handshake] removed pipe\n");

	//client reads from server
    	char msg[32];
    	read(stc, msg,sizeof(msg));
    	printf("[Client Handshake] Received ack <%s>\n", msg);

	//client sends to server
    	write(cts, msg,sizeof(msg));
    	printf("[Client Handshake] Sent ack\n");
	printf("[Client Handshake] Complete\n");

	int input;
	int output;

    	while(1){

        	printf("GCD CALCULATOR\nFirst Int: ");
        	scanf("%d",&input);
		write(cts,&input,sizeof(input));

		printf("Second Int: ");
		scanf("%d",&input);
		write(cts,&input,sizeof(input));

		read(stc,&output,sizeof(output));
        	printf("GCD: %d\n\n",output);
 	}

	return 0;
}
