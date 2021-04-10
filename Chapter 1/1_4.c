#include <stdio.h>
int main()
{
    float fahr, celsius;
    int lower, upper, step;
    lower=0;
    upper=300;
    step=20;
    celsius = lower;
    printf("Celsius\tFarenheit\n");
    while (celsius <= upper) {
    fahr = 32.0 + (9.0/5.0)*celsius;
    printf("%-7.0f\t%-10.1f\n", celsius, fahr);
    celsius = celsius + step;
    }
}