#include<stdio.h>
int main()
{
    int c=(getchar()!=EOF);
    while(c) 
    {
        printf("%d",c);
        c=(getchar()!=EOF);
    }
    printf("%d",c);
}
/*Press ctrl+D twice*/