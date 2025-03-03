#include <stdio.h>

// to compile: terminal > gcc main.c -o main.exe

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
            break;
        default:
            printf("Incorrect input. Please try again.\n");
            break;
            goto start;
        }
    }

    return 0;
}