# include <stdio.h> 
#include<stdlib.h>
struct student {
  int rollnum;
  char name[30];
  int age;
};

int numbers[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

struct student students[] = {
    [0].rollnum = 1,[0].name = "Test1",[0].age = 15,
    [1].rollnum = 2,[1].name = "Test2",[1].age = 16,
    [2].rollnum = 3,[2].name = "Test3",[2].age = 14,
    [3].rollnum = 4,[3].name = "Test4",[3].age = 13,
    [4].rollnum = 5,[4].name = "Test5",[4].age = 12,
}; 

int save_num_text( char *filename ) {
   FILE *fptr;
   fptr = fopen(filename,"w");
   if(fptr == NULL){
    printf("Could not open the file");   
    return -1;
   }
  for(int i=0;i<20;i++){
    fprintf(fptr,"%d ",numbers[i]);
  }
  fclose(fptr);
  return 0;
}

int read_num_text( char *filename ) {
  FILE *fptr;
  fptr = fopen(filename,"r");
  if(fptr == NULL){
    printf("Could not open the file");   
    return -1;            
  }
  for(int i=0;i<20;i++){
    int num;
    fscanf(fptr,"%d",&num);
    printf("%d ",num);
  }
  fclose(fptr);
  return 0;
}

int save_struct_text( char *filename ) {
  FILE *fptr;
  fptr = fopen(filename,"w");
  if(fptr == NULL){
    printf("Could not open the file");   
    return -1;            
  }
  for(int i=0;i<5;i++){
    fprintf(fptr,"%d %s %d ",students[i].rollnum,students[i].name,students[i].age);
  }
  fclose(fptr);
  return 0;
}

int read_struct_text( char *filename ) {
  FILE *fptr;
  fptr = fopen(filename,"r");
  if(fptr == NULL){
    printf("Could not open the file");   
    return -1;            
  }
  for(int i=0;i<5;i++){
    int rollnum,age;
    char name[30];
    fscanf(fptr,"%d %s %d",&rollnum, name, &age);
    printf("%d %s %d ",rollnum,name,age);
  }
  fclose(fptr);
  return 0;
}


int save_num_binary( char *filename ) {
  FILE *fptr;
  fptr = fopen(filename,"wb");
  if(fptr == NULL){
    printf("Could not open the file");   
    return -1;           
  }
  for(int i=0;i<20;i++){
    fwrite(&numbers[i], sizeof(int), 1, fptr);   }
  fclose(fptr);
  return 0;
}

int read_num_binary( char *filename ) {
  FILE *fptr;
  fptr = fopen(filename,"rb");
  if(fptr == NULL){
    printf("Could not open the file");   
    return -1;            
  }
  for(int i=0;i<20;i++){
    int num;
    fread(&num, sizeof(int), 1, fptr);     
    printf("%d ",num);
  }
  fclose(fptr);
  return 0;
}

int save_struct_binary( char *filename ) {
  FILE *fptr;
  fptr = fopen(filename,"wb");
  if(fptr == NULL){
    printf("Could not open the file");   
    return -1;             
  }
  for(int i=0;i<5;i++){
    fwrite(&students[i], sizeof(struct student), 1, fptr);   }
  fclose(fptr);
  return 0;
}

int read_struct_binary( char *filename ) {
  FILE *fptr;
  fptr = fopen(filename,"rb");
  if(fptr == NULL){
    printf("Could not open the file");   
    return -1;             
  }
  for(int i=0;i<5;i++){
    struct student temp;
    fread(&temp, sizeof(struct student), 1, fptr);     
    printf("%d %s %d ",temp.rollnum,temp.name,temp.age);
  }
  fclose(fptr);
  return 0;
}

