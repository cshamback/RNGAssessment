#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef unsigned __int128 __uint128_t;

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

int print_u128_u(__uint128_t u128)
{
    int rc;
    // check if the value is larger than UINT64_MAX
    // (maximum unsigned 64-bit value)
    if (u128 > UINT64_MAX)
    {
        // if so, divide by the largest power of 10
        // that is still smaller than UINT64_MAX
        __uint128_t leading = u128 / P10_UINT64;
        uint64_t trailing = u128 % P10_UINT64;
        rc = print_u128_u(leading); // prints to console and stores value at the same time

        // print the result of the division
        // also print the remainder mod (P10)
        rc += printf("%." TO_STRING(E10_UINT64) PRIu64, trailing);
    }
    else
    {
        // not too big to fit in a 64-bit unsigned integer
        // convert and print
        uint64_t u64 = u128;
        rc = printf("%" PRIu64, u64);
    }
    return rc; // number of digits can be stored in an int variable
    // print this number using printf("\n%d\n", rc); (%d is a placeholder for rc)
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