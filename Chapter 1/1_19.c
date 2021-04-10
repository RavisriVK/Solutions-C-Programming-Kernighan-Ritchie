#include <stdio.h>
int getLine(char s[], int lim)
{
    int c=getchar();
    int i;
    for(i=0; (i<(lim-1))&&c!=EOF&&c!='\n' ;i++)
    {
        s[i]=c;
        c=getchar();
    }
    if(c=='\n')
    {
        s[i]=c;
        ++i;
    }
    s[i]='\0';
    return i;
}
void reverse(char s[], int length)
{
    if(length>0&&s[length-1]=='\n')
    length--;
    char s1[length];
    for(int i=0; i<length; i++)
    s1[i]=s[i];
    for(int i=0; i<length; i++)
    {
        s[i]=s1[length-1-i];
    }
}
int main()
{
    char line[100];
    int length=0;
    while((length=getLine(line,100))>0)
    {
        reverse(line,length);
        printf("%s",line);
    }
    return 0;
}