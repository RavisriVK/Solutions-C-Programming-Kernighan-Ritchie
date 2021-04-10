#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAXLENGTH 100

char **readlines(int nlines);
void writelines(char *lines[], int nlines, int rev);
void bsort(char *lines[], int nlines, int (*comp)(char *, char *), int fold, int dir);
int fstrcmp(char *s1, char *s2);
void swap(char *v[], int i, int j);

//./a.out #nlines -n -r
int main(int argc, char *argv[]) {
    int nlines=atoi(argv[1]);
    int fold=0;
    int rev=0;
    int dir=0;
    while(argc>2) {
        argc--;
        if(strcmp(argv[argc],"-f")==0)
            fold=1;
        else if(strcmp(argv[argc],"-r")==0)
            rev=1;
        else if(strcmp(argv[argc],"-d")==0)
            dir=1;
    }
    printf("Dir=%d, Fold=%d, Rev=%d\n",dir,fold,rev);
    char **lines;
    lines=readlines(nlines);
    bsort(lines,nlines,(int (*)(char*,char*))(strcmp),fold,dir);
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

void swap(char *v[], int i, int j) {
    char *temp;
    temp=v[i];
    v[i]=v[j];
    v[j]=temp;
}

void bsort(char *lines[], int nlines, int (*comp)(char *, char *), int fold, int dir) {
    char *t1, *t2;
    int k,l1,l2;
    for(int i=0; i<nlines-1; i++) {
        for(int j=0; j<nlines-1-i; j++) {
            t1=(char *)malloc((strlen(lines[j])+1)*sizeof(char));
            t2=(char *)malloc((strlen(lines[j+1])+1)*sizeof(char));
            if(dir==1) {
                for(k=l1=0; lines[j][k]!='\0'; k++) {
                    if(isalnum(lines[j][k])||lines[j][k]==' ') {
                        t1[l1]=toupper(lines[j][k]);
                        l1++;
                    }
                }
                t1[l1]='\0';
                for(k=l2=0; lines[j+1][k]!='\0'; k++) {
                    if(isalnum(lines[j+1][k])||lines[j+1][k]==' ') {
                        t2[l2]=toupper(lines[j+1][k]);
                        l2++;
                    }
                }
                t2[l2]='\0';
            } else {
                for(k=0; lines[j][k]!='\0'; k++) {
                    t1[k]=lines[j][k];
                }
                l1=k;
                t1[k]='\0';
                for(k=0; lines[j+1][k]!='\0'; k++) {
                    t2[k]=lines[j+1][k];
                }
                l2=k;
                t2[k]='\0';
            }
            if(fold==1) {
                for(k=0; k<l1; k++) {
                    t1[k]=toupper(t1[k]);
                }
                for(k=0; k<l2; k++) {
                    t2[k]=toupper(t2[k]);
                }
            }
            if(comp(t1,t2)>0) {
                swap(lines, j, j+1);
            }
            free(t1);
            free(t2);
        }
    }
}