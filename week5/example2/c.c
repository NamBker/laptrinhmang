<<<<<<< HEAD
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
=======
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
>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1

int main(){
	int client_sock;
	char buff[100];
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
	
	bytes_received = recv(client_sock,buff,100,0);
	if(bytes_received == -1){
		printf("\nError!Cannot receive data from sever!\n");
<<<<<<< HEAD
		close(client_sock);	
		exit(-1);
=======
		close(client_sock);
		exit(EXIT_FAILURE);
>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1
	}
	buff[bytes_received] = '\0';
	puts(buff);

	unsigned long fsize;
	FILE *rm;
	char filename[100];
	do{
		printf("\nInsert name file sent.('Q' or 'q' to Quit):");
		memset(filename,'\0',(strlen(filename)+1));
		gets(filename);	
	    rm = fopen(filename, "r");
	    if(rm != NULL){
	    	 printf("Found file %s\n", filename);
		    fseek(rm, 0, SEEK_END);
		    fsize = ftell(rm);
		    rewind(rm);
		    printf("File contains %ld bytes!\n", fsize);
		    if(fsize <2){ //2000000
		    	printf("Number bytes  of File < 2MB Not Sent!\n");
		    }
		    else{
			    printf("Sending the file now");
				while(!feof(rm)){

    				memset(buff,'\0',(strlen(buff)+1));
				  	int nread = fread(buff,100, 1,rm);
<<<<<<< HEAD
				  	printf("client_read:%s\n",buff);
=======
>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1
				  	if(nread >= 0){
				  		bytes_total = bytes_total+nread*100;
				  		 bytes_sent = send(client_sock, buff, strlen(buff), 0);
						if(bytes_sent == -1){
							printf("\nError!Cannot send data to sever!\n");
							close(client_sock);	
						}
				  	}
				  	else{
				  		printf("%s\n",buff);
				  	}
				} 
				printf("\nYou  sent Server");

				rewind(rm);
				 // received to server
				fclose(rm);
				FILE *fp;
				strtok(filename,".");
				strcat(filename,"_converse.txt");
<<<<<<< HEAD
				 
				fp = fopen("server_client.txt","w");
=======
				fp = fopen(filename,"w");
>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1
				if(fp != NULL){
					do{
						memset(buff,'\0',(strlen(buff)+1));
						bytes_received = recv(client_sock,buff,100,0); //blocking
						if (bytes_received < 0){
							printf("\nError!Can not receive data from client!");
							close(client_sock);
						}
						else{
<<<<<<< HEAD
							printf("%s\n",buff);
=======
>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1
							fputs(buff,fp);
							memset(buff,'\0',(strlen(buff)+1));
							if(bytes_received == 0){
								break;
							}
							if(bytes_received <100 && bytes_received >0){
								break;
							}
						}
					}
					while(bytes_received >0);
				}
				fclose(fp);
			}
		}
		else{
			if((strcmp(filename,"Q") != 0) && (strcmp(filename,"q") != 0)){
				printf("Not file Found\n");
			}
<<<<<<< HEAD
=======
			else{
		  		 bytes_sent = send(client_sock, "Q", strlen("Q"), 0);

			}
>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1
		}
	}while((strcmp(filename,"Q") != 0) && (strcmp(filename,"q") != 0));


	printf("\nTotal bytes you sent to server:%d bytes\n",bytes_total);
	close(client_sock);
	return 0;
}
