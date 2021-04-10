#include<stdio.h>
int strlen(char s[]) {
    int i;
    for(i=0;s[i]!='\0';i++)
    ;
    return i;
}
int strrindex(char s[], char t[]) {
    int i,j;
    for(i=strlen(s)-strlen(t);i>=0;i--) {
        for(j=0; t[j]!='\0'&&s[i+j]==t[j]; j++)
        ;
        if(t[j]=='\0')
        return i;
    }
    return -1;
}
int main() {
    char s[]="hello world!";
    char t[]="wor";
    printf("%d\n",strrindex(s,t));
}