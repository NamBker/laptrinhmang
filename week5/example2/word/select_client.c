#include <stdio.h>          /* These are the usual header files */
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/wait.h>

int main(){
	int client_sock;
	char buff[1024];
	struct sockaddr_in server_addr;
	int bytes_sent,bytes_received,bytes_total;
	bytes_total= 0;

	client_sock=socket(AF_INET,SOCK_STREAM,0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5550);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))!=0){
		printf("\nError!Can not connect to sever!Client exit imediately! ");
		return 0;
	}
	
	bytes_received = recv(client_sock,buff,1024,0);
	if(bytes_received == -1){
		printf("\nError!Cannot receive data from sever!\n");
		close(client_sock);
		exit(-1);
	}
	buff[bytes_received] = '\0';
	puts(buff);

	do{
		printf("\nInsert string to send:");
		memset(buff,'\0',(strlen(buff)+1));
		gets(buff);
		printf("\nyou click:");
		puts(buff);
		bytes_sent = send(client_sock,buff,strlen(buff),0);
		bytes_total = bytes_total +bytes_sent;
		
		if(bytes_sent == -1){
			printf("\nError!Cannot send data to sever!\n");
			close(client_sock);
			exit(-1);
		}

		bytes_received = recv(client_sock,buff,1024,0);
		if(bytes_received == -1){
			printf("\nError!Cannot receive data from sever!\n");
			close(client_sock);
			exit(-1);
		}
		buff[bytes_received] = '\0';
		puts(buff);

	}
	while((strcmp(buff,"Q") != 0) && (strcmp(buff,"q")) != 0);

	printf("Total bytes you sent to server:%d bytes\n",bytes_total);
	close(client_sock);
	return 0;
}