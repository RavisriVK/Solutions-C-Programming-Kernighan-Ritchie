#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define WORDMAX 100
#define BUFMAX 100

int buf[BUFMAX];
int bufp;

int getword(char *s, int lim);
int getch();
void ungetch(int c);

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *p, char *w);
void treeprintf(struct tnode *p);
struct tnode *talloc();
char *strdupl(char *s);

int main() {
    char s[WORDMAX];
    int c;
    struct tnode *p;
    p=NULL;
    while((c=getword(s,WORDMAX))!=EOF) {
        if(isalpha(s[0])) {
            p=addtree(p,s);
        }
    }
    treeprintf(p);
}

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;
    if(p==NULL) {
        p=talloc();
        p->word=strdupl(w);
        p->count=1;
    } else if((cond=strcmp(w,p->word))==0) {
        p->count++;    
    } else if(cond<0) {
        p->left=addtree(p->left,w);
    } else {
        p->right=addtree(p->right,w);
    }
    return p;
}

void treeprintf(struct tnode *p) {
    if(p!=NULL) {
        treeprintf(p->left);
        printf("%s==>%d\n",p->word,p->count);
        treeprintf(p->right);
    }
    free(p);
}

struct tnode *talloc() {
    return (struct tnode *)malloc(sizeof(struct tnode));
}

char *strdupl(char *s) {
    char *p;
    p=(char *)malloc((strlen(s)+1)*sizeof(char));
    if(p!=NULL)
        strcpy(p,s);
    return p;
}

int getword(char *s, int lim) {
    int c;
    char *w=s;
    while((c=getch())==' '||c=='\t')
        ;
    if(isalpha(c)) {
        *s++=c;
        for( ;--lim>0 && isalnum((c=getch())) ; )
            *s++=c;
        ungetch(c);
        *s='\0';
        return *w;
    } else {
        *s++=c;
        *s='\0';
        return c;
    }
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