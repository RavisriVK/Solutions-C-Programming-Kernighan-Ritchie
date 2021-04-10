#include<stdio.h>
#define n 8
int main()
{
    int c=getchar();
    char ws[100];
    int position=1;
    int blankstart=0;
    int tabs=0;
    int spaces=0;
    while(c!=EOF)
    {
        if(c=='\n') {
            position=0;
        } else if(c==' ') {
            blankstart++;
        } else if(c=='\t') {
            blankstart+=(n-((position-1)%n));
            position+=(n-((position-1)%n))-1;
        } else if(blankstart!=0) {
            if(position/n==(position-blankstart)/n)
            spaces=blankstart;
            else
            spaces=(position-1)%n;
            tabs=(blankstart-spaces)%n==0 ? ((blankstart-spaces)/n) : (((blankstart-spaces)/n)+1) ;
            for(int i=0; i<tabs; i++)
            putchar('\t');
            for(int i=0; i<spaces; i++)
            putchar(' ');
            putchar(c);
            blankstart=0;
        } else {
            putchar(c);
        }
        c=getchar();
        position++;
    }
    return 0;
}
/* 12345678901234567890
   hei     ji ijih h    */