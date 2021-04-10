#include<stdio.h>
#include<string.h>
int mod(int n) {
    return n<0?(-1)*n:n;
}
void itoa(int n, char s[]) {
    if((n/10)==0) {
        if(n>=0) {
            s[0]=n+'0';
            s[1]='\0';
        } else {
            s[0]='-';
            s[1]=(-1*n)+'0';
            s[2]='\0';
        }
    } else {
        itoa(n/10,s);
        int ln=strlen(s);
        s[ln]=(mod(n)%10)+'0';
        s[ln+1]='\0';
    }
}
int main() {
    int n=-1243;
    char s[100];
    itoa(n,s);
    printf("%s\n",s);
}