#include <stdio.h>          /* These are the usual header files */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 5550  /* Port that will be opened */ 

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
 
	int server_sock; /* file descriptors */
	char recv_data[100],buff[100];
	int bytes_sent, bytes_received;
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */
	int sin_size;
	unsigned long bytes_total = 0;

	if ((server_sock=socket(AF_INET, SOCK_DGRAM, 0)) == -1 ){  /* calls socket() */
		printf("socket() error\n");
		exit(-1);
	}

	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
	server.sin_addr.s_addr = INADDR_ANY;  /* INADDR_ANY puts your IP address automatically */   
	bzero(&(server.sin_zero),8); /* zero the rest of the structure */

  
	if(bind(server_sock,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1){ /* calls bind() */
		printf("bind() error\n");
		exit(-1);
	}     
	FILE *fp;
	int nread;
	fp = fopen("server.txt", "w");
	fclose(fp);


	while(1){
		fp = fopen("server.txt", "r+");
		do{
			memset(recv_data,'\0',(strlen(recv_data)+1));
			sin_size=sizeof(struct sockaddr_in);
			bytes_received = recvfrom(server_sock,recv_data,100,0, (struct sockaddr *) &client, &sin_size);
			
			bytes_total = bytes_total+ bytes_received;
			String_Upper(recv_data);
			fputs(recv_data,fp);
			recv_data[bytes_received] = '\0';

			// Sent file to client
			if(bytes_received <100 && bytes_received > 0){
				rewind(fp);
				printf("End receive from client\n");
				printf("Sendding the file to Client...\n");
				while(!feof(fp)){
    				memset(buff,'\0',(strlen(buff)+1));
					nread = fread(buff,100, 1,fp);
				  	printf("%s\n",buff);
				  	if(nread >=0){
				  		sin_size=sizeof(client);
						bytes_sent = sendto(server_sock,buff,strlen(buff),0,(struct sockaddr *) &client, sin_size ); /* send to the client welcome message */
						if (bytes_sent < 0){
							printf("\nError!Can not sent data to client!");
							break;
						}	
				  	}else{
				  		printf("Eror read file on Server\n");
				  		break;
				  	}
				}
				printf("End sent to Client\n");
				fclose(fp);
				fp = fopen("server.txt","w");
				fclose(fp); 
				fp = fopen("server.txt", "r+");
				
			}
			if(bytes_received < 0){
				printf("Error !Can not receive data from client\n");
				break;
			}

		}
		while(bytes_received >0);
	}
	fclose(fp);

	close(server_sock);
	return 0;
}


		
	