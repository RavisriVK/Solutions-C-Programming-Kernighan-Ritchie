#include<stdio.h>
unsigned setbits(unsigned x, int p, int n, unsigned y) {
    return  ((~((~(~0<<n))<<(p+1-n)))&x)|((y<<(p+1-n))&(~(~0<<(p+1))));
}
int main() {
    unsigned x=175;
    unsigned y=250;
    int p=3;
    int n=4;
    printf("%u\n",setbits(x,p,n,y));
}