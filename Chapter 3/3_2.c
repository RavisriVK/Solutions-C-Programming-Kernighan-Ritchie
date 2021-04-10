#include<stdio.h>
void escape(char s[], char t[]) {
    int j,i;
    for(i=j=0; t[i]!='\0'; i++) {
        switch(t[i]) {
            case '\n':s[j++]='\\';s[j++]='n';break;
            case '\t':s[j++]='\\';s[j++]='t';break;
            default: s[j++]=t[i];
        }
    }
    s[j]='\0';
}
void convert(char s[], char t[]) {
    int i,j;
    for(i=j=0; t[i]!='\0'; i++) {
        switch(t[i]) {
            case '\\':
                if(t[i+1]=='t') {
                    s[j++]='\t';
                    i++;
                } else if(t[i+1]=='n') {
                    s[j++]='\n';
                    i++;
                } else {
                    s[j++]=t[i];
                } break;
            default: s[j++]=t[i];
        }
    }
    s[j]='\0';
}
int main() {
    char t[]="Eh-\nI'm tired anyway\n";
    char s[50];
    escape(s,t);
    printf("%s\n",s);
}