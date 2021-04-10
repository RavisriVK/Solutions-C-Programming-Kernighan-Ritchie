#include<stdio.h>
#include<string.h>
#define LINEMAX 100
int main(int argc, char *argv[]) {
    char line1[LINEMAX];
    char line2[LINEMAX];
    char *e1,*e2;
    FILE *p1=fopen(argv[1],"r");
    FILE *p2=fopen(argv[2],"r");
    e1=fgets(line1,LINEMAX,p1);
    e2=fgets(line2,LINEMAX,p2);
    while(  e1!=NULL  &&  e2!=NULL )   {
        if(strcmp(line1,line2)!=0) {
            printf("FILE 1==>%s",line1);
            printf("FILE 2==>%s\n",line2);
        }
        e1=fgets(line1,LINEMAX,p1);
        e2=fgets(line2,LINEMAX,p2);
    }
    if(e1==NULL&&e2!=NULL)
        printf("FILE 1 is shorter than FILE 2.\n\n");
    else if(e2==NULL&&e1!=NULL)
        printf("FILE 2 is shorter than FILE 1.\n\n");
    fclose(p1);
    fclose(p2);
}