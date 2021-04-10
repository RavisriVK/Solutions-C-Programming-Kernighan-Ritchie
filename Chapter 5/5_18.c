#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define BUFMAX 100
#define MAXOUT 1000

char buf[BUFMAX];
char bufp;

int getch();
void ungetch(int c);

#define MAXTOKEN 100

enum {NAME, PARENTHESES, BRACKETS};

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[MAXOUT];

int inError;

int gettoken(void);
void dcl(void);
void dirdcl(void);

int main() {
    while(gettoken()!=EOF) {
        strcpy(datatype,token);
        out[0]='\0';
        dcl();
        if(inError==0) {
            printf("%s: %s %s\n",name,out,datatype);
        } else {
            printf("ERROR: NOT A VALID DECLARATION\n");
            inError=0;
        }
    }
}

void dcl() {
    int ns;
    for(ns=0;gettoken()=='*';ns++) //stops at the token just after the last *
        ;
    dirdcl();
    while(ns-->0)
        strcat(out," pointer to");
}

void dirdcl() {
    int type;
    //no need to get a token just yet, as gettoken has left off at the start of a direct declaration
    if(tokentype==NAME) {
        strcpy(name,token);
    } else if(tokentype=='(') {
        dcl();
        //after dcl, gettoken should stop at a closing ')'
        if(tokentype!=')') {
            printf("ERROR: MISSING CLOSING PARENTHESIS\n");
            inError=1;
            return;
        }
    } else {
        printf("ERROR: EXPECTED A NAME OR (dcl)\n");
        inError=1;
        return;
    }

    while((type=gettoken())==PARENTHESES||type==BRACKETS) {
        if(type==PARENTHESES) {
            strcat(out," function returning");
        } else {
            strcat(out," array[");
            strcat(out,token);
            strcat(out,"] of");
        }
    }
}

int gettoken() {
    int c;
    char *p=token;
    while((c=getch())==' '||c=='\t')
        ;
    if(c=='(') {
        if((c=getch())==')') {
            return tokentype=PARENTHESES;
        } else {
            ungetch(c);
            return tokentype='(';
        }
    } else if(c=='[') {
        while((c=getch())!=']') {
            *p++=c;
        }
        *p='\0';
        return tokentype=BRACKETS;
    } else if(isalnum(c)) {
        for(*p++=c;isalnum((c=getch()));)
            *p++=c;
        *p='\0';
        ungetch(c);
        return tokentype=NAME;
    } else {
        return tokentype=c;
    }
}

int getch() {
    return bufp==0?getchar():buf[--bufp];
}

void ungetch(int c) {
    if(bufp<BUFMAX) {
        buf[bufp++]=c;
    } else {
        printf("ERROR: BUFFER FULL\n");
    }
}