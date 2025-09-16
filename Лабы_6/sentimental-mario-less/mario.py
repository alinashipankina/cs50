from cs50 import get_int

def main():
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break

    # Вывод строк с кирпичами
    for i in range(height):
        print_row(height - i, i + 1)

def print_row(spaces, bricks):
    # Вывод пробелов
    for i in range(spaces - 1):
        print(" ", end="")

    # Вывод кирпичей
    for j in range(bricks):
        print("#", end="")

    print()

main()
