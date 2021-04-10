#include<stdio.h>
#include<ctype.h>
#define BUFMAX 100
#define MAXLINE 100
char buf[BUFMAX];
int bufp=0;

char *Getline() {
    static char line[MAXLINE]="";
    char *lp=line;
    while((lp-line)<(MAXLINE-1) && (*(lp++)=getchar())!='\n')
        ;
    *lp=0;
    return line;
}

int Atoi(char *s) {
    int sign;
    int value=0;
    while(*s==' '||*s=='\t')
        s++;
    sign=(*s=='-')?-1:1;
    if(*s=='-'||*s=='+')
        s++;
    while(isdigit(*s))
        value=value*10+(*s++-'0');
    return sign*value;
}

void Reverse(char *s, int n) {
    char temp;
    for(int i=0; i<n/2; i++) {
        temp=*(s+i);
        *(s+i)=*(s+n-1-i);
        *(s+n-1-i)=temp;
    }
}

void Itoa(char *s, int n) {
    int sign=1;
    int dig=0;
    if(n<0) {
        n=-n;
        sign=-1;
        dig++;
    }
    while(n>0) {
        *s=n%10+'0';
        n/=10;
        dig++;
        s++;
    }
    if(sign==-1)
    *s++='-';
    *s='\0';
    Reverse(s-dig,dig);
}

int Strindex(char *s, char *t) {
    char *beginning=s;
    int i;
    while(*s!='\0') {
        for(i=0;(*(t+i)!='\0')&&(*(s+i)==*(t+i)); i++)
            ;
        if(*(t+i)=='\0')
            return s-beginning;
        s++;
    }
    return -1;
}

int getch() {
    if(bufp>0)
    return buf[--bufp];
    else
    return getchar();
}

void ungetch(int c) {
    if(bufp<BUFMAX)
    buf[bufp++]=c;
    else
    printf("ERROR:BUFFER FULL\n");
}

int Getop(char *s) {
    do {
        *s=getch();
    } while(*s==' '||*s=='\t');
    if(*s=='-') {
        s++;
        *s=getch();
        if(!isdigit(*s)) {
            ungetch(*s);
            *s--='\0';
            return *s;
        }
    } else if(!isdigit(*s)) {
        *(s+1)='\0';
        return *s; 
    }
    while(isdigit(*s)) {
        s++;
        *s=getch();
    }
    if(*s=='.') {
        *(++s)=getch();
        while(isdigit(*s)) {
            s++;
            *s=getch();
        }
    }
    ungetch(*s);
    *s='\0';
    return '0';
}
int main() {
    char s[100];
    while(1) {
        Getop(s);
        printf("%s\n",s);
    }
}