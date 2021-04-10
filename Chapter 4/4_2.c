#include<stdio.h>
#include<math.h>
int isSpace(char c) {
    if(c==' '||c=='\t')
    return 1;
    else 
    return 0;
}
int isDigit(char c) {
    if(c>='0'&&c<='9')
    return 1;
    else
    return 0;
}
double Pow(double b, int p) {
    int sign=1;
    double value=1.0;
    if(p<0) {
        sign=-1;
        p=-p;
    }
    for(int i=0; i<p;i++) {
        value*=b;
    }
    if(sign==-1)
    value=1.0/value;
    return value;
}
double atof(char s[]) {
    int i,sign,power;
    double value;
    for(i=0;isSpace(s[i]);i++)
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
        value+=(s[i]-'0')*Pow(10.0,power);
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
    value=value*Pow(10.0,power);
    return value;
}
int main() {
    char s[]="12.56e3";
    printf("%lf\n",atof(s));
}