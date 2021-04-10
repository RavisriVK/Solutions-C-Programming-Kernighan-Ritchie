 #include<stdio.h>
 #include<ctype.h>
 #include<math.h>

int getFloat(float *pn) {
    static int lp=0;
    if(lp==0)
    lp=getchar();
    int c, sign=1, dec=0;
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
    } else if(!isdigit(c)&&c!='.') {
        return 0;
    }
    while(isdigit(c)) {
        *pn=*pn*10 + (c-'0');
        if(isdigit(lp)) {
            c=lp;
            lp=getchar();
        } else
            break;
    }
    if(lp=='.') {
        c=lp;
        lp=getchar();
        while(isdigit(lp)) {
            dec++;
            *pn=*pn*10 + (lp-'0');
            c=lp;
            lp=getchar();
        }
    }
    *pn=(float)(*pn/pow(10.0,dec));
    *pn*=sign;
    return 1;
}
int main() {
    float x,y;
    getFloat(&x);
    getFloat(&y);
    printf("%f\n",x+y);
}