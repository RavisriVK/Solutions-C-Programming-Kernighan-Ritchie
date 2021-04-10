#include<stdio.h>
int isList(char a, char b) {
    if(a>='a'&&b<='z'&&a<b)
    return 1;
    else if(a>='A'&&b<='Z'&&a<b)
    return 1;
    else if(a>='0'&&b<='9'&&a<b)
    return 1;
    else 
    return 0;
}
void expand(char s1[], char s2[]) {
    int j=0,i;
    if(s1[1]!='-'||!(isList(s1[0],s1[2])))
    s2[j++]=s1[0];
    for(i=1; s1[i+1]!='\0'; i++) {
        if(s1[i]=='-' && isList(s1[i-1],s1[i+1])) {
            for(char k=s1[i-1]; k<=s1[i+1]; k++)
            s2[j++]=k;
            i++;
        } else if( !(s1[i+1]=='-'&&isList(s1[i],s1[i+2])) ) {
            s2[j++]=s1[i];
        }
    }
    if(s1[i-1]!=' '||!(isList(s1[i-2],s1[i])))
    s2[j++]=s1[i];
    s2[j]='\0';
}
int main() {
    char s1[]="1-3b-aStudents of sections A-A are automatically promoted.1-9";
    char s2[100];
    expand(s1,s2);
    printf("%s",s2);
}