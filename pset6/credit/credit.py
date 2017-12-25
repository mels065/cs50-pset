import re

INVALID = 'INVALID'

def main():
    num = get_credit_card()

    if luhn(num): print(get_company(num))
    else: print(INVALID)


def get_credit_card():
    NUM_REGEX = re.compile('^\d+$')
    while True:
        num = input("Type in a credit card number: ")
        if (NUM_REGEX.match(num)):
            break

    return num


def luhn(num):
    total = 0
    for digit in [int(num[i]) * 2 for i in range(len(num)-2, -1, -2)]:
        total += (digit // 10) + (digit % 10)

    total += sum([int(num[i]) for i in range(0, len(num), 2)])

    return total % 10 == 0


def get_company(num):
    AMEX = 'AMEX'
    MC = 'MASTERCARD'
    VISA = 'VISA'

    AMEX_LEN = 15
    AMEX_NUMS = re.compile('^3[47]')
    MC_LEN = 16
    MC_NUMS = re.compile('^5[1-5]')
    VISA_LENS = (13, 16)
    VISA_NUM = re.compile('^4')

    if len(num) == AMEX_LEN and AMEX_NUMS.match(num): return AMEX
    elif len(num) == MC_LEN and MC_NUMS.match(num): return MC
    elif len(num) in VISA_LENS and VISA_NUM.match(num): return VISA

    return INVALID

if __name__ == '__main__':
    main()
