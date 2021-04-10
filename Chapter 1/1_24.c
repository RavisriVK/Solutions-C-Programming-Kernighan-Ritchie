#include<stdio.h>
int main() {
    int bt1=0, bt2=0, br1=0, br2=0, p1=0, p2=0, sq=0, dq=0;
    int p=getchar();
    int c=getchar();
    int n=getchar();
    switch(p) {
            case '[':bt1++;break;
            case ']':bt2++;break;
            case '{':br1++;break;
            case '}':br2++;break;
            case '(':p1++;break;
            case ')':p2++;break;
            case '\"':dq++;break;
            case '\'':sq++;break;
    }
    while(n!=EOF) {
        switch(c) {
            case '[':if(!(c=='['&&n=='\''&&p=='\''))bt1++;break;
            case ']':if(!(c==']'&&n=='\''&&p=='\''))bt2++;break;
            case '{':if(!(c=='{'&&n=='\''&&p=='\''))br1++;break;
            case '}':if(!(c=='}'&&n=='\''&&p=='\''))br2++;break;
            case '(':if(!(c=='('&&n=='\''&&p=='\''))p1++;break;
            case ')':if(!(c==')'&&n=='\''&&p=='\''))p2++;break;
            case '\"':if(!(c=='\"'&&n=='\''&&p=='\\'))dq++;break;
            case '\'':if(!(c=='\''&&n=='\''&&p=='\\'))sq++;break;
        }
        if(bt2>bt1) {
            printf("Unbalanced brackets!\n");
            return 0;
        } else if(br2>br1) {
            printf("Unbalanced braces!\n");
            return 0;
        } else if(p2>p1) {
            printf("Unbalanced parentheses!\n");
            return 0;
        }
        p=c;
        c=n;
        n=getchar();
    }
    switch(c) {
            case '[':bt1++;break;
            case ']':bt2++;break;
            case '{':br1++;break;
            case '}':br2++;break;
            case '\"':dq++;break;
            case '\'':sq++;break;
    }
    if(br1!=br2) {
        printf("Unbalanced braces!\n");
        return 0;
    } else if(bt1!=bt2) {
        printf("Unbalanced brackets!\n");
        return 0;
    } else if(p1!=p2) {
        printf("Unbalanced parentheses!\n");
        return 0;
    } else if(sq%2!=0) {
        printf("Unbalanced single quotes!\n");
        return 0;
    } else if(dq%2!=0) {
        printf("Unbalanced double quotes!\n");
        return 0;
    } else {
        printf("VALID!!!\n");
        return 0;
    }

}