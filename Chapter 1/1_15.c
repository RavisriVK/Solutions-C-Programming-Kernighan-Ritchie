#include<stdio.h>
float convert(float fahr)
{
    return (5.0/9.0)*(fahr-32.0);
}
int main()
{
    for(int i=0;i<=300;i+=20)
    {
        printf("%-4.1d %-4.1f\n",i,convert(1.0*i));
    }
}