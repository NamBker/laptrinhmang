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

#define PORT 5550   /* Port that will be opened */ 
#define BACKLOG 2   /* Number of allowed connections */

<<<<<<< HEAD
=======



>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1
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
 
<<<<<<< HEAD
=======

>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1
  int listen_sock, conn_sock; /* file descriptors */
  char recv_data[100];
  int bytes_sent, bytes_received;
  struct sockaddr_in server; /* server's address information */
  struct sockaddr_in client; /* client's address information */

  int sin_size;
<<<<<<< HEAD

=======
  size_t  size;
>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1

  fd_set active_fd_set, read_fd_set;
  int i;

<<<<<<< HEAD

=======
>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1
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

<<<<<<< HEAD
    FILE *fp;
  fp = fopen("server.txt","w");
  fclose(fp);
=======
  FILE *fp;
  char filename[200];
>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1

  FD_ZERO(&active_fd_set);
  FD_SET(listen_sock,&active_fd_set);

  while(1){
    read_fd_set = active_fd_set;
<<<<<<< HEAD
    if(select(FD_SETSIZE,&read_fd_set,NULL,NULL,NULL) <0){
=======
      if(select(FD_SETSIZE,&read_fd_set,NULL,NULL,NULL) <0){
>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1
      perror("Select");
      exit(EXIT_FAILURE);
    }


    for(i=0; i< FD_SETSIZE; ++i){
      if(FD_ISSET(i,&read_fd_set)){
        if(i == listen_sock){
          int new;
<<<<<<< HEAD
          sin_size =sizeof(client);
          new = accept(listen_sock,(struct sockaddr *)&client,&sin_size);
          if( new < 0){
            perror("Accept");
            exit(EXIT_FAILURE);

          }

          fprintf (stderr,"Server: connect from host %s, port %hd.\n",inet_ntoa (client.sin_addr),
                         ntohs (client.sin_port));

          bytes_sent = send(new,"Welcome to my server.\n",22,0); /* send to the client welcome message */
=======
          size =sizeof(client);
          new = accept(listen_sock,(struct sockaddr *)&client,&size); /* calls accept() */
          if(new < 0){         
            printf("accept() error\n");
            exit(EXIT_FAILURE);
          }
          printf("%s\n",i );

          fprintf (stderr,"Server: connect from host %s, port %hd.\n",inet_ntoa (client.sin_addr),
                               ntohs (client.sin_port));  
          bytes_sent = send(new,"Welcome to my server.\n",22,0); /* send to the client welcome message */
          
>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1
          if (bytes_sent < 0){
            printf("\nError!Can not sent data to client!");
            close(new);
            continue;
          }
<<<<<<< HEAD

          FD_SET(new,&active_fd_set);
        }
        else{         
              fp = fopen("server.txt","r+");
           do{
              memset(recv_data,'\0',(strlen(recv_data)+1));
              bytes_received = recv(i,recv_data,100,0); //blocking
              printf("server_recv:%s\n",recv_data );

              if (bytes_received < 0){
                printf("\nError!Can not receive data from client!");
                  close(i);
                  FD_CLR(i,&active_fd_set);
              }
             
            } while( bytes_received > 0 && bytes_received < 100);
        }


      }
    }

  }
}
=======
            memset(filename,'\0',(strlen(filename)+1));
            strcat(filename,"server_");
            int port;
            port = ntohs (client.sin_port);
            char post[15];
            sprintf(post,"%d",port);
            strcat(filename,post);
            strcat(filename,".txt");
            fp = fopen(filename,"w");
            fclose(fp);

          FD_SET(new,&active_fd_set);
        }
        else{
            fp = fopen(filename,"r+");
            do{
              memset(recv_data,'\0',(strlen(recv_data)+1));
              bytes_received = recv(i,recv_data,100,0); //blocking
              if (bytes_received < 0){
                printf("\nError!Can not receive data from client!");
                fclose(fp);
                close(i);
                FD_CLR(i,&active_fd_set);
              }
              else{
                    String_Upper(recv_data);
                    fputs(recv_data,fp);
                    if(strcmp(recv_data,"q") == 0 || strcmp(recv_data,"Q") == 0){
                        printf("End one process!!!\n");
                        fclose(fp);
                        close(i);
                        FD_CLR(i,&active_fd_set);
                    }
                    memset(recv_data,'\0',(strlen(recv_data)+1));
                    if(bytes_received >0 && bytes_received < 100){
                        // sent file to client
                          rewind(fp);
                          printf("Sending the file now");
                          while(!feof(fp)){
                            memset(recv_data,'\0',(strlen(recv_data)+1));
                            int nread = fread(recv_data,100, 1,fp);
                            printf("%d\n",nread);
                            if(nread > 0){
                                bytes_sent = send(i, recv_data, strlen(recv_data), 0);
                                if(bytes_sent == -1){
                                  printf("\nError!Cannot send data to sever!\n");
                                  fclose(fp);
                                  close(i);
                                  FD_CLR(i,&active_fd_set);
                                }
                            }
                            if(nread == 0){
                               bytes_sent = send(i, recv_data, strlen(recv_data), 0);
                                if(bytes_sent == -1){
                                  printf("\nError!Cannot send data to sever!\n");
                                }
                                fclose(fp);
                                close(i);
                                FD_CLR(i,&active_fd_set);
                            }
                          }
                    }
                }
            } while(bytes_received >0);



        }

      }
    }
  }
}
>>>>>>> 41436eed61b64842ecf01950f3418be2ed5aaec1
