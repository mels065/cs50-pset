/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

#define LIMIT 65536

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n <= 0) return false;

    int start = 0;
    int end = n;
    int middle;
    while (start <= end)
    {
        middle = (start + end) / 2;
        if (value == values[middle]) return true;
        if (value > values[middle]) start = middle + 1;
        else end = middle - 1;
    }

    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int keyArr[LIMIT];
    for (int i = 0; i < n; i++)
    {
        keyArr[values[i]] += 1;
    }

    int i = 0;
    for (int j = 0; j <= n; j++)
    {
        for (int k = 0; k < keyArr[j]; k++)
        {
            values[i] = j;
            i++;
        }
    }
}
