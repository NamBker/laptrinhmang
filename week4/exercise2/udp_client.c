#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <string.h>

int main(){
	int client_sock;
	char buff[100],recv_data[100];
	struct sockaddr_in server_addr;
	int bytes_sent,bytes_received, sin_size;
	int bytes_total = 0;

	client_sock=socket(AF_INET,SOCK_DGRAM,0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5550);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	


	unsigned long fsize;
	FILE *rm;
	char filename[100];

	do{
		printf("\nInsert name file sent.('Q' or 'q' to Quit):");
		memset(filename,'\0',(strlen(filename)+1));
		gets(filename);	
		sin_size = sizeof(struct sockaddr);

		rm = fopen(filename, "r");
	    if(rm != NULL){
	    	printf("Found file %s\n", filename);
		    fseek(rm, 0, SEEK_END);
		    fsize = ftell(rm);
		    rewind(rm);

		    printf("File contains %ld bytes!\n", fsize);
		    if(fsize <20){
		    	printf("Number bytes  of File < 2MB Not Sent!\n");
		    }
		    else{
			    printf("Sending the file now\n");
			    while(!feof(rm)){
    				memset(buff,'\0',(strlen(buff)+1));
				  	int nread = fread(buff,100, 1,rm);
				  	if(nread >=0){
						bytes_sent = sendto(client_sock,buff,strlen(buff),0, (struct sockaddr *) &server_addr, sin_size);
						if(bytes_sent == -1){
							printf("\nError!Cannot send data to sever!\n");
							close(client_sock);	
							exit(-1);
						}							
				  	}	
				} 
				printf("You sent to sever!\n");

				 // received to server
				fclose(rm);
				FILE *fp;
				strtok(filename,".");
				strcat(filename,"_converse.txt");
				
				fp = fopen(filename,"w");
				printf("Nam file: %s\n",filename );

				do{

					memset(recv_data,'\0',(strlen(recv_data)+1));
					bytes_received = recvfrom(client_sock,recv_data,100,0, (struct sockaddr *) &server_addr, &sin_size);
					fputs(recv_data,fp);
					bytes_total = bytes_total + bytes_received;

					recv_data[bytes_received] = '\0';

					if(bytes_received < 0){
						printf("Error !Can not receive data from client\n");
						break;
					}
					if(bytes_received > 0  && bytes_received < 100){
						rewind(fp);
						printf("End Receive from Server!\n");
						break;
					}
					recv_data[bytes_received] = '\0';

				}
				while(bytes_received >0);

				// if(bytes_received == -1){
				// 	printf("\nError!Cannot receive data from sever!\n");
				// 	close(client_sock);
				// 	exit(-1);
				// }

			}
		}
		else{
			if((strcmp(filename,"Q") != 0) && (strcmp(filename,"q") != 0)){
				printf("Not file Found\n");
			}
		}
	}while((strcmp(filename,"Q") != 0) && (strcmp(filename,"q") != 0));

	printf("bytes receive server: %d\n",bytes_total );
	close(client_sock);
	return 0;
}
