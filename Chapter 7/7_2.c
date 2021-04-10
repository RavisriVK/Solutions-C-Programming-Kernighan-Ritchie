#include<stdio.h>
#include<ctype.h>
#include<string.h>
void strrev(char *s,int n);
int hexd(int n);
int main() {
    int c;
    int n=0;
    while((c=getchar())!=EOF) {
        if(isgraph(c)) {
            putchar(c);
            n++;
        } else {
            n+=hexd(c);
        } if(n>=25||c=='\n') {
            putchar('\n');
            n=0;
        }
    }
}
void strrev(char *s, int n) {
    char temp;
    for(int i=0; i<n/2; i++) {
        temp=s[i];
        s[i]=s[n-1-i];
        s[n-1-i]=temp;
    }
}
int hexd(int n) {
    char s[100];
    char *p=s;
    do {
        if(n%16>=0&&n%16<10) {
            *p='0'+n%16;
        } else {
            *p='A'+(n%16-10);
        }
        p++;
        n/=16;
    } while(n>0);
    *p='\0';
    strrev(s,p-s);
    printf("<0x%s>",s);
    return 4+strlen(s);
}