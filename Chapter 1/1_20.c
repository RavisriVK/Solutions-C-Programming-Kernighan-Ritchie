#include<stdio.h>
#define n 8
/*To bring to positions that are integral multiples of n*/
int main()
{
    int position=1;
    int nblanks;
    int c=getchar();
    while(c!=EOF)
    {
        if(c=='\n')
        position=0;
        if(c!='\t')
        putchar(c);
        else {
            nblanks=n-((position-1)%n);
            position=position+nblanks-1;
            for(int i=0;i<nblanks;i++)
            putchar(' ');
        } 
        c=getchar();
        position++;
    }
    return 0;
}
/* 123456789
   he  ij in */