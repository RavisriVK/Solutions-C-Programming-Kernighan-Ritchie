#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define WORDMAX 100

#define BUFMAX 100

int buf[BUFMAX];
int bufp;

struct key {
    char *name;
    int count;
} keyword []= {
    "auto",0,
    "break",0,
    "case",0,
    "char",0,
    "const",0,
    "continue",0,
    "default",0,
    "do",0,
    "double",0,
    "else",0,
    "enum",0,
    "extern",0,
    "float",0,
    "for",0,
    "goto",0,
    "if",0,
    "int",0,
    "long",0,
    "register",0,
    "return",0,
    "short",0,
    "signed",0,
    "sizeof",0,
    "static",0,
    "struct",0,
    "switch",0,
    "typedef",0,
    "union",0,
    "unsigned",0,
    "void",0,
    "volatile",0,
    "while",0,
};

int binsearch(char *s, struct key keyword[], int n);
int getword(char *s, int lim);

int getch();
void ungetch(int c);

int main() {
    int c,p,temp;
    int inSingleComment=0;
    int inDoubleComment=0;
    int inStringConstant=0;
    int loc;
    char s[WORDMAX];
    p=getword(s,WORDMAX);
    if(p!=EOF) {
        if(p=='\"')
            inStringConstant=1;
        else if(((loc=binsearch(s,keyword,32))>=0)&&isalpha(s[0])) {
            if((temp=getch())!='_')
                keyword[loc].count++;
            ungetch(temp);
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

            if(inStringConstant==0&&inDoubleComment==0&&inSingleComment==0&&p!='_'&&((loc=binsearch(s,keyword,32))>=0)) {
                if((temp=getch())!='_')
                    keyword[loc].count++;
                ungetch(temp);
            }
            p=c;
        }
    }
    for(int i=0; i<32; i++) {
        if(keyword[i].count) {
            printf("%s==>%d\n",keyword[i].name,keyword[i].count);
        }
    }
}

int binsearch(char *s, struct key keyword[], int n) {
    int low=0;
    int high=n-1;
    int mid;
    while(low<=high) {
        mid=(low+high)/2;
        if(strcmp(s,keyword[mid].name)==0) {
            return mid;
        } else if(strcmp(s,keyword[mid].name)<0) {
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

/*
#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define WORDMAX 100

#define BUFMAX 100

int buf[BUFMAX];
int bufp;

struct key {
    char *name;
    int count;
} keyword []= {
    "auto",0,
    "break",0,
    "case",0,
    "char",0,
    "const",0,
    "continue",0,
    "default",0,
    "do",0,
    "double",0,
    "else",0,
    "enum",0,
    "extern",0,
    "float",0,
    "for",0,
    "goto",0,
    "if",0,
    "int",0,
    "long",0,
    "register",0,
    "return",0,
    "short",0,
    "signed",0,
    "sizeof",0,
    "static",0,
    "struct",0,
    "switch",0,
    "typedef",0,
    "union",0,
    "unsigned",0,
    "void",0,
    "volatile",0,
    "while",0,
};

struct key *binsearch(char *s, struct key *keyword, int n);
int getword(char *s, int lim);

int getch();
void ungetch(int c);

int main() {
    int c,p,temp;
    int inSingleComment=0;
    int inDoubleComment=0;
    int inStringConstant=0;
    struct key *loc;
    char s[WORDMAX];
    p=getword(s,WORDMAX);
    if(p!=EOF) {
        if((loc=binsearch(s,keyword,32))!=NULL) {
            if((temp=getch())!='_')
                loc->count++;
            ungetch(temp);
        }
        if(p=='\"') {
            inStringConstant=1;
            //printf("<StC>");
        }
        while((c=getword(s,WORDMAX))!=EOF) {
            if(inDoubleComment==0 && inStringConstant==0 && c=='/'&&p=='/')
                inSingleComment=1;
            if(inSingleComment==0 && inStringConstant==0 && c=='*'&&p=='/')
                inDoubleComment=1;
            if(inDoubleComment==0 && inSingleComment==0 && c=='\"')
                inStringConstant=1;
            
            if(inSingleComment==1&&c=='\n') 
                inSingleComment=0;
            if(inDoubleComment==1&&c=='/'&&p=='*') 
                inDoubleComment=0;
            if(inStringConstant==1&&c=='\"') 
                inStringConstant=0;

            if(inStringConstant==0&&inDoubleComment==0&&inSingleComment==0&&p!='_'&&((loc=binsearch(s,keyword,32))!=NULL)) {
                if((temp=getch())!='_')
                    loc->count++;
                ungetch(temp);
            }
            p=c;
        }
    }
    for(int i=0; i<32; i++) {
        if(keyword[i].count) {
            printf("%s==>%d\n",keyword[i].name,keyword[i].count);
        }
    }
}

struct key *binsearch(char *s, struct key *keyword, int n) {
    struct key *low=keyword;
    struct key *high=keyword+n-1;
    struct key *mid;
    while (low <= high) {
        mid = low + (high-low) / 2;
        if (strcmp(s, mid->name) < 0)
            high = mid-1;
        else if (strcmp(s, mid->name) > 0)
            low = mid + 1;
        else
           return mid;
    }
    return NULL;
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
*/