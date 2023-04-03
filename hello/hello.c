#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks the name of the user
    string name = get_string("What's your name?\n");
    // Prints out the name
    printf("hello, %s\n", name);
}