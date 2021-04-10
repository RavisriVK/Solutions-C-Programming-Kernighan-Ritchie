#include<stdio.h>
#define LINELIMIT 100
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
void copy(char to[], char from[])
{
    int i;
    for(i=0;from[i]!='\0';i++)
    {
        to[i]=from[i];
    }
    to[i]='\0';
}
int main()
{
    int length=0;
    char line[LINELIMIT];
    /*int maxlength=0;
    char longestline[LINELIMIT];*/
    while( (length=getLine(line,LINELIMIT)) >0)
    {
        /*if(length>maxlength)
        {
            maxlength=length;
            copy(longestline,line);
        }*/
        //printf("\n%d==>%s\n",length,line);
        if(length>80)
        printf("%s\n",line);
    }
    //printf("\n%d==>%s\n",maxlength,longestline);
    return 0;
}