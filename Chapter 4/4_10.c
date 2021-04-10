#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define VARIABLE 'V'
#define ANSWER 'A'
#define MAXLINE 100

#define MAXVAL 100

#define BUFSIZE 100

void push(double);
double pop(void);
void print(void);
void duplicate(void);
void clear(void);
void swap(void);
int getop(char s[]);

int getLine();

int isDigit(int);
int isVariable(int);
int isAnswer(int);
int isEngaged(int);
int strLen(char[]);
double atof(char[]);

double variables[26];
int engage[26];
int lastEngaged;
double ans;

int sp=0;
double val[MAXVAL];

char line[MAXLINE];
int lp;

int main() {
    int type;
    char s[MAXOP];
    int temp1,temp2;
    getLine();
    while((type=getop(s))!=EOF) {
        //printf("(%s)",s);
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
                //printf("%c=>",type);
                push(pop()+pop());
                break;
            case '*':
                //printf("%c=>",type);
                push(pop()*pop());
                break;
            case '-':
                //printf("%c=>",type);
                push((-1)*(pop()-pop()));
                break;
            case '/':
                //printf("%c=>",type);
                temp1=pop();
                if(temp1!=0)
                push(pop()/temp1);
                else
                printf("ERROR:DIVISION BY ZERO\n");
                break;
            case '%':
                //printf("%c=>",type);
                temp2=pop();
                temp1=pop();
                if(temp1==floor(temp1)&&temp2==floor(temp2))
                push(temp1%temp2);
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
            case '\n':
                //printf("\\n");
                printf("%lf\n",(ans=pop()));
                break;
            default:
                //printf("%c=>",type);
                printf("ERROR:INVALID COMMAND %c\n",type);
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
        //printf("Pop %lf=>",val[sp-1]);
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
    int c,i;
    while((c=line[lp++])==' '||c=='\t')
        ;
    s[0]=c;
    if(c=='\n') {
        getLine();
        return '\n';
    }
    s[1]='\0';
    if(!isDigit(c)) {
        if(isAnswer(c)) {
            return ANSWER;
        } else if(isVariable(c)) {
            return VARIABLE;
        } else if(c!='.'&&c!='-') {
            return c;
        } else if(c=='.'&&isDigit(line[lp])) {
            ;
        } else if(c=='.'&&!isDigit(line[lp])) { 
            return c;
        } else if(c=='-'&&isDigit(line[lp])) {
            ;
        } else {
            return c;
        } 
    }
    for(i=1;isDigit(c=line[lp++]);i++) {
        s[i]=c;
    }
    if(c=='.') {
        s[i++]=c;
        for(;isDigit(c=line[lp++]);)
            s[i++]=c;
    }
    s[i]='\0';
    return NUMBER;
}

/*int getop(char s[]) {
    if(sscanf(line,"%s",s)==0)
        return '\n';
    if(isAnswer(*s))
        return ANSWER;
    else if(isVariable(*s))
        return VARIABLE;
    else if(*s!='-'&&isdigit(*s)==0)
        return *s;
    else if(strcmp("-",s)==0)
        return '-';
    else
        return NUMBER;
} */

int getLine()
{
    int c=getchar();
    int i;
    for(i=0;(c!='\n'&&c!=EOF)&&(i<MAXLINE-1);++i)
    {
        line[i]=c;
        c=getchar();
    }
    if(c=='\n') {
        line[i]='\n';
        ++i;
    }
    line[i]='\0';
    lp=0;
    return i;
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

int strLen(char s[]) {
    int i;
    for(i=0; s[i]!='\0'; i++)
    ;
    return i;
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

double atof(char s[]) {
    int i,sign,power;
    double value;
    for(i=0;(s[i]==' '||s[i]=='\t');i++)
    ;
    sign=(s[i]=='-')?-1:1;
    if(s[i]=='-'||s[i]=='+')
    i++;
    for(value=0;isDigit(s[i]);i++) {
        value=10*value+(s[i]-'0');
    }
    if(s[i]=='.')
    i++;
    for(power=-1;isDigit(s[i]);i++,power--) {
        value+=(s[i]-'0')*pow(10.0,power);
    }
    value*=sign;
    if(s[i]=='e'||s[i]=='E')
    i++;
    sign=(s[i]=='-')?-1:1;
    if(s[i]=='-'||s[i]=='+')
    i++;
    for(power=0;isDigit(s[i]);i++) {
        power=power*10+(s[i]-'0');
    }
    power*=sign;
    value=value*pow(10.0,power);
    return value;
}