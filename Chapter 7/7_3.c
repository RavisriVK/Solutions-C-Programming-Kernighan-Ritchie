#include<stdio.h>
#include<stdarg.h>
void minprintf(char *fmt, ...) {
    va_list ap;
    char *p;
    int ival;
    double dval;
    char *sval;
    va_start(ap, fmt);
    for(p=fmt;*p;p++) {
        if(*p!='%') {
            putchar(*p);
            continue;
        }
        switch(*++p) {
            case 'd':
                ival=va_arg(ap,int);
                printf("%d",ival);
                break;
            case 'c':
                ival=va_arg(ap,int);
                putchar(ival);
                break;
            case 'f':
                dval=va_arg(ap,double);
                printf("%f",dval);
                break;
            case 's':
                sval=va_arg(ap,char *);
                for(;*sval;sval++)
                    putchar(*sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}
int main() {
    minprintf("%d % %f %s\n",123,23.23,"hello");
}