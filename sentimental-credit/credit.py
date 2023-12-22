from math import pow


def main():
    number = 0
    while number <= 0:
        number = int(input("Number: "))
    length = len(str(number))
    if length == 13 or length == 15 or length == 16:
        find_cc_name(number, length)
    else:
        print("INVALID")


def find_cc_name(number, length):
    copy = number
    sum1, sum2 = 0, 0
    while copy > 0:
        sum1 += copy % 10
        copy //= 10
        digit = (copy % 10) * 2
        sum2 += (digit % 10) + (digit // 10)
        copy //= 10

    sum1 += sum2
    if sum1 % 10 != 0:
        print("INVALID")
    else:
        check = number // pow(10, length - 2)
        if check == 34 or check == 37:
            print("AMEX")
        elif check == 51 or check == 52 or check == 53 or check == 54 or check == 55:
            print("MASTERCARD")
        elif check // 10 == 4:
            print("VISA")
        else:
            print("INVALID")


main()
