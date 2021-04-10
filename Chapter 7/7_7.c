#include<stdio.h>
#include<string.h>
#define LINEMAX 100
char *pattern(char *s, char *w) {
    char *p;
    for(;*s;s++) {
        for(p=w;*p&&(*p==*(s+(p-w)));p++)
            ;
        if(*p=='\0')
            return s;
    }
    return NULL;
}
int main(int argc, char *argv[]) {
    char line[LINEMAX];
    char word[LINEMAX];
    FILE *p;
    if(argc==2) {
        p=stdin;
        strcpy(word,argv[1]);
    } else if(argc>2) {
        p=fopen(argv[1],"r");
        strcpy(word,argv[2]);
    } else {
        printf("INSUFFICIENT ARGUMENTS\n");
        return 1;
    }
    while(fgets(line,LINEMAX,p)!=NULL)
        if(pattern(line,word)!=NULL)
            fputs(line,stdout);
    fclose(p);
}