#include<stdio.h>
char charset[]="0123456789abcdefghijklmnopqrstuvwxyz";
void reverse(char s[], int length) {
    for(int i=0; i<length/2; i++) {
        s[i]=s[i]+s[length-1-i];
        s[length-i-1]=s[i]-s[length-1-i];
        s[i]=s[i]-s[length-i-1];
    }
}
void itob(int n, char s[], int b) {
    int i=0, sign;
    if(n<0) {
        n=-n;
        sign=-1;
    }
    do {
        s[i++]=charset[n%b];
        n/=b;
    } while(n>0);
    if(sign==-1)
    s[i++]='-';
    s[i]='\0';
    reverse(s,i);
}
int main() {
    int n=-123456789;
    int b=16;
    char s[100];
    itob(n,s,b);
    printf("%s\n",s);
}