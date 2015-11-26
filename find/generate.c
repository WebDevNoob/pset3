/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
 
// standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // If the number of args given is not 2 and is not 3, output the Usage, indicating [s]eed as optional
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Convert the variable given to an integer (Because C can only pass Char** into main) 
    int n = atoi(argv[1]);

    // If the number of args given is 3, seed the random generator with a long integer that is the integer of the second arg
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    // If no 3rd arg, set the seed to the current time
    {
        srand48((long int) time(NULL));
    }

    // For i less than number of random numbers wanted, print a positive number between 0 and 65536
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
