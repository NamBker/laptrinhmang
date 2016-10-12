#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int gethostname(char *name,size_t len);

struct hostent *gethostbyname(const char *hostname);



void menu(){
  printf("********************************\n");
  printf("\tProgram IP\n");
  printf("\t1.Xem tên miền chính\n");
  printf("\t2.Địa chỉ IP\n");
  printf("\t3.Tên miền phụ\n");
  printf("\t4.Các địa chỉ IP phụ\n");
  printf("\t5.Thoát\n");
  printf("********************************\n");
}

void del(){
  while(getchar() != '\n');
}


void main(){
  int choose;

  do{
    printf(" Nhap IP/nameM\n");
    menu();
    printf("Nhap lua chon cua ban?:");
    scanf("%d",&choose);
    while(choose != 1 && choose != 2 && choose != 3 && choose != 4 && choose != 5){
      printf("Lua chon cua ban sai! \nVui long nhap lai:");
      del();
      scanf("%d",&choose);
    };
    switch(choose){
      case 1:
      break;
      case 2:
      break;
      case 3:
      break;
      case 4:
      break;
    }
  }while(choose != 5);
}
