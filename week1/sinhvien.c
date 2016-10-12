#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//////////////////////
/// Note 3 chuc nang chay duoc nhung van bi core dump
typedef struct sinhvien{
  char mssv[10];
  char hodem[30];
  char ten[15];
  float giuaki;
  float cuoiki;
  char kq[2];
} elementtype;
#include "lllib.h"
typedef struct chitietmonhoc{
  char maMonhoc[10];
  char monHoc[30];
  int hesoGiuaki,hesoCuoiki;
  char kiHoc[10];
  int soLuongSV;
}chitietmonhoc;
char maMonhoc[10];
char monHoc[30];
char kiHoc[10];
int soLuongSV=0;
char nameFile[40];
elementtype e;
char yesOrNo;
FILE *fp;
////////////////////////
void addNew();
void del(){
  while(getchar() != '\n');
}
///////////////////////////
void menu(){
    printf("---------------------------***************-----------------\n");
    printf("\t------------- Student Programming-------\n");
    printf("\t1.\tAdd a new score board\n");
    printf("\t2.\tAdd score\n");
    printf("\t3.\tRemove score\n");
    printf("\t4.\tSearch score\n");
    printf("\t5.\tDisplay score board and score report\n");
    printf("\tYour choice(1-6,other to quit):");
 }

void menu2(){

  printf("\tBan co muon thuc hien tiep tuc chuc nang nay?(Y/N):");
  del();
  scanf("%[^\n]",&yesOrNo);
  while(yesOrNo != 'Y' && yesOrNo != 'N' && yesOrNo != 'y' && yesOrNo != 'n'){
    printf("\tLua chon cua ban sai!.Vui long nhap lai:");
    del();
    scanf("%[^\n]",&yesOrNo);
  }
}

void readFile(char* file){
  char buff[255];
  if ((fp=fopen(file,"r"))==NULL){
       printf("Error! opening file on Function readFile");
       exit(1); 
   }

  char *Name,*subjectID,*subject,*f3,*f7,*semester,*studentCount;

  fgets(buff,100, fp);
  subjectID = strtok(buff,"|");
  subjectID = strtok(NULL,"|");
  fgets(buff,100, fp);
  subject = strtok(buff,"|");
  subject = strtok(NULL,"|");
  fgets(buff,100,fp);
  Name = strtok(buff,"|");
  f3 = strtok(NULL,"|");
  f7 = strtok(NULL,"|");
  fgets(buff,100, fp);
  semester = strtok(buff,"|");
  semester = strtok(NULL,"|");
  fgets(buff,100, fp);
  studentCount = strtok(buff,"|");
  studentCount = strtok(NULL,"|");

  int count = atoi(studentCount);
  soLuongSV = count;
  for (int i = 0; i < count; ++i)
  {
    fgets(buff,200,fp);
    Name = strtok(buff,"|");
    Name = strtok(NULL,"|");
    strcpy(e.mssv,Name);
    Name = strtok(NULL,"|");
    strcpy(e.hodem,Name);    
    Name = strtok(NULL,"|");
    strcpy(e.ten,Name);
    Name = strtok(NULL,"|");
    e.giuaki = atoi(Name);
    Name = strtok(NULL,"|");
    e.cuoiki = atoi(Name);
    Name = strtok(NULL,"|");
    strcpy(e.kq,Name);
    insertaffter(e);
  }
  fclose(fp);
  printf("Read  from file congalucation!\n");
}

void wirteFIle(char* file){
  fp=fopen(nameFile,"w"); 
      fprintf(fp, "SubjectID|%s\n",maMonhoc);
      fprintf(fp, "Subject|%s\n",monHoc);
      fprintf(fp, "F|30|70\n");
      fprintf(fp, "Semester|%s\n",kiHoc);
      fprintf(fp, "studentCount|%d\n",soLuongSV);
      cur = root;
    while(cur != NULL){
      fprintf(fp, "S|%s|%s|%s|%2.1f|%2.1f|%s|\n",cur->element.mssv,cur->element.hodem,cur->element.ten,cur->element.giuaki,cur->element.cuoiki,cur->element.kq);
      cur = cur->next;
    }
    fclose(fp);
}

char xeploai[4];
char* scoreFinal(float giuaki,float cuoiki){
  float kq;
  kq = (giuaki*0.3 + cuoiki*.7);
  if((giuaki < 3) || (cuoiki < 3) || (kq < 4)){
    strcpy(xeploai,"F");
  }
  else{
    if(4 <= kq && kq < 5.5){
      strcpy(xeploai,"D");
    }
    else
      if(kq < 6.5){
        strcpy(xeploai,"C");
      }
      else
      if(kq < 8 ){
        strcpy(xeploai,"B");
      }
      else{
        strcpy(xeploai,"A");
      }
  }
  return (char *)xeploai;
}

/// DOc file tu thang add New
void addNew(){
  int countSV;
  printf("\t\t-----Add New--------\n");
  strcpy(nameFile,"");
  strcpy(maMonhoc,"");
  strcpy(kiHoc,"");
  printf("Nhap ma mon hoc:");
  del();
  scanf("%[^\n]",maMonhoc);

  printf("Nhap ten mon hoc:");
  del();
  scanf("%[^\n]",monHoc);

  printf("Nhap ma hoc ki:");
  del();
  scanf("%[^\n]",kiHoc);

  printf("Nhap so luong SV:");
  scanf("%d",&countSV);
  soLuongSV = countSV;
  // ghep ten file
  strcpy(nameFile,maMonhoc);
  strcat(nameFile,"_");
  strcat(nameFile,kiHoc);
  strcat(nameFile,".txt");

  elementtype e;
  char *kqTinh;
  fp=fopen(nameFile,"w"); // ghi tiep vao cuoi neu chua co thi ghi vao phan cuoi cua file
    // Chi ghi minh thich thi minh ghi thoi
    fprintf(fp, "SubjectID|%s\n",maMonhoc);
    fprintf(fp, "Subject|%s\n",monHoc);
    fprintf(fp, "F|30|70\n");
    fprintf(fp, "Semester|%s\n",kiHoc);
    fprintf(fp, "studentCount|%d\n",soLuongSV);
  for (int i = 0; i <soLuongSV; ++i){
    printf("-----------------------\n");
    printf("Nhap ma so sinh Vien:");
    del();
    scanf("%[^\n]",e.mssv);
    printf("Nhap Ho ten dem:");
    del();
    scanf("%[^\n]",e.hodem);
    printf("Nhap Ten sinh  vien:");
    del();
    scanf("%[^\n]",e.ten);
    printf("Nhap diem giua ki:");
    scanf("%f",&e.giuaki);
    while(e.giuaki <0 || e.giuaki >10){
      printf("Nhap diem sai:");
      del();
      scanf("%f",&e.giuaki);
    }
    printf("Nhap diem cuoi ki:");
    scanf("%f",&e.cuoiki);
    while(e.cuoiki <0 || e.cuoiki >10){
      printf("Nhap diem sai:");
      del();
      scanf("%f",&e.cuoiki);
    }
    kqTinh = scoreFinal(e.giuaki,e.cuoiki);
    strcpy(e.kq,kqTinh);
    fprintf(fp, "S|%s|%s|%s|%2.1f|%2.1f|%s|\n",e.mssv,e.hodem,e.ten,e.giuaki,e.cuoiki,e.kq);
  }
    
    fclose(fp);
}


void addScore(){
  printf("\t\t-----Add Score------\n"); 
  strcpy(nameFile,"");
  strcpy(maMonhoc,"");
  strcpy(kiHoc,"");
  printf("%s\n",nameFile);
  printf("Nhap ma mon hoc:");
  del();
  scanf("%[^\n]",maMonhoc);
  printf("Nhap ma hoc ki:");
  del();
  scanf("%[^\n]",kiHoc);
  strcpy(nameFile,maMonhoc);
  strcat(nameFile,"_");
  strcat(nameFile,kiHoc);
  strcat(nameFile,".txt");
  if((fp=fopen(nameFile,"r")) == NULL){
    printf("Error Open file on Fuction Add Score\n");
  }else{
    readFile(nameFile);
    printf("-------- NEW STUDENT----------\n");
    printf("Nhap ma so sinh Vien:");
    del();
    scanf("%[^\n]",e.mssv);
    printf("Nhap Ho ten dem:");
    del();
    scanf("%[^\n]",e.hodem);
    printf("Nhap Ten sinh  vien:");
    del();
    scanf("%[^\n]",e.ten);
    printf("Nhap diem giua ki:");
    scanf("%f",&e.giuaki);
    while(e.giuaki <0 || e.giuaki >10){
      printf("Nhap diem sai:");
      del();
      scanf("%f",&e.giuaki);
    }
    printf("Nhap diem cuoi ki:");
    scanf("%f",&e.cuoiki);
    while(e.cuoiki <0 || e.cuoiki >10){
      printf("Nhap diem sai:");
      del();
      scanf("%f",&e.cuoiki);
    }
    char *kqTinh;
    kqTinh = scoreFinal(e.giuaki,e.cuoiki);
    strcpy(e.kq,kqTinh);
    soLuongSV = soLuongSV+1;
    wirteFIle(nameFile);
  }
}

void removeScore(){
  printf("\t\t-----Remove Score----\n"); 
    do{  
        strcpy(nameFile,"");
        strcpy(maMonhoc,"");
        strcpy(kiHoc,"");
        printf("Nhap ma mon hoc:");
        del();
        scanf("%[^\n]",maMonhoc);
        printf("Nhap ma hoc ki:");
        del();
        scanf("%[^\n]",kiHoc);
        strcpy(nameFile,maMonhoc);
        strcat(nameFile,"_");
        strcat(nameFile,kiHoc);
        strcat(nameFile,".txt");
        fp=fopen(nameFile,"r");
        if(fp == NULL){
          printf("Error Open file on function Remove Score\n");
          menu2();

        }
    }
    while (fp == NULL  && yesOrNo != 'N' && yesOrNo != 'n');

  if(fp != NULL){
      readFile(nameFile);
      char maSoSinhVien[10];
      printf("Nhap ma so sinh vien Xoa:");
      del();
      scanf("%[^\n]",maSoSinhVien);

      cur = root;
      while(cur != NULL){
        if(strcmp(maSoSinhVien,cur->element.mssv) == 0){
          printf("Da sao sinh vien mssv:%s\n",cur->element.mssv);
          deletecur();
          soLuongSV = soLuongSV-1;
        }
        cur = cur->next;
      };
    wirteFIle(nameFile);
  }
}


void searchScore(){
  printf("\t\t------Search Information OF Student----\n");
  printf("Nhap ma mon hoc:");
  del();
  scanf("%[^\n]",maMonhoc);
  printf("Nhap ma hoc ki:");
  del();
  scanf("%[^\n]",kiHoc);
  strcpy(nameFile,strcat(maMonhoc,"_"));
  strcpy(nameFile,strcat(nameFile,kiHoc));
  strcat(nameFile,".txt");
  fp=fopen(nameFile,"r");
  if(fp == NULL){
    printf("Error Open file on function Remove Score\n");
    menu2();
  }
  else{
      char soMASV[10];
      readFile(nameFile);
      printf("Nhap ma so sinh vien:");
      del();
      scanf("%[^\n]",soMASV);
      cur = root;
      while(cur != NULL){
        if(strcmp(soMASV,cur->element.mssv) ==0){
          printf("--------------------\n");
          printf("\tXin chao: %s%s!\n",cur->element.hodem,cur->element.ten);
          printf("\nDiem cua ban la: Giua ky= %.1f %.1f \nXep loai: %s \n",cur->element.giuaki,cur->element.cuoiki,cur->element.kq);
        }
        cur = cur->next;
      }
  }
}
float traLai(float a,float b){
  return(a*0.3+ b*0.7);
}
void disPlay(){
  char nameSave[40];
  printf("\t\t------DisPlay--------\n");
    printf("Nhap ma mon hoc:");
    del();
    scanf("%[^\n]",maMonhoc);
    printf("Nhap ma hoc ki:");
    del();
    scanf("%[^\n]",kiHoc);
    strcpy(nameFile,strcat(maMonhoc,"_"));
    strcpy(nameFile,strcat(nameFile,kiHoc));
    strcpy(nameSave,nameFile);
    strcat(nameFile,".txt");
    strcat(nameSave,"_rp_txt");
    fp=fopen(nameFile,"r");
    if(fp == NULL){
      printf("Error Open file on function Remove Score\n");
      menu2();
    }
    else{
      readFile(nameFile);
      float hightScore= 0;
      float lowScore = 0;
      float temp;
      char nameHight[40];
      char nameLow[40];
      int scoreA=0,scoreB=0,scoreC=0,scoreD=0;
      float tongScore=0;
      cur = root;
      lowScore =  traLai(cur->element.giuaki,cur->element.cuoiki);
      hightScore = traLai(cur->element.giuaki,cur->element.cuoiki);
      while(cur != NULL){
        temp = traLai(cur->element.giuaki,cur->element.cuoiki);
        tongScore = tongScore + temp;
        if(temp < lowScore){
          lowScore = temp;
        }
        if(temp>hightScore){
          hightScore = temp;
        }
        if(strcmp(cur->element.kq,"A") == 0){
            scoreA = scoreA+1;
        }
        if(strcmp(cur->element.kq,"B") == 0){
            scoreB = scoreB+1;
        }
        if(strcmp(cur->element.kq,"C") == 0){
            scoreC = scoreC+1;
        }
        if(strcmp(cur->element.kq,"D") == 0){
            scoreD = scoreD+1;
        }
        cur = cur->next;
      }

      printf("The student with the lowest mark is:%0.1f\n", lowScore);
      printf("The student with the highest mark is:%0.1f\n",hightScore);
      printf("The average mark is:%0.1f\n", tongScore/soLuongSV);
      printf("A histogram of the subject %s is:\n",monHoc);
      printf("A:");
      for (int i = 0; i < scoreA; ++i)
      {
        printf("*");
      }
      printf("\nB:");
      for (int i = 0; i < scoreB; ++i)
      {
        printf("*");
      }
      printf("\nC:");
      for (int i = 0; i < scoreC; ++i)
      {
        printf("*");
      }
      printf("\nD:");
      for (int i = 0; i < scoreD; ++i)
      {
        printf("*");
      }
      printf("\n");
      printf("%s\n",nameSave);
      fp = fopen(nameSave,"w");

      fprintf(fp,"The student with the lowest mark is:%0.1f\n", lowScore);
      fprintf(fp,"The student with the highest mark is:%0.1f\n",hightScore);
      fprintf(fp,"The average mark is:%0.1f\n", tongScore/soLuongSV);
      fprintf(fp,"A histogram of the subject %s is:\n",monHoc);
      fprintf(fp,"A:");
      for (int i = 0; i < scoreA; ++i)
      {
        fprintf(fp,"*");
      }
      fprintf(fp,"\nB:");
      for (int i = 0; i < scoreB; ++i)
      {
        fprintf(fp,"*");
      }
      fprintf(fp,"\nC:");
      for (int i = 0; i < scoreC; ++i)
      {
        fprintf(fp,"*");
      }
      fprintf(fp,"\nD:");
      for (int i = 0; i < scoreD; ++i)
      {
        fprintf(fp,"*");
      }
      fprintf(fp,"\n");
      fclose(fp);
    }

}

void main(){
  int choose;
  char choose2;
  do{
      menu();
      scanf("%d",&choose);
      while(choose != 1 && choose != 2 && choose != 3 && choose !=4 && choose != 5 && choose != 6){
        printf("Lua chon cua ban sai!.Nhap lai:");
        del();
        scanf("%d",&choose);
      }
      switch(choose){
      case 1:
          do{
            addNew();
            menu2();
          }
          while(yesOrNo != 'N' && yesOrNo != 'n');
          break;
      case 2:
          do{
            addScore();
            menu2();
          }
          while(yesOrNo != 'N' &&  yesOrNo != 'n');
          break;
      case 3:
          do{
            removeScore();
            menu2();
          }
          while(yesOrNo != 'N' && yesOrNo != 'n');
          break;
      case 4:
          do{
              searchScore();
              menu2(); 
          }
          while(yesOrNo != 'N' && yesOrNo != 'n');
          break;
      case 5:
          do{
              disPlay();
              menu2();
          }while(yesOrNo != 'N' && yesOrNo != 'n');
          break;
    }
  }
  while(choose != 6);
}
