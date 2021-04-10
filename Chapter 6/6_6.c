#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

/*Related to obtaining a word*/

#define WORDMAX 100

#define BUFMAX 100

int buf[BUFMAX];
int bufp;

int getword(char *s, int lim);
int getch();
void ungetch(int c);

/*=============================*/
#define HASHSIZE 10

struct llist {
    char *identifier;
    char *reptext;
    struct llist *next;
};

struct llist *hashtable[HASHSIZE];

unsigned int hashcode(char *s);
struct llist *lookup(char *s);
struct llist *install(char *s, char *t);
char *strdupl(char *s);

int main() {
    char s[WORDMAX],df[WORDMAX];
    int c,p;
    printf("==>");
    p=getword(s,WORDMAX);
    printf("%s",s);
    while((c=getword(s,WORDMAX))!=EOF) {
        if(p=='#'&&strcmp(s,"define")==0) {
            getword(df,WORDMAX);
            getword(s,WORDMAX);
            printf("define %s %s",df,s);
            install(df,s);
        } else if(isalpha(c)&&lookup(s)!=NULL) {
            printf("%s ",lookup(s)->reptext);
        } else {
            printf("%s ",s);
            if(s[0]=='\n')
                printf("\b==>");
        }
        p=c;
    }
}

struct llist *install(char *s, char *t) {
    unsigned int hashvalue=hashcode(s);
    struct llist *p;
    if((p=lookup(s))==NULL) {
        p=hashtable[hashvalue];
        hashtable[hashvalue]=(struct llist*)malloc(sizeof(struct llist));
        hashtable[hashvalue]->identifier=strdupl(s);
        hashtable[hashvalue]->reptext=strdupl(t);
        //printf("<%s==%s>",hashtable[hashvalue]->identifier,hashtable[hashvalue]->reptext=strdupl(t));
        hashtable[hashvalue]->next=p;
    } else {
        free(p->identifier);
    }
    return hashtable[hashvalue];
}

struct llist *lookup(char *s) {
    unsigned int hashvalue=hashcode(s);
    struct llist *p=hashtable[hashvalue];
    while(p!=NULL && strcmp(p->identifier,s)!=0)
        p=hashtable[hashvalue]->next;
    return p;
}

unsigned int hashcode(char *s) {
    unsigned int hashvalue;
    for(hashvalue=0;*s!='\0';s++)
        hashvalue=*s + 31*hashvalue;
    return hashvalue%HASHSIZE;
}

char *strdupl(char *s) {
    char *p;
    p=(char *)malloc((strlen(s)+1)*sizeof(char));
    if(p!=NULL)
        strcpy(p,s);
    return p;
}

/*=============================*/

int getword(char *s, int lim) {
    char *b=s;
    int c;
    while((c=getch())==' '||c=='\t')
        ;
    *s++=c;
    if(isalpha(c)) {
        for( ; --lim>0 && isalnum(c=getch()) ; )
            *s++=c;
        ungetch(c);
    } else if(isnumber(c)) {
        for( ; --lim>0 && isnumber(c=getch()) ; )
            *s++=c;
        ungetch(c);
    }
    *s='\0';
    return *b;
}

int getch() {
    return bufp>0?buf[--bufp]:getchar();
}

void ungetch(int c) {
    if(bufp<BUFMAX) {
        buf[bufp++]=c;
    } else {
        printf("ERROR: BUFFER FULL\n");
    }
}