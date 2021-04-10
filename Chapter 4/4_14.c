#include<stdio.h>
#define swap(t,x,y) { t temp=(x) ; (x)=(y) ; (y)=temp; }
int main() {
    int X=12;
    int Y=78;
    swap(int,X,Y);
    printf("%d %d\n",X,Y);
}