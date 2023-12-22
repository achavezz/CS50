#include <cs50.h>
#include <math.h>
#include <stdio.h>

int find_length(long number);
string find_cc_name(long number, int length);

int main(void)
{

    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    int length = find_length(number);
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
    }
    else
    {
        string cc_name = find_cc_name(number, length);
        printf("%s\n", cc_name);
    }
}

int find_length(long number)
{
    int length = 0;
    while (number != 0)
    {
        number /= 10;
        length++;
    }
    return length;
}

string find_cc_name(long number, int length)
{
    int sum1 = 0;
    int sum2 = 0;
    long copy = number;
    do
    {
        sum1 += copy % 10;
        copy /= 10;
        int digit = (copy % 10) * 2;
        sum2 += digit % 10 + digit / 10;
        copy /= 10;
    }
    while (copy > 0);
    sum1 += sum2;
    printf("sum1: %d\n", sum1);
    if (sum1 % 10 != 0)
    {
        return "INVALID";
    }
    else
    {
        int check = number / pow(10, length - 2);
        if (check == 34 || check == 37)
        {
            return "AMEX";
        }
        else if (check == 51 || check == 52 || check == 53 || check == 54 || check == 55)
        {
            return "MASTERCARD";
        }
        else if (check / 10 == 4)
        {
            return "VISA";
        }
        else
        {
            return "INVALID";
        }
    }
}