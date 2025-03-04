#include <stdio.h>

#include "utils.h"

// to compile: terminal > gcc main.c utils.c -o main.exe

// Collatz-Weyl
static __uint128_t c[4] = {35553453455, 535345345, 4565464562456, 246565465}; // array of 4 unsigned ints, first item, c[0], must be odd
__uint128_t CWG128();

int main()
{
    while (1)
    {
    start:
        printf("Choose an RNG algorithm:\n");

        int in = 0;

        printf("\t1. Blum-Blum-Shub (BBS)\n");
        printf("\t2. Lagged Fibonacci Generator (LFG)\n");
        printf("\t3. Collatz-Weyl\n");

        scanf("%d", &in); // %d means the input is an integer

        switch (in)
        {
        case 1:
            printf("You have chosen BBS.\n");
            break;
        case 2:
            printf("You have chosen LFG.\n");
            break;
        case 3:
            printf("You have chosen Collatz-Weyl\n");
            __uint128_t result = CWG128();

            printf("Result: \n");
            print_u128_u(result);
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
    printf("Intermediate step. C[1]: %d\n", c[1]);

    return c[2] >> 96 ^ c[1];
}