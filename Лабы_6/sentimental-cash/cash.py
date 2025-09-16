from cs50 import get_float


def main():

    while True:
        cash = get_float("Change: ")
        if cash > 0.00:
            break

    quarter = GetQuarter(cash)
    # print(quarter)
    cash = round((cash - (quarter * 0.25)), 2)
    # print(f"{cash:.2f}")
    # print(cash)

    dime = GetDime(cash)
    # print(dime)
    cash = round((cash - (dime * 0.10)), 2)
    # print(f"{cash:.2f}")
    # print(cash)

    nickel = GetNickel(cash)
    # print(nickel)
    cash = round((cash - (nickel * 0.05)), 2)
    # print(f"{cash:.2f}")
    # print(cash)

    penny = GetPenny(cash)
    # print(penny)
    cash = round((cash - (penny * 0.01)), 2)
    # print(f"{cash:.2f}")
    # print(cash)

    count = quarter + dime + nickel + penny
    print(count)

# Расчет 25-центовиков
def GetQuarter(money):
    quarter = 0

    while money > 0.24:
        quarter += 1
        money = money - 0.25

    return quarter

# Расчет 10-центовиков
def GetDime(money):
    dime = 0

    while money > 0.09 and money < 0.25:
        dime += 1
        money = money - 0.10

    return dime

# Расчет 5-центовиков


def GetNickel(money):
    nickel = 0

    while money > 0.04 and money < 0.10:
        nickel += 1
        money = money - 0.05

    return nickel

# Расчет 1-центовиков


def GetPenny(money):
    penny = 0

    while money >= 0.01:
        penny += 1
        money = money - 0.01

    return penny


main()
