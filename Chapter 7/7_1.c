#include<stdio.h>
#include<ctype.h>
int main(int argc, char *argv[]) {
    int (*con)(int);
    con=argv[1][0]=='0'?tolower:toupper;
    char *s=argv[2];
    while(*s!='\0') {
        *s=con(*s);
        s++;
    }
    printf("%s\n",argv[2]);
}