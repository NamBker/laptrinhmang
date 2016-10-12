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

typedef struct User{
	char name[40];
	char password[40];
}elementtype;
void del(){
	while(getchar() != '\n');
}
int main(){
	int client_sock;
	char buff[100];
	char recv_data[100];
	struct sockaddr_in server_addr;
	int bytes_sent,bytes_received,bytes_total;
	bytes_total= 0;

	client_sock=socket(AF_INET,SOCK_STREAM,0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5550);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))!=0){
		printf("\nError!Can not connect to sever!Client exit imediately! \n");
		return 0; 
	}
	
	bytes_received = recv(client_sock,buff,100,0);
	if(bytes_received == -1){
		printf("\nError!Cannot receive data from sever!\n");
		close(client_sock);
		exit(-1);
	}
	buff[bytes_received] = '\0';
	puts(buff);
	char choose[20];
	char name[40];
	char password[40];
	int memory= 0;
	elementtype SESSION;
	elementtype user;
	strcpy(SESSION.name,"");
	strcpy(SESSION.password,"");


	do{
		if(strcmp(SESSION.name,"") == 0){
			printf("You not login\n");
			printf("\n1.lOGIN\n2.EXIT\nChoose:");
			gets(choose);
			while( strcmp(choose,"1") != 0 && strcmp(choose,"2") ){
				printf("Error choose.Againt:");
				gets(choose);
			}
			if(strcmp(choose,"1") == 0){
				printf("*******************\n");
				printf("You name is:");
				gets(name);
				printf("%s\n",name);
				strcpy(buff,name);
				bytes_sent = send(client_sock,buff,100,0);
				if(bytes_sent == -1){
					printf("\nError!Cannot send data to sever!\n");
					close(client_sock);
					exit(-1);
				}
				bytes_received = recv(client_sock,recv_data,100,0);

				if(bytes_received == -1){
					printf("\nError!Cannot receive data from sever!\n");
					close(client_sock);
					exit(-1);
				}
				if(strcmp(recv_data,"0") == 0){
					printf("Username error\n");
					close(client_sock);
					exit(-1);	
				}
				if(strcmp(recv_data,"1") == 0){
					printf("User have on server\n");
					strcpy(user.name,recv_data);
					do{
						printf("You password is:");
						gets(password);
						strcmp(SESSION.password,password);
						strcpy(buff,password);
						bytes_sent = send(client_sock,buff,100,0);
						if(bytes_sent == -1){
							printf("\nError!Cannot send data to sever!\n");
							close(client_sock);
							exit(-1);
						}

						memset(recv_data,'\0',(strlen(recv_data)+1));
						bytes_received = recv(client_sock,recv_data,100,0);
						if(strcmp(recv_data,"1") == 0){
							strcpy(SESSION.name,name);
							strcpy(SESSION.password,password);
							printf("Log in sussess\n");
							
							
							// to do
						}
						if(strcmp(recv_data,"0") == 0){
							printf("Error Password\n");
						}	
					}while(strcmp(recv_data,"1") != 0);	
				}
			}
			else{
				bytes_sent = send(client_sock,"2",strlen("2"),0);
				printf("Exit programs\n");
			}
		}
		else{
			printf("*********************\n");
			printf("Welcome Hello:%s\n",SESSION.name);
			printf("Somthing to do\n");
			printf("\n1.LOGOUT\n2.EXIT\nChoose:");
			gets(choose);
			while( strcmp(choose,"1") != 0 && strcmp(choose,"2") != 0){
				printf("Error choose.Againt:");
				gets(choose);
			}
			if(strcmp(choose,"1") == 0){
				strcpy(SESSION.name,"");	
			}
			
		}
	}while((strcmp(choose,"2") != 0));


	close(client_sock);
	return 0;
}