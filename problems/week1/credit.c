#include <stdio.h>
#include "../../lib/cs50.h"

/*
Input a credit card number and determine whether it's a
Visa, Mastercard or Amex. Also check it's a valid card
number using Luhn's Algorithm.
(https://cs50.harvard.edu/x/2022/psets/1/credit/)
*/

int main(void)
{
    // Initialise variable
    int first_number;
    int second_number;

    // Get the user to input card number
    long number = get_long("Card Number: ");

    // Start the sum at 0
    int sum = 0;

    // Start card length counter at 0
    int i = 0;

    // While the card number is more than 2 digits long
    while (number >= 1)
    {
        // Save the second to last number
        if (number < 100 && number > 9)
        {
            second_number = number % 10;
        }

        // Save the first number
        if (number < 10)
        {
            first_number = number;
        }

        // Increment the length conuter
        i++;
        // Get the last digit
        int digit = number % 10;
        // If the length counter is odd add the sum
        if (i % 2 == 1)
        {
            sum += digit;
        }
        // If the length counter is even, double the sum and add the digits
        else
        {
            // Double the digit
            digit = digit * 2;
            // If the doubled digit is 2 digits, add the digits
            if (digit >= 10)
            {
                sum += digit % 10;
                sum += digit / 10;
            }
            // Otherwise add the digit times 2
            else
            {
                sum += digit;
            }
        }

        // Remove the last digit from the number
        number = number / 10;
    }

    bool sumcheck = (sum % 10 == 0);

    if (sumcheck)
    {
        if (first_number == 3
            && (second_number == 4 || second_number == 7)
            && i == 15)
        {
            printf("AMEX\n");
        }
        else if (first_number == 5
                 && (second_number == 1 || second_number == 2
                     || second_number == 3 || second_number == 4
                     || second_number == 5) && i == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (first_number == 4
                 && (i == 13 || i == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}