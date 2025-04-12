#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

typedef unsigned __int128 __uint128_t;

// to compile: terminal > gcc main.c utils.c -o main.exe

// Collatz-Weyl
static __uint128_t c[4] = {35553453455, 535345345, 4565464562456, 246565465}; // array of 4 unsigned ints, first item, c[0], must be odd
static __uint128_t x;

__uint128_t CWG128();
char *BBS128();
double *acorn();

int main()
{
    __uint128_t input = 298837938472475740085289658204777285555;
    print_u128_u(input);
    char *result = u128ToString(input, 128);
    printf("%s\n", result);
    /*
    while (1)
    {
    start:
        printf("Choose an RNG algorithm:\n");

        int in = 0;

        printf("\t1. Blum-Blum-Shub (BBS)\n");
        printf("\t2. ACORN\n");
        printf("\t3. Collatz-Weyl\n");

        scanf("%d", &in); // %d means the input is an integer

        switch (in)
        {
        case 1:
            printf("You have chosen BBS.\n");
            char *resultBBS = BBS128(107, 7793, 7919);

            printf("Result: \n");
            printf("%s\n", resultBBS);

            free(resultBBS);

            break;
        case 2:
            printf("You have chosen ACORN.\n");
            printf("You will get 128 random doubles between [0, 1). Please choose a seed of at least 10^5.");
            scanf("%d", &in);

            acorn(in, 128);

            break;
        case 3:
            printf("You have chosen Collatz-Weyl\n");
            __uint128_t resultCW = CWG128();

            printf("Result: \n");
            print_u128_u(resultCW);
            printf("\n");

            break;
        default:
            printf("Incorrect input. Please try again.\n");
            break;
            goto start;
        }
    }
        */

    return 0;
}

static uint64_t a, weyl, s; // s must be odd
__uint128_t CWG128_64(void)
{
    x = (x | 1) * ((a += x) >> 1) ^ (weyl += s);
    return a >> 48 ^ x;
}

// BBS algorithm:

/*
    x_j ≡ x^2_{j−1} (mod n)
    b_j = x_j (mod 2) // least significant bit of x_j
*/

// PREREQUESITES:
// - p and q must be prime.
// - gcd(x0, pq) = 1
char *BBS128(int x0, int p, int q)
{
    // returns bit string of length 128
    // using string because not base 10
    char *result = (char *)malloc((128 + 1) * sizeof(char));

    int n = p * q;
    int prevx = x0;

    printf("n: %d prevx: %d ", n, x0);

    // repeat once for every digit in the final result
    for (int i = 0; i < 128 - 1; i++)
    {
        int xi = prevx * prevx;
        xi = xi % n;
        printf("xi: %d prevx: %d", xi, prevx);
        prevx = xi;

        char b = (xi % 2) + '0'; // converts (xi % 2), which can only be 0 or 1, to a char

        printf(" b: %c\n", b); // %c for print char
        result[i] = b;
    }

    // printf("%s\n", result);
    result[128] = '\0'; // make it null terminated so we can print

    return result;
}

double *acorn(int seed, int length)
{
    // initialize
    int k = 15;               // must be between 10 and 20
    long long M = pow(2, 60); // recommended by wikramatna, 2^30 is mid, 2^120 is exceptional
    printf("M value (2^60): %lld\n", M);

    double Y1[length];
    double Y2[length];

    seed = seed % M;
    printf("Seed: %d\n", seed);

    // initialize Y1 with seed
    for (int i = 0; i < length; i++)
    {
        Y1[i] = seed;
    }

    // main calculation sequence
    for (int i = 0; i < k; i++)
    {
        Y2[0] = seed;

        for (int j = 1; j < length; j++)
        {
            Y2[j] = ((long long)(Y1[j] + Y2[j - 1])) % M;
            Y1[j] = Y2[j];
        }
    }

    printDoubleArr(Y2);

    // convert every Y2 to double
    for (int i = 0; i < length; i++)
    {
        // divide every Y by M
        Y2[i] = Y2[i] / M;
    }

    printDoubleArr(Y2);
}