import re

MAX_HEIGHT = 23

def main():
    height = get_height()
    print_pyramid(height)


def get_height():
    digit_regex = re.compile('^\d+$')
    while True:
        height = input("Enter a height (no more than {}: ".format(MAX_HEIGHT))
        if digit_regex.match(height):
            height = int(height)
            if height >= 0 and height <= MAX_HEIGHT:
                break

    return height


def print_pyramid(height):
    for i in range(height):
        print("{}{} {}".format(get_padding(height, i), get_bricks(i), get_bricks(i)))


def get_padding(height, i):
    return ' ' * (height - i - 1)


def get_bricks(i):
    return '#' * (i + 1)


if __name__ == '__main__':
    main()
