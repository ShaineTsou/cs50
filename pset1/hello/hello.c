#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask user for their name and greet them with their name
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}