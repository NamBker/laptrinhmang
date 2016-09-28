#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
int main(){
	FILE *rm;
	rm = fopen(filename, "r");
	while(rm == NULL){
		printf("File not found\n");
		printf("Insert name file sent again:");
		memset(buff,'\0',(strlen(buff)+1));
		gets(filename);
		if((strcmp(filename,"Q") == 0) || (strcmp(filename,"q")) == 0){
			break;
		}	
		rm = fopen(filename, "r");
	}

	if(rm != NULL){
		while(fgets(buff,100,rm) != NULL){
			printf("%s",buff );	
			if(bytes_sent == -1){
				printf("\nError!Cannot send data to sever!\n");
				close(client_sock);
			}
			buff[bytes_sent] = '\0';
		}
	// bytes_sent = send(client_sock,"ket thuc tai day",strlen("ket thuc tai day")+1,0);
	}
}