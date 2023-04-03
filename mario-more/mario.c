#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Main "loop for" to print every line
    for (int index = 0; index < height; index += 1)
    {
        // first "loop for" to print the blank spaces before the first hash
        for (int space = 0; space < height - index - 1; space += 1)
        {
            printf(" ");
        }
        // prints the left half of the pyramid
        for (int hash = 0; hash <= index; hash += 1)
        {
            printf("#");
        }
        // prints the space between each half
        printf("  ");
        // prints the right half of the pyramid
        for (int hash2 = 0; hash2 <= index; hash2 += 1)
        {
            printf("#");
        }
        // breaks the line
        printf("\n");
    }
}