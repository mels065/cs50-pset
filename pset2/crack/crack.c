#include <stdio.h>
#include <crypt.h>
#include <cs50.h>
#include <string.h>

#define PW_LENGTH 4
#define SALT_LENGTH 2
#define UPPER_A_CODE 65
#define UPPER_Z_CODE 90
#define LOWER_A_CODE 97
#define LOWER_Z_CODE 122

void get_password(int n, char pw[], string hash, string salt);

int main(void)
{
    string hash = get_string("Hash: ");
    char salt[2] = "";

    // Get the first two characters of salt
    salt[0] = hash[0];
    salt[1] = hash[1];

    char pw[5];
    // Get the password, by passing in the reference to pw, which will store the result
    get_password(PW_LENGTH, pw, hash, salt);

    if (strcmp(pw, "0000") == 0)
    {
        printf("No password found");
    }
    else
    {
        printf("%s\n", pw);
    }
}


void get_password(int n, char pw[], string hash, string salt)
{
    // Base case
    if (n == 1)
    {
        // Iterate through A-Z and a-z
        for (int c = UPPER_A_CODE; c <= LOWER_Z_CODE; c++)
        {
            // Ignore the ASCII characters between 'Z' and 'a'
            if (c > UPPER_Z_CODE && c < LOWER_A_CODE)
            {
                continue;
            }
            // Assign character to 0th index
            pw[0] = (char) c;
            // If the password matches, we've found it and can return
            if (strcmp(crypt(pw, salt), hash) == 0)
            {
                return;
            }
        }
        // If we didn't find anything, then assign '0' to 0th character
        pw[0] = '0';
    }
    else
    {
        // Call this function, decrementing n by 1
        get_password(n - 1, pw, hash, salt);
        // If the (n -2)th character does not equal '0', we've found it and can return
        if (pw[n - 2] != '0')
        {
            return;
        }

        // Set current index to n - 1
        int i = n - 1;
        // Iterate through A-Z and a-z
        for (int c = UPPER_A_CODE; c <= LOWER_Z_CODE; c++)
        {
            // Ignore the ASCII characters between 'Z' and 'a'
            if (c > UPPER_Z_CODE && c < LOWER_A_CODE)
            {
                continue;
            }
            // Assign character to i-th index
            pw[i] = (char) c;
            // Call this function, decrementing n by 1
            get_password(n - 1, pw, hash, salt);
            // If the (n -2)th character does not equal '0', we've found it and can return
            if (pw[n - 2] != '0')
            {
                return;
            }
        }

        // If we didn't find anything, then assign '0' to the i-th character
        pw[i] = '0';
    }
}
