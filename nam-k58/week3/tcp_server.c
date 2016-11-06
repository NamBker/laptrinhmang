#include <stdio.h>          /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 5550   /* Port that will be opened */ 
#define BACKLOG 2   /* Number of allowed connections */

int main()
{
 
	int listen_sock, conn_sock; /* file descriptors */
	char recv_data[1024];
	int bytes_sent, bytes_received;
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */

	int sin_size;

	if ((listen_sock=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		printf("socket() error\n");
		exit(-1);
	}

	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
	server.sin_addr.s_addr = INADDR_ANY;  /* INADDR_ANY puts your IP address automatically */   
	bzero(&(server.sin_zero),8); /* zero the rest of the structure */

  
	if(bind(listen_sock,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1){ /* calls bind() */
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

		printf("You got a connection from %s\n",inet_ntoa(client.sin_addr) ); /* prints client's IP */
  
		bytes_sent = send(conn_sock,recv_data,strlen(recv_data),0); /* send to the client welcome message */
		if (bytes_sent < 0){
			printf("\nError!Can not sent data to client!");
			close(conn_sock);
			continue;
		}
		
		bytes_received = recv(conn_sock,recv_data,1024,0); //blocking



		if (bytes_received < 0){
			printf("\nError!Can not receive data from client!");
			close(conn_sock);
		}
		else{
			recv_data[bytes_received] = '\0';
			puts(recv_data);
		}	
	}
	
	close(listen_sock);
	return 0;
}