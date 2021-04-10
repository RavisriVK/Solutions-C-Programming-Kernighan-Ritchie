#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAXLENGTH 100

char **readlines(int nlines);
void writelines(char *lines[], int nlines, int rev);
void bsort(void *lines[], int nlines, int (*comp)(void *, void *));
int fstrcmp(char *s1, char *s2);
void swap(void *v[], int i, int j);

//./a.out #nlines -n -r
int main(int argc, char *argv[]) {
    int nlines=atoi(argv[1]);
    int fold=0;
    int rev=0;
    if(argc>2) {
        if(strcmp("-f",argv[2])==0)
        fold=1;
        else if(strcmp("-r",argv[2])==0)
        rev=1;
        if(argc>3) {
            if(strcmp("-f",argv[3])==0)
            fold=1;
            else if(strcmp("-r",argv[3])==0)
            rev=1;
        }
    }
    printf("Fold=%d, Rev=%d\n",fold,rev);
    char **lines;
    lines=readlines(nlines);
    if(fold==1)
        bsort((void **)lines,nlines,(int (*)(void*,void*))(fstrcmp));
    else
        bsort((void **)lines,nlines,(int (*)(void*,void*))(strcmp));
    writelines(lines,nlines,rev);

}

char **readlines(int nlines) {
    char **lines;
    lines=(char **)malloc(nlines*sizeof(char*));
    char *temp;
    char l[MAXLENGTH];
    temp=l;
    int c;
    for(int i=0; i<nlines; i++) {
        temp=l;
        while((c=getchar())!='\n') {
            *temp=c;
            temp++;
        }
        *temp='\0';
        lines[i]=(char *)malloc((temp-l+1)*sizeof(char));
        strcpy(lines[i],l);
    }
    return lines;
}

void writelines(char *lines[], int nlines, int rev) {
    if(rev==0) {
        for(int i=0; i<nlines; i++) {
            printf("%s\n",lines[i]);
            free(lines[i]);
        }
    } else {
        for(int i=nlines-1; i>=0; i--) {
            printf("%s\n",lines[i]);
            free(lines[i]);
        }
    }
    free(lines);
}

int fstrcmp(char *s1, char *s2) {
    while((toupper(*s1)==toupper(*s2))) {
        s1++;
        s2++;
        if(*s1=='\0'&& *s2=='\0')
        return 0;
    }
    return toupper(*s1)-toupper(*s2);
}

void swap(void *v[], int i, int j) {
    void *temp;
    temp=v[i];
    v[i]=v[j];
    v[j]=temp;
}

void bsort(void *lines[], int nlines, int (*comp)(void *, void *)) {
    for(int i=0; i<nlines-1; i++) {
        for(int j=0; j<nlines-1-i; j++) {
            if(comp(lines[j],lines[j+1])>0) {
                swap(lines, j, j+1);
            }
        }
    }
}