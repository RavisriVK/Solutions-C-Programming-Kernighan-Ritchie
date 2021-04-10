#include<stdio.h>
#include<math.h>

#define MAXOP 100
#define NUMBER '0'
#define VARIABLE 'V'

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

int isDigit(int);
double atof(char[]);

int sp=0;
double val[MAXVAL];

char buf[BUFSIZE];
int bufp=0;

int main() {
    int type;
    char s[MAXOP];
    int temp1,temp2;
    while((type=getop(s))!=EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
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
                printf("%lf\n",pop());
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
    while((c=getch())==' '||c=='\t')
        ;
    s[0]=c;
    s[1]='\0';
    if(!isDigit(c)) {
        if(c!='.'&&c!='-') {
            return c;
        } else if(c=='.') {
            ;
        } else if(c=='-'&&isDigit(d=getch())) {
            ungetch(d);
        } else {
            ungetch(d);
            return c;
        } 
    }
    for(i++;isDigit(c=getch());i++)
        s[i]=c;
    if(c=='.') {
        s[i++]=c;
        for(;isDigit(c=getch());i++)
            s[i]=c;
    }
    s[i]='\0';
    //if(c!=EOF)
        ungetch(c);
    return NUMBER;
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

int isDigit(int c) {
    if(c>='0'&&c<='9')
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