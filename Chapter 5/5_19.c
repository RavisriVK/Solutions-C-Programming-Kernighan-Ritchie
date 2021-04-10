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

int gettoken(void);

int main() {
    int type, ptype;
    char temp[MAXTOKEN];
    while((ptype=gettoken())!=EOF) {
        strcpy(out,token);
        while((type=gettoken())!='\n') {
            if(type==PARENTHESES||type==BRACKETS) {
                strcat(out,token);
            } else if(type=='*') {
                if(ptype!='*') {
                    sprintf(temp,"(*%s)",out);
                    strcpy(out,temp);
                } else {
                    sprintf(temp,"(*%s",out+1);
                    strcpy(out,temp);
                }
            } else if(type==NAME) {
                if(ptype!=PARENTHESES&&ptype!=BRACKETS&&out[0]=='(') {
                    sprintf(temp,"%s",out+1);
                    temp[strlen(temp)-1]='\0';
                    strcpy(out,temp);
                }
                sprintf(temp,"%s %s",token,out);
                strcpy(out,temp);
            } else {
                printf("ERROR\n");
            }
            ptype=type;
        }
        printf("%s\n",out);
    }
}

int gettoken() {
    int c;
    char *p=token;
    while((c=getch())==' '||c=='\t')
        ;
    if(c=='(') {
        if((c=getch())==')') {
            strcpy(token,"()");
            return tokentype=PARENTHESES;
        } else {
            ungetch(c);
            return tokentype='(';
        }
    } else if(c=='[') {
        *p++='[';
        while((c=getch())!=']') {
            *p++=c;
        }
        *p++=']';
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