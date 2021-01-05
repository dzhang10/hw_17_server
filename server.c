#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>



int gcd(int a, int b){

        int r=a%b;

        while(r!=0){
                a=b;
                b=r;
                r=a%b;
        }

        return b;

}

int main() {

	while(1){
		printf("[Server Setup] cts created (aka WKP)\n");
		//-1 server creates pipe
		mkfifo("cts", 0644);

		//-1 server waits for connection
		printf("[Server Setup] Waiting for client connection...\n");
		int cts = open("cts", O_RDONLY);

		printf("[Server Setup] client connection initiated\n");

		//server gets the stc pipe
		char pipe_name[32];
    		read(cts,pipe_name,sizeof(pipe_name));
		printf("[Server Handshake] received client pipe name: %s\n",pipe_name);
    		remove("cts");
		printf("[Server Handshake] cts (aka WKP) removed \n");

		//2 server sends to client
    		int stc = open("stc", O_WRONLY);
		printf("[Server Handshake] connected to client\n");


    		write(stc,"HELLO",6);
		printf("[Server Handshake] Acknowledgement sent\n");

		//server gets acknowledgement from client
    		char msg[32];
    		read(cts, msg,sizeof(msg));
    		printf("[Server Handshake] Acknowledgement Received <%s>\n", msg);

		int input1;
		int input2;
		int answer;

		while(read(cts,&input1,sizeof(input1)) && read(cts,&input2,sizeof(input2))){
			answer = gcd(input1,input2);
			write(stc,&answer,sizeof(answer));
		}
    	}
}
