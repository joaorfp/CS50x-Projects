from cs50 import get_float


def main():
    # get an input and turns it in a integer
    input = get_float("Change owed: ") * 100
    while input < 0:
        input = get_float("Change owed: ") * 100
    input = int(input)
    coins = 0

    # discounts 25 cents
    while input >= 25:
        input -= 25
        coins += 1

    # discounts 10 cents
    while input >= 10:
        input -= 10
        coins += 1

    # discounts 5 cents
    while input >= 5:
        input -= 5
        coins += 1

    # discounts 1 cent
    while input >= 1:
        input -= 1
        coins += 1
    # prints the amount of coins
    print(coins)


main()