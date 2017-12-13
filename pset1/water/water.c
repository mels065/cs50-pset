#include <stdio.h>
#include <cs50.h>

#define BOTTLES_PER_MINUTE 12

int main(void) {
    printf("How many minutes do you spend in the shower? ");
    int minutes = get_int();

    printf("You use up %i bottles of water when you shower", minutes * BOTTLES_PER_MINUTE);
}
