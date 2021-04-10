#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXLENGTH 100

char **readlines(int nlines);
void writelines(char *lines[], int nlines, int rev);
void bsort(void *lines[], int nlines, int (*comp)(void *, void *));
int numcmp(char *s1, char *s2);
void swap(void *v[], int i, int j);

//./a.out #nlines -n -r
int main(int argc, char *argv[]) {
    int nlines=atoi(argv[1]);
    int numeric=0;
    int rev=0;
    if(argc>2) {
        if(strcmp("-n",argv[2])==0)
        numeric=1;
        else if(strcmp("-r",argv[2])==0)
        rev=1;
        if(argc>3) {
            if(strcmp("-n",argv[3])==0)
            numeric=1;
            else if(strcmp("-r",argv[3])==0)
            rev=1;
        }
    }
    printf("Numeric=%d, Rev=%d\n",numeric,rev);
    char **lines;
    lines=readlines(nlines);
    if(numeric==1)
        bsort((void **)lines,nlines,(int (*)(void*,void*))(numcmp));
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

int numcmp(char *s1, char *s2) {
    double d1=atof(s1);
    double d2=atof(s2);
    if(d1>d2)
        return 1;
    else
        return 0;
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