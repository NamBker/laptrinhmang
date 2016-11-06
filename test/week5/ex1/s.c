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

#define PORT 5550   /* Port that will be opened */ 
#define BACKLOG 20   /* Number of allowed connections */
#define FILENAME "server.txt"

void sig_chld(int signo){
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("[ForkingServer] Child %d terminated\n",pid);
}

void String_Upper(char string[]) 
{
	int i = 0;
 
	while (string[i] != '\0') 
	{
    	if (string[i] >= 'a' && string[i] <= 'z') {
        	string[i] = string[i] - 32;
    	}
      	i++;
	}
}

int main()
{
 
	int listen_sock, conn_sock; /* file descriptors */
	char recv_data[100];
	int bytes_sent, bytes_received;
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */

	pid_t pid;

	int sin_size;

	if ((listen_sock=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		printf("socket() error\n");
		exit(-1);
	}
	printf("Server-socket() is OK...\n");
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */   

	if(bind(listen_sock,(struct sockaddr*)&server,sizeof(server))==-1){ /* calls bind() */
		printf("bind() error\n");
		exit(-1);
	}     

	if(listen(listen_sock,BACKLOG) == -1){  /* calls listen() */
		printf("listen() error\n");
		exit(-1);
	}




	while(1){
		sin_size=sizeof(struct sockaddr_in);
		if ((conn_sock = accept(listen_sock,(struct sockaddr *)&client,&sin_size))==-1){ /* calls accept() */
			printf("accept() error\n");
			exit(-1);
		}

		if((pid = fork()) == 0){
			close(listen_sock);
			printf("\nYou got a connection from %s\n",inet_ntoa(client.sin_addr) ); /* prints client's IP */
			bytes_sent = send(conn_sock,"Welcome to my server.\n",22,0); /* send to the client welcome message */
			
			if (bytes_sent < 0){
				printf("\nError!Can not sent data to client!");
				close(conn_sock);
				continue;
			}
			FILE *fp;
			fp = fopen(FILENAME,"w");
			rewind(fp);
			fclose(fp);
			fp = fopen(FILENAME,"r+");
			do{
				memset(recv_data,'\0',(strlen(recv_data)+1));
				bytes_received = recv(conn_sock,recv_data,100,0); //blocking
				if (bytes_received < 0){
					printf("\nError!Can not receive data from client!");
					fclose(fp);
					close(conn_sock);
				}
				else{
					String_Upper(recv_data);
					fputs(recv_data,fp);
					memset(recv_data,'\0',(strlen(recv_data)+1));
					if(bytes_received >0 && bytes_received < 100){
						// sent file to client
					    rewind(fp);
					    printf("Sending the file now");
					    while(!feof(fp)){
							memset(recv_data,'\0',(strlen(recv_data)+1));
						  	int nread = fread(recv_data,100, 1,fp);
						  	if(nread >= 0){
						  		bytes_sent = send(conn_sock, recv_data, strlen(recv_data), 0);
								if(bytes_sent == -1){
									printf("\nError!Cannot send data to sever!\n");
									fclose(fp);
									close(conn_sock);
								}
						  	}
						} 
					printf("End sent to Client\n");
					fclose(fp);
					fp = fopen(FILENAME,"w");
					fclose(fp); 
					fp = fopen(FILENAME, "r+");				
					}
				}
			} while(bytes_received >0);
			exit(0);
		}
			signal(SIGCHLD,sig_chld);
			close(conn_sock);
	}
	
	close(listen_sock);
	return 0;
}