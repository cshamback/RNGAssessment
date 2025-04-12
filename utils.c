#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef unsigned __int128 uint128_t;
typedef unsigned long long u64;

// ===
// =======--------------------------------------------------------------------------------------------------------------------------------------
// PRINTING 128-BIT UNSIGNED INTEGERS
// =======--------------------------------------------------------------------------------------------------------------------------------------
// ===

// GOAL: print as a series of 64 bit integers!

// https://stackoverflow.com/questions/11656241/how-to-print-uint128-t-number-using-gcc
/*
** Using documented GCC type unsigned __int128 instead of undocumented
** obsolescent typedef name __uint128_t.  Works with GCC 4.7.1 but not
** GCC 4.1.2 (but __uint128_t works with GCC 4.1.2) on Mac OS X 10.7.4.
*/

/*      UINT64_MAX 18446744073709551615ULL */

// constant that represents the largest power of 10 that is smaller
// than UINT_64
#define P10_UINT64 10000000000000000000ULL /* 19 zeroes */
#define E10_UINT64 19                      // number of 0s in P10_UINT64

#define STRINGIZER(x) #x
#define TO_STRING(x) STRINGIZER(x)
void print_u128_u(uint128_t u128, char* buf) {
    char b[40];
    int i = 0;
    if (u128==0) {
        buf[0] = '0';
        buf[1] = '\0';
    }
    while(u128 != 0) {
        b[i++] = u128%10 + '0'; 
        u128/= 10;     
    }
    for(int j=0; j < 40; j++){
        buf[j] = b[i-j-1];
    }

}


// prints array of doubles as a series of doubles
void printDoubleArr(double *arr)
{
    size_t size = sizeof(arr) / sizeof(arr[0]);
    // printf("Size: %d size of arr: %d size of first element %llu\n", size, sizeof(arr), sizeof(arr[0]));

    printf("[");
    for (int i = 0; i < 128 - 1; i++)
    {
        printf("%f ,", arr[i]);
    }
    printf("%d]\n", arr[size - 1]);
}

int getLengthOfNum(__uint128_t input)
{
    // base case: num is < 10
    if (input < 10)
    {
        return 1;
    }

    return 1 + getLengthOfNum(input / 10);
}

static const char *charmap = "0123456789";

char *u128ToString(__uint128_t u128)
{
    if (u128 == 0)
    {
        return "0\0";
    }

    // uint128 is at most 40 characters long
    // we need an extra one to insert '\0' to make it printable.
    char *result = (char *)malloc((41) * sizeof(char));
    int index = 0;

    while (u128 > 0)
    {
        result[index++] = '0' + (u128 % 10);

        u128 /= 10;
    }

    result[40] = '\0';
    return result;
}

char *strToBinary(__uint128_t input, int len)
{
    char *u128 = u128ToString(input);
    char *result = (char *)malloc((len + 1) * sizeof(char));

    for (int i = 0; i < len; i++)
    {
        if ((int)u128[i] >= 5)
        {
            result[i] = 1;
        }
        else
        {
            result[i] = 0;
        }
    }

    result[128] = '\0'; // make it null terminated so we can print
    return result;
}

char *doubleArrToBinary(double *arr, int len)
{
    char *result = (char *)malloc((len + 1) * sizeof(char));
    return result;
}
