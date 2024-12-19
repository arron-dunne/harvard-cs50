#include <stdio.h>
#include "../../lib/cs50.h"

/*
The Hello program prompts the user for their name, and then
returns a greeting to them
Full Question: https://cs50.harvard.edu/x/2022/psets/1/hello/
*/

int main(void)
{
    // Ask users name and save to a variable
    string name = get_string("What's your name? : ");

    // Print the users name
    printf("hello, %s\n", name);
}
