#include<stdio.h>
#include<math.h>
int htoi(char s[]) {
    double value=0;
    int length=0;
    while(s[length]!='\0')
    length++;
    int rem=0;
    if(length>=2&&s[0]=='0'&&(s[1]=='x'||s[1]=='X'))
    rem=2;
    for(int i=0; i<length-rem; i++) {
        if(s[length-i-1]>='0'&&s[length-i-1]<='9')
        value+=(s[length-i-1]-'0')*pow(16.0,i);
        else if(s[length-i-1]>='a'&&s[length-i-1]<='f')
        value+=(10+s[length-1-i]-'a')*pow(16.0,i);
        else if(s[length-i-1]>='A'&&s[length-i-1]<='F')
        value+=(10+s[length-1-i]-'A')*pow(16.0,i);
    }
    return (int)value;
}
int main() {
    printf("%s=%d\n","0xf9e8d7",htoi("0xf9e8d7"));
}