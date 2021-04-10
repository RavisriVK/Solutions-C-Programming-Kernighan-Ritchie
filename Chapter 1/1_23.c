#include<stdio.h>
int main() {
    int previous=getchar();
    int pprev;
    int current=getchar();
    int inSingle=0;
    int inDouble=0;
    int pQuotes=0;

    while(current!=EOF) {
        if(previous=='/'&&current=='/'&&(pQuotes%2==0)) {
            inSingle=1;
        } else if(previous=='/'&&current=='*'&&(pQuotes%2==0)) {
            inDouble=1;
        } else if(inSingle==0&&inDouble==0) {
            putchar(previous);
        } else if(inSingle==1&&current=='\n') {
            inSingle=0;
        } else if(inDouble==1&&current=='/'&&previous=='*') {
            inDouble=0;
            previous=current;
            current=getchar();
        }
        if(previous=='\"'&&!(current=='\''&&pprev!='\''))
        pQuotes++;
        pprev=previous;  /*hello*/  //yooo
        previous=current;
        current=getchar();
    }
    printf("/*kiki*/");
    putchar(previous);
    return 0;
}
