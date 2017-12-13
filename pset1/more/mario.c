#include <stdio.h>
#include <string.h>
#include <cs50.h>

#define HEIGHT_CAP 23
#define GAP_SPACES 2

void printSpaces(int n);

void printPyramid(int i);


int main(void)
{
    int height;

    do
    {
        height = get_int("Enter a height between 0 and %i: ", HEIGHT_CAP);
    }
    while (height < 0 || height > HEIGHT_CAP);

    for (int i = 0; i < height; i++)
    {
        printSpaces(height - (i + 1)); // Thisformula determines the number of spaces
        printPyramid(i);
        printSpaces(GAP_SPACES);
        printPyramid(i);

        printf("\n");
    }
}

void printSpaces(int n)
{
    for (int j = 0; j < n; j++)
    {
        printf(" ");
    }
}

void printPyramid(int i)
{
    for (int j = 0; j < i + 1; j++)
    {
        printf("#");
    }
}

