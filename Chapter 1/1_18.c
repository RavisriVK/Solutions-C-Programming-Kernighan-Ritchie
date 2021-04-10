#include<stdio.h>
int isWhiteSpace(char c)
{
    if(c==' '||c=='\t'||c=='\n'||c=='\0'||c==EOF)
    return 1;
    else
    return 0;
}
int modCopy(char s[])
{
    int length=0;
    int i;
    while(s[length]!='\0')
    {
        length++;
    }
    for(i=length-1;i>=0&&(isWhiteSpace(s[i])==1);--i)
    {
        s[i]='\0';
    }
    return (i+1);
}
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
int main()
{
    int length=0;
    char line[100];
    while( (length=getLine(line,100)) >0)
    {
        if(modCopy(line)>0)
        printf("%s\n",line);
    }
    return 0;
}