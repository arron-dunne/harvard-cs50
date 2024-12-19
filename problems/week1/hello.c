#include <stdio.h>
#include "../../lib/cs50.h"

int main(void)
{
    // Ask users name and save to a variable
    string name = get_string("What's your name? : ");

    // Print the users name
    printf("hello, %s\n", name);
}
