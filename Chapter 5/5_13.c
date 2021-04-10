#include<stdio.h>
#include<string.h>
#define MAXLENGTH 100
int getLine(char s[], int lim)
{
    int c=getchar();
    int i;
    for(i=0;(c!='\n'&&c!=EOF)&&(i<lim-1);++i)
    {
        s[i]=c;
        c=getchar();
    }
    if(c=='\n') {
        s[i]='\n';
        ++i;
    }
    s[i]='\0';
    return i;
}

void printLines(int n, int lim, char lines[][lim]) {
    for(int i=0; i<n; i++)
    printf("%s",*(lines+i));
}

int main(int argc, char *argv[]) {
    int n=5,length;
    char temp[MAXLENGTH];
    if(argc>1 && argv[1][0]=='-' && argv[1][1]>='0' && argv[1][1]<='9')
        n=argv[1][1]-'0';
    char lines[n][MAXLENGTH];
    for(int i=0; i<n; i++) {
        if( getLine(lines[i],MAXLENGTH)==0 ) {
            printf("OUTPUT:\n");
            printLines(i,MAXLENGTH,lines);
            return 0;
        }
    }
    while( (length=getLine(temp,MAXLENGTH)) ) {
        for(int i=0; i<n-1; i++) {
            strcpy(lines[i],lines[i+1]);
        }
        strcpy(lines[n-1],temp);
    }
    printf("OUTPUT:\n");
    printLines(n,MAXLENGTH,lines);
    return 0;
}