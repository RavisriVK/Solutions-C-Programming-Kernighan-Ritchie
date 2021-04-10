#include<stdio.h>
void strncpy(char *s, char *t, int n) {
    int i;
    for(i=0; (i<n) && (*s++=*t++) ; i++)
        ;
    while(i<n) {
        *s++=0;
        i++;
    }
}
void strncat(char *s, char *t, int n) {
    while(*s++) ;
    s--;
    for(int i=0; (i<n) && (*s++=*t++); i++) ;
}
int strncmp(char *s, char *t, int n) {
    for(int i=0;(i<n)&&(*s==*t);i++,s++,t++)
        if(*s=='\0'||i==n-1)
            return 0;
    return *s-*t;
}
int main() {
    char a[100]="HELLO WORLD";
    char *t="HELLO WORLD!";
    char *s=a;
    int n=12;
    //*(s+n)='\0';
    printf("%d\n",strncmp(s,t,n));
}