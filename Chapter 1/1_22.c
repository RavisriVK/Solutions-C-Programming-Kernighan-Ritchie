#include<stdio.h>
#define n 20
#define llim 100
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
int fold(char s[], int start, int length) 
{
    int nonblankbegin=0;
    int newstart=0;
    if((length-start)<=n) {
        for(int i=start; i<length; i++) 
        {
            if(s[i]!=' '&&s[i]!='\t')
            nonblankbegin=1;
            if(nonblankbegin==1)
            putchar(s[i]);
        }
        putchar('\n');
        return -1;
    } else {
            for(int i=start+n-1;i>=start;i--)
            {
                if(s[i]==' '||s[i]=='\t')
                {
                    newstart=i+1;
                    break;
                }
            }
            if(newstart==0)
            newstart=start+n;
            
            for(int i=start ;i<newstart; i++)
            {
                if(s[i]!=' '&&s[i]!='\t')
                nonblankbegin=1;
                if(nonblankbegin==1)
                putchar(s[i]);
            }
            putchar('\n');    
            return newstart;
    }
}



int main()
{
    char line[llim];
    int length=getLine(line, llim);
    int start=0;
    while(length>0)
    {
        start=fold(line, start, length-1);
        while(start>=0) {
            start=fold(line, start, length-1);
        }
        length=getLine(line, llim);
        start=0;
    }
}