#include <stdio.h>          /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
// #include <time.h>

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
	char recv_data[100];
	int bytes_sent, bytes_received;
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */

	int sin_size;

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

	FILE *fp;
	fp = fopen("server.txt","w");

	while(1){
		sin_size=sizeof(struct sockaddr_in);
		if ((conn_sock = accept(listen_sock,(struct sockaddr *)&client,&sin_size))==-1){ /* calls accept() */
			printf("accept() error\n");
			exit(-1);
		}
  
		printf("\nYou got a connection from %s\n",inet_ntoa(client.sin_addr) ); /* prints client's IP */
  
		bytes_sent = send(conn_sock,"Welcome to my server.\n",22,0); /* send to the client welcome message */
		if (bytes_sent < 0){
			printf("\nError!Can not sent data to client!");
			close(conn_sock);
			continue;
		}

		do{
			bytes_received = recv(conn_sock,recv_data,100,0); //blocking
			if (bytes_received < 0){
				printf("\nError!Can not receive data from client!");
				close(conn_sock);
			}
			else{

				recv_data[bytes_received] = '\0';
				String_Upper(recv_data);
				// puts(recv_data);

				fprintf(fp, "%s",recv_data);
				if(strcmp(recv_data,"Q") == 0 || strcmp(recv_data,"q") == 0){
					rewind(fp);
				}
			}	
		}
		while(strcmp(recv_data,"Q") != 0 && strcmp(recv_data,"q") != 0 && bytes_received != 0);
		
		
		// fclose(fp);
		// fp = fopen("server.txt","r");
		// if(fp == NULL){
		// 	printf("File read on Server not Found\n");
		// 	exit(1);
		// }
		// if(fp != NULL){
		// 	printf("cc\n");
		// 	while(fgets(recv_data,100,fp) != NULL){
		// 		puts(recv_data);
		// 		bytes_sent = send(conn_sock,recv_data,strlen(recv_data),0);
		// 		if(bytes_sent < 0){
		// 			printf("\nError!Cannot send data to sever!\n");
		// 			close(conn_sock);
		// 		}
		// 		recv_data[bytes_sent] = '\0';
		// 	}			
		// }
		// fclose(fp);
		printf("\n");
	}
	
	close(listen_sock);
	return 0;
}