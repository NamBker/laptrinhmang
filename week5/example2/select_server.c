#include <stdio.h>     
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
#define BACKLOG 2   /* Number of allowed connections */

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
	char recv_data[1024];
	int bytes_sent, bytes_received;
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */

	int sin_size;


	fd_set active_fd_set, read_fd_set;
	int i;


	if ((listen_sock=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		printf("socket() error\n");
		exit(-1);
	}
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

	FD_ZERO(&active_fd_set);
	FD_SET(listen_sock,&active_fd_set);

	while(1){
		read_fd_set = active_fd_set;
		if(select(FD_SETSIZE,&read_fd_set,NULL,NULL,NULL) <0){
			perror("Select");
			exit(EXIT_FAILURE);
		}


		for(i=0; i< FD_SETSIZE; ++i){
			if(FD_ISSET(i,&read_fd_set)){
				if(i == listen_sock){
					int new;
					sin_size =sizeof(client);
					new = accept(listen_sock,(struct sockaddr *)&client,&sin_size);
					if( new < 0){
						perror("Accept");
						exit(EXIT_FAILURE);

					}

					fprintf (stderr,"Server: connect from host %s, port %hd.\n",inet_ntoa (client.sin_addr),
                         ntohs (client.sin_port));

					bytes_sent = send(new,"Welcome to my server.\n",22,0); /* send to the client welcome message */
					if (bytes_sent < 0){
						printf("\nError!Can not sent data to client!");
						close(new);
						continue;
					}

					FD_SET(new,&active_fd_set);
				}
				else{					
					bytes_received = recv(i,recv_data,1024,0); //blocking
					if (bytes_received < 0){
						printf("\nError!Can not receive data from client!");
						close(i);
						FD_CLR(i,&active_fd_set);
					}
					else{
						recv_data[bytes_received] = '\0';
						if(strcmp(recv_data,"q") == 0 || strcmp(recv_data,"Q") == 0){					
                            bytes_sent = send(i,"Q",strlen("Q"),0); /* send to the client welcome message */
							close(i);
							FD_CLR(i,&active_fd_set);
						}
						String_Upper(recv_data);
						printf("recv_data: %s\n",recv_data );
						printf("bytes_received: %d\n",bytes_received); 
						bytes_sent = send(i,recv_data,strlen(recv_data),0); /* send to the client welcome message */
					}	
					
				}
			}
		}

	}
}
