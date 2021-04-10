#include<stdio.h>
int main()
{
    int charlist[128]={0};
    int c=getchar();
    while(c!=EOF)
    {
        for(int i=0;i<128;i++)
        {
            if(i==c)
            charlist[i]++;
        }
        c=getchar();
    }
    for(int i=0; i<128; i++)
    {
        if(charlist[i]!=0)
        {
            printf("%c:\t",(char)i);
            for(int j=0; j<charlist[i];j++)
            printf("=");
            printf("\n");
        }
    }
}