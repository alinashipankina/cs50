from cs50 import get_int
import re

def main():
    while True:
        card = get_int("Number: ")
        break

    number = str(card)

    if len(number) == 15 and (re.match(r'34', number) or re.match(r'37', number)) and (GetAlgorithmLuna(number)):
        print("AMEX")
    elif len(number) == 16 and (re.match(r'51', number) or re.match(r'52', number) or re.match(r'53', number) or re.match(r'54', number) or re.match(r'55', number)) and (GetAlgorithmLuna(number)):
        print("MASTERCARD")
    elif (len(number) == 13 or len(number) == 16) and re.match(r'4', number) and (GetAlgorithmLuna(number)):
        print("VISA")
    else:
        print("INVALID")



# Расчет алгоритма Луна
def GetAlgorithmLuna(number):
    luna = list(number)
    luna.reverse()

    intLuna = [int(i) for i in luna]
    #print(intLuna)

    # Оболочка для суммирования элементов, умноженных вдвое
    shell = 0

    # Умножение элементов через одну позицию на 2, а также их сложение между собой в переменную shell
    for i in range(1, len(intLuna), 2):
        intLuna[i] *= 2
        #print(intLuna[i])
        if intLuna[i] >= 10:
            intLuna[i] = intLuna[i] // 10 + intLuna[i] % 10
        shell += intLuna[i]
    #print(shell)

    #print(intLuna)

    summa = 0
    # Выявление суммы цифр, которые не были умножены на 2 в предыдущей итерации
    for i in range(0, len(intLuna), 2):
        summa += intLuna[i]
    #print(summa)

    allSumma = shell + summa

    #print(allSumma)

    return allSumma % 10 == 0

main()
