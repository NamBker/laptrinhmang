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
#include <stdbool.h>

#define PORT 5550   /* Port that will be opened */ 
#define BACKLOG 2   /* Number of allowed connections */

typedef struct User{
	char name[40];
	char password[40];
}elementtype;

#include "lllib.h"
elementtype e;
elementtype user;

void sig_chld(int signo){
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("[ForkingServer] Child %d terminated\n",pid);
}
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

int main(){

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
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */   

	if(bind(listen_sock,(struct sockaddr*)&server,sizeof(server))==-1){ /* calls bind() */
		printf("bind() error\n");
		exit(-1);
	}     

	if(listen(listen_sock,BACKLOG) == -1){  
		printf("listen() error\n");
		exit(-1);
	}
	FILE *fp;
	fp = fopen("test.txt","r+");

	while(1){
		sin_size=sizeof(struct sockaddr_in);
		if ((conn_sock = accept(listen_sock,(struct sockaddr *)&client,&sin_size))==-1){
			printf("accept() error\n");
			exit(-1);
		}
  
		if((pid = fork()) == 0){
			printf("**************\n");
			printf("You got a connection from %s\n",inet_ntoa(client.sin_addr) ); 
  
			bytes_sent = send(conn_sock,"Welcome to my server.\n",22,0); 
			if (bytes_sent < 0){
				printf("\nError!Can not sent data to client!");
				close(conn_sock);
				continue;
			}

				// Doc du lieu
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
			do{
				printf("****************\n");
				printf("Waiting from Client:\n");
				memset(recv_data,'\0',(strlen(recv_data)+1));
				bytes_received = recv(conn_sock,recv_data,100,0);
				if (bytes_received < 0){
					printf("\nError!Can not receive data from client!");
					close(conn_sock);
				}
				else{
					printf("User: %s\n",recv_data);
					if(searcUser(recv_data) == 0){
						printf("Server haven't username: %s\n",recv_data);
						bytes_sent = send(conn_sock,"0",strlen("0"),0); 
						if(bytes_sent == -1){
							printf("\nError!Cannot send data to sever!\n");
							close(conn_sock);
							exit(-1);
						}
					}

					if(searcUser(recv_data) == 1){

						printf("Username of you can Sign Up:%s\n",recv_data);
						bytes_sent = send(conn_sock,"1",strlen("1"),0); 	
						if(bytes_sent == -1){
							printf("\nError!Cannot send data to sever!\n");
							close(conn_sock);
							exit(-1);
						}
						do{
							printf("Check password\n");
							memset(recv_data,'\0',(strlen(recv_data)+1));
							bytes_received = recv(conn_sock,recv_data,100,0);
							if (bytes_received < 0){
								printf("\nError!Can not receive data from client!");
								close(conn_sock);
							}
							else{
								if(checkPassword(recv_data) == 1){
									printf("Password ok:%s\n",recv_data);
									bytes_sent = send(conn_sock,"1",strlen("1"),0); 
									printf("Somthing doing....\n");	
								}
								else{
									printf("user:%s\n",user.name);
									printf("error password:%s\n",recv_data);
									bytes_sent = send(conn_sock,"0",strlen("0"),0); 	

								}
							}
						}while(checkPassword(recv_data) != 1);
						printf("End check password\n");
					}


				}	
			}while(strcmp(recv_data,"2") != 0 && bytes_received != 0);
			
			exit(0);
		}
		signal(SIGCHLD,sig_chld);
			close(conn_sock);

	}
	
	close(listen_sock);
	return 0;
}