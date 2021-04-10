#include<stdio.h>
#define LINELENGTH 30
#define PAGESIZE 10
int main(int argc, char *argv[]) {
    FILE *p;
    int position;
    int line=1;
    int page=1;
    int c;
    while(--argc>0) {
        p=fopen(argv[argc],"r");
        printf("\nPAGE NUMBER %d\n",page++);
        position=1;
        line=1;
        while((c=fgetc(p))!=EOF) {
            if(position>=LINELENGTH) {
                putchar('\n');
                position=1;
                line++;
            } else if(c=='\n') {
                position=1;
                line++;
            }
            if(line>PAGESIZE) {
                line=1;
                printf("\nPAGE NUMBER %d\n",page++);
            }
            putchar(c);
            position++;
        } 
        for(int i=0; i<PAGESIZE-line+1; i++)
            printf("\n");
        fclose(p);
    }
}