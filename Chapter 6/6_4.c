#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define WORDMAX 100

#define BUFMAX 100

int buf[BUFMAX];
int bufp;

struct wordcount {
    char *w;
    int count;
};

struct tnode {
    char *w;
    int count;
    struct tnode *left;
    struct tnode *right;
};

int ndwords;

struct tnode *addtree(struct tnode *p, char *w);
void treeprintf(struct tnode *p);
struct tnode *talloc();
char *strdupl(char *s);
struct wordcount *putarray(struct tnode *p, struct wordcount *aw);
void sort(struct wordcount *aw);
void arrayprintf(struct wordcount *p);

void ungetch(int c);
int getch();
int getword(char *s, int lim);

int main() {
    char s[WORDMAX];
    struct tnode *p;
    p=NULL;
    while(getword(s,WORDMAX)!=EOF)
        if(isalpha(s[0]))
            p=addtree(p,s);
    printf("ND;%d\n",ndwords);
    struct wordcount *aw;
    aw=(struct wordcount*)malloc(ndwords*sizeof(struct wordcount));
    //treeprintf(p);
    putarray(p,aw);
    sort(aw);
    arrayprintf(aw);
    free(aw);
}

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;
    if(p==NULL) {
        p=talloc();
        p->w=strdupl(w);
        p->count=1;
        ndwords++;
    } else if((cond=strcmp(w,p->w))==0) {
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
        printf("%s==>%d\n",p->w,p->count);
        treeprintf(p->right);
    }
    free(p);
}

void arrayprintf(struct wordcount *p) {
    for(int i=0; i<ndwords; i++) {
        printf("%s==>%d\n",p->w,p->count);
        p++;
    }
}

void sort(struct wordcount *aw) {
    struct wordcount temp;
    for(int i=0; i<ndwords-1; i++) {
        for(int j=0; j<ndwords-1-i; j++) {
            if((aw+j)->count>(aw+j+1)->count) {
                temp.count=(aw+j)->count;
                temp.w=(aw+j)->w;
                (aw+j)->count=(aw+j+1)->count;
                (aw+j)->w=(aw+j+1)->w;
                (aw+j+1)->count=temp.count;
                (aw+j+1)->w=temp.w;
            }
        }
    }
}

struct wordcount *putarray(struct tnode *p, struct wordcount *aw) {
    if(p!=NULL) {
        aw=putarray(p->left,aw);
        aw->w=strdupl(p->w);
        aw->count=p->count;
        aw++;
        aw=putarray(p->right,aw);
    }
    free(p);
    return aw;
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
    char *b=s;
    int c;
    while((c=getch())==' '||c=='\t')
        ;
    *s++=c;
    if(isalpha(c)) {
        for( ; --lim>0 && isalnum(c=getch()) ; )
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