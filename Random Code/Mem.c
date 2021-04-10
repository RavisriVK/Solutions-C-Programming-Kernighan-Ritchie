#include<stdio.h>
#define ALLOCSIZE 1000

char allocbuf[ALLOCSIZE];
char *allocp=allocbuf;

char *alloc(int n) {
    if(ALLOCSIZE+allocbuf-allocp>=n) {
        allocp+=n;
        return allocp-n;
    } else {
        return 0;
    }
}

void afree(char *p) {
    if(p>=allocbuf&&p<allocbuf+ALLOCSIZE)
    allocp=p;
}

int main() {
    char *p;
    p=alloc(10);
    for(int i=0; i<9; i++) {
        *(p+i)=getchar();
    }
    *(p+9)='\0';
    printf("%s",p+1);
    afree(p);
}