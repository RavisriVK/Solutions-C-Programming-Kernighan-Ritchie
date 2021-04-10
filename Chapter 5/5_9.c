#include<stdio.h>
static int daytab[2][12]= 
{ {31,28,31,30,31,30,31,31,30,31,30,31},
{31,29,31,30,31,30,31,31,30,31,30,31} };

int day_of_year(int day, int month, int year) {
    int leap= (year%4==0&&year%100!=0)||year%400==0;
    if((day<1)||(month<1)||(day>*(*(daytab+leap)+month-1)))
    return -1;
    for(int i=1; i<month; i++)
        day+=*(*(daytab+leap)+i-1);
    return day;
}
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap= (year%4==0&&year%100!=0)||year%400==0;
    if( (yearday<1) || ( yearday> (leap?366:365) ) ) {
        *pmonth=-1;
        *pday=-1;
        return ;
    }
    int i;
    for(i=0;yearday>*(*(daytab+leap)+i);i++)
        yearday-=*(*(daytab+leap)+i-1);
    *pday=yearday;
    *pmonth=i+1;
}
int main() {
    int d=31,m=4,y=2020;
    printf("%d\n",day_of_year(d,m,y));
    
}