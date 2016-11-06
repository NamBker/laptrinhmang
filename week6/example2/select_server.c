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
#include <stdbool.h>


#define PORT 5550   /* Port that will be opened */ 
#define BACKLOG 2   /* Number of allowed connections */


typedef struct User{
	char name[40];
	char password[40];
}elementtype;

#include "library/lllib.h"
elementtype e;
elementtype user;

bool searcUser(char *name){
	int memory = 0;
	cur = root;
	while(cur != NULL){
		if(strcmp(name,cur->element.name) == 0){
			strcpy(user.name,cur->element.name);
			strcpy(user.password,cur->element.password);
			memory = 1;
		}
		cur = cur->next;
	}
	if(memory == 0){
		return false;
	}
	if(memory == 1){
		return true;
	}	
}
bool checkPassword(char *pass){
	int memory = 0;
	if(strcmp(pass,user.password) == 0){
		return true;
	}
	return false;
}

int main()
{
 
	int listen_sock, conn_sock; /* file descriptors */
	char recv_data[100];
	int bytes_sent, bytes_received;
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */

	int sin_size;


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

	FILE *fp;
	fd_set active_fd_set, read_fd_set;
	fp = fopen("library/test.txt","r+");
	FD_ZERO(&active_fd_set);
	FD_SET(listen_sock,&active_fd_set);

	// read data
	int sum = 0;
	int c;
	while(!feof(fp)){
		c = getc(fp);
		if(c == '\n'){
			sum = sum +1;
		}

	}
	rewind(fp);
	for(int i=0; i<sum; i++){
		fscanf(fp,"%s %s",e.name,e.password);
		printf("%s:",e.name );
		printf("%s\n",e.password );
		insertaffter(e);
	}

	char str[2]=":";
	char *token;
	char name[100];
	char check[100];
	int session[100];
	for(i= 0; i < 99; i++){
		session[i] = 0;
	}
	
	

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

					printf("**************\n");
					fprintf (stderr,"Server: You connect from host %s, port %hd.\n",inet_ntoa (client.sin_addr),
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
					bytes_received = recv(i,recv_data,100,0); //blocking
					if (bytes_received < 0){
						printf("\nError!Can not receive data from client!");
						close(i);
						FD_CLR(i,&active_fd_set);
					}
					recv_data[bytes_received] = '\0';

					if(strcmp(recv_data,"q") == 0 || strcmp(recv_data,"Q") == 0 || strcmp(recv_data,"2") == 0 || session[i] == 3){					
						fprintf (stderr,"Server: You terminated from host %s, port %hd.\n",inet_ntoa (client.sin_addr),
                         ntohs (client.sin_port));
						printf("*****************\n");
	                    bytes_sent = send(i,"Q",strlen("Q"),0); /* send to the client welcome message */
						close(i);
						FD_CLR(i,&active_fd_set);
						session[i] = 0;
					}
					else{
						token = strtok(recv_data,str);
						strcpy(name,token);
						token = strtok(NULL,str);
						strcpy(check,token);
						printf("**************\n");
						fprintf (stderr,"Server: You connect from host %s, port %hd.\n",inet_ntoa (client.sin_addr),
                         ntohs (client.sin_port));
						if(strcmp(check,"username") == 0){
							printf("Kiem tra user\n");
							if(searcUser(name) == 0){
								printf("Server haven't username: %s\n",name);
								bytes_sent = send(i,"0",strlen("0"),0); 
							}
							if(searcUser(name) == 1){
								printf("Username of you can Sign Up:%s\n",name);
								bytes_sent = send(i,"1",strlen("1"),0); 	
							}
						} // end check recv is user

						if(strcmp(check,"password") == 0){
							printf("Check password\n");
							if(checkPassword(name) == 1){
								printf("Password ok:%s\n",name);
								printf("Somthing doing....\n");	
								bytes_sent = send(i,"1",strlen("1"),0); 
								session[i] = 0;
							}
							if(checkPassword(name) == 0){
								printf("user:%s\n",user.name);
								printf("error password:%s\n",name);
								bytes_sent = send(i,"0",strlen("0"),0);
								session[i] = session[i] + 1;
							}
						} // end check recv is password
					}

				}
			} // end if isset
		} // end for check 

	}
}



					
								
					