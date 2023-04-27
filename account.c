#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct account {
    char id[20]; 
    char password[20];
};
struct account account[2];

int main(){
   char name[20];
   char password[20];
   int answer=0;
   int answer1=0;
   int flag=0;
   char const* const filename="read_name.txt";
   FILE *fp=fopen(filename,"r");
   if(fp == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   int p=0;
   //printf("\nhello");
     while(fscanf(fp,"%s%s", account[p].id, account[p].password)!=EOF)
      {
       p++;
      }
 
  /* for(int i=0;i<p;i++)
    {
     printf("\n%s\t%s\t",account[i].id,account[i].password);
    }*/
  //  printf("Enter user id and password\n");
   scanf("%s", name);
   scanf("%s", password);

    answer = strcmp(name, account[0].id);
    answer1 = strcmp(password, account[0].password);
   if(answer==0 && answer1==0)
    {
      flag=1;
    }
    else{
      flag=0;
    }
   printf("%d\n", flag);
   return 0;
  }