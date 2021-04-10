#include<stdio.h>
#include<stdarg.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
void getdouble(char *s) {
    char *b=s;
    int c;
    while(isgraph(c=getchar())==0)
        ;
    for( ; isnumber(*s++=c); c=getchar())
        ;
    if(*(s-1)=='.') 
        while(isnumber(*s++=(c=getchar())))
            ;
    ungetc(*--s,stdin);
    *s='\0';
    printf("<%s>\n",b);
}
void getint(char *s) {
    char *b=s;
    int c;
    while(isgraph(c=getchar())==0)
        ;
    for( ; isnumber(*s++=c); c=getchar())
        ;
    ungetc(*--s,stdin);
    *s='\0';
    printf("<%s>\n",b);
}
void getword(char *s) {
    char *b=s;
    int c;
    while(isgraph(c=getchar())==0)
        ;
    for( ; isgraph(*s++=c); c=getchar())
        ;
    ungetc(*--s,stdin);
    *s='\0';
    printf("<%s>\n",b);
}
void minscanf(char *fmt, ...) {
    va_list ap;
    char w[100];
    char c;
    char *p;
    int *ival;
    char *cval;
    double *dval;
    char *sval;
    va_start(ap,fmt);
    for(p=fmt;*p;p++) {
        if(*p=='%') {
            switch(*++p) {
                case 'd':
                    ival=va_arg(ap,int*);
                    getint(w);
                    *ival=atoi(w);
                    break;
                case 'f':
                    dval=va_arg(ap,double*);
                    getdouble(w);
                    *dval=atof(w);
                    break;
                case 'c':
                    cval=va_arg(ap,char*);
                    while(isgraph(*cval=getchar())==0)
                        ;
                    break;
                case 's':
                    sval=va_arg(ap,char*);
                    getword(w);
                    strcpy(sval,w);
                    break;
            }
        } else if(isgraph(*p)!=0) {
            getchar();
        } else if(isgraph(*p)==0) {
            while(isgraph(c=getchar())==0)
                ;
            ungetc(c,stdin);
        }
    }
    va_end(ap);
}

int main() {
    int n;
    char c;
    char s[100];
    double d;
    minscanf("%d hello %chello %s %f",&n,&c,s,&d);
    printf("%d %c %s %f",n,c,s,d);
}