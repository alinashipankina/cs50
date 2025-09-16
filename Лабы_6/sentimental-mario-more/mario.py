from cs50 import get_int

def main():
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break

    for i in range(height):
        print_row(height - i, i + 1)

# Печать всех сторон пирамиды, начиная с левой
def print_row(spaces, bricks):
    for i in range(spaces - 1):
        print(" ", end="")

    for j in range(bricks):
        print("#", end="")

    print(" " * 2, end="")

    print_row_right(bricks)

# Печать правой стороны пирамиды
def print_row_right(bricks):
    for i in range(bricks):
        print("#", end="")

    print()

main()
