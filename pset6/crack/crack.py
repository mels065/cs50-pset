import crypt
import sys

NUM_OF_ARGS = 2
PW_LENGTH = 4
UPPER_A_CODE = 65
UPPER_Z_CODE = 90
LOWER_A_CODE = 97
LOWER_Z_CODE = 122

def main():
    if (not has_argument()):
        print("Must have exactly {} arguments".format(NUM_OF_ARGS))
        return 1

    for n in range(1, PW_LENGTH+1):
        pw = get_password(n, sys.argv[1])
        if pw:
            print(pw)
            break


def has_argument():
    return len(sys.argv) == NUM_OF_ARGS


def get_password(n, hash_val, pw=""):
    if n == 0:
        if (crypt.crypt(pw, hash_val[:2]) == hash_val): return pw
        else: return None

    for c in [chr(i) for i in range(UPPER_A_CODE, LOWER_Z_CODE + 1) if is_alpha_char_index(i)]:
        new_pw = get_password(n-1, hash_val, pw+c)
        if new_pw: return new_pw

    return None


def is_alpha_char_index(i):
    return not (i > UPPER_Z_CODE and i < LOWER_A_CODE)


if __name__ == '__main__':
    main()
