/*The point was to show that EOF is an integer and not a character, and therefore can't be stored in the character array buf. But no problems seem to arise when I try to store EOF in a char type variable!*/

#include<stdio.h>
#include<stdio.h>
#include<math.h>

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

int isDigit(int);
int isVariable(int);
int isAnswer(int);
int isEngaged(int);
double atof(char[]);

double variables[26];
int engage[26];
int lastEngaged;
double ans;

int sp=0;
double val[MAXVAL];

int proceed=1;

int main() {
    int type;
    char s[MAXOP];
    int temp1,temp2;
    while(proceed) {
        type=getop(s);
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
                if(sp!=0)
                printf("%lf\n",(ans=pop()));
                break;
            case EOF:
                printf("%lf\n",(ans=pop()));
                proceed=0;
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
    int c,i=0,d;
    static int start=0,session=1;
    if(start>0) {
        c=start;
        if(c=='\n') {
            start=0;
            return '\n';
        }
    } else {
        c=getchar();
    } 
    start=getchar();
    while(c==' '||c=='\t') {
        c=start;
        if(c=='\n') {
            start=0;
            return '\n';
        }
        start=getchar();
    }
    s[0]=c;
    s[1]='\0';
    if(!isDigit(c)) {
        if(isAnswer(c)) {
            return ANSWER;
        } else if(isVariable(c)) {
            return VARIABLE;
        } else if(c!='.'&&c!='-') {
            return c;
        } else if(c=='.'&&isDigit(start)) {
            ;
        } else if(c=='-'&&isDigit(start)) {
            ;
        } else {
            return c;
        } 
    }
    for(i=1;isDigit(c=start);i++) {
        s[i]=c;
        start=getchar();
    }
    if(c=='.') {
        start=getchar();
        s[i++]=c;
        for(;isDigit(c=start);i++) {
            s[i]=c;
            start=getchar();
        }
    }
    s[i]='\0';
    return NUMBER;
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