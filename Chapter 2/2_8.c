#include<stdio.h>
unsigned rightrot(unsigned x, int n) {
    return (((~(~0<<n))&x)<<(8*sizeof(unsigned)-n))|(x>>n);
}
int main() {
    unsigned x=10;
    int n=4;
    printf("%u\n",rightrot(x,n));
}