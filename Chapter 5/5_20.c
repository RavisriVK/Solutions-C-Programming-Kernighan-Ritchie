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
char *datatypelist[]={"char","int","float","double","long","short","void"};
char *qualifierlist[]={"const","volatile","restrict","register","static","extern","signed","unsigned"};

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[MAXOUT];

int inError;

int gettoken(void);
void dcl(void);
void dirdcl(void);

int isDataType(char *s);
int isQualifier(char *s);

int main() {
    while(gettoken()!=EOF) {
        datatype[0]='\0';
        while(isQualifier(token)) {
            strcat(datatype,token);
            strcat(datatype," ");
            gettoken();
        }
        if(isDataType(token)) {
            strcat(datatype,token);
        } else {
            inError=1;
            printf("ERROR: NO DATATYPE MENTIONED\n");
        }
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

    while((type=gettoken())==PARENTHESES||type==BRACKETS||type=='(') {
        if(type==PARENTHESES) {
            strcat(out," function returning");
        } else if(type=='(') {
            strcat(out," function with arguments of type");
            while(gettoken()!=')') {
                if(tokentype!=',') {
                    strcat(out," ");
                    strcat(out,token);
                } else {
                    strcat(out,",");
                }
            }
            strcat(out," returning");
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

int isDataType(char *s) {
    for(int i=0; i<7; i++) {
        if(strcmp(s,datatypelist[i])==0)
            return 1;
    }
    return 0;
}

int isQualifier(char *s) {
    for(int i=0; i<8; i++) {
        if(strcmp(s,qualifierlist[i])==0)
            return 1;
    }
    return 0;
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