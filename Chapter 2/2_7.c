#include<stdio.h>
unsigned invert(unsigned x, int p, int n) {
    return ((~((~(~0<<n))<<(p+1-n)))&x)|(((~(~0<<n))<<(p+1-n))&(~x));
}
int main() {
    unsigned x=175;
    int p=3;
    int n=4;
    printf("%u\n",invert(x,p,n));
}