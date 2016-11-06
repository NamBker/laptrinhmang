#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <errno.h>

int main(){
  int kt;
  char string[50], **p;

  struct in_addr someAddr,addr,ipv4addr;
  struct hostent *he;
  struct in_addr **addr_list;

  printf("Input the IP adress: ");
  scanf("%s",string);

  //check xem la hostname hay la IP
  kt = inet_aton(string,&someAddr);
  if(kt == 0){
    he = gethostbyname(string);
  }
  else{
    inet_pton(AF_INET,string, &ipv4addr);
    he = gethostbyaddr(&ipv4addr,sizeof(ipv4addr),AF_INET);
  }

  // Ten mien
  if(he == NULL){
    herror("Get host!:");
    return 1;
  }
  printf("Host name: %s\n",he->h_name);

  //Ten mien phu
  for(p = he->h_aliases; *p != NULL; p++){
    printf("Aliases: %s\n",*p);
  }
 
  //In ra ip address va Ip phu
  addr_list = (struct in_addr **)he->h_addr_list;
  int i;
  for(i=0;addr_list[i] != NULL; i++){
    printf("IP address: %s\n",inet_ntoa(*addr_list[i]));
  }
  printf("\n");
  return 0;
}



