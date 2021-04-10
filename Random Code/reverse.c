#include<stdio.h>
void reverse(char s[], int length) {
    for(int i=0; i<length/2; i++) {
        s[i]=s[i]+s[length-1-i];
        s[length-i-1]=s[i]-s[length-1-i];
        s[i]=s[i]-s[length-i-1];
    }
}
int main() {
    char s[]="ravisri";
    reverse(s,7);
    printf("%s\n",s);
}