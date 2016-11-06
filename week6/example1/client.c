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
    

    unsigned long fsize;
    FILE *rm;
    char filename[100];
    do{
        printf("\nInsert name file sent.('Q' or 'q' to Quit):");
        memset(filename,'\0',(strlen(filename)+1));
        gets(filename); 
        rm = fopen(filename, "r+");
        if(rm != NULL){
            printf("Found file %s\n", filename);
            fseek(rm, 0, SEEK_END);
            fsize = ftell(rm);
            rewind(rm);
            printf("File contains %ld bytes!\n", fsize);
            if(fsize < 2000000){ 
                printf("Number bytes  of File < 2MB Not Sent!\n");
            }
            else{
                printf("Sending the file now");
                while(!feof(rm)){
                    memset(buff,'\0',(strlen(buff)+1));
                    int nread = fread(buff,100, 1,rm);
                    if(nread >= 0){
                        bytes_sent = send(client_sock, buff, strlen(buff), 0);
                        if(bytes_sent == -1){
                            printf("\nError!Cannot send data to sever!\n");
                            close(client_sock); 
                        }
                    }
                } 
                printf("\nYou  sent Server");

                rewind(rm);
                 // received to server
                fclose(rm);
                FILE *fp;
                strtok(filename,".");
                strcat(filename,"_converse.txt");
                 
                fp = fopen(filename,"w");
                if(fp != NULL){
                    do{
                        memset(buff,'\0',(strlen(buff)+1));
                        bytes_received = recv(client_sock,buff,100,0); //blocking
                        if (bytes_received < 0){
                            printf("\nError!Can not receive data from client!");
                            close(client_sock);
                        }
                        else{
                            fputs(buff,fp);
                            memset(buff,'\0',(strlen(buff)+1));
                            bytes_total = bytes_total+ bytes_received;
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
            if((strcmp(filename,"Q") == 0) || (strcmp(filename,"q") == 0)){
                bytes_sent = send(client_sock,"Q", strlen("Q"), 0);

            }
        }
    }while((strcmp(filename,"Q") != 0) && (strcmp(filename,"q") != 0));
    printf("\nTotal bytes you sent to server:%d bytes\n",bytes_total);
    close(client_sock);
    return 0;
}
