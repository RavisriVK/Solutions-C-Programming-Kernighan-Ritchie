#include<stdio.h>
int main()
{
    int previous=getchar();
    if(previous!=EOF)
    putchar(previous);
    int current=getchar();
    while(current!=EOF)
    {
        if(!(previous==' '&&current==' '))
        putchar(current);
        previous=current;
        current=getchar();
    }
}