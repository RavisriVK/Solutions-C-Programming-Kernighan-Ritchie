#include<stdio.h>
/*int strend(char *s, char *t) {
    int i;
    while(*s!='\0') {
        for(i=0;(*(t+i)!='\0')&&(*(s+i)==*(t+i)); i++)
            ;
        if(*(s+i)=='\0')
            return 1;
        s++;
    }
    return 0;
}*/
int strend(char *s, char *t) {
    char *r=t;
    while(*s++) ;
    while(*t++) ;
    s--;
    t--;
    while((t>r)&&(*s==*t)) {
        s--;
        t--;
    }
    if(t==r&&*t==*s)
    return 1;
    else
    return 0;
}
int main() {
    char *s="HELLORAVISRI";
    char *t="RAVISRI";
    printf("%d\n",strend(s,t));
}