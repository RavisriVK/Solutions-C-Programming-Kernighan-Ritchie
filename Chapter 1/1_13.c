#include<stdio.h>
int main()
{
    int wc=0;
    int previous=getchar();
    int current=getchar();
    int length[100]={0};
    if((previous!=' '&&previous!='\t'&&previous!='\n'))
    {
        wc++;
        length[0]++;
    }
    int maxlength;
    while(current!=EOF)
    {
        if((current!=' '&&current!='\t'&&current!='\n'))
        {
            if((previous==' '||previous=='\t'||previous=='\n'))
            {
                wc++;
            }
            length[wc-1]++;
        }
        previous=current;
        current=getchar();
    }
    maxlength=length[0];
    for(int i=0; i<wc; i++)
    {
        if(maxlength<length[i])
        maxlength=length[i];
    }
    printf("\n");
    for(int i=1; i<=maxlength; i++)
    {
        printf("%d:\t",i);
        for(int j=0; j<wc; j++)
        {
            if(i==length[j])
            {
                printf("=");
            }
        }
        printf("\n");
    }
}