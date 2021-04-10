#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define MAXOP 100
#define NUMBER '0'
#define VARIABLE 'V'
#define ANSWER 'A'

#define MAXVAL 100

#define BUFSIZE 100

void push(double);
double pop(void);
void print(void);
void duplicate(void);
void clear(void);
void swap(void);
int getop(char s[]);

int getch(void);
void ungetch(int);
void ungets(char *);

int isDigit(int);
int isVariable(int);
int isAnswer(int);
int isEngaged(int);

double variables[26];
int engage[26];
int lastEngaged;
double ans;

int sp=0;
double val[MAXVAL];

char buf[BUFSIZE];
int bufp=0;

int main() {
    int type;
    char s[MAXOP];
    double temp1,temp2;
    while((type=getop(s))!=EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case VARIABLE:
                if(!isEngaged(s[0])) {
                    engage[s[0]-'a']=1;
                    lastEngaged=s[0]-'a';
                } else {
                    push(variables[s[0]-'a']);
                    lastEngaged=s[0]-'a';
                }
                break;
            case '=':
                variables[lastEngaged]=pop();
                push(variables[lastEngaged]);
                break;
            case ANSWER:
                push(ans);
                break;
            case '+':
                push(pop()+pop());
                break;
            case '*':
                push(pop()*pop());
                break;
            case '-':
                push((-1)*(pop()-pop()));
                break;
            case '/':
                temp1=pop();
                if(temp1!=0)
                push(pop()/temp1);
                else
                printf("ERROR:DIVISION BY ZERO\n");
                break;
            case '%':
                temp2=pop();
                temp1=pop();
                if((temp1==floor(temp1))&&(temp2==floor(temp2)))
                    push(((int)temp1)%((int)temp2));
                else
                    printf("ERROR:MODULUS OF NON INTEGERS\n");
                break;
            case 'S':
                push(sin(pop()));
                break;
            case 'E':
                push(exp(pop()));
                break;
            case 'P':
                temp1=pop();
                push(pow(pop(),temp1));
                break;
            case ';':
                printf("%lf\n",(ans=pop()));
                break;
            default:
                printf("ERROR:INVALID COMMAND\n");
                break;
        }
    }
    return 0;
}

double pop() {
    if(sp==0) {
        printf("ERROR:NO VALUE IN STACK\n");
        return 0.0;
    } else {
        return val[--sp];
    }
}

void push(double f) {
    if(sp<MAXVAL) {
        val[sp++]=f;
        //printf("Push %lf=>",f);
    } else {
        printf("ERROR:STACK FULL\n");
    }
}

void print() {
    if(sp>0) {
        printf("%lf\n",val[sp-1]);
    } else {
        printf("STACK IS EMPTY\n");
    }
}

void clear() {
    for(int i=0; i<sp; i++)
    val[i]=0;
    sp=0;
}

void duplicate() {
    if(sp>0&&sp<(MAXVAL-1)) {
        val[sp]=val[sp-1];
        sp++;
    } else {
        printf("UNABLE TO DUPLICATE\n");
    }
}

void swap() {
    int temp;
    if(sp>1) {
        temp=val[sp-1];
        val[sp-1]=val[sp-2];
        val[sp-2]=temp;
    } else {
        printf("NOT ENOUGH ELEMENTS TO SWAP\n");
    }
}

int getop(char s[]) {
    scanf("%s",s);
    if(isAnswer(*s)) {
        ungets(s+1);
        return ANSWER;
    } else if(isVariable(*s)) {
        ungets(s+1);
        return VARIABLE;
    } else if(*s!='-'&&isdigit(*s)==0) {
        ungets(s+1);
        return *s;
    } else if(strcmp("-",s)==0) {
        return '-';
    } else {
        ungets(s);
        double temp;
        scanf("%lf",&temp);
        sprintf(s,"%lf",temp);
        return NUMBER;
    }
}

int getch() {
    if(bufp>0)
    return buf[--bufp];
    else
    return getchar();
}

void ungetch(int c) {
    if(bufp<BUFSIZE)
    buf[bufp++]=c;
    else
    printf("ERROR:BUFFER FULL\n");
}

void ungets(char s[]) {
    int length=strlen(s);
    for(int i=1; i<=length; i++)
    ungetc(s[length-i],stdin);
}

int isDigit(int c) {
    if(c>='0'&&c<='9')
    return 1;
    else
    return 0;
}

int isVariable(int c) {
    if((c>='a'&&c<='z'))
    return 1;
    else
    return 0;
}

int isAnswer(int c) {
    if(c=='A')
    return 1;
    else
    return 0;
}

int isEngaged(int c) {
    if(engage[c-'a'])
    return 1;
    else 
    return 0;
}