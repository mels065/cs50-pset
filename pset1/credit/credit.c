#include <stdio.h>
#include <string.h>
#include <cs50.h>

#define AMEX_LEN 15
#define AMEX_START_1 34
#define AMEX_START_2 37

#define MASTER_LEN 16
// Since the beginning digits range between 51 to 55 inclusive, we can just check to see if they are within that range
#define MASTER_START_RANGE_1 51
#define MASTER_START_RANGE_2 55

#define VISA_LEN_1 13
#define VISA_LEN_2 16
#define VISA_START 4

bool checksum(long long credit_num);

string get_credit_card_holder(long long credit_num);

bool check_len_proof(int length_proof);

long long ten_to_the_nth(int n);

int main(void)
{
    long long credit_num = get_long_long("Number: ");
    if (checksum(credit_num))
    {
        printf("%s\n", get_credit_card_holder(credit_num));
    }
    else
    {
        printf("INVALID\n");
    }
}

bool checksum(long long credit_num)
{
    long long it = 10;
    long long digit;
    long long sum = 0;
    // STEP 0
    while (credit_num / it > 0)
    {
        digit = (credit_num % (it * 10) / it) * 2;
        sum += (digit / 10) + (digit % 10);
        it *= 100;
    }

    // STEP 1
    it = 1;
    while (credit_num / it > 0)
    {
        if (it == 1)
        {
            digit = credit_num % 10;
        }
        else
        {
            digit = (credit_num % (it * 10) / it);
        }
        sum += digit;
        it *= 100;
    }

    return sum % 10 == 0;
}

string get_credit_card_holder(long long credit_num)
{
    // AMERICAN EXPRESS
    long long length_proof = credit_num / ten_to_the_nth(AMEX_LEN - 1);
    long long start_digits = credit_num / ten_to_the_nth(AMEX_LEN - 2);
    if (check_len_proof(length_proof) && (start_digits == AMEX_START_1
                                         || start_digits == AMEX_START_2))
    {
        return "AMEX";
    }

    // MASTERCARD
    length_proof = credit_num / ten_to_the_nth(MASTER_LEN - 1);
    start_digits = credit_num / ten_to_the_nth(MASTER_LEN - 2);
    if (check_len_proof(length_proof) && (start_digits >= MASTER_START_RANGE_1
                                         && start_digits <= MASTER_START_RANGE_2))
    {
        return "MASTERCARD";
    }

    // VISA
    long long length_proof_1 = credit_num / ten_to_the_nth(VISA_LEN_1 - 1);
    long long length_proof_2 = credit_num / ten_to_the_nth(VISA_LEN_2 - 1);
    long long start_digits_1 = credit_num / ten_to_the_nth(VISA_LEN_1 - 1);
    long long start_digits_2 = credit_num / ten_to_the_nth(VISA_LEN_2 - 1);
    if ((check_len_proof(length_proof_1) || check_len_proof(length_proof_2))
        && (start_digits_1 == VISA_START || start_digits_2 == VISA_START))
    {
        return "VISA";
    }

    return "INVALID";
}

bool check_len_proof(int length_proof)
{
    return length_proof > 0 && length_proof <= 9;
}

long long ten_to_the_nth(int n)
{
    long long result = 1;
    for (int i = 0; i < n; i++)
    {
        result *= 10;
    }

    return result;
}
