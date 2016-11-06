#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>


typedef struct User{
	char name[40];
	char password[40];
}elementtype;

#include "lllib.h"
elementtype e;
elementtype user;
bool searcUser(char *name){
	int memory = 0;
	cur = root;
	while(cur != NULL){
		if(strcmp(name,cur->element.name) == 0){
			printf("Ok\n");
			strcpy(user.name,cur->element.name);
			strcpy(user.password,cur->element.password);
			memory = 1;
		}
		cur = cur->next;
	}
	if(memory == 0){
		return false;
	}
	if(memory == 1){
		return true;
	}	
}
bool checkPassword(char * pass){
	int memory = 0;
	if(strcmp(pass,user.password) == 0){
		return true;
	}
	return false;
}
int main(){
	FILE * fp;
	fp = fopen("test.txt","r+");
	elementtype SESSION;
	char name[40] = "nguyenvannam" ;
	char password[40] = "123456";
	printf("Read db\n");
	for(int i=0; i<3; i++){
		fscanf(fp,"%s %s",e.name,e.password);
		printf("%s:",e.name );
		printf("%s\n",e.password );
		insertaffter(e);
	}
	int choose;
	strcpy(SESSION.name,"");
	do{
		if(strcmp(SESSION.name,"") == 0){
			printf("\n1.lOGIN\n2.EXIT\nChoose:");
			scanf("%d",&choose);
			if(choose == 1){
				if(searcUser(name) == 1){
						printf("Have user\n");
						
						if(checkPassword(password) == 1){
							printf("Password ok");
							strcpy(SESSION.name,user.name);
						}
						else{
							printf("Erorr\n");
						}
					}
					else{
						printf("false\n");
					}
			}
		}
		else{
			printf("\n1.LOGOUT\n2.EXIT\nChoose:");
			scanf("%d",&choose);
			strcpy(SESSION.name,"");
		}
	}while(choose != 2);
	

}