#include<stdio.h>
#include<string.h>
#define MAXLINES 100
#define ALLOCSIZE 1000
#define MAXLENGTH 100

int Getline(char*);
int Readlines(char *lines[], int maxlines, char allocbuf[]);
void Writelines(char *lines[],int nlines);
void Sortlines(char *lines[], int nlines);

int main() {
    char *lines[MAXLINES];
    char allocbuf[ALLOCSIZE];
    int nlines=Readlines(lines,MAXLINES,allocbuf);
    printf("NO.:%d\n",nlines);
    Sortlines(lines,nlines);
    Writelines(lines,nlines);
    return 0;
}

int Readlines(char *lines[], int maxlines, char *allocbuf) {
    char *allocp=allocbuf;
    int nlines=0;
    int length;
    char s[MAXLENGTH];
    do {
        length=Getline(s);
        *lines=allocp;
        allocp+=(length+1);
        strcpy(*lines,s);
        lines++;
        nlines++;
    } while(*(lines-1)>0 && length>0 && nlines<maxlines);
    return nlines-1;
}

void Writelines(char *lines[], int nlines) {
    for(int i=0; i<nlines; i++) {
        printf("%s\n",*(lines+i));
    }
}

void Sortlines(char *lines[], int nlines) {
    char *temp;
    for(int i=0; i<(nlines-1); i++) {
        for(int j=0; j<(nlines-1-i); j++) {
            if(strcmp(lines[j],lines[j+1])<0) {
                temp=lines[j+1];
                lines[j+1]=lines[j];
                lines[j]=temp;
            }
        }
    }
}

int Getline(char *s) {
    int i;
    for(i=0; (*(s+i)=getchar())!='\n' && i<(MAXLENGTH-1); i++) ;
    *(s+i)='\0';
    return i;
}
