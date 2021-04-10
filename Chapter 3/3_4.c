#include<stdio.h>
#include<limits.h>
void reverse(char s[], int length) {
    for(int i=0; i<length/2; i++) {
        s[i]=s[i]+s[length-1-i];
        s[length-i-1]=s[i]-s[length-1-i];
        s[i]=s[i]-s[length-i-1];
    }
}
int itoa(int n, char s[]) {
    int length=0;
    int sign;
    if(n==INT_MIN) {
        s[length=itoa(n/10,s)]= (10*(n/10)) - n + '0';
        s[++length]='\0';
        return length;
    } else if(n<0) {
        sign=-1;
        n=-n;
    }
    do {
        s[length++]=n%10+'0';
    } while(n/=10);
    if(sign==-1)
    s[length++]='-';
    s[length]='\0';
    reverse(s,length);
    return length;
}
int main() {
    int n=-2147483648;
    char s[100];
    itoa(n,s);
    printf("%s\n",s);
}