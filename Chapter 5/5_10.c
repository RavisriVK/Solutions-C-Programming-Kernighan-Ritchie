#include<stdio.h>
#include<math.h>

#define NUMBER '0'

#define MAXVAL 100

void push(double);
double pop(void);
int getop(char s[]);

int OpType(char *s);

int isDigit(int);
double atof(char[]);

int sp=0;
double val[MAXVAL];

int main(int argc, char *argv[]) {
    char *s;
    int temp1,temp2;
    while(argc-->1) {
        switch(OpType(s=*++argv)) {
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
            default:
                printf("ERROR:INVALID COMMAND\n");
                break;
        }
    }
    printf("%lf\n",pop());
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

int OpType(char *s) {
    int nd=0;
    if(!isDigit(*s)&&*s!='.'&&*s!='-') {
        return *s;
    } else if(*s=='-'&&!isDigit(*(s+1))) {
        return *s;
    }
    while(isDigit(*s)||*s=='.') {
        if(*s=='.')
            nd++;
        s++;
    }
    if(nd<=1)
        return NUMBER;
    else
        return -1;
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