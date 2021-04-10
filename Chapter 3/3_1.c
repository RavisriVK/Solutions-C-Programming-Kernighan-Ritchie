#include<stdio.h>
#define n 1000000
/*binsearch: find x in v[O] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[]) {
    int lower=0, higher=n-1, mid;
    while(lower<=higher) {
        mid=(lower+higher)/2;
        if(x==v[mid])
        return mid;
        else if(x>v[mid])
        lower=mid+1;
        else
        higher=mid-1;
    }
    return -1;
}
int binsearchMOD(int x, int v[]) {
    int lower=0, higher=n-1, mid;
    while(lower<higher) {
        mid=(lower+higher)/2;
        if(x>v[mid]) {
            lower=mid+1;
        } else {
            higher=mid;
        }
    }
    if(x==v[lower]) {
        return lower;
    }
    return -1;
}
int main() {
    int v[n];
    for(int i=0; i<n; i++)
    v[i]=i;
    int x=8989;
    printf("1==>%d\n",binsearch(x,v));
    printf("2==>%d\n",binsearchMOD(x,v));
}