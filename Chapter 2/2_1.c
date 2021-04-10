#include<stdio.h>
#include<limits.h>
#include<float.h>
#include<math.h>
int main() {
    printf("Ranges of int and char from the limits.h header:\n");
    printf("Range of signed char is %d to %d.\n",CHAR_MIN,CHAR_MAX);
    printf("Range of unsigned char is %d to %d.\n",0,UCHAR_MAX);
    printf("Range of signed short int is %d to %d.\n",SHRT_MIN,SHRT_MAX);
    printf("Range of unsigned short int is %d to %d.\n",0,USHRT_MAX);
    printf("Range of signed int is %d to %d.\n",INT_MIN,INT_MAX);
    printf("Range of unsigned int is %d to %u.\n",0,UINT_MAX);
    printf("Range of signed long int is %ld to %ld.\n",LONG_MIN,LONG_MAX);
    printf("Range of unsigned long int is %d to %lu.\n",0,ULONG_MAX);
    printf("\nRanges of int and char by direct computation:\n");
    printf("Range of signed char is %.0f to %.0f.\n",(-1)*pow(2,8*sizeof(char)-1),pow(2,8*sizeof(char)-1)-1);
    printf("Range of unsigned char is %d to %.0f.\n",0,pow(2,8*sizeof(char))-1);
    printf("Range of signed short int is %.0f to %.0f.\n",(-1)*pow(2,8*sizeof(short)-1),pow(2,8*sizeof(short)-1)-1);
    printf("Range of unsigned short int is %d to %.0f.\n",0,pow(2,8*sizeof(short))-1);
    printf("Range of signed int is %.0f to %.0f.\n",(-1)*pow(2,8*sizeof(int)-1),pow(2,8*sizeof(int)-1)-1);
    printf("Range of unsigned int is %d to %.0f.\n",0,pow(2,8*sizeof(int))-1);
    printf("Range of signed long int is %.0f to %.0f.\n",(-1)*pow(2,8*sizeof(long)-1),pow(2,8*sizeof(char)-1)-1);
    printf("Range of unsigned long int is %d to %.0f.\n",0,pow(2,8*sizeof(long))-1);
    printf("\nRanges of floating-point type from the float.h header:\n");
    printf("Range of float is %g to %g.\n",FLT_MIN, FLT_MAX);
    printf("Range of double is %g to %g.\n",DBL_MIN, DBL_MAX);
    printf("Range of long double is %Lg to %Lg.\n",LDBL_MIN, LDBL_MAX);
    return 0;
}