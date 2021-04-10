#include<stdio.h>
int main()
{
    int blanks=0;
    int tabs=0;
    int newlines=0;
    int c=getchar();
    while(c!=EOF)
    {
        if(c==' ')
        ++blanks;
        else if(c=='\t')
        ++tabs;
        else if(c=='\n')
        ++newlines;
        c=getchar();
    }
    printf("\nBlanks=%d,Tabs=%d,New Lines=%d\n",blanks, tabs, newlines);
}