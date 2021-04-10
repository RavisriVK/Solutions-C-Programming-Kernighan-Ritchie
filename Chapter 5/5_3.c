#include<stdio.h>
void strcat(char *s, char *t) {
    while(*s++)
    ;
    s--;
    while(*s++=*t++)
    ;
}
int main() {
    char s[100]="RAVISRI";
    char t[100]="123";
    strcat(s,t+1);
    printf("%s\n",s);
}