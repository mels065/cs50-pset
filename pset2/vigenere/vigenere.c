#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

// For decoding from and to the cipher index
#define UPPERCASE_OFFSET 65
#define LOWERCASE_OFFSET 97
#define ALPHA_WRAP 26

bool is_argc_correct(int argc);

bool has_any_non_alpha_chars(string s);

bool is_non_alpha(char c);

bool is_uppercased(char c);

int get_offset(char c);

int main(int argc, string argv[])
{
    if (!is_argc_correct(argc))
    {
        printf("Provide exactly 1 argument\n");
        return 1;
    }
    if (has_any_non_alpha_chars(argv[1]))
    {
        printf("The argument contains non-alphabetic characters\n");
        return 1;
    }

    string key = argv[1];
    string plaintext = get_string("plaintext: ");
    if (plaintext == NULL)
    {
        printf("Plaintext must have at least 1 character");
        return 1;
    }

    printf("ciphertext: ");
    int j = 0;
    int key_len = strlen(key);
    int p;
    int k;
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // Get the indexes for the cipher
        p = (int) plaintext[i] - get_offset(plaintext[i]);
        k = (int) (toupper(key[j]) - UPPERCASE_OFFSET);

        // In the case that we encounter a non-alpha character in plaintext, just print it
        if (is_non_alpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
        }
        // If not, then we cipher
        else
        {
            // Add the indexes, wrap around, and then add the offset
            printf("%c", (p + k) % ALPHA_WRAP + get_offset(plaintext[i]));
            // Increment j, and if it goes over the length of key, wrap around
            j = (j + 1) % key_len;
        }
    }

    printf("\n");
}

// Make sure only 1 argument was provided
// Note: the 2 includes the program invocation as well
bool is_argc_correct(int argc)
{
    return argc == 2;
}

// Iterate through string and return true if any non-alphabetic characters are encountered
bool has_any_non_alpha_chars(string s)
{
    char c;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        c = toupper(s[i]);
        if (is_non_alpha(c))
        {
            return true;
        }
    }
    return false;
}

// Non-alpha characters are outside of the bounds of upper case and lower case ASCII codes
bool is_non_alpha(char c)
{
    return (c < 'A' || c > 'Z') && (c < 'a' || c > 'z');
}

// Check to see if character is uppercased
bool is_uppercased(char c)
{
    return c >= 'A' && c <= 'Z';
}

// Check to see if the current character is upper or lower cased, and return the appropriate offset
int get_offset(char c)
{
    return is_uppercased(c) ? UPPERCASE_OFFSET : LOWERCASE_OFFSET;
}
