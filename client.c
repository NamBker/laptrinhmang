#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <string.h>

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
		close(client_sock);
		exit(-1);
	}
	buff[bytes_received] = '\0';
	puts(buff);

	unsigned long fsize;
	FILE *rm;
	char filename[100];
	do{
		printf("\nInsert name file sent.('Q' or 'q' to Quit):");
		memset(buff,'\0',(strlen(buff)+1));

		gets(filename);	
	    rm = fopen(filename, "r");
	    if(rm != NULL){
	    	 printf("Found file %s\n", filename);
		    fseek(rm, 0, SEEK_END);
		    fsize = ftell(rm);
		    rewind(rm);

		    printf("File contains %ld bytes!\n", fsize);
		    if(fsize <2000000){
		    	printf("Number bytes  of File < 2MB Not Sent!\n");
		    }
		    else{
			    printf("Sending the file now");
				while(fgets(buff,100,rm) != NULL){

					bytes_sent = send(client_sock,buff,strlen(buff),0);
					bytes_total = bytes_total +bytes_sent;
					
					if(bytes_sent == -1){
						printf("\nError!Cannot send data to sever!\n");
						close(client_sock);
					}
					buff[bytes_sent] = '\0';
				}
				bytes_sent = send(client_sock,buff,strlen(buff),0);
				if(bytes_sent == -1){
					printf("\nError!Cannot send data to sever!\n");
					close(client_sock);
				}
				buff[bytes_sent] = '\0';
				printf("\nYou  sent Server");
			}
		}
		else{
			if((strcmp(filename,"Q") != 0) && (strcmp(filename,"q") != 0)){
				printf("Not file Found\n");
			}
			else{
				strcpy(buff,filename);
				bytes_sent = send(client_sock,buff,strlen(buff),0);
				bytes_total = bytes_total +bytes_sent;
				
				if(bytes_sent == -1){
					printf("\nError!Cannot send data to sever!\n");
					close(client_sock);
				}
				buff[bytes_sent] = '\0';
			}
		}
	}while((strcmp(filename,"Q") != 0) && (strcmp(filename,"q") != 0));

		// received to server
		// strtok(filename,".");
		// strcat(filename,"_v1.txt");  // file name gio ten la: 
		// printf("%s\n",filename);
		// fclose(rm);
		// rm = fopen(filename,"w");
		// do{
		// 	bytes_received = recv(client_sock,buff,100,0); //blocking
		// 	if (bytes_received < 0){
		// 		printf("\nError!Can not receive data from client!");
		// 		close(client_sock);
		// 	}
		// 	else{
		// 		buff[bytes_received] = '\0';
		// 		printf("%s\n",buff);
		// 		fprintf(rm, "%s",buff);
		// 	}
	
		// }
		// while(bytes_received != 0);



		// bytes_received = recv(client_sock,buff,100,0);
		// if(bytes_received == -1){
		// 	printf("\nError!Cannot receive data from sever!\n");
		// 	close(client_sock);
		// 	exit(-1);
		// }
	// while((strcmp(buff,"Q") != 0) && (strcmp(buff,"Q")) != 0);

	printf("\nTotal bytes you sent to server:%d bytes\n",bytes_total);

	close(client_sock);
	return 0;
}