#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

// to compile: terminal > gcc main.c utils.c -o main.exe

// Collatz-Weyl
static __uint128_t c[4] = {35553453455, 535345345, 4565464562456, 246565465}; // array of 4 unsigned ints, first item, c[0], must be odd
__uint128_t CWG128();
char *BBS128();

int main()
{
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
            char *resultBBS = BBS128(17, 43, 53);

            printf("Result: \n");
            printf("%s\n", &resultBBS);

            break;
        case 2:
            printf("You have chosen ACORN.\n");
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

    return 0;
}

// 2-line collatz-weyl algorithm CWG128
__uint128_t CWG128(void)
{
    c[1] = (c[1] >> 1) * ((c[2] += c[1]) | 1) ^ (c[3] += c[0]);
    // printf("Intermediate step. C[1]: %d\n", c[1]);

    return c[2] >> 96 ^ c[1];
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