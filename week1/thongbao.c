#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
void nhapma();
void phanloai();
char chose;
char HAZCHEM[10];
 int lOng;
char kitudau[4][50] = {"Jets","Fog","Foam","Dry agent"};

//--------------------
char show;
void reactivity(){
    printf("Reactivity:   Can be violently reactive\n");
}
void protection_Full(){
    printf("Protection:   Full body protective clothing and masks\n");
}
void protection_BA(){
    printf("Protection:   Breathing apparatus, protective gloves\n");
    
}
void protection_BA_Fire(){
    printf("Protection:   Breathing apparatus, protective gloves for fire only\n");
}
void containment_Dilute(){
    printf("Containment:  May be diluted and washed down the drain\n");
}
void containment_Contain(){
    printf("Containments: Chemicals should be stored in containers. \n\t\t Not for exposure Other chemicals and water.\n");
}
void evacuation(){
    printf("Evacuation:   Consider evacuation.\n!");
}
///////////////////////////////////////////////////////
void phanloai(){
  int H1;
  char H2,H3;
  if(lOng == 2){
    H1 = (int)HAZCHEM[0]-48;
    H2 = HAZCHEM[1];
  }
  if(lOng == 3 ){
      H1 = (int)HAZCHEM[0]-48;
      H2 = HAZCHEM[1];
      H3 = HAZCHEM[2];
  }
  printf("***Emergency action advice***\n");
  printf("Material: \t%s\n",kitudau[H1]);
  switch(H2){
  case 'P':
    reactivity();
    protection_Full();
    containment_Dilute();
    break;
  case 'R':
    protection_Full();
    containment_Dilute();
    break;
  case 'S':
    reactivity();
    if(lOng == 3){
      protection_BA_Fire();  
      containment_Dilute();
      evacuation();
    }
    else{
      protection_BA();
      containment_Dilute();
    }
    break;
  case 'T':
    if(lOng == 3){
      protection_BA_Fire();
      containment_Dilute();
      evacuation();
    }
    else{
      protection_BA();
      containment_Dilute();
    }
    break;
  case 'W':
    reactivity();
    protection_Full();
    containment_Contain();
    break;
  case 'X':
    protection_Full();
    containment_Contain();
    break;
  case 'Y':
    reactivity();
    if(lOng == 3){
      protection_BA_Fire();
      containment_Contain();
      evacuation();
    }
    else{
      protection_BA();
      containment_Contain();  
    }
    break;
  case 'Z':
    reactivity();
    if(lOng == 3){
      protection_BA_Fire();
      containment_Contain();
      evacuation();
    }
    else{
      protection_BA();
      containment_Contain();
    }
    break;
  }
  printf("-------------------------------\n");

}
void del(){
  while(getchar() != '\n');
}

void nhapma(){
     printf("Enter HAZCHEM code:");
     scanf("%[^\n]",HAZCHEM);
     lOng = strlen(HAZCHEM);
     while(lOng>3 || lOng <2 || (HAZCHEM[0] != '1' && HAZCHEM[0] != '2' && HAZCHEM[0] != '3' && HAZCHEM[0] != '4')|| (lOng == 3 && HAZCHEM[2] != 'E') ||(HAZCHEM[1]< 'P' || HAZCHEM[1] > 'Z') || (HAZCHEM[1] != 'S' && HAZCHEM[1] != 'T' && HAZCHEM[1] != 'Y' && HAZCHEM[1] != 'Z')){
       while(lOng>3){
         printf("Ma ban nhap qua dai:");
         printf("\nNhap lai:");
         del();
         scanf("%[^\n]",HAZCHEM);
         lOng = strlen(HAZCHEM);
       }
       while(lOng<2){
         printf("Ma ban nhap qua ngan:");
         printf("\nNhap lai:");
         del();
         scanf("%[^\n]",HAZCHEM);
         lOng = strlen(HAZCHEM);
       }
       while(HAZCHEM[0] != '1' && HAZCHEM[0] != '2' && HAZCHEM[0] != '3' && HAZCHEM[0] != '4'){
         printf("Ki tu dau tien cua ban sai:");
         del();
         scanf("%[^\n]",HAZCHEM);
         lOng = strlen(HAZCHEM);
       }
       while(HAZCHEM[1]< 'P' || HAZCHEM[1] > 'Z' ){
         printf("Ma thu 2 cua ban sai:");
         del();
         scanf("%[^\n]",HAZCHEM);
         lOng = strlen(HAZCHEM);
       }
       while(lOng == 3 && HAZCHEM[2] != 'E' ){
           printf("Ma thu 3 cua ban sai:");
           del();
           scanf("%[^\n]",HAZCHEM);
           lOng =strlen(HAZCHEM);
       }
       while(HAZCHEM[1] != 'S' && HAZCHEM[1] != 'T' && HAZCHEM[1] != 'Y' && HAZCHEM[1] != 'Z'){
          printf("Khi co 3 ki tu.Ma thu 2 chi:(S,T,Y,Z):");
          printf("\nNhap lai:");
          del();
          scanf("%[^\n]",HAZCHEM);
          lOng = strlen(HAZCHEM);
        }
    }
}

void main(){
  nhapma();
  printf("Ma ban da nhap la: %s",HAZCHEM);
  printf("\n----------------------------\n");
  phanloai();
}
