#include<stdio.h>
void lower(char s[]) {
    for(int i=0; s[i]!='\0'; i++) {
        (s[i]>='A'&&s[i]<='Z')?s[i]+=('a'-'A'):0;
    }
}
int main() {
    char s[]="HelLO WOrld!";
    lower(s);
    printf("%s\n",s);
}