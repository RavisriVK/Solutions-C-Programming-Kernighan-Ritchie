#include<stdio.h>
#include<limits.h>
void reverse(char s[], int length) {
    for(int i=0; i<length/2; i++) {
        s[i]=s[i]+s[length-1-i];
        s[length-i-1]=s[i]-s[length-1-i];
        s[i]=s[i]-s[length-i-1];
    }
}
int itoa(int n, char s[], int w) {
    int length=0;
    int returnvalue;
    int sign;
    if(n<0) {
        sign=-1;
        n=-n;
    }
    do {
        s[length++]=n%10+'0';
    } while(n/=10);
    if(sign==-1)
    s[length++]='-';
    returnvalue=length;
    for(int i=0; i<(w-returnvalue); i++)
    s[length++]=' ';
    reverse(s,length);
    s[length]='\0';
    return returnvalue;
}
int main() {
    int n=41342523;
    char s[100];
    printf("%s\n",itoa(n,s,15),s);
}