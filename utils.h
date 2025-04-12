#include <stdio.h>
#include <inttypes.h>
    

typedef unsigned __int128 __uint128_t;
void  print_u128_u(__uint128_t u128, char* buf);
void printDoubleArr(double *arr);

int getLengthOfNum(double input);

char *u128ToString(__uint128_t u128, int len);
char *strToBinary(__uint128_t input, int len);
char *doubleArrToBinary(double *arr, int len);
