#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define WORDMAX 100

#define BUFMAX 100

int buf[BUFMAX];
int bufp;

char *keyword []= {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while"
};

int binsearch(char *s, char *keyword[], int n);
int getword(char *s, int lim);

int getch();
void ungetch(int c);

struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *p, char *w);
void treeprintf(struct tnode *p, int n);
struct tnode *talloc();
char *strdupl(char *s);

int main(int argc, char *argv[]) {
    int c,p,temp;
    int inSingleComment=0;
    int inDoubleComment=0;
    int inStringConstant=0;
    int loc;
    char s[WORDMAX];
    p=getword(s,WORDMAX);
    struct tnode *root;
    root=NULL;
    if(p!=EOF) {
        if(p=='\"')
            inStringConstant=1;
        else if(((loc=binsearch(s,keyword,32))<0)&&isalpha(s[0])) {
            root=addtree(root,s);
        }
        while((c=getword(s,WORDMAX))!=EOF) {
            if(inDoubleComment==0 && inStringConstant==0 && c=='/'&&p=='/')
                inSingleComment=1;
            else if(inSingleComment==0 && inStringConstant==0 && c=='*'&&p=='/')
                inDoubleComment=1;
            else if(inDoubleComment==0 && inSingleComment==0 && inStringConstant==0 && c=='\"')
                inStringConstant=1;
            else if(inSingleComment==1&&c=='\n') 
                inSingleComment=0;
            else if(inDoubleComment==1&&c=='/'&&p=='*') 
                inDoubleComment=0;
            else if(inStringConstant==1&&c=='\"'&&p!='\\')
                inStringConstant=0;
            else if(inStringConstant==0&&inDoubleComment==0&&inSingleComment==0&&p!='_')
                if(((loc=binsearch(s,keyword,32))<0)&&isalpha(s[0])) {
                    root=addtree(root,s);
                }
            p=c;
        }
    }
    treeprintf(root,atoi(argv[1]));
}

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;
    if(p==NULL) {
        p=talloc();
        p->word=strdupl(w);
    } else if((cond=strcmp(w,p->word))==0) {
        ;
    } else if(cond<0) {
        p->left=addtree(p->left,w);
    } else {
        p->right=addtree(p->right,w);
    }
    return p;
}

void treeprintf(struct tnode *p, int n) {
    static char last[WORDMAX]="";
    if(p!=NULL) {
        treeprintf(p->left,n);
        if(strncmp(p->word,last,n)!=0) {
            printf("GROUP:");
            for(int i=0; p->word[i]!='\0' && i<n; i++)
            putchar(p->word[i]);
            putchar('\n');
        }
        strcpy(last,p->word);
        printf("%s\n",p->word);
        treeprintf(p->right,n);
    }
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

int binsearch(char *s, char *keyword[], int n) {
    int low=0;
    int high=n-1;
    int mid;
    while(low<=high) {
        mid=(low+high)/2;
        if(strcmp(s,keyword[mid])==0) {
            return mid;
        } else if(strcmp(s,keyword[mid])<0) {
            high=mid-1;
        } else {
            low=mid+1;
        }
    }
    return -1;
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