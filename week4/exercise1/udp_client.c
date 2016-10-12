#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <string.h>

int main(){
	int client_sock;
	char buff[1024];
	struct sockaddr_in server_addr;
	int bytes_sent,bytes_received, sin_size;
	int bytes_total= 0;

	client_sock=socket(AF_INET,SOCK_DGRAM,0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5550);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	

	do{
		printf("\nInsert string to send:");
		memset(buff,'\0',(strlen(buff)+1));
		gets(buff);
		sin_size = sizeof(struct sockaddr);
		
		bytes_sent = sendto(client_sock,buff,strlen(buff),0, (struct sockaddr *) &server_addr, sin_size);
		if(bytes_sent == -1){
			printf("\nError!Cannot send data to sever!\n");
			close(client_sock);
			exit(-1);
		}
		bytes_total = bytes_total + bytes_sent;

		bytes_received = recvfrom(client_sock,buff,1024,0, (struct sockaddr *) &server_addr, &sin_size);
		if(bytes_received == -1){
			printf("\nError!Cannot receive data from sever!\n");
			close(client_sock);
			exit(-1);
		}
		buff[bytes_received] = '\0';
		puts(buff);
	}while(strcmp(buff,"Q") != 0 && strcmp(buff,"q") != 0);
	
	printf("You sent to server %d bytes\n",bytes_total);
	close(client_sock);
	return 0;
}
