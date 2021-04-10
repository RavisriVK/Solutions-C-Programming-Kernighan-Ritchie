#include<stdio.h>
#include<string.h>
void reverse(char s[], int length) {
    if(length>=2) {
        reverse(s,length-1);
        char temp=s[length-1];
        for(int i=length-2; i>=0; i--)
        s[i+1]=s[i];
        s[0]=temp;
    }
}
int main() {
    char s[]="RAVISRI";
    reverse(s,7);
    printf("%s\n",s);
}