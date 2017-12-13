#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool is_letter(char c);

bool is_space(char c);

int main(void)
{
    string name = get_string();

    // Used to see if a space was the last checked character
    bool checked_spaces = true;
    char current;
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        // Uppercase it right away so it's easier to check
        current = toupper(name[i]);

        // If it's the first letter after encountering space(s)
        if (checked_spaces && is_letter(current))
        {
            printf("%c", current);
            checked_spaces = false;
        }
        // If it's the first space after encountering letter(s)
        else if (!checked_spaces && is_space(current))
        {
            checked_spaces = true;
        }
    }

    printf("\n");
}

bool is_letter(char c)
{
    return c >= 'A' && c <= 'Z';
}

bool is_space(char c)
{
    return c == ' ';
}
