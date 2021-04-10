#include<stdio.h>
void squeeze(char s1[], char s2[]) {
    int i,j,k,flag=0;
    for(int i=j=0; s1[i]!='\0'; i++) {
        for(int k=0; s2[k]!='\0'; k++)
            if(s1[i]==s2[k])
            flag=1;
        if(flag==0)
        s1[j++]=s1[i];
        else
        flag=0;
    }
    s1[j]='\0';
}
int main() {
    char s1[]="hello world";
    char s2[]="aeiou";
    squeeze(s1,s2);
    printf("%s\n",s1);
}