#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_grid(int height);

int main(void)
{
    int height = get_height();
    print_grid(height);
}

int get_height(void)
{
    int size;
    do
    {
        size = get_int("Height: ");
    }
    while (!(size > 0 && size < 9));

    return size;
}

void print_grid(int height)
{
    for (int i = 0; i < height; i++)
    {
        int diff = height - (i + 1);
        // add spaces to left of row
        for (int k = 0; k < diff; k++)
        {
            printf(" ");
        }

        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("  ");

        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // add spaces to right of roww
        for (int k = 0; k < diff; k++)
        {
            printf("");
        }

        printf("\n");
    }
}