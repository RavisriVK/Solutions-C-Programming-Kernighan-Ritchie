#include<stdio.h>
int main()
{
    int previous=getchar();
    putchar('\n');
    if(previous!=' '&&previous!='\t'&&previous!='\n'&&previous!=EOF)
    putchar(previous);
    int current=getchar();
    while(current!=EOF)
    {
        if((current!=' '&&current!='\t'&&current!='\n'))
        {
            if((previous==' '||previous=='\t'||previous=='\n'))
            {
                putchar('\n');
            }
            putchar(current);
        }
        previous=current;
        current=getchar();
    }
}