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
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/time.h>


#define PORT 5550   /* Port that will be opened */ 
#define BACKLOG  2   /* Number of allowed connections */

#define TRUE             1
#define FALSE            0
#define TIMEOUT 		 3*60*1000


void String_Upper(char string[]) 
{	
  int i = 0;
 
  while (string[i] != '\0') 
  {
      if (string[i] >= 'a' && string[i] <= 'z') {
          string[i] = string[i] -  32;
      }
        i++;
  }
}

int main(){
	int listen_sock = -1 , conn_sock = -1; /* file descriptors */
    int desc_ready, end_server = FALSE;

	char recv_data[100];
	int bytes_sent, bytes_received;
	struct sockaddr_in server; /* server's address information */

    struct pollfd fds[200];
	int sin_size;
    
	int nfds = 1, current_size = 0, i, j, rc;
	int timeout;

	if ((listen_sock=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
		printf("socket() error\n");
		exit(-1);
	}

	int on = 1;	
  	rc = setsockopt(listen_sock, SOL_SOCKET,  SO_REUSEADDR,
                  (char *)&on, sizeof(on));
  	if (rc < 0){
    	perror("setsockopt() failed");
    	close(listen_sock);
    	exit(-1);
  	}
  	rc = ioctl(listen_sock, FIONBIO, (char *)&on);
  	if (rc < 0){
    	perror("ioctl() failed");
    	close(listen_sock);
    	exit(-1);
  	}
	
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);   
	server.sin_addr.s_addr = htonl(INADDR_ANY);  

	if(rc = bind(listen_sock,(struct sockaddr*)&server,sizeof(server))==-1){ 
		printf("bind() error\n");
		exit(-1);
	} 

	fds[0].fd = listen_sock;
	fds[0].events = POLLIN;
	timeout = (TIMEOUT);

	 rc = listen(listen_sock,BACKLOG);
	 if(rc < 0){
	 	perror("Listen() failed");
	 	close(listen_sock);
	 	exit(-1);
	 }

	// read data
	int sum = 0,c;

	int compress_array = FALSE;
	int close_conn;

	char str[2]=":";
	char *token;
	char name[100];
	char check[100];
	int session[100];
	for(i= 0; i < 99; i++){
		session[i] = 0;
	}
	FILE *fp;
 	char filename[200];
	
	do{
		rc = poll(fds,nfds,timeout);
		if(rc < 0){
			perror("poll() failed");
			break;
		}
		if(rc == 0){
			printf("poll() timed out.End program\n");
			break;
		}
		current_size = nfds;

		for(i=0; i< current_size; ++i){
			if(fds[i].revents == 0)
				continue;
			if(fds[i].revents != POLLIN){
				printf("Error! revents= %d\n",fds[i].revents );
				end_server = TRUE;
				break;
			}

			if (fds[i].fd == listen_sock){
				printf("***************\n");
		        printf("  Listening socket is readable\n");
		        do{
		          	conn_sock = accept(listen_sock, NULL, NULL);
		          	if (conn_sock < 0){
		            	if(errno != EWOULDBLOCK){
		              		perror("  accept() failed");
		            		end_server = TRUE;
		            	}
		            	break;
		          	}		          	
		          	printf("  New incoming connection - %d\n", conn_sock);
		          	fds[nfds].fd = conn_sock;
		          	fds[nfds].events = POLLIN;
		          	nfds++;
		        } while (conn_sock != -1);

			// dat ten cho ket noi
	          memset(filename,'\0',(strlen(filename)+1));
	          strcat(filename,"fileserver/server_");
	          int port;
	          port = nfds;
	          char post[15];
	          sprintf(post,"%d",port);
	          strcat(filename,post);
	          strcat(filename,".txt");
	          fp = fopen(filename,"w");
	          printf("File out:%s\n",filename );
	          fclose(fp);
			  fp = fopen(filename,"r+");
  		      printf("**********************\n");
  		       printf(" Server: is being recv_data from Client\n");	

		    }
		    else{
		    	close_conn = FALSE;

					memset(recv_data,'\0',(strlen(recv_data)+1));
					bytes_received = recv(fds[i].fd,recv_data,100,0); //blocking
					if (bytes_received < 0){
						printf("\nError!Can not receive data from client!");
						close_conn = TRUE;
					}

					recv_data[bytes_received] = '\0';
					if(strcmp(recv_data,"q") == 0 || strcmp(recv_data,"Q") == 0 || strcmp(recv_data,"2") == 0 || session[i] == 3){					
						printf("*************************\n");
						printf("Client (%d) terminated from host:\n",i);
                    	bytes_sent = send(fds[i].fd,"Q",strlen("Q"),0); /* send to the client welcome message */
						close_conn = TRUE;
					}
					else{
						String_Upper(recv_data);
						fputs(recv_data,fp);
						if(bytes_received >0 && bytes_received < 100){
							// sent file to client
						    rewind(fp);
						    printf("Sending the file to client\n");
						    while(!feof(fp)){
								memset(recv_data,'\0',(strlen(recv_data)+1));
							  	int nread = fread(recv_data,100, 1,fp);
							  	if(nread >= 0){
							  		bytes_sent = send(fds[i].fd, recv_data, strlen(recv_data), 0);
									if(bytes_sent == -1){
										printf("\nError!Cannot send data to sever!\n");
										fclose(fp);
										close_conn = TRUE;
										break;
									}
							  	}
							} 
						printf("End sent to Client\n");
						rewind(fp);				
						}
					}	
			    
		
				    if (close_conn){
			          close(fds[i].fd);
			          fds[i].fd = -1;
			          compress_array = TRUE;
			        }
		     }
		 }	

			if(compress_array){
				compress_array = FALSE;
				for (int k = 0; k < nfds; k++){
					if(fds[k].fd == -1){
						for (j = k; j < nfds; j++){
							fds[j].fd = fds[j+1].fd;
						}
						nfds--;
					}
				}
			}

		}while(end_server == FALSE);

	for (i = 0; i < nfds; i++){
		if(fds[i].fd >= 0)
			close(fds[i].fd);
	}
	printf("\n");
}



