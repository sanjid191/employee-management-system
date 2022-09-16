#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
int main()
{
   FILE *fp , *ft;
   char another, choice;

   struct emp {
        char name[30];
        int age;
        float bs;
   };

   struct emp e;
   char empname[30];
   long int recsize ;

   fp = fopen("EMP.DAT","rb+");
    if(fp == NULL){
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL){
            printf("Con not open file");
            exit(1);
        }
    }

    recsize = sizeof(e);

    while(1){

       system("cls");
       printf("1. Add Record \n");
       printf("2. List Records \n");
       printf("3. Modify Records \n");
       printf("4. Delete Records \n");
       printf("5. Exit \n");
       printf("Your Choice: ");
       fflush(stdin);
       choice  = getche();



     switch(choice){

         case '1':
             system("cls");
             fseek(fp,0,SEEK_END);

             another = 'y';
             while(another == 'y') {
                printf("\nEnter name: ");
                //s` canf("%s",e.name);
                gets (e.name);
                printf("\nEnter age: ");
                scanf("%d", &e.age);
                printf("\nEnter basic salary: ");
                scanf("%f", &e.bs);

                fwrite(&e,recsize,1,fp);

                printf("\nAdd another record(y/n) ");
                fflush(stdin);
                another = getche();
             }
             break;


          case '2':
             system("cls");
             rewind(fp);
             while(fread(&e,recsize,1,fp)==1) {
                 printf("\n-----\n  Employees Name : %s \n  Age: %d \n  Salary: %.2f \n-----",e.name,e.age,e.bs);
             }
             getch();
             break;


          case '3':
             system("cls");
             another = 'y';
             while(another == 'y'){
                printf("Enter the employee name to modify: ");
                scanf("%s", empname);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1) {
                    if(strcmp(e.name,empname) == 0){
                        printf("\nEnter new name: ");
                        scanf("%s",e.name);
                        printf("\nEnter new age: ");
                        scanf("%d",&e.age);
                        printf("\nEnter new basic salary: ");
                        scanf("%f",&e.bs);
                        fseek(fp,-recsize,SEEK_CUR);
                        fwrite(&e,recsize,1,fp);
                        break;
                    }
                }
                printf("\nModify another record(y/n)");
                fflush(stdin);
                another = getche();
             }
             break;

          case '4':
             system("cls");
             another = 'y';
             while(another == 'y'){
                printf("\nEnter name of employee to delete: ");
                scanf("%s",empname);
                ft = fopen("Temp.dat","wb");
                rewind(fp);
                while(fread(&e,recsize,1,fp) == 1){
                    if(strcmp(e.name,empname) != 0){
                        fwrite(&e,recsize,1,ft);
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT");
                rename("Temp.dat","EMP.DAT");
                fp = fopen("EMP.DAT", "rb+");
                printf("Delete another record(y/n)");
                fflush(stdin);
                another = getche();
             }
             break;

          case '5':
               fclose(fp); 
               exit(0); 
        }
    }
    return 0;
}

