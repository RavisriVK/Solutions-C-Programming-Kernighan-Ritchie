 #include<stdio.h>
 #include<ctype.h>

int getInt(int *pn) {
    static int lp=0;
    if(lp==0)
    lp=getchar();
    int c, sign=1;
    *pn=0;
    while(isspace(c=lp)) {
        lp=getchar();
    }
    lp=getchar();
    if(c=='-'&&isdigit(lp)) {
        sign=-1;
        c=lp;
        lp=getchar();
    } else if(c=='+'&&isdigit(lp)) {
        c=lp;
        lp=getchar();
    } else if(!isdigit(c)) {
        return 0;
    }
    while(isdigit(c)) {
        *pn=*pn*10 + (c-'0');
        c=lp;
        if(isdigit(lp))
        lp=getchar();
        else
        break;
    }
    *pn*=sign;
    return 1;
}
int main() {
    int x,y;
    getInt(&x);
    getInt(&y);
    printf("%d\n",x+y);
}