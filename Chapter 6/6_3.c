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

struct oclist {
    int line;
    struct oclist *next;
};

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
    struct oclist *list;
};

struct tnode *addtree(struct tnode *p, char *w, int oc);
void treeprintf(struct tnode *p);
struct tnode *talloc();
char *strdupl(char *s);

struct oclist *listalloc();
struct oclist *addoccurence(struct oclist *p, int oc);
void printoccurrence(struct oclist *p);

int main() {
    char s[WORDMAX];
    int c, linenum=0;
    struct tnode *p;
    p=NULL;
    while((c=getword(s,WORDMAX))!=EOF) {
        if(isalpha(s[0])) {
            p=addtree(p,s,linenum);
        }
        if(c=='\n') {
            linenum++;
        }
    }
    treeprintf(p);
}

struct tnode *addtree(struct tnode *p, char *w, int oc) {
    int cond;
    if(p==NULL) {
        p=talloc();
        p->list=NULL;
        p->list=addoccurence(p->list,oc);
        p->word=strdupl(w);
        p->count=1;
    } else if((cond=strcmp(w,p->word))==0) {
        p->count++;
        p->list=addoccurence(p->list,oc);
    } else if(cond<0) {
        p->left=addtree(p->left,w, oc);
    } else {
        p->right=addtree(p->right,w, oc);
    }
    return p;
}

void treeprintf(struct tnode *p) {
    if(p!=NULL) {
        treeprintf(p->left);
        printf("%s==>%d\n",p->word,p->count);
        printoccurrence(p->list);
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

struct oclist *addoccurence(struct oclist *p, int oc) {
    if(p==NULL) {
        p=listalloc();
        p->line=oc;
        p->next=NULL;
    } else {
        p->next=addoccurence(p->next,oc);
    }
    return p;
}

void printoccurrence(struct oclist *p) {
    if(p!=NULL) {
        printf("Line number: %d\n",p->line);
        printoccurrence(p->next);
    }
    free(p);
}

struct oclist *listalloc() {
    return (struct oclist*)malloc(sizeof(struct oclist));
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